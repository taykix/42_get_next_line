# Get Next Line

Get Next Line is a project from the 42 curriculum focused on reading text from a file descriptor line by line.  
The goal of the project is to implement a function that returns the next line from a file, standard input, or another valid file descriptor each time it is called.

## About the Project

In this project, I implemented the `get_next_line` function in C.  
The function reads from a file descriptor and returns one line at a time, including the newline character when present.

This project helped me understand how file descriptors work, how buffered reading is handled, and how static variables can be used to preserve data between multiple function calls.

## Function Prototype

```c
char *get_next_line(int fd);
```

## What I Learned

- Reading from file descriptors using `read`
- Managing buffers and partial reads
- Using static variables to keep data between function calls
- Handling dynamic memory allocation with `malloc` and `free`
- Working with strings and memory in C
- Detecting newlines and returning complete lines
- Preventing memory leaks
- Handling edge cases such as empty files, invalid file descriptors, and end-of-file behavior

## Allowed External Functions

The project was developed under the 42 constraints, using only a limited set of allowed external functions:

- `read`
- `malloc`
- `free`

All required helper functions for string handling and memory management were implemented manually.

## Technologies Used

- C
- Makefile
- Git
- Norminette

## Project Status

Completed as part of the 42 Wolfsburg curriculum.
