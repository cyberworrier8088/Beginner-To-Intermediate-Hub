# 🗄️ To-Do List - Method 3: The JSON Database

Welcome to **Level 3**! Here, we introduce the concept of "Structured Data" using the built-in `json` library. 

### 🧠 The Problem with Plain Text
In Level 2, we saved tasks as just a raw line in a text file (`"Buy milk"`). But what if our app needs to remember multiple pieces of information about a single task?
- Task Name: "Buy milk"
- Task Status: "Done"
- Creation Date: "2024-05-10"

If we put all of that in a normal text file, we have to invent a weird system to separate the words (like `Buy milk|Done|2024-05-10`), and parsing that is an absolute nightmare.

### 🛠️ The Solution: JSON and Dictionaries
**JSON** stands for *JavaScript Object Notation*. Despite the name, it is the universal language of the Internet. Every time an app on your phone talks to a server, they are sending JSON messages.

1.  **Dictionaries**: Instead of making our tasks a string, we make them a Python Dictionary: `{"name": "Buy milk", "status": "Pending"}`. Dictionaries use "Key-Value" pairs, which is incredibly organized.
2.  **`json.dump()`**: We use this function to magically convert our Python Dictionaries into a deeply organized text file (`database.json`). 
3.  **`json.load()`**: When the app starts, this function pulls the text from our `.json` file and automatically rebuilds it into Python Dictionaries!

### 🏃 How to Run
```bash
python todo.py
```
Try adding a few tasks and marking one as "Done". Then, open the `database.json` file in your editor. Notice how beautiful and structured the data looks! Now you are building databases like a real Software Engineer.
