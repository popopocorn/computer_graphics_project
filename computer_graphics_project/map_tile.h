#pragma once
#include"read_obj.h"
#include"aabb.h";



struct MapTile
{
	//-------------------------------------------------
	// ��� ����
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
	// ��� �Լ�
	//-------------------------------------------------
	
	MapTile() = default;
	MapTile(float, float, float, char *, char*); // x,y,z��ǥ, ��, �ش� ��ü�� Ÿ��

	aabb get_aabb(); //aabb�ڽ� ������

	void update_position(); // ��ġ ��ȯ�� ���� ������Ʈ

	


};