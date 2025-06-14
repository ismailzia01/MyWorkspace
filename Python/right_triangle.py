n = int(input("Enter the length of the triangle: "))
for i in range(n+1):
    for j in range(i):
        print(i, end = ' ')
    print()