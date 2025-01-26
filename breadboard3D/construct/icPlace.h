#ifndef ICPLACE_H
#define ICPLACE_H

#include "../common.h"

//todo: fix backwards placement
void icPlace(Common& common){ 

int numPins = 0;
int icIndex = -1;
for(int i = 0; i < common.netlistVector.size(); i++){
	std::string id = common.netlistVector[i][0];
	if(std::strcmp(id.c_str(), "-i") == 0){
		icIndex = i;
		break; //Only allowing one IC per netlist for now
	}
}

if(icIndex != -1){
	numPins = common.netlistVector[icIndex].size() - 3;
	for(int i = 0; i < numPins; i++){
		std::string key = common.netlistVector[icIndex][i + 2];
		int nodeNum = common.nodeMap.find(key)->second;
	
		/*for(int j = 0; j < numPins / 2; j++){ //F
			common.breadboardRailDescriptorArrayF[1 + j] = nodeNum;
			common.breadboardOccupancyMatrixF[1 + j][6] = 1;
		}
		for(int j = 0; j < numPins / 2; j++){//A
			common.breadboardRailDescriptorArrayA[1 + j] = nodeNum;
			common.breadboardOccupancyMatrixA[1 + j][6] = 1;
		}*/

		if(i < numPins/2){
			common.breadboardRailDescriptorArrayF[1 + i] = nodeNum;
			common.breadboardOccupancyMatrixF[1 + i][6] = 1;
		}else{			
			common.breadboardRailDescriptorArrayA[numPins/2 + 1 - (1 + i - numPins/2)] = nodeNum;
			common.breadboardOccupancyMatrixA[numPins/2 + 1 - (1 + i - numPins/2)][6] = 1;
		}

	}	

}

}
#endif