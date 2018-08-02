#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE 52

// Snake
typedef struct {
  int x;      // X-Coordinate on board
  int y;      // Y-Coordinate on board
  char display;       // display value on board
} Snake;

// Food
typedef struct {
  int x;      // X-Coordinate on board
  int y;      // Y-Coordinate on board
  char display;       // display value on board
} Food;

// create food for snake
Food* createFood() {
  Food *food = (Food *)malloc(sizeof(Food));

  srand(time(NULL));
  food->x = rand() % BOARD_SIZE;

  srand(time(NULL));
  food->y = rand() % BOARD_SIZE;

  food->display = '0';
  
  return food;
}

// mark food on the board
void markFood(Food *food, char board[][BOARD_SIZE]) {
  board[food->x][food->y] = food->display;
}

// display board to the screen
void displayBoard(char board[][BOARD_SIZE]) {
  for(int i = 0; i < BOARD_SIZE; i++) {
    for(int j = 0; j < BOARD_SIZE; j++) {
      if((i == 0 || i == BOARD_SIZE - 1) && j != 0) {
        putc('-', stdout);
        if(i == 0 && j == BOARD_SIZE - 1) {
          putc('\n', stdout);
        }  
      } else if(j == 1 || j == BOARD_SIZE - 1) {
        putc('|', stdout);
        if(j == BOARD_SIZE - 1) {
          putc('\n', stdout);
        }
      } else {
        putc(board[i][j], stdout);
      }
    }
  }
  putc('\n', stdout);
}

int main(int argc, char const *argv[])
{
  Snake *head, *tail;
  Food *food;
  
  char board[BOARD_SIZE][BOARD_SIZE];
  memset(board, ' ', sizeof(board[0][0]) * BOARD_SIZE * BOARD_SIZE);

  food = createFood();
  markFood(food, board);

  displayBoard(board);
  
  return 0;
}
