```YAML
---
useMath: true
---
```


## Le Finale
## Ben Holmgren
## benjamin.holmgren1@student.montana.edu
## CSCI 476
## Due 4/27/2021 (noon)

### Task 1.1

Indeed, system() and execve() are both used to execute external programs,
but there's an important difference in how each handle data. Importantly,
since system() takes in a string passed to the shell as a command to run,
there is no seperation between a command and data. In the context of the
course material, this opens up system() calls to setuid vulnerabilities.

Contrast that to execve(), which seperates code and data in different
arguments. This has the effect of executing a program directly, and feeding
in arguments therafter. Doing so gets rid of this vulnerability in system()
calls where we could just tack on potentially unintended data following
a shell command.

### Task 1.2

The two conditions needed to exploit a shellshock vulnerability are:

* The target process must be running a vulnerable version of bash
* The payload getting parsed by the vulnerable version of bash gets inputs
by way of environment variables

### Task 1.3

If we run 'nc -l 7070', then we obtain a TCP server that listens for a
connection on port 7070.

Running '/bin/cat < /dev/tcp/10.0.2.6/7070 >&0' on machine 2, we find a 
connection on the port we were listening on with machine 1. The command calls
the standard 'cat' command, whose input device is set to the TCP connection by 
the < symbol. This sends input to the port being listened to by machine 1. 

Now we just need to figure out what this >&0 is all about. 
From referencing back to the shellshock lab, 0 represents the
standard input device. So this is telling us to redirect the output device
to be the standard input device, which is just the shell we're running on
machine 1.

I believe then that this command should
stream any inputs and outputs in the shell of machine 2
and cat them into the shell being run on machine 1. In this way, machine 1
should obtain a live stream of everything that machine 2 is doing.
It seems that whatever is output by machine 2 is redirected to the stdin device,
which has been already redirected to the TCP connection. At the same time,
whatever is input into machine 2 is redirected to the TCP connection as well by
the first part of the command.

### Task 1.4

ASLR stands for "address space layout randomization", and it does precisely
what the name would imply, randomizing the starting addresses of the heap
and the stack. This makes buffer overflow attacks more difficult, because
it makes it harder to guess where these critical addresses are in memory,
which is necessary for these kinds of attacks to work. Without ASLR,
we saw in the lab that we could just examine the execution of a program and see
where things (the heap and the stack in particular)
were located in memory, basing our guesses of their addresses off of these
observations. With ASLR enabled, such a simple approach is not possible.


### Task 1.5

The underlying cause for XSS vulnerabilities is that HTML allows JavaScript
code to be interspersed with data. We saw that for a simple website like
the Elgg web app, if this isn't addressed properly with inputs
intended for data, javascript code can be mixed in with data and cause real
problems (changing passwords/data throughout the system at large).

For the sake of specificity, XSS vulnerabilities stem from taking an
inline approach to writing an HTML page, 
because a browser can't safely distinguish
if the inlined code originates from a trusted source or an untrusted user
as it's being rendered. A user's inputs need to be clearly delineated, and
not in the form of inline HTML code in order to avoid such problems.

### Task 1.6

Reflected XSS refers to a malicious script coming from a current HTTP request
to a vulnerable party.

Stored XSS refers to a malicious script coming from a website's database to a 
vulnerable party.

For reflected XSS, the idea is that a victim could click on a link for 
example, and that link could have some embedded javascript code in it 
which could allow a malicious party to execute some unintended command.
In this way, we could theoretically execute a command that would send a
victim's private data to an attacker.
Interestingly, for reflected XSS, code could
be executed in the browser from some input, and if the input is reflected back
in the browser it could execute and do malicious things.

For stored XSS, the idea is that in areas where users could input things into
a database from a website, they might be able to send code into the database,
potentially causing harm in that way. The most famous example of this is likely
when code is inputted into say, a comment section on a website. If the website
doesn't sanitize these inputs, the code will be rendered in the browser.

