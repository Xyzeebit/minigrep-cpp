#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "args.h"

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
    bool case_sensitive = false;
    int line_count = 0;
    std::string pattern;
    std::string output_file;

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
    args::ArgParser cli;
    cli.helptext = "Usage: \
                       ./minigrep bog poem.txt";
    cli.version = "1.0";
    
    cli.option("out o", "minigrep.txt");
    cli.option("pattern r", "");
    cli.flag("case-sensitive i");

    cli.parse(argc, argv);

    auto size = cli.args.size();
    Minigrep mg;

    if(cli.found("i"))
    {
        mg.case_sensitive = true;
        //std::cout << "case sensitive\n";
    }
    if(cli.found("o"))
    {
        mg.output_file = cli.value("out");
        //std::cout << "write to file: "
            //<< mg.output_file << '\n';
    }
    if(cli.found("r"))
    {
        mg.pattern = cli.value("r");
        //std::cout << "Pattern: " 
            //<< mg.pattern << '\n';
    }
}
