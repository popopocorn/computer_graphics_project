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




MapTile::MapTile(float in_x, float in_y, float in_z, char* m, char* t) {
	x = in_x;
	y = in_y;
	z = in_z;
	read_obj_file(m, &model);
	type = t;


}

aabb MapTile::get_aabb() {
	return box;
}


void MapTile::update_position() {
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(x, y, z));
}