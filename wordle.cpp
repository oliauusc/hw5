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
void wordleHelper(std::string&,
    std::string& ,
    const std::set<std::string>&,
    std::set<std::string>&,
    int, int);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::string currentWord = in;

    int lettersNotIn = 0;
    for (int i = 0; i<currentWord.size(); i++) {
      if (currentWord[i] == '-') lettersNotIn++;
    } 

    std::string floatTemp = floating;
    std::set<std::string> answers;
    wordleHelper(currentWord, floatTemp, dict, answers, 0, lettersNotIn);
    return answers;
}


// Define any helper functions here
void wordleHelper(
    std::string& currentWord,
    std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& answers,
    int index,
    int lettersNotIn)
{
    // Add your code here
    if (lettersNotIn < floating.size()) return;

    if (index == currentWord.size()) {
        if ((floating.empty())  && (dict.find(currentWord) != dict.end()))
            answers.insert(currentWord);
        return;
    }

    else if (currentWord[index] != '-') {
        wordleHelper(currentWord, floating, dict, answers, index + 1, lettersNotIn);
        return;
    }

    else {
        // std::string lettersToTry;
        // if (!floating.empty()) {
        //     for (char ch : floating) lettersToTry+=(ch);
        // } 
        // else {
        //     for (char ch = 'a'; ch <= 'z'; ++ch) 
        //         lettersToTry+=(ch);
        // }

        for (char ch = 'a'; ch <= 'z'; ++ch) 

        // for (char ch : lettersToTry) 
        {
            std::string nextWord = currentWord;
            std::string newFloating = floating;

            nextWord[index] = ch;

        int pos = newFloating.find(ch);
        if (pos != std::string::npos) {
            newFloating.erase(pos, 1);
            wordleHelper(nextWord, newFloating, dict, answers, index + 1, lettersNotIn-1);
        }
        else wordleHelper(nextWord, floating, dict, answers, index + 1, lettersNotIn-1);
        }
    }
}


        // for (char letter = 'a'; letter <= 'z'; ++letter)
        // {
        //     if (floatsNotIn == lettersNotIn && (floating.find(letter) == std::string::npos)) {
        //         continue;
        //     }
        //     currentWord[index] = letter;

        //     if (floating.find(letter) != std::string::npos) {
        //         std::string newFloating = floating;
        //         int newFloatsNotIn  = floatsNotIn;
        //         newFloatsNotIn = newFloatsNotIn-1;
        //         newFloating[floating.find(letter)] = '-';
        //         wordleHelper(currentWord, newFloating, dict, answers, index + 1, lettersNotIn-1, newFloatsNotIn);
        //     } 

        //     else wordleHelper(currentWord, floating, dict, answers, index + 1, lettersNotIn-1, floatsNotIn);

        //     // else wordleHelper(currentWord, newFloating, dict, answers, index + 1, lettersNotIn-1, newFloatsNotIn);
        // }
        // currentWord[index] = '-';
//     }
// }
    