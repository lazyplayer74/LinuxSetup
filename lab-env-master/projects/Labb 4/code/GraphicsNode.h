#pragma once

class GraphicsNode {
private:
	MeshResource* Mesh;
	TextureResource* Texture;
	shaderObject* Shader;

	Matrix4D Transform;
public:
	GraphicsNode();
	~GraphicsNode();

	MeshResource* getMesh();
	void setMesh(MeshResource* newMesh);

	TextureResource* getTexture();
	void setTexture(TextureResource* newTexture);

	shaderObject* getShader();
	void setShader(shaderObject* newShader);

	Vector4D getPosition();
	void setPosition(Vector4D newPosition);
	void move(Vector4D movement);

	Matrix4D getRotation();
	void setRotation(Matrix4D newRotation);
	void rotate(Matrix4D rotation);

	Matrix4D getTransform();
	void setTransform(Matrix4D newTransform);

	void setup();

	void draw();
};

inline GraphicsNode::GraphicsNode(){
	this->Mesh = new MeshResource();
	this->Texture = new TextureResource();
	this->Shader = new shaderObject("C:\\Users\\Work\\Desktop\\VertexShader.txt", "C:\\Users\\Work\\Desktop\\PixelShader.txt");

	Transform = Matrix4D(Vector4D(0,0,1,0), 3.141592 * 0, Vector4D(0, 0, 0, 0));
}

inline GraphicsNode::~GraphicsNode() {

}


inline MeshResource* GraphicsNode::getMesh() {
	return Mesh;
}

inline void GraphicsNode::setMesh(MeshResource* newMesh) {
	this->Mesh = newMesh;
}

inline TextureResource* GraphicsNode::getTexture() {
	return Texture;
}

inline void GraphicsNode::setTexture(TextureResource* newTexture) {
	this->Texture = newTexture;
}

inline shaderObject* GraphicsNode::getShader() {
	return Shader;
}

inline void GraphicsNode::setShader(shaderObject* newShader) {
	this->Shader = newShader;
}

inline Vector4D GraphicsNode::getPosition() {
	return Transform.getPosition();
}

inline void GraphicsNode::setPosition(Vector4D newPosition) {
	Transform.setPosition(newPosition);
}

inline void GraphicsNode::move(Vector4D movement) {
	Transform.setPosition(Transform.getPosition() + movement);
}

inline Matrix4D GraphicsNode::getRotation() {
	return Transform.getRotation();
}

inline void GraphicsNode::setRotation(Matrix4D newRotation) {
	Transform.setRotation(newRotation);
}

inline void GraphicsNode::rotate(Matrix4D rotation) {
	Transform.setRotation(Transform.getRotation() * rotation);
}

inline void GraphicsNode::setup() {
	Texture->loadTextureFromFile("C:\\Users\\Work\\Desktop\\container.jpg");//change to local filepath
	Texture->generateTexture();

	Mesh->generateCube();

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

inline void GraphicsNode::draw() {
	Shader->use();

	Mesh->reset();
	Mesh->translate(Transform.getPosition());
	Mesh->rotate(Transform.getRotation());

	Mesh->bindBuffer3D();

	Texture->bindTexture();
	Mesh->draw();
}