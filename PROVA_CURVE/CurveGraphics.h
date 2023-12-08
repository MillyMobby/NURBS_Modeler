#pragma once
#include "Vec3f.h"
#include "Vec4d.h"
#include "Mat4d.h"
#include "Shader.h"
#include "CurveMath.h"
#include "PredefinedCurves.h"
#include "LineStripGraphics.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

class CurveGraphics {
private:

	//POLIGONO DI CONTROLLO
	static const int MaxNumPoints = 200;    
	int _pointsNumber = 0, _curvePointsNumber = 0;
	double* controlPolygon;
	int _selectedVert = -1;
	GLuint _VAO = -1; 
	GLuint _VBO = -1;

	const unsigned int _nElements_position = 4; 	
	const unsigned int _nElements_color = 3;

	//CURVA
	static const int steps = 100;
	double curvePoints[steps * 500];
	GLuint _curveVAO = -1; 
	GLuint _curveVBO = -1;

	CurveMath curveMath;
	std::vector<int> multiplicities;
	PredefinedCurves predefinedCurves;
	std::vector<float> weights = std::vector<float>(100, 0.5);

	//VERTICES SETTINGS
	unsigned int _stride = 4;
	unsigned int _curveStride = 3;
	const unsigned int _posLocation = 0;   // "location = 0"  vertex shader 
	const unsigned int _colorLocation = 1;
	
	Vec3f _pointsColor = Vec3f(0.0f, 1.0f, 1.0f); 
	Vec3f _lineColor = Vec3f(1.0f, 0.0f, 1.0f);
	Vec3f _curveColor = Vec3f(1.0f, 0.7f, 1.0f);
	
	bool isChanged = false, isVisible = false, isSelected = false;
	double tValue;
	Vec3f mouse = Vec3f(0);
	
public:	
	CurveGraphics() {
		controlPolygon = new double[MaxNumPoints * 4]; 
		curveMath.generateKnots();
		curveMath.setDegree(3); // grado di default
	};
	~CurveGraphics();

	inline bool getIsChanged() const { return isChanged; }
	inline void setIsChanged(bool b) { isChanged = b; }

	inline void setMouse(Vec3f pos) { mouse = pos; }

	inline int get_tValue() const { return tValue; }
	inline void set_tValue(int t) { tValue = t; }

	const int getSelectedVert();
	void setSelectedVert(int s);
	void nullVertexSelection();

	const bool isCurveSelected();
	void setSelected(bool s);

	const bool isCurveVisible();
	void setVisible(bool v);
	
	const int getPointsNumber();

	const double& getControlPt_X(int& i);
	const double& getControlPt_Y(int& i);
	const double& getControlPt_W(int& i);

	void setLineColor(/*Vec3f col*/);
	void setCurveColor(/*Vec3f col*/);
	void setColor();
	Vec3f randomColor();
	
	unsigned int calculateStride();
	//RENDERING
	void initGL();
	void initCurveGL();
	void setupGL();
	void cleanGL(GLuint& shaderProgram);

	//POINTS MANIPULATION
	void LoadPointsIntoVBO();
	void LoadPointsIntoCurveVBO();
    void AddPoint(double x, double y);
	void AddCurvePoint(double x, double y);	
    void ChangePoint(int i, double x, double y, double z);
	void ChangePoint(int i, double x, double y);
	void ChangeDegree(int p);
	void modifyCurve();
	void ChangeCurvePoint(int i, double x, double y);

	void rendering(int &deg, bool& makeBezier, bool& makeNURBS, std::vector<float>& w, int curveType);
	void renderScene();
	void renderCurve();	
	
	//ARRAYS CONVERTED IN Vec3d FORMAT
	std::vector<Vec3d> controlPointsVector();
	std::vector<Vec3d>curvePointsVector();
	std::vector<float>getWeights();
	CurveMath getCurveMath();

	//NURBS WEIGHTS 
	void addWeights(std::vector<float> w);
	std::vector<int> getMultiplicityVector();
	void editMultiplicity(int pointIndex);
	void resizeMultiplicities();
	void setMultiplicity(int i);
	inline int getPointMultiplicity(int i) const { return multiplicities[i]; }
	void deleteLastMultiplicity();
	void deleteFirstMultiplicity(int i);

	void setPredefinedCurve(int knotsType, std::vector<float>& w);

    void RemoveFirstPoint(); 
	void RemoveLastPoint();
	void RemoveLastCurvePoint();

	void transformWithCamera(Camera& camera);
	void transformWithCameraRotation(Camera& camera, bool rotation);
	Vec3d findCurveCenter();

	Vec3d pointAtGiven_t(float& t, double& w, double& h);
	void replaceAllControlPoints(std::vector<Vec3d> newPoints,int deg);

	std::vector<double> BSplineBasisGraphic(double& t);
	std::vector<double> deCasteljauLerps(double t, std::vector<double>& iterationPoints, int p,int count);
	std::vector<double> deBoorLerps(double t, std::vector<double>& iterationPoints, int p, int count);
};

