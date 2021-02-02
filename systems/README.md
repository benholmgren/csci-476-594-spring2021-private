1. 

* The fork() syscall copies the current calling process, creating a child process. In effect, this creates 
a second identical process which may be used to carry out a desired task, while keeping the REPL loop going.
 Immediately after fork though, one has two identical programs running in memory.

* exec() means execute, it effectively allows us to execute a given program. Importantly, after calling fork,
one is able to make the new calling process execute a desired program, changing memory or gaining whatever result
is desired while still maintaining a REPL
loop. 

2. 

* ![data](./data.pdf)
