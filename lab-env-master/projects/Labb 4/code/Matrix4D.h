#pragma once

#include "Vector4D.h"

class Matrix4D {
private:
	float internalMatrix[16];

public:

	Matrix4D() {
		for (int i = 0; i < 16; i++) {
			internalMatrix[i] = 0;
		}
	}

	Matrix4D(Vector4D axis, float rad) {
		for (int i = 0; i < 16; i++) {
			internalMatrix[i] = 0;
		}


		///*
		internalMatrix[0] = axis[0] * axis[0] + (1 - axis[0] * axis[0]) * cos(rad);
		internalMatrix[1] = axis[0] * axis[1] * (1 - cos(rad)) - axis[2] * sin(rad);
		internalMatrix[2] = axis[0] * axis[2] * (1 - cos(rad)) + axis[1] * sin(rad);

		internalMatrix[4] = axis[0] * axis[1] * (1 - cos(rad)) + axis[2] * sin(rad);
		internalMatrix[5] = axis[1] * axis[1] + (1 - axis[1] * axis[1]) * cos(rad);
		internalMatrix[6] = axis[1] * axis[2] * (1 - cos(rad)) - axis[0] * sin(rad);

		internalMatrix[8] = axis[0] * axis[2] * (1 - cos(rad)) - axis[1] * sin(rad);
		internalMatrix[9] = axis[1] * axis[2] * (1 - cos(rad)) + axis[0] * sin(rad);
		internalMatrix[10] = axis[2] * axis[2] + (1 - axis[2] * axis[2]) * cos(rad);
		//*/

		/*
			internalMatrix[0] = 1 + (1 - cos(rad)) * (axis[0] * axis[0] - 1);
			internalMatrix[1] = -axis[2] * sin(rad) + (1 - cos(rad)) * axis[0] * axis[1];
			internalMatrix[2] = axis[1] * sin(rad) + (1 - cos(rad)) * axis[0] * axis[2];

			internalMatrix[4] = axis[2] * sin(rad) + (1 - cos(rad)) * axis[0] * axis[1];
			internalMatrix[5] = 1 + (1 - cos(rad)) * (axis[1] * axis[1] - 1);
			internalMatrix[6] = -axis[0] * sin(rad) + (1 - cos(rad)) * axis[1] * axis[2];

			internalMatrix[8] = -axis[1] * sin(rad) + (1 - cos(rad)) * axis[0] * axis[2];
			internalMatrix[9] = axis[0] * sin(rad) + (1 - cos(rad)) * axis[1] * axis[2];
			internalMatrix[10] = 1 + (1 - cos(rad)) * (axis[2] * axis[2] - 1);
		//*/

		/*
		internalMatrix[0] = cos(rad) + axis[0]* axis[0]* (1 - cos(rad));
		internalMatrix[1] = axis[0]* axis[1] * (1 - cos(rad)) - axis[2] * sin(rad);
		internalMatrix[2] = axis[0]* axis[2] *(1-cos(rad)) + axis[1] * sin(rad);

		internalMatrix[4] = axis[1] * axis[0]* (1- cos(rad)) + axis[2] * sin(rad);
		internalMatrix[5] = cos(rad) + axis[1] * axis[1] * (1 - cos(rad));
		internalMatrix[6] = axis[1] * axis[2] * (1 - cos(rad)) - axis[0]* sin(rad);

		internalMatrix[8] = axis[2] * axis[0]* (1 - cos(rad)) - axis[1] * sin(rad);
		internalMatrix[9] = axis[2] * axis[1] * (1 - cos(rad)) + axis[0]* sin(rad);
		internalMatrix[10] = cos(rad) + axis[0]* axis[0]* (1 - cos(rad));
		//*/
		internalMatrix[15] = 1;

	}

	Matrix4D(char c, float rad) {
		for (int i = 0; i < 16; i++) {
			internalMatrix[i] = 0;
		}

		internalMatrix[0] = 1;
		internalMatrix[5] = 1;
		internalMatrix[10] = 1;
		internalMatrix[15] = 1;

		if (c == 'X') {
			internalMatrix[5] = cos(rad);
			internalMatrix[6] = sin(rad);
			internalMatrix[9] = -sin(rad);
			internalMatrix[10] = cos(rad);
		}
		else if (c == 'Y') {
			internalMatrix[0] = cos(rad);
			internalMatrix[2] = -sin(rad);
			internalMatrix[8] = sin(rad);
			internalMatrix[10] = cos(rad);
		}
		else if (c == 'Z') {
			internalMatrix[0] = cos(rad);
			internalMatrix[1] = -sin(rad);
			internalMatrix[4] = sin(rad);
			internalMatrix[5] = cos(rad);
		}
		else {
			internalMatrix[0] = 0;
			internalMatrix[5] = 0;
			internalMatrix[10] = 0;
			internalMatrix[15] = 0;
		}

	}

