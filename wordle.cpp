#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helper(std::string& word, const std::string& in, std::string floating, size_t n, std::set<std::string>& str, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> str;
    std::string word = in;
    std::string f = floating;
    size_t n = 0;

    helper(word, in, f, n, str, dict);

    return str;
}

// Define any helper functions here
void helper(std::string& word, const std::string& in, std::string floating, size_t n, std::set<std::string>& str, const std::set<std::string>& dict)
{
    if (n == in.length())
    {
        if (floating.empty() && dict.find(word) != dict.end())
        {
            str.insert(word);
        }
        return;
    }

    if (in[n] == '-') // Is a Blank
    {
        if (in.length() - n < floating.size()) return;

        if (in.length() - n == floating.size())
        {
            for (size_t i = 0; i < floating.size(); ++i)
            {
                std::string newFloating = floating;

                word[n] = floating[i];
                newFloating.erase(newFloating.begin() + i);
                helper(word, in, newFloating, n + 1, str, dict);
            }
        }
        else
        {
            for (char l = 'a'; l <= 'z'; ++l)
            {
                std::string newFloating = floating;
                size_t idx = newFloating.find(l);

                word[n] = l;
                
                if (idx != std::string::npos)
                {
                    newFloating.erase(newFloating.begin() + idx);
                }

                helper(word, in, newFloating, n + 1, str, dict);
            }
        }
    }
    else // Not a Blank
    {
        word[n] = in[n];
        helper(word, in, floating, n + 1, str, dict);
    }
}
