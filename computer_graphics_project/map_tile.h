#pragma once
#include"read_obj.h"
#include"aabb.h";



struct MapTile
{
	//-------------------------------------------------
	// 멤버 변수
	//-------------------------------------------------
	float x;
	float y;
	float z;

	Model model;

	aabb box;

	std::string type;

	glm::mat4 trans;

	glm::vec3 color;




	//-------------------------------------------------
	// 멤버 함수
	//-------------------------------------------------
	
	MapTile() = default;
	MapTile(float, float, float, char *, char*); // x,y,z좌표, 모델, 해당 물체의 타입

	aabb get_aabb(); //aabb박스 얻어오기

	void update_position(); // 위치 변환을 위한 업데이트

	


};