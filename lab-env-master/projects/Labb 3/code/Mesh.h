#pragma once

#include "Vector4D.h"
#include "Matrix4D.h"

class MeshResource {
private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	float verticies[7 * 8]; // vector of vertecies to bind
	unsigned int indices[3 * 12];
	float textureCourdinates[2*8];

public:
	MeshResource();
	~MeshResource();

	void generateSquare();
	void generateCube();

	void bindBuffer2D();
	void bindBuffer3D();
	void draw();

	void translate(Vector4D translation);
	void rotate(Matrix4D rotation);

	bool outOfBounds();
};

inline MeshResource::MeshResource() {
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	float temp[21] =
	{
		-0.5f,	-0.5f,	-1,			// pos 0
		0,		0,		0,		1,	// color 0
		0,		0.5f,	-1,			// pos 1
		0,		0,		0,		1,	// color 1
		0.5f,	-0.5f,	-1,			// pos 2
		0,		0,		0,		1	// color 2
	};

	for (int i = 0; i < 21; i++) {
		verticies[i] = temp[i];
	}

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
}

inline MeshResource::~MeshResource() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ARRAY_BUFFER | GL_ELEMENT_ARRAY_BUFFER);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

inline void MeshResource::generateSquare() {
	float tempVert[36] =
	{
		-0.5f,	0.5f,	-1,			// pos 0 TL
		0,		1,		0,		1,	// color 0
		0,		1,					// Texture 0

		0.5f,	0.5f,	-1,			// pos 1 TR
		0,		0,		1,		1,	// color 1
		1,		1,					// Texture 1

		-0.5f,	-0.5f,	-1,			// pos 2 BL
		0,		0,		1,		1,	// color 2
		0,		0,					// Texture 2

		0.5f,	-0.5f,	-1,			// pos 3 BR
		0,		1,		0,		1,	// color 3
		1,		0					// Texture 3
	};

	for (int i = 0; i < 36; i++) {
		verticies[i] = tempVert[i];
	}

	int tempInd[6] = { 0,3,2,0,3,1 };

	for (int i = 0; i < 6; i++) {
		indices[i] = tempInd[i];
	}
}

inline void MeshResource::generateCube() {
	float tempVert[56] =
	{
		-0.5f,	0.5f,	0.5f,			// pos 0 FTL
		1,		0,		0,		1,		// color 0

		0.5f,	0.5f,	0.5f,			// pos 1 FTR
		0,		1,		0,		1,		// color 1
		
		-0.5f,	-0.5f,	0.5f,			// pos 2 FBL
		0,		0,		1,		1,		// color 2

		0.5f,	-0.5f,	0.5f,			// pos 3 FBR
		1,		1,		0,		1,		// color 3

		-0.5f,	0.5f,	-0.5f,			// pos 4 BTL
		1,		0,		1,		1,		// color 4

		0.5f,	0.5f,	-0.5f,			// pos 5 BTR
		0,		1,		1,		1,		// color 5

		-0.5f,	-0.5f,	-0.5f,			// pos 6 BBL
		1,		1,		1,		1,		// color 6

		0.5f,	-0.5f,	-0.5f,			// pos 7 BBR
		0,		0,		0,		1		// color 7
	};

	for (int i = 0; i < 56; i++) {
		verticies[i] = tempVert[i];
	}

	int tempInd[36] = {	0,3,1, //front square
						0,3,2,
						0,5,4, //top square
						0,5,1,
						4,7,5, //back square
						4,7,6,
						2,7,3, //bottom square
						2,7,6,
						0,6,4, //left square
						0,6,2,
						1,7,3, //right square
						1,7,5

	};

	for (int i = 0; i < 36; i++) {
		indices[i] = tempInd[i];
	}
}

inline void MeshResource::bindBuffer2D() {
	/*unsigned int VBO;
	glGenBuffers(1, &VBO);*/

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_DYNAMIC_DRAW); //change to dynamic or stream when moving object
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 9, NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 9, (GLvoid*)(sizeof(float32) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//Texture Setup

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

inline void MeshResource::bindBuffer3D() {
	/*unsigned int VBO;
	glGenBuffers(1, &VBO);*/

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_DYNAMIC_DRAW); //change to dynamic or stream when moving object

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, (GLvoid*)(sizeof(float32) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//Texture Setup

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

inline void MeshResource::draw() {
	/*unsigned int VAO;
	glGenVertexArrays(1, &VAO);*/

	glBindVertexArray(VAO);

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

inline void MeshResource::translate(Vector4D translation) {
	for (int i = 0; i < 8; i++) {
		Vector4D tempTranslation(verticies[i * 7 + 0], verticies[i * 7 + 1], verticies[i * 7 + 2], 0);
		
		tempTranslation += translation;

		verticies[i * 7 + 0] = tempTranslation[0];
		verticies[i * 7 + 1] = tempTranslation[1];
		verticies[i * 7 + 2] = tempTranslation[2];
	}
}

inline void MeshResource::rotate(Matrix4D rotationMatrix) {

	float Cx, Cy, Cz;

	Cx = (verticies[0] + verticies[49]) / 2;
	Cy = (verticies[1] + verticies[50]) / 2;
	Cz = (verticies[2] + verticies[51]) / 2;

	//Rotate
	for (int i = 0; i < 8; i++) {
		Vector4D tempTranslation(verticies[i * 7 + 0], verticies[i * 7 + 1], verticies[i * 7 + 2], 0);

		tempTranslation[0] -= Cx;
		tempTranslation[1] -= Cy;
		tempTranslation[2] -= Cz;

		tempTranslation = rotationMatrix * tempTranslation;

		tempTranslation[0] += Cx;
		tempTranslation[1] += Cy;
		tempTranslation[2] += Cz;

		verticies[i * 7 + 0] = tempTranslation[0];
		verticies[i * 7 + 1] = tempTranslation[1];
		verticies[i * 7 + 2] = tempTranslation[2];
	}
}

inline bool MeshResource::outOfBounds() {
	/*for (int i = 0; i < 4; i++) {
		if (-1 < verticies[i * 7 + 0] < 1 || -1 < verticies[i * 7 + 1] < 1) {
			return false;
		}
	}*/
	float Cx, Cy;

	Cx = (verticies[0] + verticies[21]) / 2;
	Cy = (verticies[1] + verticies[22]) / 2;

	if (Cx > 1 || Cx < -1) {
		return true;
	}
	return false;
}