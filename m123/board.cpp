// This is the header file board.h, which includes the declarations of the class Board and its methods.
#include "board.h"

// Use standard namespace for various input/output objects
using std::cout;
using std::endl;
using std::vector;

// These two constants are defined to represent two different board layouts.
#define BOARD_ONE 1
#define BOARD_TWO 2

// This constant represents the first board layout.
const vector<vector<Cell>> Board::BOARD_1 = {
    {BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY},
    {EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY,
     EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED}};

// This constant represents the second board layout.
const vector<vector<Cell>> Board::BOARD_2 = {
    {BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
     EMPTY},
    {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    {EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}};

// This is the constructor of the class Board.
Board::Board()
{
  // A new board is created, consisting of a two-dimensional vector with dimensions DEFAULT_BOARD_DIMENSION x DEFAULT_BOARD_DIMENSION.
  board = new std::vector<std::vector<Cell>>(
      DEFAULT_BOARD_DIMENSION,
      std::vector<Cell>(DEFAULT_BOARD_DIMENSION, EMPTY));
}

// This is the destructor of the class Board.
Board::~Board()
{
  // The board is deleted and the pointer to the board is set to nullptr.
  delete board;
  board = nullptr;
}

// This method loads the specified board layout.
void Board::load(int board_Id)
{
  // If the specified board is the second one, then the board is loaded with the corresponding constant BOARD_2.
  if (board_Id == BOARD_TWO)
  {
    *board = BOARD_2;
  }
  // If the specified board is the first one, then the board is loaded with the corresponding constant BOARD_1.
  else if (board_Id == BOARD_ONE)
  {
    *board = BOARD_1;
  }
}

// Attempt to place the player on the board
bool Board::placePlayer(Position position)
{
  bool return_value = true;
  // Check if position is blocked or out of bounds
  if (position.y < 0 || position.y >= DEFAULT_BOARD_DIMENSION ||
      position.x < 0 || position.x >= DEFAULT_BOARD_DIMENSION ||
      (*board)[position.x][position.y] == BLOCKED)
  {
    return_value = false;
  }
  else
  {
    // Place player on board
    (*board)[position.x][position.y] = PLAYER;
  }
  return return_value;
}

// Move player forward or Display error message
PlayerMove Board::movePlayerForward(Player *player)
{
  // Get position of cell in front of player
  Position forward_position = player->getNextForwardPosition();
  // Check if position is out of bounds
  if (forward_position.x < 0 || forward_position.y >= DEFAULT_BOARD_DIMENSION || forward_position.y < 0 ||
      forward_position.x >= DEFAULT_BOARD_DIMENSION)
  {
    return OUTSIDE_BOUNDS;
  }
  // Check if cell in front of player is blocked
  else if ((*board)[forward_position.x][forward_position.y] == BLOCKED)
  {
    return CELL_BLOCKED;
  }
  else
  {
    // Move player to new position
    (*board)[player->position.x][player->position.y] = EMPTY;
    (*board)[forward_position.x][forward_position.y] = PLAYER;
    player->updatePosition(forward_position);
    return PLAYER_MOVED;
  }
}

// Display the board
void Board::display(Player *player)
{

  cout << LINE_OUTPUT
       << EMPTY_OUTPUT
       << LINE_OUTPUT;
  // Print column numbers
  for (int column = 0; column < DEFAULT_BOARD_DIMENSION; column++)
  {
    cout << column
         << LINE_OUTPUT;
  }
  cout << endl;

  for (int row = 0; row < DEFAULT_BOARD_DIMENSION; row++)
  {
    // Print row number
    cout << LINE_OUTPUT
         << row
         << LINE_OUTPUT;
    for (int column = 0; column < DEFAULT_BOARD_DIMENSION; column++)
    {

      if ((*board)[row][column] == BLOCKED)
      {
        // Print blocked cell
        cout << BLOCKED_OUTPUT
             << LINE_OUTPUT;
      }
      else if ((*board)[row][column] == EMPTY)
      {
        // Print empty cell
        cout << EMPTY_OUTPUT
             << LINE_OUTPUT;
      }
      else if ((*board)[row][column] == PLAYER)
      {
        // Print player and its direction
        player->displayDirection();
        cout << LINE_OUTPUT;
      }
    }
    cout << endl;
  }
}
