#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include "Camera.h"
class Shader
{
private:
	std::string _name = "";
	std::string _vertexShader = "";
	std::string _gShader = "";
	std::string _fragmentShader = "";
	GLuint _shaderProgram = -1; 

public:

	const static unsigned int maxLightsNumber = 3;

	Shader() {};
	~Shader() { }
	void processShader();
	void setName(std::string name);
	std::string& getName();
	void setVShader(std::string vShader);
	const std::string& getVShader();
	void setGShader(std::string gShader);
	const std::string& getGShader();
	void setFShader(std::string fShader);
	const std::string& getFShader();

	GLuint& getShaderProgram(); 

	void setMat4(const std::string& name, const Mat4d& value); //NEW CAMERA
	void setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w);
	void setVec3(const std::string name, const float& x, const float& y, const float& z); // NEW LUCI 
	void setI1(const std::string name, const bool& b); //NEW LUCI 
	void setT1(const std::string name, const int& b); // NEW ARI
	void setVec4i(const std::string& name, const int& x, const int& y, const int& z, const int& w); //NEW ARI
	void setF(const std::string name, const float& f); //NEW ARI

	void setUniform(const std::string& name, std::vector<int> value, const int& count = -1);//NEW ARIIIIIIIII ??????
	void setUniform(const std::string& name, std::vector<float> value, const int& count);
	//void updateLightUniform(Light& light, const int& lightIndex, const bool& isEnable);//NEW LUCI
	
	//void updateObjectUniform(Object obj);

	bool buildMaterial(const std::string& vShaderPath/*, const std::string& gShaderPath*/, const std::string& fShaderPath);
	bool compile(const std::string& shaderCode, const GLenum& shaderType, GLuint& shader);
	bool link(const GLuint& vShader/*, const GLuint& gShader*/, const GLuint& fShader);

	void clean();
	bool readShader(const std::string& path, std::string& shader);
	bool buildMaterial();

	void draw();
	void updateCameraUniform(const Camera& cam);
};

