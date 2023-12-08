#include "CurveGraphics.h"

CurveGraphics::~CurveGraphics() { delete[] controlPolygon; }

const int CurveGraphics::getSelectedVert() {  return _selectedVert; }

void CurveGraphics::setSelectedVert(int s) {
    if (_selectedVert!=-1 && _selectedVert != -2) controlPolygon[_selectedVert * _stride + 3] = 1;
     _selectedVert = s;
}

void CurveGraphics::nullVertexSelection() {
    if (_selectedVert != -1) controlPolygon[_selectedVert * _stride + 3] = 1;
    LoadPointsIntoVBO();
    _selectedVert = -1;
}

const bool CurveGraphics::isCurveSelected() { return isSelected; }
void CurveGraphics::setSelected(bool s) {  isSelected = s;  }

const bool CurveGraphics::isCurveVisible() { return isVisible; }
void CurveGraphics::setVisible(bool v) { isVisible = v; }


const int CurveGraphics::getPointsNumber() {  return _pointsNumber; }


const double& CurveGraphics::getControlPt_X(int& i) { 
    return controlPolygon[i * _stride];
}

const double& CurveGraphics::getControlPt_Y(int& i) {   
    return controlPolygon[i * _stride + 1];
}

const double& CurveGraphics::getControlPt_W(int& i) {
    return controlPolygon[i * _stride + 2];
}

void CurveGraphics::setLineColor(/*Vec3f col*/) {
    _lineColor = randomColor();
}

void CurveGraphics::setCurveColor(/*Vec3f col*/) {
    _curveColor = randomColor();
}

void CurveGraphics::setColor() {
    setLineColor();
    setCurveColor();
}

Vec3f CurveGraphics::randomColor() {
    float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    return Vec3f(x, y, z);
}

void CurveGraphics::initGL() {
    //pcurva.initGL();
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    GLsizeiptr verticesSize = MaxNumPoints * sizeof(controlPolygon[0]);


    glBufferData(GL_ARRAY_BUFFER, verticesSize, (void*)0, GL_STATIC_DRAW);
    glVertexAttribPointer(0, _nElements_position, GL_DOUBLE, GL_FALSE, _stride * sizeof(GLdouble), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    initCurveGL();
    
}

void CurveGraphics::initCurveGL() {  
    glGenVertexArrays(1, &_curveVAO);
    glGenBuffers(1, &_curveVBO);
    glBindVertexArray(_curveVAO);
    glBindBuffer(GL_ARRAY_BUFFER, _curveVBO);
 GLsizeiptr verticesSize = (steps*600) * sizeof(controlPolygon[0]);
    
    glBufferData(GL_ARRAY_BUFFER, verticesSize, (void*)0, GL_STATIC_DRAW); 
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, _curveStride * sizeof(GLdouble), (void*)0);
    glEnableVertexAttribArray(0);  
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CurveGraphics::setupGL() {

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// depth buffering
    glDepthFunc(GL_LEQUAL);		// multipass shaders (?????????????)

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);		// Antialias 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(10);
    glLineWidth(5); 
}

void CurveGraphics::cleanGL(GLuint &shaderProgram) {
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteVertexArrays(1, &_curveVAO);
    glDeleteBuffers(1, &_curveVBO);
    glDeleteProgram(shaderProgram);
}

void CurveGraphics::LoadPointsIntoVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, _VBO); 
    glBufferSubData(GL_ARRAY_BUFFER, 0, _pointsNumber * 4 * sizeof(double), controlPolygon); //non e' un resize
   // glBufferSubData(GL_ARRAY_BUFFER, 0, _vertices.size()/3 * sizeof(_vertices[0]), _vertices.data());    
  
}

void CurveGraphics::LoadPointsIntoCurveVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, _curveVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, _curvePointsNumber * 3 * sizeof(double)+1, curvePoints);
    
}


