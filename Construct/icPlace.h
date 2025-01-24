//Could just do this directly from the netlistVector!

int numPins = 0;
int icIndex = -1;
for(int i = 0; i < netlistVector.size(); i++){
	std::string id = netlistVector[i][0];
	if(std::strcmp(id, "-i") == 0){
		icIndex = i;
		break; //Only allowing one IC per netlist for now
	}
}

if(icIndex != -1){
	numsPins = netlistVector[icIndex].size() - 3;
	for(int i = 0; i < numPins; i++){
		std::string key = netlistVector[icIndex][i + 2];
		int nodeNum = nodeMap.find(key)->second;

		for(int j = 0; j < numPins / 2; j++){ //F
			breadboardRailDescriptorArrayF[1 + j] = nodeNum;
			breadboardOccupancyMatrixF[1 + j][6] = 1;
		}
		for(int j = 0; j < numPins / 2; j++){//A
			breadboardRailDescriptorArrayA[1 + j] = nodeNum;
			breadboardOccupancyMatrixA[1 + j][6] = 1;
		}

	}
}