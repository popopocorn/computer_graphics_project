#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<gl/glm/ext.hpp>
#include<gl/glm/glm.hpp>
#include<gl/glm/gtc/matrix_transform.hpp>
#include"file_open.h"
#include"read_obj.h"
#include"map_tile.h"
#include"aabb.h";
#include<string>



/*
	float x;
	float y;
	float z;

	Model model;

	aabb box;

	std::string type;

	glm::mat4 trans;

	glm::vec3 color;
*/


aabb make_aabb(const Model m);


MapTile::MapTile(float in_x, float in_y, float in_z, const char* m, const char* t, glm::vec3 c) {
	init_x = in_x;
	init_y = in_y;
	init_z = in_z;
	read_obj_file(m, &model);
	type = t;
	box = make_aabb(model);

	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(init_x + x, init_y + y, init_z + z));
	color = c;

	dx = speed;
	dy = speed;
	dz = speed;
	std::cout << box;

}
void MapTile::gen_buffer() {
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(Vertex), model.vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, model.nvectors.size() * sizeof(Normal), model.nvectors.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
}

aabb MapTile::get_aabb() {
	return box;
}


void MapTile::update_position() {
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(init_x + x, init_y + y, init_z + z));
}
void MapTile::handle_collision() {
	//������ �������� �����Ͻ� ����Ʈ����
	//�����̸� ���� �÷��ְ� ��ü ����
}


aabb make_aabb(const Model m) { // aabb�� ����� �ִ� �Լ�, �𵨿��� x, y, z������ �ִ�, �ּҰ��� ã�� ����
	float min_x = std::numeric_limits<float>::max();
	float max_x = std::numeric_limits<float>::min();
	float min_y = std::numeric_limits<float>::max();
	float max_y = std::numeric_limits<float>::min();
	float min_z = std::numeric_limits<float>::max();
	float max_z = std::numeric_limits<float>::min();

	for (int i = 0; i < m.vertices.size()-1; ++i) {
		min_x = std::min(min_x, m.vertices[i].x);
		max_x = std::max(max_x, m.vertices[i].x);

		min_y = std::min(min_y, m.vertices[i].y);
		max_y = std::max(max_y, m.vertices[i].y);

		min_z = std::min(min_z, m.vertices[i].z);
		max_z = std::max(max_z, m.vertices[i].z);
	}
	aabb temp = {
		min_x,
		max_x,

		min_y,
		max_y,

		min_z,
		max_z,
	};

	return temp;
}
void MapTile::move_x() {
	x += dx;
	box.min_x += dx;
	box.max_x += dx;
	if (x < -max_dx) {
		dx = -dx;
		std::cout << box << std::endl;
	}
	if (x > max_dx) {
		dx = -dx;
		std::cout << box << std::endl;
	}

};

void MapTile::move_y() {
	y += dy;
	box.min_y += dy;
	box.max_y += dy;
	if (y < -max_dy) {
		dy = -dy;
		std::cout << box << std::endl;
	}
	if (y > max_dy) {
		dy = -dy;
		std::cout << box << std::endl;
	}


};

void MapTile::move_z() {
	z += dz;
	box.min_z += dz;
	box.max_z += dz;
	if (z < -max_dz) {
		dz = -dz;
		std::cout << box << std::endl;
	}
	if (z > max_dz) {
		dz = -dz;
		std::cout << box << std::endl;
	}
	
};