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