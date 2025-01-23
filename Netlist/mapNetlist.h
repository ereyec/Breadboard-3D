std::vector<elementTableRow> elementTable;

//Conventions: -i for IC
//...std::vector<std::vector<std::string>> netlistVector;

//Mapping the netlist nodes to indices
int index = 0;
std::unordered_map<std::string, int> nodeMap;

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

	if(type == 'R')
	else if(type == 'C')
	else if(type == 'L')
	else if(type == 'D')	
}

//Print the element table to ascertain correctness
for(int i = 0; i < elementTable.size(); i++){
	std::cout << "Type: " << int << "  Elements: " << elementTable[i].elements[0] << " "
<< elementTable[i].elements[1] << std::endl;

}


