age = 22
if age >= 18:
    print("You are an adult.")
else:
    print("You are a minor.")  

#Short Hand If
if age >= 18: print("You are an adult.")
#Short Hand If Else
print("You are an adult.") if age >= 18 else print("You are a minor.")
#Nested If
if age >= 18:
    if age >= 21:
        print("You are an adult and can drink alcohol.")
    else:
        print("You are an adult but cannot drink alcohol.")
#If Elif Else
if age < 18:
    print("You are a minor.")
elif age < 21:
    print("You are an adult but cannot drink alcohol.")
else:
    print("You are an adult and can drink alcohol.")
#If Elif Else with multiple conditions
if age < 18:
    print("You are a minor.")
elif age < 21:
    print("You are an adult but cannot drink alcohol.")
elif age < 25:
    print("You are an adult and can drink alcohol but cannot rent a car.")
else:
    print("You are an adult and can drink alcohol and rent a car.")

    