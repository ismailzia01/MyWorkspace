#List in Python
num = [1, 2, 3, 4, 5]
print(num)#Printing list to the console 

#List are mutable 
num[0] = 9
num[3] = 6
print(num)

#multidimensional list 
my_list = [[1,2,3], [['a', 'b', 'c'], 5, 6]]
print(my_list)

#accessing elements from a multidimensional list
print(my_list[0])
print(my_list[1][0])
print(my_list[1][0][1])

#Adding elements to a list 
#using append() method
# add item at the end
num.append(8)
num.append(14) 
print(num)

#using insert() method 
#add item at a specific position
num.insert(5, 25)
print(num)

#using extend() method
#add all items of one list in another list
list1 = [1, 2, 3]
list2 = [4, 5, 6]
list1.extend(list2)

print(list1)
print(len(list1))

#taking input of lists
#using for loop
#first get the size 

size = int(input("Enter the size of list : "))
list = []
for i in range(size):
    x = int(input())
    list.append(x)

print(list)

#Remove items from list 
#using remove() method
#Removes specified item
list1.remove(1)
print(list1)

#using pop() method 
list1.pop(1) #returns deleted item
print(list1)

#if the index is not specified then 
#the last item will be deleted

#using del keyword
#removes item at specified index
#can remove the complete list
del list2[0]
print(list2)
del list1
print(list2)

#clear list using clear() method 

list2.clear()
print(list2)
