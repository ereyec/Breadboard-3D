//(std::vector<int>& nodes, int* half1, int* hole1, int* rail1, int* half2,  int* hole2, int* rail2)

//(return type void), Returns if the pair {E1, E2} is found in either A or F, and the code is updated.

int E1 = nodes[0], E2 = nodes[1];

bool containsE1 = false, containsE2 = false;
int tempRail1, tempRail2;
int tempHalf1, tempHalf2;

for(int i = 0; i < 59; i++){
	if(breadboardRailDescriptorArrayF[i] == E1 && !breadboardRailFullArrayF[i]){
		containsE1 = true;
		tempRail1 = i;
		tempHalf1 = 70;
	}
	if(breadboardRailDescriptorArrayA[i] == E1 && !breadboardRailFullArrayA[i]){
		containsE1 = true;
		tempRail1 = i;
		tempHalf1 = 65;
	}

	if(breadboardRailDescriptorArrayF[i] == E2 && !breadboardRailFullArrayF[i]){
		containsE2 = true;
		tempRail2 = i;
		tempHalf2 = 70;
	}
	if(breadboardRailDescriptorArrayA[i] == E2 && !breadboardRailFullArrayA[i]){
		containsE2 = true;
		tempRail2 = i;
		tempHalf2 = 65;
	}	
}

if(containsE1 && containsE2)
{
	//Find hole in E1
	std::vector<int> holes1;
	if(tempHalf1 == 70){}
	if(tempHalf1 == 65){}

	//Find holes in E2
	std::vector<int> holes2;
	if(tempHalf2 == 70){}
	if(tempHalf2 == 65){}		
}






