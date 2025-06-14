for i in range(5, 0, -1):
    print(i)
print("Done")
#using reversed function
for i in reversed(range(1, 6, 1)):
    print(i)
print("Done")

#Reversing a string 

greeting = "Hello"
for i in reversed(greeting):
    print(i, end='')
print()
#Countig words of a string using split() function
sentence = "My name is Mohammad Ismail Zia . I am from Mau. And i am a Software Engineer "
count = 0
for word in sentence.split():
    count += 1
print(f"The sentence has {count} words in it ")