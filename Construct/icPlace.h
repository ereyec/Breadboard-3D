#ifndef ICPLACE_H
#define ICPLACE_H

#include "../common.h"

void icPlace(Common& common){

int numPins = 0;
int icIndex = -1;
for(int i = 0; i < common.netlistVector.size(); i++){
	std::string id = common.netlistVector[i][0];
	if(std::strcmp(id, "-i") == 0){
		icIndex = i;
		break; //Only allowing one IC per netlist for now
	}
}

if(icIndex != -1){
	numsPins = common.netlistVector[icIndex].size() - 3;
	for(int i = 0; i < numPins; i++){
		std::string key = common.netlistVector[icIndex][i + 2];
		int nodeNum = common.nodeMap.find(key)->second;

		for(int j = 0; j < numPins / 2; j++){ //F
			common.breadboardRailDescriptorArrayF[1 + j] = nodeNum;
			common.breadboardOccupancyMatrixF[1 + j][6] = 1;
		}
		for(int j = 0; j < numPins / 2; j++){//A
			common.breadboardRailDescriptorArrayA[1 + j] = nodeNum;
			common.breadboardOccupancyMatrixA[1 + j][6] = 1;
		}

	}
}

}
#endif