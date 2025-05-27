#include "player.h"

// Define the number of directions (north,south,east and west) and the number of rotations to the right
#define DIRECTION_NUMBER 4
#define RIGHT_ROTATION_NUMBER 1

// Use the cout object from the std namespace
using std::cout;

// Define a default constructor for the Position class
Position::Position()
{
  this->x = 0;
  this->y = 0;
}

// Define a constructor that takes two integers for the Position class and stores them in x and y
Position::Position(int x, int y)
{
  this->x = x;
  this->y = y;
}

// Define a default constructor for the Player class
Player::Player()
{
  this->direction = NORTH;
  this->position = Position(0, 0);
  this->moves = 0;
}

// Initialise the player with a starting position and direction
void Player::initialisePlayer(Position *position, Direction direction)
{
  this->direction = direction;
  this->position = *position;
  this->moves = 0;
}

// Turn the player's direction either right or left based on turnDirection
void Player::turnDirection(TurnDirection turnDirection)
{

  // Calculate the number of rotations to the left, given the number of rotations to the right
  int rotate_right = RIGHT_ROTATION_NUMBER;
  int direction_number = DIRECTION_NUMBER;
  int rotate_left = direction_number - rotate_right;

  // Determine whether to rotate left or right, based on the given turn direction
  int left_or_right = (turnDirection == TURN_RIGHT) ? rotate_right : rotate_left;

  // Calculate the new direction for the player, after the turn
  this->direction = static_cast<Direction>((this->direction + left_or_right) % direction_number);
}

// Get the next position that the player will move to, based on their current position and direction
Position Player::getNextForwardPosition()
{
  // Perform checks and update x and y according to the input direction
  Position nextPosition = this->position;
  if (this->direction == NORTH)
  {
    nextPosition.x--;
  }
  else if (this->direction == SOUTH)
  {
    nextPosition.x++;
  }
  else if (this->direction == EAST)
  {
    nextPosition.y++;
  }
  else if (this->direction == WEST)
  {
    nextPosition.y--;
  }
  return nextPosition;
}

// Update the player's current position
void Player::updatePosition(Position position)
{
  this->position = position;
  // increment number of moves by 1 after each successful move
  this->moves++;
}

// Display an arrow indicating the player's current direction
void Player::displayDirection()
{
  if (this->direction == NORTH)
  {
    cout << (DIRECTION_ARROW_OUTPUT_NORTH);
  }
  else if (this->direction == SOUTH)
  {
    cout << (DIRECTION_ARROW_OUTPUT_SOUTH);
  }
  else if (this->direction == EAST)
  {
    cout << (DIRECTION_ARROW_OUTPUT_EAST);
  }
  else if (this->direction == WEST)
  {
    cout << (DIRECTION_ARROW_OUTPUT_WEST);
  }
}
