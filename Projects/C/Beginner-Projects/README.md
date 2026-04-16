# C Programming Projects - Setup Guide

## Quick Start for Beginners

### 1. Install a C Compiler

**Windows (Recommended):**
```bash
# Install MSYS2 for modern GCC
# 1. Download from: https://www.msys2.org/
# 2. Run the installer
# 3. Open MSYS2 terminal and run:
pacman -Syu
pacman -Su
pacman -S mingw-w64-x86_64-gcc

# 4. Add to PATH: C:\msys64\mingw64\bin
```

**Alternative Windows (MinGW):**
```bash
# Download from: https://www.mingw-w64.org/
# Install and add to PATH
```

**Mac:**
```bash
# Install Xcode Command Line Tools
xcode-select --install
```

**Linux:**
```bash
# Ubuntu/Debian:
sudo apt-get update
sudo apt-get install gcc

# CentOS/RHEL:
sudo yum install gcc

# Fedora:
sudo dnf install gcc
```

### 2. Verify Installation
```bash
gcc --version
```

### 3. How to Compile and Run Any Project

**Navigate to project directory:**
```bash
cd Projects/C/Beginner-Projects/[project-name]/[level]/
```

**Compile:**
```bash
gcc filename.c -o program_name
```

**Run:**
```bash
# Linux/Mac:
./program_name

# Windows:
program_name.exe
```

## Project Structure

Each project follows this pattern:
```
project-name/
  level-1/
    filename.c        # Source code
    README.md          # Detailed instructions
  level-2/
    filename.c        # More advanced version
    README.md
```

## Learning Path

### Level 1: Absolute Beginner
- **Greeter** - Basic input/output
- **Calculator** - Math operations
- **Number Guesser** - Loops and randomness

### Level 2: Getting Comfortable
- **Calculator Level 2** - Functions and menus
- **String Operations** - Text processing
- **File Manager** - File I/O

### Level 3: Intermediate
- **To-Do List** - Data structures
- **Student Database** - Complex data management

## Common Commands

| Command | What it does |
|---------|-------------|
| `gcc file.c -o program` | Compile C file |
| `./program` | Run compiled program |
| `gcc -Wall file.c -o program` | Compile with warnings |
| `gcc -g file.c -o program` | Compile with debug info |

## Troubleshooting

**"gcc not found"**: Compiler not installed or not in PATH

**"Permission denied"**: Use `chmod +x program` on Linux/Mac

**Compilation errors**: Check for typos, missing semicolons

**Program closes immediately**: Add `getchar();` before `return 0;`

## Best Practices

1. **Always compile with warnings**: `gcc -Wall file.c -o program`
2. **Read error messages carefully** - they tell you the line number
3. **Test each level before moving to the next**
4. **Experiment with the code** - change values and see what happens
5. **Read the README files** - they have detailed explanations

Happy coding! Start with the **Greeter** project if you're completely new to C.
