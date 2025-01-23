/*Maps breadboard code to a vec3 position*/

glm::vec2 getPosition(int half, int row, int col){
	glm::ivec2 pivot; //glm::ivec2(row, col)

	if(half == 70){ //'F'
		if(row > 1){
			pivot = glm::ivec2(31, 1);
			pivot.x -= (row - 2) * 2;
			pivot.y += col * 2;
		}else{
			pivot = glm::ivec2(39, 1);	
			pivot.x -= row * 2;
			pivot.y += col * 2;	
		}
	}
	if(half == 65){ //'A'
		if(row > 1){
			pivot = glm::ivec2(9, 1);
			pivot.x += row * 2;
			pivot.y += col * 2;
		}else{
			pivot = glm::ivec2(1, 1);
			pivot.x += (row - 2) * 2;
			pivot.y += col * 2;
		}
	}

	glm::vec2 position = glm::vec2(pivot.y * 0.25f, pivot.x * 0.25f); //!!
	
	return position;
}