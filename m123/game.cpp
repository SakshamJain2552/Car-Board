/*
In this implementation, I have used a while loop to allow the user to repeatedly choose between various menus. The loop terminates when the user chooses to quit. To prevent invalid inputs from crashing the program,
I have included input validation using cin.fail() and cin.clear() and other methods.
I have also used the STL vector class to store the game board and the players'
information. To make the game more user-friendly, I have added prompts and error messages to guide the user.

During the implementation, I encountered issues with the conversion of string inputs to float values, which I resolved by using the
stof function. I also had to carefully design the program flow to ensure that there were no infinite loops or logical errors.

One potential improvement to the design of the start-up code could be to use object-oriented programming to create classes
 for the game board and the players, which could make the code more organized and easier to maintain. Additionally, the code could be
 optimized by reducing the number of unnecessary variables and functions, and by using more efficient data structures and helper methods where appropriate.
*/

// include the game header file
#include "game.h"

// import standard library functions and objects
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

// define constants for board numbers
#define BOARD_ONE "1"
#define BOARD_TWO "2"

// Game constructor
Game::Game()
{
    // create a new Player and Board object
    player = new Player;
    board = new Board;
}

// Game destructor
Game::~Game()
{
    // delete the Player and Board objects and set their pointers to nullptr
    delete player;
    delete board;
    board = nullptr;
    player = nullptr;
}

// start method of the Game class
void Game::start()
{
    // print the available commands for the game
    cout << "You can use the following commands to play the game:"
         << endl
         << "load <g>"
         << endl
         << "     g: number of the game board to load"
         << endl
         << "init <x>,<y>,<direction>"
         << endl
         << "     x: horizontal position of the car on the board (between 0 & 9)"
         << endl
         << "     y: vertical position of the car on the board (between 0 & 9)"
         << endl
         << "     direction: direction of the car\'s movement (north, east, south, "
            "west)"
         << endl
         << "forward (or f)"
         << endl
         << "turn_left (or l)"
         << endl
         << "turn_right (or R)"
         << endl
         << "quit"
         << endl
         << endl;

    cin.ignore();

    // display the board and the player's initial position
    (*board).display(player);
    cout << endl;

    // load the game board then initialize the player's position and finally play the game
    if (loadBoard())
    {
        if (initializePlayer())
        {
            play();
            std::cout << "\nTotal Player Moves: " << player->moves << std::endl;
        }
    }
}

/*

* This function loads a game board, based on user input, and displays it.

* @return bool True if the board was successfully loaded, false if the user chooses to quit the game.

*/
bool Game::loadBoard()
{
    // initialise variables for menu loop
    string choice = "";
    bool load_board = false;
    bool do_quit = false;
    bool return_value = false;

    // While the user has not chosen to quit the game
    while (!do_quit && !cin.eof())
    {
        // set necessary boolean values each time loop is called
        load_board = false;
        do_quit = false;
        return_value = true;
        string user_command = "";
        string board_number = "";

        // Prompt the user with available commands
        cout << "At this stage of the program, only two commands are acceptable:"
             << endl
             << "load <g>"
             << endl
             << "quit"
             << endl
             << endl;

        // Read user input
        choice = Helper::readInput();

        // if choice is empty, print invalid input
        if (choice.empty())
        {
            Helper::printInvalidInput();
        }
        else
        {
            // split choice into multiple objects using the space character as a delimiter
            stringstream split_string(choice);

            // check if there was extra input when choice was split
            if (split_string >> user_command >> board_number && split_string.eof())
            {
                // If user inputs the load command and a valid board number
                if (user_command == COMMAND_LOAD && (board_number == BOARD_TWO || board_number == BOARD_ONE))
                {
                    load_board = true;
                    do_quit = true;
                    return_value = true;
                }

                // If user inputs a load command with an invalid board number
                else
                {
                    Helper::printInvalidInput();
                }
            }

            // If user inputs the quit command
            else if (user_command == COMMAND_QUIT)
            {
                do_quit = true;
                return_value = false;
            }

            // If user inputs an invalid command
            else
            {
                Helper::printInvalidInput();
            }
        }

        // If the user input was valid and a board needs to be loaded
        if (load_board)
        {
            // convert board_number from string to int and store in board_id
            int board_id = stoi(board_number);
            (*board).load(board_id);
            (*board).display(player);
            cout << endl;
        }
    }
    return return_value;
}

