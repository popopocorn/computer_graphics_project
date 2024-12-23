#include<iostream>
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<gl/freeglut_ext.h>
#include<gl/glm/ext.hpp>
#include<gl/glm/glm.hpp>
#include<gl/glm/gtc/matrix_transform.hpp>
#include"file_open.h"
#include"read_obj.h"
#include<vector>
#include<random>
#include"map_tile.h"


#define green_color glm::vec3(0.0f, 1.0f, 0.0f)
#define blue_color glm::vec3(0.0f, 0.0f, 1.0f)
#define sky_color glm::vec3(0.0f, 0.5f, 1.0f)
#define purple_color glm::vec3(1.0f, 0.0f, 1.0f)
#define brown_color glm::vec3(0.5f, 0.3f, 0.0f)
#define gray_color glm::vec3(0.5f, 0.5f, 0.5f)
#define white_color glm::vec3(1.0f, 1.0f, 1.0f)
#define red_color glm::vec3(1.0f, 0.0f, 0.0f)
#define yellow_color glm::vec3(1.0f, 1.0f, 0.0f)
/*
테스트용 임시 코드 입니다.
화면 출력, aabb 값 확인 등 디버그용 출력을 할 코드 입니다. 개선 사항 있으면 적어주세요
--------------------------------------------------------------------------------------



*/


//미리 선언할거
#define vertex_shader_code "21_Vertex_shader.glsl"
#define fragment_shader_code "21_Fragment_shader.glsl"

//------------------------------------------------------
//콜백함수

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid timer(int);

//------------------------------------------------------
//셰이더 용 선언
GLuint shader_program;
GLuint vertexShader;
GLuint fragmentShader;
GLuint VAO, VBO, EBO;

void make_vertex_shader();
void make_fragment_shader();
GLuint make_shader();
GLvoid init_buffer();
//------------------------------------------------------
//전역변수
GLclampf base_r = 0.0f;
GLclampf base_g = 0.0f;
GLclampf base_b = 0.0f;
GLint width{ 800 }, height{ 600 };

float camera_x;
float camera_y;
float camera_z;
float camera_angle;

//------------------------------------------------------
//필요한 함수 선언
std::random_device(rd);
std::mt19937 g(rd());
//MapTile(float, float, float, char *, char*);


//맵 배열
MapTile map1[] = {
    MapTile(0.0f, 0.0f, 0.0f, "platform.obj", "floor", green_color),//바닥
    MapTile(0.0f, 0.0f, -4.0f, "platform.obj", "platform_x", red_color),//x축으로 움직이는 발판
    MapTile(0.0f, 0.0f, -8.0f, "platform.obj", "platform_y", yellow_color),//y축으로 움직이는 발판
    MapTile(0.0f, 0.0f, -12.0f, "platform.obj", "platform_z", brown_color),//z축으로 움직이는 발판
    MapTile(0.0f, 0.0f, -16.0f, "platform.obj", "floor", green_color),//바닥
    MapTile(0.0f, 0.2f, -16.6f, "niddle.obj", "niddle", red_color),//가시
    MapTile(0.2f, 0.2f, -16.6f, "niddle.obj", "niddle", red_color),//가시
    MapTile(0.4f, 0.2f, -16.6f, "niddle.obj", "niddle", red_color),//가시
    MapTile(0.6f, 0.2f, -16.6f, "niddle.obj", "niddle", red_color),//가시
    MapTile(0.8f, 0.2f, -16.6f, "niddle.obj", "niddle", red_color),//가시
    MapTile(-0.2f, 0.2f, -14.6f, "niddle.obj", "niddle", red_color),//가시
    MapTile(-0.4f, 0.2f, -14.6f, "niddle.obj", "niddle", red_color),//가시
    MapTile(-0.6f, 0.2f, -14.6f, "niddle.obj", "niddle", red_color),//가시
    MapTile(-0.8f, 0.2f, -14.6f, "niddle.obj", "niddle", red_color),//가시
    MapTile(0.0f, 0.0f, -20.0f, "platform.obj", "floor", green_color),//바닥

    MapTile(0.0f, 0.25f, -20.5f, "cube1.obj", "goal", blue_color),//골


};


