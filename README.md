# Pipex - Unix Pipe Implementation in C


## Table of Contents
1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Usage](#usage)
4. [How It Works](#how-it-works)
5. [Features](#features)
6. [Project Structure](#project-structure)
7. [Contributing](#contributing)
8. [License](#license)

## Introduction
**Pipex** is a C program that simulates the behavior of Unix pipes (`|`), allowing you to chain commands together by redirecting the output of one command to the input of another. This implementation mimics the functionality of commands like:

```bash
$ < input_file cmd1 | cmd2 > output_file
```

The program takes exactly four arguments:
1. Input file
2. First command
3. Second command
4. Output file

## Installation
1. Clone the repository:
```bash
git clone https://github.com/<your-username>/pipex.git
cd pipex
```

2. Compile the program:
```bash
make
```
The executable `pipex` will be created in the root directory.

## Usage
```bash
./pipex input_file "command1" "command2" output_file
```

### Example
```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```
This is equivalent to:
```bash
< input.txt grep hello | wc -l > output.txt
```

## How It Works
### Program Flow
1. Validate argument count (exactly 4 arguments + program name)
2. Open input and output files
3. Create a pipe and fork two child processes:
   - **First child**:
     - Redirects STDIN from input file
     - Redirects STDOUT to pipe's write end
     - Executes first command
   - **Second child**:
     - Redirects STDIN from pipe's read end
     - Redirects STDOUT to output file
     - Executes second command
4. Parent process waits for both children to complete

### Key Components
- **Path Resolution**: Searches for commands using the `PATH` environment variable
- **Error Handling**: Comprehensive error messages and proper cleanup
- **Memory Management**: Custom allocators with automatic cleanup
- **Process Management**: Uses `fork()`, `pipe()`, and `execve()` for command execution

## Features
- 🛠️ Implements Unix-like pipe functionality
- 🔍 Searches commands in `PATH` environment variable
- 🚦 Comprehensive error handling
- 💾 Memory-safe with proper cleanup
- 📁 Handles file input/output redirection
- ⚡ Supports absolute path commands
- � Graceful exit with proper status codes

## Project Structure
```
pipex/
├── Makefile           # Compilation rules
├── pipex              # Compiled executable
├── pipex.h            # Header file
├── pipex.c            # Main program logic
├── utils/             # Utility functions
│   ├── ft_split.c     # String splitting
│   ├── ft_strjoin.c   # String concatenation
│   ├── ft_strnstr.c   # Substring search
│   ├── path_utils.c   # PATH resolution
│   ├── error_utils.c  # Error handling
│   └── ...            # Other helper functions
└── libft/             # Custom library functions
    ├── ft_calloc.c
    ├── ft_strdup.c
    ├── ft_strncmp.c
    └── ...
```

