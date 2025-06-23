num1=10
num2=20
num3=30
#find the largest of three
if num1>=num2:
    if num3>=num1:
        print(f"{num3} is the greatest number")
    else:
        print(f"{num1} is the greatest number")
elif num2 <= num3:
    print(f"{num3} is the greatest number ")
else:
    print(f"{num2} is the greatest number ")