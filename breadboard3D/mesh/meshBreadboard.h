#ifndef MESHBREADBOARD_H
#define MESHBREADBOARD_H

#include "../common.h"
#include "../context.h"
#include "meshes.h"
#include "./jumper_wire_model/sampler.h"

/*Creates the vertex data for the breadboard, then buffers it to the GPU*/
void meshBreadboard(Common& common, Context& context){

//Elements and their leads
for(int i = 0; i < common.elementTable.size(); i++){
	//Element Vertices (Textured)
	//Retrieve the code:
	int h1 = common.elementTable[i].code[0];
	int x1 = common.elementTable[i].code[1];
	int y1 = common.elementTable[i].code[2];
	int h2 = common.elementTable[i].code[3];
	int x2 = common.elementTable[i].code[4];
	int y2 = common.elementTable[i].code[5];
	
	glm::vec2 lead1Pos2D = getPosition(h1, x1, y1);
	glm::vec2 lead2Pos2D = getPosition(h2, x2, y2);
	glm::vec2 elementPos2D = getMidpoint2D(lead1Pos2D.x, lead1Pos2D.y, lead2Pos2D.x, lead2Pos2D.y);
	glm::vec3 elementPos3D = glm::vec3(elementPos2D.x, 2.f, elementPos2D.y);
	
	float xzAngle = getAngleFromPoints(lead1Pos2D.x, lead1Pos2D.y, lead2Pos2D.x, lead2Pos2D.y);

	glm::mat3 rotationMatrix = getRotationMatrix(xzAngle);

	glm::vec3 v1 = (rotationMatrix * elementVertices::v1) + elementPos3D;
	glm::vec3 v2 = (rotationMatrix * elementVertices::v2) + elementPos3D;
	glm::vec3 v3 = (rotationMatrix * elementVertices::v3) + elementPos3D;
	glm::vec3 v4 = (rotationMatrix * elementVertices::v4) + elementPos3D;

	glm::vec2 t1;
	glm::vec2 t2;
	glm::vec2 t3;
	glm::vec2 t4;

	if(common.elementTable[i].type == R){
		t1 = elementVertices::t1;
		t2 = elementVertices::t2;
		t3 = elementVertices::t5;
		t4 = elementVertices::t6;
	}
	else if(common.elementTable[i].type == C){
		t1 = elementVertices::t2;
		t2 = elementVertices::t3;
		t3 = elementVertices::t6;
		t4 = elementVertices::t7;
	}
	else if(common.elementTable[i].type == D){
		t1 = elementVertices::t3;
		t2 = elementVertices::t4;
		t3 = elementVertices::t7;
		t4 = elementVertices::t8;
	}

	

	pushV3T2(context.tVertexData,v1, t1);
	pushV3T2(context.tVertexData,v2, t2);
	pushV3T2(context.tVertexData,v3, t3);
	pushV3T2(context.tVertexData,v2, t2);
	pushV3T2(context.tVertexData,v3, t3);
	pushV3T2(context.tVertexData,v4, t4);

	//Lead Vertices (GL_LINES)
	glm::vec3 lead1Pos3D = glm::vec3(lead1Pos2D.x, 0.0f, lead1Pos2D.y);
	glm::vec3 lead2Pos3D = glm::vec3(lead2Pos2D.x, 0.0f, lead2Pos2D.y);
	
	glm::vec3 lead1RootPos = (rotationMatrix * leadBaseVertices::l1) + elementPos3D;
	glm::vec3 lead2RootPos = (rotationMatrix * leadBaseVertices::l2) + elementPos3D;
	
	pushV3(context.lVertexData, lead1Pos3D);
	pushV3(context.lVertexData, lead1RootPos);
	pushV3(context.lVertexData, lead2Pos3D);
	pushV3(context.lVertexData, lead2RootPos);

}

//The breadboard
{
	glm::vec3 v1 = breadboardVertices::v1;
	glm::vec3 v2 = breadboardVertices::v2;
	glm::vec3 v3 = breadboardVertices::v3;
	glm::vec3 v4 = breadboardVertices::v4;
	
	pushV3T2(context.oVertexData, v1, breadboardVertices::t3);
	pushV3T2(context.oVertexData, v2, breadboardVertices::t1);
	pushV3T2(context.oVertexData, v3, breadboardVertices::t4);
	pushV3T2(context.oVertexData, v2, breadboardVertices::t1);
	pushV3T2(context.oVertexData, v3, breadboardVertices::t4);
	pushV3T2(context.oVertexData, v4, breadboardVertices::t2);

	glm::vec3 color = glm::vec3(0.82f, 0.8f, 0.741f);
	pushV3C3(context.cVertexData, breadboardVertices::v1, color);
	pushV3C3(context.cVertexData, breadboardVertices::v3, color);
	pushV3C3(context.cVertexData, breadboardVertices::v5, color);
	pushV3C3(context.cVertexData, breadboardVertices::v3, color);
	pushV3C3(context.cVertexData, breadboardVertices::v5, color);
	pushV3C3(context.cVertexData, breadboardVertices::v7, color);

	color = glm::vec3(0.87f, 0.86f, 0.82f);
	pushV3C3(context.cVertexData, breadboardVertices::v1, color);
	pushV3C3(context.cVertexData, breadboardVertices::v2, color);
	pushV3C3(context.cVertexData, breadboardVertices::v5, color);
	pushV3C3(context.cVertexData, breadboardVertices::v2, color);
	pushV3C3(context.cVertexData, breadboardVertices::v5, color);
	pushV3C3(context.cVertexData, breadboardVertices::v6, color);

	color = glm::vec3(0.82f, 0.8f, 0.741f);
	pushV3C3(context.cVertexData, breadboardVertices::v4, color);
	pushV3C3(context.cVertexData, breadboardVertices::v2, color);
	pushV3C3(context.cVertexData, breadboardVertices::v8, color);
	pushV3C3(context.cVertexData, breadboardVertices::v2, color);
	pushV3C3(context.cVertexData, breadboardVertices::v8, color);
	pushV3C3(context.cVertexData, breadboardVertices::v6, color);

	color = glm::vec3(0.87f, 0.86f, 0.82f);
	pushV3C3(context.cVertexData, breadboardVertices::v3, color);
	pushV3C3(context.cVertexData, breadboardVertices::v4, color);
	pushV3C3(context.cVertexData, breadboardVertices::v7, color);
	pushV3C3(context.cVertexData, breadboardVertices::v4, color);
	pushV3C3(context.cVertexData, breadboardVertices::v7, color);
	pushV3C3(context.cVertexData, breadboardVertices::v8, color);

	color = glm::vec3(0.925f, 0.929f, 0.906f);
	pushV3C3(context.cVertexData, breadboardVertices::v5, color);
	pushV3C3(context.cVertexData, breadboardVertices::v6, color);
	pushV3C3(context.cVertexData, breadboardVertices::v7, color);
	pushV3C3(context.cVertexData, breadboardVertices::v6, color);
	pushV3C3(context.cVertexData, breadboardVertices::v7, color);
	pushV3C3(context.cVertexData, breadboardVertices::v8, color);
	

	//Todo: Place IC vertices (if applicable here)
	if(common.numPins != -1){
		v1 = integratedCircuitVertices::v1;
		v2 = integratedCircuitVertices::v2;
		v3 = integratedCircuitVertices::v3;
		v4 = integratedCircuitVertices::v4;

		float scale = (common.numPins / 2.f) - 1.f;
		v1.z = v1.z * scale;
		v2.z = v2.z * scale;
		v3.z = v3.z * scale + 0.25f;
		v4.z = v4.z * scale + 0.25f;

		glm::vec2 position2D = getPosition(70, 6, 1); //change!!
		glm::vec3 position3D = glm::vec3(position2D.x, 0.0f, position2D.y);
		
		v1 += position3D;
		v2 += position3D;
		v3 += position3D;
		v4 += position3D;


		pushV3T2(context.oVertexData, v1, integratedCircuitVertices::t1);
		pushV3T2(context.oVertexData, v2, integratedCircuitVertices::t2);
		pushV3T2(context.oVertexData, v3, integratedCircuitVertices::t3);
		pushV3T2(context.oVertexData, v2, integratedCircuitVertices::t2);
		pushV3T2(context.oVertexData, v3, integratedCircuitVertices::t3);
		pushV3T2(context.oVertexData, v4, integratedCircuitVertices::t4);

		//first pin
		glm::vec3 gray = glm::vec3(0.5f, 0.5f, 0.5f);
		for(int i = 0; i < common.numPins / 2; i++){			
			pushV3C3(context.cVertexData, icPinVertices::v1 + position3D, gray);
			pushV3C3(context.cVertexData, icPinVertices::v2 + position3D, gray);
			pushV3C3(context.cVertexData, icPinVertices::v3 + position3D, gray);
			pushV3C3(context.cVertexData, icPinVertices::v2 + position3D, gray);
			pushV3C3(context.cVertexData, icPinVertices::v3 + position3D, gray);
			pushV3C3(context.cVertexData, icPinVertices::v4 + position3D, gray);
			position3D += glm::vec3(0.0f, 0.0f, 0.5f);
		}
		position3D = glm::vec3(position2D.x + 7.f/4.f, 0.0f, position2D.y);
		for(int i = 0; i < common.numPins / 2; i++){			
			pushV3C3(context.cVertexData, icPinVertices::v1 + position3D, gray);
			pushV3C3(context.cVertexData, icPinVertices::v2 + position3D, gray);
			pushV3C3(context.cVertexData, icPinVertices::v3 + position3D, gray);
			pushV3C3(context.cVertexData, icPinVertices::v2 + position3D, gray);
			pushV3C3(context.cVertexData, icPinVertices::v3 + position3D, gray);
			pushV3C3(context.cVertexData, icPinVertices::v4 + position3D, gray);
			position3D += glm::vec3(0.0f, 0.0f, 0.5f);
		}

	}
}

//Jumper wires (todo)
//Write test input here.
//common.jumperWireTable.push_back({70, 0, 0, 70, 0, 28});
sampleAndMeshJumperWires(common, context);

glGenVertexArrays(1, &context.tVAO);
glGenBuffers(1, &context.tVBO);
glBindVertexArray(context.tVAO);
glBindBuffer(GL_ARRAY_BUFFER, context.tVBO);
glBufferData(GL_ARRAY_BUFFER, context.tVertexData.size() * sizeof(float), context.tVertexData.data(), GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);

glGenVertexArrays(1, &context.lVAO);
glGenBuffers(1, &context.lVBO);
glBindVertexArray(context.lVAO);
glBindBuffer(GL_ARRAY_BUFFER, context.lVBO);
glBufferData(GL_ARRAY_BUFFER, context.lVertexData.size() * sizeof(float), context.lVertexData.data(), GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);

glGenVertexArrays(1, &context.oVAO);
glGenBuffers(1, &context.oVBO);
glBindVertexArray(context.oVAO);
glBindBuffer(GL_ARRAY_BUFFER, context.oVBO);
glBufferData(GL_ARRAY_BUFFER, context.oVertexData.size() * sizeof(float), context.oVertexData.data(), GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);

glGenVertexArrays(1, &context.cVAO);
glGenBuffers(1, &context.cVBO);
glBindVertexArray(context.cVAO);
glBindBuffer(GL_ARRAY_BUFFER, context.cVBO);
glBufferData(GL_ARRAY_BUFFER, context.cVertexData.size() * sizeof(float), context.cVertexData.data(), GL_STATIC_DRAW);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);

}
#endif