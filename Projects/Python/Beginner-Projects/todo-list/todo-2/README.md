# 🗃️ To-Do List - Method 2: The File Keeper

Welcome to **Level 2**! In Level 1, our app had 'Amnesia'. Every time we closed it, the data was erased from the computer's temporary memory (RAM). Now, we will teach the app how to write things down on paper (the hard drive).

### 🧠 The Core Concept: File I/O
I/O stands for **Input / Output**. It is the concept of a program communicating with the outside world. In this case, our program opens a `.txt` file, reads the data (Input), and saves new data (Output).

### 🛠️ Technical Deep Dive
1.  **The `open()` function**: This is built right into Python. We use it in two modes:
    *   `"r"` mode (Read): Opens the file just to look at the text.
    *   `"w"` mode (Write): This mode is dangerous! It instantly deletes everything in the file and overwrites it. If we want to add a task, we must read all the tasks into our list, add the new task, and write the *entire list* back to the file.
2.  **Context Managers (`with`)**: You'll see `with open(...) as file:`. In older languages, if you opened a file, you had to manually type `file.close()` when you were done. If you forgot, the file would get corrupted! The `with` keyword is a "Context Manager". It automatically closes the file the second the block of code finishes, even if there's an error. 
3.  **Persistence**: Now, when you add a task, we call `save_tasks()`. We save the file instantly so that if your computer suddenly loses power, your task list is safe!

### 🏃 How to Run
```bash
python todo.py
```
Try adding a task. Then, look inside this folder. You will see a new file magically appear called `my_database.txt`. You can actually open it with Notepad! Try editing the text file directly and running your script again. It's connected!
