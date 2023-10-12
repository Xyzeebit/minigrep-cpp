#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct Result
{
    int line;
    int position;
    std::string text;
};

struct Minigrep
{
    std::string word;
    std::string path;
    std::vector<Result> lines;
    std::string text;

    Minigrep(std::string word_to_find, std::string filepath) : path{filepath}, word{word_to_find}
    {}

    void search(const std::string w, const std::string t)
    {
    }

    void run()
    {
        std::ifstream file(path, std::ios_base::in);
        if(file.is_open())
        {
            while(file.good())
            {
                std::getline(file, text);
                search(word, text);
            }
            file.close();
        }
    }
};

int main(int argc, char* argv[])
{
    if(argc >= 2)
    {
        Minigrep mg {argv[1], argv[2]};
        mg.run();
    }
    else
    {
        std::cout << "Not enough arguments pass into program" << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "./minigrep hello helloword.txt" << std::endl;
    }
}
