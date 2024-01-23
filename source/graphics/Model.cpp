#include "Model.h"

Model::Model(std::vector<float> vertices, std::vector<unsigned int> indices){
	
	VertexBuffer vb(vertices.data(), vertices.size());
	IndexBuffer ib(indices.data(), indices.size());
}

void Model::Render() {
	
}