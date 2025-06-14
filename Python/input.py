name = input("Enter your name : ")
#input() method always returns a string
#so we need to typecast inorder to have a integer value

age = int(input("Enter your age : "))

print("Hello {} !" .format(name))
print("You are {} years old ".format(age))  

#reading a list using split() method
#split() method is used to split a string into a list
#syntax string.split(seperator, maxsplit)
#if we do not provide any argument then it will
#split after every whitespace 

list = input("Enter the elements of list : ").split()
print(list)

for i in range(0, 3):
    list[i] = int(list[i])
print(list)