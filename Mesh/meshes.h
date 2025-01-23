#define HOLE_DIST 0.25
#define ELEMENT_CORE_LEN 0.6
#define LEAD_TO_LEAD_LEN 6.0

struct elementVertices{
	glm::vec3 v1 = glm::vec3(-0.3f, 0.1f, 0.f);
	glm::vec3 v2 = glm::vec3(0.3f, 0.1f, 0.f);
	glm::vec3 v3 = glm::vec3(-0.3f, -0.1f, 0.f);
	glm::vec3 v4 = glm::vec3(0.3f, -0.1f, 0.f);
	glm::vec2 t1;
	glm::vec2 t2;
	glm::vec2 t3;
	glm::vec2 t4;
};

struct leadBaseVertices{
	glm::vec3 l1 = glm::vec3(-0.3f, 0.0f, 0.0f);
	glm::vec3 l2 = glm::vec3(0.3f, 0.0f, 0.0f);
};