
## Contact Information
name: Nimra Sharnez
email: nish6496@colorado.edu

## File Information
Root is **/home/kernel/linux-hwe-4.15.0**

> ./include/linux/**syscalls.h**
>> This file contains declarations of System Call including the one I added. Just before the end of the file #endif line, I declared the system call **sys_cs3573_add()** with its arguments **int number 1, int number 2, int \*result**. The *asmlinkage* keyword is used to clarify that the parameters of the System Call are all available on the stack.

> ./arch/x86/entry/**syscalls/syscall_64.tbl**
>> This file is the system table of the kernel for x86_64. The table has the pointers to the functions that implement the system calls themselves. The format in which I inputted my new system call is <number> (in this case 334) <abi> (64) <name> (this has to be the same as the .c file that our system call is in, it is the name of the call) and <entry point> (this is the name of the function implementing the system call, this matches its declaration in the *syscalls.h* file.). This file will be read by the script that runs the system call I wrote.

> ./arch/x86/kernel/**Makefile**
>> This file tells the build about the kernel call. This file is where I specified the objects that I wanted to be built (cs3753.o). During the next kernel recompilation, this object will be added to the source.

> ./arch/x86/kernel/**cs3753.c**
>> This is the file I wrote the actual function that implements the system call. I include the header file (kernel.h) which "contains many of the constants and functions used in kernel programming" along with the header file (linkage.h) that "defines macros that are used to keep the stack safe and ordered". I knew to do this from our hello world example!
>> The function does a KERN ALERT to repeat the arguments passed into the function, computes the addition problem, and then does another KERN ALERT to say what the two numbers added together equals. Finally we should expect it to return 0 upon successful compilation.

Additional Files
> **syscall2.c**
>> This is the c file that we compile that gives us our a.out (expected to return 0). This c code calls the system call by its number (334), and passes in the paramaters inside of the main. It stores the return value in *call* and prints out the return value, result of the added numbers. 

> **a.out**
>> a.out is the output of the syscall2.c file which is the return value of the system call (0 if successful) and the result of the numbers added.

> **mydmesg.log**
>> This is the output when **dmesg** is called after compiling *syscall2.c*


## Building and Running Test Program
First compile syscall2.c in the terminal window
> $ gcc syscall2.c
This should give us *a.out* which we can now run
> $ ./a.out
We should expect to see the printf statement in syscall2.c
> System call output: 0 3
The first number is the return value of the system call and the second number is the result parameter that was compiled through the addition of the first two parameters passed in in the syscall.c file

To view the dmesg, just run 
> $ dmesg
This should return the KERN ALERTs.# Operating-Stystems
