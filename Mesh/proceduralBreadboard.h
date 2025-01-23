/*Generate a breadboard procedurally (rather than relying on an image)*/

const int HEIGHT = 41;
const int NUM_RAILS  = 59;
const int WIDTH = 59 * 2 + 1;
int nrChannels = 4;

glm::vec3 black = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 lightBeige = glm::vec3(0.925f, 0.929f, 0.906f);
glm::vec3 darkBeige = glm::vec3(0.82f, 0.8f, 0.741f);

float* breadboardTextureData = (float*)malloc(HEIGHT * WIDTH * nrChannels * sizeof(float));