void CurveGraphics::AddPoint(double x, double y)
{
    if (isSelected && isVisible) {
        int preview;
        bool repeated = false;
        _pointsNumber > 0 ? preview = _pointsNumber - 1 : preview = 0;

        if (preview != 0) {
            if (controlPolygon[preview * _stride] == x && controlPolygon[preview * _stride + 1] == y) {
                std::cout << "il punto è ripetuto \n";
                editMultiplicity(_pointsNumber - 1);
                repeated = true;
            }
        }

        if (_pointsNumber < MaxNumPoints && repeated == false) {

            controlPolygon[_pointsNumber * _stride] = x;
            controlPolygon[_pointsNumber * _stride + 1] = y;
            controlPolygon[_pointsNumber * _stride + 2] = 1;
            controlPolygon[_pointsNumber * _stride + 3] = 1;
            _pointsNumber++;
            editMultiplicity(_pointsNumber);
            LoadPointsIntoVBO();
        }    
        curveMath.setControlPoints(controlPointsVector());
        curveMath.generateKnots();
        predefinedCurves.setLoaded(false);
        isChanged = true;
    }
   
}


void CurveGraphics::AddCurvePoint(double x, double y) {
    if (isSelected && isVisible) {
        curvePoints[_curvePointsNumber * _curveStride] = x;
        curvePoints[_curvePointsNumber * _curveStride + 1] = y;
        curvePoints[_curvePointsNumber * _curveStride + 2] = 1;

        _curvePointsNumber++;
        LoadPointsIntoCurveVBO();
    }
}

void CurveGraphics::ChangePoint(int i, double x, double y, double z)
{
    if (isSelected && isVisible) {
        if (i >= 0 && i < _pointsNumber) {
            controlPolygon[i * _stride] = x;
            controlPolygon[i * _stride + 1] = y;
            controlPolygon[i * _stride + 2] = z;
            if (_selectedVert == i) controlPolygon[i * _stride + 3] = 0;
            else if (_selectedVert == -1) controlPolygon[i * _stride + 3] = 1;   
        }
        LoadPointsIntoVBO();

        curveMath.setControlPoints(controlPointsVector());
        isChanged = true;
    }
}
void CurveGraphics::ChangePoint(int i, double x, double y)
{
    if (isSelected && isVisible) {
        if (i >= 0 && i < _pointsNumber) {
            controlPolygon[i * _stride] = x;
            controlPolygon[i * _stride + 1] = y;
            if (_selectedVert == i) controlPolygon[i * _stride + 3] = 0;
            else if (_selectedVert == -1) controlPolygon[i * _stride + 3] = 1;
        }
        LoadPointsIntoVBO();

        curveMath.setControlPoints(controlPointsVector());
        isChanged = true;
    }
}

void CurveGraphics::ChangeDegree(int p) {
    if (_pointsNumber >= p + 1 && p != curveMath.getDegree()) {
        curveMath.setDegree(p);
        isChanged = true;
    }
}

void CurveGraphics::modifyCurve() {   
    if (isVisible && isChanged && _pointsNumber > 0) {
        resizeMultiplicities();
        double uincMin = 0.001;
        std::vector<Vec3d> controlPoints = controlPointsVector();
        curveMath.setControlPoints(controlPoints);
        curveMath.generateKnots();
        int count = 0;
        Vec3d point = Vec3d(0);

        if (curveMath.degenere(_pointsNumber) == false && _pointsNumber>0 ) {

            for (double u = curveMath.getDomainLeft(); u < curveMath.getDomainRight()+uincMin; u = u+uincMin) {
                if (curveMath.getKnotsSize() == (curveMath.getDegree()+1)*2)
                {
                    curveMath.setBezier(true);
                    point = curveMath.deCasteljau(u);
                }
                else
                {
                    curveMath.setBezier(false);
                    point = curveMath.deBoor(double(u));
                    
                }
                if (_curvePointsNumber > 0 && count < _curvePointsNumber) { ChangeCurvePoint(count, point.x, point.y); }
                else if (_curvePointsNumber >= 0 && count >= _curvePointsNumber) { AddCurvePoint(point.x, point.y); }
                count++;
            }
        }
    } isChanged = false;   
}

