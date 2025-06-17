#Check if the number is power of two or not
x=int(input("Enter a number : "))
if x>0 and x&(x-1) == 0:
    print(f"{x} is power of 2")
else:
    print(f"{x} is not power of 2")