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
    int id;                     //Unique identifier
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
void DisplayError(std::string const&);

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
void DisplayError ( std::string const& message )
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
    std::cin >> movie->releaseYear;
    movie->releaseYear = ReadInt(1900, 2100);

    movie->description = ReadString("Enter the optional description: ", false);
    
    // Genres, up to 5
    for (int index = 0; index < 5; ++index)
    {
        std::string genre = ReadString("Enter the genre (or blank to continue): ", false);        
        if (genre == "")
            break;
        else if (genre == " ")
            continue;

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

    //An uninitialized pointer points to garbage
    // Initialize pointer to memory 0 which is invalid
    //  NULL - C version, not preferred as it is still an int
    //  nullptr - preferred in C++
    //float* pFloat = NULL;    
    float* pFloat = nullptr;
    //pFloat = 0;   Don't do this
    //pFloat = 1234;
    
    //Always ensure pointer is valid (not null) before dereferencing
    //if (pFloat != nullptr) {
    if (pFloat) {
        //This is going to crash hard if pointer is NULL
        *pFloat = 123.45;
    }

    //Initializing a pointer
    // nullptr
    float localFloat = 123.45;

    //Initialize a pointer to a local variable or parameter
    pFloat = &localFloat;  //Address of localFloat, must be a variable
    *pFloat = 456.78;   //localFloat = 456.78

    //Initialize a pointer to an array element
    float someFloats[10] = {0};
    pFloat = &someFloats[1];   //Ptr references second element

    //Compiler error, types must exactly match
    //pFloat = pInt;   // float* = int*

    //Dynamic memory
    // new_op ::= new T  returns T*
    pFloat = new float;
    *pFloat = 89.76;    

    for (int index = 0; index < 10000; ++index)
    {
        pFloat = new float;
        *pFloat = index;

        //Deleting a pointer twice will crash or corrupt memory unless it is nullptr
        //Immediately after deleting a pointer you should set it to nullptr
        delete pFloat;
        pFloat = nullptr;

        //Ensure you call delete for each pointer you allocate using new
        delete pFloat;
        pFloat = nullptr;
        //*pFloat = index; //Using a deallocated pointer may crash or corrupt
    }

    //Pointer assignment must exactly match the types used (no coercion)
    // pFloat = float*
    // someFloats[1] = float
    // &(Et) = T*
    // &(someFloats[1]) = &(float) = float*

}

// Pointers vs pass by ref
void EditMovieWithPassByReference(Movie& movie)  //C++ with pass by ref, preferred
{
    movie.title = ReadString("Enter the new title: ", true);

    std::cout << "Enter the new run length: ";
    movie.runLength = ReadInt(0);
}

//Switching from ref to pointers
// 1. Change ref parameter to pointer
// 2. Validate the parameter
// 3. Dereference to get underlying value or use pointer access op
void EditMovieWithPointer(Movie* movie)  //C with pointers, only if needed
{
    if (movie == nullptr)
        return;
    
    //movie.title = ReadString("Enter the new title: ", true);
    movie->title = ReadString("Enter the new title: ", true);

    std::cout << "Enter the new run length: ";
    movie->runLength = ReadInt(0);
}

void ArrayAndPointerDemo()
{
    const int MaxSize = 100;
    
    int numbers[MaxSize];
    
    for (int index = 0; index < MaxSize; ++index)
        numbers[index] = index + 1;

    for (int index = 0; index < MaxSize; ++index)
        std::cout << numbers[index] << std::endl;

    //Arrays and pointers are interchangeable
    // - Can assign a pointer to an array and vice versa
    // - Can use array element operator on pointer
    // - Can use pointer dereference on array variable
    // - Can use either array element operator or pointer arithmetic to get to elements
    // arr[N] = *(arr + N)
    // Pointer arithmetic means adding/subtracting int from pointer moves the value
    //   by a full element size, not bytes (cannot point into a partial element)
    int* pNumbers = numbers;
    for (int index = 0; index < MaxSize; ++index)
        pNumbers[index] = index + 1;   //Can use array syntax with pointers and vice versa

    //Can enumerate without using array element operator
    int* pElement = numbers;
    for (int index = 0; index < MaxSize; ++index)
        //std::cout << numbers[index] << std::endl;
        std::cout << *(numbers + index) << std::endl;

    pElement = numbers;
    for (int index = 0; index < MaxSize; ++index)
        //std::cout << numbers[index] << std::endl;
        std::cout << *(pElement++) << std::endl;
}

