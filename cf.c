#include <stdio.h>
#include <stdbool.h>

/*
 *Starts the game by asking who is going to go first
 *Returns true for human start and false for CPU start 
 *
 *Obtains user input for who will start the game and lets the user know
 *if they have entered an invalid input
*/

bool startGame(){
  int start=-1; //Start is 1 for player start and 2 for computer start
  printf("Who goes first? \nEnter \"1\" for yourself or \"2\" for computer...\n");

  while (start!= 1 && start!=2){
    scanf("%i", &start); //user enters number 1 for themselves to start and 2 for the computer to start
  
    if (start==1){
      printf("\nPlayer Start \n\n"); //Player Start
      return true; 
    }

    else if (start == 2){
      printf("\nCPU start \n\n"); //Computer Start
      return false;
    }

    else{
      printf("\nInvalid Input. Try Again...\n"); //Anything that is not 1 or 2
      while(getchar() != '\n'); //Clears any characters entered
    } 
  }
}

/*
 *Sets up the game board and makes it empty by placing '.' in every space
*/
void setBoard(char board[6][7]){
  for (int r= 0; r<6; r++){ //iterates through rows
    for(int c= 0; c<7; c++){ //iterates through columns
      board[r][c]= '.';
    }
  }
}

/*
 *Prints out the current game board
*/
void printBoard(char board[6][7]){
  printf("%c ", ' ');
  for (char header= 'A'; header<= 'G'; header++){ //Makes header A-G
    printf("%c ", header);
  }
  printf("\n");

  //Prints board with first column the row numbers
  for (int row=0, posNum=6; row<6, posNum>=1; row++, posNum--){ 
    printf("%i ", posNum);
    for (int column=0; column<7; column++){
      printf("%c ",board[row][column]);
    }
    printf("\n");
  }
  printf("\n");
}

/*
 *Checks gameboard to see if the game is a draw i.e. the board is full
 *returns true if the game is a draw and false if it is not
*/
bool tieCheck(char board[6][7]){
  int counter = 0; //iterates through columns
  for (int column=0; column<7; column++){
    if (board[0][column]!='.'){ //Checks that all columns have a token in them
      counter++;
    }
  }
  if (counter == 7){
    return true;
  }
  return false;
}

/*
 *checks for vertical wins
 *returns true for vertical wins, false otherwise
*/
bool checkVertical(char copyBoard[6][7], int row, int column, char token, int checkNum, int winningRows[4], int winningColumns[4]){
  int counter = 0;//counts how many tokens are in a row vertically
  int r;//iterates through rows
  int winCounter = 0;

  for (r = row; r < 7; r++){ //Checks vertically going down
    if (copyBoard[r][column] == token){
      counter++;
      winningRows[winCounter] = r;
      winningColumns[winCounter] = column;
      winCounter++;
      if (counter == checkNum){
        return true;
      }
    }
    else{
      break;
    }
  }
  
  counter=0;
  winCounter=0;
  for (r = r-1; r >= 0; r--){ //Checks vertically going up
    if (copyBoard[r][column] == token){
      counter++;
      winningRows[winCounter] = r;
      winningColumns[winCounter] = column;
      winCounter++;
      if (counter == checkNum){
        return true;
      }
    }
    else{
      break;
    }    
  }        
  return false; 
}

/*
 *checks for horizontal wins
 *returns true if there is a horizontal win, false otherwise
*/
bool checkHorizontal(char copyBoard[6][7], int row, int column, char token, int checkNum, int winningRows[4], int winningColumns[4]){
  int counter=0;//counts how many tokens are in a row horizontally
  int winCounter = 0;//holds columns and rows of a 4-in-a-row

  int c; //iterates through columns

  for (c = column; c < 7; c++){ //Checks horizontally to the right
    if (copyBoard[row][c] == token){
      counter++;
      winningRows[winCounter] = row;
      winningColumns[winCounter] = c;
      winCounter++;      
      if (counter == checkNum){
        return true;
      }
    }
    else{
      break;
    }
  }
  
  winCounter = 0;
  counter=0;
  for (c = c-1; c >= 0; c--){
    if (copyBoard[row][c] == token){ //Checks horizontally to the left
      counter++;
      winningRows[winCounter] = row;
      winningColumns[winCounter] = c;
      winCounter++;      
      if (counter == checkNum){
        return true;
      }
    }
    else{
      break;
    }    
  }  
  return false;
}

