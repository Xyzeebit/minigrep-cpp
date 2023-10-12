#include <iostream>

struct Minigrep
{
    int line_number;
    std::string word;
    std::string path;
    std::string line;

    Minigrep(std::string filepath, std::string word_to_find) : path{filepath}, word{word_to_find}
    {}
};

int main(int argc, char* argv[])
{
    for(int i = 0; i < argc; ++i)
    {
        std::cout << argv[i];
    }
    std::cout << std::endl;
}
