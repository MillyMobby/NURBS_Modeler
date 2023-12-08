#include "Scene.h"
void Scene::initScene() {
	_shader.processShader();
	initCurves();
	initBasis();
	initLerps();
}

Camera& Scene::getCamera() { return _camera; }

void Scene::loadCamera(int w, int h) {
	H = h;
	W = w;
	_camera.setNear(0.1); 
	_camera.setFar(100.0); 

	_camera.setEye(Vec3d(0.0f, 0.0f, 2.0f));
	_camera.setLookAt(Vec3d(0.0f, 0.0f, 1.0f));
	_camera.setup(Vec3d(0.0f, 1.0f, 0.0f));
	_camera.computeAspectRatio(w,h);
	Mat4d id = Mat4d::identity();
	_camera.setTransform(id);
	
	_camera.update(w,h);
}

void Scene::updateCamera(int w, int h) {
	_camera.update(w, h);
	_imgui.setH(h);
	_imgui.setW(w);
}

void Scene::checkForTransformations(bool wasMoved, bool rotation) {
	curves[selectedCurve]->setMouse(mouse);
	if (wasMoved && rotation) {
		curves[selectedCurve]->transformWithCameraRotation(_camera, rotation);
		Mat4d id = Mat4d::identity();
		_camera.setTransform(id);
		isChanged = true;
	}
	else if (wasMoved) {
		curves[selectedCurve]->transformWithCamera(_camera);
		Mat4d id = Mat4d::identity();
		_camera.setTransform(id);
		isChanged = true;
	}
}

void Scene::setIMGUI(GLFWwindow* window) {
	_imgui.setIMGUI(window);
}

void Scene::BG() {  glClearColor(_imgui.backgroundColor.x * _imgui.backgroundColor.w, _imgui.backgroundColor.y * _imgui.backgroundColor.w, _imgui.backgroundColor.z * _imgui.backgroundColor.w, _imgui.backgroundColor.w); }

void Scene::run(float deltaTime) {
	glUseProgram(_shader.getShaderProgram());

	if (_imgui.addCurve == 1 && activatedCurves<maxCurvesNumber-1) {
		_imgui.selectedCurve = activatedCurves + 1; 
		selectNewCurve(_imgui.selectedCurve); 
		isChanged = false; 
		_imgui.updateHierarchy(activatedCurves);
	}
	if (_imgui.selectedCurve != selectedCurve) {
		
		if (_imgui.selectedCurve >activatedCurves) { _imgui.selectedCurve = selectedCurve; }
		else {
			selectNewCurve(_imgui.selectedCurve);
			_imgui.itemCurrent = curves[selectedCurve]->getCurveMath().getKnotsType();
		}		
	}

	lerps(_imgui.showLerps);
	splitCurve(_imgui.splitCurve);
	degreeRaiseBezier(_imgui.degreeRaiseBezier);
	BSplineBasisGraphic();
	
	pass_tPointToIMGUI();	
	
	renderAllCurveGraphics();
	renderAllBasisFunctions();
	
	_shader.updateCameraUniform(_camera);
}

void Scene::circle(float deltaTime) {
	renderAllCurveGraphics();
}

void Scene::clean() {
	for (int i = 0; i < curves.size(); i++) {
		curves[i]->cleanGL(_shader.getShaderProgram());
	}

	for (int i = 0; i < basisFunctions.size(); i++) {
		basisFunctions[i]->cleanGL(_shader.getShaderProgram());
	}
	_imgui.cleanupIMGUI();
}


