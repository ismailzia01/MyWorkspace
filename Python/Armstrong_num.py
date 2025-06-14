num = int(input("Enter a number :"))
n = num
count = 0
sum = 0

while n != 0:
    n //= 10
    count += 1
n = num
while n != 0:
    digit = n % 10
    sum += digit ** count
    n //= 10
if sum == num:
    print("Armstrong")
else:
    print("NO")