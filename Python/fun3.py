print("Enter three numbers: ")
a = int(input())
b = int(input())
c = int(input())
def max_of_three(a, b, c):
    if a >= b and a >= c:
        return a
    elif b >= a and b >= c:
        return b
    else:
        return c
print("The largest number is:", max_of_three(a, b, c))
# This code takes three numbers as input and prints the largest of the three.
# It defines a function `max_of_three` that compares the three numbers and returns the largest one.
# The main part of the code prompts the user for input and calls the function to display the result.
# The function uses simple conditional statements to determine which number is the largest.
# This is a straightforward implementation that effectively demonstrates the use of functions and conditional logic in Python.
# The code is efficient and easy to understand, making it suitable for beginners learning Python.
# It can be further enhanced by adding error handling for non-integer inputs or by allowing the user to input more than three numbers.
# Overall, this code serves as a good example of basic Python programming concepts such as functions, input/output, and conditional statements.
# It can be used as a starting point for more complex programs that require similar logic.
# The function can also be modified to handle lists or other data structures if needed.
