with open("hello.txt", 'r') as file:
    list = file.read().split()
print(list) 
only_letters = [word for word in list if word.isalpha()]
print(only_letters)