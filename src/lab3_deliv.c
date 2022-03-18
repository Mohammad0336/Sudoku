//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <pthread.h>
//
//
////global variables
//int puzzle[9][9];
//
//// function to read puzzle into array
//int readPuzzle(void){
//	FILE *myFile;
//
//	myFile = fopen("src/puzzle.txt", "r");
//
//	if (!myFile){
//		printf("Error Opening File\n");
//		return -1;
//	} else {
//
//		for (int i = 0; i < 9; i++){
//
//			for (int j = 0; j < 9; j++){
//
//				fscanf(myFile, "%d", &puzzle[i][j]);
//			}
//		}
//
//
//		printf("Puzzle was parsed!\n\n");
//	}
//
//	return 1;
//
//
//}
//
////check if square is valid
//int isSafe(int puzzle[9][9], int row, int col, int num){
//
//	// check if used in row
//	for (int i= 0; i < 9; i++ )
//		if (puzzle[row][i] == num)
//			return -1;
//
//	// check if used in col
//	for (int i= 0; i < 9; i++ )
//		if (puzzle[i][col] == num)
//			return -1;
//
//	// check if used in box
//	for (int row = 0; row < 3; row++)
//		for (int col = 0; col < 3; col++)
//			if (puzzle[row + (row  -row % 3)][col + (col - col % 3)] == num)
//				return -1;
//
//	// if all the checks are passed
//	// return valid
//	return 1;
//
//
//
//}
//
//// function to solve puzzle
//// ran recursvely
//int solve(int puzzle[9][9], int row, int col) {
//
//	//reached bottom of puzzle
//	if (row == 9){
//		//success
//		return 1;
//	}
//
//	// if reached last number in row
//	if (col == 9){
//		row++;
//		col = 0;
//		solve(puzzle, row, col);
//	}
//
//	//check if number in square
//	if (puzzle[row][col] != 0){
//		col++;
//		solve(puzzle,row,col);
//	}
//
//	// try each number in the square
//	// check if its safe to place
//	for (int i = 1; i < 10; i++){
//		if (isSafe(puzzle, row, col, i) == 1){
//			//put number in square
//			puzzle[row][col] = i;
//			solve(puzzle, row, col);
//		}
//
//		// if did not work
//		puzzle[row][col] = 0;
//	}
//
//	return -1;
//}
//
//
//// function to verify
//// uses threads
//
//
//
//// print puzzle
//void printPuzzle(int puzzle[9][9]){
//
//	for (int i = 0; i < 9; i++){
//		for (int j = 0; j < 9; j++){
//			printf("%d ", puzzle[i][j]);
//		}
//		printf("\n");
//	}
//}
//
//
//// Thread functions
//
//
//// for thread functions pass the starting point and calculate based the row, col or square
//int checkRow(void *threadArg){
//
//	//pass start position to function
//	struct position *positionPtr = (struct position *)threadArg;
//	struct position pos = *positionPtr;
//
//	int accessed[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//
//	for(int i = 0; i < 9; i++){
//		accessed[i] = 1;
//	}
//
//	int sum= 0;
//
//	// after checking all numbers
//	for (int i = 0; i < 9; i++){
//		sum += accessed[i];
//	}
//
//	// if all are accessed
//	if (sum == 9){
//		//return success
//		return 1;
//	}
//
//	return -1;
//
//	pthread_exit(NULL);
//}
//
//struct position{
//	int row;
//	int col;
//};
//
//
//int validSudoku(int puzzle[][]){
//
//	int numThreads = 27;
//
//	pthread_t thread[numThreads];
//
//	int thNum = 0;
//	int row[9];
//
//	for(int i = 0; i < 9; i++){
//
//		for(int j = 0; j < 9; j++ ){
//			row[j] = puzzle[i][j];
//		}
//
//
//		pthread_create(&thread[i], NULL, checkRow, (void*)&row);
//		thNum++;
//
//	}
//
//
//	return 1;
//
//	]
//}
//
//
//
//int main(void) {
//
//	//if cannot read puzzle exit with error
//	if (readPuzzle() == -1){
//		return -1;
//	}
//
//	printPuzzle(puzzle);
//
//	printf("Solving!\n");
//
//
//	if (solve(puzzle,0,0) == 1){
//		printPuzzle(puzzle);
//	} else {
//		printf("No Solution Found!");
//	}
//
//
//
//	return 1;
//}
