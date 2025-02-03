#ifndef ICPLACE_H
#define ICPLACE_H

#include <random>
#include "../common.h"

//todo: fix backwards placement
void icPlace(Common& common){ 

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(0, 6);

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

//iterate through the rail descriptor array, if any rail is vcc or ground, connect a jumper wire to vcc/ground. 
//Check for conflicts with previous code!
for(int i = 0; i < 59; i++){
	int node;
	node = common.breadboardRailDescriptorArrayF[i];
	if(node == common.groundNode){
		common.breadboardOccupancyMatrixF[i][1] = 1;
		common.breadboardOccupancyMatrixF[i][2] = 1;
		common.jumperWireTable.push_back({{70, 1, i, 70, 2, i}, dist(gen)});
	}
	if(node == common.vccNode){
		common.breadboardOccupancyMatrixF[i][0] = 1;
		common.breadboardOccupancyMatrixF[i][2] = 1;
		common.jumperWireTable.push_back({{70, 0, i, 70, 2, i}, dist(gen)});
	}
	node = common.breadboardRailDescriptorArrayA[i];
	if(node == common.groundNode){
		common.breadboardOccupancyMatrixA[i][1] = 1;
		common.breadboardOccupancyMatrixA[i][2] = 1;
		common.jumperWireTable.push_back({{65, 1, i, 65, 2, i}, dist(gen)});
	}
	if(node == common.vccNode){
		common.breadboardOccupancyMatrixA[i][0] = 1;
		common.breadboardOccupancyMatrixA[i][2] = 1;
		common.jumperWireTable.push_back({{65, 0, i, 65, 2, i}, dist(gen)});
	}
}

}
#endif