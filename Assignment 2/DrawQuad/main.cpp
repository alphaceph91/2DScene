#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "soil.h"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

#define USE_INDEX_BUFFER 1
#define NUM_VERTICES 60 // 54 for the scene and 6 for the window
#define NUM_INDICES 72 // indices are only for the scene not for the window

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int shaderProgram;
int vertexShader, fragmentShader;
int positionID, colorID;
int texCoordID, textureID;
int Shader, Texture;

const char * windowFilename = "images/window.png";

bool transparent = true;

GLfloat vertices[] = {
	//2D SCENE
	//TREE 1
		-0.6f, -0.6f, 0.0f,//0
		-0.6f, -0.4f, 0.0f,//1
		-0.4f, -0.6f, 0.0f,//2
		-0.4f, -0.4f, 0.0f,//3

		-0.7f, -0.4f, 0.0f,//4
		-0.3f, -0.4f, 0.0f,//5
		-0.5f, -0.1f, 0.0f,//6

		-0.7f, -0.1f, 0.0f,//7
		-0.3f, -0.1f, 0.0f,//8
		-0.5f, 0.2f, 0.0f,//9

		-0.7f, 0.2f, 0.0f,//10
		-0.3f, 0.2f, 0.0f,//11
		-0.5f, 0.5f, 0.0f,//12

	//TREE 2
		0.1f, -0.3f, 0.0f,//13
		0.1f, -0.1f, 0.0f,//14
		0.3f, -0.3f, 0.0f,//15
		0.3f, -0.1f, 0.0f,//16

		0.0f, -0.1f, 0.0f,//17
		0.4f, -0.1f, 0.0f,//18
		0.2f, 0.2f, 0.0f,//19

		0.0f, 0.2f, 0.0f,//20
		0.4f, 0.2f, 0.0f,//21
		0.2f, 0.5f, 0.0f,//22

		0.0f, 0.5f, 0.0f,//23
		0.4f, 0.5f, 0.0f,//24
		0.2f, 0.8f, 0.0f,//25

	//House 1
		-0.2f, 0.3f, 0.0f,//26
		-0.3f, 0.2f, 0.0f,//27
		 0.1f, 0.3f, 0.0f,//28
		 0.2f, 0.2f, 0.0f,//29

		-0.2f, 0.2f, 0.0f,//30
		-0.2f, 0.0f, 0.0f,//31
		 0.1f, 0.2f, 0.0f,//32
		 0.1f, 0.0f, 0.0f,//33

		-0.1f, 0.1f, 0.0f,//34
		-0.1f, 0.0f, 0.0f,//35
		 0.0f, 0.1f, 0.0f,//36
		 0.0f, 0.0f, 0.0f,//37

	 //House 2
		-0.5f, -0.1f, 0.0f,//38
		-0.4f, -0.1f, 0.0f,//39
		-0.4f, -0.2f, 0.0f,//40
		-0.5f, -0.2f, 0.0f,//41

		-0.5f, -0.2f, 0.0f,//42
		-0.6f, -0.3f, 0.0f,//43
		-0.2f, -0.2f, 0.0f,//44
		-0.1f, -0.3f, 0.0f,//45


		-0.2f, -0.3f, 0.0f,//46
		-0.2f, -0.5f, 0.0f,//47
		-0.5f, -0.5f, 0.0f,//48
		-0.5f, -0.3f, 0.0f,//49

		-0.3f, -0.5f, 0.0f,//50
		-0.4f, -0.5f, 0.0f,//51
		-0.4f, -0.4f, 0.0f,//52
		-0.3f, -0.4f, 0.0f,//53

		//WINDOW
		-0.5f, -0.5f, 0.0f,//54
		-0.5f, 0.5f, 0.0f,//55
		 0.5f, 0.5f, 0.0f,//56

		0.5f, 0.5f, 0.0f,//57
		0.5f, -0.5f, 0.0f,//58
		-0.5f, -0.5f, 0.0f//59
};