/*
 *Checks for diagonal wins
 *returns true if there are diagonal wins, false otherwise
*/
bool checkDiagonal(char copyBoard[6][7], int row, int column, char token, int checkNum, int winningRows[4], int winningColumns[4]){
  int counter = 0; //counts how many tokens are in a row diagonally
  int winCounter = 0; //holds columns and rows of a 4-in-a-row
  int rowD = row; //iterates row diagonally (starts equal to the row the last token was placed)
  int colD = column; //iterates column diagonally (starts equal to the column the last token was placed)
  
  counter=0;
    while(rowD>=0 && colD>=0){ //Checks diagonal from last place the token was placed up to the top left corner
      if (copyBoard[rowD][colD] == token){
        counter++;
        winningRows[winCounter] = rowD;
        winningColumns[winCounter] = colD;
        winCounter++;        
      if (counter == checkNum){
        return true;
      }
    }
    else{
      break;
    } 
    rowD--;
    colD--;   
  } 
  
  winCounter=0;
  counter=0;
  rowD = rowD + 1;
  colD = colD + 1;
  while (rowD < 6 && colD < 7){ //Checks diagonal going to the bottom right
    if (copyBoard[rowD][colD] == token){
      counter++;
      winningRows[winCounter] = rowD;
      winningColumns[winCounter] = colD;
      winCounter++;
      if (counter == checkNum){
        return true;
      }
    }
    else{
      break;
    } 
    rowD++;
    colD++;    
  }       
  
  counter=0;
  winCounter=0;
  rowD = row;
  colD = column;
    while (rowD < 6 && colD>=0){ //Checks from last place token placed to bottom left
      if (copyBoard[rowD][colD] == token){
        counter++;
        winningRows[winCounter] = rowD;
        winningColumns[winCounter] = colD;
        winCounter++;        
      if (counter == checkNum){
        return true;
      }
    }
    else{
      break;
    } 
    rowD++;
    colD--;   
  }        
  
  winCounter=0;
  counter=0;
  rowD = rowD - 1;
  colD = colD + 1;
  while (rowD >= 0 && colD < 7){ //Checks diagonal going to the top right
    if (copyBoard[rowD][colD] == token){
      counter++;
      winningRows[winCounter] = rowD;
      winningColumns[winCounter] = colD;
      winCounter++;      
      if (counter == checkNum){
        return true;
      }
    }
    else{
      break;
    } 
  rowD--;
  colD++;   
  }
  return false;
}

/*
 *Returns true if the game is over and false otherwise
*/
bool isGameOver(char board[6][7], int row, int column, char token, int checkNum, int winningRows[4], int winningColumns[4]){

  //checks for horizontal wins
  bool horizontalWin = checkHorizontal(board, row, column, token, checkNum, winningRows, winningColumns);
  if (horizontalWin){
    return true;
  }

  //checks for diagonal wins
  bool diagonalWin = checkDiagonal(board, row, column, token, checkNum, winningRows, winningColumns);
  if (diagonalWin){
    return true;
  }

  //checks for vertical wins
  bool verticalWin = checkVertical(board, row, column, token, checkNum, winningRows, winningColumns);
  if (verticalWin){
    return true;
  }
  return false;
}
  

/*
 *Carries out the first priorities of a computer move
 *
 *1st. Winning
 *2nd. Blocking a human win
 *
 *returns true if a move has been selected otherwise, returns false
*/
bool computerMove(char board[6][7], int coordinates[2], char humanToken, char cpuToken, int recordedMoves[42], int numMoves){
  int emptyRows[4];
  int emptyCols[4];
  
  char copyBoard[6][7]; //creates copy of board for checking possible moves
  int winCol; //"Winning" column computer selects for move
  int winRow; //"Winning" row computer selects for move
  char token = cpuToken; //token to check for cpu wins, then human wins for blocking

  for (int i=0; i<=1; i++){ //First checks if computer can win, then checks for blocks
    for (int column = 0; column<7; column++){
    
      for (int r=0; r<6; r++){ //Makes a copy of the game board
        for (int c=0; c<7; c++){
          copyBoard[r][c]=board[r][c];
        }
      }
    
      //Checks if column is full
      if (copyBoard[0][column]!='.'){
        continue;
      }

      //Checks where the next open space in the column is
      for (int row=0; row<6; row++){

        //Places token above the last placed token in that row
        if (copyBoard[row][column]!= '.'){
          copyBoard[row-1][column]= token;
          winRow=row-1;
          winCol=column;
          break;
        }
      
        //If the column is empty this places token in the first row
        else if (row==5 && copyBoard[row][column]=='.'){
          copyBoard[row][column]= token;
          winRow=row;
          winCol=column;
          break;
        }
      }

      //Check if there is any possible wins
      if(isGameOver(copyBoard, winRow, winCol, token, 4, emptyRows, emptyCols)){
        board[winRow][winCol]=cpuToken;
        coordinates[0] = winRow;
        coordinates[1] = winCol;
        recordedMoves[numMoves] = winCol;
        return true;
      }
    }
  token=humanToken;
  }
  return false;
}

