#ifndef PROCEDURALBREADBOARD_H
#define PROCEDURALBREADBOARD_H

#include "../common.h"
#include "../context.h"

/*Generate a breadboard texture procedurally (rather than relying on an image)*/
void generateBreadboardTexture(Context& context, Common& common){

const int HEIGHT = 41;
const int NUM_RAILS  = 59;
const int WIDTH = 59 * 2 + 1;
int nrChannels = 4;

context.breadboardTexture = Texturef(WIDTH, HEIGHT);

glm::vec3 black = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 lightBeige = glm::vec3(0.925f, 0.929f, 0.906f);
glm::vec3 darkBeige = glm::vec3(0.82f, 0.8f, 0.741f);

context.breadboardTexture.data = (float*)malloc(HEIGHT * WIDTH * nrChannels * sizeof(float));

int holeRows[] = {9, 11, 13, 15, 17, 23, 25, 27, 29, 31};
int railHoleRows[] = {1, 3, 37, 39};
int dividerRows[] = {19, 20, 21};
int regularRows[] = {0, 2, 4, 5, 6, 7, 8, 10, 12, 14, 16, 18, 22, 24, 26, 28, 30, 32, 33, 34, 35, 36, 38, 40};

//Fill breadboard texture colors
for(int i = 0; i < 41; i++){
	for(int j = 0; j < 119; j++){
		int index = (i * 119 + j) * 4;
		context.breadboardTexture.data[index] = lightBeige.x;
		context.breadboardTexture.data[index + 1] = lightBeige.y;
		context.breadboardTexture.data[index + 2] = lightBeige.z;
		context.breadboardTexture.data[index + 3] = 1.0f;
	}
}

for(int i = 19; i < 22; i++){
	for(int j = 0; j < 119; j++){
		int index = (i * 119 + j) * 4;
		context.breadboardTexture.data[index] = darkBeige.x;
		context.breadboardTexture.data[index + 1] = darkBeige.y;
		context.breadboardTexture.data[index + 2] = darkBeige.z;
		context.breadboardTexture.data[index + 3] = 1.0f;		
	}
}

for(int ia = 0; ia < 10; ia++){
	int i = holeRows[ia];
	for(int j = 1; j < 119; j += 2){
		int index = (i * 119 + j) * 4;
		context.breadboardTexture.data[index] = black.x;
		context.breadboardTexture.data[index + 1] = black.y;
		context.breadboardTexture.data[index + 2] = black.z;
		context.breadboardTexture.data[index + 3] = 1.0f;		
	}
}

for(int ia = 0; ia < 4; ia++){
	int i = railHoleRows[ia];
	for(int j = 1; j < 119; j += 2){
		if( ( (j+1)%12 ) != 0){
			int index = (i * 119 + j) * 4;
			context.breadboardTexture.data[index] = black.x;
			context.breadboardTexture.data[index + 1] = black.y;
			context.breadboardTexture.data[index + 2] = black.z;
			context.breadboardTexture.data[index + 3] = 1.0f;					
		}
	}
}

glBindTexture(GL_TEXTURE_2D, context.breadboardTexture.ID);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, context.breadboardTexture.data);
glBindTexture(GL_TEXTURE_2D, 0);

}
#endif