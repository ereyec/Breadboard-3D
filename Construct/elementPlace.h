#ifndef ELEMENTPLACE_H
#define ELEMENTPLACE_H

#include "../common.h"

void placeElement(Common& common, int node1, int node2, int elementTableIndex){

//SCAN BREADBOARD DATA
std::vector<point> v1;
std::vector<point> v2;

for(int x = 0; x < 59; x++){ //node 1 , also should rename x and y to row/col
	point p;
	for(int y = 0; y < 1; y++){ //VCC
		bool c1 = common.breadboardOccupancyMatrixF[x][y];
		bool c2 = (node1 == common.vccNode);
		if(!c1 && c2){
			p = { {70, y, x} };
			v1.push_back(p);
		}
		c1 = common.breadboardOccupancyMatrixA[x][y];
		if(!c1 && c2){
			p = { {70, y, x} };
			v1.push_back(p);
		}
	}
	for(int y = 1; y < 2; y++){ //GND
		bool c1 = common.breadboardOccupancyMatrixF[x][y];
		bool c2 = (node1 == common.groundNode);
		if(!c1 && c2){
			p = { {70, y, x} };
			v1.push_back(p);
		}
		c1 = common.breadboardOccupancyMatrixA[x][y];
		if(!c1 && c2){
			p = { {70, y, x} };
			v1.push_back(p);
		}
	}
	for(int y = 2; y < 7; y++){
		bool c1 = common.breadboardOccupancyMatrixF[x][y];
		bool c2 = common.breadboardRailFullArrayF[x];
		bool c3 = (common.breadboardRailDescriptorArrayF[x] == node1); //!!!!
		if(!c1 && !c2 && c3){
			p = { {70, y, x} };
			v1.push_back(p);
		}
		c1 = 	common.breadboardOccupancyMatrixA[x][y];
		c2 = common.breadboardRailFullArrayA[x];
		c3 = (common.breadboardRailDescriptorArrayA[x] == node1);
		if(!c1 && !c2 && c3){
			p = { {65, y, x} };
			v1.push_back(p);
		}
	}
}

for(int x = 0; x < 59; x++){ //node 2
	point p;
	for(int y = 0; y < 1; y++){ //VCC
		bool c1 = common.breadboardOccupancyMatrixF[x][y];
		bool c2 = (node2 == common.vccNode);
		if(!c1 && c2){
			p = { {70, y, x} };
			v1.push_back(p);
		}
		c1 = common.breadboardOccupancyMatrixA[x][y];
		if(!c1 && c2){
			p = { {70, y, x} };
			v1.push_back(p);
		}
	}
	for(int y = 1; y < 2; y++){ //GND
		bool c1 = common.breadboardOccupancyMatrixF[x][y];
		bool c2 = (node2 == common.groundNode);
		if(!c1 && c2){
			p = { {70, y, x} };
			v1.push_back(p);
		}
		c1 = common.breadboardOccupancyMatrixA[x][y];
		if(!c1 && c2){
			p = { {70, y, x} };
			v1.push_back(p);
		}
	}
	for(int y = 2; y < 7; y++){		
		bool c1 = common.breadboardOccupancyMatrixF[x][y];
		bool c2 = common.breadboardRailFullArrayF[x];
		bool c3 = (common.breadboardRailDescriptorArrayF[x] == node2); 
		if(!c1 && !c2 && c3){
			p = { {70, y, x} };
			v2.push_back(p);
		}
		c1 = 	common.breadboardOccupancyMatrixA[x][y];
		c2 = common.breadboardRailFullArrayA[x];
		c3 = (common.breadboardRailDescriptorArrayA[x] == node2);
		if(!c1 && !c2 && c3){
			p = { {65, y, x} };
			v2.push_back(p);
		}
	}
}

//Pair Creation
std::vector<pair> pairs;
for(int i = 0; i < v1.size(); i++){
	for(int j = 0; j < v2.size(); j++){
		pair p;
		p.code[0] = v1[i].code[0];
		p.code[1] = v1[i].code[1];
		p.code[2] = v1[i].code[2];
		p.code[3] = v2[j].code[0];
		p.code[4] = v2[j].code[1];	
		p.code[5] = v2[j].code[2];
		glm::vec2 q1 = getPosition(p.code[0], p.code[1], p.code[2]);
		glm::vec2 q2 = getPosition(p.code[3], p.code[4], p.code[5]);
		float distance = distance(q1, q2);
		p.distance = distance;
		pairs.push_back(p);
	}
}

std::sort(pairs.begin(), pairs.end(), [](const pair& a, const pair& b)
{ return a.distance < b.distance; }
);

//SET MATRIX OCCUPANCY
if(pairs[0].code[0] == 70){
	common.breadboardOccupancyMatrixF[pairs[0].code[2]][pairs[0].code[1]] = 1;
}
else if(pairs[0].code[0] == 65){
	common.breadboardOccupancyMatrixA[pairs[0].code[2]][pairs[0].code[1]] = 1;
}

if(pairs[0].code[3] == 70){
	common.breadboardOccupancyMatrixF[pairs[0].code[5]][pairs[0].code[4]] = 1;
}
else if(pairs[0].code[3] == 65){
	common.breadboardOccupancyMatrixA[pairs[0].code[5]][pairs[0].code[4]] = 1;
}

//UPDATE ELEMENT TABLE
std::memcpy(common.elementTable[elementTableIndex].code, pairs[0].code, sizeof(pairs[0].code)); //!!!

}
#endif
