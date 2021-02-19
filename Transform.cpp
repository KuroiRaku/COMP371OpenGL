#include "Transform.hpp"

Transform::Transform(){
     position = glm::vec3(0.0f, 0.0f, 0.0f);
     rotation = glm::vec3(0.0f, 0.0f, 0.0f);
     scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(const glm::vec3& p, const glm::vec3& r, const glm::vec3& s){
     position = p;
     rotation = r;
     scale = s;
}

glm::mat4 Transform::getMatrix() {
     glm::mat4 matrix;

     glm::mat4 positionMatrix = glm::translate(position);
     glm::mat4 rotX = glm::rotate(glm::radians(rotation.x), glm::vec3(1, 0, 0));
     glm::mat4 rotY = glm::rotate(glm::radians(rotation.y), glm::vec3(0, 1, 0));
     glm::mat4 rotZ = glm::rotate(glm::radians(rotation.z), glm::vec3(0, 0, 1));
     glm::mat4 rotationMatrix = rotZ * rotY * rotX;
     glm::mat4 scaleMatrix = glm::scale(scale);

     matrix = positionMatrix * rotationMatrix * scaleMatrix;
     return matrix;
}
