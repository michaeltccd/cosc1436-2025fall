/*
 * Final Version
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

/// <summary>Reads an integer from the terminal.</summary>
/// <param name="minimumValue">Minimum value</param>
/// <param name="maximumValue">Maximum value</param>
/// <returns>Integer value provided by user</returns>
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

/// <summary>Reads an integer from the terminal.</summary>
/// <param name="minimumValue">Minimum value</param>
/// <returns>Integer value provided by user</returns>
int ReadInt(int minimumValue)
{
    return ReadInt(minimumValue, INT_MAX);
}

/// <summary>Reads a string from the terminal.</summary>
/// <param name="message">Message to show</param>
/// <param name="isRequired">true if the input is required</param>
/// <returns>String value provided by user.</returns>
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

/// <summary>Adds a movie to an array.</summary>
/// <param name="movies">Array</param>
/// <param name="size">Size of the array</param>
/// <param name="movie">Movie to add</param>
/// <returns>Index of new movie if inserted or -1 otherwise.</returns>
int AddToMovieArray(Movie movies[], int size, Movie movie)
{
    //Enumerate the array looking for the first blank movie
    for (int index = 0; index < size; ++index)
    {
        if (movies[index].title == "")
        {
            //Set the array element
            movies[index] = movie;
            return index;
        }
    }

    DisplayError("No space available for new movie");
    return -1;
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

void ViewMovies( Movie movies[], int size )
{
    //Enumerate movies until we run out
    //for (Movie movie: movies)
    for (int index = 0; index < size; ++index)
    {
        if (movies[index].title == "")
            return;

        ViewMovie(movies[index]);
    };
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

void DeleteMovie()
{
    Movie movie;
    if (!Confirm("Are you sure you want to delete " + movie.title + "?"))
        return;

    //TODO: Delete movie
    movie.title = "";
}

void EditMovie()
{
    DisplayWarning("Not implemented yet");
}

void PointerDemo()
{    
    int localInt = 1234;

    //Pointer - memory address    
    //Data points
    //  Pointer value is a memory address (8 bytes)
    //  Value pointed to by pointer (dereferenced value) is int (4 bytes)
    // pointer_decl ::= T* id
    int* pInt;              //Pointer to an int
    pInt = &localInt;

    localInt =9876;

    // Dereferencing a pointer returns the original type T
    //   dereference_op := *ptr
    *pInt = 5678;
}

int main()
{       
    PointerDemo();

    //Cannot calculate the size of an array at runtime so use a const int variable
    const int MaximumMovies = 100;
    Movie movies[MaximumMovies];

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
            case 'a': AddToMovieArray(movies, MaximumMovies, AddMovie()); break;

            case 'V':
            case 'v': ViewMovies(movies, MaximumMovies); break;            

            case 'D':
            case 'd': DeleteMovie(); break;

            case 'E':
            case 'e': EditMovie(); break;

            case 'Q':
            case 'q': done = true;

            default: DisplayError("Invalid choice"); break;
        };
    } while (!done);
}