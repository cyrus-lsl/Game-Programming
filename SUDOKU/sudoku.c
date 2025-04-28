#include <stdio.h>

// Initialize the specified game board.
void initGameBoard(int gameBoard[][9], int puzzle[][9]) {

    for (int i = 0 ; i < 9 ; i++){
        for (int j = 0 ; j < 9 ; j++){
            gameBoard[i][j] = puzzle[i][j];
        }
    }
}

/* Display the specified game board on the screen.
   You are required to exactly follow the output format stated in the project specification.
   IMPORTANT: Using other output format will result in mark deduction. */
void printGameBoard(int gameBoard[][9]) {
    printf("  012 345 678\n");
    printf("+---+---+---+\n");
    for (int i = 0 ; i <= 8 ; i++){
        if (i % 3 == 0 && i != 0){
            printf("+---+---+---+\n");
        }
        printf("%d|",i);
        for (int j = 0 ; j <=8 ; j++){
            if(j % 3 == 0 && j != 0){
                    printf("|");
                }
            if (gameBoard[i][j] == -1){
            printf("X");
            }
            else if (gameBoard[i][j] == 0){
                printf(" ");
            }
            else{
                printf("%d",gameBoard[i][j]);
            }
        }
        printf("\n");
    }
    printf("+---+---+---+\n");
}

