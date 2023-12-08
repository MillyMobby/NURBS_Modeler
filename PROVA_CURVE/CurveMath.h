#pragma once
#include "Vec3d.h"
#include "PredefinedCurves.h"


enum Knot_Types {
    OPEN,
    CIRCLE,
    UNIFORM
};

class CurveMath
{
private:
    std::vector<double> knots;		
    std::vector<Vec3d> controlPoints; 

    bool bezier = false, makeNURBS = false;

    int degree;
    int knotsType = 0;
    PredefinedCurves predefinedCurves;

public:
    CurveMath() {};
    ~CurveMath() {};

    bool degenere(int pointsNum);
    const int getKnotsInterval(double t);
    const std::vector<double> getKnotsVector();

    const double getKnot(int i);
    inline int getKnotsSize() const {  return knots.size(); }

    inline bool isBezier() const { return bezier; }
    inline void setBezier(bool isBezier) { bezier = isBezier; }
    inline bool isNURBS() const { return makeNURBS; }
    inline void setNURBS(bool NURBS) { makeNURBS = NURBS; }


    inline int getKnotsType() const { return knotsType; }
    inline void setKnotsType(int type) { knotsType = type; }
    inline int getDegree() const { return degree; }

    inline double getDomainLeft() const { return 0; }
    inline double getDomainRight() const { return 1; }

    inline int getControlPointsSize() const { return controlPoints.size(); }

    
    void generateKnots();
    void openKnots();
    void circle();
    void setControlPoints(std::vector<Vec3d> cp);
    void setDegree(int p);

    Vec3d deCasteljau(double t);
    void deCasteljauSplit(double t, std::vector<Vec3d>& left, std::vector<Vec3d>& right);
    Vec3d deBoor(double t);   
    std::vector<double> BSplineBase(double t);
    void degreeRaise(std::vector<Vec3d>& newPoints);
};

