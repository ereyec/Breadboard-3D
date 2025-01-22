bool breadboardOccupancyMatrixF[59][7] = {}; 
bool breadboardOccupancyMatrixA[59][7] = {};

int breadboardRailDescriptorArrayF[59] = {};
int breadboardRailDescriptorArrayA[59] = {};

bool breadboardRailFullArrayF[59] = {};
bool breadboardRailFullArrayA[59] = {};

void initializeBRFA(bool brfa[]){
	for(int i = 5; i < 59; i += 5) brfa[i] = true;
}

void initializeBRDA(int brda[]){
	for(int i = 0; i < 59; i++) brda[i] = -1;
}

enum elementTypes{
	R,
	C,
	L,
	T,
	W
};

enum nodeType{
	VCC,
	GND,
	ORDINARY,
	EXTRAORDINARY
};

enum pairType{
	SIMPLE,
	COMPLEX
};

struct elementTableRow{
	int type;
	std::vector<int> nodes;
	int code[6];
};

struct nodeTableRow{
	int type;
	std::vector<int> elements;
};

