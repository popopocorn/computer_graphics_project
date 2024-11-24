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

}