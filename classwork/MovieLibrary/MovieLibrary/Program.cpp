/*
 * Final Version
 * COSC 1436
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>  //File IO
#include <sstream>  //Stringstream

//Movie details
struct Movie
{    
    int id;                     //Unique identifier
    std::string title;          //Required
    std::string description;    //Optional
    int runLength;              //Required, 0
    int releaseYear;            //Optional, but between 1900-2100
    bool isClassic;             //Required, false
    std::string genres;         //Optional (comma separated list of genres)
};

//TODO: Discuss
void ClearInputBuffer()
{
    std::cin.ignore(INT32_MAX, '\n');
}

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

/// <summary>Resets the terminal text color.</summary>
void ResetTextColor()
{
    std::cout << "\033[0m";
}

/// <summary>Set the terminal text color.</summary>
/// <param name="color">Text color</param>
void SetTextColor ( ForegroundColor color )
{
    std::cout << "\033[" << (int)color << "m";
}

/// <summary>Displays an error message.</summary>
/// <param name="message">Message to display.</param>
void DisplayError ( std::string const& message )
{
    //std::cout << "\033[91m" 
    SetTextColor(ForegroundColor::BrightRed);
    std::cout << "ERROR: " << message << std::endl;
    ResetTextColor();
}

/// <summary>Display a confirmation message.</summary>
/// <param name="message">Message to show.</param>
/// <returns>Returns true or false depending on whether confirmed or not.</returns>
bool Confirm(std::string message)
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
int AddToMovieArray(Movie* movies[], int size, Movie* movie)
{
    static int nextId = 1;

    //Validate parameters first
    // Pointers generally should not null
    if (movie == nullptr)
    {
        DisplayError("Invalid movie");
        return -1;
    };

    //Enumerate the array looking for the first blank movie
    for (int index = 0; index < size; ++index)
    {
        //if (movies[index].title == "")        
        //if (movies[index] == nullptr)
        if (!movies[index])
        {
            //Set unique ID of movie
            //movie.id = 0;
            movie->id = nextId++;

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
void ViewMovie ( Movie* movie )
{    
    //if (movie.title == "")
    if (!movie)
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
    std::cout << "Id " << movie->id << std::endl;
    std::cout << movie->title << " (" << movie->releaseYear << ")" << std::endl;
    std::cout << "Run Length " << movie->runLength << " mins" << std::endl;
    std::cout << "Genres " << movie->genres << std::endl;
    std::cout << "Is Classic? " << (movie->isClassic ? "Yes" : "No") << std::endl;
    if (movie->description != "")
        std::cout << movie->description << std::endl;
    std::cout << std::endl;
}

void ViewMovie(Movie& movie)
{
    ViewMovie(&movie);
}
void ViewMovies( Movie* movies[], int size )
{
    //Enumerate movies until we run out
    //for (Movie movie: movies)
    for (int index = 0; index < size; ++index)
    {
        //if (movies[index].title == "")
        //  return;
        if (movies[index])           
            ViewMovie(movies[index]);
    };
}

/// <summary>Prompt user and add movie details.</summary>
Movie* AddMovie ()
{
    //Movie movie;// = {0};
    Movie* movie = new Movie;

    //Get movie details
    movie->title = ReadString("Enter movie title: ", true);
    
    std::cout << "Enter the run length (in minutes): ";
    movie->runLength = ReadInt(0);

    std::cout << "Enter the release year (1900-2100): ";
    //std::cin >> movie->releaseYear;
    movie->releaseYear = ReadInt(1900, 2100);
    
    ClearInputBuffer();
    movie->description = ReadString("Enter the optional description: ", false);
    
    // Genres, up to 5
    for (int index = 0; index < 5; ++index)
    {
        std::string genre = ReadString("Enter the genre (or blank to continue): ", false);        
        if (genre == "")
            break;
        else if (genre == " ")
            continue;

        //TODO: Fix issue with having no genres to begin with
        movie->genres = movie->genres + ", " + genre;
    }

    movie->isClassic = Confirm("Is this a classic movie?");

    return movie;
}

Movie* FindMovie(Movie* movies[], int size, int id)
{
    for (int index = 0; index < size; ++index)
    {
        //If pointer valid and movie matches ID then return it
        if (movies[index] && movies[index]->id == id)
            return movies[index];
    };

    return nullptr;
}

void RemoveMovieFromArray(Movie* movies[], int size, Movie* movie)
{
    for (int index = 0; index < size; ++index)
    {
        if (movies[index] == movie)
        {
            movies[index] = nullptr;
            delete movie;
            return;
        }
    }
}

void DeleteMovie(Movie* movies[], int size)
{
    //Get movie to delete
    std::cout << "Enter the movie ID to delete: ";
    int id = ReadInt(1);

    //Find the movie
    Movie* movie = FindMovie(movies, size, id);
    if (!movie)
    {
        DisplayWarning("Movie not found");
        return;
    };

    if (!Confirm("Are you sure you want to delete " + movie->title + "?"))
        return;

    //Delete movie
    RemoveMovieFromArray(movies, size, movie);    
}

void EditMovie()
{
    DisplayWarning("Not implemented yet");
}

void LoadMovies(Movie* movies[], int size)
{
    //TODO: Implement this
}

std::string QuoteString(std::string const& value)
{
    std::stringstream str;

    //If no starting double quote, then add double quote
    if (value.length() == 0 || value[0] != '"')
        str << '"';
    str << value;

    //If no ending double quote, then add double quote
    if (value.length() == 0 || value[value.length() - 1] != '"')
        str << '"';

    return str.str();
}


void SaveMovie(std::ofstream& file, Movie* pMovie)
{
    if (!pMovie)
        return;

    // Id, title, release year, run length, isClassic, genres, description
    file << pMovie->id
        << ", " << QuoteString(pMovie->title)
        << ", " << pMovie->releaseYear
        << ", " << pMovie->runLength
        << ", " << (pMovie->isClassic ? 1 : 0)
        << ", " << QuoteString(pMovie->genres)
        << ", " << QuoteString(pMovie->description)
        << std::endl;
}

void SaveMovies(const char* filename, Movie* movies[], int size)
{
    //std::fstream fs;
    //std::ifstream ifs;
    //std::ofstream ofs;

    std::ofstream file;

    //To use a file, must open it
    // Flags (bitwise OR together)
    //   in | out - access mode
    //   binary - text (default) or binary
    //   app | ate | trunc - write mode
    //        app - append (always)
    //        ate - append (by default)
    //        trunc - replace 
    file.open(filename, std::ios::out | std::ios::trunc);
    if (file.fail())
    {
        DisplayError("Unable to save movies");
        return;
    };

    //file << "Writing to the file";
    for (int index = 0; index < size; ++index)
        SaveMovie(file, movies[index]);
}

int main()
{           
    const char* FileName = "movies.csv";

    //Cannot calculate the size of an array at runtime so use a const int variable
    const int MaximumMovies = 100;
    Movie* movies[MaximumMovies] = {0};

    LoadMovies(movies, MaximumMovies);

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
        ClearInputBuffer();

        switch (choice)
        {
            case 'A': 
            case 'a': AddToMovieArray(movies, MaximumMovies, AddMovie()); break;

            case 'V':
            case 'v': ViewMovies(movies, MaximumMovies); break;            

            case 'D':
            case 'd': DeleteMovie(movies, MaximumMovies); break;

            case 'E':
            case 'e': EditMovie(); break;

            case 'Q':
            case 'q': SaveMovies(FileName, movies, MaximumMovies); done = true; break;

            default: DisplayError("Invalid choice"); break;
        };
    } while (!done);
}