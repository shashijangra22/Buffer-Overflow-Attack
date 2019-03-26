# Title : Buffer Overflow Attack

## Environment Settings
- Using a 32-Bit Operating System(Ubuntu 16.04) because the given shellcode has assembly language instructions written for 32-bit OS.
- Setting up `zsh`.
    1. sudo apt install zsh
    2. cd /bin
    3. sudo rm sh
    4. sudo ln -s /bin/zsh /bin/sh
- Disabling the stack protection by using `-fno-stack-protector` while compiling the code.
- Making the stack executable by using `-z execstack` while compiling the code.
- Disabling ASLR (`Address Space Layout Randomization`) which is a default feature to protect attacks like Buffer Overflow.
- Setting permissions of the vulnerable program to be executable by any user.

## Steps to see the working of overflow attack
- Steps as root user
    - `sudo sysctl -w kernel.randomize_va_space=0`
    - `sudo gcc vuln.c -o vuln -fno-stack-protector -z execstack`
    - `sudo chmod 4755 vuln`
- Steps as non-root user
    - `gcc exploit.c -o exp`
    - `./exp`
    - .`/vuln`
    - Expected outcome is a root shell is spawned which the non-root user can check by the `#` sign or typing the command `whoami` to get the username as `root`

## [Part-1] Approach to Solve the problem
- As we can see that the vuln.c file is vulnerable to buffer overflow attack because it is using the strcpy function (which does not make a check on size of the string it is copying).
- Our file size is 517 bytes and buffer size is 12 bytes that means we can overflow it So, We filled the entire 517 bytes with NO-Operation `\x90` and last 25 bytes with the shell code.
- As our buffer size is 12 bytes, the program will allocate it 20 bytes of memory and 4 bytes of EBP and 4 bytes of return address which we need to modify.
- that means after 24th byte we need to overwrite the address of malicious code so that our vuln program will return back to the malicious code.
- We take the address of any random location in between those 517 bytes and fill that value after the 24th Byte of the buffer so that when our vuln program returns it should point to some No-Op sled which is leading to the malicious code, Hence a shell is spawned with root access because the file is compiled using set-root-uid bit as root permissions.

## [Part-2] Now, we let /bin/sh point back to /bin/bash, and run the same attack developed in the previous task. 
- Can you get a shell?
    - YES
- Is the shell the root shell?
    - NO
- What has happened?
    - This happened because the original shell `/bin/bash` has default protection mechanism by which it automatically drops it's privileges when invoked.
    - Therefore, even if we can “fool” a privileged Set-UID program to invoke a shell, we are not able to retain the privileges within the shell.