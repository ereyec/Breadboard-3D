#ifndef JWNSTRUCTS_H
#define JWNSTRUCTS_H

struct catenaryParams{
	float a;
	float dcOffset;
};

struct logitParams{
	float a; //determines the width
	float b; //determines the horizontal offset
	float dcOffset;
};

struct fitCurve{
	glm::vec2 a0;
	glm::vec2 a1;
	glm::vec2 a2;
};

struct jumperWireModel{
	catenaryParams c;
	logitParams lp;
	fitCurve fc;
	glm::vec2 lead1Pos2D;
	glm::vec2 lead2Pos2D;
	glm::vec2 wirePos;
	std::vector<glm::vec2> catenarySamplePoints;
	std::vector<glm::vec2> logitSamplePoints;
	std::vector<glm::vec2> flippedCatenarySamplePoints;
	std::vector<glm::vec2> flippedLogitSamplePoints;
};

#endif