void Scene::handleMouseEvents(int& button, int& action, double& clipX, double& clipY, int& width,int& height) {
	auto& io = ImGui::GetIO();
	if (io.WantCaptureMouse || io.WantCaptureKeyboard) { return; }
	else {
		_imgui.showLerps = false; 
		for (int i = 0; i < lerp.size(); i++) {
			lerp[i]->setChanged(true);
		}
		curves[selectedCurve]->findCurveCenter();
	}
	
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && _imgui.itemCurrent==0) {
		std::vector<GLfloat> vertices;
		curves[selectedCurve]->AddPoint(clipX, clipY);
		_imgui.maxDegree = curves[selectedCurve]->getPointsNumber() - 1;
		BSplineBasisGraphic();
	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
		if (action == GLFW_PRESS) {
			startX = clipX, startY = clipY;
			//curves[selectedCurve]->setSelectedVert(-2); 
		}
		else if (action == GLFW_RELEASE) {
			curves[selectedCurve]->setSelectedVert(-1);
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			
			double minDist = 1000.0;
			int minI;
			for (int i = 0; i < curves[selectedCurve]->getPointsNumber(); i++) {
				double thisDistX = (/*xpos*/clipX - curves[selectedCurve]->getControlPt_X(i)) * 0.5f * (double)width;
				double thisDistY = (/*ypos*/clipY - curves[selectedCurve]->getControlPt_Y(i)) * 0.5f * (double)height;
				double thisDist = sqrtf(thisDistX * thisDistX + thisDistY * thisDistY);
				if (thisDist < minDist) {
					minDist = thisDist;
					minI = i;
				}
				if (minDist <= 10.0) { minI; }
				else {}
			}
			curves[selectedCurve]->setSelectedVert(minI);
			basisFunctions[minI]->setSelectedVert(1);
			if (_imgui.itemCurrent == 0) {
				curves[selectedCurve]->ChangePoint(minI, clipX, clipY);
			}
			else {
				//double pt = curves[selectedCurve]->getControlPt_Y(minI);
				//double over = std::abs(-pt + clipY); //- curves[selectedCurve]->getControlPt_Y(v);
				//clipY = -curves[selectedCurve]->getControlPt_Y(minI) + clipY;
				//offsetY = /*offsetY - */over;
				
				//if (clipY >= 0 /*&& clipY!= curves[selectedCurve]->getControlPt_Y(minI)*/) {
					curves[selectedCurve]->ChangePoint(minI, /*xpos, ypos*/clipX, clipY/*clipY-0.1*/);
					//if (offsetY != clipY - curves[selectedCurve]->getControlPt_Y(minI)) {
						 //offsetY = clipY - curves[selectedCurve]->getControlPt_Y(minI);
					//curves[selectedCurve]->ChangePoint(minI, curves[selectedCurve]->getControlPt_X(minI), curves[selectedCurve]->getControlPt_Y(minI));
						//curves[selectedCurve]->ChangePoint(minI, /*xpos, ypos*/clipX, curves[selectedCurve]->getControlPt_Y(minI)/*offsetYcurves[selectedCurve]->getControlPt_Y(minI)clipY-0.1*/);
					//}
					
				//}

				//else if (clipY < 0 /*&& clipY != curves[selectedCurve]->getControlPt_Y(minI)*/) {
					//curves[selectedCurve]->ChangePoint(minI, /*xpos, ypos*/clipX, -clipY/*clipY-0.1*/);
					//if (offsetY != clipY + curves[selectedCurve]->getControlPt_Y(minI)) {
						 //offsetY = clipY + curves[selectedCurve]->getControlPt_Y(minI);
						 //curves[selectedCurve]->ChangePoint(minI, /*xpos, ypos*/clipX, offsetY/*curves[selectedCurve]->getControlPt_Y(minI)clipY-0.1*/);
					//}
					
				//}
				//else curves[selectedCurve]->ChangePoint(minI, /*xpos, ypos*/clipX, curves[selectedCurve]->getControlPt_Y(minI));
				//curves[selectedCurve]->ChangePoint(minI, /*xpos, ypos*/clipX, curves[selectedCurve]->getControlPt_Y(minI)/*clipY-0.1*/);
			}
		}
		else if (action == GLFW_RELEASE) {
			int s = curves[selectedCurve]->getSelectedVert();
			basisFunctions[s]->setSelectedVert(-1);
			curves[selectedCurve]->setSelectedVert(-1);			
		}
	}
}

