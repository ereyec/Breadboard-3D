#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <string>
#include <unordered_map>
#include <cstring>
#include <cmath>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum elementTypes{
	R,
	C,
	L,
	D,
	T,
	W
};

enum nodeType{
	VCC,
	GND,
};

struct pair{
	int code[6];
	float distance;
};

struct point{
	int code[3];
};

struct elementTableRow{
	int type;
	std::vector<int> nodes;
	int code[6];
};

struct nodeTableRow{
	int type;
	std::vector<int> elements;
};


class Common{ //todo: rename this to breadboard?
public:
	std::vector<std::vector<std::string>> netlistVector;

	std::vector<elementTableRow> elementTable;
	std::vector<nodeTableRow> nodeTable;

	std::unordered_map<std::string, int> nodeMap;
	
	int groundNode;
	int vccNode;

	int numPins; //1-ic model

	bool breadboardOccupancyMatrixF[59][7]; 
	bool breadboardOccupancyMatrixA[59][7];

	int breadboardRailDescriptorArrayF[59];
	int breadboardRailDescriptorArrayA[59];

	bool breadboardRailFullArrayF[59];
	bool breadboardRailFullArrayA[59];

	Common()
	{
		//Every five power rail holes there is a gap of one hole width.
		for(int i = 5; i < 59; i += 5){
			breadboardOccupancyMatrixF[i][0] = 1;
			breadboardOccupancyMatrixF[i][1] = 1;
			breadboardOccupancyMatrixA[i][0] = 1;
			breadboardOccupancyMatrixA[i][1] = 1;
		}

		//Initialize descriptor arrays
		for(int i = 0; i < 59; i++){
			breadboardRailDescriptorArrayF[i] = -1;
			breadboardRailDescriptorArrayA[i] = -1;
		}
	}

};

Common common;

/*Maps breadboard code to a vec3 position*/
glm::vec2 getPosition(int half, int row, int col){
	glm::ivec2 pivot; //glm::ivec2(row, col)
	//pivots flipped
	if(half == 70){ //'F'
		if(row > 1){
			pivot = glm::ivec2(9, 1);
			pivot.x += (row - 2) * 2; 
			pivot.y += col * 2;
		}else{
			pivot = glm::ivec2(1, 1);
			pivot.x += row * 2;
			pivot.y += col * 2;	
		}
	}
	if(half == 65){ //'A'
		if(row > 1){
			pivot = glm::ivec2(23, 1);
			pivot.x += (6 - row) * 2;
			pivot.y += col * 2;
		}else{
			pivot = glm::ivec2(37, 1);
			pivot.x += (1 - row) * 2;
			pivot.y += col * 2;
		}
	}

	glm::vec2 position = glm::vec2(pivot.x * 0.25f, pivot.y * 0.25f); //!!
	
	return position;
}

glm::mat3 getRotationMatrix(float ang){ //Rotation about the y-axis
	glm::mat3 matrix(
		std::cos(ang), 0, std::sin(ang),
		0, 1, 0,
		-std::sin(ang), 0, std::cos(ang)
	);

	return matrix;
}

float getAngleFromPoints(float x1, float z1, float x2, float z2){
	float O = z2 - z1;
	float A = x2 - x1;
	if(std::abs(A) < 0.00001) A = 0.00001;
	float angle = std::atan2(O, A); //Note: range is -pi to pi, correction is done next.

	if(angle < 0) angle = 6.283185 + angle;

	return angle;
}

glm::vec2 getMidpoint2D(float x1, float y1, float x2, float y2){
	glm::vec2 midpoint = glm::vec2((x1+x2) / 2.f, (y1+y2) / 2.f);
	return midpoint;
}

float getDistance(glm::vec2 p1, glm::vec2 p2){
	return std::sqrt( (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y) );
}

void pushV3T2(std::vector<float>& vertices, glm::vec3 vec, glm::vec2 tex){
	vertices.push_back(vec.x);
        vertices.push_back(vec.y);
        vertices.push_back(vec.z);
        vertices.push_back(tex.x);
        vertices.push_back(tex.y);
}

void pushV3(std::vector<float>& vertices, glm::vec3 vec){
	vertices.push_back(vec.x);
        vertices.push_back(vec.y);
        vertices.push_back(vec.z);
}

void pushV3C3(std::vector<float>& vertices, glm::vec3 vec, glm::vec3 col){
	vertices.push_back(vec.x);
        vertices.push_back(vec.y);
        vertices.push_back(vec.z);
	vertices.push_back(col.x);
        vertices.push_back(col.y);
        vertices.push_back(col.z);
}

#endif
