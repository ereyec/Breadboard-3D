#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>

int main(){
	std::vector<std::vector<std::string>> netlistVector;

	FILE* file = NULL;
	file = fopen("../netlistExample.txt", "r");
	if(file == NULL) return -1;
	
	char line[256];

	int index = 0;
	while(fgets(line, sizeof(line), file)){		
		netlistVector.resize(index + 1);
		//printf("%s\n", line);

		char* word = strtok(line, " ");
		if(word != NULL) netlistVector[index].push_back(word); //char* to string conversion needed?
		//printf("%s\n", word);

		while(word != NULL){
			word = strtok(NULL, " ");
			if(word != NULL) {
				//printf("%s\n", word);
				netlistVector[index].push_back(word); //char* to string conversion needed?
			}
		}
		index++;
	}

	fclose(file);

	//Test: Print out all of the data in the vector:
	for(int i = 0; i < netlistVector.size(); i++){
		for(int j = 0; j < netlistVector[i].size(); j++){
			std::cout << netlistVector[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}