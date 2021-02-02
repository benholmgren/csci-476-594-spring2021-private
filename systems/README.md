1. 

* The fork() syscall copies the current calling process, creating a child process. In effect, this creates 
a second identical process which may be used to carry out a desired task, while keeping the REPL loop going.
 Immediately after fork though, one has two identical programs running in memory.

* exec() means execute, it effectively allows us to execute a given program. Importantly, after calling fork,
one is able to make the new calling process execute a desired program, changing memory or gaining whatever result
is desired while still maintaining a REPL
loop. 

2. 

![memory_image](./data.pdf)

3.

It is important that code and data are delineated, because we need to pretty rigorously and universally know where 
instructions should be in memory. That way, no matter the operating system or programming language or whatever else, 
we should be able to pretty universally access our instructions. In doing so, we're able to reliably run and execute code,
and create, access, and store whatever data we could ever want thereafter. But in order to gain all of the amazing possibilities
that could come from giving a computer a set of instructions (code) we need to know where that code will be at all times,
and further, we need to know that data will be in another reserved (seperate) place, where it too may be accessed when
desired.

4.

A few threats that seem immediately apparent could stem from the allocation of memory for specific tasks, and the limitations
that coincide with that allocation. Namely, one may worry about overflowing a buffer, a stack, or a heap, thereby making a program
not run properly, and potentially, if done carefully, I'd presume someone could access neighboring segments of memory in this way
which may not be intended. Further, it may also be possible to access the code layer in some way to then make modifications to a given
program so that it does what we want. This may be done through tampering in the BSS layer through some global static data in some way.
I'm not sure quite how this would work but I'd bet that it's been done.

5.

A trust boundary, is the delineation in memory of areas that may be accessed by other layers, and areas that are not supposed be accessible
by other layers. Namely, given some level of privilege, one may or may not access some specific area in memory, the lines of which are determined
by this trust boundary.

6.

Major elements of a stack frame include the arguments to a function, a return address, the previous frame pointer, and local variables. Arguments to the
function are important because they almost certainly are accessed throughout the execution of that function, a return address is important in case the
value given by that function needs to be retrieved for a later task, the previous frame pointer is important because a function might be called within another
function, so it's necessary to be able to backtrack to the frame which resulted in the current frame being called, so that we aren't lost after
executing one function. Finally, we need to address local variables, which may be accessed throughout the given function in order to attain a resulting
return value.

