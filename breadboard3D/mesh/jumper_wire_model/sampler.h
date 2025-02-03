#ifndef SAMPLER_H
#define SAMPLER_H

#include "../../common.h"
#include "../../context.h"
#include "jwmStructs.h"
#include "curveMath.h"
#include "jwmTransformMesh.h"

//Get the code from each jumper wire element, then obtain the basic points. 
void sampleAndMeshJumperWires(Common& common, Context& context){
for(int i = 0; i < common.jumperWireTable.size(); i++){
jumperWireModel jwm;

int wireCode[6];
std::memcpy(wireCode, common.jumperWireTable[i].code, sizeof(common.jumperWireTable[i].code)); 

jwm.lead1Pos2D = getPosition(wireCode[0], wireCode[1], wireCode[2]);
jwm.lead2Pos2D = getPosition(wireCode[3], wireCode[4], wireCode[5]);
float wireDistance = getDistance(jwm.lead1Pos2D, jwm.lead2Pos2D);

jwm.wirePos = getMidpoint2D(jwm.lead1Pos2D.x, jwm.lead1Pos2D.y, jwm.lead2Pos2D.x, jwm.lead2Pos2D.y);

calculateCatenaryFromDist(jwm.c, wireDistance);
calculateLogitFunction(jwm.lp, wireDistance);
calculateFitCurve(jwm.fc, jwm.c, jwm.lp, wireDistance);

glm::vec2 apex = glm::vec2(0, -jwm.c.a+ jwm.c.dcOffset);
jwm.catenarySamplePoints = {apex, glm::vec2(0,0), glm::vec2(0,0), jwm.fc.a0};
jwm.logitSamplePoints = {glm::vec2(0,0), glm::vec2(0,0), glm::vec2(0,0), jwm.fc.a2};

float x0, y0;

x0 = lerp(apex.x, jwm.fc.a0.x, 0.333f);
y0 = -jwm.c.a * std::cosh(x0 / jwm.c.a) + jwm.c.dcOffset;
jwm.catenarySamplePoints[1] = glm::vec2(x0, y0);

x0 = lerp(apex.x, jwm.fc.a0.x, 0.667f);
y0 = -jwm.c.a * std::cosh(x0 / jwm.c.a) + jwm.c.dcOffset;
jwm.catenarySamplePoints[2] = glm::vec2(x0, y0);

jwm.logitSamplePoints[0] = glm::vec2(jwm.lp.b, 0.0f);

x0 = lerp(jwm.lp.b, jwm.fc.a2.x, 0.333f);
y0 = -std::log((1 - jwm.lp.a*(x0 - jwm.lp.b) ) / (jwm.lp.a*(x0 - jwm.lp.b) )) + jwm.lp.dcOffset;
jwm.logitSamplePoints[1] = glm::vec2(x0, y0);

x0 = lerp(jwm.lp.b, jwm.fc.a2.x, 0.667f);
y0 = -std::log((1 - jwm.lp.a*(x0 - jwm.lp.b) ) / (jwm.lp.a*(x0 - jwm.lp.b) )) + jwm.lp.dcOffset;
jwm.logitSamplePoints[2] = glm::vec2(x0, y0);

//Next, flip all sample points about vertical axis. 
jwm.flippedCatenarySamplePoints = {glm::vec2(0,0), glm::vec2(0,0), glm::vec2(0,0), glm::vec2(0,0)};
jwm.flippedLogitSamplePoints = {glm::vec2(0,0), glm::vec2(0,0), glm::vec2(0,0), glm::vec2(0,0)};

for(int i = 0; i < 4; i++){
	jwm.flippedCatenarySamplePoints[i].x = -jwm.catenarySamplePoints[i].x;
	jwm.flippedCatenarySamplePoints[i].y = jwm.catenarySamplePoints[i].y;
	jwm.flippedLogitSamplePoints[i].x = -jwm.logitSamplePoints[i].x;
	jwm.flippedLogitSamplePoints[i].y = jwm.logitSamplePoints[i].y;
}
transformAndMeshWire(jwm, context, common, i);

}

}
#endif
