#include "functions.hpp"
#include "utilities.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

std::string Single(const std::string &data, const std::string &dna_input) {
    const std::vector<std::vector<std::string>> &information = RetrieveData(data);
    std::vector<int> vect_dna; //contains the # of consecutive dna for each word
    std::string result;
    vect_dna = CountDna(dna_input, information);
    std::cout<<"this is the value of vect dna at 2 " << vect_dna.at(2) << " it's supposed to be 2"<<std::endl;
    int match_founded = 0;
    for (unsigned int i = 1; i < information.size(); i++) { // skip first row of information
        if (Match(vect_dna, information.at(i))) { //matching between vect_dna and every row of info
            result = information.at(i).at(0);
            match_founded++;
        }
        result = "No match";
    }
    if (match_founded != 1) {
        result = "No match";
        return result;
    }
    return result;
}

std::vector<std::vector<std::string>> RetrieveData(const std::string &data) {
    std::ifstream ifs{data};
    if (!ifs.is_open()) { // if file is not opened
        std::cout << "Warning: was unable to open file" << std::endl;
    }
    std::vector<std::vector<std::string>> information;
    for(std::string line; std::getline(ifs, line); line = "") {
        information.push_back(utilities::GetSubstrs(line,','));
    }
    return information;
}

std::vector<int> CountDna(const std::string &data, const std::vector<std::vector<std::string>> &word) { //word e.g: AGAC , data e.g: AGAGAAGA
    std::vector<int> result;
    for (unsigned int i = 1; i < word.at(0).size(); i++) { // e.g loops thru the 5 words in the first row
        std::string str = word.at(0).at(i); // str = dna sequence we need
        std::cout<<"this is str " <<  str.length() <<std::endl;
        bool consecutive = false;
        int max = 0;
        int count = 0;
        for (unsigned int j = 0; j < data.length(); j++) { // loops thru every character from input
            std::string current_sequence = data.substr(j, str.length());
            if (current_sequence == str) { // if the input from j to length of word == the str
                if (consecutive) {
                count ++;
                } else {
                    consecutive = true;
                    count = 1;
                }
                if (count > max) {
                    max = count;
                }
                j = j + str.length() - 1; // change value of j to the value aft accouting for length of word
            } else {
                consecutive = false;
                count = 0;
            }
        }
        result.push_back(max);
    }  
    return result;
}

bool Match(const std::vector<int> &dna_vect, const std::vector<std::string> &info_vect) {
    bool match_found = false;
    unsigned int number_of_matching_elements = 0;
    for (unsigned int i = 0; i < info_vect.size() - 1; i++) { // names, 2, 4, 6
        int integer = std::stoi(info_vect[i + 1]);
        // std::cout<<"dna_vect value" << dna_vect.at(i) <<std::endl;
        // std::cout<<"integer value" << integer <<std::endl;
        if (dna_vect[i] == integer) {
            number_of_matching_elements++;
        }
    }
    // std::cout<<"num of matching elements" << number_of_matching_elements <<std::endl;
    if (number_of_matching_elements == (info_vect.size() - 1)) {
        match_found = true;
    }
    return match_found;
}


