#ifndef CURVEMATH_H
#define CURVEMATH_H

#include <cmath>
#include <iostream>

#define WIRE_LENGTH 53.0
#define MAX_CAT_A 11.35
#define MAX_CAT_DIST 36

struct catenaryParams{
	float a;
	float dcOffset;
};

struct logitParams{
	float a; //determines the width
	float b; //determines the 'time' shift offset
	float dcOffset;
};

struct fitCurve{
	glm::vec2 a0;
	glm::vec2 a1;
	glm::vec2 a2;
};

float lerp(float a, float b, float t){
	return a + (b - a) * t;
}

void calculateCatenaryFromDist(catenaryParams& c, float distance){	
	float guess = 1.f;
	float result = 2 * guess * std::sinh((distance / 2) / guess);
	float epsilon = 1.f;

	if(distance <= MAX_CAT_DIST){
		c.a = MAX_CAT_A;
		c.dcOffset = 28.87; //magic number
	}

	//For the largest of distances (~52), check num of iterations
	int iterationCount = 0;
	while(std::abs(result - 53.0) > epsilon){
		//FPI (fixed point iteration) for now
		//todo: use newton raphson method later for faster results
		if(result > 53.0){
			guess += 0.01f; 
		}else{
			guess -= 0.01f;
		}
		result = 2 * guess * std::sinh((distance / 2) / guess);	
		iterationCount++;
		if(iterationCount > 1000){
			std::cout << "Iteration count has exceeded 1000. " << std::endl;
			break;
		}
	}	
	c.a = guess;	
	c.dcoffset = -guess * std::cosh((distance / 2) / guess) + guess;

}

void calculateLogitFunction(logitParams& lp, float distance){
	float width = lerp(0.5f, 4, 1 - (0.5f*dist) / 18.f);
	lp.a = 1 / width;
	lp.b = distance / 2.f;
	
	//Iteratively calculate the DC offset
	float dcoffset = 0.f;
	float epsilon = 0.01f;
	float result = -std::log((1 - lp.a*(distance/2 + epsilon - lp.b))/(lp.a * (distance/2 + epsilon - lp.b))) + dcoffset;
	while(result < 0){
		dcoffset += 0.1f;
		result = -std::log((1 - lp.a*(distance/2 + epsilon - lp.b))/(lp.a * (distance/2 + epsilon - lp.b))) + dcoffset; 
	}
	
	lp.dcOffset = dcoffset;	
}

void calculateFitCurve(fitCurve& fc, catenaryParams& c, logitParams& lp, float distance){

	//first, iteratively find the intersection point between the catenary and the logit function:
	//keep track of its y value.
	//suggestions: start with distance/2, iterate in increments of 0.01, FPI is fine
	float g1, g2;

	float x0 = distance / 2;
	g1 = -c.a * std::cosh((x0) / c.a) + c.dcOffset;
	//for g2, does it matter if the result is -inf at first?	
	//if g2 results in a domain error, make appropriate correction!
	g2 = -std::log((1 - lp.a*(x0 - lp.b))/(lp.a * (x0 - lp.b))) + lp.dcOffset;
	while(g2 < g1){
		x0 += 0.01f;
		g1 = -c.a * std::cosh((x0) / c.a) + c.dcOffset;
		g2 = -std::log((1 - lp.a*(x0 - lp.b))/(lp.a * (x0 - lp.b))) + lp.dcOffset;
	}
	float y0 = g1;	

	//next, divide this y value by half. Find the corresponding x value in the logit function.
	//suggestions: is there a better way than doing this iteratively?
	float y1 = y0 / 2.f;
	float x1 = lp.b;
	g1 = -std::log((1 - lp.a*(x1 - lp.b))/(lp.a * (x1 - lp.b))) + lp.dcOffset;
	while(g1 < y1){
		x1 += 0.01f;
		g1 = -std::log((1 - lp.a*(x1 - lp.b))/(lp.a * (x1 - lp.b))) + lp.dcOffset;
	}

	//find a point on the catenary halfway from the intersection point to the y axis (on the catenary). 
	//suggestions: start with distance/4 on the catenary for point a0
	fc.a0 = -c.a * std::cosh((distance / 4) / c.a) + c.dcOffset;
	fc.a2 = glm::vec2(x1, y1);

	//between the two points we've found, calculate the midpoint. 
	//suggestions: use the midpoint function from common.h
	glm::vec2 md = getMidpoint2D(fc.a0.x, fc.a0.y, fc.a2.x, fc.a2.y);	
	glm::vec2 m0 = md;

	//create a perpendicular line to find the halfway point toward the curve.
	//suggestions: review algebra, will this be iterative as well?
	glm::vec2 dxdy = -(a2.x - a0.x)/(a2.y - a0.y); 
	g1 = -c.a * std::cosh((md.x) / c.a) + c.dcOffset;

	while(md.y < g1){
		md.x += 0.01f;
		g1 = -c.a * std::cosh((md.x) / c.a) + c.dcOffset;
	}

	fc.a1 = getMidPoint2D(m0.x, m0.y, md.x, md.y);
 
}

#endif