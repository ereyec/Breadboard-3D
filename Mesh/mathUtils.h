glm::mat3 getRotationMatrix(float ang){ //Rotation about the y-axis
	glm::mat3 matrix(
		std::cos(ang), 0, std::sin(ang),
		0, 1, 0,
		-std::sin(ang), 0, std::cos(ang)
	);

	return matrix;
}

float getAngleFromPoints(float x1, float z1, float x2, float z2){
	float O = z2 - z1;
	float A = x2 - x1;
	if(std::abs(A) < 0.001) A = 0.001;
	float angle = std::atan2(O/A); //Note: range is -pi to pi

	return angle;
}

glm::vec2 getMidpoint2D(float x1, float y1, float x2, float y2){
	glm::vec2 midpoint = glm::vec2((x1+x2) / 2.f, (y1+y2) / 2.f);
	return midpoint;
}

float getDistance(glm::vec2 p1, glm::vec2 p2){
	return std::sqrt( (p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y) );
}

void pushV3T2(std::vector<float>& vertices, glm::vec3 vec, glm::vec2 tex){
	vertices.push_back(vec.x);
        vertices.push_back(vec.y);
        vertices.push_back(vec.z);
        vertices.push_back(tex.x);
        vertices.push_back(tex.y);
}

void pushV3(std::vector<float>& vertices, glm::vec3 vec){
	vertices.push_back(vec.x);
        vertices.push_back(vec.y);
        vertices.push_back(vec.z);
}
