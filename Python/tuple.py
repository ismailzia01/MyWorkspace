car = ('Audi', 'BMW', 'Mercedes')
# #Creating a tuple using tuple() method
car = tuple(('Audi', 'BMW', 'Mercedes'))
#length of tuple
print(len(car))
# #cannot have two same items
# car = ('Audi', 'BMW', 'Mercedes', 'Audi')
# #will not be considered
# print(car)
# #tuples are immutable
# car[0] = 'BMW'
# print(car)
# #Accessing values using index
print(car[0])
# #Accessing values using negative index
print(car[-1])
#Tuple with one item
car = ('Audi',)
# #Creating a tuple with one item using tuple() method
car = tuple(('Audi',))
#tuple constructor
car = tuple(('Audi', 'BMW', 'Mercedes'))
#tuple slicing
car = ('Audi', 'BMW', 'Mercedes')
car = car[0:2]
print(car)
#tuple slicing with step
car = ('Audi', 'BMW', 'Mercedes')
car = car[0:2:1]
print(car)
#Adding items to a tuple
car = ('Audi', 'BMW', 'Mercedes')
car = car + ('Porsche',)
print(car)
#By converting a tuple to a list
car = list(car)
car.append('Tesla')
car = tuple(car)
print(car)  

#updating a tuple
car = ('Audi', 'BMW', 'Mercedes')
car = list(car)
car[0] = 'Porsche'
car = tuple(car)
print(car)
#Removing items from a tuple
car = ('Audi', 'BMW', 'Mercedes')
car = list(car)
car.remove('BMW')
car = tuple(car)
print(car)

#Unpacking a tuple
car = ('Audi', 'BMW', 'Mercedes')
car1, car2, car3 = car
print(car1)
print(car2)
print(car3)

#Unpacking a tuple with * (Asterisk)
car = ('Audi', 'BMW', 'Mercedes')
car1, *car2 = car
print(car1)
print(car2)