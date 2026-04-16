# 👋 The Advanced Greeter - C Level 1: Basic I/O

Welcome to **C Programming**! C is the grand-daddy of modern programming. Windows, Mac OS, Linux, and even Python itself were all written in C. It is insanely fast, but it requires you to manually manage the computer's memory.

### 🧠 The Core Concept: Compilation
With Python, you type a script and run it. Python is an "Interpreted" language. 
C is a "Compiled" language. You cannot run `main.c`. You must run a compiler tool (like GCC) to translate your human-readable English text into pure 1s and 0s (Binary) for your computer chip to read. This creates a `.exe` file.

### 🛠️ Technical Deep Dive
1.  **`#include <stdio.h>`**: C comes with almost nothing built-in. To print words to a screen, we have to include the Standard Input/Output library.
2.  **`int main()`**: Every C program absolutely requires a function called `main`. When you double-click the `.exe`, the Operating System searches specifically for `main` and starts executing the code inside it.
3.  **Strict Typing**: In Python, you can type `age = 40`. In C, you MUST specify exactly how much RAM to reserve. You type `int age;` to reserve 4 bytes of memory specifically for numbers.
4.  **`&` (The Address-Of Operator)**: Look at `scanf("%d", &age);`. We don't just say `age`. We use `&` to tell the scanner the literal physical address in your computer's RAM where the variable `age` is stored, so it knows where to inject the user's typed number!

### 🏃 How to Compile and Run
You need GCC (MinGW on Windows) installed. Open your terminal in this folder and enter the following commands:

**Step 1: Compile the Code**
```bash
gcc main.c -o greeter.exe
```
*(This command means: "Take main.c, compile it, and output exactly the name greeter.exe")*

**Step 2: Run the Binary App**
```bash
./greeter.exe
```
