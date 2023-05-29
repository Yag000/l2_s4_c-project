# C project for the S4 of the Computer Science Bachelor's Degree

**(by Yago Iglesias Vazquez(@Yag000) and Gabin Dudillieu(@GabinDDL))**

## Compilation and execution of the main program

Firstly, to compile the project, you need to use the following command:

```bash
make main
```

Then, to run the program, use the command:

```bash
./main text.txt
```

The result will be displayed in the current terminal.

Several flags are also available for executing the main program (the text file should always be in the first position, except when using `-i` flag):

- `-i` allows taking input from the current terminal instead of a text file (if a text file is provided in the first position, this flag is ignored). This option should always be placed in the **first position**. You can use the `exit` command to exit from it.

- `-v` displays the command in addition to the basic output given by the command (when coupled with the `-i` flag, this flag is ignored).

- `-c` allows continuing reading the text, even after a non-program-stopping error occurs (such as a file path error).

- `-o=output.txt` replaces "output.txt" with an output file name to display the command results in that file instead of the current terminal (if the file does not exist, it will be created if possible).

  -`-r=input.txt` replaces "input.txt" with an output file name to display the command inputs in that output, thus recording a new input (if the file does not exist, it will be created if possible).

## Compilation and execution of tests

You can run a battery of tests to check if the code compiles correctly, if the unit tests succeed, and if all the outputs of the given inputs match the expected outputs _(It is not necessary to compile the unit tests separately, the program will do it automatically)_.

For that, you can use the command:

```bash
./test.sh
```

There are also several flags available for executing this battery of tests:

- `-v` displays more details about the given unit tests.
- `--valgrind` runs the tests with valgrind.
- `--only-main` runs only the main tests.
- `--only-unit` runs only the unit tests.
- `--help` or `-h`displays an explanation of the options.

You can also compile and run only the unit tests by using the command:P

```bash
make test && ./test
```

_Note that you can add `-v` at the end to display more details about the performed unit tests._

## Removing compiled files

To remove the compiled files, use the command:

```bash
make clean
```

## Other additions

In the given inputs, the paths must follow the format provided in the project guidelines.

However, in our project, it is possible to use the names `.` and `..` as many times as necessary, which select the current node and the parent of the current node, respectively.

We have also implemented an additional command, `echo`, which displays a message in the current terminal. This command can take an indefinite number of arguments and will display all the given arguments, separated by a space.

Lastly, for the following commands: `ls`, `mkdir`, and `touch`, it is possible, in addition to the project requirements, to provide them with full paths as arguments.
