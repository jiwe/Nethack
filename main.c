#include<ncurses.h>
#include <stdlib.h>

typedef struct Player
{
  int xPosition;
  int yPosition;
  int health;
} Player;

int screenSetUp();
int mapSetUp();
Player * playerSetUp();
int handleInput(int input, Player * user);
int playerMove(int y, int x, Player * user);
int checkPostion(int newY, int newX, Player * user);

int main ()
{
  Player * user;
  int ch;
  screenSetUp();
  
  mapSetUp();
  
  user = playerSetUp();
  
  while ((ch = getch()) != 'q')
  {
    handleInput(ch, user);
  }
  endwin();
  
  return 0;
}

int screenSetUp()
{
  initscr();
  printw("Hello world!");
  noecho();
  refresh();
  
  return 0;
}

int mapSetUp()
{
  mvprintw(13, 13, "-----------");
  mvprintw(14, 13, "|..........|");
  mvprintw(15, 13, "|..........|");
  mvprintw(16, 13, "|..........|");
  mvprintw(17, 13, "|..........|");
  mvprintw(18, 13, "-----------");
   
  mvprintw(3, 40, "-----------");
  mvprintw(4, 40, "|..........|");
  mvprintw(5, 40, "|..........|");
  mvprintw(6, 40, "|..........|");
  mvprintw(7, 40, "|..........|");
  mvprintw(8, 40, "-----------");
  
  mvprintw(13, 40, "-----------");
  mvprintw(14, 40, "|..........|");
  mvprintw(15, 40, "|..........|");
  mvprintw(16, 40, "|..........|");
  mvprintw(17, 40, "|..........|");
  mvprintw(18, 40, "-----------");
}

Player * playerSetUp()
{
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));
  
  newPlayer->xPosition = 14;
  newPlayer->yPosition = 14;
  newPlayer->health = 20;
  
  playerMove(14, 14, newPlayer);
  
  return newPlayer;
}

int handleInput(int input, Player * user)
{
  int newX, newY;

  switch (input)
  {
    case 'w':
    case 'W':
      newX = user->xPosition;
      newY = user->yPosition - 1;
      break;

    case 's':
    case 'S':
      newX = user->xPosition;
      newY = user->yPosition + 1;
      break;

    case 'a':
    case 'A':
      newX = user->xPosition - 1;
      newY = user->yPosition;
      break;

    case 'd':
    case 'D':
      newX = user->xPosition + 1;
      newY = user->yPosition;
      break;
    
    default:
      break;
  }
  
  checkPostion(newY, newX, user);
}

int playerMove(int y, int x, Player * user)
{
  mvprintw(user->yPosition, user->xPosition, ".");
  user->xPosition = x;
  user->yPosition = y;
  mvprintw(user->yPosition, user->xPosition, "@");
  move(user->yPosition, user->xPosition);
}

int checkPostion(int newY, int newX, Player * user)
{
  int space;
  switch (mvinch(newY, newX))
  {
    case '.':
      playerMove(newY, newX, user);
      break;
    default:
      move(user->yPosition, user->xPosition);
      break;
  }
}