GLfloat colors[] = {
	//COLOR FOR THE SCENE
	//TREE 1
	//Brown
	0.5f, 0.35f, 0.05f, 1.0f,
	0.5f, 0.35f, 0.05f, 1.0f,
	0.5f, 0.35f, 0.05f, 1.0f,
	0.5f, 0.35f, 0.05f, 1.0f,

	//Green
	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,

	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,

	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,

	//TREE 2
	//Brown
	0.5f, 0.35f, 0.05f, 1.0f,
	0.5f, 0.35f, 0.05f, 1.0f,
	0.5f, 0.35f, 0.05f, 1.0f,
	0.5f, 0.35f, 0.05f, 1.0f,

	//Green
	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,

	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,

	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,
	0.0f, 1.7f, 0.0f, 1.0f,

	//House 1
	//yellow
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,

	//blue
	0.0f, 0.2f, 0.8f, 1.0f,
	0.0f, 0.2f, 0.8f, 1.0f,
	0.0f, 0.2f, 0.8f, 1.0f,
	0.0f, 0.2f, 0.8f, 1.0f,

	//red
	0.8f, 0.0f, 0.0f, 1.0f,
	0.8f, 0.0f, 0.0f, 1.0f,
	0.8f, 0.0f, 0.0f, 1.0f,
	0.8f, 0.0f, 0.0f, 1.0f,

	//House 2
	//yellow
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,

	//yellow
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,

	//blue
	0.0f, 0.2f, 0.8f, 1.0f,
	0.0f, 0.2f, 0.8f, 1.0f,
	0.0f, 0.2f, 0.8f, 1.0f,
	0.0f, 0.2f, 0.8f, 1.0f,

	//red
	0.8f, 0.0f, 0.0f, 1.0f,
	0.8f, 0.0f, 0.0f, 1.0f,
	0.8f, 0.0f, 0.0f, 1.0f,
	0.8f, 0.0f, 0.0f, 1.0f,

	// COLOR FOR THE WINDOW
	1.0f, 1.0f, 0.0f, 1.0f, //window color with alpha value
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,

	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
};

GLfloat texcoords[] = {
	0.0f, 0.0f,//1
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//2
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//3
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//4
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//5
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//6
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//7
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//8
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//9
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//10
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//11
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//12
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//13
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//14
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,

	0.0f, 0.0f,//15
	1.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f
	
};

GLuint indices[] = { 
	0, 1, 2, 1, 3, 2, 4, 5, 6, 7, 8, 9,
	10, 11, 12, 13, 14, 15, 14, 15, 16,
	17, 18, 19, 20, 21, 22, 23, 24, 25,
	26, 27, 28, 27, 28, 29, 30, 31, 32,
	31, 32, 33, 34, 35, 36, 35, 36, 37,
	38, 39, 40, 38, 40, 41, 42, 43, 44,
	43, 44, 45, 46, 47, 48, 46, 48, 49,
	50, 51, 52, 50, 52, 53
}; //INDICES ONLY FOR THE 2D SCENE

unsigned int vbo;
unsigned int vao;
unsigned int indexBufferID;
unsigned int texture;

// loadFile - loads text file into char* fname
std::string loadFile(const char *fname) {
	std::ifstream file(fname);
	if (!file.is_open()) {
		std::cout << "Unable to open file " << fname << std::endl;
		exit(1);
	}

	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();

	return fileData.str();
}

