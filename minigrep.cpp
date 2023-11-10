#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>
#include "args.h"

using std::regex_constants::ECMAScript;
using std::regex_constants::icase;

struct Result
{
    int line;
    int position;
    std::string text;
    std::string word;
    std::string output;

    operator const char*()
    {
        std::ostringstream result;
        result << "found on line: " << line
            << ", position: " << position
            << '\n' << text << '\n';
        output = result.str();
        return output.c_str();
    }
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
                match(w, t, smatch, rgx, c);
            }
            else
            {
                std::regex irgx(pattern, ECMAScript | icase);
                match(w, t, smatch, irgx, c);
            }
        }
        else
        {
            std::regex rgx{word};
            std::smatch smatch;
            match(word, t, smatch, rgx, c);
        }
    }

    void match(const std::string pattern, const std::string text, std::smatch smatch, std::regex rgx, int counter)
    {
        if(std::regex_search(text, smatch, rgx))
        {
            for(auto i = 0; i < smatch.size(); ++i)
            {
                Result r;
                r.line = counter;
                r.position = smatch.position(i);
                r.word = pattern;
                r.text = text;
                lines.push_back(r);
            }
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

    void write_to_file(Result r)
    {
        std::ofstream file(output_file, std::ios_base::out|std::ios_base::app);
        if(file.is_open())
        {
            file << r;
            file.close();
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
        //search word should override pattern
        mg.pattern = cli.args[0];
    }
    else
    {
        std::cout << "not enough arguments supplied" << std::endl;
    }
    const bool ok = mg.run();
    if(ok)
    {
        for(auto& e : mg.lines)
        {
            if(cli.found("o"))
            {
                mg.write_to_file(e);
            }
            else
            {
                std::cout << e << std::endl;
            }
        }
    }
    else
    {
        std::cout << "an error occurred\n";
    }
}
