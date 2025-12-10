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

// Discuss
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

        //Fix issue with having no genres to begin with
        if (movie->genres.length() > 0)
            movie->genres = movie->genres + ", " + genre;
        else
            movie->genres = genre;
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

int ParseFields(std::string const& line, std::string fields[], int size)
{
    int fieldIndex = 0;
    std::string field;
    
    for (int index = 0; index < line.length() && fieldIndex < size; ++index)
    {
        //Comma marks end of previous field
        if (line[index] == ',')
        {
            //Move the field value into the array and move to the next field
            fields[fieldIndex++] = field;
            field = "";
        } else if (isspace(line[index]))   //Ignore whitespace
            continue;
        else if (line[index] == '"')
        {
            //Read string until eof or we get to the next quote
            int endString = line.find('"', index + 1);
            if (endString < 0)  //Ran out of string
                return -1;

            //Field is everything between the quotes
            field = line.substr(index + 1, (endString - index - 1));                          

            //Jump the parsing to the end of the string
            index = endString;
        } else 
            field += line[index];
    };

    //Whatever remains in the last field is moved to the last array element
    fields[fieldIndex++] = field;
    return fieldIndex;
}

int ParseInt(std::string const& field)
{
    //Assume the string is valid because it is coming from the CSV file
    return strtol(field.c_str(), nullptr, 10);
}

std::string ParseString(std::string const& field)
{
    if (field == "")
        return field;

    //Strip the quotes off
    std::stringstream str;
        
    for (int index = 0; index < field.length(); ++index)
    {
        if (field[index] == '"' && (index == 0 || index == field.length() - 1))
            continue;

        str << field[index];
    }

    return str.str();
}

Movie* LoadMovie(std::string const& line)
{
    if (line == "")
        return nullptr;

    std::string fields[7];
    int count = ParseFields(line, fields, 7);
    if (count != 7)
        return nullptr;

    //Parse the strings into their appropriately typed fields
    Movie* pMovie = new Movie();
    pMovie->id = ParseInt(fields[0]);
    pMovie->title = ParseString(fields[1]);
    pMovie->releaseYear = ParseInt(fields[2]);
    pMovie->runLength = ParseInt(fields[3]);
    pMovie->isClassic = ParseInt(fields[4]) != 0;
    pMovie->genres = ParseString(fields[5]);
    pMovie->description = ParseString(fields[6]);

    return pMovie;
}
    

void LoadMovies(const char* filename, Movie* movies[], int size)
{
    std::ifstream file;

    file.open(filename, std::ios::in);
    if (file.fail())
        return;

    //Read each line, until end of file
    // eof()
    //if (file.eof())
        //end of file

    //While we still have room and we haven't reached the EOF
    int index = 0;
    while (index < size && !file.eof())
    {
        std::string line;
        std::getline(file, line);

        //Read/write a single character
        //char ch;
        //file.get(ch); //Read a single char
        //outfile.put(ch);  //Write a single char        

        //Error handling
        bool isFailed = file.fail();
        bool isBad = file.bad();  //Don't generally use this one

        bool isGood = file.good();   //Nobody really uses this
        //if (file.good())
        //    ;  //Read was successful

        //Resets a failed file stream
        if (file.bad())
            file.clear();
        
        //If movie loaded then add to array and move to next line
        Movie* pMovie = LoadMovie(line);
        if (pMovie)
            movies[index++] = pMovie;

        //file.getline();  //C-String version
    }

    //TODO: Need to find largest movie ID, if any and ensure we start there when adding new movies
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

    //Release the file
    file.close();
}

int main()
{           
    const char* FileName = "movies.csv";

    //Cannot calculate the size of an array at runtime so use a const int variable
    const int MaximumMovies = 100;
    Movie* movies[MaximumMovies] = {0};

    LoadMovies(FileName, movies, MaximumMovies);

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