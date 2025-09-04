import random
import string
with open("words.txt", 'r') as file:
    my_list = file.read().split()

#have only words that don't contain numbers are other symbols
lives = 10
words_list = [word for word in my_list if word.isalpha()]

def HangMan():
    word = random.choice(words_list).upper()#randomly chooses a word
    word_letter = set(word)#letters in the word ,
    alphabet = set(string.ascii_uppercase)
    used_letter = set()# what the user has guessed
    lives = 6

    while len(word_letter) > 0 and lives > 0:
        print(f"\nYou have left Lives : {lives}")
        #letters used
        #' '.join(['a', 'b', 'cd']) -->'a b cd'
        print("Letters Used : ", ' '.join(used_letter))
        
        #what current word is (ie W - R D)
        word_list = [letter if letter in used_letter else '-' for letter in word]
        print("\nCurrent Word : ",' '.join(word_list))
        user_letter = input("Guess a character :")[0].upper()
        if user_letter in alphabet - used_letter:
            used_letter.add(user_letter)
            if user_letter in word_letter:
                word_letter.remove(user_letter)
            else:
                lives = lives - 1 # takes away a life  if wrong 
                print("Letter is not in the word !")
        elif user_letter in used_letter:
            print(f"You Have Already used this letter , Guess Another one")
        else :
            print("Invalid character !")
        #print(used_letter)
        #print(word)
    # gets here when len(word_list) == 0 and lives == 0
    if lives == 0:
        print(f"You died , sorry, the word was {word}")
        print("Play Again [y/n] :")
        char = input()[0]
        GameOver(char)
    else :
        print(f"You guessed the word {word}")
        print("Play Again [y/n] :")
        char = input()[0]
        GameOver(char)

def GameOver(char):
    if char != 'n':
        HangMan()
    else: 
        exit()
HangMan()