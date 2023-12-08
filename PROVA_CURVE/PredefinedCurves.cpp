#include "PredefinedCurves.h"
const std::vector<float> PredefinedCurves::getCircleWeights() {
	const std::vector<float> circleWeights = { 1, 0.707107, 1, 0.707107, 1, 0.707107, 1, 0.707107 ,1 };	
	return circleWeights;
}

const std::vector<double> PredefinedCurves::circleKnots() {
	const std::vector<double> knots = { 0,0,0,0.25, 0.25,0.5,0.5,0.75,0.75,1,1,1 };
	return knots;
}

const std::vector<double> PredefinedCurves::getCircleControlPolygon() {
	const std::vector<double> circleControlPolygon = {
	// 0.3, 0.0, //P1
	// 0.3, 0.3, //P2
	// 0.0, 0.3, //P3
	//-0.3, 0.3, //P4
	//-0.3, 0.0, //P5
	//-0.3,-0.3, //P6
	// 0.0,-0.3, //P7
	// 0.3,-0.3, //P8
	// 0.3, 0.0, //P9
 0.333333, 0.12,
 0.332292, 0.528,
0.123958, 0.524,
- 0.0864583, 0.522,
- 0.084375, 0.128,
- 0.0822917, -0.28,
0.126042, -0.276,
0.333333, -0.272,
0.333333, 0.12

	};

	return circleControlPolygon;
}

const int getCircleDegree() {
	return 2;
}

