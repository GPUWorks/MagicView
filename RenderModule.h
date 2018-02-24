#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include <iostream>

#include "Camera.h"

class RenderModule
{
public:
	RenderModule() {};
	~RenderModule() { clear(); };

	virtual void setVertexShaderSource() = 0;
	virtual void setFragmentShaderSource() = 0;

	virtual void setData(std::vector<float> vd, std::vector<int> id, std::vector<float> nd, std::vector<float> cd) = 0;
	virtual void init() = 0;

	void genVertexBuffer();
	void genIndexBuffer();
	void genNormalBuffer();
	void genColorBuffer();
	virtual void genVertexArray() = 0;


	void setCamera(Camera c);
	void setLightDistance(double d);
	void setLamp();
	void setMatrix();

	virtual void render() = 0;

	void clear();

protected:
	QString vertexShaderSource;
	QString fragmentShaderSource;

	QOpenGLShaderProgram* mProgram;
	QOpenGLVertexArrayObject* mVAO;
	QOpenGLBuffer* mVertex;
	QOpenGLBuffer* mIndex;
	QOpenGLBuffer* mNormal;
	QOpenGLBuffer* mColor;

	QOpenGLBuffer::UsagePattern mPrimType;

	GLuint lightDisID;
	GLuint lightPowerID;

	GLuint mvpID;
	GLuint modelMatrixID;
	GLuint viewMatrixID;

	// data
	std::vector<float> vertexData;
	std::vector<int> indexData;
	std::vector<float> normalData;
	std::vector<float> colorData;
	
	Camera camera;
	double lightDistance;
};

class MeshModule : public RenderModule
{
public:
	MeshModule() {};
	~MeshModule() {};

	void setVertexShaderSource();
	void setFragmentShaderSource();

	void setData(std::vector<float> vd, std::vector<int> id, std::vector<float> nd, std::vector<float> cd);

	void genVertexArray();

	void init();
	void render();
};

class WireFrameModule : public RenderModule
{
public:
	WireFrameModule() {};
	~WireFrameModule() {};

	void setVertexShaderSource();
	void setFragmentShaderSource();

	void setData(std::vector<float> vd, std::vector<int> id, std::vector<float> nd, std::vector<float> cd);

	void genVertexArray();

	void init();
	void render();

};