void CurveGraphics::ChangeCurvePoint(int i, double x, double y)
{
    if (isSelected && isVisible) {
        if (i >= 0 && i < _curvePointsNumber) {
            curvePoints[i * _curveStride] = x;
            curvePoints[i * _curveStride + 1] = y;
        }
        LoadPointsIntoCurveVBO();
    }
}

void CurveGraphics::rendering(int& deg, bool& makeBezier, bool& makeNURBS, std::vector<float>& w, int curveType) {
    if (isSelected) {
        curveMath.setKnotsType(curveType);
        //makeNURBS = curveMath.isNURBS();
        /*curveMath.setNURBS(makeNURBS);
        curveMath.setBezier(makeBezier);*/
        for (int i = 0; i < _pointsNumber; i++) { weights[i] = w[i]; }     
        
        if (curveType == 1 && makeNURBS == true) {
            if (predefinedCurves.getLoaded() == false) setPredefinedCurve(curveType, w);
            curveMath.setNURBS(true);
            curveMath.setDegree(2);
            makeBezier = false;
            deg = curveMath.getDegree();
        }
        else if (curveType == 0 /*&& curveMath.getKnotsType() == 1*/) { predefinedCurves.setLoaded(false); curveMath.setKnotsType(0); modifyCurve(); }
            if (makeBezier == true && _pointsNumber > 1)
            {
                if (deg != _pointsNumber - 1) {
                    ChangeDegree(_pointsNumber - 1); 
                    deg = curveMath.getDegree();
                }
            }
            else if (_pointsNumber >= deg + 1 && deg != curveMath.getDegree()) {
                curveMath.setDegree(deg);
                isChanged = true;
            }

            else { deg = curveMath.getDegree();  }

        //if (deg == curveMath.getDegree())  { deg = curveMath.getDegree(); /*isChanged = false; */}
            curveMath.setNURBS(makeNURBS);
        resizeMultiplicities();

        addWeights(w);
       
       
        if (isChanged == true || makeNURBS == true) { 
            modifyCurve();  isChanged = false;
        }
    }
    
    if (curveMath.degenere(_pointsNumber) == false) {
        renderScene();
        
        if (deg == curveMath.getDegree() && isSelected) renderCurve();
        else if (isSelected==false) renderCurve();
    }
    else renderScene();
    isChanged = false;
}

void CurveGraphics::renderScene() {
    if (isVisible) {
        glBindVertexArray(_VAO);
        //linee
        if (_pointsNumber > 0)
        {
            glBegin(GL_LINE_STRIP);
            glVertexAttrib3f(_colorLocation, _lineColor.x, _lineColor.y, _lineColor.z);	
            glDrawArrays(GL_LINE_STRIP, 0, _pointsNumber);
            glEnd();
        }
        // punti
        glVertexAttrib3f(_colorLocation, _pointsColor.x, _pointsColor.y, _pointsColor.z);
        glDrawArrays(GL_POINTS, 0, _pointsNumber);

        glBindVertexArray(0);
    }
}

void CurveGraphics::renderCurve()
{
    if (isVisible) {
        if (_curvePointsNumber > 0) {
            glBindVertexArray(_curveVAO);
            glBegin(GL_LINE_STRIP);
            glLineWidth(2);
            glVertexAttrib3f(_colorLocation, _curveColor.x, _curveColor.y, _curveColor.z);
            glDrawArrays(GL_LINE_STRIP, 0, _curvePointsNumber);
            glEnd();
        }      
    }
    //isChanged = false;
}

