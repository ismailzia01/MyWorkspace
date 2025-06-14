car = {'brand' : 'audi', 'model' : 'q7'}
print(car)

#length using len() method
 
print(len(car))

#cannot have two same items with key
car = {'brand' : 'audi', 'model' : 'q7', 'model' : 'q8'}
#latest will be considered
print(car)

#dictionaries are mutable
car ['model'] = 'q7'
print(car)


#Accessing values using key names 
car = {'brand' : 'audi', 'model' : 'q7'}
print(car['brand'])
#Accessing values using get() method
car = {'brand' : 'audi', 'model' : 'q7'}
print(car.get('brand'))
#Accessing values using key() method
car_keys = car.keys()
print(car_keys)
#Accessing values using values() method
car_values = car.values()
print(car_values)
#Accessing values using items() method
car_items = car.items()
print(car_items)    

#Changing values using key names
car['model'] = 'q8'
print(car)  
#Changing values using update() method
car.update({'model' : 'q7'})
print(car)
#Adding new items using key names
car['year'] = 2020
print(car)
#Adding new items using update() method
car.update({'year' : 2021}) 

#Removing items using pop() method
car.pop('model')
print(car)
#Removing items using popitem() method
car.popitem()
print(car)
#Removing items using del() method
del car['brand']
print(car)
#Removing items using clear() method
car.clear()
print(car)
#Deleting the dictionary
del car
#Creating a dictionary using dict() method
car = dict(brand = 'audi', model = 'q7')
print(car)
#Creating a dictionary using fromkeys() method
car = dict.fromkeys(['brand', 'model'], 'audi')
print(car)
#Creating a dictionary using zip() method
car = dict(zip(['brand', 'model'], ['audi', 'q7']))
print(car)