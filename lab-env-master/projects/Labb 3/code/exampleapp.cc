//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>

const GLchar* vs =
"#version 430\n"
"layout(location=0) in vec3 aPos;\n"
"layout(location=1) in vec4 aColor;\n"
"layout(location=2) in vec2 aTexCoord;\n"
"layout(location=0) out vec4 ourColor;\n"
"layout(location=1) out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0);\n"
"	ourColor = aColor;\n"
"	TexCoord = aTexCoord;\n"
"}\n";

const GLchar* ps =
"#version 430\n"
"layout(location=0) in vec4 ourColor;\n"
"layout(location=1) in vec2 TexCoord;\n"
"layout(location=0) out vec4 PixelColor;\n"
"uniform sampler2D ourTexture;\n"
"void main()\n"
"{\n"
//"	Color = color;\n"
"PixelColor = texture(ourTexture, TexCoord);\n"
"}\n";

using namespace Display;
namespace Example
{

//------------------------------------------------------------------------------
/**
*/
ExampleApp::ExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
ExampleApp::~ExampleApp()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
bool
ExampleApp::Open()
{
	App::Open();
	this->window = new Display::Window;
	window->SetKeyPressFunction([this](int32, int32, int32, int32)
	{
		this->window->Close();
	});

	GLfloat buf[] =
	{
		-0.5f,	-0.5f,	-1,			// pos 0
		1,		0,		0,		1,	// color 0
		0,		0.5f,	-1,			// pos 1
		0,		1,		0,		1,	// color 1
		0.5f,	-0.5f,	-1,			// pos 2
		0,		0,		1,		1	// color 2
	};

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		// setup vertex shader
		this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLint length = std::strlen(vs);
		glShaderSource(this->vertexShader, 1, &vs, &length);
		glCompileShader(this->vertexShader);

		// get error log
		GLint shaderLogSize;
		glGetShaderiv(this->vertexShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->vertexShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// setup pixel shader
		this->pixelShader = glCreateShader(GL_FRAGMENT_SHADER);
		length = std::strlen(ps);
		glShaderSource(this->pixelShader, 1, &ps, &length);
		glCompileShader(this->pixelShader);

		// get error log
		shaderLogSize;
		glGetShaderiv(this->pixelShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetShaderInfoLog(this->pixelShader, shaderLogSize, NULL, buf);
			printf("[SHADER COMPILE ERROR]: %s", buf);
			delete[] buf;
		}

		// create a program object
		this->program = glCreateProgram();
		glAttachShader(this->program, this->vertexShader);
		glAttachShader(this->program, this->pixelShader);
		glLinkProgram(this->program);
		glGetProgramiv(this->program, GL_INFO_LOG_LENGTH, &shaderLogSize);
		if (shaderLogSize > 0)
		{
			GLchar* buf = new GLchar[shaderLogSize];
			glGetProgramInfoLog(this->program, shaderLogSize, NULL, buf);
			printf("[PROGRAM LINK ERROR]: %s", buf);
			delete[] buf;
		}

		// setup vbo
		glGenBuffers(1, &this->triangle);
		glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
ExampleApp::Run()
{

	TextureResource texture;
	texture.loadTextureFromFile("C:\\Users\\Work\\Desktop\\container.jpg");//change to local filepath
	//texture.loadTextureFromFile("container");
	texture.generateTexture();


	MeshResource mesh;
	mesh.generateSquare();
	//mesh.generateCube();

	Vector4D translateVector(0.0005, 0, 0, 0);

	Vector4D rotationAxel(1, 1, 1, 0);

	rotationAxel.Normalize();

	Matrix4D rotationMatrix(rotationAxel, 0.0005);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();

		// do stuff

		if (mesh.outOfBounds()) {
			translateVector = translateVector * -1;
		}

		//mesh.rotate(rotationMatrix);

		//mesh.translate(translateVector);

		mesh.bindBuffer2D();
		//mesh.bindBuffer3D();
		//glBindBuffer(GL_ARRAY_BUFFER, this->triangle);
		glUseProgram(this->program);
		//glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, NULL);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, (GLvoid*)(sizeof(float32) * 3));
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		
		texture.bindTexture();
		mesh.draw();
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		this->window->SwapBuffers();
	}
}

} // namespace Example