#include <iostream>
#include <string>

struct Minigrep
{
    int line_number;
    std::string word;
    std::string path;
    std::string line;

    Minigrep(std::string word_to_find, std::string filepath) : path{filepath}, word{word_to_find}
    {}
};

int main(int argc, char* argv[])
{
    if(argc >= 2)
    {
        std::cout << "Word: " << argv[1]
            << " File path: " << argv[2]
            << std::endl;
    }
    else
    {
        std::cout << "Not enough arguments pass into program" << std::endl;
        std::cout << "Usage" << std::endl;
        std::cout << "./minigrep hello helloword.txt" << std::endl;
    }
}
