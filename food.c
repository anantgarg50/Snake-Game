#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "./headers/food.h"
#include "./headers/board.h"

// create food for snake
Food *createFood(char board[][BOARD_Y])
{
  Food *food = (Food *)malloc(sizeof(Food));

  do
  {
    srand(time(NULL));
    food->x = rand() % (BOARD_X - 2) + 1;

    srand(time(NULL));
    food->y = rand() % (BOARD_Y - 2) + 1;
  } while (board[food->x][food->y] != ' ');

  food->display = '0';

  return food;
}

// mark food on the board
void markFood(Food *food, char board[][BOARD_Y])
{
  board[food->x][food->y] = food->display;
}
