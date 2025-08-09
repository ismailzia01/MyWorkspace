num = int(input("Enter a number: "))
def even_or_odd(num):
    return num % 2 == 0
print("The number is even." if even_or_odd(num) else "The number is odd.")