void Scene::updatePointsByMouse(double& dotX, double& dotY, float& deltaTime) {
	int v = curves[selectedCurve]->getSelectedVert();
	if (curves[selectedCurve]->getSelectedVert() == -1) { return; }
	else if (curves[selectedCurve]->getSelectedVert() == -2) {
		Mat4d trans = Mat4d::translation((dotX - startX) * deltaTime, (dotY - startY) * deltaTime, 0);
		_camera.updateTransformMatrix(trans);
		checkForTransformations(true, false);
	}
	else {
		if (_imgui.itemCurrent == 0) { curves[selectedCurve]->ChangePoint(curves[selectedCurve]->getSelectedVert(), dotX, dotY); }
		else {
			//double pt = curves[selectedCurve]->getControlPt_Y(v);
			//double over = (-pt + dotY); //- curves[selectedCurve]->getControlPt_Y(v);
			//		offsetY = /*offsetY - */over;
			//if (dotY > 0) {
			//
			//		curves[selectedCurve]->ChangePoint(v, /*xpos, ypos*/dotX, offsetY/*clipY-0.1*/);
			//		std::cout << "offset= " << offsetY << std::endl;
			//}

			//else if (dotY < 0) {
				curves[selectedCurve]->ChangePoint(v, /*xpos, ypos*/dotX, /*-offsetY*/dotY);
			//	 offsetY = dotY - curves[selectedCurve]->getControlPt_Y(v);
			//	curves[selectedCurve]->ChangePoint(v, /*xpos, ypos*/dotX, offsetY/*clipY-0.1*/);
			//}
		}
	}
}

void Scene::handleKeyEvents(int key) {
	_imgui.showLerps = false;
	for (int i = 0; i < lerp.size(); i++) {
		lerp[i]->setChanged(true);
		lerp[i]->clearVertives();
		_imgui.makeBezier = false;
	}
	if (key == GLFW_KEY_F) {
		if (_imgui.itemCurrent == 1) {
				curves[selectedCurve]->getCurveMath().setKnotsType(0); 
				curves[selectedCurve]->getCurveMath().generateKnots();
				_imgui.item = 0;
				_imgui.setPredefinedCurve();
				//if (_imgui.grado > 2/*curves[selectedCurve]->getPointsNumber()>1*/) { _imgui.maxDegree = curves[selectedCurve]->getPointsNumber() - 1; }
		}
		else {
			if (curves[selectedCurve]->getSelectedVert() != 0)
			{			
					curves[selectedCurve]->RemoveFirstPoint();
					_imgui.weights[curves[selectedCurve]->getPointsNumber()/*-1*/] = 0.5f;
					if (_imgui.maxDegree == _imgui.grado && _imgui.grado > 2) {
						_imgui.grado--; _imgui.maxDegree--;
						curves[selectedCurve]->modifyCurve();
					}
					else _imgui.maxDegree--;

				if (curves[selectedCurve]->getSelectedVert() < 0) {
					//graphics->setSelectedVert(graphics->getSelectedVert());
				}
				else curves[selectedCurve]->setSelectedVert(-1);
			}			
		}
	}
	else if (key == GLFW_KEY_L) {
		if (_imgui.itemCurrent == 1) {
				curves[selectedCurve]->getCurveMath().setKnotsType(0);
				curves[selectedCurve]->getCurveMath().generateKnots();
				_imgui.item = 0;
				_imgui.setPredefinedCurve();
		}
		else {
			if (curves[selectedCurve]->getSelectedVert() != curves[selectedCurve]->getPointsNumber() - 1)
			{
				curves[selectedCurve]->RemoveLastPoint(); 

				_imgui.weights[curves[selectedCurve]->getPointsNumber()/*-1*/] = 0.5f;
				if (_imgui.maxDegree == _imgui.grado && _imgui.grado > 2) {
					_imgui.grado--; _imgui.maxDegree--;
					curves[selectedCurve]->modifyCurve();
				}
				else _imgui.maxDegree--;
			}
			else curves[selectedCurve]->setSelectedVert(-1);
		}		
	}
	clearBasis();		
}