	Matrix4D(Vector4D axis, float rad, Vector4D position) {
		for (int i = 0; i < 16; i++) {
			internalMatrix[i] = 0;
		}

		internalMatrix[0] = axis[0] * axis[0] + (1 - axis[0] * axis[0]) * cos(rad);
		internalMatrix[1] = axis[0] * axis[1] * (1 - cos(rad)) - axis[2] * sin(rad);
		internalMatrix[2] = axis[0] * axis[2] * (1 - cos(rad)) + axis[1] * sin(rad);

		internalMatrix[4] = axis[0] * axis[1] * (1 - cos(rad)) + axis[2] * sin(rad);
		internalMatrix[5] = axis[1] * axis[1] + (1 - axis[1] * axis[1]) * cos(rad);
		internalMatrix[6] = axis[1] * axis[2] * (1 - cos(rad)) - axis[0] * sin(rad);

		internalMatrix[8] = axis[0] * axis[2] * (1 - cos(rad)) - axis[1] * sin(rad);
		internalMatrix[9] = axis[1] * axis[2] * (1 - cos(rad)) + axis[0] * sin(rad);
		internalMatrix[10] = axis[2] * axis[2] + (1 - axis[2] * axis[2]) * cos(rad);

		internalMatrix[15] = 1;

		this->setPosition(position);
	}

	float getValue(int col, int row) {
		int index = row * 4 + col;
		return internalMatrix[index];
	}

	void setValue(int col, int row, float newValue) {
		int index = row * 4 + col;
		internalMatrix[index] = newValue;
	}

	Matrix4D getRotation() {
		Matrix4D returnMatrix = *this;
		returnMatrix.setValue(3, 0, 0);
		returnMatrix.setValue(3, 1, 0);
		returnMatrix.setValue(3, 2, 0);

		return returnMatrix;
	}

	void setRotation(Matrix4D newRotation) {
		for (int i = 0; i < 4; i++) {
			internalMatrix[i * 4 + 0] = newRotation.getValue(0, i);
			internalMatrix[i * 4 + 1] = newRotation.getValue(1, i);
			internalMatrix[i * 4 + 2] = newRotation.getValue(2, i);
		}
	}

	Vector4D getPosition() {
		Vector4D returnVector(internalMatrix[3], internalMatrix[7], internalMatrix[11], 0);

		return returnVector;
	}

	void setPosition(Vector4D newPosition) {
		internalMatrix[3] = newPosition[0];
		internalMatrix[7] = newPosition[1];
		internalMatrix[11] = newPosition[2];
	}

