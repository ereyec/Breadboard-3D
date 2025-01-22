//Process each element from the element table; use the node table for decoding node type (if applicable). 
//Perform any checks/bookkeeping in between processing elements. 

//..std::vector<elementTableRow> elementTable;
//..std::vector<nodeTableRow> nodeTable;

int decode(elementTableRow& etr){
	if(etr.nodes[0] == VCC || etr.nodes[0] == GND) return SIMPLE;
	else if(etr.nodes[1] == VCC || etr.nodes[1] == GND) return SIMPLE;
	else return COMPLEX;
}

for(int i = 0; i < elementTable.size(); i++){
	int PT = decode(elementTable[i]);

	int ha1, ho1, r1, ha2, ho2, r2; //code nums

	if(PT == SIMPLE){
		
	}
	else if(PT == COMPLEX){
		//use pairseaarch and nodesearch functions to obtain code. 
	
		//update the element table with the code. 
		elementTable[i].code[0] = ha1;
		//...
	}
		
}


