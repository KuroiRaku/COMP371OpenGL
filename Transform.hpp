#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtx/transform.hpp>

struct Transform {

     Transform();
     Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
     glm::mat4 getMatrix();

     glm::vec3 position;
     glm::vec3 rotation;
     glm::vec3 scale;


};

#endif
