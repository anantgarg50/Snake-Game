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
void saveCurrentGame(Snake *, Food *);

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
  puts("Press 'S' to save the game and exit");
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

  Snake *snakeHead = createNewSnake();

  mainGame(snakeHead, NULL, true, board);
}

void loadLastSaved()
{
}

void mainGame(Snake *snakeHead, Food *food, bool foodEaten, char board[][BOARD_Y])
{
  bool gameOver = false;
  int move;
  do
  {
    memset(board, ' ', sizeof(board[0][0]) * BOARD_X * BOARD_Y);
    putSnakeOnBoard(snakeHead, board);

    if (foodEaten)
    {
      food = createFood(board);
      foodEaten = false;
    }
    markFood(food, board);

    displayBoard(board);

    move = inputMove();
    if (!move)
    {
      saveCurrentGame(snakeHead, food);
    }
    moveSnake(snakeHead, move);
    foodEaten = hasEatenFood(&snakeHead, food);
    gameOver = checkSnakeBite(snakeHead, board);
  } while (!gameOver);

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
    return -1;
  }
  else if (input == 'S' || input == 's')
  {
    return 0;
  }

  while (getchar() != '\n')
    ;

  return move;
}

void saveCurrentGame(Snake *head, Food *food)
{
  FILE *saveGame = fopen("./Saved Game/last_save.txt", "w");

  if (saveGame == NULL)
  {
    puts("There was a problem in saving current game...exiting!");
    exit(1);
  }

  fprintf(saveGame, "%c\n%d %d %c\n", 'f', food->x, food->y, food->display);

  fprintf(saveGame, "%c\n", 's');
  while (head)
  {
    fprintf(saveGame, "%d %d %c\n", head->x, head->y, head->display);
    head = head->next;
  }

  puts("Game saved successfully!");
  fclose(saveGame);

  exit(0);
}