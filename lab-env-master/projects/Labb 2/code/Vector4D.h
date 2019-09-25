#pragma once

#include <math.h>

class Vector4D {
private:
	float internalVector[4];
	float lenght;
	bool isLenghtUpToDate;

public:

	//Default constructor
	Vector4D() {
		internalVector[0] = 0;
		internalVector[1] = 0;
		internalVector[2] = 0;
		internalVector[3] = 0;

		lenght = 0;
		isLenghtUpToDate = true;
	}

	//Constructor
	Vector4D(float x, float y, float z, float w) {
		internalVector[0] = x;
		internalVector[1] = y;
		internalVector[2] = z;
		internalVector[3] = w;

		lenght = 0;
		isLenghtUpToDate = false;
	}

	float& operator[](int index) {
		return internalVector[index];
	}

	Vector4D operator+(Vector4D rightVector) {
		Vector4D returnVector;
		returnVector[0] = internalVector[0] + rightVector[0];
		returnVector[1] = internalVector[1] + rightVector[1];
		returnVector[2] = internalVector[2] + rightVector[2];
		returnVector[3] = internalVector[3] + rightVector[3];

		return returnVector;
	}

	void operator+=(Vector4D rightVector) {
		internalVector[0] += rightVector[0];
		internalVector[1] += rightVector[1];
		internalVector[2] += rightVector[2];
		internalVector[3] += rightVector[3];
		isLenghtUpToDate = false;
	}

	Vector4D operator-(Vector4D rightVector) {
		Vector4D returnVector;
		returnVector[0] = internalVector[0] - rightVector[0];
		returnVector[1] = internalVector[1] - rightVector[1];
		returnVector[2] = internalVector[2] - rightVector[2];
		returnVector[3] = internalVector[3] - rightVector[3];

		return returnVector;
	}

	void operator-=(Vector4D rightVector) {
		internalVector[0] -= rightVector[0];
		internalVector[1] -= rightVector[1];
		internalVector[2] -= rightVector[2];
		internalVector[3] -= rightVector[3];

		isLenghtUpToDate = false;
	}

	Vector4D operator*(float x) {
		Vector4D returnVector;

		returnVector[0] = internalVector[0] * x;
		returnVector[1] = internalVector[1] * x;
		returnVector[2] = internalVector[2] * x;
		returnVector[3] = internalVector[3] * x;

		return returnVector;
	}

	float getLenght() {
		if (isLenghtUpToDate) {
			return lenght;
		}

		lenght = sqrt(internalVector[0] * internalVector[0] + internalVector[1] * internalVector[1] + internalVector[2] * internalVector[2] + internalVector[3] * internalVector[3]);
		isLenghtUpToDate = true;
		return lenght;
	}

	void Normalize() {
		float l = this->getLenght();

		internalVector[0] /= l;
		internalVector[1] /= l;
		internalVector[2] /= l;
		internalVector[3] /= l;

		lenght = 1;

		isLenghtUpToDate = true;
	}

	int operator*(Vector4D rightVector) {
		return internalVector[0] * rightVector[0] + internalVector[1] * rightVector[1] + internalVector[2] * rightVector[2] + internalVector[3] * rightVector[3];
	}

	Vector4D crossProduct(Vector4D rightVector) {
		Vector4D returnVector;

		returnVector[0] = internalVector[1] * rightVector[2] - internalVector[2] * rightVector[1];
		returnVector[1] = internalVector[1] * rightVector[3] - internalVector[3] * rightVector[1];
		returnVector[2] = internalVector[3] * rightVector[2] - internalVector[2] * rightVector[3];
		returnVector[3] = 0;

		return returnVector;
	}
};