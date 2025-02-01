glm::vec2 apex = glm::vec2(0, -c.a+ c.dcOffset);
std::vector<glm::vec2> catenarySamplePoints = {apex, glm::vec2(0,0), glm::vec2(0,0), fc.a0};
std::vector<glm::vec2> logitSamplePoints = {glm::vec2(0,0), glm::vec2(0,0), glm::vec2(0,0), fc.a2};

float x0, y0;

x0 = lerp(apex.x, fc.a0.x, 0.333f);
y0 = -c.a * std::cosh(x0 / c.a) + c.dcOffset;
catenarySamplePoints[1] = glm::vec2(x0, y0);

x0 = lerp(apex.x, fc.a0.x, 0.667f);
y0 = -c.a * std::cosh(x0 / c.a) + c.dcOffset;
 catenarySamplePoints[2] = glm::vec2(x0, y0);

logitSamplePoints[0] = glm::vec2(lp.b, 0.0f);

x0 = lerp(lp.b, fc.a2.x, 0.333f);
y0 = -std::log((1 - lp.a*(x0 - lp.b) ) / (lp.a*(x0 - lp.b) )) + lp.dcOffset;
logitSamplePoints[1] = glm::vec2(x0, y0);

x0 = lerp(lp.b, fc.a2.x, 0.667f);
y0 = -std::log((1 - lp.a*(x0 - lp.b) ) / (lp.a*(x0 - lp.b) )) + lp.dcOffset;
logitSamplePoints[2] = glm::vec2(x0, y0);

//Next, flip all sample points about vertical axis. 

std::vector<glm::vec2> flippedCatenarySamplePoints = {catenarySamplePoints[0], 
catenarySamplePoints[1], catenarySamplePoints[2], catenarySamplePoints[3]};

std::vector<glm::vec2> flippedLogitSamplePoints = {logitSamplePoints[0], 
logitSamplePoints[1], logitSamplePoints[2], logitSamplePoints[3]};


