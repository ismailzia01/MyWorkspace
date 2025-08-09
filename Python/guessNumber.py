#building a guess the number game from scratch and adding both computer and user guesses
import random

def gameover(char):
    if char != 'n':
        guess_number()
    else: 
        exit()

def guess_number():
    range = int(input("Choose range from 1 to range :"))
    random_number = random.randint(1, range)
    guess = int(input(f"Guess a number between 1 and {range} : "))
    char = 'y'
    count = 1
    while(1):
        if guess == random_number:
            print(f"Yay! you guessed it right in {count} times !!!")
            print("Play Again [y/n] :")
            char = input()[0]
            gameover(char)
        elif count >= 3:
            if guess > random_number: 
                print("too high ")
            elif guess < random_number:
                print("too low")
        print("You Guessed it wrong \n")
        guess = int(input("Try Again :"))
        count += 1

def guess_numberAI():
    range = int(input("Choose a range from 1  to x"))
    random_number = random.randint(1, range)
    guess = random.randint(1, range)
    count = 1
    while(1):
        print(f"is {guess} is too high [H], too low [L] or correct [C]\n")
        var = input()
        if var == 'c' or var == 'C':
            print(f"Yay! the computer guessed it right in {count} times !!!")
            print("Play Again [y/n] :")
            char = input()[0]
            gameover(char)
        elif var == 'h' or var == 'H':
            guess = random.randint(1, guess)
        elif var == 'l' or var =='L':
            guess = random.randint(guess, range)
        count += 1
while(1):
    print("\t----Guess the Number----\n")
    print("\t1) User\n")
    print("\t2) Computer\n")
    print("\t3) Exit \n")
    choice = int(input("choose and option : "))
    if choice == 1:
        guess_number()
    elif choice == 2:
        guess_numberAI()
    elif choice == 3:
        exit()
    else :
        print("Invalid input: ")










#      tutorial output
#       guess the number
#        let computer guess the number 
#       guess the number 
#       try again , 