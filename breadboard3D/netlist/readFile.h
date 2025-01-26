#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>

#include "../common.h"

int readFile(Common& common, const char* filename){
	FILE* file = NULL;
	file = fopen(filename, "r");
	if(file == NULL){
		std::cout << "Could not open " << filename << std::endl;
		std::cout << "Please check that the file name is correct and that the file exists." << std::endl;
		return -1;
	}
	
	char line[256];

	int index = 0;
	while(fgets(line, sizeof(line), file)){		
		common.netlistVector.resize(index + 1);

		char* word = strtok(line, " ");
		if(word != NULL) common.netlistVector[index].push_back(word); //!!!

		while(word != NULL){
			word = strtok(NULL, " ");
			if(word != NULL) {
				common.netlistVector[index].push_back(word); //!!!
			}
		}
		index++;
	}

	fclose(file);	
	
	return 0;
}

#endif