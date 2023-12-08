#include "LineStripGraphics.h"
LineStripGraphics::~LineStripGraphics() { _vertices.clear(); }

void LineStripGraphics::setVertices(std::vector<double> vertices) {
   _vertices.clear();
    for (auto vertex : vertices) {
        _vertices.push_back(vertex);
    }
    
    _pointsNumber = _vertices.size()/3;
    LoadPointsIntoVBO();
    isChanged = true;
}

std::vector<double> LineStripGraphics::getVertices() {
    return _vertices;
}

void LineStripGraphics::clearVertives() {
    _vertices.clear();
}

const int LineStripGraphics::getSelectedVert() { return _selectedVert; }

void LineStripGraphics::setSelectedVert(int s) { _selectedVert = s; }

void LineStripGraphics::setLineColor(Vec3f col) {
    _lineColor = col;
}

const int LineStripGraphics::getPointsNumber() { return _pointsNumber; }

const double& LineStripGraphics::getControlPt_X(int& i) {
    if (_pointsNumber > 0)return _vertices[i * _stride];
   return 0;
}

const double& LineStripGraphics::getControlPt_Y(int& i) {
    if (_pointsNumber > 0) return _vertices[i * _stride + 1];
     return 0;
}

const double& LineStripGraphics::getControlPt_Z(int& i) {
    if (_pointsNumber > 0) return _vertices[i * _stride + 2];
    return 0;
}

void LineStripGraphics::initGL() {
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    GLsizeiptr verticesSize = 1000*3* sizeof((void*)(0));

    glBufferData(GL_ARRAY_BUFFER, verticesSize, _vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, _stride * sizeof(GLdouble), (void*)(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void LineStripGraphics::setupGL() {

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthFunc(GL_LEQUAL);		

    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);	
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPointSize(5);
    glLineWidth(5);
}

void LineStripGraphics::cleanGL(GLuint& shaderProgram) {
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    
    glDeleteProgram(shaderProgram);
}

void LineStripGraphics::LoadPointsIntoVBO()
{
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, _pointsNumber * 3 * sizeof(double), &_vertices[0]); 
}

void LineStripGraphics::AddPoint(double x, double y)
{
    _vertices.push_back(x);
    _vertices.push_back(y);
    
    _pointsNumber++; 
        
    LoadPointsIntoVBO();
    
   isChanged = true;
}

void LineStripGraphics::ChangePoint(int i, double x, double y, double z)
{
    if (i >= 0 && i < _pointsNumber) {
        _vertices[i * _stride] = x;
        _vertices[i * _stride + 1] = y;
        _vertices[i * _stride + 2] = z;
    }
    LoadPointsIntoVBO();
    isChanged = true;
}

void LineStripGraphics::ChangePoint(int i, double x, double y)
{
    if (i >= 0 && i < _pointsNumber) {
        _vertices[i * _stride] = x;
        _vertices[i * _stride + 1] = y;
    }
    LoadPointsIntoVBO();
    isChanged = true;
}


void LineStripGraphics::RemoveFirstPoint()
{
    if (_pointsNumber == 0) { return; }

    for (int i = 0; i < _pointsNumber - 1; i++) {
        _vertices[i * _stride] = _vertices[(i + 1) * _stride];
        _vertices[i * _stride + 1] = _vertices[(i + 1) * _stride + 1];       
    }
    _pointsNumber--;
    if (_pointsNumber > 0) {
        LoadPointsIntoVBO();
        
        isChanged = true;
    }
}

void LineStripGraphics::RemoveLastPoint() {
    if (_pointsNumber == 0) {
        return;
    }
    if (_pointsNumber > 0) {
        _pointsNumber--;
       
        isChanged = true;
    }
}

void LineStripGraphics::renderScene() {
        if (_pointsNumber > 0) {
            glBindVertexArray(_VAO);
            glVertexAttrib3f(_colorLocation, _lineColor.x, _lineColor.y, _lineColor.z);
            glDrawArrays(GL_LINE_STRIP, 0, _pointsNumber); 

            if (drawPoints) {
                glVertexAttrib3f(_colorLocation, _pointsColor.x, _pointsColor.y, _pointsColor.z);
                glDrawArrays(GL_POINTS, 0, _pointsNumber);

                glBindVertexArray(0);
            }
        }   
        isChanged = false;
}

void LineStripGraphics::setLineColor() {
    _lineColor = randomColor();
}

void LineStripGraphics::setLineColor(float r, float g, float b) {
    _lineColor = Vec3f(r, g, b);
}

void LineStripGraphics::setColor() {
    setLineColor();  
}

Vec3f LineStripGraphics::randomColor() {
    float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    return Vec3f(x, y, z);
}