std::vector<Vec3d> CurveGraphics::controlPointsVector() {
    Vec3d pt = Vec3d(0);
    std::vector<Vec3d> controlPt;

    for (int i = 0; i < _pointsNumber * 4; i = i + 4) {
        for (int j = 0; j < getPointMultiplicity(i / 4); j++) {
            controlPt.push_back(pt);

            controlPt.back().x = controlPolygon[i];
            controlPt.back().y = controlPolygon[i + 1];
            controlPt.back().z = controlPolygon[i + 2];
        }
    }
    return controlPt;
}

std::vector<Vec3d> CurveGraphics::curvePointsVector() {

    Vec3d pt = Vec3d(0);
    std::vector<Vec3d> curvept;
    for (int i = 0; i < _curvePointsNumber * 3; i = i + 3) {

        curvept.push_back(pt);

        curvept[i / 3].x = curvePoints[i];
        curvept[i / 3].y = curvePoints[i + 1];
        curvept[i / 3].z = curvePoints[i + 2];
        std::cout << curvept[i / 3];
    }
    return curvept;
}

std::vector<float> CurveGraphics::getWeights() {
    return weights;
}

CurveMath CurveGraphics::getCurveMath() {
    return curveMath;
}

void CurveGraphics::addWeights(std::vector<float> w) {
    if (isSelected && isVisible) {
        for (int i = 0; i < _pointsNumber; i++) {
            if (w[i] != controlPolygon[i * _stride + 2]) {
                ChangePoint(i,
                    controlPolygon[i * _stride],
                    controlPolygon[i * _stride + 1],
                    w[i]);
            }
            weights[i] = w[i];
        }
    }   
}

std::vector<int> CurveGraphics::getMultiplicityVector() { return multiplicities; }

void CurveGraphics::editMultiplicity(int pointIndex) {
    if (multiplicities.size() >= pointIndex) {
        if (multiplicities.back() < curveMath.getDegree()) multiplicities.back()++;
        else std::cout << "degenere\n";
    }
    else multiplicities.push_back(1);
}

void CurveGraphics::resizeMultiplicities() {
    if (isSelected && isVisible) {
        if (multiplicities.size() > 0) {
            int degree = curveMath.getDegree();
            for (int i = 0; i < multiplicities.size(); i++) {
                if (degree >= 1 && multiplicities[i] > degree) multiplicities[i] = degree;
            }
        }
    }
}

void CurveGraphics::setMultiplicity(int i) { multiplicities.push_back(i); }

void CurveGraphics::deleteLastMultiplicity() { multiplicities.pop_back(); }

void CurveGraphics::deleteFirstMultiplicity(int i) {
    multiplicities[i] = multiplicities[(i + 1)];
    if (i + 1 == multiplicities.size()) { multiplicities.pop_back(); }
}

void CurveGraphics::setPredefinedCurve(int knotsType, std::vector<float>& w) {
    
    
    const const std::vector<double> v = PredefinedCurves::getCircleControlPolygon();
    
    while (_pointsNumber > 0) {

        RemoveLastPoint();
    }
    for (int i = 0; i < 9; i++) {
        AddPoint(v[i * 2], v[i * 2 + 1]);
    }
    curveMath.setKnotsType(knotsType);
    curveMath.setControlPoints(controlPointsVector());
    curveMath.generateKnots();
    predefinedCurves.setLoaded(true);
    isChanged = true;
}


void CurveGraphics::RemoveFirstPoint()
{
    if (isSelected && isVisible) {
        curveMath.setKnotsType(0); 
        predefinedCurves.setLoaded(false);
        if (_pointsNumber == 0) { curveMath.setBezier(false); curveMath.setDegree(3); isChanged = false; return; }
    
        for (int i = 0; i < _pointsNumber - 1; i++) {
            controlPolygon[i * _stride] = controlPolygon[(i + 1) * _stride ];
            controlPolygon[i * _stride + 1] = controlPolygon[(i + 1) * _stride + 1];
            controlPolygon[i * _stride + 2] = controlPolygon[(i + 1) * _stride + 2];
            controlPolygon[i * _stride + 3] = controlPolygon[(i + 1) * _stride + 3];
            deleteFirstMultiplicity(i);
        }
        _pointsNumber--;
        if (_pointsNumber > 0) {
            LoadPointsIntoVBO();
            curveMath.setControlPoints(controlPointsVector());
            curveMath.generateKnots();
            isChanged = true;
        }
    }    
}

