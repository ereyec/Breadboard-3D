bool CF(std::vector<int>& nodes, int* half1, int* hole1, int* rail1, int* half2,  int* hole2, int* rail2)
{

int E1 = nodes[0], E2 = nodes[1];

bool containsE1 = false, containsE2 = false;
int tempRail1, tempRail2;
for(int i = 0; i < 59; i++){
	if(breadboardRailDescriptorArrayF[i] == E1 && !breadboardRailFullArrayF[i]){
		containsE1 = true;
		tempRail1 = i;
	}
	if(breadboardRailDescriptorArrayF[i] == E2 && !breadboardRailFullArrayF[i]){
		containsE2 = true;
		tempRail2 = i;
	}
}

if(containsE1 && containsE2)
{
	//Find hole in E1
	std::vector<int> holes1;
	for(int x = 2; x < 7; x++){
		if(breadboardOccupancyMatrixF[tempRail1][x] == 0) holes1.push_back(x);
	}
	if(holes1.size() > 2){
		breadboardOccupancyMatrixF[tempRail1][holes1[0]] = 1;
		//UPDATE THE CODE:
		*half1 = 70;
		*hole1 = holes1[0];
		*rail1 = tempRail1;
	}else{
		//We need to find a spot and create a new node.
		for(int i = 0; i < 59; i++){
			if(breadboardRailDescriptorArrayF[i] == -1){
				breadboardRailDescriptorArrayF[i] = E1;
				tempRail1 = i;
				breadboardOccupancyMatrixF[tempRail1][0] = 1;
				//UPDATE THE CODE:
				*half1 = 70;
				*hole1 = 0;
				*rail1 = tempRail1;
			}
		}
	}

	//Find hole in E2 - MAKE SURE THERE ISN'T ANY ..1 LEFT!
	std::vector<int> holes2;
	for (int x = 2; x < 7; x++) {
		if (breadboardOccupancyMatrixF[tempRail2][x] == 0) holes2.push_back(x);
	}
	if (holes2.size() > 2) {
		breadboardOccupancyMatrixF[tempRail2][holes2[0]] = 1;
		//UPDATE THE CODE:
		*half2 = 70;
		*hole2 = holes2[0];
		*rail2 = tempRail2;
	}
	else {
		//We need to find a spot and create a new node.
		for (int i = 0; i < 59; i++) {
			if (breadboardRailDescriptorArrayF[i] == -1) {
				breadboardRailDescriptorArrayF[i] = E2;
				tempRail2 = i;
				breadboardOccupancyMatrixF[tempRail2][0] = 1;
				//UPDATE THE CODE:
				*half2 = 70;
				*hole2 = 0;
				*rail2 = tempRail2;
			}
		}
	}
	return true;
}


}
