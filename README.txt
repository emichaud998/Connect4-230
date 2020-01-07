Our implementation of a Connect 4 game begins in the main method with initializing 
all the variables needed to run the game, including our array "board" which holds 
the game board and all its changes as the game progresses. First, the "startGame" 
method is called, which looks for a input of a 1 or 2 to decide who is going first 
and returns this decision. The "setBoard" method is called next, initializing an 
empty game board to contain the '.' character for every space in the board. Then, 
"printBoard" is called to print the starting empty board. An if statement assigns 
'X' tokens to the starting player and 'O' tokens to the second player. The bulk of 
the program is run in the next while loop which progresses until an end of game 
situation by checking if the "isGameOver" or "tieCheck" methods return true. The 
while loop switches between the human player's turn and the computer's turn until 
the game is either won or tied. It uses "doComputerTurn" and "doHumanTurn" to 
carry out the respective player's turn, and prints out the game board state after 
every move. In the "doHumanTurn" method, the user is prompted to pick a column to 
place their token until they pick one that is valid and not full. In the 
"doComputerTurn" method, the computer first looks to see if it can win and places 
a token there, if not it looks to see if the human can win anywhere and places a 
token there to block it, then if neither of those are true, the computer looks to 
build a connection horizontally, vertically, or diagonally, and finally, if it 
cannot do any of these it places a token near the last place the human placed 
their token. Once the game is over, the program then converts the winning rows and 
columns to the correct format using "Sorter" and "convertRowColWins" methods and 
prints these out. Finally, a list of all the columns played during the game is 
printed and the program ends. 

Link to Video:
https://youtu.be/6hSKiEwBj60