int* ResizeArray(int array[], int oldSize, int newSize)
{
    if (newSize <= 0)
    {
        DisplayError("I don't think so");
        return nullptr;
    }
    //int* pNewValue = new int;

    //newSize > 0
    int* pNewArray = new int[newSize];

    //Init the array because we cannot use init syntax with new
    for (int index = 0; index < newSize; ++index)
        pNewArray[index] = 0;

    //Copy values from old to new array
    oldSize = (oldSize < newSize) ? oldSize : newSize;
    for (int index = 0; index < oldSize; ++index)
        pNewArray[index] = array[index];

    return pNewArray;
}

void DeleteArray(int* array)
{
    // Rules
    // 1. Array better have been allocated using new
    // 2. You must delete the entire array using delete[]
    // 3. If delete[] is called on a null ptr it will most likely crash
    if (array)
        delete[] array;
    array = nullptr;
}

int youWillNeverDoThis = 100;
int* ReturningAPointerDemo(int someValue, int values[])
{
    int* ptr = nullptr;

    // Valid cases for returning a pointer
    // 1. Dynamically allocated memory using new
    ptr = new int;
    // 2. Elements of an array parameter
    ptr = &values[0];
    // 3. Global variables
    ptr = &youWillNeverDoThis;

    // Invalid cases
    // 1. Parameters  (ptr = &someValue)
    // 2. Local variables (int localVar; ptr= &localVar;)

    return nullptr;
}

void ConstantDemo()
{
    //Context is generally pointers and references
    int someValue;
    int* ptrNonconst;       //Non-const means a value can be read or written
    int const* ptrConst;    //Const means a value can only be read (int const*)    
    ptrNonconst = &someValue;

    //Can treat a non-const value as const (can treat a writable value as readonly)    
    ptrConst = ptrNonconst;

    //Cannot treat a const value as non-const (cannot treat a readonly value as writable)
    //ptrNonconst = ptrConst;

    //In rare cases can remove the constant if you are absolutely sure the value is writable
    ptrNonconst = (int*)ptrConst;
    ptrNonconst = const_cast<int*>(ptrConst);

    //6 forms of constant references and pointers, dividing line is *, read right to left
    // 1)       T *         pointer to T (ptr: RW, value: RW)
    // 2)       T * const   const pointer to T (ptr: R, value: RW)
    // 3) T const *         pointer to const T (ptr: RW, value: R)      
    // 4) const T *         pointer to T const (ptr: RW, value: R)
    // 5) T const * const   const pointer to const T (ptr: R, value: R)
    // 6) const T * const   const poitner to T const (ptr: R, value: R)
    // Forms 3 and 4 are the same, forms 5 and 6 are the same
}

int main()
{           
    //Movie movie;

    ////Calling pass by reference function
    //EditMovieWithPassByReference(movie);

    ////Calling with pointer 
    //// 4. Must use address of if normal variable, or pointer
    //EditMovieWithPointer(&movie);

    //PointerDemo();

    //Cannot calculate the size of an array at runtime so use a const int variable
    const int MaximumMovies = 100;
    Movie* movies[MaximumMovies] = {0};

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
            case 'd': DeleteMovie(movies, MaximumMovies); break;

            case 'E':
            case 'e': EditMovie(); break;

            case 'Q':
            case 'q': done = true;

            default: DisplayError("Invalid choice"); break;
        };
    } while (!done);
}