
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "../includes/constants.h"
#include "../includes/fileio.h"


bool openFile(std::fstream& myfile, const std::string& myFileName,
		std::ios_base::openmode mode){
		myfile.open(myFileName, mode);
		if (!myfile.is_open())
			return false;
		else
			return true;
}

void closeFile(std::fstream& myfile){
	if (myfile.is_open()){
		myfile.close();
	}
}

int writetoFile(std::vector<constants::entry>  &entries, const std::string &outputfilename){
	if(entries.size() == 0){
		return constants::FAIL_NO_ARRAY_DATA;
	}

	std::ofstream myfile;
	myfile.open(outputfilename.c_str());
	if (!myfile.is_open())
		return constants::FAIL_FILE_DID_NOT_OPEN;


//	if(!openFile(myfile, outputfilename.c_str()), std::ios_base::out){
//		return constants::FAIL_FILE_DID_NOT_OPEN;
//	}

	std::string stringForm;
		for (int var = 0; var < (int)entries.size(); ++var) {
			std::stringstream ss;
			ss << entries[var]. number_occurences;
			std::string count = ss.str();
			stringForm = entries[var].word + "  " + count;
			myfile << stringForm << std::endl;
		}
//		myfile << '\r';

//		closeFile(myfile);
		if (myfile.is_open()){
				myfile.close();
			}

	return 0;
}
