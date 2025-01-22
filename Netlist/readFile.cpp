#include <stdio.h>
#include <cstring>
#include <iostream>
#include <vector>

int main(){
	FILE* file = NULL;
	file = fopen("file.txt", "r");
	if(file == NULL) return -1;
	
	char line[256];
	fgets(line, sizeof(line), file);
	printf("%s\n", line);

	char* word = strtok(line, " ");
	printf("%s\n", word);

	while(word != NULL){
		word = strtok(NULL, " ");
		if(word != NULL) printf("%s\n", word);
	}

	fclose(file);
	return 0;
}