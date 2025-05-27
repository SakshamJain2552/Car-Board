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

@brief This function generates the game board based on user input

@return bool return_value - Whether the board was successfully loaded or not
*/
bool Game::loadBoard()
{
    string choice = "";
    bool gen = false;
    bool do_quit = false;
    bool return_value = false;

    /*

@brief This loop continues until the user inputs quit or generates a valid board
*/
    while (!do_quit && !cin.eof())
    {
        // initialise variables
        int size = 0;
        float random = 0;
        std::vector<std::string> loadArr = {};
        loadArr.clear();
        gen = false;
        do_quit = false;
        return_value = true;
        string user_command = "";
        string board_number = "";

        // Display acceptable user commands
        cout << "At this stage of the program, only two commands are acceptable:"
             << endl
             << "generate <d>, <p>"
             << endl
             << "quit"
             << endl
             << endl;

        // Read user input
        choice = Helper::readInput();

        if (choice.empty())
        {
            Helper::printInvalidInput();
        }
        else
        {
            stringstream split_string(choice);

            if (split_string >> user_command >> board_number && split_string.eof())
            {
                // Check if input is in the correct format for generating a board
                if (user_command == COMMAND_GENERATE_RANDOM && (board_number.length() == 6 || board_number.length() == 4))
                {
                    // Split board_number into its components and check if they are valid
                    Helper::splitString(board_number, loadArr, ",");
                    if (loadArr.size() == 2)
                    {
                        if (isdigit(loadArr[0][0]) && isdigit(loadArr[1][0]))
                        {
                            // Convert string components into integer and float
                            size = stoi(loadArr[0]);
                            random = stof(loadArr[1]);

                            // Check if size and random values are within acceptable range
                            if ((size >= 10 && size <= 20) && (random >= 0 && random < 1))
                            {
                                gen = true;
                                do_quit = true;
                                return_value = true;
                            }
                        }
                    }
                }
                else
                {
                    Helper::printInvalidInput();
                }
            }
            else if (user_command == COMMAND_QUIT)
            {
                do_quit = true;
                return_value = false;
            }
            else
            {
                Helper::printInvalidInput();
            }
        }
        // Generate board if input is valid
        if (gen)
        {
            (*board).generateboard(size, random);
            (*board).display(this->player);
            cout << endl;
        }
    }
    return return_value;
}

// This function initializes the player on the game board by prompting the user to enter commands and values.
// The accepted commands are generate <d>,<p>, init <x>,<y>,<direction>, and quit.
// The function returns a boolean indicating whether the player was successfully initialized or not.
// The function uses the Helper class to split the input string and perform validation checks on the user's input.
bool Game::initializePlayer()
{

    // Initialize variables.
    string choice = "";
    bool gen = false;
    bool init_player = false;
    bool do_quit = false;
    bool return_value = false;
    vector<string> initialise_player = {};

    // Continue prompting user for input until they quit or the player is initialized.
    while (!do_quit && !cin.eof())
    {
        // Initialize variables for each loop iteration.
        string user_command = "";
        string user_value = "";
        int size = 0;
        float random = 0;

        gen = false;
        init_player = false;
        do_quit = false;
        bool invalid_input = false;
        return_value = false;

        initialise_player.clear();
        // Prompt the user for input and display acceptable commands.
        cout << "At this stage of the program, only three commands are acceptable:"
             << endl
             << "generate <d>,<p>"
             << endl
             << "init <x>,<y>,<direction>"
             << endl
             << "quit"
             << endl
             << endl;

        choice = Helper::readInput();

        // Check if input is empty and print error message if it is.
        if (choice.empty())
        {
            Helper::printInvalidInput();
        }
        else
        {
            // Split the input string into a command and a value using a stringstream.
            stringstream split_string(choice);

            // Check if the command and value were successfully extracted and there are no additional characters.
            if (split_string >> user_command >> user_value && split_string.eof())
            {
                if (user_command == COMMAND_GENERATE_RANDOM && (user_value.length() == 6 || user_value.length() == 4))
                {
                    // If the command is generate and the value is the correct format, parse the size and random values.
                    Helper::splitString(user_value, initialise_player, ",");
                    if (initialise_player.size() == 2)
                    {
                        if (isdigit(initialise_player[0][0]) && isdigit(initialise_player[1][0]))
                        {

                            size = stoi(initialise_player[0]);
                            random = stof(initialise_player[1]);
                            // Check if size and random values are within acceptable ranges.
                            if ((size >= 10 && size <= 20) && (random >= 0 && random <= 1))
                            {
                                gen = true;
                            }
                        }
                    }
                }
                // If the command is init, split the value string into x, y, and direction values.
                else if (user_command == COMMAND_INIT)
                {
                    Helper::splitString(user_value, initialise_player, ",");
                    if (true)
                    {
                        init_player = true;
                    }
                }
                // If the command is not valid, print an error message.
                else
                {
                    Helper::printInvalidInput();
                }
            }
            // If the command is quit, set the do_quit flag to true.
            else if (user_command == COMMAND_QUIT)
            {
                do_quit = true;
            }
            // If the input is invalid, print an error message.
            else
            {
                invalid_input = true;
                Helper::printInvalidInput();
            }
        }
        // generate board
        if (gen)
        {
            (*board).generateboard(size, random);
            (*board).display(this->player);
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
            // (*board).display(player);
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
                // invalid_input = true;
                cout << "Unable to place player at that cell."
                     << endl
                     << endl;
            }
            else
            // if none of the above conditions were met, print an error message
            {
                // invalid_input = true;
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