void Scene::windowShouldCloseIMGUI(GLFWwindow* _window) {
	_imgui.windowIMGUI(_window);
	_imgui.renderIMGUI();
}

void Scene::prepareCurveGraphics() {
	for (int i = 0; i < maxCurvesNumber; i++) {
		CurveGraphics* obj = new CurveGraphics();
		curves.push_back(obj);
	}
	curves[0]->setSelected(true);
	curves[0]->setVisible(true);
}

void Scene::selectNewCurve(int activeIndex) {
	if (activeIndex != selectedCurve) {
		if (activeIndex > activatedCurves + 1) { activeIndex = activatedCurves + 1; }
		if (activeIndex <= maxCurvesNumber) {
			clearBasis();

			curves[selectedCurve]->nullVertexSelection();
			curves[selectedCurve]->setSelected(false);
			curves[activeIndex]->setSelected(true);
			curves[activeIndex]->setVisible(true);
			if (activeIndex != selectedCurve) { isChanged = true; }
			selectedCurve = activeIndex;

			if (activeIndex > activatedCurves) {
				activatedCurves++;
				curves[selectedCurve]->setColor();
			}
		}
	}
	_imgui.showLerps = false;
	updateIMGUIaccordingToSelectedCurve();
	BSplineBasisGraphic();
}

void Scene::renderAllCurveGraphics() {
	for (int i = 0; i < curves.size(); i++) {
		curves[i]->rendering(_imgui.grado, _imgui.makeBezier, _imgui.makeNURBS, _imgui.weights, _imgui.itemCurrent);
	}
}

void Scene::updateIMGUIaccordingToSelectedCurve() {
	_imgui.makeBezier = curves[selectedCurve]->getCurveMath().isBezier();
	_imgui.makeNURBS = curves[selectedCurve]->getCurveMath().isNURBS();
	_imgui.grado = curves[selectedCurve]->getCurveMath().getDegree();
	_imgui.maxDegree = curves[selectedCurve]->getPointsNumber() - 1;
	_imgui.weights = curves[selectedCurve]->getWeights();
	_imgui.item = curves[selectedCurve]->getCurveMath().getKnotsType();
	_imgui.itemCurrent = curves[selectedCurve]->getCurveMath().getKnotsType();

	pass_tPointToIMGUI();
}

void Scene::initCurves() {
	for (int i = 0; i < curves.size(); i++) {
		curves[i]->setupGL();
		curves[i]->initGL();
	}
}

