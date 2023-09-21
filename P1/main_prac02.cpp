/*---------------------------------------------------------*/
/* ----------------   Práctica 2 --------------------------*/
/*-----------------    2024-1   ---------------------------*/
/*------------- Sanchez Maldonado Mario Alberto  ---------------*/
#include <glew.h>
#include <glfw3.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

GLFWmonitor *monitors;
GLuint VBO[2], VAO[2], EBO[2];
GLuint shaderProgramYellow, shaderProgramColor;

static const char* myVertexShader = "										\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
																			\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);						\n\
}";

static const char* myVertexShaderColor = "									\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
layout (location = 1) in vec3 aColor;										\n\
out vec3 ourColor;															\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos, 1.0);											\n\
	ourColor = aColor;														\n\
}";

// Fragment Shader
static const char* myFragmentShaderYellow = "								\n\
#version 330																\n\
																			\n\
out vec3 finalColor;														\n\
																			\n\
void main()																	\n\
{																			\n\
    finalColor = vec3(1.2f, 3.65f, 1.72f);									\n\
}";

static const char* myFragmentShaderColor = "								\n\
#version 330 core															\n\
out vec4 FragColor;															\n\
in vec3 ourColor;															\n\
																			\n\
void main()																	\n\
{																			\n\
	FragColor = vec4(ourColor, 1.0f);										\n\
}";

void myData(void);
void setupShaders(void);
void display(void);
void getResolution(void);


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}

