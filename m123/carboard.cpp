// Include necessary header files
#include "game.h"
#include "helper.h"

// Use standard namespace for various input/output objects
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

// Define constants for input choices
#define INPUT_CHOICE_ONE 1
#define INPUT_CHOICE_TWO 2
#define INPUT_CHOICE_THREE 3

// Function to display student information
void showStudentInformation(string name, string no, string email)
{
    // Display student information
    cout << endl
         << "--------------------------"
         << endl
         << "Name: "
         << name
         << endl
         << "No: "
         << no
         << endl
         << "Email: "
         << email
         << endl
         << "--------------------------"
         << endl;
}

// Main function
int main()
{
    // Declare choice and do_quit variables
    string choice = "";
    bool do_quit = false;

    // declare student info
    string name = "Saksham Jain", no = "3923854", email = "s3923854@student.rmit.edu.au";

    // Main loop that quits if do_quit = true or EOF character is entered
    while (!do_quit && !cin.eof())
    {
        // Declare variables for main menu
        Game *game = new Game;
        bool incorrect_input = false;
        bool student_information = false;
        bool game_start = false;
        do_quit = false;
        int input_choice = 0;

        // Clear input stream if incorrect input
        if (incorrect_input)
        {
            cin.clear();
            while (cin.get() != '\n')
                ;
            incorrect_input = false;
        }

        // Display main menu
        cout << endl
             << "Welcome to Car Board"
             << endl
             << "--------------------"
             << endl
             << "1. Play Game"
             << endl
             << "2. Show Student's Information"
             << endl
             << "3. Quit"
             << endl
             << endl;
        cout << "Please enter your choice: " << endl;

        // Get user input into choice
        cin >> choice;

        // Remove leading and trailing whitespace
        choice = choice.erase(0, choice.find_first_not_of(" \t\n\r\f\v"));
        choice = choice.erase(choice.find_last_not_of(" \t\n\r\f\v") + 1);

        // Check if input is of correct size
        if (choice.size() != 1)
        {
            incorrect_input = true;
        }
        else
        {
            input_choice = stoi(choice);
        }

        // Display new line
        cout << endl;

        // Check input choice and set appropriate boolean variables
        if (cin.fail())
        {
            incorrect_input = true;
        }
        else
        {
            // if Choice is equal to none of the given options, then set incorrect_input = true
            if (input_choice != INPUT_CHOICE_ONE && input_choice != INPUT_CHOICE_TWO && input_choice != INPUT_CHOICE_THREE)
            {
                incorrect_input = true;
            }
            game_start = (input_choice == INPUT_CHOICE_ONE);
            student_information = (input_choice == INPUT_CHOICE_TWO);
            do_quit = (input_choice == INPUT_CHOICE_THREE);
        }

        // Start game, show student information or quit according to user input
        if (game_start)
        {
            (*game).start();
        }
        else if (student_information)
        {
            showStudentInformation(name, no, email);
            input_choice = 0;
        }
        else if (do_quit)
        {
            delete game;
            game = nullptr;
        }
    }
    // Exit the Program
    return EXIT_SUCCESS;
}