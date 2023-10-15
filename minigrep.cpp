#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct Result
{
    int line;
    int position;
    std::string text;
    std::string word;
};

struct Minigrep
{
    std::string word;
    std::string path;
    std::vector<Result> lines;
    std::string text;
    int line_count = 0;

    Minigrep(std::string word_to_find, std::string filepath) : path{filepath}, word{word_to_find}
    {}

    void search(const std::string w, const std::string t, const int c)
    {
        auto found = t.find(w);
        if(found != std::string::npos)
        {
            Result r;
            r.text = t;
            r.word = w;
            r.position = found;
            r.line = c;
            lines.push_back(r);
        }
    }

    bool run()
    {
        std::ifstream file(path, std::ios_base::in);
        if(file.is_open())
        {
            while(file.good())
            {
                std::getline(file, text);
                ++line_count;
                search(word, text, line_count);
            }
            file.close();
            return true;
        }
        else 
        {
            return false;
        }
    }
};

int main(int argc, char* argv[])
{
    if(argc >= 2)
    {
        Minigrep mg {argv[1], argv[2]};
        const bool ok = mg.run();

        if(ok)
        {
            if(mg.lines.size() > 0)
            {
                for(auto& e : mg.lines)
                {
                    std::cout << "Text: "
                        << e.text << '\n'
                        << "Word: " << e.word
                        << '\n' << "Line No: "
                        << e.line << '\n'
                        << "Column No: "
                        << e.position << '\n';
                }
            }
            else
            {
                std::cout << argv[1] << " not found in " << argv[2] << std::endl;
            }
        }
        else 
        {
            std::cout << "Unable to read from file " << argv[2] << std::endl;
        }
        
        std::cout << std::endl;
    }
    else
    {
        std::cout << "Not enough arguments pass into program" << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "./minigrep hello helloworld.txt" << std::endl;
    }
}