void myData()
{
	float vertices[] = 
	{
		// positions         //Color
		//Orejas izquierda
		
		-0.4734f,0.63863f, 0.0f,    1.0f, 0.0f, 0.0f, //0 - c
		-0.29605f,0.44354f, 0.0f,	1.0f, 0.0f, 0.0f, //1 - d
		-0.49705f,0.39624f, 0.0f,	1.0f, 0.0f, 0.0f, //2 - e
		-0.45862f,0.26323f, 0.0f,	1.0f, 0.0f, 0.0f, //3 - f
		//Orejas Derecha
		0.46361f,0.63567f, 0.0f,    1.0f, 0.0f, 0.0f,  //4 - h
		0.49908f,0.39624f, 0.0f,	1.0f, 0.0f, 0.0f, //5 - i
		0.45475f,0.25732f, 0.0f,	1.0f, 0.0f, 0.0f, //6 - j
		0.29808f,0.43763f, 0.0f,	1.0f, 0.0f, 0.0f, //7 - g

		-0.00321f,0.44606f, 0.0f,	1.0f, 0.6f, 0.8f, //8 - k

		-0.0f,0.2f, 0.0f,	        1.0f, 0.6f, 0.8f, //9 - m
		-0.22245f,0.10862f, 0.0f,	1.0f, 0.6f, 0.8f, //10 - l
		0.21586,0.10883f, 0.0f,	    1.0f, 0.6f, 0.8f, //11 - n


		// Ojo izquierdo
		-0.34327f,-0.04135f, 0.0f,  0.0f, 1.2f, 0.1f,  //12 - o
		-0.26703f,-0.16149f, 0.0f,	0.0f, 1.2f, 0.1f, //13 - p
		-0.13764f,-0.17536f, 0.0f,	0.0f, 1.2f, 0.1f, //14 - q
		-0.16999f,-0.06445f, 0.0f,	0.0f, 1.2f, 0.1f, //15 - r

		// Ojo Derecho
		0.26438f,-0.16149f, 0.0f,    0.0f, 1.2f, 0.1f,  //16 - u
		0.32677f,-0.05521f, 0.0f,	0.0f, 1.2f, 0.1f, //17 - v
		0.16503f,-0.07138f, 0.0f,	0.0f, 1.2f, 0.1f, //18 - s
		0.12807f,-0.17536f, 0.0f,	0.0f, 1.2f, 0.1f, //19 - t

		-0.58155f,0.11465f, 0.0f,	1.0f, 0.4f, 0.5f, //20 - w
		0.5817f,0.09356f, 0.0f,	    1.0f, 0.4f, 0.5f, //21 - z

		-0.68437f,-0.23934f, 0.0f,	1.0f, 0.4f, 0.5f, //22 - a-1
		-0.25315f,-0.56411f, 0.0f,	    1.0f, 0.4f, 0.5f, //23 - b-1
		0.24843f,-0.5623f, 0.0f,	1.0f, 0.4f, 0.5f, //24 - c-1
		0.67785f,-0.24295f, 0.0f,	    1.0f, 0.4f, 0.5f, //25 - d-1

		//Nariz
		-0.09228f,-0.54896f, 0.0f,  1.0f, 0.2f, 0.5f,  //26 - e-1
		0.08079f,-0.547f, 0.0f,	    1.0f, 0.2f, 0.5f, //27 - i-1
		0.10477f,-0.62194f, 0.0f,	1.0f, 0.2f, 0.5f, //28 - h-1
		0.00259f,-0.66573f, 0.0f,	1.0f, 0.2f, 0.5f, //29 - g-1
		-0.10688,-0.62559f, 0.0f,	1.0f, 0.2f, 0.5f, //30 - f-1

		// boca
		
		0.16922f,-0.70784f, 0.0f,	0.0f, 0.2f, 0.2f, //31 - k-1
		0.00074f,-0.77477f, 0.0f,   0.0f, 0.2f, 0.2f,  //32 - m-1
		-0.18304f,-0.7068f, 0.0f,	0.0f, 0.2f, 0.2f, //33 - l-1
		0.00259f,-0.66573f, 0.0f,	0.0f, 0.2f, 0.2f, //34 - g-1

		-0.54332f,0.79336f, 0.0f,   1.0f, 0.2f, 0.5f,  //35 - n-1
		-0.58155f,0.11465f, 0.0f,	1.0f, 0.2f, 0.5f, //36 - w-1
		-0.45862f,0.26323f, 0.0f,	1.0f, 0.2f, 0.5f, //37 - h-1
		-0.49705f,0.39624f, 0.0f,	1.0f, 0.2f, 0.5f, //38 - g-1
		-0.4734f,0.63863f, 0.0f,	1.0f, 0.2f, 0.5f, //39 - f-1

		-0.54332f,0.79336f, 0.0f,   1.0f, 0.2f, 0.5f,  //40 - n-1
		-0.4734f,0.63863f, 0.0f,    1.0f, 0.0f, 0.0f, //41 - c
		-0.29605f,0.44354f, 0.0f,	1.0f, 0.0f, 0.0f, //42 - d
		-0.14099f, 0.44223f, 0.0f,	0.0f, 0.6f, 1.6f, //43 - g-1


		0.53933f, 0.78848f, 0.0f,   1.0f, 0.2f, 0.5f,  //44 - n-1
		0.46361f,0.63567f, 0.0f,    1.0f, 0.0f, 1.0f,  //45 - h
		0.49908f,0.39624f, 0.0f,	1.0f, 0.0f, 1.0f, //46 - i
		0.45475f,0.25732f, 0.0f,	1.0f, 0.0f, 1.0f, //47 - j
		0.5817f,0.09356f, 0.0f,	    1.0f, 0.4f, 0.5f, //48 - z

		0.53933f, 0.78848f, 0.0f,   1.0f, 0.2f, 0.5f,  //49 - n-1
		0.46361f,0.63567f, 0.0f,    1.0f, 0.0f, 1.0f,  //50 - h
		0.29808f,0.43763f, 0.0f,	1.0f, 0.0f, 1.0f, //51 - g
		0.13699f, 0.43735f, 0.0f,	0.0f, 0.6f, 1.6f, //52 - g-1

	};

	unsigned int indices[] =
	{
		//1, 2, 3,	//Single Triangle
		//0, 1, 3, 4, 9,	//Triangle Fan with 0 as pivot
		//7, 6, 5, 4, 9, 8 //Triangle Fan with 7 as pivot
		
		1, 0, 2, 3, //Triangle Fan with 1 - h as pivot
		4, 5, 6, 7, //Triangle Fan with 4 - h as pivot
		1, 8, 9, 10, 3, //Triangle Fan with 1 - d as pivot
		7, 6, 11, 9, 8, //Triangle Fan with 7 - g as pivot
		12, 13, 14, 15, //Triangle Fan with 12 - o as pivot
		16, 17, 18, 19, //Triangle Fan with 16 - u as pivot
		20, 12, 15, 10, 3, //Triangle Fan with 20 - w as pivot
		6, 11, 18, 17, 21, //Triangle Fan with 6 - j as pivot
		20, 22, 23, 14, 13, 12, //Triangle Fan with 20 - w as pivot
		21, 17, 16, 19, 24, 25, //Triangle Fan with 21 - z as pivot
		26, 27, 28, 29, 30, //Triangle Fan with 26 - e as pivot


		31, 32, 33, 34, //Triangle Fan with 29 - g as pivot

		9, 11,  18, 19, 24,  27,  26, 23, 14, 15, 10, //Triangle Fan with 9 - z as pivot
		//m - n - s - t - c1 - l1 - e1 - b1 - q - r - l

		29, 30, 26, 23, 33,
		//g1 - f1 - e1 - b1 - l1
		29, 28, 27, 24, 31,
		//g1 - h1 - i1 - c1 - k1

		35, 36,37, 38, 39,
		//g1 - h1 - i1 - c1 - k1
		40, 41,42, 43,
		//g1 - h1 - i1 - c1 - k1
		44, 45,46, 47, 48,
		//g1 - h1 - i1 - c1 - k1
		49, 50,51, 52,
		//g1 - h1 - i1 - c1 - k1


	};

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);



	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void setupShaders()
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &myVertexShader, NULL);
	glCompileShader(vertexShader);

	unsigned int vertexShaderColor = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderColor, 1, &myVertexShaderColor, NULL);
	glCompileShader(vertexShaderColor);

	unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderYellow, 1, &myFragmentShaderYellow, NULL);
	glCompileShader(fragmentShaderYellow);

	unsigned int fragmentShaderColor = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderColor, 1, &myFragmentShaderColor, NULL);
	glCompileShader(fragmentShaderColor);


	//Crear el Programa que combina Geometría con Color
	shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramYellow);

	shaderProgramColor = glCreateProgram();
	glAttachShader(shaderProgramColor, vertexShaderColor);
	glAttachShader(shaderProgramColor, fragmentShaderColor);
	glLinkProgram(shaderProgramColor);
	//Check for errors 

	//ya con el Programa, el Shader no es necesario
	glDeleteShader(vertexShader);
	glDeleteShader(vertexShaderColor);
	glDeleteShader(fragmentShaderYellow);
	glDeleteShader(fragmentShaderColor);

}

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 2",NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//My Functions
	//Setup Data to use
	myData();
	//To Setup Shaders
	setupShaders();
    
    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Background color
        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		//Display Section
		glUseProgram(shaderProgramYellow);

		glBindVertexArray(VAO[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);

		glPointSize(10.0);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		//glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(3 * sizeof(float)));
		
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(8 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(13 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(26 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(31 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(36 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(42 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 11, GL_UNSIGNED_INT, (void*)(57 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(68 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(73 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(78 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(83 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(87 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(92 * sizeof(float)));
		//Display Section
		glUseProgram(shaderProgramColor);

		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(0 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(4 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(18 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(22 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 5, GL_UNSIGNED_INT, (void*)(48 * sizeof(float)));
		glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, (void*)(53 * sizeof(float)));
		

		glBindVertexArray(0);
		glUseProgram(0);

		//End of Display Section

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);  //Close
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}