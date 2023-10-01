#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAZE_WIDTH 50
#define MAZE_HEIGHT 50
#define CELL_SIZE 10

int maze[MAZE_WIDTH][MAZE_HEIGHT];

// directions for DFS
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

void generateMaze(int x, int y) {
  // mark the current cell as visited
  maze[x][y] = 1;

  // shuffle the directions
  int directions[4] = {0, 1, 2, 3};
  for (int i = 0; i < 4; i++) {
    int j = rand() % (4 - i) + i;
    int temp = directions[i];
    directions[i] = directions[j];
    directions[j] = temp;
  }

  // visit the neighboring cells in a random order
  for (int i = 0; i < 4; i++) {
    int newX = x + dx[directions[i]];
    int newY = y + dy[directions[i]];
    if (newX >= 0 && newX < MAZE_WIDTH && newY >= 0 && newY < MAZE_HEIGHT && !maze[newX][newY]) {
      generateMaze(newX, newY);
    }
  }
}

void drawMaze() {
  for (int i = 0; i < MAZE_WIDTH; i++) {
    for (int j = 0; j < MAZE_HEIGHT; j++) {
      if (maze[i][j]) {
        // draw a white cell for visited cells
        setcolor(WHITE);
      } else {
        // draw a black cell for walls
        setcolor(BLACK);
      }
      // draw the cell
      rectangle(i * CELL_SIZE, j * CELL_SIZE, (i + 1) * CELL_SIZE, (j + 1) * CELL_SIZE);
    }
  }
}

int main() {
  // seed the random number generator
  srand(time(NULL));

  // initialize the graphics window
  int gd = DETECT, gm;
  initgraph(&gd, &gm, "");

  // generate the maze
  generateMaze(0, 0);

  // draw the maze
  drawMaze();

  // wait for the user to close the window
  getch();
  closegraph();
  return 0;
}