In one word, the major difference between reflected and stored XSS is persistence.
Reflected XSS is something that can occur for just one victim at a time,
whereas stored XSS could occur for any victim(s) visiting a site with such
a vulnerability.
 
Enough of my ramblings, you get the point by now. I just think that this is an especially
interesting, and potentially dangerous vulnerability in the world that we live in.

### Task 1.7

After Alice and Bob have sent their initial messages, Alice can compute $(g^y mod p)^x mod p
= g^{yx} mod p$ and Bob can compute $(g^x mod p)^y mod p = g^{xy}mod p$ using each of
their privately generated $x$ and $y$ values respectively. But in this way, Bob and Alice
get a common secret key, which is this shared value of $g_{xy}mod p$ that each party is
able to compute.

Yet another triumph in the annals of human history/computation of cyclic groups!

### Task 1.8

Public key cryptography only really works with using very large numbers, 
and this has a significant cost in performance. In the textbook, it is discussed that RSA
decryption is about 1000 times slower in practice than AES, revealing the significant
performance gap between public key and symmetric key encryption in the real world.

This necessitates the need for a combination of the two tactics; this is gained
by a mixture symmetric key cryptography when we can get away with it, and public key
cryptography when it's necessary. This is precisely hybrid encryption. How does such
a scheme work? The bulk of the actual data ends up being encrypted by symmetric-key
encryption, and then the key for this encryption is encrypted itself using public
key cryptography, and it's shared with a recipient. The encrypted data (which has been
secured, say using AES) is just sent to the recipient as is, since it's encrypted
for anyone without the shared key. All that really needs to be sent using public key crypto
is the symmetric key for the encrypted shared data. In this way, one avoids the expensive
computation needed to decrypt all of the data using public key cryptography standing alone.

### Task 1.9

(i.)

When you run programs at the command line, these programs/libraries are found using local
variables, like for instance PATH. The intended use of such variables is to point users
to the normal programs they'd execute on the command line, many of which are located in
places like /bin. Overwriting variables such as PATH can cause these programs to be found
in abnormal locations.

(ii.)

Since the generally intended versions of the programs are in /bin and normally not in a
different directory, the risk is that these environment variables could be overwritten 
by some kind of sneaky process, where a malicious party could insert a variant 
of one of these common command line programs where it wasn't
expected or intended. Such a thing could overwrite the standard programs most people use in
favor of an unintended one, which could have vulnerabilities an attacker could exploit.

We saw this in Task 6 of the Set-UID lab, where we called an especially cringy line of code
in hindsight

"system("ls");"

Which uses the relative path for the ls command, allowing a potentially entirely different
ls program to be run than the generally intended one if environment variables are manipulated
in the right manner.

### Task 1.10

Three countermeasures to buffer-overflow attacks. Ready, set, go:

(i.)

We can use ASLR, which was described above but in a nutshell just randomly moves
addresses in memory for each given execution of some program. This makes it much
more difficult to guess the correct locations of the stack and the heap, which is
necessary to successfully carry out a buffer overflow attack. However, such a
countermeasure can still be brute forced into coersion, if we simply guess the same
address enough times inevitably the randomization should crack at some point. But it
is definitely more annoying to try to breach.

(ii.)

Another approach is using a stack guard in the compiler. This really just boils down
to having the compiler check for us if anything in memory is overflowing into the
stack, and the compiler can then stop the code from compiling correctly if this is
the case. Such a tactic feels much more difficult to breach, unless somehow an attacker
could insert their own vulnerable compiler onto a system to exploit.

(iii.)

A final approack is to just make the stack not executable. Generally, we don't need the
stack to be executable anyways, so if it's not executable, the idea is that an extended
buffer couldn't find its way onto the stack and then be executed in an unintended manner,
since the stack is just simply not executable. In practice, this too can be overcome,
although it definitely does make the job of an attacker more difficult. Really, this
just boils down to the fact that somewhere, something has to be executable in order
for anyone to accomplish anything in the world, and just because
the stack is off limits doesn't mean that other areas necessarily could be reached
and exploited. Though, finding these other exploitable areas is an annoying challenge
in its own right.
