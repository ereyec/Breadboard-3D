//INPUT: int elementIndex, std::vector<int>& nodes; We also have the breadboard occupancy matrix and //breadboard rail descriptor array. 

//CODE: char half1, int hole1, int rail1,  char half2, int hole2, int rail2

//search for F to see if it contains both nodes in nodes. 

bool containsE1 = false;
bool containsE2 = false;

int E1 = nodes[0];
int E2 = nodes[1];

for(int i = 0; i < 59; i++){
	if(breadboardRailDescriptorArray[i] == E1) containsE1 = true;
	if(breadboardRailDescriptorArray[i] == E2) containsE2 = true;
}

//IF(containsE1 && containsE2)

//find hole in E1, if found update code. if not found find a new rail to create a node and then place there, making //sure to do appropriate steps (adding jumper wire element)

//find hole in E2, if found if not found

//ENDIF




