/*
 * Chapter 4
 * COSC 1436
 */
#include <iostream>
#include <string>

int main()
{
    //Movie details
    std::string title;          //Required
    std::string description;    //Optional
    int runLength;              //Required, 0
    int releaseYear;            //Optional, but between 1900-2100
    double userRating;          //Optional, 1.0-10.0
    bool isClassic;             //Required, false

    //Get movie details
    std::cout << "Enter movie title: ";
    std::getline(std::cin, title);

    //Title is required
    bool isEmpty = title == "";
    if (isEmpty)
        std::cout << "Title is required" << std::endl;

    std::cout << "Enter the run length (in minutes): ";
    std::cin >> runLength;
    if (runLength < 0)
    {
        std::cout << "Run length must be at least 0" << std::endl;
        runLength = 0;
    };

    std::cout << "Enter the release year (1900-2100): ";
    std::cin >> releaseYear;
    /*if (releaseYear < 1900)
    {
        std::cout << "Release year must be at least 1900" << std::endl;
        releaseYear = 1900;
    } else if (releaseYear > 2100)
    {
        std::cout << "Release year must be between 1900 and 2100" << std::endl;
        releaseYear = 1900;
    }*/

    // Logical AND &&   Eb && Eb => bool
    // Logical OR ||    Eb || Eb => bool
    // Logical NOT !    !Eb => bool
    if (releaseYear < 1900 || releaseYear > 2100)
    {
        std::cout << "Release year must be between 1900 and 2100" << std::endl;
        releaseYear = 1900;
    }

    std::cout << "Enter the optional description: ";
    std::getline(std::cin, description);

    // Validate userRating
    std::cout << "Enter the optional user rating (1.0-10.0): ";
    std::cin >> userRating;
    if (userRating < 1.0 || userRating > 10.0)
    {
        std::cout << "Rating must be between 1.0 and 10.0" << std::endl;
        userRating = 1.0;
    }
    /*if (userRating < 1.0)
    {
        std::cout << "Rating must be between 1.0 and 10.0" << std::endl;
        userRating = 1.0;
    } else if (userRating > 10.0)
    {
        std::cout << "Rating must be between 1.0 and 10.0" << std::endl;
        userRating = 1.0;
    }*/

    std::cout << "Is this a classic (Y/N)? ";
    std::string input;
    std::cin >> input;

    // if (Eb) S [ else S ] ;
    // Else associates with nearest preceding if
    // Nested if
    //   if (E1) 
    //     if (E2) 
    //       if (E3)
    //          S (E1, E2 and E3 must be true)
    // if-else-if
    //   if (E1)
    //     S
    //   else if (E2)
    //     S  (E1 is false and E2 is true)
    // 

    /*if (_strcmpi(input.c_str(), "Y") == 0)
        isClassic = true;
    if (_strcmpi(input.c_str(), "N") == 0)
        isClassic = false;
    else
        std::cout << "You must enter either Y or N";*/
    if (_strcmpi(input.c_str(), "Y") == 0)
        isClassic = true;
    else 
        if (_strcmpi(input.c_str(), "N") == 0)
            isClassic = false;
        else
            std::cout << "You must enter either Y or N";
    //TODO: Handle other values
}

void relationalDemo()
{
    std::cout << "Enter two values: ";

    int left, right;
    std::cin >> left >> right;

    // Relational operators ::= > >= < <= == !=
    //   Warning 1 - Equality and equals are similar and work in the same situations
    //   Warning 2 - Be very, very careful of floating point comparison for equality
    //                 Consider using >= or <= instead unless comparing to an integer
    //   Warning 3 - Strings compare by character values not by locale
    bool areEqual = left == right;
    std::cout << "areEqual = " << areEqual << std::endl;
    areEqual = left == right;
    std::cout << "areEqual = " << areEqual << std::endl;

    //areEqual = 10 == left;
    //areEqual = 10 = left;

    std::cout << "> " << (left > right) << std::endl;
    std::cout << "< " << (left < right) << std::endl;
    std::cout << ">= " << (left >= right) << std::endl;
    std::cout << "<= " << (left <= right) << std::endl;
    std::cout << "== " << (left == right) << std::endl;
    std::cout << "!= " << (left != right) << std::endl;

    float someValue = (10 / 3.0) * 3.0;
    float someOtherValue = (10 * 3.0) / 3.0;
    areEqual = someValue == someOtherValue;
    std::cout << areEqual << std::endl;

    // Comparison works but is case sensitive
    std::string name1 = "Bob";
    std::string name2 = "bob";
    std::cout << (name1 == name2) << std::endl;

    // To compare strings case insensitive use the strcmpi
    //  > 0 ::= left > right
    //  < 0 ::= left < right
    //  == 0 ::= left == right
    areEqual = _strcmpi(name1.c_str(), name2.c_str()) == 0;
}
