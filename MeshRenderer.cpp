#include "MeshRenderer.h"
#include "GLDebug.h"
#include <fstream>
#include <regex>
#include "Rendering.h"

namespace Rendering {

	MeshRenderer::MeshRenderer() : Drawable3D()
	{
		_transform = new Transform();
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		glEnableVertexAttribArray(position_index);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::position));

		glEnableVertexAttribArray(uv_index);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::uv)));

		glEnableVertexAttribArray(normal_index);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::normal)));

		glEnableVertexAttribArray(color_index);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::color)));
		
		triangles_streamed = false;
		vertices_streamed = false;
	}

	std::regex vec3_regex("(-?[0-9]+.?[0-9]*) (-?[0-9]+.?[0-9]*) (-?[0-9]+.?[0-9]*)");
	glm::vec3 match_vec3(const std::string & text)
	{
		std::smatch match;
		std::regex_search(text, match, vec3_regex);
		return glm::vec3(std::stof(match[1]), std::stof(match[2]), std::stof(match[3]));
	}


	std::regex header_regex("^[a-z]+");
	std::regex float_regex("-?[0-9]+.?[0-9]*");
	std::regex vertex_regex("([0-9]+)\\/([0-9]*)\\/([0-9]*)");
	std::regex vec2_regex("(-?[0-9]+.?[0-9]*) (-?[0-9]+.?[0-9]*)");
	glm::vec2 match_vec2(const std::string & text)
	{
		std::smatch match;
		std::regex_search(text, match, vec2_regex);
		return glm::vec2(std::stof(match[1]), std::stof(match[2]));
	}


	MeshRenderer::MeshRenderer(std::string filename) : MeshRenderer()
	{
		std::ifstream infile(filename);

		if (!infile.good()) {
			std::cout << "File " << filename << " not found." << std::endl;
		}
		std::vector<glm::vec3> temp_positions;
		std::vector<glm::vec2> temp_texcoords;
		std::vector<glm::vec3> temp_normals;

		std::vector<unsigned int> vertIndices, texcoordIndices, normalIndices;

		//A lookup for getting the Vertex a string represents as well as the index of that Vertex
		std::unordered_map<std::string, std::pair<Vertex, unsigned int>> vertCombinations;

		std::string line;

		while (std::getline(infile, line)) {
			std::smatch match;
			std::regex_search(line, match, header_regex);
			std::string header = match[0];
			if (header == "v") {
				glm::vec3 position = match_vec3(line);
				temp_positions.push_back(position);
			}
			else if (header == "vt") {
				glm::vec2 texcoord = match_vec2(line);
				temp_texcoords.push_back(texcoord);
			}
			else if (header == "vn") {
				glm::vec3 normal = match_vec3(line);
				temp_normals.push_back(normal);
			}
			else if (header == "f") {
				std::string::const_iterator start = line.begin();
				std::string::const_iterator end = line.end();
				int num_verts = 0; //Count the number of vertices, so that if there's a fourth the quad completing triangle can be added
				while (std::regex_search(start, end, match, vertex_regex)) {
					num_verts++;
					Vertex vertex;
					std::unordered_map<std::string, std::pair<Vertex, unsigned int>>::iterator vert_pair = vertCombinations.find(match[0]);
					unsigned int index;
					//If the combination wasn't found, add a new one
					if (vert_pair == vertCombinations.end()) {
						//subtracting to account for 1-indexing instead of 0-indexing
						glm::vec3 position = (temp_positions[std::stoi(match[1]) - 1]);
						glm::vec2 uv = (match[2].str().size() != 0 ? temp_texcoords[std::stoi(match[2]) - 1] : glm::vec2(0.0f, 0.0f));
						glm::vec3 normal = (match[3].str().size() != 0 ? temp_normals[std::stoi(match[3]) - 1] : glm::vec3(0.0f, 0.0f, 0.0f));
						vertex = Vertex(position, uv, normal);
						index = vertices.size();
						vertices.push_back(vertex);
						vertCombinations[match[0]] = std::pair<Vertex, unsigned int>(vertex, index); //Add the new string to VertextFormat mapping
					}
					else {
						//The Vertex already exists, so just get the index (second of the combination) and add that to the triangle
						index = vert_pair->second.second;
					}
					if (num_verts < 4) { //We're still in the first (or only) triangle
						triangles.push_back(index);
					}
					else { //It's a quad, so add a triangle consisting of vertices whos indices are at the end of the triangle vector
						int curr_triangle_size = triangles.size();
						triangles.push_back(triangles[curr_triangle_size - 3]);
						triangles.push_back(triangles[curr_triangle_size - 1]);
						triangles.push_back(index);
					}

					start = match[0].second;
				}
			}
		}
	}


	MeshRenderer::~MeshRenderer()
	{
		delete _transform;
	}
	void MeshRenderer::Draw()
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		if (!vertices_streamed) {
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
			vertices_streamed = true;
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		if (!triangles_streamed) {
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(VertexIndex), triangles.data(), GL_STATIC_DRAW);
			triangles_streamed = true;
		}
		glDrawElements(GL_TRIANGLES, triangles.size(), GL_UNSIGNED_INT, (void*)0);
	}
	Transform * MeshRenderer::GetTransform()
	{
		return _transform;
	}
}