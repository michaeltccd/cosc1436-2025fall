/*
 * Chapter 4
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
    //double userRating;        //Optional, 1.0-10.0
    bool isClassic;             //Required, false
    std::string genres;         //Optional (comma separated list of genres)
};

int main()
{
    //Demo prefix/postfix-increment/decrement
    /*std::cout << "Enter a value: ";
    int number;
    std::cin >> number;

    // Prefix increment ++x ::= x += 1; return x
    // Prefix decrement --x ::=  x -= 1; return x
    // Postfix increment x++ ::= temp = x; x += 1; return temp
    // Postfix decrement x-- ::= temp = x; x -= 1; return temp
    std::cout << "Prefix (++x) = " << ++number << ", x = " << number << std::endl;
    std::cout << "Prefix (--x) = " << --number << ", x = " << number << std::endl;
    std::cout << "Postfix (x++) = " << number++ << ", x = " << number << std::endl;
    std::cout << "Postfix (x--) = " << number-- << ", x = " << number << std::endl;*/

    //Demo nested loops 10x12 = 120
    //   1 2 3 4 5
    // 1 1 2 3 4 5
    // 2 2 4 6 8 10
    // 3 3 6 9 12 15
    /*for (int rows = 1; rows <= 100; ++rows)
    {
        for (int cols = 1; cols <= 50; ++cols)
        {
            std::cout << std::setw(4) << (rows * cols);
        }

        std::cout << std::endl;
    }*/

    // Looping construct
    //    while-statement ::= while (Eb) S;
    //      Pre-test, evaluates Eb and executes S if true
    //      S executed zero or more times
    // 
    //Display main menu
    bool done = false;
    do //while (!done)
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

        //Validate input
        //if (choice == "A" || choice == "a")
        //{
        //    //TODO: Move add code here
        //    std::cout << "Add not implemented" << std::endl;
        //} else if (choice == "V" || choice == "v")
        //{
        //    //TODO: Movie view code here
        //    std::cout << "View not implemented" << std::endl;
        //} else if (choice == "E" || choice == "e")
        //{
        //    std::cout << "Edit Not implemented" << std::endl;
        //} else if (choice == "D" || choice == "d")
        //{
        //    std::cout << "Delete Not implemented" << std::endl;
        //} else if (choice == "Q" || choice == "q")
        //{
        //    return 0;
        //} else
        //{
        //    std::cout << "Invalid choice" << std::endl;
        //};
        // Switch :: Replacement for an if-else-if where each if condition is Expr == Value
        // switch-statement ::= switch (E) { case-statement* [ default-statement ] }
        // case-statement ::= case E : S 
        // default-statement ::= default : S
        // break-statement ::= break ;
        // 
        // Switch expression must be either char or an integral expression
        // case labels must be:
        //   - Compile time constants (e.g. literal, simple expression)
        //   - Unique within switch
        // Case statements fall through to next case unless break statement used
        // Default statement executes if no cases match expression
        switch (choice)
        {
            case 'A': //std::cout << "Add not implemented" << std::endl; break;
            case 'a': std::cout << "Add not implemented" << std::endl; done = true; break;

            case 'V':
            case 'v':
            {
                //Declaring a variable
                //switch-statement
                std::cout << "View not implemented" << std::endl;
                done = true;
                break;
            }

            case 'D':
            case 'd': std::cout << "Delete not implemented" << std::endl; done = true; break;

            case 'E':
            case 'e': std::cout << "Edit not implemented" << std::endl; done = true; break;

            case 'Q':
            case 'q': return 0;

            default: std::cout << "Invalid choice" << std::endl; break;
        };
    } while (!done);

    //int id;
    Movie movie = {0};

    //Get movie details
    std::cout << "Enter movie title: ";
    std::cin.ignore();
    std::getline(std::cin, movie.title);

    //Title is required
    //bool isEmpty = title == "";
    //if (isEmpty)
    while (movie.title == "")
    {
        std::cout << "Title is required" << std::endl;
        std::getline(std::cin, movie.title);
    }

    std::cout << "Enter the run length (in minutes): ";
    /*runLength = -1;
    while (runLength < 0)
    {
        std::cin >> runLength;
        if (runLength < 0)
            std::cout << "ERROR: Run length must be at least 0" << std::endl;
    }*/
    //std::cin >> runLength;
    do //  while (runLength < 0)
    {           
        std::cin >> movie.runLength;

        //Error
        if (movie.runLength < 0)
        {
            std::string message = "Run length must be at least 0";
            std::cout << "ERROR: " << message << std::endl;
        }

        //std::cin >> runLength;
    } while (movie.runLength < 0);

    std::cout << "Enter the release year (1900-2100): ";
    std::cin >> movie.releaseYear;
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
    while (movie.releaseYear < 1900 || movie.releaseYear > 2100)
    {
        std::cout << "Release year must be between 1900 and 2100" << std::endl;
        //releaseYear = 1900;
        std::cin >> movie.releaseYear;
    }

    std::cout << "Enter the optional description: ";
    std::cin.ignore();
    std::getline(std::cin, movie.description);

    // Validate userRating
    /*std::cout << "Enter the optional user rating (1.0-10.0): ";
    std::cin >> userRating;
    if (userRating < 1.0 || userRating > 10.0)
    {
        std::cout << "Rating must be between 1.0 and 10.0" << std::endl;
        userRating = 1.0;
    }*/
    /*if (userRating < 1.0)
    {
        std::cout << "Rating must be between 1.0 and 10.0" << std::endl;
        userRating = 1.0;
    } else if (userRating > 10.0)
    {
        std::cout << "Rating must be between 1.0 and 10.0" << std::endl;
        userRating = 1.0;
    }*/

    // Genres, up to 5
    //done = false;
    //int count = 0;
    //while (!done && count < 5)
    //{
    //    std::string genre;

    //    std::cout << "Enter the genre (or blank to continue): ";        
    //    std::getline(std::cin, genre);
    //    if (genre == "")
    //        done = true;
    //    else
    //        genres = genres + ", " + genre;

    //    ++count;  // or, count++
    //}
    done = false;

    // for-statement ::= for (init-expr ; test-expr ; update-expr ) S ;
    //   Used for fixed iterations, equivalent to 
    //      init-expr;
    //      while (test-expr) { S; update-expr; }
    //   Pre-test so S runs zero or more times
    //   init-expr can be a variable declaration to reduce scope (preferred)
    // break-statement ::= break ;
    //   Usable in loops, exits the loop immediately
    // continue-statement ::= continue ;
    //   Usable in loops, exits the current iteration of a loop and evaluates condition again normally
    //int index = 0;
    //for (count = 0; count < 5 && !done; ++count)
    //for (index = 0; index < 5; ++index)
    for (int index = 0; index < 5; ++index)
    {
        std::string genre;

        std::cout << "Enter the genre (or blank to continue): ";
        std::getline(std::cin, genre);
        if (genre == "")
            //done = true;
            //index = 5;
            break;
        else if (genre == " ")
            continue;
        
        movie.genres = movie.genres + ", " + genre;

        //++count;  // or, count++
    }

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

    //Infinite loop
    //while (true) {}
    //for (;;) {}

    /*if (_strcmpi(input.c_str(), "Y") == 0)
        isClassic = true;
    if (_strcmpi(input.c_str(), "N") == 0)
        isClassic = false;
    else
        std::cout << "You must enter either Y or N";*/
    //done = false;
    //while (!done)
    while (true)
    {        
        if (_strcmpi(input.c_str(), "Y") == 0)
        {
            movie.isClassic = true;
            //done = true;
            break;
        } else if (_strcmpi(input.c_str(), "N") == 0)
        {
            movie.isClassic = false;
            //done = true;
            break;
        } else {
            std::cout << "You must enter either Y or N";

            std::cin >> input;
        }
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
    //std::cout << "User Rating = " << userRating << std::endl;
    //std::cout << "Is Classic? " << isClassic << std::endl;
    /*if (isClassic)
        std::cout << "Is Classic? Yes" << std::endl;
    else
        std::cout << "Is Classic? No" << std::endl;*/
    /*std::string classicIndicator;
    if (isClassic)
        classicIndicator = "Yes";
    else
        classicIndicator = "No";*/
    //Conditional_expression ::= Eb ? Et : Ef
    //std::string classicIndicator = isClassic ? "Yes" : "No";
    std::cout << "Is Classic? " << (movie.isClassic ? "Yes" : "No") << std::endl;
    if (movie.description != "")
        std::cout << movie.description << std::endl;
    std::cout << std::endl;
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
