#pragma once
#include <vector>
class PredefinedCurves
{
private:
	bool loaded = false;

public:
	PredefinedCurves() { };
	~PredefinedCurves() {};

	inline bool getLoaded() const  { return loaded; }
	inline void setLoaded(bool state) { loaded = state; }
	
	static const std::vector<float> getCircleWeights();
	static const std::vector<double> circleKnots();
	static const std::vector<double> getCircleControlPolygon();

	const int getCircleDegree();
	
};

