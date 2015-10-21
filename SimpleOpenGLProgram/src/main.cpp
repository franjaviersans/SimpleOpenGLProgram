#include "Definitions.h"
#include "VBOQuad.h"
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <string>

using namespace std;

namespace glfwFunc{
	GLFWwindow* glfwWindow;
	VBOQuad * m_quad;
	GLuint program;
	glm::mat4x4 mProjMatrix, mModelViewMatrix;
	
	///< The resizing function
	void resizeCB(GLFWwindow* window, int iWidth, int iHeight){
		if(iHeight == 0) iHeight = 1;
		float ratio = iWidth / float(iHeight);
		glViewport(0, 0, iWidth, iHeight);
		//Set Projection Matrix
		mProjMatrix = glm::perspective(45.f, ratio, 1.0f, 10.0f);
	}

	///< The main rendering function.
	void draw(){
		glClearColor(0.15f, 0.15f, 0.15f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//First Cube
		mModelViewMatrix =  glm::translate(glm::mat4(), glm::vec3(0.0f,0.0f,-2.0f)); 

		//Draw a Quad
		glUseProgram( program );
		{
			GLint loc = glGetUniformLocation(program, "mProjection");
			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mProjMatrix));

			loc = glGetUniformLocation(program, "mModelView");
			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mModelViewMatrix));

			m_quad->Draw();
		}
		glUseProgram( 0 );

		glfwSwapBuffers(glfwWindow);
	}

	///Fucntion to read the shaders
	void readShader (string source, GLuint type){
		ifstream inFile( source.c_str(), ios::in );
		std::stringstream code;
		code << inFile.rdbuf();
		inFile.close();
		string s_code = code.str();

		GLuint shaderHandle = glCreateShader(type);
		const char * c_code = s_code.c_str();
		glShaderSource( shaderHandle, 1, &c_code, NULL );
		// Compile the shader
		glCompileShader(shaderHandle);
		// Compile succeeded, attach shader
		glAttachShader(program, shaderHandle);
	}

	/// Init all data and variables.
	/// @return true if everything is ok, false otherwise
	bool initialize(){
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		//Init GLEW
		glewExperimental = GL_TRUE;
		if(glewInit() != GLEW_OK) 
		{
			return false;
		}

		m_quad = new VBOQuad();

		//Send window size events to AntTweakBar
		glfwSetWindowSizeCallback(glfwWindow, resizeCB);

		//Create shader program
		program = glCreateProgram();
		{
			//Read Vertex Shader
			readShader("./shaders/basic.vert", GL_VERTEX_SHADER);

			//Read Fragment Shader
			readShader("./shaders/basic.frag", GL_FRAGMENT_SHADER);

			//Link program
			glLinkProgram(program);

			//Set attribute locations
			glUseProgram(program);
			{
				glBindAttribLocation(program, WORLD_COORD_LOCATION, "vVertex");
				glBindAttribLocation(program, COLOR_COORD_LOCATION, "vColor");
			}
			glUseProgram( 0 );
		}

		return true;
	}

	/// Here all data must be destroyed + glfwTerminate
	void destroy(){
		// Delete the program
		delete m_quad;
		glDeleteProgram (program);
		glfwDestroyWindow(glfwWindow);
		glfwTerminate();
	}
}

int main(int argc, char** argv){
	if (!glfwInit())	exit(EXIT_FAILURE);
	glfwFunc::glfwWindow = glfwCreateWindow(1024, 768, "Hello GLFW", NULL, NULL);
	if (!glfwFunc::glfwWindow){
		glfwTerminate(); exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(glfwFunc::glfwWindow);
	if(!glfwFunc::initialize()) exit(EXIT_FAILURE);
	glfwFunc::resizeCB(glfwFunc::glfwWindow, 1024, 768);	//just the 1st time

	// main loop!
	while (!glfwWindowShouldClose(glfwFunc::glfwWindow)){
		glfwFunc::draw();
		glfwPollEvents();	//or glfwWaitEvents()
	}

	glfwFunc::destroy();
	return EXIT_SUCCESS;
}
