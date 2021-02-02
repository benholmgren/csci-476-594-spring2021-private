## Systems & Software: Towards Security
## Ben Holmgren (f15p655)
## benjamin.holmgren1@student.montana.edu
## CSCI 476
## Due 2/2/2021


### Task 1 

* The fork() syscall copies the current calling process, creating a child process. In effect, this creates 
a second identical process which may be used to carry out a desired task, while keeping the REPL loop going.
 Immediately after fork though, one has two identical programs running in memory.

* exec() means execute, it effectively allows us to execute a given program. Importantly, after calling fork,
one is able to make the new calling process execute a desired program, changing memory or gaining whatever result
is desired while still maintaining a REPL
loop. 

### Task 2
For some reason my linked image isn't showing up in the README, but if you just click the link it'll open and you
can view my solution

![memory_image](./data.pdf)

### Task 3

It is important that code and data are delineated, because we need to pretty rigorously and universally know where 
instructions should be in memory. That way, no matter the operating system or programming language or whatever else, 
we should be able to pretty universally access our instructions. In doing so, we're able to reliably run and execute code,
and create, access, and store whatever data we could ever want thereafter. But in order to gain all of the amazing possibilities
that could come from giving a computer a set of instructions (code) we need to know where that code will be at all times,
and further, we need to know that data will be in another reserved (seperate) place, where it too may be accessed when
desired.

### Task 4

A few threats that seem immediately apparent could stem from the allocation of memory for specific tasks, and the limitations
that coincide with that allocation. Namely, one may worry about overflowing a buffer, a stack, or a heap, thereby making a program
not run properly, and potentially, if done carefully, I'd presume someone could access neighboring segments of memory in this way
which may not be intended. Further, it may also be possible to access the code layer in some way to then make modifications to a given
program so that it does what we want. This may be done through tampering in the BSS layer through some global static data in some way.
I'm not sure quite how this would work but I'd bet that it's been done.

### Task 5

A trust boundary, is the delineation in memory of areas that may be accessed by other layers, and areas that are not supposed be accessible
by other layers. Namely, given some level of privilege, one may or may not access some specific area in memory, the lines of which are determined
by this trust boundary.

### Task 6

Major elements of a stack frame include the arguments to a function, a return address, the previous frame pointer, and local variables. Arguments to the
function are important because they almost certainly are accessed throughout the execution of that function, a return address is important in case the
value given by that function needs to be retrieved for a later task, the previous frame pointer is important because a function might be called within another
function, so it's necessary to be able to backtrack to the frame which resulted in the current frame being called, so that we aren't lost after
executing one function. Finally, we need to address local variables, which may be accessed throughout the given function in order to attain a resulting
return value.


### Task 7

* Main is located towards the bottom addresses in memory, in the page that's executable. Main is stored near the bottom since it's code, and as it is a set of
instructions, it needs to be designated as executable.

* Printf is located in libc section of memory. We know this because printf corresponds to a library, so it makes sense that it'd live with other libraries
in the memory mapping segment of memory.

* Argv is located on the stack, which makes sense because it's an argument to a function. It is just the inputs to the function main, so it should be in a
stack frame and live on the stack.

* Environ also definitely lives on the stack, which we can tell by its address. This too makes sense, because we know that environ is a variable corresponding
to the user environment, and it gets copied when a child process is created so that the environment of a program stays consistent throughout function calls.
From earlier, this sounds a lot like the part of a stack frame which keeps track of previous function calls. As such, it makes sense that it also lives on the stack. 

### Task 8

* The compiler first runs a program through the preprocessor. When run through the preprocessor, we resolve directives such as #include, #if, and that sort of
thing that's preliminary for our functions to run correctly. This may be viewed in .i files

* Next, the compiler is invoked, and from there we produce assembly code that is even simpler, so that we are running a complete set of instructions in our machine.
This may be viewed in .s files

* After this, the assembler is invoked, which produces machine code in the form of .o files. Machine code is effectively the simplest set of instructions which our
machine may interpret.

* Finally, we invoke the linker, which produces an executable file. Perhaps most commonly, we may have experienced this in the form of a.out types of files. The linker
effectively works to tidy up all of the earlier work done by the compiler, and combines .o files and libraries, .a files, .lib, and other files of this nature to our
fully compiled, and now executable, code.
