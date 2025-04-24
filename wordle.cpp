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
// int checkFloats(std::string& currentWord, const std::string& floating) 
// {
//     int floatsNotIn;
//     for (int i = 0; i<floating.size(); i++) {
//         if (currentWord.find(floating[i]) == -1) floatsNotIn++;
//     } 
//     return floatsNotIn;
// }

void wordleHelper(std::string&,
    std::string& ,
    const std::set<std::string>&,
    std::set<std::string>&,
    int, int, int);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::string currentWord = in;

    int lettersNotIn = 0;
    int floatsNotIn = 0;

    for (int i = 0; i<currentWord.size(); i++) {
      if (currentWord[i] == '-') lettersNotIn++;
    } 

    for (int i = 0; i<floating.size(); i++) {
            if (currentWord.find(floating[i]) == -1) floatsNotIn++;
            } 

    std::string floatTemp = floating;

    std::set<std::string> answers;
    wordleHelper(currentWord, floatTemp, dict, answers, 0, lettersNotIn, floatsNotIn);
    return answers;
}



// Define any helper functions here
void wordleHelper(
    std::string& currentWord,
    std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& answers,
    int index,
    int lettersNotIn,
    int floatsNotIn)
{
    // Add your code here
    if (index == currentWord.size()) {
        // int floatIn;
        // std::string tempWord = currentWord;

        if (floatsNotIn != 0) return;
        // for (int i = 0; i<floating.size(); i++) {
        //     floatIn = tempWord.find(floating[i]);
        //     if (floatIn == -1) return;
        //     else tempWord[floatIn] = '1';
        // }
        // std::cout << floatIn << " " << currentWord;

        if ((dict.find(currentWord) != dict.end()))
            answers.insert(currentWord);
        
        return;
    }

    else if (currentWord[index] != '-') {
        wordleHelper(currentWord, floating, dict, answers, index + 1, lettersNotIn, floatsNotIn);
    }

    else {
        for (char letter = 'a'; letter <= 'z'; ++letter)
        {
            if (floatsNotIn == lettersNotIn) {
              if (floating.find(letter) == -1)
                continue;
            }
            
            currentWord[index] = letter;
            int newFloatsNotIn  = floatsNotIn;
            std::string newFloating = floating;

            if (floating.find(letter) != -1) {
              newFloatsNotIn = floatsNotIn-1;
              newFloating[floating.find(letter)] = '-';
            } 

            if (lettersNotIn-1 < newFloatsNotIn)
              continue;

            else wordleHelper(currentWord, newFloating, dict, answers, index + 1, lettersNotIn-1, newFloatsNotIn);
        }
        currentWord[index] = '-';
    }
}
    