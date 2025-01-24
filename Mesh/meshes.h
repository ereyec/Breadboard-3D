#define HOLE_DIST 0.25
#define ELEMENT_CORE_LEN 0.6
#define LEAD_TO_LEAD_LEN 6.0

struct elementVertices{
	inline static glm::vec3 v1 = glm::vec3(-0.3f, 0.1f, 0.f);
	inline static glm::vec3 v2 = glm::vec3(0.3f, 0.1f, 0.f);
	inline static glm::vec3 v3 = glm::vec3(-0.3f, -0.1f, 0.f);
	inline static glm::vec3 v4 = glm::vec3(0.3f, -0.1f, 0.f);
	inline static glm::vec2 t1 = glm::vec2(0, 1);
	inline static glm::vec2 t2 = glm::vec2(1, 1);
	inline static glm::vec2 t3 = glm::vec2(0, 0);
	inline static glm::vec2 t4 = glm::vec2(1, 0);
};

struct leadBaseVertices{
	inline static glm::vec3 l1 = glm::vec3(-0.3f, 0.0f, 0.0f);
	inline static glm::vec3 l2 = glm::vec3(0.3f, 0.0f, 0.0f);
};

//41*0.25 x 119*0.25 = 10.25 x 29.75
struct breadboardVertices{
	inline static glm::vec3 v1 = glm::vec3(0.0f, 0.0f, 0.0f);
	inline static glm::vec3 v2 = glm::vec3(29.75f, 0.0f, 0.0f);
	inline static glm::vec3 v3 = glm::vec3(0.0f, 0.0f, 10.25f);
	inline static glm::vec3 v4 = glm::vec3(29.75f, 0.0f, 10.25f);
	inline static glm::vec2 t1 = glm::vec2(0, 1);
	inline static glm::vec2 t2 = glm::vec2(1, 1);
	inline static glm::vec2 t3 = glm::vec2(0, 0);
	inline static glm::vec2 t4 = glm::vec2(1, 0);
};

struct integratedCircuitVertices{
	glm::vec3 v1 = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 v2 = glm::vec3(0.25f, 0.f, 0.f);
	glm::vec3 v3 = glm::vec3(0.f, 0.f, 1.5f);
	glm::vec3 v4 = glm::vec3(0.25f, 0.f, 1.5f);
};
