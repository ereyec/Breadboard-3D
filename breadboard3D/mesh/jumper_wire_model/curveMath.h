#include <cmath>
#include <iostream>
#define WIRE_LENGTH 53.0
#define MAX_CAT_A 11.35

//Catenary Calculation
struct catenaryParams{
	float a;
	float dcOffset;
};

void calculateCatenaryFromDist(catenaryParams& c, float distance){	
	float guess = 1.f;
	float result = 2 * guess * std::sinh((distance / 2) / guess);
	float epsilon = 1.f;

	//For the largest of distances (~52), check num of iterations
	while(std::abs(result - 53.0) > epsilon){
		//fixed point iteration for now
		//todo: use newton raphson method later for faster results
		if(result > 53.0){
			guess += 0.01f; 
		}else{
			guess -= 0.01f;
		}
		result = 2 * guess * std::sinh((distance / 2) / guess);		
	}

	//<- Make sure that below a certain distance, the catenary params stop changing due to wire tension.
	
	c.a = guess;	
	c.dcoffset = -guess*std::cosh((distance / 2) / guess) + guess;

}

//Logit function
struct logitParams{
	float a; //determines the width
	float b; //determines the 'time' shift offset
	float dcOffset;
};

//Polynomial fitting

