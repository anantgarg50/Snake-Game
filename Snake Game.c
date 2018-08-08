#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "snake.c"
#include "food.c"
#include "board.c"

void rulesAndControls();
void startGame();
void startNew();
void loadLastSaved();
void mainGame(Snake *, Food *, bool, char[][BOARD_Y]);
void pauseGame();
int inputMove();

int main(int argc, char const *argv[])
{
  rulesAndControls();
  startGame();

  return 0;
}

// Rules
void rulesAndControls()
{
  puts("<----------------Rules---------------->");
  puts("Beware! Don't let the Snake bite itself.");
  putchar('\n');

  puts("<----------------Controls---------------->");
  puts("Press 'Up Arrow' for UP");
  puts("Press 'Down Arrow' for DOWN");
  puts("Press 'Left Arrow' for LEFT");
  puts("Press 'Right Arrow' for RIGHT");
  puts("Press 'P' to Pause the Game");
  putchar('\n');
}

// start condition
void startGame()
{
  char input;
  puts(":::Press 'ENTER' to start or 'Esc' to Quit:::");
  printf("-->");

  while ((input = fgetc(stdin)) != '\n' && input != '\033')
  {
    while (getchar() != '\n')
      ;
    puts("Enter correct choice!");
    printf("-->");
  }

  if (input != '\n')
  {
    puts("You have exited the Snake-Game.");
    exit(0);
  }
  else
  {
    puts(":::Press 'N' to start new game or 'L' to load last saved game:::");
    printf("-->");

    while ((input = fgetc(stdin)) != 'N' && input != 'n' && input != 'L' && input != 'l')
    {
      while (getchar() != '\n')
        ;
      puts("Enter correct choice!");
      printf("-->");
    }

    while (getchar() != '\n')
      ;

    switch (input)
    {
    case 'N':
    case 'n':
      startNew();
      break;
    case 'L':
    case 'l':
      loadLastSaved();
      break;
    }
  }
}

void startNew()
{
  char board[BOARD_X][BOARD_Y];
  memset(board, ' ', sizeof(board[0][0]) * BOARD_X * BOARD_Y);

  Snake *snakeHead = createNewSnake();

  mainGame(snakeHead, NULL, true, board);
}

void loadLastSaved()
{
}

void mainGame(Snake *snakeHead, Food *food, bool foodEaten, char board[][BOARD_Y])
{
  bool gameOver = false;
  int test = 5;
  int i;
  do
  {
    putSnakeOnBoard(snakeHead, board);

    if (foodEaten)
    {
      food = createFood(board);
      foodEaten = false;
    }
    markFood(food, board);

    displayBoard(board);

    i = inputMove();
  } while (--test);

  system("clear");
  puts(":::Well Played! Game-Over:::");
}

void pauseGame()
{
  char input;

  while (getchar() != '\n')
    ;

  do
  {
    puts(":::Game Paused! Press 'ENTER' to continue:::");
    printf("-->");
    input = getchar();
    if (input != '\n')
    {
      while (getchar() != '\n')
        ;
    }
  } while (input != '\n');
}

int inputMove()
{
  char input;
  int move;

  if ((input = getchar()) == '\033')
  {
    getchar();
    switch ((input = getchar()))
    {
    case 'A':
      move = 1; // UP
      break;
    case 'B':
      move = 2; // DOWN
      break;
    case 'C':
      move = 3; // RIGHT
      break;
    case 'D':
      move = 4; // LEFT
      break;
    }
  }
  else if (input == 'P' || input == 'p')
  {
    pauseGame();
    return 0;
  }

  while (getchar() != '\n')
    ;

  return move;
}