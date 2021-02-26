#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "../includes/constants.h"
#include "../includes/array_functions.h"
#include "../includes/fileio.h"


namespace KP{
void clear(std::vector<constants::entry>  &entries){
	entries.clear();
}

int getSize(std::vector<constants::entry>  &entries){
return (int)entries.size();
}

std::string getWordAt(std::vector<constants::entry>  &entries, int i){
	if(i < (int)entries.size() - 1){
		return entries.at(i).word;
	}
	else{
		return entries.at(entries.size()-1).word;

	}
}

int getNumbOccurAt(std::vector<constants::entry>  &entries,int i){
	if(i < (int)entries.size() - 1){
			return entries.at(i).number_occurences;
		}
		else{
			return entries.at(entries.size()-1).number_occurences;
		}
}

bool processFile(std::vector<constants::entry>  &entries,std::fstream &myfstream){
	std::string line;
	while(!myfstream.eof()){
		std::getline(myfstream,line);
		processLine(entries, line);
	}

	closeFile(myfstream);
	return true;
}

void processLine(std::vector<constants::entry>  &entries,std::string &myLine){
	std::stringstream ss(myLine);
	std::string tempToken;
	while(std::getline(ss, tempToken, constants::CHAR_TO_SEARCH_FOR)){
		processToken(entries, tempToken);
	}

}

void processToken(std::vector<constants::entry>  &entries,std::string &token){
	const int NUMBER_CHARS_TO_ERASE = 1;
	std::size_t found = token.find('\r');
	if (found!=std::string::npos)
		token.erase(found,NUMBER_CHARS_TO_ERASE);
	found = token.find('.');
	if (found!=std::string::npos)
		token.erase(found,NUMBER_CHARS_TO_ERASE);

	found = token.find(' ');
	if (found!=std::string::npos)
		token.erase(found,NUMBER_CHARS_TO_ERASE);

	found = token.find(',');
	if (found!=std::string::npos)
		token.erase(found,NUMBER_CHARS_TO_ERASE);
	if (token.empty())
			return;
	std::string big = token;
	std::transform(big.begin(), big.end(), big.begin(),
			::toupper);
	int flag = 0;
	for (int var = 0; var < (int)entries.size(); ++var) {
		if(entries.at(var).word_uppercase == big){
			entries.at(var).number_occurences +=1;
			flag = 1;
		}
	}
	if(flag == 0){
		constants::entry nentry;
		nentry.word = token;
		nentry.word_uppercase = big;
		nentry.number_occurences = 1;
		entries.push_back(nentry);
	}
}

bool comp_oc(constants::entry &s1, constants::entry &s2){
	return s1.number_occurences>s2.number_occurences;
}
bool comp_word(constants::entry &s1, constants::entry &s2){
	return s1.word_uppercase<s2.word_uppercase;
}

bool desc_comp_word(constants::entry &s1, constants::entry &s2){
	return s1.word_uppercase>s2.word_uppercase;
}

void sort(std::vector<constants::entry>  &entries, constants::sortOrder so){
	switch (so){
		case constants::NUMBER_OCCURRENCES:
			std::sort(entries.begin(), entries.end(), comp_oc);
			break;
		case constants::ASCENDING:
					std::sort(entries.begin(), entries.end(), comp_word);
					break;
		case constants::DESCENDING:
							std::sort(entries.begin(), entries.end(), desc_comp_word);
							break;
		case constants::NONE:
			break;
		}

}
}
