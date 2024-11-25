#pragma once
#include"read_obj.h"
#include"aabb.h";



struct MapTile{
	//-------------------------------------------------
	// ��� ����
	//-------------------------------------------------
	float x;
	float y;
	float z;

	float max_dx;//�ִ� �̵� ����(�����̴� ������ ��)
	float max_dy;
	float max_dz;

	Model model;

	aabb box;

	std::string type; //floor, platform, niddle, niddle�� �浹�� �� �ϳ� ����

	glm::mat4 trans;

	glm::vec3 color; // ����, �ؽ�ó ���� ���� gl���� ������ ���� ���� �߰��ϰڽ��ϴ�.




	//-------------------------------------------------
	// ��� �Լ�
	//-------------------------------------------------
	
	MapTile() = default;
	MapTile(float, float, float, char *, char*); // x,y,z��ǥ, ��, �ش� ��ü�� Ÿ��

	aabb get_aabb(); //aabb�ڽ� ������

	void update_position(); // ��ġ ��ȯ�� ���� ������Ʈ

};