/*
 *The computer attempts to make opportunites for 4 in a rows
 *
 *1st. The computer checks for places it can make 3 in a row
 *2nd. The computer checks for places it can make 2 in a row
 *
 *If connection is found returns true otherwise, returns false
*/
bool computerConnections(char board[6][7], int coordinates[2], char cpuToken, int recordedMoves[42], int numMoves){

  char copyBoard[6][7]; //Makes a copy of the game board to test its playable moves
  int emptyRows[4];
  int emptyCols[4]; 

  int winCol; //"Winning" column for where the computer wants to make its turn
  int winRow; //"Winning" row for where the computer wants to make its turn

  //Tries to make connections of 2 or 3
  int checkNum = 3; //First checks for 3 connections
  winRow = 0;
  winCol = 0;
  for (int i=0; i<=1; i++){  
    for (int column = 0; column<7; column++){
    
      for (int r=0; r<6; r++){ //Makes a copy of the game board
        for (int c=0; c<7; c++){
          copyBoard[r][c]=board[r][c];
        }
      }
    
      //Checks if column is full
      if (copyBoard[0][column]!='.'){
        continue;
      }

      //Checks where the next open space in the column is
      for (int row=0; row<6; row++){

        //Places token above the last placed token in that row
        if (copyBoard[row][column]!= '.'){
          copyBoard[row-1][column]= cpuToken;
          winRow=row-1;
          winCol=column;
          break;
        }
        
        //If the column is empty this places token in the first row
        else if (row==5 && copyBoard[row][column]=='.'){
          copyBoard[row][column]= cpuToken;
          winRow=row;
          winCol=column;
          break;
        }
      }
      
      //Check if there is any possible blocks
      if(isGameOver(copyBoard, winRow, winCol, cpuToken, checkNum, emptyRows, emptyCols)){  
        board[winRow][winCol]=cpuToken;
        coordinates[0] = winRow;
        coordinates[1] = winCol;
        recordedMoves[numMoves] = winCol;
        return true;
      }
    }

    checkNum = 2; //Now check for 2 connections
  }
  return false;
}

/*
 *Decides where to "randomly" place token for computer turn
 *
 *1st. Tries to place to the right of where the players put their token
 *2nd. Tries to place to the left where the player put their token
 *3rd. Tries to place token on top of players last put token 
*/
void cpuRandomPlace(char board[6][7], int coordinates[2], int lastColumn, char cpuToken, int recordedMoves[42], int numMoves){

  //If there are no connections found, put a token in a spot related to the last column the human player chose
  int column;
  int row;
  for (column = lastColumn - 1; column<7; column++){
    if (board[0][column]!='.'){
        continue;
    }
    for (row=0; row<6; row++){
      
      //Places token above the last placed token in that row
      if (board[row][column]!= '.'){
        board[row-1][column]= cpuToken;
        coordinates[0] = row-1;
        coordinates[1] = column;
        recordedMoves[numMoves] = column;
        return;
      }
      
      //If the column is empty this places token in the first row
      else if (row==5 && board[row][column]=='.'){
        board[row][column]= cpuToken;
        coordinates[0] = row;
        coordinates[1] = column;
        recordedMoves[numMoves] = column;
        return;
      }
    }
  }

  for (column = lastColumn-1; column>=0; column--){
    if (board[0][column]!='.'){
      continue;
    }
    for (row=0; row<6; row++){
      
      //Places token above the last placed token in that row
      if (board[row][column]!= '.'){
        board[row-1][column]= cpuToken;
        coordinates[0] = row-1;
        coordinates[1] = column;
        recordedMoves[numMoves] = column;
        return;
      }
      
      //If the column is empty this places token in the first row
      else if (row==5 && board[row][column]=='.'){
        board[row][column]= cpuToken;
        coordinates[0] = row;
        coordinates[1] = column;
        recordedMoves[numMoves] = column;
        return;
      }
    }
  }

  board[row][column]= cpuToken; //Place on top of where user placed token
  coordinates[0] = row;
  coordinates[1] = column;
  recordedMoves[numMoves] = column;
}

