#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include "args.h"

using std::regex_constants::ECMAScript;
using std::regex_constants::icase;

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
        if(!pattern.empty())
        {
            std::regex rgx{pattern};
            std::smatch smatch;
            
            if(case_sensitive)
            {
                if(std::regex_search(t, smatch, rgx))
                {
                    for(auto i = 0; i < smatch.size(); ++i)
                    {
                        Result r;
                        r.line = c;
                        r.position = smatch.position(i);
                        r.word = w;
                        r.text = t;
                        lines.push_back(r);
                    }
                }
            }
            else
            {
                std::regex irgx(pattern, ECMAScript | icase);
                if(std::regex_search(t, smatch, irgx))
                {
                    for(auto i = 0; i < smatch.size(); ++i)
                    {
                        Result r;
                        r.line = c;
                        r.position = smatch.position(i);
                        r.word = w;
                        r.text = t;
                        lines.push_back(r);
                    }
                }
            }
        }
        else
        {
            std::cout << w << " " << t << '\n';
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
    }
    if(cli.found("o"))
    {
        mg.output_file = cli.value("out");
    }
    if(cli.found("r"))
    {
        mg.pattern = cli.value("r");
    }
    if(size == 1)
    {
        mg.path = cli.args[0];
    }
    else if(size == 2)
    {
        mg.word = cli.args[0];
        mg.path = cli.args[1];
    }
    else
    {
        std::cout << "not enough arguments supplied" << std::endl;
    }
    const bool ok = mg.run();
    if(!ok)
    {
        std::cout << "an error occurred\n";
    }
}
