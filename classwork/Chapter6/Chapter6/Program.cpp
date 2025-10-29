/*
 * Chapter 6
 * COSC 1436
 */
#include <iostream>
#include <string>
#include <iomanip>

//Movie details
struct Movie
{    
    std::string title;          //Required
    std::string description;    //Optional
    int runLength;              //Required, 0
    int releaseYear;            //Optional, but between 1900-2100
    bool isClassic;             //Required, false
    std::string genres;         //Optional (comma separated list of genres)
};

//DO NOT DO THIS!!!
//int g_thisIsAGlobalVariable = 100;

/// <summary>Defines possible foreground colors.</summary>
enum class ForegroundColor {
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Cyan = 36,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93,
    BrightCyan = 96
};

//Function prototypes
//Forward declarations/referencing
void DisplayError(std::string);

void ResetTextColor()
{
    std::cout << "\033[0m";
}

void SetTextColor ( ForegroundColor color )
{
    std::cout << "\033[" << (int)color << "m";
}

/// <summary>Display a confirmation message.</summary>
/// <param name="message">Message to show.</param>
/// <returns>Returns true or false depending on whether confirmed or not.</returns>
bool Confirm ( std::string message )
{
    std::cout << message << " (Y/N) ";
    std::string input;
    std::cin >> input;

    while (true)
    {
        if (_strcmpi(input.c_str(), "Y") == 0)
            return true;
        else if (_strcmpi(input.c_str(), "N") == 0)
            return false;
        else {
            DisplayError("You must enter either Y or N");

            std::cin >> input;
        }
    }
}

/// <summary>Displays an error message.</summary>
/// <param name="message">Message to display.</param>
void DisplayError ( std::string message )
{
    //std::cout << "\033[91m" 
    SetTextColor(ForegroundColor::BrightRed);
    std::cout << "ERROR: " << message << std::endl;
    ResetTextColor();
}

/// <summary>Displays a warning message.</summary>
/// <param name="message">Message to display.</param>
void DisplayWarning(std::string message)
{
    SetTextColor(ForegroundColor::BrightYellow);
    std::cout << message << std::endl;
    ResetTextColor();
}

int ReadInt ( int minimumValue, int maximumValue )
{    
    do
    {
        int value;
        std::cin >> value;
        
        if (value >= minimumValue && value <= maximumValue)
            return value;

        DisplayError("Value is outside range");
    } while (true);   
}

int ReadInt(int minimumValue)
{
    return ReadInt(minimumValue, INT_MAX);
}

std::string ReadString ( std::string message, bool isRequired )
{    
    std::cout << message;

    std::string input;
    std::getline(std::cin, input);
    
    while (isRequired && input == "")
    {
        DisplayError("Value is required");

        std::getline(std::cin, input);
    }

    return input;
}

/// <summary>View details of a movie.</summary>
/// <remarks>
/// More details including paragraphs of data if you want.
/// </remarks>
void ViewMovie ( Movie movie )
{    
    if (movie.title == "")
    {
        DisplayWarning("No movies exist");
        return;
    }

    // View movie
    //    Title (Year)
    //    Run Length # min
    //    User Rating = ##
    //    Is Classic? 
    //    [Description]
    std::cout << std::fixed << std::setprecision(1) << std::endl;
    std::cout << movie.title << " (" << movie.releaseYear << ")" << std::endl;
    std::cout << "Run Length " << movie.runLength << " mins" << std::endl;
    std::cout << "Genres " << movie.genres << std::endl;
    std::cout << "Is Classic? " << (movie.isClassic ? "Yes" : "No") << std::endl;
    if (movie.description != "")
        std::cout << movie.description << std::endl;
    std::cout << std::endl;
}

/// <summary>Prompt user and add movie details.</summary>
Movie AddMovie ()
{
    Movie movie;// = {0};

    //Get movie details
    movie.title = ReadString("Enter movie title: ", true);
    
    std::cout << "Enter the run length (in minutes): ";
    movie.runLength = ReadInt(0);

    std::cout << "Enter the release year (1900-2100): ";
    std::cin >> movie.releaseYear;
    movie.releaseYear = ReadInt(1900, 2100);    

    movie.description = ReadString("Enter the optional description: ", false);
    
    // Genres, up to 5
    for (int index = 0; index < 5; ++index)
    {
        std::string genre = ReadString("Enter the genre (or blank to continue): ", false);        
        if (genre == "")
            break;
        else if (genre == " ")
            continue;

        movie.genres = movie.genres + ", " + genre;
    }

    movie.isClassic = Confirm("Is this a classic movie?");

    return movie;
}

