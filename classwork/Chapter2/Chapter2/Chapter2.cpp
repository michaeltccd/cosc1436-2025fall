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

}
