//DSA
#include <stdio.h>

#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define ROWS 5
#define COLS 5

// Function to print the grid
void printGrid(int grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%2d  ", grid[i][j]);
        }
        printf("\n");
    }
}

// Function to check if a cell is valid
bool isValid(int row, int col) {
    return (row >= 0) && (row < ROWS) && (col >= 0) && (col < COLS);
}

// Dijkstra's algorithm to find the shortest path
void dijkstra(int grid[ROWS][COLS], int startX, int startY, int goalX, int goalY) {
    int dist[ROWS][COLS];
    bool visited[ROWS][COLS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            dist[i][j] = INT_MAX;
            visited[i][j] = false;
        }
    }

    dist[startX][startY] = 0;

    for (int count = 0; count < ROWS * COLS - 1; count++) {
        int minDist = INT_MAX;
        int minRow = -1;
        int minCol = -1;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (!visited[i][j] && dist[i][j] < minDist) {
                    minDist = dist[i][j];
                    minRow = i;
                    minCol = j;
                }
            }
        }

        if (minRow == -1 || minCol == -1) {
            break; // No valid path
        }

        visited[minRow][minCol] = true;

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        for (int k = 0; k < 4; k++) {
            int newRow = minRow + dr[k];
            int newCol = minCol + dc[k];

            if (isValid(newRow, newCol) && !visited[newRow][newCol] &&
                grid[newRow][newCol] && dist[minRow][minCol] + grid[newRow][newCol] < dist[newRow][newCol]) {
                dist[newRow][newCol] = dist[minRow][minCol] + grid[newRow][newCol];
            }
        }
    }

    if (dist[goalX][goalY] == INT_MAX) {
        printf("No valid path from (%d, %d) to (%d, %d)\n", startX, startY, goalX, goalY);
    } else {
        printf("Shortest path from (%d, %d) to (%d, %d) has a length of %d\n", startX, startY, goalX, goalY, dist[goalX][goalY]);
    }
}

int main() {
    int grid[ROWS][COLS] = {
        {1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 1, 1, 1, 1}
    };

    int startX, startY, goalX, goalY;
    char input[20];

    printf("Grid:\n");
    printGrid(grid);

    // Get the start point (row col)
    while (1) {
        printf("Enter the start point (row col): ");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d%d", &startX, &startY) == 2 && isValid(startX, startY)) {
            break;
        } else {
            printf("Invalid input. Please enter valid coordinates.\n");
        }
    }

    // Get the goal point (row col)
    while (1) {
        printf("Enter the goal point (row col): ");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d%d", &goalX, &goalY) == 2 && isValid(goalX, goalY)) {
            break;
        } else {
            printf("Invalid input. Please enter valid coordinates.\n");
        }
    }

    dijkstra(grid, startX, startY, goalX, goalY);

    return 0;
}