//------------------------------------------------------
void main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutCreateWindow("Example1");

    glewExperimental = GL_TRUE;
    glewInit();

    make_vertex_shader();
    make_fragment_shader();
    shader_program = make_shader();

    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeyboard);
    glutTimerFunc(10, timer, 0);

    glEnable(GL_DEPTH_TEST);  // 깊이 테스트 활성화
    init_buffer();
    for (MapTile& map : map1) {
        map.gen_buffer();
        
    }
    
    
    
    glutMainLoop();

}

GLvoid drawScene(GLvoid) {

    glClearColor(base_r, base_g, base_b, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_program);

    glValidateProgram(shader_program);


    glEnable(GL_CULL_FACE);

    glm::mat4 proj2 = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 50.0f);
    GLuint projection = glGetUniformLocation(shader_program, "projection");
    proj2 = glm::translate(proj2, glm::vec3(0.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(proj2));


    glm::mat4 view(1.0f);

    glm::vec3 camera_pos(0.0f, 0.0f, 0.0f);
    glm::vec3 camera_target(0.0, 0.0, -1.0);
    glm::vec3 camera_up(0.0f, 1.0f, 0.0f);
    view = glm::lookAt(camera_pos, camera_target, camera_up);


    view = glm::rotate(view, glm::radians(camera_angle), glm::vec3(0.0f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(camera_x, camera_y, camera_z - 10.0f));
    
    GLuint view_mat = glGetUniformLocation(shader_program, "view");
    glUniformMatrix4fv(view_mat, 1, GL_FALSE, glm::value_ptr(view));

    GLuint trans_mat = glGetUniformLocation(shader_program, "trans");
    GLuint color = glGetUniformLocation(shader_program, "in_color");
    
    for(MapTile w : map1){
        glBindVertexArray(w.VAO);
        w.update_position();
        glUniform3fv(color, 1, glm::value_ptr(w.color));
        glUniformMatrix4fv(trans_mat, 1, GL_FALSE, glm::value_ptr(w.trans));
        glDrawArrays(GL_TRIANGLES, 0, w.model.vertices.size());
    }

    glutSwapBuffers();

}


GLvoid Reshape(int w, int h) {
    glViewport(0, 0, w, h);

}
GLvoid Keyboard(unsigned char key, int x, int y) {
    switch (key) {
  
    case 'w':
        camera_z += 0.5f;
        break;

    case 's':
        camera_z -= 0.5f;
        break;

    case 'y':
        camera_angle += 1.0;
        break;

    case 'Y':
        camera_angle -= 1.0;
        break;

    case 'a':
        camera_x += 0.5f;
        break;

    case 'd':
        camera_x -= 0.5f;
        break;

    case ' ':
        camera_y -= 0.5f;
        break;

    case 'c':
        camera_y += 0.5f;
        break;

    case 'q':
        glutLeaveMainLoop();
        break;

        break;
    }



    glutPostRedisplay();
}

void make_vertex_shader() {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLchar* vertexSource;
    vertexSource = file_to_buf(vertex_shader_code);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
        std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
        return;
    }
    else {
        std::cout << "컴파일 성공\n";
    }
}
void make_fragment_shader() {
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLchar* fragmentSource;
    fragmentSource = file_to_buf(fragment_shader_code);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLint result;
    GLchar errorLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
        std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorLog << std::endl;
        return;
    }
    else {
        std::cout << "컴파일 성공\n";
    }
}
GLuint make_shader() {
    GLuint shader01;
    shader01 = glCreateProgram();
    glAttachShader(shader01, vertexShader);
    glAttachShader(shader01, fragmentShader);

    glLinkProgram(shader01);


    GLint result;
    GLchar errorLog[512];
    glGetProgramiv(shader01, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader01, 512, NULL, errorLog);
        std::cerr << "셰이더 생성 실패\n" << errorLog << std::endl;

    }
    else {
        std::cout << "\n컴파일 성공\n";

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

    }


    glUseProgram(shader01);

    return shader01;

}

GLvoid init_buffer() {


}
GLvoid SpecialKeyboard(int key, int x, int y) {

    glutPostRedisplay();
}
GLvoid timer(int value) {

    for (MapTile& map : map1) {
        if (map.type == "platform_x") {
            map.move_x();
            
        }else if (map.type == "platform_y") {
            map.move_y();
            
        }else if (map.type == "platform_z") {
            map.move_z();

        }

    }

    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}
