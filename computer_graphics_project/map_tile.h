#pragma once

#include"aabb.h";
#include<string>


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

	GLuint VAO, VBO, EBO;

	std::string type; //floor, platform, niddle, coin, niddle�� �浹�� �� �ϳ� ����, coin�� ���� �ÿ� ���ھ� ����

	glm::mat4 trans;

	glm::vec3 color; // ����, �ؽ�ó ���� ���� gl���� ������ ���� ���� �߰��ϰڽ��ϴ�.




	//-------------------------------------------------
	// ��� �Լ�
	//-------------------------------------------------
	
	MapTile() = default;
	MapTile(float, float, float, const char*, const char*); // x,y,z��ǥ, ��, �ش� ��ü�� Ÿ��

	aabb get_aabb(); //aabb�ڽ� ������

	void update_position(); // ��ġ ��ȯ�� ���� ������Ʈ, �����Ӹ��� ȣ��?
	void gen_buffer();

	void handle_collision(); // ���ڷ� �÷��̾� Ŭ���� �޾ƿ��� �浹�� �� �Լ� ȣ��

};


