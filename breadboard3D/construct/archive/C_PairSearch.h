//(std::vector<int>& nodes, int* half1, int* hole1, int* rail1, int* half2,  int* hole2, int* rail2)

int E1 = nodes[0], E2 = nodes[1];

bool E1RailFound = false;
bool E2RailFound = false;
int tempRail1, tempRail2;

for(int i = 0; i < 59; i++){
	if(breadboardRailDescriptorArrayA[i] == E1 && !breadboardRailFullArrayA[i]){
		E1RailFound = true;
		tempRail1 = i;
	}
	else if(breadboardRailDescriptorArrayF[i] == E1 && !breadboardRailFullArrayF[i]){
		E1RailFound = true;
		tempRail1 = i;
	}
	if(breadboardRailDescriptorArrayA[i] == E2 && !breadboardRailFullArrayA[i]){
		E2RailFound = true;
		tempRail2 = i;
	}
	else if(breadboardRailDescriptorArrayF[i] == E2 && !breadboardRailFullArrayF[i]){
		E2RailFound = true;
		tempRail2 = i;
	}	
}

if(E1RailFound){
	//Hole search
	//Check the number of empty holes while keeping track of their indices. >2 place in next available spot,
	//otherwise we need to find a spot and create a new node. 
	std::vector<int> holes;
	for(int x = 2; x < 7; x++){
		
	}
}
else{
	//Node Search then Hole search
}

if(E2RailFound){
	//Hole search
}
else{
	//Node Search then Hole search
}