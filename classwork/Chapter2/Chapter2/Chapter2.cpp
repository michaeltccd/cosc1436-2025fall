/*
 * Your Name
 * Lab #
 * COSC 1436 Fall 2025
 * 
 * Why are we here?
 */
//Preprocessor directive
#include <iostream>

int main()
{
    //Every statement in C++ must end with a semicolon
    // Statement = Anything that does something in the language
    
    //std::cout << "Hello World" << " " << "Your Name";
    //std::cout<<"Hello World"<<" "<<"Your Name";
    //std::cout << "Hello World" 
    //          << " " 
    //          << "Your Name";
    //std::cout << "Hello World";
    //std::cout << "Your Name";
    std::cout << "Hello World " << "Your Name" << std::endl;
    std::cout << "You are " << 20 << " years old" << std::endl;

    //Identical to << endl;
    std::cout << "Hello World " << "Your Name\n";

    //std::cout << "Hello World \"Your Name\"";
    std::cout << "C:\\Windows";
    //String literals "..."
    // "Whatever"
    // Escape sequence - special meaning to the compiler
    //     - Starts with \ followed by a character
    //   \n - newline
    //   \t - tab
    //   \" - double quote
    //   \\ - slash
    
    //Integer literals - one or more digits 

    //Floating point literals - one or more digits + fraction
    // 3.14159 or 3E10 -3E10 3E-10  3e10 -3e10

    // Variable - Named memory location where data is stored
    std::string name;
    name = "Name";
    std::cout << "Hello World " << name;

    //var-decl ::= T id;
    // type = defines what can be stored in the variable and in what format
    int age;
    age = 20;
    std::cout << "You are " << age << " years old";

    // Area of rectangle calculator
    // A = lw 
    std::string firstName;
    //int length;
    //int width;
    //length = 10;
    //width = 20;
    int length = 10, width = 20;       

    //Uninitialized variable - YOU MUST assign a value to a variable before you read it
    //int area;
    //area = 0;
    int area = 0;
    //area = length * width;

    std::cout << "Area of rectangle is " << area << std::endl;

    //2 different approaches to variable declarations
    // Block - all variables together
    //int radius, diameter;
    //std::string circleName;

    //Now I can use the variables

    //Inline - variables are declared just before they are used
    int radius, diameter;
    //Use radius, diameter

    std::string circleName;
    //Use circleName

    double pi;
    pi = 3.14159;

    char letterGrade;
    letterGrade = 'A';

    bool isPassing;
    isPassing = true;

    //Assignment is right associative
    //length = 100;
    //width = 100;
    length = width = 100;
}
