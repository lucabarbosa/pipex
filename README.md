# Pipex

A 42 School project that recreates the behavior of shell pipes in C, allowing you to chain two commands together just like in the shell.

## 📚 Project Overview

Pipex is a system programming project that teaches fundamental UNIX concepts by implementing a simplified version of the shell pipe mechanism. The program takes two commands and executes them in a pipeline, redirecting input from a file and output to another file.

**Pipex:**
```bash
./pipex file1 cmd1 cmd2 file2
```
Should behave exactly like:
```bash
< file1 cmd1 | cmd2 > file2
```

## 🎯 Learning Objectives

Through this project, you'll learn:

- **Process Management**: Understanding `fork()`, `execve()`, and process creation
- **Inter-Process Communication (IPC)**: Using pipes to connect processes
- **File Descriptors**: Manipulating stdin, stdout, and file descriptors with `dup2()`
- **System Calls**: Working with low-level UNIX system calls
- **Error Handling**: Properly handling errors and exit statuses
- **Memory Management**: Avoiding memory leaks and proper cleanup
- **PATH Resolution**: Finding executables in the system PATH

### Key Concepts Learned

1. **Pipes (`pipe()`)**: Creating unidirectional data channels between processes
2. **File Descriptor Redirection (`dup2()`)**: Redirecting stdin/stdout to files or pipes
3. **Process Creation (`fork()`)**: Creating child processes
4. **Program Execution (`execve()`)**: Replacing process with a new program
5. **Process Synchronization (`wait()`, `waitpid()`)**: Waiting for child processes to finish
6. **Environment Variables**: Parsing and using the PATH environment variable

## 🛠️ Compilation

### Prerequisites

- Clang or GCC compiler
- Make

### Build Commands

```bash
# Compile the project
make

# Clean object files
make clean

# Clean all generated files
make fclean

# Recompile everything
make re
```

## 🚀 Usage

### Basic Usage

```bash
./pipex infile "cmd1" "cmd2" outfile
```

### Examples

**Example 1: Count lines in ls output**
```bash
./pipex infile "ls -l" "wc -l" outfile
```
Equivalent to:
```bash
< infile ls -l | wc -l > outfile
```

**Example 2: Count words matching a pattern**
```bash
./pipex infile "grep a1" "wc -w" outfile
```
Equivalent to:
```bash
< infile grep a1 | wc -w > outfile
```

**Example 3: Process text files**
```bash
./pipex input.txt "cat -e" "grep '$'" output.txt
```
Equivalent to:
```bash
< input.txt cat -e | grep '$' > output.txt
```

## 🧪 Testing Your Implementation

### Comparing Output with Shell

To verify your pipex works correctly, compare its output with the actual shell command:

```bash
# Create test files
echo "Hello World\nTest Line\nAnother Line" > infile

# Run your pipex
./pipex infile "cat" "wc -l" outfile1

# Run the equivalent shell command
< infile cat | wc -l > outfile2

# Or you can use the Makefile to test outputs
./pipex Makefile "cat" "wc -l" outfile

# Check the outfile
cat outfile1 # check the results
cat outfile2 # check if the results are the same

# Check exit status
echo $?  # Should be 0 if files are identical
```

### Memory Leak Testing

```bash
# Using valgrind
valgrind --leak-check=full --show-leak-kinds=all ./pipex infile "cat" "wc -l" outfile

# Should show: All heap blocks were freed -- no leaks are possible
```

## 📖 Study Resources

To better understand the concepts behind this project, check out these resources:

- **[42 Pipex Guide](https://42-cursus.gitbook.io/guide/2-rank-02/pipex)** - Comprehensive guide covering all the theory and implementation details

- **[Unix Processes in C YouTube Series](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)** - Excellent video tutorials explaining processes, pipes, and system calls

## 📁 Project Structure

```
pipex/
├── Makefile
├── pipex.h              # Header file with structures and function prototypes
├── pipex.c              # Main function and initialization
├── pipe_exec.c          # Pipe creation and command execution
├── get_path.c           # PATH resolution and command finding
├── free_exit.c          # Memory management and error handling
└── libft/               # Your libft library
    ├── libft.h
    └── *.c
```

## 🔍 Function Breakdown

### Main Components

- **`main()`**: Validates arguments, initializes structures, and orchestrates execution
- **`cmd_pipe_exec()`**: Creates pipes, forks processes, and executes commands
- **`get_path()`**: Resolves command paths using the PATH environment variable
- **`free_and_exit()`**: Cleans up memory and exits with appropriate status

### System Calls Used

- `pipe()`: Create a pipe
- `fork()`: Create a child process
- `execve()`: Execute a program
- `dup2()`: Duplicate file descriptor
- `open()`: Open files
- `close()`: Close file descriptors
- `wait()`/`waitpid()`: Wait for child processes
- `access()`: Check file accessibility

## ⚠️ Common Pitfalls

1. **Forgetting to close file descriptors**: Leads to descriptor leaks
2. **Not checking return values**: Always check system calls for errors
3. **Incorrect PATH parsing**: Handle cases where PATH doesn't exist
4. **Memory leaks**: Free all allocated memory before exit
5. **Zombie processes**: Always wait for child processes
6. **Exit status**: Return the exit status of the last command

## 📝 Notes

- The program must behave exactly like the shell equivalent
- All memory must be properly freed (no leaks)
- Error handling should match shell behavior
- Exit status should match the last command's exit status

---

*This project is part of the 42 School curriculum and focuses on understanding UNIX system programming concepts.*