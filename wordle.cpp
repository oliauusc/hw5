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
    const std::string& ,
    const std::set<std::string>&,
    std::set<std::string>&,
    int);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::string currentWord = in;

    std::set<std::string> answers;
    wordleHelper(currentWord, floating, dict, answers, 0);
    return answers;
}

// Define any helper functions here
void wordleHelper(
    std::string& currentWord,
    const std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& answers,
    int index)
{
    // Add your code here
    if (index > currentWord.size()) {
        int floatIn;
        std::string tempWord = currentWord;

        for (int i = 0; i<floating.size(); i++) {
            floatIn = tempWord.find(floating[i]);
            if (floatIn == -1) return;
            else tempWord[floatIn] = '1';
        }
        // std::cout << floatIn << " " << currentWord;

        if ((dict.find(currentWord) != dict.end()))
            answers.insert(currentWord);
        
        return;
    }

    else if (currentWord[index] != '-') {
        // std::cout << "inpalce, next";
        wordleHelper(currentWord, floating, dict, answers, index + 1);
    }
    else {
        for (char letter = 'a'; letter <= 'z'; ++letter)
        {
            currentWord[index] = letter;

            int floatsNotIn = 0;
            int lettersNotIn = 0;



            for (int i = 0; i<floating.size(); i++) {
            if (currentWord.find(floating[i]) == -1) floatsNotIn++;
            }   

            for (int i = 0; i<currentWord.size(); i++) {
            if (currentWord[i] == '-') lettersNotIn++;
            } 

            if (lettersNotIn < floatsNotIn)
            continue;

            else wordleHelper(currentWord, floating, dict, answers, index + 1);

            // std::cout << "next";
        }
        currentWord[index] = '-';
    }
}
    