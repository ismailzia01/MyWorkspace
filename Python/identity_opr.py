x = "Hello"
y = "Hello"

#using id() function to print the ids
print(id(x))
print(id(y))

#identity operators are used to compare the object
# of the ids that is pointed by a variable
print(x is y)
print(x is not y)

#The difference between == and is operator is 
#that == compares object whiile is compare ids

list1 = [1, 2, 3]
list2 = [1, 2, 3]

print(list1 == list2)
print(list1 is list2) # false because list can be modified 

#thats is why python doesnot point to same address 