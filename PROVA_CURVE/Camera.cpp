#include "Camera.h"
void Camera::setEye(const Vec3d& eye) {
	_eye = eye;
	_isChanged = true;
}
const Vec3d& Camera::getEye() const {
	return _eye;
}

void Camera::setLookAt(const Vec3d& lookat) {
	_lookAt = lookat;
	_isChanged = true;
}

const Vec3d& Camera::getLookAt() const {
	return _lookAt;
}
void Camera::setup(const Vec3d& up) {
	_up = up;
	_isChanged = true;
}
const Vec3d& Camera::getUp() const {
	return _up;
}
void Camera::setFov(const float& fov) {
	_fov = fov;
	_isChanged = true;

}
const float Camera::getFov() const {
	return _fov * (180.0 / 3.141592653589793238463);
}
void Camera::setNear(const float& cameraNear) {
	_near = cameraNear;
	_isChanged = true;
}
const float& Camera::getNear() const {
	return _near;
}

void Camera::setFar(const float& cameraFar) {
	_far = cameraFar;
	_isChanged = true;
}
const float& Camera::getFar() const {
	return _far;
}

void Camera::setTransform(const Mat4d& transform) {
    _transform = transform;
    _isChanged = true;
}
const Mat4d& Camera::getTransform() const {
    return _transform;
}

const float& Camera::getAspectRatio() const {
	return _aspectRatio;
}

void Camera::computeAspectRatio(int width, int height) {
	_aspectRatio = static_cast<double> (width) / static_cast<double> (height);
	_isChanged = true;
}

void Camera::ProcessKeyboard(int direction, double deltaTime)
{
    double velocity =  deltaTime/8;
    if (direction == FORWARD) {
        
        Mat4d scale = Mat4d::scaleMatrix(1.5+ velocity/4, 1.5 + velocity / 4, 1.5 + velocity / 4);      
        updateTransformMatrix(scale);
    }
    if (direction == BACKWARD) {
        Mat4d scale = Mat4d::scaleMatrix(1.5/2- velocity / 4, 1.5/2- velocity / 4, 1.5/2- velocity / 4);
        updateTransformMatrix(scale);
    }
    if (direction == ROTATION_SX) {     
        Mat4d rot = Mat4d::rotateZ(velocity* 3.141592653589793238463 );       
        updateTransformMatrix(rot);

    }
    if (direction == ROTATION_DX) {
        Mat4d rot = Mat4d::rotateZ(velocity * -3.141592653589793238463 );
        updateTransformMatrix(rot);
    }
    if (direction == LEFT) {      
        Mat4d trans = Mat4d::translation(-velocity, 0, 0);
        updateTransformMatrix(trans);
    }
    if (direction == RIGHT) {
        
        Mat4d trans = Mat4d::translation(velocity, 0, 0);
        updateTransformMatrix(trans);        
    }
}

void Camera::updateProjectionMatrix(int w, int h) {
    computeAspectRatio(w, h);    
    _projectionMatrix = Mat4d::orthographic(-1, 1, -1, 1, _near, _far);
}

const Mat4d& Camera::getProjectionMatrix() const {
    return _projectionMatrix;
}

const Mat4d& Camera::getViewMatrix() const {
    return _viewMatrix;
}

const Mat4d& Camera::getZoomMatrix() const {
    return _zoom;
}

void Camera::updateViewMatrix(Mat4d& transform) {
    _viewMatrix = Mat4d::ViewMatrix(_eye, _lookAt, _up);
    _viewMatrix = _zoom*_viewMatrix;
}

void Camera::updateTransformMatrix(Mat4d& transform) {
    _transform = transform * _transform;
}

void Camera::update(int w, int h) {
    Mat4d id = Mat4d::identity();
    if (_isChanged) {
        
        updateViewMatrix(id);
        updateProjectionMatrix(w,h);

        _isChanged = false;
    }
}

void Camera::getEyeFromMatrix() {
    Vec4d eye = _viewMatrix.getCol(3);
    std::cout << "eye " << eye << std::endl;
}