/*
 *Does a computer turn in order of priority
 *
 *1. Checks if the computer can win and if so makes it's move there
 *2. Checks if the computer can block the player from winning and makes it's move there
 *3. Tries to make connections of 3 and makes it's move there
 *4. Tries to make connections of 2 and makes it's move there
 *5. "Randomly" places token in relation to where the player's last move was
*/
void doComputerTurn(char board[6][7], int coordinates[2], int lastColumn, char humanToken, char cpuToken, int recordedMoves[42], int numMoves){
  void convertColumns(int arrayLength, int numColumns[arrayLength], char letterColumns[arrayLength]); //Initializes the convertColumns method

  char cpuMoveLetter[1]; //Holds the letter of the column the cpu plays during turn
  int cpuMoveNumber[1]; //Holds the number of the column the cpu plays during turn

  printf("It's the CPU's turn! \n \n");
  
  //First checks if cpu can win, then block human win 
  bool cpuMove = computerMove(board, coordinates, humanToken, cpuToken, recordedMoves, numMoves);
  if (cpuMove){

    //Prints out the column the computer chose
    cpuMoveNumber[0] = coordinates[1];
    convertColumns(1, cpuMoveNumber, cpuMoveLetter);
    printf("%c\n\n", cpuMoveLetter[0]);
    
    printBoard(board);
    return;
  }

  //Tries to make a connection horizontally, diagonally, or vertically
  bool cpuConnection = computerConnections(board, coordinates, cpuToken, recordedMoves, numMoves);
  
  if (cpuConnection){
    //Prints out the column the computer chose
    cpuMoveNumber[0] = coordinates[1];
    convertColumns(1, cpuMoveNumber, cpuMoveLetter);
    printf("%c\n\n", cpuMoveLetter[0]);
    
    printBoard(board);
    return;
  }

  //Places the token in relation to where the human placed their token
  cpuRandomPlace(board, coordinates, lastColumn, cpuToken, recordedMoves, numMoves);
  
  //Prints out the column the computer chose
  cpuMoveNumber[0] = coordinates[1];
  convertColumns(1, cpuMoveNumber, cpuMoveLetter);
  printf("%c\n\n", cpuMoveLetter[0]);
  
  printBoard(board);
}

/*
 *Does a human turn
 *
 *Takes in a user input and either completes move
 *or asks for a different move depending on if 
 *that column is full
*/
void doHumanTurn(char board[6][7], int coordinates[2], char humanToken, int recordedMoves[42],int numMoves){

  bool turn = false; //False until the turn has been successfully completed
  int column = 0; //Column Index
  int row=0; //for iterating through rows
  char col = ' '; //Letter Column

  printf("It's your turn! Enter a capital \"A\" through \"G\" to place your token in that column... \n");

  while (!turn){ 
    scanf(" %c" , &col); //User Input column Letter
    printf("\n");
    
    //Checks if input matches a column ID
    if(col != 'A' && col != 'B' && col != 'C' && col != 'D' && col != 'E' && col != 'F' && col != 'G'){
      printf("Invalid Column. Choose Again. \n");
      continue;
    }
    
    column = (col-'A'); //Gets Index of Column
    
    //Checks if column is full
    if (board[0][column]!='.'){
      printf("Column Full. Choose Again. \n");
      continue;
    }

    //Checks where the next open space in the column is
    for (row=0; row<6; row++){
      
      if (board[row][column]!= '.'){
        board[row-1][column]= humanToken;
        turn= true;
        row = row - 1;
        break;
      }
      
      else if (row==5 && board[row][column]=='.'){
        board[row][column]= humanToken;
        turn= true;
        break;
      }
    }
  }
  coordinates[0]= row;
  coordinates[1]=column;
  recordedMoves[numMoves] = column;
  printBoard(board);
}

/*
 *Creates array of column letters from array of column numbers
*/
void convertColumns(int arrayLength, int numColumns[arrayLength], char letterColumns[arrayLength]){
  for (int i=0; i<arrayLength; i++){
    switch (numColumns[i]){
      case (0):
      letterColumns[i] = 'A';
      break;
      case(1):
      letterColumns[i] = 'B';
      break;
      case (2):
      letterColumns[i] = 'C';
      break;
      case (3):
      letterColumns[i] = 'D';
      break;
      case (4):
      letterColumns[i] = 'E';
      break;
      case (5):
      letterColumns[i] = 'F';
      break;
      case (6):
      letterColumns[i] = 'G';
      break;
    }
  }
}
/*
 *Converts winning columns from integers to letters and changes winning rows to the proper number rows on the gameboard 
*/
void convertRowColWins(char winColLetters[4], int winningRows[4], int winningColumns[4]){
  for (int i=0; i<4; i++){
    winningRows[i] = 6-(winningRows[i]);
  }
  convertColumns(4, winningColumns, winColLetters);
}

