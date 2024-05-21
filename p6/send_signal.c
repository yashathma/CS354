////////////////////////////////////////////////////////////////////////////////
// Main File:        send_signal.c
// This File:        send_signal.c
// Other Files:      my_c_signal_handler.c
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
#include <signal.h>
#include <stdlib.h>
#include <string.h>

/* Main function of send_signal.c that sends specific signals to a specified process.
 * It takes command-line arguments to determine the signal type and the target process ID.
 *
 * Pre-conditions: Must be executed with exactly two command-line arguments:
 * - The first argument should be "-i" for SIGINT or "-u" for SIGUSR1.
 * - The second argument should be the PID of the target process.
 * - The process executing this command must have the necessary permissions to send signals
 *   to the target process.
 *
 * param argc: The number of command-line arguments.
 * param argv: An array of strings representing the command-line arguments.
 * argv[1]: A string specifying the type of signal ("-i" for SIGINT, "-u" for SIGUSR1).
 * argv[2]: A string representing the process ID to which the signal will be sent.
 *
 * retval: Returns 0 on successful execution and sending of the signal.
 *         Returns 1 if there is an error in command-line arguments, signal type is invalid,
 *         or the signal could not be sent to the specified PID.
 */

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: send_signal <signal type> <pid>\n");
        return 1;
    }

    int pid = atoi(argv[2]);
    int sig = (strcmp(argv[1], "-i") == 0) ? SIGINT : (strcmp(argv[1], "-u") == 0) ? SIGUSR1 : 0;

    if (sig == 0) {
        printf("Invalid signal type. Use -i for SIGINT or -u for SIGUSR1\n");
        return 1;
    }

    if (kill(pid, sig) == -1) {
        perror("Failed to send signal");
        return 1;
    }

    return 0;
}