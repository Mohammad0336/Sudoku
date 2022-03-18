/*
 ============================================================================
 Name        : L3Suduko.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

//global variables
int puzzle[9][9];
pthread_mutex_t mutex1;
int c1 = 0;
int c2 = 0;

struct position{
	int row;
	int col;
};

// start of imported code https://codereview.stackexchange.com/questions/37430/sudoku-solver-in-c
int isAvailable(int puzzle[][9], int row, int col, int num)
{
    int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;

    for(int i=0; i<9; ++i)
    {
        if (puzzle[row][i] == num) return 0;
        if (puzzle[i][col] == num) return 0;
        if (puzzle[rowStart + (i%3)][colStart + (i/3)] == num) return 0;
    }
    return 1;
}

int fillSudoku(int puzzle[][9], int row, int col)
{
    int i;
    if(row<9 && col<9)
    {
        if(puzzle[row][col] != 0)
        {
            if((col+1)<9) return fillSudoku(puzzle, row, col+1);
            else if((row+1)<9) return fillSudoku(puzzle, row+1, 0);
            else return 1;
        }
        else
        {
            for(i=0; i<9; ++i)
            {
                if(isAvailable(puzzle, row, col, i+1))
                {
                    puzzle[row][col] = i+1;
                    if((col+1)<9)
                    {
                        if(fillSudoku(puzzle, row, col +1)) return 1;
                        else puzzle[row][col] = 0;
                    }
                    else if((row+1)<9)
                    {
                        if(fillSudoku(puzzle, row+1, 0)) return 1;
                        else puzzle[row][col] = 0;
                    }
                    else return 1;
                }
            }
        }
        return 0;
    }
    else return 1;
}
// end of imported code

// function to read puzzle into array
int readPuzzle(void){
    FILE *myFile;

    myFile = fopen("src/puzzle.txt", "r"); // read file puzzle.txt

    if (!myFile){ // check if file is not attainable
        printf("Error Opening File\n");
        return -1;
    }

    else {

        for (int i = 0; i < 9; i++){ // parsing file into array

            for (int j = 0; j < 9; j++){

                fscanf(myFile, "%1d", &puzzle[i][j]);
            }
        }


        printf("Puzzle was parsed!\n\n");
        fclose(myFile);
    }

    return 1;


}

// function to write answer to answer.txt
int writePuzzle(void){
	FILE *f = fopen("src/answer.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	int counter = 0;

	for (int i = 0; i < 9; i++){ // parsing file into array
		for (int j = 0; j < 9; j++){
			if(counter%9 == 0 && counter != 0){
				fprintf(f, "\n");
			}
			fprintf(f, " %d", puzzle[i][j]);
			counter++;

		}
	}

	fclose(f);

	return 1;
}

// print puzzle
void printPuzzle(int puzzle[9][9]){

    for (int i = 0; i < 9; i++){ // print read array
        for (int j = 0; j < 9; j++){
            printf("%1d ", puzzle[i][j]);
        }
    }
}

// function to verify rows contain integers 1-9
void *check_rows(void *param){

	int r = 0;

	while(r < 9){
		for(int i = 1; i < 10; i++){
			for(int j = 0; j < 9; j++){
				if(i == puzzle[r][j]){
					c1++;
				}
			}
		}
		r++;
	}
	printf("%d", c1);
	pthread_exit(0);
}

// function to verify cols contain integers 1-9
void *check_cols(void *param){

	int c = 0;

	while(c < 9){
		for(int i = 1; i < 10; i++){
			for(int j = 0; j < 9; j++){
				if(i == puzzle[j][c]){
					c2++;
				}
			}
		}
		c++;
	}
	printf("%d", c2);
	pthread_exit(0);
	wait(1);
}

void checkCube(void){

	int cube = 0;
	int points = 0;

		while(cube < 3){
			for(int i = 1; i < 10; i++){
				for(int j = 0; j < 3; j++){
					if(i == puzzle[j][cube]){
						points++;
					}
				}
			}
			cube++;
		}
		printf("%d", points);
}

int main(void) {

	pthread_t thread1;
	pthread_t thread2;
	pthread_t threadx[9];

//	pthread_mutex_init[&mutex1, NULL];

    // if cannot read puzzle exit with error
    if (readPuzzle() == -1){
        return -1;
    }

    // printPuzzle(puzzle);
    if(fillSudoku(puzzle, 0, 0))
        {
            for(int i=1; i<10; ++i)
            {
                for(int j=1; j<10; ++j) printf(" %d", puzzle[i-1][j-1]);
                printf("\n");
            }
        }
        else printf("\n\nNO SOLUTION\n\n");

    //writePuzzle();


//    pthread_create(&thread1, NULL, check_rows, NULL);
//    pthread_create(&thread2, NULL, check_cols, NULL);
//
//
//    pthread_join(&thread1, NULL);
//    pthread_exit(&thread1);

    checkCube();

//    pthread_join(&thread2, NULL);
//    pthread_exit(&thread2);


//	for(int i = 0; i < 9; i++){
//		pthread_create(&threadx[i], NULL, check_rows, NULL);
//	}
//
//	for(int i = 0; i < 9; i++){
//		pthread_join(threadx[i], NULL);
//	}

    return 1;
}
