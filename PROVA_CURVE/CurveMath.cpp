#include "CurveMath.h"
bool CurveMath::degenere(int pointsNum) {	
	if (pointsNum <= degree ) return true;
	else return false;
}

const int CurveMath::getKnotsInterval(double t) {
	int n = knots.size()-degree-2;
	
	for (int i = 0; i < n; i++) {
		double k = knots[i];
		if (t >= knots[i] && t < knots[i+1]) return i;
	}
	if (t >= knots[n] ) {  return n; }
	
	return -1;
}

const std::vector<double> CurveMath::getKnotsVector() { return knots; }

const double CurveMath::getKnot(int i) {
	if (i <= knots.size()-1 && i >= 0) return knots[i];
	else return 0;
}

void CurveMath::generateKnots() {
	knots.clear();
	switch (knotsType) {
	case 0:
		openKnots();
		break;
	case 1:
		circle();
		break;
	default:
		openKnots();
		break;
	}	
}

void CurveMath::openKnots() {
	knots.clear();
	for (int i = 0; i <= degree; i++) { knots.push_back(0); }

	int middle = (controlPoints.size() -1)- degree;
	for (int j = 0; j < middle; j++) {
		double h = double(j + 1) / (middle + 1);
		knots.push_back(h);		
	}	

	for (int k = 0; k <=degree; k++) { knots.push_back(1);  }
}

void CurveMath::circle() {
	if (degree == 2 && controlPoints.size() == 9) {
		knots.clear();
		for (int i = 0; i <= degree; i++) { knots.push_back(0); }
		knots.push_back(double(0.25));
		knots.push_back(double(0.25));

		knots.push_back(double(0.5));
		knots.push_back(double(0.5));

		knots.push_back(double(0.75));
		knots.push_back(double(0.75));
		for (int k = 0; k <= degree; k++) { knots.push_back(1); }
	}
	else { std::cout << "this circe only works with 9 control points and degree 2 \n"; }
}

void CurveMath::setDegree(int p) { degree = p; }

Vec3d CurveMath::deCasteljau(double t) {		
	Vec3d result = Vec3d(0);

	if (controlPoints.size() == degree + 1) {
		std::vector<Vec3d> points;
		for (int k = 0; k <= degree; k++) {
			points.push_back(controlPoints[k]);
			points.back().x *= points.back().z;
			points.back().y *= points.back().z;
		}

		for (int i = degree; i > 0; i--) {			
			for (int j = 0; j < i; j++) {
				points[j] = Vec3d::lerp(points[j], points[j + 1], t);		
			}
		}
		result = points[0]/points[0].z;
		points.clear();
	}
	return result;
}

void CurveMath::deCasteljauSplit(double t, std::vector<Vec3d>& left, std::vector<Vec3d>&right) {
	Vec3d result = Vec3d(0);

	if (controlPoints.size() == degree + 1) {
		std::vector<Vec3d> points;
		for (int k = 0; k <= degree; k++) {
			points.push_back(controlPoints[k]);
			points.back().x *= points.back().z;
			points.back().y *= points.back().z;
		}

		for (int i = degree; i > 0; i--) {
			left.push_back(points[0]);
			right.push_back(points[i]);

			for (int j = 0; j < i; j++) {
				points[j] = Vec3d::lerp(points[j], points[j + 1], t);
			}
		}
		left.push_back(points[0]);
		right.push_back(points[0]);
		points.clear();
	}
	for (int k = 0; k <= degree; k++) {		
		left[k].x /= left[k].z;
		left[k].y /= left[k].z;

		right[k].x /= right[k].z;
		right[k].y /= right[k].z;		
	}

	//return result;
}


void CurveMath::setControlPoints(std::vector<Vec3d> cp) {
	controlPoints = cp;
}

Vec3d CurveMath::deBoor(double t) {
	Vec3d result = Vec3d(0);
	if (controlPoints.size() == knots.size() - degree - 1 && degenere(controlPoints.size())==false) {

		int m = getKnotsInterval(t);
		int n = controlPoints.size();
	
		if (m >= degree && m < n) {
			std::vector<Vec3d> points;
			for (int j = m - degree; j <= m; j++) {
				points.push_back(controlPoints[j]);
				points.back().x *= points.back().z;
				points.back().y *= points.back().z;
			}

			for (int i = degree; i > 0; i--) {
				for (int j = 0; j < i; j++) {
					double omega = (t - knots[j + m - i + 1]) / (knots[j + m + 1] - knots[j + m - i + 1]);
					points[j] = Vec3d::lerp(points[j], points[j + 1], omega);
				}
			}
			result = points[0]/points[0].z; 
			points.clear();
		} 
	}
	return result;
}



std::vector<double> CurveMath::BSplineBase(double t) {
	
	int n = knots.size() - degree - 1;
	std::vector<double> B = std::vector<double>(n, 0);
	if (n>degree) {
		int m = getKnotsInterval(t);
		if (m >= degree and m < n) {
			B[m] = 1.0f;
			for (int i = 1; i <= degree; i++) {
				B[m - i] = (knots[m + 1] - t) / (knots[m + 1] - knots[m - i + 1]) * B[m - i + 1];

				for (int j = m - i + 1; j < m; j++) {
					B[j] = (t - knots[j]) / (knots[j + i] - knots[j]) * B[j] + \
						(knots[j + i + 1] - t) / (knots[j + i + 1] - knots[j + 1]) * B[j + 1];
				}
				B[m] = ((t - knots[m]) / (knots[m + i] - knots[m])) * B[m];
			}
		}
		if (makeNURBS==true) {
			if (controlPoints.size() == n) {
				double sum = 0;
				for (int k = 0; k < n; k++) {
					B[k] = controlPoints[k].z * B[k];
					sum += B[k];
				}
				for (int k = 0/*1*/; k < n; k++) {
					B[k] /= sum;
				}
			}			
		}
	}		
	return B;
}




void CurveMath::degreeRaise(std::vector<Vec3d>& newPoints) {
	std::vector<Vec3d> controlPointsCopy;
	for (int k = 0; k < controlPoints.size(); k++) {
		controlPointsCopy.push_back(controlPoints[k]);
		controlPointsCopy.back().x *= controlPointsCopy.back().z;
		controlPointsCopy.back().y *= controlPointsCopy.back().z;
	}

	if (controlPoints.size() == degree + 1) {
		newPoints.push_back(controlPointsCopy[0]);

		for (int i = 1; i < degree + 1; i++) {
			newPoints.push_back(Vec3d::lerp(controlPointsCopy[i], controlPointsCopy[i - 1], (double(i)) / (degree + 1)));
		}

		newPoints.push_back(controlPointsCopy[degree]);
		for (int i = 0; i < newPoints.size(); i++) {
			newPoints[i].x /= newPoints[i].z;
			newPoints[i].y /= newPoints[i].z;
		}
		setDegree(degree + 1);
		setControlPoints(newPoints);
	}
}





