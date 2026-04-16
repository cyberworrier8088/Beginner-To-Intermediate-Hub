# 🖼️ Calculator - Method 5: The Graphical User Interface (GUI)

Welcome to the **Endgame**! You've moved from text-based scripts to building a real Desktop Application. This version uses **Tkinter**, Python's built-in toolkit for creating windows, buttons, and menus.

### 🧠 The Shift: Event-Driven Programming
In all previous levels, the code started at the top and ran until it hit the bottom. In Level 5, the code starts, builds a window, and then **stays open**, waiting for you to do something (click a button). This is called "Event-Driven" programming—the code responds to "events" (clicks, keystrokes).

### 🛠️ Technical Concepts
1.  **Widgets**: In GUI talk, everything is a widget. The window, the buttons, and the text box are all widgets that we "place" on the screen.
2.  **The Grid System**: We use a `grid(row, column)` layout, similar to a spreadsheet (Excel), to tell Python exactly where each button should go.
3.  **The Event Loop (`mainloop`)**: This is a special while-loop that runs behind the scenes. It keeps the window visible and listens for mouse clicks. Without it, the window would vanish in a split second!
4.  **Lambdas**: Notice the `lambda x=button: on_click(x)` part? This is a "small, anonymous function" that allows us to tell the button's command exactly which number or symbol it represents.
5.  **`eval()`**: For this beginner project, we used the `eval()` function to calculate the result. It's a quick way to turn a string like `"2+2"` into the number `4`. (In professional apps, we'd use a custom "parser" to be extra safe!)

### 💡 Why learn GUI?
Building a GUI is how you turn a "script" into a "product." It makes your code accessible to people who don't know how to use a terminal. Plus, it's just really satisfying to see your own window pop up!

### 🏃 How to Run
```bash
python calculator.py
```
*Note: You need a computer with a screen (Display) to see the window. If you are using a remote server or a text-only terminal, this script will show an error.*

---
### 🏆 Mastery Achieved!
You've now seen the full evolution of a Python project.
1. **Level 1**: Simple Flow
2. **Level 2**: Modular Functions
3. **Level 3**: Object-Oriented Logic
4. **Level 4**: Data-Driven Mapping
5. **Level 5**: Graphical Interface

**What will you build next? 🚀**