void DeleteMovie(Movie& movie)
{
    if (!Confirm("Are you sure you want to delete " + movie.title + "?"))
        return;

    //TODO: Delete movie
    //DisplayWarning("Not implemented yet");
    movie.title = "";
}

void EditMovie(Movie& movie)
{
    DisplayWarning("Not implemented yet");
}

//Test function overloading
void Display ( int value )
{
    std::cout << "int" << std::endl;
}

void Display(double value)
{
    std::cout << "double" << std::endl;
}

void Display(float value)
{
    std::cout << "float" << std::endl;
}

void Display ( short value1, double value2 )
{
    std::cout << "int, double" << std::endl;
}

void Display(short value, float)
{
    std::cout << "short, float" << std::endl;
}

void Display(int, short)
{
    std::cout << "int, short" << std::endl;
}

void Display(short, int)
{
    std::cout << "int, short" << std::endl;
}

//void TestFunctionOverloading()
//{ 
//    Display(10);   //Display(int)
//    Display(4.56); // Display(double)
//    Display((short)34);  // Display(int) -> shortest type coercion
//    Display(10, 4.56F);  // Display(int, double)
//
//    long lValue = 10000L;
//    Display(lValue, 4.56);
//
//    //Display("Hello", 4.56); //Compiler error, no matches
//    //Display(10, "Hello");   //Compiler error, no matches
//
//    Display('c', 4.56F);   // short, float
//    Display((short)5, (short)10);
//}

int Factorial(int value)
{
    if (value <= 1)
        return 1;

    return value * Factorial(value - 1);
}

void ArrayDemo()
{
    const int MaxNumbers = 100;

    //Init array using { 0 }
    int numbers[MaxNumbers] = {0};
    //int numbers[100];

    //# of days in each month
    //int daysInMonth[12] = { 0 };
    //Approach 1 - correct but not readable
    /*daysInMonth[0] = daysInMonth[2] = daysInMonth[4] = daysInMonth[6] = daysInMonth[7] 
                   = daysInMonth[9] = daysInMonth[11] = 31;
    daysInMonth[1] = 28;
    daysInMonth[3] = daysInMonth[5] = daysInMonth[8] = daysInMonth[10] = 30;*/

    //Approach 2 - init expression
    // Zero init - each element is set to 0// { 0 }
    // Full init - each element is assigned a value
    // Partial init - each element is assigned a value and remaining elements are 0 initialized    
    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Implicit array sizing
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    //Set each element to its element number (element 1 = 1, element 2 = 2, etc)
    //Approach 1 for small arrays only
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;

    //Approach 2 for any array
    for (int index = 0; index < MaxNumbers; ++index)
        numbers[index] = index + 1;

    for (int index = 0; index < MaxNumbers; ++index)
        std::cout << numbers[index] << std::endl;
}

int main()
{       
    ArrayDemo();
    //std::cout << Factorial(5) << std::endl;

    //Cannot calculate the size of an array at runtime so use a const int variable
    const int MaximumMovies = 100;

    //TODO: Leaving this for now to avoid breaking code
    Movie movie;
    Movie movies[MaximumMovies];

    // Array operator []
    //    A[index] = behaves like a variable
    Movie firstElement = movies[0];

    //Display main menu
    bool done = false;
    do
    {
        std::cout << "Movie Library" << std::endl;
        std::cout << "--------------" << std::endl;
        std::cout << "A)dd Movie" << std::endl;
        std::cout << "V)iew Movies" << std::endl;
        std::cout << "E)dit Movie" << std::endl;
        std::cout << "D)elete Movie" << std::endl;
        std::cout << "Q)uit" << std::endl;

        char choice;
        std::cin >> choice;        

        switch (choice)
        {
            case 'A': 
            case 'a': movie = AddMovie(); break;

            case 'V':
            case 'v': ViewMovie(movie); break;            

            case 'D':
            case 'd': DeleteMovie(movie); break;

            case 'E':
            case 'e': EditMovie(movie); break;

            case 'Q':
            case 'q': done = true;

            default: DisplayError("Invalid choice"); break;
        };
    } while (!done);
    
    //std::cin.ignore();
    // Function call ::= func () 
    //ViewMovie();    
}