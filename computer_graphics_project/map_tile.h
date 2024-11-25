#pragma once
#include"read_obj.h"
#include"aabb.h";



struct MapTile{
	//-------------------------------------------------
	// 멤버 변수
	//-------------------------------------------------
	float x;
	float y;
	float z;

	float max_dx;//최대 이동 범위(움직이는 발판일 시)
	float max_dy;
	float max_dz;

	Model model;

	aabb box;

	std::string type; //floor, platform, niddle, niddle과 충돌시 구 하나 감소

	glm::mat4 trans;

	glm::vec3 color; // 색상, 텍스처 등은 이후 gl수업 진도에 따라 로직 추가하겠습니다.




	//-------------------------------------------------
	// 멤버 함수
	//-------------------------------------------------
	
	MapTile() = default;
	MapTile(float, float, float, char *, char*); // x,y,z좌표, 모델, 해당 물체의 타입

	aabb get_aabb(); //aabb박스 얻어오기

	void update_position(); // 위치 변환을 위한 업데이트

};