void Scene::BSplineBasisGraphic() {
	if (curves[selectedCurve]->getPointsNumber() > 1) {
		clearBasis();
		double start = 0;
		std::vector<double> v;
		std::vector<double> basisMatrix;
		std::vector<double> vertices;
		int n = curves[selectedCurve]->getCurveMath().getKnotsVector().size() - curves[selectedCurve]->getCurveMath().getDegree() - 1;

		if (curves[selectedCurve]->getCurveMath().degenere(curves[selectedCurve]->getPointsNumber()) == true) {
			for (double t = 0; t <= 1; t = t + 0.001) {
				v.clear();
				v = curves[selectedCurve]->BSplineBasisGraphic(t);
			}
			for (int j = 0; j < n; j++) { basisFunctions[j]->setVertices(v); }
		}

		else {
			for (double t = 0; t <= 1; t = t + 0.001) {
				v.clear();
				v = curves[selectedCurve]->BSplineBasisGraphic(t);
				basisMatrix.insert(std::end(basisMatrix), std::begin(v), std::end(v));

			}
			int index = 0;
			for (int j = 0; j < n; j++) {
				vertices.clear();
				for (double t = 0; t <= 1; t = t + 0.001) {
					if (_imgui.itemCurrent == 0) {
						vertices.push_back((t - 2) * 0.5);
						vertices.push_back((basisMatrix[j + n * t * 1000] - 1.8) * 0.5);
						vertices.push_back(0);
					}
					else {
						vertices.push_back((t - 2) * 0.5);
						//vertices.push_back((basisMatrix[j + n * t * 1000] - 2.15) * 0.25);
						vertices.push_back((basisMatrix[j + n * t * 1000] - 1.8) * 0.5);
						vertices.push_back(0);
					}
				}
				basisFunctions[j]->setVertices(vertices);
				if (index > 5) index = 0;
				if (j % 2 == 0) { basisFunctions[j]->setLineColor(index / 7.0f, index / 5.0f, 0.4f); }
				else { basisFunctions[j]->setLineColor(0.7f, 0.3f, index / 6.0f); }
				index++;
			}
		}
	}
}

void Scene::prepareBasisGraphics() {
	for (int i = 0; i < 100; i++) {
		LineStripGraphics* ls = new LineStripGraphics();
		basisFunctions.push_back(ls);
	}
}

void Scene::renderAllBasisFunctions() {
	int index = 0;
	if (curves[selectedCurve]->getSelectedVert() <0 ) {
		for (int i = 0; i < basisFunctions.size(); i++) {
			basisFunctions[i]->renderScene();
		}
	}
	else if (curves[selectedCurve]->getSelectedVert() >= 0) {
		for (int i = 0; i < basisFunctions.size(); i++) {

			if (index > 5) index = 0;
			if (basisFunctions[i]->getSelectedVert()==1) {
				basisFunctions[i]->setLineColor(1.0f, 0.0f, 0.0f);
			}
			else { basisFunctions[i]->setLineColor(0.5f, 0.5f, 0.5f); }
			basisFunctions[i]->renderScene();
		}
	}
}

void Scene::initBasis() {
	int index = 0;
	for (int i = 0; i < basisFunctions.size(); i++) {
		basisFunctions[i]->setupGL();
		basisFunctions[i]->initGL();
		
		if (index>5) index=0;
		if (i % 2 == 0) { basisFunctions[i]->setLineColor(index /7.0f, index /5.0f,0.4f); }
		else { basisFunctions[i]->setLineColor(0.7f, 0.3f, index /6.0f); }
		
		index++;
	}
}

void Scene::clearBasis() {
	std::vector<double> values = std::vector<double>(100, 0);
	for (int i = 0; i < basisFunctions.size(); i++) {
		basisFunctions[i]->clearVertives();
		basisFunctions[i]->setVertices(values);
	}
}

void Scene::prepareLerps() {
	for (int i = 0; i < 100; i++) {
		LineStripGraphics* l = new LineStripGraphics();
		lerp.push_back(l);
	}
}

void Scene::renderAllLerps() {
	for (int i = 0; i < _imgui.grado/*lerp.size()*/; i++) {
		lerp[i]->renderScene();
	}
}

void Scene::initLerps() {
	for (int i = 0; i < lerp.size(); i++) {
		lerp[i]->setupGL();
		lerp[i]->initGL();
		lerp[i]->setColor();
	}
}

