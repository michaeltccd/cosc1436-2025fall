#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

void CharDemo()
{
    //Character sets
    //  ANSI - 1 byte, char in C++, string for string
    //  Unicode - 2 bytes, wchar_t in C++, wstring for string
    char ansiCharacter = 'A';
    wchar_t unicodeCharacter = 'A';

    std::string ansiString = "Bob";
    std::wstring unicodeString = L"Bob";

    //Variants - Unicode variants of fixed size
    //char8_t char8Byte;
    char16_t char16Byte;
    char32_t char32Byte;
}

void CharFunctionDemo()
{
    std::string input;

    std::cout << "Enter a string: ";
    std::getline(std::cin, input);

    std::cout << "Character " 
        << std::setw(15) << "Letter? " 
        << std::setw(10) << "Digit? " 
        << std::setw(10) << "Letter/Digit? "
        << std::setw(10) << "Lowercase? "
        << std::setw(10) << "To Lower "         
        << std::setw(10) << "Uppercase? "
        << std::setw(10) << "To Upper "
        << std::setw(10) << "Space? " << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    //Enumerate the characters of the string
    for (int index = 0; index < input.length(); ++index)
    {
        char ch = input[index];

        // All char functions are from C and therefore accept and return an int, not a char
        // Typecast back to char
        std::cout << ch 
            << std::setw(15) << isalpha(ch) 
            << std::setw(10) << isdigit(ch)
            << std::setw(10) << isalnum(ch)
            << std::setw(10) << islower(ch)
            << std::setw(10) << (char)tolower(ch)
            << std::setw(10) << isupper(ch)
            << std::setw(10) << (char)toupper(ch)
            << std::setw(10) << isspace(ch)
            << std::endl;
    };
}

void UnicodeCharFunctionDemo()
{
    std::wstring input;

    std::cout << "Enter a string: ";
    std::getline(std::wcin, input);

    std::cout << "Character "
        << std::setw(15) << "Letter? "
        << std::setw(10) << "Digit? "
        << std::setw(10) << "Letter/Digit? "
        << std::setw(10) << "Lowercase? "
        << std::setw(10) << "To Lower "
        << std::setw(10) << "Uppercase? "
        << std::setw(10) << "To Upper "
        << std::setw(10) << "Space? " << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    //Enumerate the characters of the string
    for (int index = 0; index < input.length(); ++index)
    {
        wchar_t ch = input[index];

        // All char functions are from C and therefore accept and return an int, not a char
        // Typecast back to char
        std::cout << ch
            << std::setw(15) << iswalpha(ch)
            << std::setw(10) << iswdigit(ch)
            << std::setw(10) << iswalnum(ch)
            << std::setw(10) << iswlower(ch)
            << std::setw(10) << (char)towlower(ch)
            << std::setw(10) << iswupper(ch)
            << std::setw(10) << (char)towupper(ch)
            << std::setw(10) << iswspace(ch)
            << std::endl;
    };
}

void CStringDemo()
{
    //Implicit sizing makes sense here
    char title[] = "My Program";
    char title2[] = {'M', 'y', ' '};

    //Normally use char* for C strings
    // or char const* for C strings that are const
}

void CStringFunctions()
{
    //Always init C strings to null
    const int MaxInputSize = 100;
    char input[MaxInputSize+1] = {0};
    char output[MaxInputSize+1] = {0};

    std::cout << "Input a value: ";
    std::cin >> input;

    //Common C string functions - #include <cstring>
    int len = strlen(input);  //strlen(string) size_t :: returns size of string

    //Copying a string
    // std::string str;
    // str = "Hello";
    strcpy(output, input);   // strcpy(target, source) :: Copies source to target
                             // It will null terminate the target string
                             // If output is exactly the length of input then no NULL is written
                             // If output is smaller than input then it overwrites memory (security vuln)
    strncpy(output, input, MaxInputSize); //Strcpy(target, source, maxsize) :: Copies up to maxSize characters
                           
    //Concat a string
    // str += " Done";
    strcat(output, " Done");  // Concats the second string to the end of the first string
    strncat(output, " Done", MaxInputSize);  

    //Comparison
    //  str1 == str2
    strcmp(output, input); // Compares 2 strings, case sensitive (>0, =0, <0)
    _stricmp(output, input); //Case insensitive
    strncmp(output, input, MaxInputSize);  // Compares 2 strings up to max len

    char* pos = strstr(input, "a"); // Find substring in string, returns pointer to start of substring or nullptr

    //Conversion
    int value = atoi("123");  // Parses string to int
    value = atoi("123abc");  // 123
    value = atoi("abc");  // 0
    // atol -> Parses a string to a long
    // atof -> Parses a string to a floating point value (double)

    char* end;
    value =strtol("123abc", &end, 0); //Parses a string to a long, using the base given
                                      //And returns the last character parsed
}

void CPlusPlusStringFunctions()
{
    std::string input, output;

    std::cout << "Enter a value: ";
    std::cin >> input;

    //Copying a string
    output = input;

    //Concat a string
    output += " done";

    //Compare
    bool isEqual = input == output;

    //Length of the string
    int len = input.length();  //strlen(input)
    bool isEmpty = input == "";
    isEmpty = input.length() == 0;
    isEmpty = input.empty();   //Preferred

    //Resetting a string
    output = "";   // strcpy(output, "");
    output.clear();   // Clears a string

    //Modification
    output.append(" Done");  //strcat(output, " Done");
    //output.insert()

    //Find strings
    input.find("a");   //strstr(input, "a");  /// iterator

    std::string sub = input.substr(10);  //Gets the characters starting at index, up to the given length)
    sub = input.substr(10, 4);

    const char* ptr = input.c_str();  //Gets the C string version of the C++ string
}

int main()
{    
    CharFunctionDemo();
}
