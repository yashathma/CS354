////////////////////////////////////////////////////////////////////////////////
// Main File:        my_magic_square.c
// This File:        my_magic_square.c
// Other Files:      Any File Created Using this File.
// Semester:         CS 354 Lecture 002      SPRING 2024
// Grade Group:      gg 4
// Instructor:       deppeler
// 
// Author:           Yash Athma
// Email:            athma@wisc.edu
// CS Login:         athma
//
/////////////////////////// SEARCH LOG //////////////////////////////// 
// Online sources: do not rely web searches to solve your problems, 
// but if you do search for help on a topic, include Query and URLs here.
// IF YOU FIND CODED SOLUTIONS, IT IS ACADEMIC MISCONDUCT TO USE THEM
//                               (even for "just for reference")
// Date:   Query:                      URL:
// --------------------------------------------------------------------- 
// 
// 
// 
// 
// 
// AI chats: save a transcript.  No need to submit, just have available 
// if asked.
/////////////////////////// COMMIT LOG  ////////////////////////////// 
//  Date and label your work sessions, include date and brief description
//  Date:   Commit Message: 
//  -------------------------------------------------------------------
//  Date: 2/18/2024
//  Commit Message:  Started and finsihed the code. Was getting seg fault errors
//                   for a few hours then realized I had the "i" and "j" variables
//                   flipped around in generateMagicSquare.
// 
// 
///////////////////////// OTHER SOURCES OF HELP ////////////////////////////// 
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
// Date:   Name (email):   Helped with: (brief description)
// ---------------------------------------------------------------------------
// 
//////////////////////////// 80 columns wide ///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2024, Deb Deppeler
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
	int size;           // dimension of the square
	int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Promps the user for the magic square's size, read it,
 * check if it's an odd number >= 3 (if not, display the required
 * error message and exit)
 *
 * return the valid number
 */
int getSize() {
    int size;
    printf("Enter magic square's size (odd integer >=3)\n");
    scanf("%d", &size);

    if(size < 3){
        printf("Magic square size must be >= 3.\n");
        exit(1);
    }

    if(size % 2 != 1){
        printf("Magic square size must be odd.\n");
        exit(1);
    }

	return size;   
} 

/* TODO:
 * Makes a magic square of size n,
 * and stores it in a MagicSquare (on the heap)
 *
 * It may use the Siamese magic square algorithm 
 * or alternate from assignment 
 * or another valid algorithm that produces a magic square.
 *
 * n - the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct.
 */
MagicSquare *generateMagicSquare(int n) {

    // Allocate memory for the MagicSquare structure

    int **m_square = malloc(n * sizeof(int *));
    if (m_square == NULL) {
        printf("Error: Memory allocation failed\n");
        exit(1);
    }

    //Filling in arrays
    for (int i = 0; i < n; i++) {
        *(m_square+i) = malloc(n * sizeof(int));
        if (*(m_square+i) == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            exit(1);
        }
    }


    // Initialize all elements of the magic square to 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(*(m_square+i)+j) = 0;
        }
    }

    //stops when we fill out all n^2 values. [1,n^2]
    int counter = 1;
    // How we keep track of the index in the 2d array i,j domain is [0,n-1]
    //starting i and j at the top row in the middle
    int i = 0;
    int j = ((n-1)/2);
    //preserved values of i and j if the top right of a value is taken
    int oldi;
    int oldj;
    while(counter<=(n*n)){

        //Check to see if top right is taken, if it is go down a row
        if(*(*((m_square) + i) + j)!=0){
            i = oldi+1;
            j = oldj;
            *(*(m_square+i)+j) = counter;
        } else{
            *(*(m_square+i)+j) = counter;
            oldi = i;
            oldj = j;
        }
        
        //Set that value
        *(*(m_square+i)+j) = counter;

        i--;
        j++;

        //Wrapping
        if(i<0){
            i=n-1;
        }
        if(j>=n){
            j=0;
        }

        counter++;
    }

    //Assigning this magic square to the struct and reutrning it
    MagicSquare *ms = malloc(sizeof(MagicSquare));
    (ms->size) = n;
    (ms -> magic_square) = m_square;

	return ms;    
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the magic square values to the file
 * in the specified format.
 *
 * magic_square - the magic square to write to a file
 * filename - the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s\n", filename);
        exit(1); // Exit the program with error code 1
    }
    int size = magic_square->size;
    // Write magic square size to the file
    fprintf(file, "%d\n", size);

    // Write magic square values to the file
    for (int i = 0; i < magic_square->size; i++) {
        for (int j = 0; j < magic_square->size; j++) {
            int value = *(*(magic_square->magic_square + i) + j);
            fprintf(file, "%d", value);
            if (j < size - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    if (fclose(file) == EOF) {
        fprintf(stderr, "Error closing file\n");
        exit(1);
    }

}


/* TODO:
 * Generates a magic square of the user specified size and
 * outputs the square to the output filename.
 * 
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings [program name, filename]
 */
int main(int argc, char **argv) {
	// TODO: Check input arguments to get output filename
    if(argc != 2){
        printf("Usage: ./my_magic_square <output_filename>\n");
        exit(1);
    }
    //file name of input
    char *fn = *(argv+1);
	// TODO: Get magic square's size from user
    int size = getSize();

	// TODO: Generate the magic square by correctly interpreting 
	//       the algorithm(s) in the write-up or by writing or your own.  
	//       You must confirm that your program produces a 
	//       Magic Sqare as described in the linked Wikipedia page.
    MagicSquare *ms = generateMagicSquare(size);
    





	// TODO: Output the magic square
    fileOutputMagicSquare(ms, fn);

    //Free Memory

    for (int i = 0; i < (ms->size); i++) {
        free(*(ms->magic_square+i));
    }
    // Free memory for the array of pointers
    free(ms->magic_square);
    // Free memory for the MagicSquare structure
    free(ms);


	return 0;
} 

// Spring 2024

