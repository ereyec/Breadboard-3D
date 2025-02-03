#ifndef BOOKKEEPING_H
#define BOOKKEEPING_H

#include <random>
#include "../common.h"

//Done after every element place
void breadboardCheck(Common& common){

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(0, 6);

for(int i = 0; i < 59; i++){
	int countF = 0;
	int countA = 0;
	std::vector<int> setF;
	std::vector<int> setA;

	for(int j = 2; j < 7; j++){
		if(common.breadboardOccupancyMatrixF[i][j] == 1){
			countF++;
		} else{
			setF.push_back(j);
		}
		if(common.breadboardOccupancyMatrixA[i][j] == 1){
			countA++;
		} else{
			setA.push_back(j);
		}
	}

	if(countF == 5) common.breadboardRailFullArrayF[i] = 1;
	if(countA == 5) common.breadboardRailFullArrayA[i] = 1;

	if(countF == 4){
		//need to find a new empty node, then 'place' a jumper wire
		int nodeNum = common.breadboardRailDescriptorArrayF[i];
		int newRailIndex = -1;
		for(int j = 0; j < 59; j++){
			if(common.breadboardRailDescriptorArrayF[j] == -1){
				newRailIndex = j;
				break;
			}
		}
		if(newRailIndex != -1){
			common.breadboardRailDescriptorArrayF[newRailIndex] = nodeNum;
			common.breadboardOccupancyMatrixF[newRailIndex][0] = 1;
			common.breadboardOccupancyMatrixF[i][setF[0]] = 1; //!!!
			common.breadboardRailFullArrayF[i] = 1;
			//TODO: Push jumper wire code here: (untested)
			jumperWireElement jwe = {{70, 0, newRailIndex, 70, setF[0], i}, dist(gen)};
			common.jumperWireTable.push_back(jwe);
		}
	}
	
	if(countA == 4){
		//need to find a new empty node, then 'place' a jumper wire
		int nodeNum = common.breadboardRailDescriptorArrayA[i];
		int newRailIndex = -1;
		for(int j = 0; j < 59; j++){
			if(common.breadboardRailDescriptorArrayA[j] == -1){
				newRailIndex = j;
				break;
			}
		}
		if(newRailIndex != -1){
			common.breadboardRailDescriptorArrayA[newRailIndex] = nodeNum;
			common.breadboardOccupancyMatrixA[newRailIndex][0] = 1;
			common.breadboardOccupancyMatrixA[i][setA[0]] = 1; //!!!
			common.breadboardRailFullArrayA[i] = 1;
			//TODO: Push jumper wire code here. (untested)
			jumperWireElement jwe = {{65, 0, newRailIndex, 65, setA[0], i}, dist(gen)};
			common.jumperWireTable.push_back(jwe);
		}
	}
}

}
#endif