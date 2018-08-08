#include <stdio.h>
#include <malloc.h>
#include "./headers/snake.h"
#include "./headers/board.h"

// create initial snake (just head and tail)
Snake *createNewSnake()
{
  Snake *head = (Snake *)malloc(sizeof(Snake));
  Snake *body = (Snake *)malloc(sizeof(Snake));
  Snake *tail = (Snake *)malloc(sizeof(Snake));

  head->x = (BOARD_X - 2) / 2;
  head->y = (BOARD_Y - 2) / 2;
  head->display = 'A';

  head->next = body;

  body->x = head->x + 1;
  body->y = head->y;
  body->display = '#';
  body->next = tail;

  tail->x = body->x + 1;
  tail->y = body->y;
  tail->display = 'Y';
  tail->next = NULL;

  return head;
}

// mark snake on board
void putSnakeOnBoard(Snake *head, char board[][BOARD_Y])
{
  while (head)
  {
    board[head->x][head->y] = head->display;
    head = head->next;
  }
}

void checkSnakeBite(Snake *head, char board[][BOARD_Y])
{
}
void growSnake()
{
}

void moveSnakeUp(Snake *head, char board[][BOARD_Y])
{
  int prevHeadX = head->x, prevHeadY = head->y, tempX, tempY;

  if (head->x - 1 == 0)
  {
    head->x = BOARD_X - 2;
  }
  else
  {
    head->x--;
  }

  if (head->x)

    head = head->next;
  while (head)
  {
    tempX = head->x;
    tempY = head->y;
    head->x = prevHeadX;
    head->y = prevHeadY;
    prevHeadX = tempX;
    prevHeadY = tempY;
    head = head->next;
  }
}

void moveSnakeDown(Snake *head, char board[][BOARD_Y])
{
  int prevHeadX = head->x, prevHeadY = head->y, tempX, tempY;
  if (head->x + 1 == BOARD_X - 1)
  {
    head->x = 1;
  }
  else
  {
    head->x++;
  }
  head = head->next;
  while (head)
  {
    tempX = head->x;
    tempY = head->y;
    head->x = prevHeadX;
    head->y = prevHeadY;
    prevHeadX = tempX;
    prevHeadY = tempY;
    head = head->next;
  }
}

void moveSnakeLeft(Snake *head, char board[][BOARD_Y])
{
  int prevHeadX = head->x, prevHeadY = head->y, tempX, tempY;
  if (head->y - 1 == 0)
  {
    head->y = BOARD_Y - 2;
  }
  else
  {
    head->y--;
  }
  head = head->next;
  while (head)
  {
    tempX = head->x;
    tempY = head->y;
    head->x = prevHeadX;
    head->y = prevHeadY;
    prevHeadX = tempX;
    prevHeadY = tempY;
    head = head->next;
  }
}

void moveSnakeRight(Snake *head, char board[][BOARD_Y])
{
  int prevHeadX = head->x, prevHeadY = head->y, tempX, tempY;
  if (head->y + 1 == BOARD_Y - 1)
  {
    head->y = 1;
  }
  else
  {
    head->y++;
  }
  head = head->next;
  while (head)
  {
    tempX = head->x;
    tempY = head->y;
    head->x = prevHeadX;
    head->y = prevHeadY;
    prevHeadX = tempX;
    prevHeadY = tempY;
    head = head->next;
  }
}

void moveSnake(Snake **head, char board[][BOARD_Y])
{
}