void CurveGraphics::RemoveLastPoint() {
    if (isSelected && isVisible) {
         curveMath.setKnotsType(0); 
         predefinedCurves.setLoaded(false);
         if (_pointsNumber == 0) { curveMath.setBezier(false);  curveMath.setDegree(3); isChanged = false; return; }
        if (_pointsNumber > 0) {
            _pointsNumber--;
            deleteLastMultiplicity();
            curveMath.setControlPoints(controlPointsVector());
            curveMath.generateKnots();
            isChanged = true;
        }
    }
}

void CurveGraphics::RemoveLastCurvePoint() { 
    
    _curvePointsNumber = (_curvePointsNumber > 0) ? _curvePointsNumber - 1 : 0; 
}



void CurveGraphics::transformWithCamera(Camera& camera) {   
        Vec4d pt = Vec4d(0);
        Mat4d t = camera.getTransform();
        Mat4d z = camera.getZoomMatrix();
        Mat4d translation, translationInverse;
        if (t != Mat4d::identity()) {
            translation = Mat4d::translation(-mouse.x, -mouse.y, 1);
            translationInverse = Mat4d::translation(mouse.x, mouse.y, 1);
        }
        else {
            translation = Mat4d::identity();
            translationInverse = Mat4d::identity();
        }
        z = z.inverse();
        for (int i = 0; i < _pointsNumber * 4 ; i = i + 4) {
            pt.x = controlPolygon[i];
            pt.y = controlPolygon[i + 1];
            pt.z = 1 ;
            pt.w = 1;        

            Vec4d newPt = pt;
            newPt = z * translationInverse * t * translation * pt;
        
            ChangePoint(i / 4, newPt.x, newPt.y, controlPolygon[i + 2]);
        }  

}

void CurveGraphics::transformWithCameraRotation(Camera& camera, bool rotation) {
    Vec4d pt = Vec4d(0);
    Mat4d t = camera.getTransform();
    Mat4d z = camera.getZoomMatrix();
    Mat4d translation, translationInverse;
    Vec3d center = findCurveCenter();

    z = z.inverse();
    for (int i = 0; i < _pointsNumber * 4; i = i + 4) {
        translation = Mat4d::translation(-center.x,-center.y,1);
        translationInverse = Mat4d::translation(center.x, center.y, 1); 
        pt.x = controlPolygon[i];
        pt.y = controlPolygon[i + 1];
        pt.z = 1;
        pt.w = 1;

        Vec4d newPt = pt;
        newPt = z* translationInverse * t  *translation* pt;

        ChangePoint(i / 4, newPt.x, newPt.y, controlPolygon[i + 2]);
    }
}

Vec3d CurveGraphics::findCurveCenter() {   
    double X=0, Y=0;
    for (int i = 0; i < _pointsNumber; i++) {
        X+= getControlPt_X(i);
        Y+= getControlPt_Y(i);
    }
    X /= _pointsNumber;
    Y /= _pointsNumber;

    return Vec3d(X, Y, 1);
}

Vec3d CurveGraphics::pointAtGiven_t(float& t, double& w, double& h) {
    Vec3d result = Vec3d(0, 0, 0);
    if (curveMath.degenere(_pointsNumber)==false && _pointsNumber>1) {
        tValue = t;
        
        result = curveMath.deBoor(double(t));
        result.x = (result.x + 1.0000f) * 0.5000 * double(w);
        result.y = (1.0000f - result.y) * 0.5000 * double(h);
        
    }return result;
}

