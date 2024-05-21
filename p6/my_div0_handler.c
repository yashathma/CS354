////////////////////////////////////////////////////////////////////////////////
// Main File:        my_div0_handler.c
// This File:        my_div0_handler.c
// Other Files:      none dependent
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
// AI chats: save a transcript.  No need to submit, just have available 
// if asked.
/////////////////////////// COMMIT LOG  ////////////////////////////// 
//  Date and label your work sessions, include date and brief description
//  Date: May1st, 2024  Commit Message: Started and finished p6. That 
//                                      includes this file.
//  -------------------------------------------------------------------
// 
///////////////////////// OTHER SOURCES OF HELP ////////////////////////////// 
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
// Date:   Name (email):   Helped with: (brief description)
// ---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int successful_divisions = 0; // Global variable to count successful division operations

/* Handles the SIGFPE signal which is raised on arithmetic errors such as divide by zero.
 * This handler prints an error message, reports the number of successful divisions,
 * and then exits the program gracefully.
 *
 * Pre-conditions: SIGFPE is raised either by an arithmetic error or manually.
 * sig: The signal number (should be SIGFPE).
 * retval: None, as it is a void function and calls exit().
 */
void handle_sigfpe(int sig) {
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %d\n", successful_divisions);
    printf("The program will be terminated.\n");
    exit(0);
}

/* Handles the SIGINT signal, typically triggered by Ctrl+C. This handler prints the total
 * number of successful division operations completed before the interruption and exits the program.
 *
 * Pre-conditions: SIGINT is usually sent when the user presses Ctrl+C at the terminal.
 * sig: The signal number (should be SIGINT).
 * retval: None, as it is a void function and calls exit().
 */
void handle_sigint(int sig) {
    printf("\nTotal number of operations completed successfully: %d\n", successful_divisions);
    printf("The program will be terminated.\n");
    exit(0);
}

/* The main function initializes signal handlers for SIGFPE and SIGINT, then enters an infinite loop
 * to prompt the user for two integers and perform division with them. It handles divide by zero
 * by raising SIGFPE. The loop continues until an interruption (SIGINT) or an EOF on input.
 *
 * Pre-conditions: None.
 * retval: Returns 0 upon termination via SIGINT handler or if an EOF occurs on input.
 */
int main() {
    char input[100];
    int int1, int2;
    struct sigaction sa;

    // Setup SIGFPE handler
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigfpe;
    sigaction(SIGFPE, &sa, NULL);

    // Setup SIGINT handler
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigint;
    sigaction(SIGINT, &sa, NULL);

    // Main loop to handle user input and perform division
    while (1) {
        printf("Enter first integer: ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        int1 = atoi(input);

        printf("Enter second integer: ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        int2 = atoi(input);

        if (int2 == 0) {
            raise(SIGFPE); // Manually raise SIGFPE if division by zero is attempted
        } else {
            printf("%d / %d is %d with a remainder of %d\n", int1, int2, int1 / int2, int1 % int2);
            successful_divisions++;
        }
    }

    return 0;
}