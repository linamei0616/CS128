#include "functions.hpp"
#include <string>
#include <iostream>
#include <vector>
// Your function definitions should go in this source file.

bool InvalidHawaiianWord(std::vector<char> vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        if (vec.at(i) != 'a' && vec.at(i) != 'e' && vec.at(i) != 'i' && vec.at(i) != 'o'
         && vec.at(i) != 'u' && vec.at(i) != 'p' && vec.at(i) != 'k' && vec.at(i) != 'h'
         && vec.at(i) != 'l' && vec.at(i) != 'm' && vec.at(i) != 'n' && vec.at(i) != 'w'
         && vec.at(i) != ' ' && vec.at(i) != '-' && vec.at(i) != '\'') {
            return true;
        }
    }
    return false;
}
std::vector<char> ConvertingToVector(std::string word) {
    std::vector<char> converted_vector;
    std::string str;
    for (unsigned int i = 0; i < word.length(); i++) {
        str += std::tolower(word[i]);
    }
    for (unsigned int i = 0; i < str.length(); i++) {
        converted_vector.push_back(str[i]);
        // std::cout << word[i] << std::endl;
    }
    return converted_vector;
}
bool CheckVConsonant(std::vector<char> vec) {
    unsigned int x = 0;
    for (unsigned int i = 0; i < vec.size(); i++) {
        if (((vec[0] == 'e') || (vec[0] == 'i')) && (vec[1] == 'w')) {
            x++;
            break; // if it's supposed to be a v sound
        }
    }
    return (x>0);
}
std::string CheckConsonants(char c) {
    if (c == 'm') {
        return "m";
    }
    if (c == 'k') {
        return "k";
    }
    if (c == 'h') {
        return "h";
    }
    if (c == 'n') {
        return "n";
    }
    if (c == 'l') {
        return "l";
    }
    if (c == 'p') {
        return "p";
    }
    return ""; 
}
std::string CheckVowel(char c) {
    if (c == 'a') {
        return "ah";
    }
    if (c == 'e') {
        return "eh";
    }
    if (c == 'i') {
        return "ee";
    }
    if (c == 'o') {
        return "oh";
    }
    if (c == 'u') {
        return "oo";
    }
    if (c == '-') {
        return "-";
    }
    if (c == ' ') {
        return " ";
    }
    if (c == '\'') {
        return "\'";
    }
    return "";
}
std::string CheckVowelGroups(std::vector<char> vec) {
    if ((vec[0] == 'a') && ((vec[1] == 'i') || (vec[1] == 'e'))) {
        return "eye";
    }
    if (((vec[0] == 'a') && ((vec[1] == 'o') || (vec[1] == 'u')))
    || (vec[0] == 'o' && vec[1] == 'u')) {
        return "ow";
    }
    if (vec[0] == 'e' && vec[1] == 'i') {
        return "ay";
    }
    if (vec[0] == 'e' && vec[1] == 'u') {
        return "eh-oo";
    }
    if (vec[0] == 'i' && vec[1] == 'u') {
        return "ew";
    }
    if (vec[0] == 'o' && vec[1] == 'i') {
        return "oy";
    }
    if (vec[0] == 'u' && vec[1] == 'i') {
        return "ooey";
    }
    return "";
}
std::string AddingDash(std::vector<char> vec) {
    if ((Vowel(vec[0])) && (!(VowelGroups(vec)) && ((vec[1] != '\'') && (vec[1] != ' ') && vec[0] != '\'')
    && vec.size() > 1 && vec[0] != ' ' && vec[0] != '\'')) {
        return "-";
    }
    if (((VowelGroups(vec)) && ((vec[1] != '\'') && (vec[1] != ' ') && vec[0] != '\'')
    && vec.size() > 2 && vec[0] != ' ' && vec[0] != '\'')) {
        return "-";
    }
    return "";
}
std::vector<char> RemovingElements(std::vector<char> vec) {
    int x = 0;
    if (WConsonants(vec) && x == 0) {
      vec.erase(vec.begin());
      x++;
    }
    if (Consonants(vec[0]) && x == 0) {
      vec.erase(vec.begin());
      x++;
    }
    if (vec.size() > 1) {
        if (VowelGroups(vec) && x == 0) {
        vec.erase(vec.begin());
        vec.erase(vec.begin());
        x++;
        }
    }
    if (Vowel(vec[0]) && x == 0) {
      vec.erase(vec.begin());
      x++;
    }
    return vec;
  }

bool Consonants(char c) {
    return (c == 'm' || c == 'k' || c == 'h' || c == 'n' || c == 'l' || c == 'm' || c == 'p');
}
bool WConsonants(std::vector<char> vec) {
    return (((vec[0] == 'e') || (vec[0] == 'i')) && (vec[1] == 'w')) || (vec[0] == 'w');
}
bool VowelGroups(std::vector<char> vec) {
    return ((vec[0] == 'a') && ((vec[1] == 'i') || (vec[1] == 'e'))) 
    || (((vec[0] == 'a') && ((vec[1] == 'o') || (vec[1] == 'u')))
    || (vec[0] == 'o' && vec[1] == 'u'))
    || (vec[0] == 'e' && vec[1] == 'i')
    || (vec[0] == 'e' && vec[1] == 'u')
    || (vec[0] == 'i' && vec[1] == 'u')
    || (vec[0] == 'o' && vec[1] == 'i')
    || (vec[0] == 'u' && vec[1] == 'i');
}
bool Vowel(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == ' ' || c == '\'');
}

