## Contact Info

> name: Nimra Sharnez
> email: nish6496@colorado.edu

---

## File Descriptions

> /home/kernel/modules/**Makefile**: 
>>File that tells the compiler to creates a module object. *obj-m* means module. We see in the second line what I typed when I run the *make* command (in the instructions section), I am telling the compiler to create a module object named **part2Module.o**.

>  /home/kernel/modules/**Part2Module.c**:  
>> This is the Loadable Kernel Module (LKM). This object file is intended to add functionality to the running kernel very quickly. In this file, we register our character driver in our init() function and unregister in our exit() function. We bind these functions to be ran when the module is installed/ uninstalled accordingly with the help of **module_init()** and **module_exit**. Inside of this file, I implemented the five functions: **open, close, seek, read** and **write**. I then used a *struct* to point to these implementations so that a user may define a file destination being the associated Character Device to this file, and use these implementations of the five functions. 

>  /home/user/**part3.c**: 
>> This file is a User-Space Test Program. In this file, I give the user the functionality to read, write, seek or exit once this file is ran. A user will utilize the five functions defined in the /home/kernel/modules/**Part2Module.c** file in user space with this test program written in C. 

---

## Instructions

> 1) First, create a Device File by typing the following:
>> sudo mknod –m 777 /dev/simple_character_device c 240 0​
>> NOTE: make sure your major number (second to last in the above command) is unique. Check Linux source tree, I just happened to use 240 since it was available.
> 2) Create a directory called Modules in Kernel space and put the Makefile and Part2Module.c files here.
> 3) Compile the module by running the following make command:
>> ​make -C /lib/modules/$(uname -r)/build M=$PWD ​
>> This should make the kernel module (file ending in .ko)
> 4) Install the module by running the following command:
>> sudo insmod Part2Module.ko
> 5) Run *dmesg* to ensure that it worked, you should see something like:
>> *inside part2_init function*
> 6) Now we are ready to run the User-Space Test Program! Go back into user space (home/user)
> 7) Place the part3.c file here. 
> 8) Compile the file by running the following:
>> gcc part3.c -o part3
> 9) This should create a part3.o object. Run it.
>> ./part3
> 10) You are now able to write, read, seek and exit! Have fun!!!

---