void Scene::lerps(bool show) {
	for (int i = 0; i < lerp.size(); i++) { lerp[i]->clearVertives(); }
	if (_imgui.showLerps && curves[selectedCurve]->getCurveMath().isBezier()) {
		std::vector<double> lerpPoints;
		int c = 0;
		for (int p = _imgui.grado; p > 0; p--) {
			if (lerp[c]->getChanged() == true || lerp[c]->getPointsNumber() == 0 || _imgui.getIsChanged() || isChanged || _imgui.makeNURBS) {
				std::vector<double>aux;
				aux = curves[selectedCurve]->deCasteljauLerps(_imgui.t, lerpPoints, p, c);
				lerp[c]->setVertices(aux);
				lerp[c]->setDrawPoints(true);
				lerpPoints.clear();

				for (int i = 0; i < aux.size(); i++) {
					lerpPoints.push_back(aux[i]);
				}
			}
			c++;
		}
		renderAllLerps();
	}
	else if (_imgui.showLerps && curves[selectedCurve]->getCurveMath().isBezier() == false) {
		std::vector<double> lerpPoints;
		int c = 0;
		for (int p = _imgui.grado; p > 0; p--) {
			//if (_imgui.getIsChanged()) {

			std::vector<double>aux;
			aux = curves[selectedCurve]->deBoorLerps(_imgui.t, lerpPoints, p, c);
			lerp[c]->setVertices(aux);
			lerp[c]->setDrawPoints(true);
			lerpPoints.clear();
			for (int i = 0; i < aux.size(); i++) {
				lerpPoints.push_back(aux[i]);
			}
			//}
			c++;
		}
		renderAllLerps();
	}
}

void Scene::clearLerps() {
	std::vector<double> values = std::vector<double>(10, 0);
	for (int i = 0; i < basisFunctions.size(); i++) {
		lerp[i]->clearVertives();
		lerp[i]->setVertices(values);
	}
}

void Scene::pass_tPointToIMGUI() {
	double width = (double)_imgui.w ; double height = (double)_imgui.h;

		Vec3d currentPt = curves[selectedCurve]->pointAtGiven_t(_imgui.t,width, height);
		_imgui.tPoint = ImVec2(currentPt.x, currentPt.y);
		
		tValue = _imgui.t;	
}

void Scene::splitCurve(int split) {
	if (split==1 && activatedCurves<maxCurvesNumber) {
		std::vector<Vec3d> left, right;
		std::vector<float> weights, weights2;
		std::string name;
		bool nurbs = _imgui.makeNURBS;
		int deg = _imgui.grado;
		if (curves[selectedCurve]->getCurveMath().isBezier()) {
			/*Vec3d pt = */curves[selectedCurve]->getCurveMath().deCasteljauSplit(_imgui.t, left, right);
			
			curves[selectedCurve]->replaceAllControlPoints(left, deg);
			curves[selectedCurve]->getCurveMath().setNURBS(nurbs);
			for (int i = 0; i < left.size(); i++) {
				weights.push_back(left[i].z);				
			}
			curves[selectedCurve]->addWeights(weights);
			
			int previous = selectedCurve;
			_imgui.selectedCurve = activatedCurves + 1;
			selectNewCurve(_imgui.selectedCurve);			
			_imgui.updateHierarchy(activatedCurves);
			
			curves[selectedCurve]->replaceAllControlPoints(right, deg);
			/*name = std::to_string(selectedCurve + 1) + "split2";
			_imgui.renameCurve(selectedCurve, name);*/
			updateIMGUIaccordingToSelectedCurve();
			curves[selectedCurve]->getCurveMath().setNURBS(nurbs);
			_imgui.makeNURBS = nurbs;
			
			for (int i = 0; i < right.size(); i++) {
				weights2.push_back(right[i].z);
			}
			curves[selectedCurve]->addWeights(weights2);
		}
	}
}

void Scene::degreeRaiseBezier(int raise) {
	if (raise == 1) {
		std::vector<Vec3d> newPoints;
		int deg = _imgui.grado;
		if (curves[selectedCurve]->getCurveMath().isBezier()) {
			curves[selectedCurve]->getCurveMath().degreeRaise(newPoints);
			curves[selectedCurve]->replaceAllControlPoints(newPoints, deg);
			updateIMGUIaccordingToSelectedCurve();			
		}
	}
}