/*

* This function is responsible for initializing the player's position on the board based on the user's input.

* It displays acceptable commands to the user which are load <g>, init <x>,<y>,<direction>, quit. It then reads the user's

* input and checks for its validity. If the input is valid, it determines if it's a load, init or quit command and performs

* the corresponding actions. If the input is invalid, it prints a message to the console.

* @return bool - returns true if player was successfully placed on the board and false otherwise.
*/
bool Game::initializePlayer()
{
    // Variable declarations
    string choice = "";
    bool load_board = false;
    bool init_player = false;
    bool do_quit = false;
    bool return_value = false;
    vector<string> initialise_player = {};

    // Loop until user quits
    while (!do_quit && !cin.eof())
    {

        // set necessary boolean values each time loop is called
        string user_command = "";
        string user_value = "";
        load_board = false;
        init_player = false;
        do_quit = false;
        bool invalid_input = false;
        return_value = false;

        initialise_player.clear();

        // Display acceptable commands to the user
        cout << "At this stage of the program, only three commands are acceptable:"
             << endl
             << "load <g>"
             << endl
             << "init <x>,<y>,<direction>"
             << endl
             << "quit"
             << endl
             << endl;

        // Read user input
        choice = Helper::readInput();

        if (choice.empty())
        {
            // print invalid_input
            Helper::printInvalidInput();
        }
        else
        {
            // split user input using space character as a delimiter
            stringstream split_string(choice);

            // check for extra input in the buffer
            if (split_string >> user_command >> user_value && split_string.eof())
            {
                // Check if input is a load command and the board value is correct
                if (user_command == COMMAND_LOAD && (user_value == BOARD_ONE || user_value == BOARD_TWO))
                {
                    load_board = true;
                }
                // Check if input is an init command
                else if (user_command == COMMAND_INIT && (user_value.length() == 9 || user_value.length() == 8))
                {
                    // further split user_value using a comma as a delimiter
                    Helper::splitString(user_value, initialise_player, ",");
                    // check if the newly split objects are a digit and not anything else
                    if (isdigit(initialise_player[0][0]) && isdigit(initialise_player[1][0]))
                    {
                        init_player = true;
                    }
                }
                else
                {
                    Helper::printInvalidInput();
                }
            }
            // Check if input is a quit command
            else if (user_command == COMMAND_QUIT)
            {
                do_quit = true;
            }
            else
            {
                invalid_input = true;
                Helper::printInvalidInput();
            }
        }

        // Load board
        if (load_board)
        {
            // convert user_value from string to int
            int board_id = stoi(user_value);
            (*board).load(board_id);
            (*board).display(player);
            cout << endl;
        }

        // Initialize player
        else if (init_player)
        {
            // store initialize player input into appropriate variables
            string player_direction = initialise_player[2];
            int player_x = stoi(initialise_player[1]);
            int player_y = stoi(initialise_player[0]);

            bool invalid_direction = false;

            // set player position and determine the direction
            Position object_position(player_x, player_y);
            Direction object_direction;
            // check the input direction string and assign the corresponding Direction value
            if (player_direction == DIRECTION_NORTH)
            {
                object_direction = NORTH;
            }
            else if (player_direction == DIRECTION_SOUTH)
            {
                object_direction = SOUTH;
            }
            else if (player_direction == DIRECTION_EAST)
            {
                object_direction = EAST;
            }
            else if (player_direction == DIRECTION_WEST)
            {
                object_direction = WEST;
            }
            else
            {
                // if the input direction is not one of the valid options, set invalid_direction to true
                invalid_direction = true;
            }

            // call the initialisePlayer function of the Player object, passing in the position and direction objects as arguments
            (*player).initialisePlayer(&object_position, object_direction);

            // call the placePlayer function of the Board object, passing in the position object as an argument, and assign the return value to place_player
            bool place_player = (*board).placePlayer(object_position);

            // check if the input direction was invalid, and print an error message if true
            if (invalid_direction)
            {
                Helper::printInvalidInput();
            }

            // check if the player was successfully placed on the board, and display the board or error
            else if (place_player && !invalid_direction)
            {
                (*board).display(player);
                cout << endl;
                // set do_quit to true and return_value to true, since the player has been successfully placed and the game can continue
                do_quit = true;
                return_value = true;
            }
            // if the player was not successfully placed, print an error message
            else if (place_player == false)
            {
                cout << "Unable to place player at that cell."
                     << endl
                     << endl;
            }

            // if none of the above conditions were met, print an error message
            else
            {
                Helper::printInvalidInput();
            }
        }
    }

    return return_value;
}

// This function handles the game logic and user input
void Game::play()
{

    // Initialize variables
    string choice = "";
    bool invalid_input = false;
    bool forward = false;
    bool turn_right = false;
    bool turn_left = false;
    bool do_quit = false;

    // Loop until the player quits the game
    while (!do_quit && !cin.eof())
    {
        // Reset variables
        invalid_input = false;
        forward = false;
        turn_right = false;
        turn_left = false;
        do_quit = false;

        // If the previous input was invalid, clear the input stream
        if (invalid_input)
        {
            cin.clear();
            while (cin.get() != '\n')
                ;
            invalid_input = false;
        }
        // Display available commands
        cout << "At this stage of the program, only four commands are acceptable:"
             << endl
             << "forward (or f)" << endl
             << "turn_left (or l)" << endl
             << "turn_right (or r)" << endl
             << "quit" << endl
             << endl;
        // Get user input
        cin >> choice;
        cout << endl;
        // Check if the input is valid
        if (cin.fail())
        {
            invalid_input = true;
            Helper::printInvalidInput();
        }
        else
        {
            // set corresponding value to true based on user input
            forward = (choice == "forward" || choice == "f");
            do_quit = (choice == "quit");
            turn_left = (choice == "turn_left" || choice == "l");
            turn_right = (choice == "turn_right" || choice == "r");

            // If the input is not valid, print an error message
            if (!forward && !do_quit && !turn_left && !turn_right)
            {
                invalid_input = true;
                Helper::printInvalidInput();
            }
        }

        // Handle user input
        if (forward)
        {
            // Move player forward and display the updated game board or the error message
            PlayerMove check = (*board).movePlayerForward(player);

            if (check == PLAYER_MOVED)
            {
                cout << "Player Moved." << endl
                     << endl;
            }
            else if (check == CELL_BLOCKED)
            {
                cout << "Error: cannot move forward because the road is blocked" << endl
                     << endl;
            }
            else if (check == OUTSIDE_BOUNDS)
            {
                cout << "The car is at the edge of the board and cannot move "
                     << "further in that direction"
                     << endl
                     << endl;
            }

            (*board).display(player);
            cout << endl;
        }
        else if (turn_left)
        {
            // Turn player left and display the updated game board
            TurnDirection direct = TURN_LEFT;
            (*player).turnDirection(direct);
            (*board).display(player);
            cout << endl;
        }
        else if (turn_right)
        {
            // Turn player right and display the updated game board
            TurnDirection direct = TURN_RIGHT;
            (*player).turnDirection(direct);
            (*board).display(player);
            cout << endl;
        }
    }
}