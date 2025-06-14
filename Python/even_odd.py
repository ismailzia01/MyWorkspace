list = list(range(1,25))
even_numbers = []
odd_numbers = []
for ele in list:
    if ele % 2 == 0:
        even_numbers.append(ele)
    else:
        odd_numbers.append(ele)

print(even_numbers)
print(odd_numbers)