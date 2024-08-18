#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FONT_BACKGROUND_WHITE "\e[47m"
#define FONT_DEFAULT_BACKGROUND_COLOR "\e[49m"

#define MAZE_WIDTH 16
#define MAZE_HEIGHT 16

typedef struct mazeCell {
  unsigned char visited; // To check if the algorithm visited this cell yet
  unsigned char topWall; // The bottom and right walls are not needed
  unsigned char leftWall;
} mazecell;

mazecell maze[MAZE_WIDTH][MAZE_HEIGHT];

void generateMaze(int currentX, int currentY) {
  int unvisitedNeighbourNum;
  int unvisitedNeighbours[4][2];
  maze[currentX][currentY].visited = 1;
  while (1) {
    unvisitedNeighbourNum = 0;
    if (currentX > 0 && maze[currentX - 1][currentY].visited != 1) {
      unvisitedNeighbours[unvisitedNeighbourNum][0] = currentX - 1;
      unvisitedNeighbours[unvisitedNeighbourNum][1] = currentY;
      unvisitedNeighbourNum++;
    }
    if (currentY > 0 && maze[currentX][currentY - 1].visited != 1) {
      unvisitedNeighbours[unvisitedNeighbourNum][0] = currentX;
      unvisitedNeighbours[unvisitedNeighbourNum][1] = currentY - 1;
      unvisitedNeighbourNum++;
    }
    if (currentX < (MAZE_WIDTH - 1) && maze[currentX + 1][currentY].visited != 1) {
      unvisitedNeighbours[unvisitedNeighbourNum][0] = currentX + 1;
      unvisitedNeighbours[unvisitedNeighbourNum][1] = currentY;
      unvisitedNeighbourNum++;
    }
    if (currentY < (MAZE_HEIGHT - 1) && maze[currentX][currentY + 1].visited != 1) {
      unvisitedNeighbours[unvisitedNeighbourNum][0] = currentX;
      unvisitedNeighbours[unvisitedNeighbourNum][1] = currentY + 1;
      unvisitedNeighbourNum++;
    }
    if (unvisitedNeighbourNum == 0) {
      return;
    }
    int nextNeighbourIndex = rand() % unvisitedNeighbourNum;
    if (currentX > unvisitedNeighbours[nextNeighbourIndex][0]) {
      maze[currentX][currentY].leftWall = 0;
    } else if (currentX < unvisitedNeighbours[nextNeighbourIndex][0]) {
      maze[unvisitedNeighbours[nextNeighbourIndex][0]][unvisitedNeighbours[nextNeighbourIndex][1]].leftWall = 0;
    } else if (currentY > unvisitedNeighbours[nextNeighbourIndex][1]) {
      maze[currentX][currentY].topWall = 0;
    } else if (currentY < unvisitedNeighbours[nextNeighbourIndex][1]) {
      maze[unvisitedNeighbours[nextNeighbourIndex][0]][unvisitedNeighbours[nextNeighbourIndex][1]].topWall = 0;
    }
    generateMaze(unvisitedNeighbours[nextNeighbourIndex][0], unvisitedNeighbours[nextNeighbourIndex][1]);
  }
}

int main() {
  // Initialize the rand() function 
  srand(time(NULL));

  // Initialize the maze cells
  for (int x = 0; x < MAZE_WIDTH; x++) {
    for (int y = 0; y < MAZE_HEIGHT; y++) {
      maze[x][y].visited = 0;
      maze[x][y].topWall = 1;
      maze[x][y].leftWall = 1;
    }
  }

  // Generate the maze
  generateMaze(0, 0);
  maze[0][0].leftWall = 0; // Create an entrance to the maze

  // Render the maze onto the screen
  for (int y = 0; y < MAZE_HEIGHT; y++) {
    for (int x = 0; x < MAZE_WIDTH; x++) {
      if (maze[x][y].topWall) {
        printf("%s    %s", FONT_BACKGROUND_WHITE, FONT_DEFAULT_BACKGROUND_COLOR);
      } else {
        printf("%s  %s  ", FONT_BACKGROUND_WHITE, FONT_DEFAULT_BACKGROUND_COLOR);
      }
    }
    printf("%s  %s\n", FONT_BACKGROUND_WHITE, FONT_DEFAULT_BACKGROUND_COLOR);
    for (int x = 0; x < MAZE_WIDTH; x++) {
      if (maze[x][y].leftWall) {
        printf("%s  %s  ", FONT_BACKGROUND_WHITE, FONT_DEFAULT_BACKGROUND_COLOR);
      } else {
        printf("    ");
      }
    }
    if (y == (MAZE_HEIGHT - 1)) {
      printf("\n"); // Create an exit to the maze
    } else {
      printf("%s  %s\n", FONT_BACKGROUND_WHITE, FONT_DEFAULT_BACKGROUND_COLOR);
    }
  }
  printf("%s", FONT_BACKGROUND_WHITE);
  for (int bottomLine = 0; bottomLine < MAZE_WIDTH; bottomLine++) {
    printf("    "); // Four spaces coloured white
  }
  printf("  %s\n", FONT_DEFAULT_BACKGROUND_COLOR);
}
