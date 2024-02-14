////////////////////////////////////////////////////////////////////////////////
// Main File:        check_board.c
// This File:        check_board.c
// Other Files:		 boardN.txt and boardNsolution.txt (Not Submitted)
// Semester:         CS 354 Lecture 002      SPRING 2024
// Grade Group:      gg 4
// Instructor:       deppeler
// 
// Author:           Yash Athma
// Email:            athma@wisc.edu
// CS Login:         athma

////////////////////////////////////////////////////////////////////////////////
// Fix compiler error
// Implement remaining functionality

///////////////////////////////////////////////////////////////////////////////
// Copyright 2021-24 Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get 
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
// 09/20/2021 Revised to free memory allocated in get_board_size function.
// 01/24/2022 Revised to use pointers for CLAs
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DELIM = ",";  // commas ',' are a common delimiter character for data strings

/* TODO: implement this function
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 * 
 * A valid row or column contains only blanks or the digits 1-size, 
 * with no duplicate digits, where size is the value 1 to 9.
 * 
 * Note: p2A requires only that each row and each column are valid.
 * 
 * board: heap allocated 2D array of integers 
 * size:  number of rows and columns in the board
 */

int valid_board(int **board, int size) {
    if (size > 9 || size < 1) {
        return 0;
    }

    //check rows
    for (int i = 0; i < size; i++) {
        //Used to check repeats in rows
        int *valsInRow = malloc((size + 1) * sizeof(int)); // Need an extra slot for counting zeros
        if (valsInRow == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        // Initialize checking array
        memset(valsInRow, 0, (size + 1) * sizeof(int));

        // Iterating over all values in the row
        for (int j = 0; j < size; j++) {
            int val = *(*(board + i) + j);
            if (val < 0 || val > size) {
                // Value is out of range
                free(valsInRow);
                return 0;
            } else if (val != 0 && *(valsInRow+val) == 1) {
                // Duplicate value found in the row
                free(valsInRow);
                return 0;
            }
            *(valsInRow+val) = 1; // Mark value as seen
        }
        free(valsInRow);
    }

    //check columns
    for (int i = 0; i < size; i++) {
        //Used to check repeats in columns
        int *valsInColumn = malloc((size + 1) * sizeof(int)); // Need an extra slot for counting zeros
        if (valsInColumn == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        // Initialize checking array
        memset(valsInColumn, 0, (size + 1) * sizeof(int));

        // Iterating over all values in the column
        for (int j = 0; j < size; j++) {
            int val = *(*(board + j) + i);
            if (val < 0 || val > size) {
                // Value is out of range
                free(valsInColumn);
                return 0;
            } else if (val != 0 && *(valsInColumn+val) == 1) {
                // Duplicate value found in the column
                free(valsInColumn);
                return 0;
            }
            *(valsInColumn+val) = 1; // Mark value as seen
        }
        free(valsInColumn);
    }

    //Didn't fail any tests
    return 1;
}

/* COMPLETED (DO NOT EDIT):       
 * Read the first line of file to get the size of that board.
 * 
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * POST-CONDITION: the integer whos address is passed in as size (int *) 
 * will now have the size (number of rows and cols) of the board being checked.
 */
void get_board_size(FILE *fptr, int *size) {      
	char *line = NULL;
	size_t len = 0;

	// 'man getline' to learn about <stdio.h> getline
	if ( getline(&line, &len, fptr) == -1 ) {
		printf("Error reading the input file.\n");
		free(line);
		exit(1);
	}

	char *size_chars = NULL;
	size_chars = strtok(line, DELIM);
	*size = atoi(size_chars);

	// free memory allocated for line 
	free(line);
	line = NULL;
}


/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 * It prints "invalid" (without quotes) if the input file is not valid.
 *
 * Usage: A single CLA that is the name of a file that contains board data.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 *
 * Returns 0 if able to correctly output valid or invalid.
 * Exit with a non-zero result if unable to open and read the file given.
 */
int main(int argc, char **argv) {
    // TODO: Check if number of command-line arguments is correct.
    if (argc != 2) {
        printf("Usage: %s <input_filename>\n", *(argv+0));
        exit(1);
    }

    // Open the file
    FILE *fp = fopen(*(argv+1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    // will store the board's size, number of rows and columns
    int size;

    // Call get_board_size to read first line of file as the board size.
    get_board_size(fp, &size);

    // Dynamically allocate a 2D array for given board size.
    // You must dynamically create a 1D array of pointers to other 1D arrays of ints
    int **board = malloc(size * sizeof(int *));
    if (board == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        (*(board+i)) = malloc(size * sizeof(int));
        if ((*(board+i)) == NULL) {
            printf("Memory allocation failed.\n");
            for (int j = 0; j < i; j++) {
                free(*(board+j));
            }
            free(board);
            fclose(fp);
            exit(1);
        }
    }

    // Read the remaining lines.
    // Tokenize each line and store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {
        // read the line
        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading line %i of the file.\n", i + 2);
            for (int j = 0; j <= i; j++) {
                free(*(board+j));
            }
            free(board);
            free(line);
            fclose(fp);
            exit(1);
        }

        token = strtok(line, DELIM);
        for (int j = 0; j < size; j++) {
            // initialize elements of your 2D array.
            *(*(board+i)+j) = atoi(token);
            token = strtok(NULL, DELIM);
        }
    }
    free(line);

    // Call valid_board and print the appropriate output depending on the function's return value.
    int isValid = valid_board(board, size);
    if (isValid == 1) {
        printf("valid\n");
    } else {
        printf("invalid\n");
    }

    // TODO: Free dynamically allocated memory.

    for (int i = 0; i < size; i++) {
        free(*(board+i));
    }
    free(board);

    // Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    }

    return 0;
}

