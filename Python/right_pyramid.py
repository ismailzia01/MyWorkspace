rows = int(input("Enter the number of rows :"))
for i in range(1, rows+1):
    for j in range(1, i+1):
        print("*", end = ' ')
    print()
for i in range(1, rows+1):
    for j in range(rows - i, 0, -1):
        print("*", end = ' ')
    print()