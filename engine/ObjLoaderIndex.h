#pragma once

#include "../OBJLoader.hpp"
#include <cstring>
#include <vector>
#include <string>
#include <stdlib.h>
#include <glm/glm.hpp>

void loadOBJ(
	const char* path,
	std::vector<unsigned int>& vertexIndices,
	std::vector<glm::vec3>& temp_vertices,
	std::vector<glm::vec3>& out_normals,
	std::vector<glm::vec2>& out_uvs) {

	IndexedModel model = OBJModel(path).ToIndexedModel();

	vertexIndices = model.indices;
	temp_vertices = model.positions;
	out_normals = model.normals;
	out_uvs = model.texCoords;

}
