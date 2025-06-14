#mutabel
#list , dict , 
# tupple , string 

x = 10 
print(x)

 #purely object oriented 
y = x
print(y)
print(x)
print(id(x))
print(id(y))

car = ['audi', 'bmw', 'mercedes']
car3 = ['audi', 'bmw', 'mercedes']
print(id(car))
print(id(car3))
car2 = car
print(car)
print(car2)
car2[0] = 'new'
print(car2)
print(car)

str = "my name is ismail , 234 , @"
digit = 0
letter = 0
special = 0
for char in str:
    if str.isalpha():
        letter += 1
    elif str.isnumeric():
        digit += 1
    else:
        special += 1
    
print(letter)
print(digit)
print(special)