/*
 *Sorts the winning coordinates into alphabetical order
 *for printing the winning spots to console
*/
void sorter(int winningRows[4], int winningCol[4]){
  for (int i = 0; i<3; i++){
    for (int j = (i+1); j<4; j++){
      if (winningCol[j]<winningCol[i]){
        int Rowtemp = winningRows[i];
        winningRows[i] = winningRows[j];
        winningRows[j] = Rowtemp;
        char colTemp = winningCol[i];
        winningCol[i] = winningCol[j];
        winningCol[j] =colTemp;
      }
    }
  }
}

/*
 *Plays Connect-4 against a computer AI
*/
int main(void) {
  char humanToken; //the human player's character token
  char cpuToken; //the computer player's character token
  char board[6][7]; //array representing the game board
  int recordedMoves[42]; //Keeps track of the number column of each move
  int numMoves = 0; //Keeps track of the number of moves
  char letterRecordedMoves[42]; //Holds the letter column of each move
  int humanCoordinates[2]; //Creates array for row and column of human's last placed token
  int cpuCoordinates[2]; //Creates array for row and column of computer's last placed token
  int winningColumns[4]; //Contains the winning columns
  int winningRows[4]; //Contains the winning rows
  char winColLetters[4]; //Contains the winning column letters
  int lastColumn = 4; //Gives last column that human placed their token (starts as 4 to place cpu start in center)
  bool humanWinCheck = false, cpuWinCheck = false; //Holds true if either human or computer has won

  bool starter = startGame(); //returns either true(Human Start) or false(Computer Start)

  setBoard(board);
  printBoard(board);
  
  bool computerTurn; //Holds true if its the computer's turn

  if(starter){ //computerTurn is false
    computerTurn = false;
    humanToken = 'X';
    cpuToken = 'O';
    }
  else{ //computerTurn is true
    computerTurn = true;
    humanToken = 'O';
    cpuToken = 'X';
  } 
  
  while (!cpuWinCheck && !humanWinCheck && !tieCheck(board)){ //while the game has not been won (or tied)

    if(computerTurn == 1){ //Computer's Turn
      doComputerTurn(board, cpuCoordinates, lastColumn, humanToken, cpuToken, recordedMoves, numMoves);
      numMoves++;
      computerTurn = false;
      
      //Checks to see if the CPU won during this move
      cpuWinCheck = isGameOver(board, cpuCoordinates[0], cpuCoordinates[1], cpuToken, 4, winningRows, winningColumns);
      if (cpuWinCheck){
        printf("Computer Wins! \n\n");
      }
      
    }
    
    else{ //Human's Turn
      doHumanTurn(board, humanCoordinates, humanToken, recordedMoves, numMoves);
      numMoves++;
      computerTurn = true;
      lastColumn = humanCoordinates[1];
      
      //Checks to see if the human won during this move
      humanWinCheck = isGameOver(board, humanCoordinates[0], humanCoordinates[1], humanToken, 4, winningRows, winningColumns);
      
      if(humanWinCheck){
        printf("Congratulations You Win! \n\n");
      }
      
    }
  }

  //Checks if the game was a tie
  if (tieCheck(board)){
    printf("It's a Draw! \n\n");
  }

  printBoard(board); //prints endgame board
  
  if (!tieCheck(board)){ ////Prints winning rows and columns if game is not a tie
    if (winningColumns[0] == winningColumns[1]){
      printf("Connect 4 in a vertical with discs: ");
    }
    else if (winningRows[0] == winningRows[1]){
      printf("Connect 4 in a horizontal with discs: ");
    }
    else{
      printf("Connect 4 in a diagonal with discs: ");
    }
  
    sorter(winningRows, winningColumns); //Sorts winning discs in alphabetical column order
    convertRowColWins(winColLetters, winningRows, winningColumns); //Converts column letters into integers


    for (int i = 0; i<3; i++){
      printf("%i%c, ", winningRows[i], winColLetters[i]);
    }

    printf("and %i%c \n", winningRows[3], winColLetters[3]);
  }

  //Converts recorded column numbers to letters
  convertColumns(numMoves, recordedMoves, letterRecordedMoves);

  //Prints recorded moves
  printf("Recorded Moves: {");
  int i;
  for (i = 0; i < (numMoves-1); i++){
    printf("%c, ", letterRecordedMoves[i]);
  }
  printf("%c}\n", letterRecordedMoves[i]);

  return 0;
}