## Lab 03
## Ben Holmgren
## benjamin.holmgren1@student.montana.edu
## CSCI 476
## Due 3/2/2021 (noon)


### Task 1.1

Compiling and running the provided code (after correctly setting up my
environment as per the instructions) yielded the following result:

![1.1](1_1.png)

This indicates that running the provided code gives us a shell. Much of
the environment appears to be the same as it was when the code is
executed, as demonstrated by calling 'ls'. But both programs when run 
give us a new shell.

### Task 1.2

In short, main takes a bunch of code put into a string (the exact code
is dependent on whether we want the 32 bit or 64 bit scenario), turns that
string into a function, and calls the function. Now, one may wonder
what that code actually entails? Importantly, this is assembly to execute
programs. Namely, all of these hex values equate to letters, spelling out 
instructions in reverse. Calling 'man ascii', we can see what each of
these hex values equate to. 

Examining this table, and without getting too in the weeds (as the prompt
asks that we **briefly** describe what main does), we discover that for both
programs, execve("/bin/sh", argv, 0) is being called.

### Task 2.1

Running the provided commands, we can find that the distance from the start of
the buffer to ebp is precisely 108. Knowing that the return value lies directly
above the address for ebp, we obtain that the distance between the start
of the buffer and ebp is 108 + 4 = 112.

![108](108.png)

### Task 2.2

We know that the return address is 4 bytes away from the address where ebp
is located. From before, we found that ebp was located at 0xffffcd88, so then
the return address we would expect to be located at 0xffffcd88 + 0xffffcd04 = 0xffffcd8c (just by googling
this computation). 

But this isn't the whole story. We were using the debugger
which makes the stack deeper than it would be if we were just running the 
program normally. By running the provided code to test the stack layout, we
find the address of a variable normally:

![s1](s1.png)

And then running the same code in the debugger, we find the same variable's
 address, while in the debugger, allowing us to estimate the cushion the
debugger is adding to the stack.

![s2](s2.png)

![ds](ds.png)

Then, adding this final cushion to the address we found earlier in the debugger,
we have a good estimation of what return address to use in our attack. Namely,
we want to use ffffcd8c + 0x144 = 0xffffced0.

Then, we use the same shellcode as was used in the 32-bit system in the
prior example. We know that the buffer is of length 517, so we want to 
inject in this shell code right at the end of the buffer, giving us
that ``start = 517 - len(shellcode)``

As described in 2.1, the offset we will use is 112. Filling in each of
these values in their specified location in exploit.py, running exploit.py
and finally stack-L1, we successfully obtain a root shell!

![mainframe](mainframe.png)

And, to reiterate, here is the code that I ran in exploit.py
which let me achieve such a feat:

![payload](payload.png)


