# malloc-logger
a library that intercepts all the malloc calls in an application and outputs after each malloc call the number of bytes allocated so far by the program, on stderr

## Build the shared library file

Under Linux, compile and run `make` in the project directory. This would build the `.so` file in the present working directory.

## Running the program

Run the program by using the LD_PRELOAD technique.

Run the following in the terminal to check the results

`LD_PRELOAD=[path]/malloc.so [prog with args]`

For example, try running this if you're in the project directory

`LD_PRELOAD=./malloc.so seq 1 5`

## Potential improvement

[This article](https://optumsoft.com/dangers-of-using-dlsym-with-rtld_next/) explains why the current implementation probably cannot free the memory allocations correctly.