	Matrix4D operator*(Matrix4D rightMatrix) {
		Matrix4D returnMatrix;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					returnMatrix.setValue(i, j, returnMatrix.getValue(i, j) + this->getValue(i, k) * rightMatrix.getValue(k, j));
				}
			}
		}

		return returnMatrix;
	}

	Vector4D operator*(Vector4D rightVector) {
		Vector4D returnVector;

		returnVector[0] = this->getValue(0, 0) * rightVector[0] + this->getValue(1, 0) * rightVector[1] + this->getValue(2, 0) * rightVector[2] + this->getValue(3, 0) * rightVector[3];
		returnVector[1] = this->getValue(0, 1) * rightVector[0] + this->getValue(1, 1) * rightVector[1] + this->getValue(2, 1) * rightVector[2] + this->getValue(3, 1) * rightVector[3];
		returnVector[2] = this->getValue(0, 2) * rightVector[0] + this->getValue(1, 2) * rightVector[1] + this->getValue(2, 2) * rightVector[2] + this->getValue(3, 2) * rightVector[3];
		returnVector[3] = this->getValue(0, 3) * rightVector[0] + this->getValue(1, 3) * rightVector[1] + this->getValue(2, 3) * rightVector[2] + this->getValue(3, 3) * rightVector[3];

		return returnVector;

	}

	void transpose() {
		int index = 0;
		float newMatrix[16];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				newMatrix[index] = this->getValue(i, j);
				index++;
			}
		}

		for (int i = 0; i < 16; i++) {
			internalMatrix[i] = newMatrix[i];
		}

	}

	bool invert() {
		float invertedMatrix[16];
		double det;
		int i;

		invertedMatrix[0] = internalMatrix[5] * internalMatrix[10] * internalMatrix[15] -
			internalMatrix[5] * internalMatrix[11] * internalMatrix[14] -
			internalMatrix[9] * internalMatrix[6] * internalMatrix[15] +
			internalMatrix[9] * internalMatrix[7] * internalMatrix[14] +
			internalMatrix[13] * internalMatrix[6] * internalMatrix[11] -
			internalMatrix[13] * internalMatrix[7] * internalMatrix[10];

		invertedMatrix[4] = -internalMatrix[4] * internalMatrix[10] * internalMatrix[15] +
			internalMatrix[4] * internalMatrix[11] * internalMatrix[14] +
			internalMatrix[8] * internalMatrix[6] * internalMatrix[15] -
			internalMatrix[8] * internalMatrix[7] * internalMatrix[14] -
			internalMatrix[12] * internalMatrix[6] * internalMatrix[11] +
			internalMatrix[12] * internalMatrix[7] * internalMatrix[10];

		invertedMatrix[8] = internalMatrix[4] * internalMatrix[9] * internalMatrix[15] -
			internalMatrix[4] * internalMatrix[11] * internalMatrix[13] -
			internalMatrix[8] * internalMatrix[5] * internalMatrix[15] +
			internalMatrix[8] * internalMatrix[7] * internalMatrix[13] +
			internalMatrix[12] * internalMatrix[5] * internalMatrix[11] -
			internalMatrix[12] * internalMatrix[7] * internalMatrix[9];

		invertedMatrix[12] = -internalMatrix[4] * internalMatrix[9] * internalMatrix[14] +
			internalMatrix[4] * internalMatrix[10] * internalMatrix[13] +
			internalMatrix[8] * internalMatrix[5] * internalMatrix[14] -
			internalMatrix[8] * internalMatrix[6] * internalMatrix[13] -
			internalMatrix[12] * internalMatrix[5] * internalMatrix[10] +
			internalMatrix[12] * internalMatrix[6] * internalMatrix[9];

		invertedMatrix[1] = -internalMatrix[1] * internalMatrix[10] * internalMatrix[15] +
			internalMatrix[1] * internalMatrix[11] * internalMatrix[14] +
			internalMatrix[9] * internalMatrix[2] * internalMatrix[15] -
			internalMatrix[9] * internalMatrix[3] * internalMatrix[14] -
			internalMatrix[13] * internalMatrix[2] * internalMatrix[11] +
			internalMatrix[13] * internalMatrix[3] * internalMatrix[10];

		invertedMatrix[5] = internalMatrix[0] * internalMatrix[10] * internalMatrix[15] -
			internalMatrix[0] * internalMatrix[11] * internalMatrix[14] -
			internalMatrix[8] * internalMatrix[2] * internalMatrix[15] +
			internalMatrix[8] * internalMatrix[3] * internalMatrix[14] +
			internalMatrix[12] * internalMatrix[2] * internalMatrix[11] -
			internalMatrix[12] * internalMatrix[3] * internalMatrix[10];

		invertedMatrix[9] = -internalMatrix[0] * internalMatrix[9] * internalMatrix[15] +
			internalMatrix[0] * internalMatrix[11] * internalMatrix[13] +
			internalMatrix[8] * internalMatrix[1] * internalMatrix[15] -
			internalMatrix[8] * internalMatrix[3] * internalMatrix[13] -
			internalMatrix[12] * internalMatrix[1] * internalMatrix[11] +
			internalMatrix[12] * internalMatrix[3] * internalMatrix[9];

		invertedMatrix[13] = internalMatrix[0] * internalMatrix[9] * internalMatrix[14] -
			internalMatrix[0] * internalMatrix[10] * internalMatrix[13] -
			internalMatrix[8] * internalMatrix[1] * internalMatrix[14] +
			internalMatrix[8] * internalMatrix[2] * internalMatrix[13] +
			internalMatrix[12] * internalMatrix[1] * internalMatrix[10] -
			internalMatrix[12] * internalMatrix[2] * internalMatrix[9];

		invertedMatrix[2] = internalMatrix[1] * internalMatrix[6] * internalMatrix[15] -
			internalMatrix[1] * internalMatrix[7] * internalMatrix[14] -
			internalMatrix[5] * internalMatrix[2] * internalMatrix[15] +
			internalMatrix[5] * internalMatrix[3] * internalMatrix[14] +
			internalMatrix[13] * internalMatrix[2] * internalMatrix[7] -
			internalMatrix[13] * internalMatrix[3] * internalMatrix[6];

		invertedMatrix[6] = -internalMatrix[0] * internalMatrix[6] * internalMatrix[15] +
			internalMatrix[0] * internalMatrix[7] * internalMatrix[14] +
			internalMatrix[4] * internalMatrix[2] * internalMatrix[15] -
			internalMatrix[4] * internalMatrix[3] * internalMatrix[14] -
			internalMatrix[12] * internalMatrix[2] * internalMatrix[7] +
			internalMatrix[12] * internalMatrix[3] * internalMatrix[6];

		invertedMatrix[10] = internalMatrix[0] * internalMatrix[5] * internalMatrix[15] -
			internalMatrix[0] * internalMatrix[7] * internalMatrix[13] -
			internalMatrix[4] * internalMatrix[1] * internalMatrix[15] +
			internalMatrix[4] * internalMatrix[3] * internalMatrix[13] +
			internalMatrix[12] * internalMatrix[1] * internalMatrix[7] -
			internalMatrix[12] * internalMatrix[3] * internalMatrix[5];

		invertedMatrix[14] = -internalMatrix[0] * internalMatrix[5] * internalMatrix[14] +
			internalMatrix[0] * internalMatrix[6] * internalMatrix[13] +
			internalMatrix[4] * internalMatrix[1] * internalMatrix[14] -
			internalMatrix[4] * internalMatrix[2] * internalMatrix[13] -
			internalMatrix[12] * internalMatrix[1] * internalMatrix[6] +
			internalMatrix[12] * internalMatrix[2] * internalMatrix[5];

		invertedMatrix[3] = -internalMatrix[1] * internalMatrix[6] * internalMatrix[11] +
			internalMatrix[1] * internalMatrix[7] * internalMatrix[10] +
			internalMatrix[5] * internalMatrix[2] * internalMatrix[11] -
			internalMatrix[5] * internalMatrix[3] * internalMatrix[10] -
			internalMatrix[9] * internalMatrix[2] * internalMatrix[7] +
			internalMatrix[9] * internalMatrix[3] * internalMatrix[6];

		invertedMatrix[7] = internalMatrix[0] * internalMatrix[6] * internalMatrix[11] -
			internalMatrix[0] * internalMatrix[7] * internalMatrix[10] -
			internalMatrix[4] * internalMatrix[2] * internalMatrix[11] +
			internalMatrix[4] * internalMatrix[3] * internalMatrix[10] +
			internalMatrix[8] * internalMatrix[2] * internalMatrix[7] -
			internalMatrix[8] * internalMatrix[3] * internalMatrix[6];

		invertedMatrix[11] = -internalMatrix[0] * internalMatrix[5] * internalMatrix[11] +
			internalMatrix[0] * internalMatrix[7] * internalMatrix[9] +
			internalMatrix[4] * internalMatrix[1] * internalMatrix[11] -
			internalMatrix[4] * internalMatrix[3] * internalMatrix[9] -
			internalMatrix[8] * internalMatrix[1] * internalMatrix[7] +
			internalMatrix[8] * internalMatrix[3] * internalMatrix[5];

		invertedMatrix[15] = internalMatrix[0] * internalMatrix[5] * internalMatrix[10] -
			internalMatrix[0] * internalMatrix[6] * internalMatrix[9] -
			internalMatrix[4] * internalMatrix[1] * internalMatrix[10] +
			internalMatrix[4] * internalMatrix[2] * internalMatrix[9] +
			internalMatrix[8] * internalMatrix[1] * internalMatrix[6] -
			internalMatrix[8] * internalMatrix[2] * internalMatrix[5];

		det = internalMatrix[0] * invertedMatrix[0] + internalMatrix[1] * invertedMatrix[4] + internalMatrix[2] * invertedMatrix[8] + internalMatrix[3] * invertedMatrix[12];

		if (det == 0)
			return false;

		det = 1.0 / det;

		for (i = 0; i < 16; i++)
			internalMatrix[i] = invertedMatrix[i] * det;

		return true;
	}
};