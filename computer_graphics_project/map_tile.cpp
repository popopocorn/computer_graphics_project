#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<gl/glm/ext.hpp>
#include<gl/glm/glm.hpp>
#include<gl/glm/gtc/matrix_transform.hpp>
#include"file_open.h"
#include"read_obj.h"
#include"map_tile.h"
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


MapTile::MapTile(float in_x, float in_y, float in_z, const char* m, const char* t) {
	x = in_x;
	y = in_y;
	z = in_z;
	read_obj_file(m, &model);
	type = t;
	box = make_aabb(model);

	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(x, y, z));


}

aabb MapTile::get_aabb() {
	return box;
}


void MapTile::update_position() {
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(x, y, z));
}



aabb make_aabb(const Model m) { // aabb를 만들어 주는 함수, 모델에서 x, y, z각각의 최대, 최소값을 찾아 리턴
	float min_x = std::numeric_limits<float>::max();
	float max_x = std::numeric_limits<float>::min();
	float min_y = std::numeric_limits<float>::max();
	float max_y = std::numeric_limits<float>::min();
	float min_z = std::numeric_limits<float>::max();
	float max_z = std::numeric_limits<float>::min();

	for (int i = 0; i < m.vertex_count; ++i) {
		min_x = std::min(min_x, m.vertices[i].x);
		max_x = std::max(min_x, m.vertices[i].x);

		min_y = std::min(min_y, m.vertices[i].y);
		max_y = std::max(min_y, m.vertices[i].y);

		min_z = std::min(min_z, m.vertices[i].z);
		max_z = std::max(min_z, m.vertices[i].z);
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