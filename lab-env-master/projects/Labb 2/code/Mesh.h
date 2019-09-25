#pragma once

#include "Vector4D.h"
#include "Matrix4D.h"

class MeshResource {
private:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	float verticies[7 * 4]; // vector of vertecies to bind
	unsigned int indices[6];
public:
	MeshResource();
	~MeshResource();

	void generateSquare();

	void bindBuffer();
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

}

inline void MeshResource::generateSquare() {
	float tempVert[28] =
	{
		-0.5f,	0.5f,	-1,			// pos 0 TL
		0,		1,		0,		1,	// color 0
		0.5f,	0.5f,	-1,			// pos 1 TR
		0,		0,		1,		1,	// color 1
		-0.5f,	-0.5f,	-1,			// pos 2 BL
		0,		0,		1,		1,	// color 2
		0.5f,	-0.5f,	-1,			// pos 3 BR
		0,		1,		0,		1	// color 3
	};

	for (int i = 0; i < 28; i++) {
		verticies[i] = tempVert[i];
	}

	int tempInd[6] = { 0,3,2,0,3,1 };

	for (int i = 0; i < 6; i++) {
		indices[i] = tempInd[i];
	}
}

inline void MeshResource::bindBuffer() {
	/*unsigned int VBO;
	glGenBuffers(1, &VBO);*/

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW); //change to dynamic or stream when moving object
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float32) * 7, (GLvoid*)(sizeof(float32) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
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
	for (int i = 0; i < 4; i++) {
		Vector4D tempTranslation(verticies[i * 7 + 0], verticies[i * 7 + 1], verticies[i * 7 + 2], 0);
		
		tempTranslation += translation;

		verticies[i * 7 + 0] = tempTranslation[0];
		verticies[i * 7 + 1] = tempTranslation[1];
		verticies[i * 7 + 2] = tempTranslation[2];
	}
}

inline void MeshResource::rotate(Matrix4D rotationMatrix) {

	float Cx, Cy;

	Cx = (verticies[0] + verticies[21]) / 2;
	Cy = (verticies[1] + verticies[22]) / 2;

	//Rotate
	for (int i = 0; i < 4; i++) {
		Vector4D tempTranslation(verticies[i * 7 + 0], verticies[i * 7 + 1], verticies[i * 7 + 2], 0);

		tempTranslation[0] -= Cx;
		tempTranslation[1] -= Cy;

		tempTranslation = rotationMatrix * tempTranslation;

		tempTranslation[0] += Cx;
		tempTranslation[1] += Cy;

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