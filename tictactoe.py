#
#   Vladislav Zolotukhin - A simple Tic-Tac-Toe practice example
#   2024-10-15
#

from tkinter import *
import random

def next_turn(row, col):
    global player
    if buttons[row][col]['text'] == "" and check_winner() is False: # if the spot is available and a winner hasn't been declared
        if player == players[0]: # default symbol is "x"
            buttons[row][col]['text'] = player
            if check_winner() is False:
                player = players[1]
                label.config(text=(players[1] + "'s turn"))
            elif check_winner() is True:
                label.config(text=(players[0] + " wins!"))
            elif check_winner() == "Tie":
                label.config(text=("Tie Game"))
        else:
            buttons[row][col]['text'] = player
            if check_winner() is False:
                player = players[0]
                label.config(text=(players[0] + "'s turn"))
            elif check_winner() is True:
                label.config(text=(players[1] + " wins!"))
            elif check_winner() == "Tie":
                label.config(text=("Tie Game"))


def check_winner():
    for row in range(3):
        # if all the button symbols are the same and there are symbols (not empty "")
        if buttons[row][0]['text'] == buttons[row][1]['text'] == buttons[row][2]['text'] != "": 
            buttons[row][0].config(fg="red")
            buttons[row][1].config(fg="red")
            buttons[row][2].config(fg="red")
            return True
    
    for col in range(3):
        if buttons[0][col]['text'] == buttons[1][col]['text'] == buttons[2][col]['text'] != "": 
            buttons[0][col].config(fg="red")
            buttons[1][col].config(fg="red")
            buttons[2][col].config(fg="red")
            return True
    
    # Diagonals
    if buttons[0][0]['text'] == buttons[1][1]['text'] == buttons[2][2]['text'] != "":
        buttons[0][0].config(fg="red")
        buttons[1][1].config(fg="red")
        buttons[2][2].config(fg="red")
        return True
    elif buttons[0][2]['text'] == buttons[1][1]['text'] == buttons[2][0]['text'] != "":
        buttons[0][2].config(fg="red")
        buttons[1][1].config(fg="red")
        buttons[2][0].config(fg="red")
        return True
    # Tie game (no empty spaces remaining on board)
    elif empty_spaces() is False:
        for row in range(3):
            for col in range(3):
                buttons[row][col].config(bg="grey")
        return "Tie"
    # No winner declared
    return False

def empty_spaces():
    spaces = 9 

    for row in range(3):
        for col in range(3):
            if buttons[row][col]['text'] != "":
                spaces -= 1

    if spaces == 0:
        return False
    return True           


def new_game():
    global player
    player = random.choice(players)
    label.config(text=(player) + "'s turn")
    for row in range(3):
        for col in range(3):
            buttons[row][col].config(text="", bg="#F0F0F0", fg="black")
            
window = Tk()
window.title("Tic-Tac-Toe")
players = ['x', 'o'] # can swap these for other less recognizable symbols if desired
player = random.choice(players) # random player starts first

buttons = [[0,0,0],[0,0,0],[0,0,0]] # gameboard is a 2D list

label = Label(text= player + "'s turn", font=("Arial", 40))
label.pack(side="top")

reset_button = Button(text="Restart Game", font=("Arial", 20), command=new_game)
reset_button.pack(side="top")

frame = Frame(window)
frame.pack()

# add the buttons for each tic-tac-toe cell 
for row in range(3):
    for column in range(3):
        buttons[row][column] = Button(frame, text="", font=("Arial",20), width=5, height=2, command=lambda row=row, column=column: next_turn(row, column))
        buttons[row][column].grid(row=row, column=column)
window.mainloop()