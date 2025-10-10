/*
 * Chapter 6
 * COSC 1436
 */
#include <iostream>
#include <string>
#include <iomanip>
#include "Program.h"

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

/// <summary>View details of a movie.</summary>
/// <remarks>
/// More details including paragraphs of data if you want.
/// </remarks>
void ViewMovie()
{
    Movie movie;

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
void AddMovie()
{
    Movie movie;// = {0};

    //Get movie details
    std::cout << "Enter movie title: ";
    std::cin.ignore();
    std::getline(std::cin, movie.title);

    //Title is required
    while (movie.title == "")
    {
        std::cout << "Title is required" << std::endl;
        std::getline(std::cin, movie.title);
    }

    std::cout << "Enter the run length (in minutes): ";
    do
    {
        std::cin >> movie.runLength;

        //Error
        if (movie.runLength < 0)
        {
            std::string message = "Run length must be at least 0";
            std::cout << "ERROR: " << message << std::endl;
        }
    } while (movie.runLength < 0);

    std::cout << "Enter the release year (1900-2100): ";
    std::cin >> movie.releaseYear;
    while (movie.releaseYear < 1900 || movie.releaseYear > 2100)
    {
        std::cout << "Release year must be between 1900 and 2100" << std::endl;

        std::cin >> movie.releaseYear;
    }

    std::cout << "Enter the optional description: ";
    std::cin.ignore();
    std::getline(std::cin, movie.description);

    // Genres, up to 5
    for (int index = 0; index < 5; ++index)
    {
        std::string genre;

        std::cout << "Enter the genre (or blank to continue): ";
        std::getline(std::cin, genre);
        if (genre == "")
            break;
        else if (genre == " ")
            continue;

        movie.genres = movie.genres + ", " + genre;
    }

    std::cout << "Is this a classic (Y/N)? ";
    std::string input;
    std::cin >> input;

    while (true)
    {
        if (_strcmpi(input.c_str(), "Y") == 0)
        {
            movie.isClassic = true;
            break;
        } else if (_strcmpi(input.c_str(), "N") == 0)
        {
            movie.isClassic = false;
            break;
        } else {
            std::cout << "You must enter either Y or N";

            std::cin >> input;
        }
    }
}

int main()
{   
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
            case 'a': AddMovie(); break;

            case 'V':
            case 'v': ViewMovie(); break;            

            case 'D':
            case 'd': std::cout << "Delete not implemented" << std::endl; break;

            case 'E':
            case 'e': std::cout << "Edit not implemented" << std::endl; break;

            case 'Q':
            case 'q': done = true;

            default: std::cout << "Invalid choice" << std::endl; break;
        };
    } while (!done);
    
    //std::cin.ignore();
    // Function call ::= func () 
    //ViewMovie();
}