#pragma once
#include "Vec3f.h"
#include "Vec4d.h"
#include "Mat4d.h"
#include "Shader.h"
class LineStripGraphics
{
	std::vector<GLdouble> _vertices;
	static const int MaxNumPoints = 100;
	int _pointsNumber = 0;// , _curvePointsNumber = 0;
	
	int _selectedVert = -1;
	GLuint _VAO = -1;
	GLuint _VBO = -1;

	//VERTICES SETTINGS
	unsigned int _stride = 3;
	//unsigned int _curveStride = 3;
	const unsigned int _posLocation = 0;  
	const unsigned int _colorLocation = 1;

	Vec3f _pointsColor = Vec3f(0.0f, 1.0f, 1.0f);
	Vec3f _lineColor = Vec3f(1.0f, 0.0f, 1.0f);

	bool isChanged = false, drawPoints= false;
public:
	LineStripGraphics() { };
	~LineStripGraphics();

	inline bool getDrawPoints() const { return drawPoints; }
	inline void setDrawPoints(bool b) { drawPoints = b; }

	inline bool getChanged() const { return isChanged; }
	inline void setChanged(bool b) { isChanged = b; }

	void setVertices(std::vector<double> vertices);
	std::vector<double> getVertices();
	void clearVertives();

	const double& getControlPt_X(int& i);
	const double& getControlPt_Y(int& i);
	const double& getControlPt_Z(int& i);

	//RENDERING
	void initGL();
	void setupGL();
	void renderScene();
	void cleanGL(GLuint& shaderProgram);

	//POINTS MANIPULATION
	void LoadPointsIntoVBO();
	void AddPoint(double x, double y);
	void ChangePoint(int i, double x, double y, double z);
	void ChangePoint(int i, double x, double y);

	const int getSelectedVert();
	void setSelectedVert(int s);

	void setLineColor(Vec3f col);

	const int getPointsNumber();

	void RemoveFirstPoint();
	void RemoveLastPoint();

	void setLineColor();
	void setLineColor(float r, float g, float b);
	void setColor();
	Vec3f randomColor();
};

