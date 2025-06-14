lines = int(input("Enter no. of lines : "))
triangle = []
for i in range(lines):
    row = []
    for j in range(i + 1):
        if j == 0 or j == i:
            row.append(1)
        else:
            row.append(triangle[i-1][j-1]+triangle[i-1][j])
    triangle.append(row)

#printing the triangle with spacing
for i in range(lines):
    print(' ' * (lines - i), end = '')
    for num in triangle[i]:
        print(num, end = ' ')
    print()