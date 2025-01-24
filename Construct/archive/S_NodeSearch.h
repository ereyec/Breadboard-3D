//(std::vector<int>& nodes, int* half1, int* hole1, int* rail1, int* half2,  int* hole2, int* rail2)

//One of these will be either VCC or GND. 
int E1 = nodes[0], E2 = nodes[1];

int powerNode;

if(nodes[0] == VCC || nodes[0] == GND) powerNode = 0;
else if(nodes[1] == VCC || nodes[1] == GND) powerNode = 1;

int E = nodes[1 - powerNode];

//Search for a rail and hole for E.
int tempRail;
int tempHalf;

bool containsE = false;

//This loop is just to see if there exists a node E in the breadboard. 
for(int i = 0; i < 59; i++){
	if(breadboardRailDescriptorArrayF[i] == E && !breadboardRailFullArrayF[i]){
		containsE = true;
		tempRail = i;
		tempHalf = 70;
	}
	if(breadboardRailDescriptorArrayA[i] == E && !breadboardRailFullArrayA[i]){
		containsE = true;
		tempRail = i;
		tempHalf = 65;
	}
}

if(containsE){
	//Hole Search
}else{
	//Node and then Hole Search
}

//Finally, place the VCC or GND in, really, any empty spot on the power rail in the respective half of the //breadboard. 



