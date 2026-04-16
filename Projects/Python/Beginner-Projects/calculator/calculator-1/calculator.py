# Welcome to your first Python project! 
# This is a super simple calculator logic. 
# We're going to keep it basic: no complex bits, just raw Python flow.

# --- STEP 1: WELCOME THE USER ---
# It's always a good idea to let the user know what the script does.
print("------------------------------")
print("   PYTHON SIMPLE CALCULATOR   ")
print("------------------------------")

# --- STEP 2: GETTING THE NUMBERS ---
# We use input() to 'talk' to the user. 
# BUT, input() always returns text (a string). 
# Since we can't do math on text, we wrap it in float() to turn it into a decimal number.
num1 = float(input("Type your first number and hit Enter: "))
num2 = float(input("Type your second number and hit Enter: "))

# --- STEP 3: PICKING AN OPERATION ---
# We need to know what the user wants to do with these numbers.
print("\nWhat should we do with these?")
print("Choose: + (Add), - (Subtract), * (Multiply), / (Divide)")
operator = input("Enter the symbol here: ")

# --- STEP 4: THE CALCULATION ENGINE ---
# This is where the magic happens. We use 'if' and 'elif' (else if) 
# to check which symbol the user typed in.

if operator == "+":
    # If it's a plus, we add them together.
    result = num1 + num2
    print(f"\n[DONE] {num1} + {num2} = {result}")

elif operator == "-":
    # If it's a minus, we take the second from the first.
    result = num1 - num2
    print(f"\n[DONE] {num1} - {num2} = {result}")

elif operator == "*":
    # The asterisk (*) is used for multiplication in coding.
    result = num1 * num2
    print(f"\n[DONE] {num1} * {num2} = {result}")

elif operator == "/":
    # Division is a bit tricky... we can't divide by zero!
    # Let's add a quick check so the program doesn't crash.
    if num2 == 0:
        print("\n[ERROR] Whoops! You can't divide by zero. Math doesn't like that.")
    else:
        result = num1 / num2
        print(f"\n[DONE] {num1} / {num2} = {result}")

else:
    # If they typed something weird like 'hello' or '%', we tell them.
    print("\n[ERROR] Invalid operator! Use +, -, *, or /.")

# End of the script. Simple, right?
print("\nThanks for using the calculator. Keep learning!")
