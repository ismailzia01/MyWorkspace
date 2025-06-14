num = int(input("Enter a Number :"))
if num <= 1:
    print("Not Prime")
else:
    flag = True
    i = 2
    while i <= num//2:
        if num % i == 0:
            flag = False
            break
        i += 1
if flag:
    print("Prime")
else:
    print("Not Prime")