void CurveGraphics::replaceAllControlPoints(std::vector<Vec3d> newPoints,int deg) {
    while (_pointsNumber > 0) {  RemoveLastPoint();  }

    curveMath.setDegree(newPoints.size() - 1);
    for (int i = 0 ; i <newPoints.size(); i++) {
        AddPoint(newPoints[i].x, newPoints[i].y);
    }
    for (int i = 0; i < newPoints.size(); i++) {
        weights[i]=newPoints[i].z;
    }
    addWeights(weights);
    modifyCurve();
}

std::vector<double> CurveGraphics::BSplineBasisGraphic(double& t) {
   std::vector<double> values = std::vector<double>(4, 0);
   
   if (curveMath.degenere(_pointsNumber) == false && curveMath.getKnotsSize()!=0)  { return curveMath.BSplineBase(t);   }
   return values;
}

std::vector<double> CurveGraphics::deCasteljauLerps(double t, std::vector<double>& iterationPoints, int p,int count) {
    std::vector<Vec3d> controlPt;
    std::vector<double> points;
    Vec3d result = Vec3d(0);
    if (iterationPoints.size() != 0) {
        for (int k = 0; k < iterationPoints.size(); k = k + 3) {
            controlPt.push_back(result);

            controlPt.back().x = iterationPoints[k]       * iterationPoints[k + 2];
            controlPt.back().y = iterationPoints[k + 1]      * iterationPoints[k + 2];
            controlPt.back().z = iterationPoints[k + 2]; 

        }
    }
    else if (iterationPoints.size() == 0 && _pointsNumber == curveMath.getDegree() + 1) {
        for (int k = 0; k < _pointsNumber * 4; k = k + 4) {
            controlPt.push_back(result);

            controlPt.back().x = controlPolygon[k]        * controlPolygon[k + 2] ;
            controlPt.back().y = controlPolygon[k + 1]      * controlPolygon[k + 2] ;
            controlPt.back().z = controlPolygon[k + 2] ;
        }        
    }
    for (int j = 0; j < p; j++) {

        result = Vec3d::lerp(controlPt[j], controlPt[j + 1], t);
        points.push_back(result.x    / result.z);
        points.push_back(result.y     / result.z);
        points.push_back(result.z);
    }
    return points;
}

std::vector<double>  CurveGraphics::deBoorLerps(double t,std::vector<double>& iterationPoints, int p, int count) {
    Vec3d result = Vec3d(0);
    std::vector<Vec3d> controlPt;
    std::vector<Vec3d> prova = controlPointsVector();
    std::vector<double> points;
    if (curveMath.getControlPointsSize() == curveMath.getKnotsVector().size() - curveMath.getDegree() -1 ) { 
        
        int m = curveMath.getKnotsInterval(t);
        int n = curveMath.getControlPointsSize();
        int degree = curveMath.getDegree();
        if (iterationPoints.size() != 0) {
            
            for (int k = 0; k < iterationPoints.size(); k = k + 3) {
                controlPt.push_back(result);

                controlPt.back().x = iterationPoints[k] * iterationPoints[k + 2];
                controlPt.back().y = iterationPoints[k + 1] * iterationPoints[k + 2];
                controlPt.back().z = iterationPoints[k + 2];

            }
            

        }
        else if (iterationPoints.size() == 0 ) {
            if (m >= p && m < n) {
                for (int k = (m - p); k <= m; k++) {
                    controlPt.push_back(prova[k]);
                    controlPt.back().x *= controlPt.back().z;
                    controlPt.back().y *= controlPt.back().z;
                    
                }

            }
        }for (int j = 0; j < p; j++) {
            double omega = ((t - curveMath.getKnot(j + m - p + 1)) / (curveMath.getKnot(j + m + 1) - curveMath.getKnot(j + m - p + 1)));
            result = Vec3d::lerp(controlPt[j], controlPt[j + 1], omega);
            points.push_back(result.x  /result.z);
            points.push_back(result.y  / result.z);
            points.push_back(result.z);
        }
        
    }
    return points;
}

