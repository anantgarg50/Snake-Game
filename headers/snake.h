#ifndef _SNAKE_H
#define _SNAKE_H

// Snake
struct Snake
{
  int x;                 // X-Coordinate on board
  int y;                 // Y-Coordinate on board
  unsigned char display; // display value on board
  struct Snake *next;    // Next node of Snake
};
typedef struct Snake Snake;

#endif