/* inputBoard() reads a char '1' to '9', or 'H' from the player. */
int inputBoard(int gameBoard[][9], int x, int y, int sol[][9], int gameMode){
    // TODO: Complete this part
    // Hint: Use while loop to keep scanning input from the player
    char cellInput;
    while (1) {
        printf("Input a number [or H: hint]: ");
        scanf(" %c", &cellInput);
        if ((cellInput < '1' || cellInput > '9') && cellInput != 'H' && cellInput != 'S') {
            printf("Invalid Input.\n");
            gameBoard[x][y] = 0;
            printGameBoard(gameBoard);
            continue;
        }
        else if (cellInput == 'H' && gameMode == 1) {
            printf("No hint in Hard mode.\n");
            gameBoard[x][y] = 0;
            return -1;
        }
        else if(cellInput == 'H'){
            gameBoard[x][y] = sol[x][y];
            return 1;
            }
        else if (cellInput == 'S'){
            return 2;
        }
        else if (cellInput == sol[x][y] + '0'){
            gameBoard[x][y] = sol[x][y];
            return 0;
        }
        else if (gameMode == 0){
            printf("Sorry, %c should not be placed at (%d,%d).\n", cellInput , x , y);
            return -1;
        }
        else {
            gameBoard[x][y] = cellInput - '0';
            return -2;
        }
    }
}
// This function outputs 1 if the gameBoard is finished (and identical to the solution), and 0 otherwise.
int checkFinish(int gameBoard[][9], int sol[][9]){
    // TODO: Complete this part
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (gameBoard[i][j] != sol[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}


/* ** Hard Mode ** */

int checkSolutionDetail(int gameBoard[][9], int x, int y){
    // TODO: Complete this part
    int incorrect = 0;
    for(int i = 0 ; i <= 8 ; i++){
        if (gameBoard[x][i] == gameBoard[x][y] && i != y){
            printf("Check again the numbers in row %d.\n", x);
            incorrect = 1;
            break;
        }
    }
    for (int j = 0 ; j <= 8 ; j++){
        if (gameBoard[j][y] == gameBoard[x][y] && j != x){
            printf("Check again the numbers in column %d.\n", y);
            incorrect = 1;
            break;
        }
    }
    int a = ( x / 3 ) * 3;
    int b = ( y / 3 ) * 3;
    for (int k = a ; k < a + 3 ; k++){
        for(int l = b ; l < b + 3 ; l++){
            if (gameBoard[k][l] == gameBoard[x][y] && (k != x || l != y)) {
                printf("Check again the numbers in subgrid where (%d, %d) is at.\n", x, y);
                incorrect = 1;
                break;
            }
        }
    }
    return incorrect;
}

/* checkFillable() checks the row/column/subgrid that the cell (x, y) resides at given the current gameBoard. */
int checkFillable(int gameBoard[][9], int x, int y){
    // TODO: Complete this part
    int fill[9] = {0};
    for (int i = 0; i < 9; i++) {
        if ((gameBoard[x][i] != 0)) {
            fill[gameBoard[x][i]-1] = 1;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (gameBoard[i][y] != 0) {
            fill[gameBoard[i][y]-1] = 1;
        }
    }
    int a = ( x / 3 ) * 3;
    int b = ( y / 3 ) * 3;
    for (int i = a ; i < a + 3; i++) {
        for (int j = b ; j < b + 3; j++) {
            if (gameBoard[i][j] != 0) {
                fill[gameBoard[i][j]-1] = 1;
            }
        }
    }
    int count = 0;
    for (int i = 0 ; i <= 8 ; i++){
        if (fill[i] == 1){
            count++;
        }
    }
    if (count == 9){
        printGameBoard(gameBoard);
        printf("Cell (%d, %d) is locked.\n", x, y);
      return 0;
    }
    return 1;
}

/* isLockBoard() determines if the input gameBoard contains a locked cell. */
int isLockBoard(int gameBoard[][9]){
    // TODO: Complete this part
    for (int i = 0 ; i <= 8 ; i++) {
        for (int j = 0 ; j <= 8 ; j++) {
            if (gameBoard[i][j] == 0) {
                if (checkFillable(gameBoard, i, j) == 0) {
                    printf("Board is locked.\n");
                    return 1;
                }
            }
        }
    }

    return 0;
}


// the savePuzzle function saves the gameBoard and solution to the file "saveGame.txt"
int savePuzzle(int gameBoard[][9], int sol[][9]){
    // TODO: Complete this part
    FILE *fp;
    fp = fopen("saveGame.txt","w");
    if (fopen("saveGame.txt","w") == NULL){
        return 0;
    }
    for (int i = 0 ; i <= 8 ; i++){
        for (int j = 0 ; j <= 8 ; j++){
            fprintf(fp, "%d ", gameBoard[i][j]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp, "\n\n");
    for (int i = 0 ; i <= 8 ; i++){
        for (int j = 0 ; j <= 8 ; j++){
            fprintf(fp, "%d ", gameBoard[i][j]); 
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
  printf("Game Saved.");
    return 1;
}

// the loadPuzzle function load the gameBoard and solution from the file "saveGame.txt"
    // TODO: Complete this part
    FILE *fp = fopen("saveGame.txt","r");
    if (fopen("saveGame.txt","r") == NULL){
        return 0;
    }
    else {
        for (int i = 0 ; i <= 8 ; i++){
            for (int j = 0 ; j <= 8 ; j++){
                fscanf(fp, "%d", &gameBoard[i][j]);
            }
        }
        for (int i = 0 ; i <= 8 ; i++){
            for (int j = 0 ; j <= 8 ; j++){
                fscanf(fp, "%d", &gameBoard[i][j]);
            }
        }
        fclose(fp);
        return 1;
    }
}

// A helper function to craft a text file containing the inputs to fill in the puzzle according to the solution.
void printSolution(int puzzle[][9],int solution[][9]){
    FILE *fp;
    fp = fopen("textInput.txt", "w");
    if (fp == NULL) {printf("Error in writing file."); return;}

    fprintf(fp,"0\n"); // Change to 1 if runns in Hard mode
    for(int i=0; i<9; i++)
    for (int j=0; j<9; j++){
        if (puzzle[i][j]==0){
            fprintf(fp, "%d %d\n", i, j);
            fprintf(fp, "%d\n", solution[i][j]);
        }
    }
    fclose(fp);
}

/* The main function */
int main()
{
    int myPuzzle[9][9];
    int mySolution[9][9];
    int gameBoard[9][9];

    int gameMode, chances = 3, hintCount = 0;
    int x, y;

    int number;
    int win = 0, validIn = 0, inputValid = 0;
    int check = 0;
    
    char save;
    printf("Load the saved game (y/n)?");
    scanf("%c", &save);
    if (save == 'y'){
        loadPuzzle(gameBoard, mySolution);
    }
    while(1) {
        printf("Enter the game mode [0: Easy. 1: Hard]: ");
        scanf("%d", &gameMode);
        FILE *fp;
        fp = fopen("puzzle.txt", "r");
        for (int i = 0 ; i <= 8 ; i++){
            for (int j = 0 ; j <= 8 ; j++){
                fscanf(fp,"%d", &myPuzzle[i][j]);
            }
        }
        for (int i = 0 ; i <= 8 ; i++){
            for (int j = 0 ; j <= 8 ; j++){
                fscanf(fp,"%d", &mySolution[i][j]);
            }
        }
        fclose(fp);
        if (gameMode != 0 && gameMode != 1){
            printf("Invalid Input.\n");
        }
        else if (gameMode == 0){
            printf("You have selected Easy mode.\n");
            break;
        }
        else{
            printf("You have selected Hard mode.\n");
            break;
        }
    }
    initGameBoard(gameBoard, myPuzzle);
    
    while(win == 0){
        printGameBoard(gameBoard);
        printf("Select a row and column: ");
        scanf("%d %d", &x, &y);
        if (x > 8 || y > 8 || x < 0 || y < 0){
            printf("Out of bound. Input Again.\n");
            continue;
        }
        else if (gameBoard[x][y] != 0){
            printf("Occupied.\n");
            continue;
        }
        else{
            gameBoard[x][y] = -1;
            printGameBoard(gameBoard);
            int result = inputBoard(gameBoard, x, y, mySolution, gameMode);
            if (result == 1){
                number = gameBoard[x][y];
                hintCount++;
                continue;
            }
            else if (result == -1) {
                gameBoard[x][y] = 0;
                continue;
            }
            else if (result == 2){
                savePuzzle(gameBoard, mySolution);
                return 0;
            }
          }
            if (checkFinish(gameBoard, mySolution) == 1){
                win = 1;
            }
    if(isLockBoard(gameBoard) == 1){
        win = -1;
    }
    }
    // Output the winning or losing message
    if(gameMode == 0){
        printGameBoard(gameBoard);
        printf("Congratulations! You have finished a puzzle in easy mode and used %d hints.", hintCount);
    }
    else if (gameMode == 1 && win == -1){
        printf("You lose.");
    }
    else {
        printGameBoard(gameBoard);
        printf("Congratulations! You have finished a puzzle in hard mode with %d chances left.", chances);
    }
    return 0;
}
