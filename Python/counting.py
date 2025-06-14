str = input("Enter a string :")
digit = 0
letters = 0
special = 0
for c in str:
    if c.isdigit():
        digit += 1
    elif c.isalpha():
        letters += 1
    else:
        special += 1

print(f"Digits    : {digit}")
print(f"Letters   : {letters}")
print(f"Special   : {special}")