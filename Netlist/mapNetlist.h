std::vector<elementTableRow> elementTable;
std::vector<nodeTableRow> nodeTable;

//Conventions: -i for IC
//...std::vector<std::vector<std::string>> netlistVector;

//Mapping the netlist nodes to indices
int index = 0;
std::unordered_map<std::string, int> nodeMap;
int groudNode, vccNode;

for(int i = 0; i < netlistVector.size(); i++){
	//Integrated circuit netlist line parsing - may not work properly. 	
	if(std::strcmp(netlistVector[i][0], "-i") == 0){ //User must manually add "-i" flag to ICs
		//Parse from index 2 to size - 2
		for(int j = 2; j < netlistVector[i].size() - 1; j++){
			std::string nodeName = netlistVector[i][j];
			if(nodeMap.find(nodeName) == nodeMap.end()){
				nodeMap.insert(std::make_pair(nodeName, index));
				index++;
			}
		}
	}
	//Resistors, capacitors, inductors, and diodes all have two leads. 
	char type = netlistVector[i][0][0]; //<- idk if this will work
	if(type == 'R' || type == 'L' || type == 'C' || type == 'D'){
		for(int j = 1; j < 3; j++){
			std::string nodeName = netlistVector[i][j];
			if(nodeMap.find(nodeName) == nodeMap.end()){
				nodeMap.insert(std::make_pair(nodeName, index));
				index++;
			}
		}
	}
}


//Adding elements to the elementTable. 
for(int i = 0; i < netlistVector.size(); i++){
	char type = netlistVector[i][0][0];
		
	elementTableRow row;
	int e1, e2;
	
	if(type == 'R'){
		e1 = nodeMap.find(netlistVector[i][1])->second;
		e2 = nodeMap.find(netlistVector[i][2])->second;
		row = {R, {e1, e2}};
	}
	else if(type == 'C'){
		e1 = nodeMap.find(netlistVector[i][1])->second;
		e2 = nodeMap.find(netlistVector[i][2])->second;
		row = {C, {e1, e2}};
	}
	else if(type == 'L'){
		e1 = nodeMap.find(netlistVector[i][1])->second;
		e2 = nodeMap.find(netlistVector[i][2])->second;
		row = {L, {e1, e2}};
	}
	else if(type == 'D'){
		e1 = nodeMap.find(netlistVector[i][1])->second;
		e2 = nodeMap.find(netlistVector[i][2])->second;
		row = {D, {e1, e2}};
	}

	elementTable.push_back(row);
}

//Test: Print the element table to ascertain correctness
for(int i = 0; i < elementTable.size(); i++){
	std::cout << "Type: " << int << " Nodes: " << elementTable[i].nodes[0] << " "
<< elementTable[i].nodes[1] << std::endl;

}

//Next, create the node table. We already have the size of the node table, it is simply the value of index + 1.
//Outer for loop will iterate index+1 times. Each iteration, search the elementTable. Any element that contains the //current index will have its index pushed on the node table row's element int vector. 
for(int i = 0; i < index + 1; i++){
	nodeTableRow row;	

	for(int j = 0; j < elementTable.size(); j++){
		for(int k = 0; k < elementTable[j].size(); k++){
			if(elementTable[j].nodes[k] == i){
				row.elements.push_back(j);
				break;
			}
		}
	}
	nodeTable.push_back(row);
}

//Test: Print the node table to ascertain correctness
for(int i = 0; i < nodeTable.size(); i++){
	std::cout << "Type: " << int << "  Nodes: ";
	
	for(int j = 0; j < nodeTable[i].elements.size(); j++){
		std::cout << nodeTable[i].elements[j] << " ";
	}
	std::cout << std::endl;
}

//Mark VCC and GND
groundNode = nodeMap.find("0")->second; //In every netlist, "0" is ground

for(int i = 0; i < netlistVector.size(); i++){
	if(std::strcmp(netlistVector[i][0], "-v") == 0){
		vccNode = nodeMap.find(netlistVector[i][2])->second;
	}
}
