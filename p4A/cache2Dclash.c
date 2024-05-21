////////////////////////////////////////////////////////////////////////////////
// Author:           Yash Athma
// Grade Group:      gg 4
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#define ROWS 128
#define COLS 8
#define ITERATIONS 100
int arr2D[ROWS][COLS];

 int main(int argc, char **argv) {
    for(int iteration = 0; iteration < ITERATIONS; iteration++) {
        for(int row = 0; row < ROWS; row += 64) {
            for(int col = 0; col < COLS; col++) {
                arr2D[row][col] = iteration + row + col;
            }
        }
    }
    return 0;
}
