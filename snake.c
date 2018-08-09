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

void recreateOldSnake(Snake **head, int x, int y, char display)
{
  Snake *temp = (Snake *)malloc(sizeof(Snake));
  temp->x = x;
  temp->y = y;
  temp->display = display;
  temp->next = NULL;

  Snake *tempHead = *head;
  if (*head)
  {
    while (tempHead->next)
    {
      tempHead = tempHead->next;
    }
    tempHead->next = temp;
  }
  else
  {
    *head = temp;
  }
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

bool checkSnakeBite(Snake *head, char board[][BOARD_Y])
{
  if (board[head->x][head->y] == '#' || board[head->x][head->y] == 'Y')
  {
    return true;
  }

  return false;
}

void growSnake(Snake **head)
{
  Snake *newHead = (Snake *)malloc(sizeof(Snake));

  newHead->display = 'A';
  newHead->next = *head;

  if ((*head)->x + 1 == (*head)->next->x)
  {
    newHead->x = (*head)->x - 1;
    newHead->y = (*head)->y;
  }
  else if ((*head)->x - 1 == (*head)->next->x)
  {
    newHead->x = (*head)->x + 1;
    newHead->y = (*head)->y;
  }
  else if ((*head)->y + 1 == (*head)->next->y)
  {
    newHead->x = (*head)->x;
    newHead->y = (*head)->y - 1;
  }
  else if ((*head)->y - 1 == (*head)->next->y)
  {
    newHead->x = (*head)->x;
    newHead->y = (*head)->y + 1;
  }

  (*head)->display = '#';

  *head = newHead;
}

void updateSnake(Snake *head, int prevHeadX, int prevHeadY)
{
  int tempX, tempY;
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

void moveSnakeUp(Snake *head)
{
  int prevHeadX = head->x, prevHeadY = head->y;

  if (head->x - 1 == 0)
  {
    head->x = BOARD_X - 2;
  }
  else
  {
    head->x--;
  }

  head = head->next;
  updateSnake(head, prevHeadX, prevHeadY);
}

void moveSnakeDown(Snake *head)
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
  updateSnake(head, prevHeadX, prevHeadY);
}

void moveSnakeLeft(Snake *head)
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
  updateSnake(head, prevHeadX, prevHeadY);
}

void moveSnakeRight(Snake *head)
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
  updateSnake(head, prevHeadX, prevHeadY);
}

void moveSnake(Snake *head, int move)
{
  switch (move)
  {
  case 1:
    moveSnakeUp(head);
    break;
  case 2:
    moveSnakeDown(head);
    break;
  case 3:
    moveSnakeRight(head);
    break;
  case 4:
    moveSnakeLeft(head);
    break;
  }
}