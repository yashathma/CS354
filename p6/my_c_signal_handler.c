////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        my_c_signal_handler.c
// Other Files:      send_signal.c
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
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int alarm_seconds = 5; // Global variable to set alarm interval
int sigusr1_count = 0; // Global variable to count SIGUSR1 signals

/* Handles the SIGALRM signal. This function is invoked when an alarm signal is received.
 * It prints the current process ID and time, and resets the alarm.
 *
 * Pre-conditions: SIGALRM must be raised by the OS as scheduled.
 * sig: The signal number (should be SIGALRM).
 * retval: None, as it is a void function.
 */
void handle_alarm(int sig) {
    time_t now;
    time(&now);
    printf("PID: %d CURRENT TIME: %s", getpid(), ctime(&now));
    alarm(alarm_seconds); // Rearm the alarm
}

/* Handles the SIGUSR1 signal. This function increments the count of SIGUSR1 signals received
 * and prints a message each time it is called.
 *
 * Pre-conditions: SIGUSR1 must be sent to the process, usually from another process or internally.
 * sig: The signal number (should be SIGUSR1).
 * retval: None, as it is a void function.
 */
void handle_sigusr1(int sig) {
    sigusr1_count++;
    printf("SIGUSR1 handled and counted!\n");
}

/* Handles the SIGINT signal, typically triggered by Ctrl+C. Prints how many times
 * SIGUSR1 was received and then terminates the program.
 *
 * Pre-conditions: SIGINT must be sent to the process, usually from the terminal (Ctrl+C).
 * sig: The signal number (should be SIGINT).
 * retval: None, as it is a void function and calls exit().
 */
void handle_sigint(int sig) {
    printf("\nSIGINT handled.\nSIGUSR1 was handled %d times. Exiting now.\n", sigusr1_count);
    exit(0);
}

/* The main function sets up signal handlers for SIGALRM, SIGUSR1, and SIGINT and enters
 * an infinite loop that pauses waiting for signals. It configures and starts an alarm
 * to demonstrate periodic signal handling.
 *
 * Pre-conditions: None.
 * retval: Returns 0 on normal exit, 1 on error setting up signal handlers.
 */
int main() {
    struct sigaction sa;

    // Clear the sigaction structure
    memset(&sa, 0, sizeof(sa));

    // Setting up the handler for SIGALRM
    sa.sa_handler = handle_alarm;
    if (sigaction(SIGALRM, &sa, NULL) != 0) {
        perror("Failed to set SIGALRM handler");
        return 1;
    }
    if (alarm(alarm_seconds) != 0) {
        fprintf(stderr, "Alarm was already set.\n");
    }

    // Setting up the handler for SIGUSR1
    sa.sa_handler = handle_sigusr1;
    if (sigaction(SIGUSR1, &sa, NULL) != 0) {
        perror("Failed to set SIGUSR1 handler");
        return 1;
    }

    // Setting up the handler for SIGINT
    sa.sa_handler = handle_sigint;
    if (sigaction(SIGINT, &sa, NULL) != 0) {
        perror("Failed to set SIGINT handler");
        return 1;
    }

    printf("PID and time print every 5 seconds.\nType Ctrl-C to end the program.\n");

    while (1) {
        pause(); // Wait for the next signal
    }

    return 0;
}