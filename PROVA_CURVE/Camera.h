#pragma once 
#include "Vec3d.h" 
#include "Mat4d.h"
//#include "Vec2f.h"
#include <cmath> 

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	ROTATION_DX,
	ROTATION_SX
};

class Camera
{
private:
	Mat4d _viewMatrix;
	Mat4d _movementMatrix;
	Mat4d _projectionMatrix;
	Mat4d _transform;
	Mat4d _zoom = Mat4d::identity();

	Vec3d _eye;
	Vec3d _lookAt;
	Vec3d _up;
	float _fov = 0.0f;
	float _aspectRatio = 0.0;
	float _near = 0.0f;
	float _far = 0.0f;
	bool _isChanged = false;

public:
	Camera() {}
	Camera(const Camera& camera) {
		_eye = camera._eye; _lookAt = camera._lookAt;
		_up = camera._up; _fov = camera._fov;
		_aspectRatio = camera._aspectRatio;
		_near = camera._near;
		_far = camera._far;
		_viewMatrix = camera._viewMatrix;
		_movementMatrix = camera._movementMatrix;
		_projectionMatrix = camera._projectionMatrix;
		_isChanged = camera._isChanged;

	}
	~Camera() {}
	void setEye(const Vec3d& eye);
	const Vec3d& getEye() const;
	//void setFront(const Vec3d& front);


	int walk(std::string direction, std::string scene);
	void setLookAt(const Vec3d& lookat);
	const Vec3d& getLookAt() const;
	void setup(const Vec3d& up);
	const Vec3d& getUp() const;
	void setFov(const float& fov);
	const float getFov() const;
	void setNear(const float& cameraNear);
	const float& getNear() const;
	void setFar(const float& cameraFar);
	const float& getFar() const;
	void setTransform(const Mat4d& transform);
	const Mat4d& getTransform() const;
	void computeAspectRatio(int width, int height);
	void ProcessKeyboard(int direction, double deltaTime); 
	const float& getAspectRatio() const;
	const Mat4d& getViewMatrix() const;
	const Mat4d& getZoomMatrix() const;
	const Mat4d& getProjectionMatrix() const;
	void updateViewMatrix(Mat4d& transform);
	void updateTransformMatrix(Mat4d& transform);
	void updateProjectionMatrix(int w, int h);
	void update(int w, int h);
	void getEyeFromMatrix();

};