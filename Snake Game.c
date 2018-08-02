#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define BOARD_SIZE 12       //define board size here


// Snake
struct Snake{
  int x;      // X-Coordinate on board
  int y;      // Y-Coordinate on board
  unsigned char display;       // display value on board
  struct Snake *next;        // Next node of Snake
};
typedef struct Snake Snake;


// Food
struct Food{
  int x;      // X-Coordinate on board
  int y;      // Y-Coordinate on board
  char display;       // display value on board
};
typedef struct Food Food;


// create initial snake (just head and tail)
void createSnake(Snake **head, Snake **tail) {
  *head = (Snake *)malloc(sizeof(Snake));
  (*head)->x = (BOARD_SIZE - 2) / 2;
  (*head)->y = (BOARD_SIZE - 2) / 2;
  (*head)->display = 'A';
  
  *tail = (Snake *)malloc(sizeof(Snake));
  (*tail)->x = (*head)->x + 1;
  (*tail)->y = (*head)->y;
  (*tail)->display = 'Y';
  (*tail)->next = NULL;

  (*head)->next = *tail;
}


// mark snake on board
void putSnakeOnBoard(Snake *head, char board[][BOARD_SIZE]) {
  while(head) {
    board[head->x][head->y] = head->display;
    head = head->next;
  }
}


// create food for snake
Food* createFood(Snake *head) {
  Food *food = (Food *)malloc(sizeof(Food));
  
  while(head) {
    do {
      srand(time(NULL));
      food->x = rand() % (BOARD_SIZE - 2) + 1;

      srand(time(NULL));
      food->y = rand() % (BOARD_SIZE - 2) + 1;
    } while(head->x == food->x || head->y == food->y);
    
    head = head->next;
  }

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
      if((i == 0 || i == BOARD_SIZE - 1)) {
        putc('-', stdout);
        if(i == 0 && j == BOARD_SIZE - 1) {
          putc('\n', stdout);
        }  
      } else if(j == 0 || j == BOARD_SIZE - 1) {
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
  Snake *snakeHead = NULL, *snakeTail = NULL;
  Food *food;
  
  char board[BOARD_SIZE][BOARD_SIZE];
  memset(board, ' ', sizeof(board[0][0]) * BOARD_SIZE * BOARD_SIZE);

  createSnake(&snakeHead, &snakeTail);
  putSnakeOnBoard(snakeHead, board);

  food = createFood(snakeHead);
  markFood(food, board);

  displayBoard(board);
  
  return 0;
}
