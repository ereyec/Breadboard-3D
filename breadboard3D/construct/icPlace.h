#ifndef ICPLACE_H
#define ICPLACE_H

#include "../common.h"

//todo: fix backwards placement
void icPlace(Common& common){ 

int icIndex = -1;
for(int i = 0; i < common.netlistVector.size(); i++){
	std::string id = common.netlistVector[i][0];
	if(std::strcmp(id.c_str(), "-i") == 0){
		icIndex = i;
		break; //Only allowing one IC per netlist for now
	}
}

if(icIndex != -1){
	common.numPins = common.netlistVector[icIndex].size() - 3;
	for(int i = 0; i < common.numPins; i++){
		std::string key = common.netlistVector[icIndex][i + 2];
		int nodeNum = common.nodeMap.find(key)->second;

		if(i < common.numPins/2){
			common.breadboardRailDescriptorArrayF[1 + i] = nodeNum;
			common.breadboardOccupancyMatrixF[1 + i][6] = 1;
		}else{			
			common.breadboardRailDescriptorArrayA[common.numPins/2 + 1 - (1 + i - common.numPins/2)] = nodeNum;
			common.breadboardOccupancyMatrixA[common.numPins/2 + 1 - (1 + i - common.numPins/2)][6] = 1;
		}

	}	

}

//Todo: Connect identical ic pin nodes and ic pin vcc and ground with jumper wires. 

}
#endif