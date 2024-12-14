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

	float init_x;
	float init_y;
	float init_z;

	float max_dx{ 2.0f };//�ִ� �̵� ����(�����̴� ������ ��)
	float max_dy{ 2.0f };
	float max_dz{ 2.0f };

	float speed{ 0.005f }; //���� �̵� �ӵ�


	float dx; // ���� ��ȭ��
	float dy;
	float dz;

	Model model;

	aabb box;

	GLuint VAO, VBO, NBO;

	std::string type; //floor, platform, niddle, coin, niddle�� �浹�� �� �ϳ� ����, coin�� ���� �ÿ� ���ھ� ����

	glm::mat4 trans;

	glm::vec3 color; // ����, �ؽ�ó ���� ���� gl���� ������ ���� ���� �߰��ϰڽ��ϴ�.




	//-------------------------------------------------
	// ��� �Լ�
	//-------------------------------------------------
	
	MapTile() = default;
	MapTile(float, float, float, const char*, const char*, glm::vec3); // x,y,z��ǥ, ��, �ش� ��ü�� Ÿ��, ��

	aabb get_aabb(); //aabb�ڽ� ������

	void update_position(); // ��ġ ��ȯ�� ���� ������Ʈ, �����Ӹ��� ȣ��?
	void gen_buffer();
	void move_x();
	void move_y();
	void move_z();
	void handle_collision(); // ���ڷ� �÷��̾� Ŭ���� �޾ƿ��� �浹�� �� �Լ� ȣ��

};


