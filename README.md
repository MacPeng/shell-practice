# shell-practice

# Unix Utilities

**Before beginning:** Read this [lab tutorial](http://pages.cs.wisc.edu/~remzi/OSTEP/lab-tutorial.pdf); it has some useful tips for programming in the C environment and is still useful even though we're using C++ in this class.

In this project, you'll build a few different UNIX utilities, simple versions
of commonly used commands like **cat**, **ls**, etc. We'll call each of them a
slightly different name to avoid confusion; for example, instead of **cat**,
you'll be implementing **wcat** (i.e., "wisconsin" cat).

Objectives:
* Re-familiarize yourself with the C/C++ programming language
* Re-familiarize yourself with a shell / terminal / command-line of UNIX
* Learn (as a side effect) how to use a proper code editor such as emacs
* Learn a little about how UNIX utilities are implemented

While the project focuses upon writing simple C++ programs, you can
see from the above that even that requires a bunch of other previous
knowledge, including a basic idea of what a shell is and how to use
the command line on some UNIX-based systems (e.g., Linux or macOS),
how to use an editor such as emacs, and of course a basic
understanding of C programming. If you **do not** have these skills
already, this is not the right place to start.

Summary of what gets turned in:
* A bunch of single .cpp files for each of the utilities below: **wcat.cpp**,
  **wgrep.cpp**, **wzip.cpp**, and **wunzip.cpp**.
* Make sure that your source code uses the **open()**, **read()**, **write()**, and **close()** calls for file, STDOUT, and STDIN I/O
* Each should compile successfully when compiled with the **-Wall** and
**-Werror** flags.
* Each should (hopefully) pass the tests we supply to you.
* We will also test your code on our own set of test cases that we don't supply.

In case you're unfamiliar with Git and GitHub, please see these tutorials:
* [Git Handbook](https://guides.github.com/introduction/git-handbook/)
* [GitHub / Git Cheatsheet](https://training.github.com/downloads/github-git-cheat-sheet/)

## wcat

The program **wcat** is a simple program. Generally, it reads a file as
specified by the user and prints its contents. A typical usage is as follows,
in which the user wants to see the contents of main.cpp, and thus types: 

```
prompt> ./wcat main.cpp
#include <stdio.h>
...
```

As shown, **wcat** reads the file **main.cpp** and prints out its contents. 
The "**./**" before the **wcat** above is a UNIX thing; it just tells the
system which directory to find **wcat** in (in this case, in the "." (dot)
directory, which means the current working directory). 

To create the **wcat** binary, you'll be creating a single source file,
**wcat.cpp**, and writing a little C++ code to implement this simplified version
of **cat**. To compile this program, you will do the following:

```
prompt> g++ -o wcat wcat.cpp -Wall -Werror
prompt> 
```

This will make a single *executable binary* called **wcat** which you can
then run as above. 

You'll need to learn how to use a few library routines from the C++ standard
library (often called **libc++**) to implement the source code for this program,
which we'll assume is in a file called **wcat.cpp**. All C++ code is
automatically linked with the C++ library, which is full of useful functions you
can call to implement your program.

For this project, you are _required_ to use the following routines to do
file input and output: **open**, **read**, **write**, and
**close**. Whenever you use a new function like this, the first
thing you should do is read about it -- how else will you learn to use
it properly?

On UNIX systems, the best way to read about such functions is to use what are
called the **man** pages (short for **manual**). In our HTML/web-driven world,
the man pages feel a bit antiquated, but they are useful and informative and
generally quite easy to use.

To access the man page for **open**, for example, just type the following
at your UNIX shell prompt: 
```
prompt> man 2 open
```

Then, read! Reading man pages effectively takes practice; why not start
learning now?

We will also give a simple overview here. The **open** function
"opens" a file, which is a common way in UNIX systems to begin the
process of file access. In this case, opening a file just gives you
back a file descriptor, which is an identifier that you can then passed
to other routines to read, write, etc.

Here is a typical usage of **open**:

```c++
int fileDescriptor = open("main.cpp", O_RDONLY);
if (fileDescriptor < 0) {
    cerr << "cannot open file" << endl;
    exit(1);
}
```

A couple of points here. First, note that **open** takes two arguments: the
*name* of the file and the *mode*. The latter just indicates what we plan to
do with the file. In this case, because we wish to read the file, we pass O_RDONLY
as the second argument. Read the man pages to see what other options are
available. 

Second, note the *critical* checking of whether the **open** actually
succeeded. This is not Java where an exception will be thrown when things goes
wrong; rather, it is C++, and it is expected (in good programs, i.e., the
only kind you'd want to write) that you always will check if the call
succeeded. Reading the man page tells you the details of what is returned when
an error is encountered; in this case, the macOS man page says:

```
If successful, open() returns a non-negative integer, termed a file
descriptor.  It returns -1 on failure.  The file pointer (used to mark
the current position within the file) is set to the beginning of the
file. 
```

Thus, as the code above does, please check that **open** does not return
-1 before trying to use the file descriptor it returns.

Third, note that when the error case occurs, the program prints a message and
then exits with error status of 1. In UNIX systems, it is traditional to
return 0 upon success, and non-zero upon failure. Here, we will use 1 to
indicate failure.

Side note: if **open()** does fail, there are many reasons possible as to
why.  You can use the functions **perror()** or **strerror()** to print out
more about *why* the error occurred; learn about those on your own (using
... you guessed it ... the man pages!).

Once a file is open, there are many different ways to read from it. The one
we're requiring here to you is **read()**, which is used to get input from
file descriptors. 

To print out file contents, use **write()**. For example, after reading
in a line with **read()** into a variable **buffer** and keeping track of
the number of bytes that you read in a variable **bytesRead**, you can
just print out the buffer as follows:

```c++
write(fileDescriptor, buffer, bytesRead)
```

Finally, when you are done reading and printing, use **close()** to close the
file (thus indicating you no longer need to read from it).

**Details**

* Your program **wcat** can be invoked with one or more files on the command
  line; it should just print out each file in turn. 
* In all non-error cases, **wcat** should exit with status code 0, usually by
  returning a 0 from **main()** (or by calling **exit(0)**).
* If *no files* are specified on the command line, **wcat** should just exit
  and return 0. Note that this is slightly different than the behavior of 
  normal UNIX **cat** (if you'd like to, figure out the difference).
* If the program tries to **open()** a file and fails, it should print the
  exact message "wcat: cannot open file" (followed by a newline) and exit
  with status code 1.  If multiple files are specified on the command line,
  the files should be printed out in order until the end of the file list is
  reached or an error opening a file is reached (at which point the error
  message is printed and **wcat** exits). 


## wgrep

The second utility you will build is called **wgrep**, a variant of the UNIX
tool **grep**. This tool looks through a file, line by line, trying to find a
user-specified search term in the line. If a line has the word within it, the
line is printed out, otherwise it is not. 

Here is how a user would look for the term **foo** in the file **bar.txt**:

```
prompt> ./wgrep foo bar.txt
this line has foo in it
so does this foolish line; do you see where?
even this line, which has barfood in it, will be printed.
```

**Details**

* Your program **wgrep** is always passed a search term and zero or
  more files to grep through (thus, more than one is possible). It should go
  through each line and see if the search term is in it; if so, the line
  should be printed, and if not, the line should be skipped.
* The matching is case sensitive. Thus, if searching for **foo**, lines
  with **Foo** will *not* match.
* Lines can be arbitrarily long (that is, you may see many many characters
  before you encounter a newline character, \\n). **wgrep** should work
  as expected even with very long lines. For this, you might want to write a
  function that reads from a file descriptor and buffers data until you reach
  a newline character.
* If **wgrep** is passed no command-line arguments, it should print
  "wgrep: searchterm [file ...]" (followed by a newline) and exit with
  status 1.  
* If **wgrep** encounters a file that it cannot open, it should print
  "wgrep: cannot open file" (followed by a newline) and exit with status 1. 
* In all other cases, **wgrep** should exit with return code 0.
* If a search term, but no file, is specified, **wgrep** should work,
  but instead of reading from a file, **wgrep** should read from
  *standard input*. Doing so is easy, because the file descriptor **STDIN_FILENO**
  is already open; you can use **read()** to read from it.
* For simplicity, if passed the empty string as a search string, **wgrep**
  can either match NO lines or match ALL lines, both are acceptable.

## wzip and wunzip

The next tools you will build come in a pair, because one (**wzip**) is a
file compression tool, and the other (**wunzip**) is a file decompression
tool. 

The type of compression used here is a simple form of compression called
*run-length encoding* (*RLE*). RLE is quite simple: when you encounter **n**
characters of the same type in a row, the compression tool (**wzip**) will
turn that into the number **n** and a single instance of the character.

Thus, if we had a file with the following contents:
```
aaaaaaaaaabbbb
```
the tool would turn it (logically) into:
```
10a4b
```

However, the exact format of the compressed file is quite important; here,
you will write out a 4-byte integer in binary format followed by the single
character in ASCII. Thus, a compressed file will consist of some number of
5-byte entries, each of which is comprised of a 4-byte integer (the run
length) and the single character. 

To write out an integer in binary format (not ASCII), you should use
**write()**. Read the man page for more details. For **wzip**, all
output should be written to standard output (the **STDOUT_FILENO** file descriptor,
which, is already open when the program starts running). 

Note that typical usage of the **wzip** tool would thus use shell 
redirection in order to write the compressed output to a file. For example,
to compress the file **file.txt** into a (hopefully smaller) **file.z**,
you would type:

```
prompt> ./wzip file.txt > file.z
```

The "greater than" sign is a UNIX shell redirection; in this case, it ensures
that the output from **wzip** is written to the file **file.z** (instead of
being printed to the screen). You'll learn more about how this works a little
later in the course.

The **wunzip** tool simply does the reverse of the **wzip** tool, taking
in a compressed file and writing (to standard output again) the uncompressed
results. For example, to see the contents of **file.txt**, you would type:

```
prompt> ./wunzip file.z
```

**wunzip** should read in the compressed file (using **read()**)
and print out the uncompressed output to standard output using **write()**.

**Details**

* Correct invocation should pass one or more files via the command line to the 
  program; if no files are specified, the program should exit with return code
  1 and print "wzip: file1 [file2 ...]" (followed by a newline) or
  "wunzip: file1 [file2 ...]" (followed by a newline) for **wzip** and
  **wunzip** respectively. 
* The format of the compressed file must match the description above exactly
  (a 4-byte integer followed by a character for each run).
* Do note that if multiple files are passed to **wzip*, they are compressed
  into a single compressed output, and when unzipped, will turn into a single
  uncompressed stream of text (thus, the information that multiple files were
  originally input into **wzip** is lost). The same thing holds for
  **wunzip**. 


### Footnotes


<a name="myfootnote1">1</a>: Unfortunately, there is a lot to learn about the
C library, but at some point, you've just got to **read documentation** to
learn what is available. Why not now, when you are young? Or, if you are old,
why not now, before it's ... ahem ... too late?




