terms = int(input("Enter no. of terms :"))
val1 = 0
val2 = 1
if terms == 1:
    print(val1)
elif terms == 2:
    print(val1, val2)
else: 
    print(f"{val1}, {val2}", end = ', ')
    while terms > 2:
        val3 = val1 + val2
        print(val3, end = ', ')
        val1 = val2
        val2 = val3
        terms -= 1
print()

