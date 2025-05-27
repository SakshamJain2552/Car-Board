// This is the header file board.h, which includes the declarations of the class Board and its methods.
#include "board.h"

// Use standard namespace for various input/output objects
using std::cout;
using std::endl;
using std::random_device;
using std::uniform_int_distribution;
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

void Board::generateboard(int dimension, float rand)
{
  this->boardSize = dimension;
  this->board = new vector<vector<Cell>>(
      dimension,
      vector<Cell>(dimension, EMPTY));

  int num_cells = dimension * dimension;
  int expected_blocks = static_cast<int>(num_cells * rand);

  // Generating random values
  random_device rd;
  uniform_int_distribution<int> distribute(0, num_cells - 1);

  // Add random BLOCKED cells
  int blocks_add = 0;
  while (blocks_add < expected_blocks)
  {
    int i = distribute(rd) / dimension;
    int j = distribute(rd) % dimension;
    if ((*this->board)[i][j] == EMPTY)
    {
      (*this->board)[i][j] = BLOCKED;
      blocks_add++;
    }
  }
}

bool Board::placePlayer(Position position)
{
  bool return_value = true;
  if (
      position.y < 0 || position.y >= boardSize ||
      position.x < 0 || position.x >= boardSize || (*board)[position.x][position.y] == BLOCKED)
  {
    return_value = false;
  }
  else
  {
    (*board)[position.x][position.y] = PLAYER;
  }
  return return_value;
}

PlayerMove Board::movePlayerForward(Player *player)
{
  Position forward_position = player->getNextForwardPosition();
  if (forward_position.x < 0 || forward_position.y >= boardSize || forward_position.y < 0 ||
      forward_position.x >= boardSize)
  {
    return OUTSIDE_BOUNDS;
  }
  else if ((*board)[forward_position.x][forward_position.y] == BLOCKED)
  {
    return CELL_BLOCKED;
  }
  else
  {
    (*board)[player->position.x][player->position.y] = EMPTY;
    (*board)[forward_position.x][forward_position.y] = PLAYER;
    player->updatePosition(forward_position);
    return PLAYER_MOVED;
  }
}

void Board::display(Player *player)
{

  cout << LINE_OUTPUT
       << EMPTY_OUTPUT
       << LINE_OUTPUT;
  for (int column = 0; column < boardSize; column++)
  {
    cout << column % 10
         << LINE_OUTPUT;
  }
  cout << endl;

  for (int row = 0; row < boardSize; row++)
  {
    cout << LINE_OUTPUT
         << row % 10
         << LINE_OUTPUT;
    for (int column = 0; column < boardSize; column++)
    {

      if ((*board)[row][column] == BLOCKED)
      {
        cout << BLOCKED_OUTPUT
             << LINE_OUTPUT;
      }
      else if ((*board)[row][column] == EMPTY)
      {
        cout << EMPTY_OUTPUT
             << LINE_OUTPUT;
      }
      else if ((*board)[row][column] == PLAYER)
      {
        player->displayDirection();
        cout << LINE_OUTPUT;
      }
    }
    cout << endl;
  }
}
