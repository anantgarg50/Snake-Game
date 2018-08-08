#include <stdio.h>
#include "./headers/board.h"

// display board to the screen
void displayBoard(char board[][BOARD_Y])
{
  //system("clear");
  puts("<----------------Snake-Game---------------->");

  for (int i = 0; i < BOARD_X; i++)
  {
    for (int j = 0; j < BOARD_Y; j++)
    {
      if ((i == 0 || i == BOARD_X - 1))
      {
        putc('-', stdout);
        if (i == 0 && j == BOARD_Y - 1)
        {
          putc('\n', stdout);
        }
      }
      else if (j == 0 || j == BOARD_Y - 1)
      {
        putc('|', stdout);
        if (j == BOARD_Y - 1)
        {
          putc('\n', stdout);
        }
      }
      else
      {
        putc(board[i][j], stdout);
      }
    }
  }
  putchar('\n');
  puts("<----------------Snake-Game---------------->");
}
