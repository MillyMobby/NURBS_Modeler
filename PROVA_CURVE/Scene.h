#pragma once
#include "Camera.h"
#include "Shader.h"
#include "CurveGraphics.h"
#include "ImguiController.h"
#include "LineStripGraphics.h"
#include "Global.h"
class Scene {
private:

	std::vector<CurveGraphics*> curves;
	std::vector<LineStripGraphics*> basisFunctions;
	std::vector<LineStripGraphics*> lerp;
	
	int selectedCurve = 0, activatedCurves=0;
	const static int maxCurvesNumber = 15, maxControlPoints = 100;
	
	ImguiController _imgui;
	Shader _shader;
	Camera _camera;
	double startX = 0, startY = 0;
	Vec3f mouse = Vec3f(0);
	
	double W = 1920, H = 1080, tValue;
	bool isChanged = false;

	double offsetY = 0;
public:

	Scene() {
		prepareBasisGraphics();
		prepareCurveGraphics();
		prepareLerps();
	};
	~Scene() { curves.clear(); basisFunctions.clear(); lerp.clear(); };
	inline int get_tValue() const { return tValue; }
	inline void set_tValue(int t) { tValue = t; }

	inline ImguiController getImgui() const { return _imgui; }
	inline Shader getShader() { return _shader; }
	inline void setMouse(Vec3f pos) { mouse = pos; }

	//VIEW AND CAMERA EVENTS
	
	void initScene();
	Camera& getCamera();
	void loadCamera(int w, int h);
	void updateCamera(int w, int h);
	void checkForTransformations(bool wasMoved, bool rotation);

	void setIMGUI(GLFWwindow* window);
	void BG();
	void run(float deltaTime);
	void circle(float deltaTime);
	void clean();
	void handleMouseEvents(int& button, int& action, double& clipX, double& clipY, int& width, int& height);
	void updatePointsByMouse(double& dotX, double& dotY, float& deltaTime);
	void handleKeyEvents(int key);
	void windowShouldCloseIMGUI(GLFWwindow* _window);


	//CURVE GRAPHICS
	void prepareCurveGraphics();
	void selectNewCurve(int activeIndex);
	void renderAllCurveGraphics();
	void updateIMGUIaccordingToSelectedCurve();
	void initCurves();

	//BASIS GRAPHICS
	void BSplineBasisGraphic();
	void prepareBasisGraphics();
	void renderAllBasisFunctions();
	void initBasis();
	void clearBasis();

	//ALGORITHM GRAPHICS
	void prepareLerps();
	void renderAllLerps();
	void initLerps();
	void lerps(bool show);
	void clearLerps();

	void pass_tPointToIMGUI();
	void splitCurve(int split);
	void degreeRaiseBezier(int raise);
	
};

