# 🎲 Number Guesser - Level 3: High Score File I/O

Welcome to **Level 3**, the final version of the Number Guesser! A game is no fun if you can't brag about your high score. We introduce File I/O to permanently store the best score entirely on the hard drive.

### 🧠 The Core Concept: Persistence
When you define variables in a python script (like `attempts = 5`), those variables live in the computer's temporary memory (RAM). When the script ends, the RAM is cleared, and the data vanishes forever. "Persistence" is the act of forcing data out of RAM and writing it physically to a hard drive so it survives computer reboots.

### 🛠️ Technical Deep Dive
1.  **Reading Files (`"r"`)**: We use `open(SCORE_FILE, "r")` to open `highscore.txt` just to read it. If the file doesn't exist, this command will crash! That's why we import `os` and use `os.path.exists()` first to check if it's safe to open.
2.  **Writing Files (`"w"`)**: We use `open(SCORE_FILE, "w")`. Unlike `"r"`, if the file doesn't exist, `"w"` mode will magically create it for you! Be very careful with `"w"`mode because it deletes absolutely everything that was previously in the file and overrides it with your new text.
3.  **String Conversion**: You cannot write an Integer (Math number) to a Text file. It must be a String. That's why we do `file.write(str(score))` when saving, and we do `int(file.read())` when loading it back. Both directions require translation!

### 🏃 How to Run
```bash
python guesser.py
```
Play the game and win. Look inside this folder and you'll see a new file called `highscore.txt` automatically created! Close the game, run it again, and try to beat your own score!