int loadShaders() {

	int vlength, flength;
	
	std::string vertexShaderString = loadFile("colorShader.vert");

	std::string fragmentShaderString;
	
	// Switch statement loading the shader from their file's, dependant on which is being used

	switch (Shader)
	{
	case 0:
		fragmentShaderString = loadFile("colorShader.frag");
		break;
	case 1:
		fragmentShaderString = loadFile("greyscaleShader.frag");
		break;
	case 2:
		fragmentShaderString = loadFile("windowShader.frag");
		break;
	}

	vlength = vertexShaderString.length();
	flength = fragmentShaderString.length();

	if (vertexShaderString.empty() || fragmentShaderString.empty()) {
		return -1;
	}

	// Vertex shader allocation
	const char *vertexShaderCStr = vertexShaderString.c_str();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (const GLchar **)&vertexShaderCStr, &vlength);
	glCompileShader(vertexShader);

	// Fragment shader allocation
	const char *fragmentShaderCStr = fragmentShaderString.c_str();
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar **)&fragmentShaderCStr, &flength);
	glCompileShader(fragmentShader);

	// Linking shaders to the shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	// Cleaning up variables to reduce memory usage

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void loadTexture() {
		
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height;
	unsigned char* image;

	// Switch statement determining which texture to load, dependant on currentTexture value

	switch (Texture)
	{
	case 0:
		image = SOIL_load_image("images/tile.png", &width, &height, 0, SOIL_LOAD_RGB);
		break;
	case 1:
		image = SOIL_load_image("images/wood.jpg", &width, &height, 0, SOIL_LOAD_RGB);
		break;
	default:
		image = SOIL_load_image(windowFilename, &width, &height, 0, SOIL_LOAD_RGBA);
		break;
	}

	// Nested else if statement, loading the texture as RGB or RGBA, dependant on if it has an alpha channel

	if (image && Texture == 2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else if (image) 
	  {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);
	  } else 
		{
			std::cout << "Failed to load texture: " << SOIL_last_result() << std::endl;
		}

}

void initBuffers() {

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, 9 * NUM_VERTICES*sizeof(GLfloat), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * NUM_VERTICES * sizeof(GLfloat), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, 3 * NUM_VERTICES * sizeof(GLfloat), 4 * NUM_VERTICES* sizeof(GLfloat), colors);

	glBufferSubData(GL_ARRAY_BUFFER, 3 * NUM_VERTICES * sizeof(GLfloat) + 4 * NUM_VERTICES * sizeof(GLfloat), 2 * NUM_VERTICES * sizeof(GLfloat), texcoords);

#ifdef USE_INDEX_BUFFER
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUM_INDICES * sizeof(GLuint), indices, GL_STATIC_DRAW);
#endif

	loadTexture();

	positionID = glGetAttribLocation(shaderProgram, "inVertex");
	colorID = glGetAttribLocation(shaderProgram, "inColor");

	// Accessing the location of the texCoord variable within the shader
	texCoordID = glGetAttribLocation(shaderProgram, "inTexCoord");

	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(3 * NUM_VERTICES * sizeof(GLfloat)));
	
	// Assigning and forwarding the relevant texCoord value for each vertex
	glVertexAttribPointer(texCoordID, 2, GL_FLOAT, GL_FALSE, 0, 
						BUFFER_OFFSET(3 * NUM_VERTICES * sizeof(GLfloat)
							+ NUM_VERTICES * 4 * sizeof(GLfloat)));
	// Accessing the texture variable within the shader, and assigning it the default 0 value
	textureID = glGetUniformLocation(shaderProgram, "tex");
	glUniform1i(textureID,0);

	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);

	// Enabling the texCoordID attribute
	glEnableVertexAttribArray(texCoordID);

}

void renderScene() {
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texture);

#define USE_INDEX_BUFFER
	glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, NULL);
	if (transparent)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Shader = 2;
	Texture = 2;

	loadShaders();
	initBuffers();

	glDrawArrays(GL_TRIANGLES, 54, 6); // 54 is the starting point from where the 
										//function starts drawing the 6 specified vertices for the window.

}

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW Window
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Assignment 2", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	if (!loadShaders()) {
		std::cout << "Failed to initialize shaders" << std::endl;
		return -1;

	}

	initBuffers();
	
	// Main Loop
	while (!glfwWindowShouldClose(window)) {
	
		processInput(window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		renderScene();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		Shader = 1, 
		Texture = 1;

		loadShaders();
		initBuffers();
	}
	else {
		Shader = 0, 
		Texture = 0;

		loadShaders();
		initBuffers();

	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		transparent = false;
	}
	else {
		transparent = true;
		windowFilename = "images/window.png";
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}