#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"
#include "PredefinedCurves.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Vec3d.h"
class ImguiController {

private:
	bool show_window = true;
	bool isChanged = false;


	bool show_demo_window = true;
	bool ConfigWindowsMoveFromTitleBarOnly = true;
	char curvesHierarchy[15][8] = { "Curve1", " ", " ", " ", " ", " ", " ", " ", " "," ", " ", " ", " ", " ", " " }; // MAX 15 CURVE

public:

	ImguiController(){  };
	inline bool getIsChanged() const { return isChanged; }
	inline void setIsChanged(bool b) { isChanged = b; }

	int w, h;
	inline void setW(int b) { w = b; } //width
	inline void setH(int b) { h = b; } //height

	inline char* getHierarchy(int i) { return curvesHierarchy[i]; }
	ImVec4 backgroundColor = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);//ImVec4(0.0f, 0.0f, 0.0f, 1.00f); //BG
	int grado = 2;
	float t = 0.123f, tCurrent = 0.123f;
	ImVec2 tPoint = ImVec2(0, 0);

	bool makeBezier = false, makeNURBS = false, showLerps = false;

	int maxDegree = 0,  minDegree = 0;

	int itemCurrent = 0, item = 0;
	int addCurve = 0, splitCurve = 0, degreeRaiseBezier = 0;

	std::vector<float>weights = std::vector<float>(100, 0.5);	
	int selectedCurve;
	//bool* open_ptr = &show_demo_window;
	
	~ImguiController() {};
	void setIMGUI(GLFWwindow* _window);
	void displayInputGuide();
	void DegreeRangeWidget();
	void degreeSlider();
	void NurbsWeightEditor();
	void windowIMGUI(GLFWwindow* _window) ;
	void renderIMGUI();
	void cleanupIMGUI();

	bool imguiWantsToCaptureMouse();
	void setPredefinedCurve();
	void updateWeightsSliders(std::vector<float> w);
	void updateHierarchy(int activatedCurves);

	void drawDecas(std::vector<Vec3d> pts);
};

