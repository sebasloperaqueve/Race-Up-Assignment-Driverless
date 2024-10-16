#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct {
    int row;
    int col;
} Point;

typedef struct {
    Point point;
    char *path;
} QueueNode;

typedef struct {
    QueueNode nodes[MAX_ROWS * MAX_COLS];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

int isEmpty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, QueueNode node) {
    q->nodes[q->rear++] = node;
}

QueueNode dequeue(Queue *q) {
    return q->nodes[q->front++];
}

int isValid(int rows, int cols, int visited[MAX_ROWS][MAX_COLS], char maze[MAX_ROWS][MAX_COLS], Point p) {
    return (p.row >= 0 && p.row < rows && p.col >= 0 && p.col < cols && 
            !visited[p.row][p.col] && maze[p.row][p.col] != '#');
}

void solveMaze(char maze[MAX_ROWS][MAX_COLS], int rows, int cols) {
    Point start, end;
    int visited[MAX_ROWS][MAX_COLS] = {0};

    // Find the starting point and the end point in the maze
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (maze[r][c] == 'S') {
                start = (Point){r, c};
            } else if (maze[r][c] == 'E') {
                end = (Point){r, c};
            }
        }
    }

    // Directions for moving (up, down, left, right)
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    char *moves[4] = {"UP", "DOWN", "LEFT", "RIGHT"};

    // BFS Initialization
    Queue queue;
    initQueue(&queue);

    QueueNode startNode = {start, ""};
    enqueue(&queue, startNode);
    visited[start.row][start.col] = 1;

    while (!isEmpty(&queue)) {
        QueueNode currentNode = dequeue(&queue);

        // Check if we've reached the end
        if (currentNode.point.row == end.row && currentNode.point.col == end.col) {
            printf("Solution: %s\n", currentNode.path);
            return;
        }

        // Explore neighbors (up, down, left, right)
        for (int i = 0; i < 4; i++) {
            Point neighbor = {currentNode.point.row + directions[i][0], currentNode.point.col + directions[i][1]};
            if (isValid(rows, cols, visited, maze, neighbor)) {
                visited[neighbor.row][neighbor.col] = 1;

                // Create the new path
                char newPath[200];
                snprintf(newPath, sizeof(newPath), "%s%s%s", currentNode.path, (currentNode.path[0] ? "," : ""), moves[i]);

                // Enqueue the neighbor
                QueueNode neighborNode = {neighbor, strdup(newPath)};
                enqueue(&queue, neighborNode);
            }
        }
    }

    printf("No solution found.\n");
}

int main(int argc, char *argv[]) {
    char maze[MAX_ROWS][MAX_COLS];
    int rows = 0;

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file provided as the first argument
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the maze from the file line by line
    char line[MAX_COLS];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Strip newline character if present
        line[strcspn(line, "\n")] = 0;
        strncpy(maze[rows], line, MAX_COLS - 1);
        maze[rows][MAX_COLS - 1] = '\0';  // Ensure the string is null-terminated
        rows++;
    }

    fclose(file);

    int cols = strlen(maze[0]);  // Assume all rows have the same number of columns

    // Solve the maze
    solveMaze(maze, rows, cols);

    return 0;
}
