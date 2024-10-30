# Custom `ls` Command Implementation in C

This project is a C-based implementation of a custom `ls` command, designed to mimic various features of the Unix `ls` utility, with additional handling for inode numbers and long-format directory listings. It includes modular components for file manipulation, memory management, and command-line flag processing.

## Project Structure

- **`UnixLs.c`**: Contains the main functionality of the custom `ls` implementation, handling command-line flags and executing `ls` options such as:
  - `-i` to display inode numbers.
  - `-l` for a long-format listing that shows permissions, ownership, and file size.
  - Combination flags like `-il` for displaying both inode numbers and long-format details.

- **`sampleOutput.txt`**: Provides sample outputs for various command-line flags, demonstrating the behavior of `UnixLs` with different options and directories【44†source】.

- **`Part-I.txt`**: Contains solutions and explanations related to virtual memory, including calculations for page faults and address translation. This is supplementary and provides theoretical insights into memory management, relevant to low-level system programming【45†source】.

- **`Makefile`**: Automates compilation, creating an executable for `UnixLs`. Running `make` compiles the `UnixLs.c` file and produces the executable.

## Getting Started

### Prerequisites
- **C Compiler**: GCC or a compatible C compiler is needed to compile the project.

### Compilation
To compile the program, run:
```bash
make
```
This will generate an executable named `UnixLs` based on `UnixLs.c`.

### Running the Program
After compilation, execute the program with various flags, such as:
```bash
./UnixLs       # Basic listing
./UnixLs -i    # Lists files with inode numbers
./UnixLs -l    # Lists files in long format
./UnixLs -il   # Combines both inode and long format
```
See `sampleOutput.txt` for examples of expected outputs for each flag combination.

## Usage

This project provides a customizable alternative to the Unix `ls` command, allowing experimentation with file and directory listing features at the system level. It’s useful for understanding Unix file management and for enhancing knowledge of system calls and low-level I/O in C.

## Example Use Cases

- As a learning tool for exploring Unix-style file handling and command-line interfaces in C.
- For experimenting with inode and permission management on a Unix-based file system.

## Technologies Used

- **C Language**: Provides low-level control over file operations and memory management.
- **Makefile**: Simplifies compilation by managing dependencies and build steps.
