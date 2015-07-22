// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

#include <common/shader.hpp>

int width, height;

void window_size_callback(GLFWwindow* window, int w, int h) {
	width = w; height = h;

	glViewport(0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double ar = std::max(width, height) / (double) std::min(width, height);
	if (width > height) gluOrtho2D(-ar,ar,-1,1);

	cout << "Resized to: " << width << " x " << height << endl;
}

int main(void) {
	if(!glfwInit()) {
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return 1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	width  = 800;
	height = 600;
	window = glfwCreateWindow(width, height, "Test", NULL, NULL);
	if(window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try 2.1.\n" );
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, window_size_callback);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return 1;
	}

	// Ensure we can capture keys
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("shader.vert", "shader.frag");

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	double lastTime = glfwGetTime();
	int nbFrames = 0;

	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
		double currentTime = glfwGetTime();
		nbFrames++;
		if (currentTime - lastTime >= 1.0) {
			printf("%.2f FPS (%.1f ms)\n", double(nbFrames)/(currentTime-lastTime), 1000./double(nbFrames));
			nbFrames = 0;
			lastTime += currentTime - lastTime;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		// Load shader, set uniforms
		glUseProgram(programID);
		GLint resolutionLocation = glGetUniformLocation(programID, "resolution");
		glUniform2f(resolutionLocation, (float)width, (float)height);
		GLint timeLocation = glGetUniformLocation(programID, "time");
		glUniform1f(timeLocation, (float)glfwGetTime());

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Draw the quad!
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); // 4 indices starting at 0 -> 1 quad

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	glfwTerminate();

	return 0;
}
