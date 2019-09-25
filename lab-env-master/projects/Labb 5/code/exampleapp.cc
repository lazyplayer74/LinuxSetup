//------------------------------------------------------------------------------
// exampleapp.cc
// (C) 2015-2018 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "exampleapp.h"
#include <cstring>
//#include <Windows.h>

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
		//this->window->Close();
	});

	if (this->window->Open())
	{
		// set clear color to gray
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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
	GraphicsNode box;
	box.setup();

	bool firstTime = true;
	float mouseX, mouseY;

	
	/*
	shaderObject shader("C:\\Users\\Work\\Desktop\\VertexShader.txt", "C:\\Users\\Work\\Desktop\\PixelShader.txt");


	TextureResource texture;
	texture.loadTextureFromFile("C:\\Users\\Work\\Desktop\\container.jpg");//change to local filepath
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
	*/
	while (this->window->IsOpen())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		this->window->Update();
		
		// do stuff
		/*
		if (GetKeyState('Q') & 0x8000)
		{
			this->window->Close();
		}

		if (GetKeyState('W') & 0x8000)
		{
			box.move(Vector4D(0, 0.001, 0, 0));
		}

		if (GetKeyState('S') & 0x8000)
		{
			box.move(Vector4D(0, -0.001, 0, 0));
		}

		if (GetKeyState('A') & 0x8000)
		{
			box.move(Vector4D(-0.001, 0, 0, 0));
		}

		if (GetKeyState('D') & 0x8000)
		{
			box.move(Vector4D(0.001, 0, 0, 0));
		}

		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
			if (firstTime) {
				POINT p;
				if (GetCursorPos(&p)) {
					mouseX = p.x;
					mouseY = p.y;
				}
				firstTime = false;
			}
			else {
				POINT p;
				if (GetCursorPos(&p)) {
					box.rotate(Matrix4D(Vector4D(0, 1, 0, 0), (p.x - mouseX) / -500));
					box.rotate(Matrix4D(Vector4D(1, 0, 0, 0), (p.y - mouseY) / -500));
					mouseX = p.x;
					mouseY = p.y;
				}
			}
		}
		else {
			firstTime = true;
		}
		*/
		box.draw();

		this->window->SwapBuffers();
	}
}

} // namespace Example