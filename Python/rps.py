import random

def gameover(char):
    if char != 'n':
        game()
    else: 
        exit()

def game():
    while(1):
        print("(r) for rock, (p) for paper, (s) for scissor")
        var = random.randint(0, 2)
        if var == 0:
            computer_choice = 'r'
        elif var == 1:
            computer_choice = 'p'
        elif var == 2:
            computer_choice = 's'
        user_choice = input("Your Choice : ")[0]
        if computer_choice == user_choice:
            print(f"Computer choice : {computer_choice}")
            print("it's a tie !")
            print("Play Again ? [y/n]:")
            ch = input()[0]
            gameover(ch)
        else:
            if (computer_choice == 'r' and user_choice == 's') or (computer_choice == 's' and user_choice == 'p') or computer_choice == 'p' and user_choice == 'r':
                print(f"Computer choice : {computer_choice}")
                print("You Lost !")
                print("Play Again ? [y/n]:")
                ch = input()[0]
                gameover(ch)
            else:
                print(f"Computer choice : {computer_choice}")
                print("You Won !")
                print("Play Again ? [y/n]:")
                ch = input()[0]
                gameover(ch)

print("\t---Rock Paper Scissor---\n") 
game()