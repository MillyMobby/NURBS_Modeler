#include "Shader.h"

void Shader::setName(std::string name) {
    _name = name;
}

std::string& Shader::getName() {
    return _name;
}

void Shader::setVShader(std::string pathvShader) {
    _vertexShader = pathvShader;
}

const std::string& Shader::getVShader() {
    return _vertexShader;
}

void Shader::setGShader(std::string pathvShader) {
    _gShader = pathvShader;
}

const std::string& Shader::getGShader() {
    return _gShader;
}

void Shader::setFShader(std::string pathfShader) {
    _fragmentShader = pathfShader;
}

const std::string& Shader::getFShader() {
    return _fragmentShader;
}


GLuint& Shader::getShaderProgram() {
    return _shaderProgram;
}

bool Shader::readShader(const std::string& path, std::string& shader) {
    bool rv = true;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shader = shaderStream.str();
    }

    catch (std::ifstream::failure error) {
        rv = false;
        std::cout << "ERRORE DI APERTURA FILE DELLO SHADER ->" << shader; // AGGIUNGERE QUALE SHADER
    }
    return rv;

}

bool Shader::buildMaterial()
{

    bool rv = true;

    std::ifstream f;


    glUseProgram(0); //lo metto perchè ignoro tutto ciò che è precedente, 

                     //tutte le chiamate opengl fatte qui non possono rischiare di riferirsi a un program vecchio (lo 0 è come se fosse "NULL")

    f.open(getVShader());
    bool vShaderExist = f.good();
    f.close();

   /* f.open(getGShader());
    bool gShaderExist = f.good();
    f.close();*/

    f.open(getFShader());
    bool fShaderExist = f.good();
    f.close();


    if (vShaderExist /*&& gShaderExist*/ && fShaderExist) {

        rv = buildMaterial(getVShader()/*, getGShader()*/, getFShader());
    }
    else {
        std::cout << "NON ESISTONO GLI SHADER DI " << _name << std::endl;
        rv = false;
    }


    return rv;
}


bool Shader::buildMaterial(const std::string& vShaderPath/*,  const std::string& gShaderPath*/, const std::string& fShaderPath)
{
    bool rv = false;
    if (readShader(vShaderPath, _vertexShader)  /*&&readShader(gShaderPath, _gShader) */&& readShader(fShaderPath, _fragmentShader)) {
        GLuint vShader;
        //GLuint gShader;
        GLuint fShader;
        if (compile(getVShader(), GL_VERTEX_SHADER, vShader) /*&& compile(getGShader(), GL_GEOMETRY_SHADER, gShader) */&& compile(getFShader(), GL_FRAGMENT_SHADER, fShader)) {
            if (link(vShader/*, gShader*/, fShader)) {

                glUseProgram(_shaderProgram); // momentaneo
                glDeleteShader(vShader);
                //glDeleteShader(gShader);
                glDeleteShader(fShader);
                rv = true;
            }
        }
    }
    return rv;
}


bool Shader::compile(const std::string& shaderCode, const GLenum& shaderType, GLuint& shader) {
    bool rv = true;
    const GLchar* shaderCodeChar = shaderCode.c_str();

    GLchar infoLog[512];
    GLint success;

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCodeChar, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl; // non è solo fragment, quello è da cambiare
        rv = false;
    }
    return rv;
}


bool Shader::link(const GLuint& vShader/*, const GLuint& gShader*/, const GLuint& fShader) {
    bool rv = true;

    GLchar infoLog[512];
    GLint success;

    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vShader);
    //glAttachShader(_shaderProgram, gShader);
    glAttachShader(_shaderProgram, fShader);
    glLinkProgram(_shaderProgram);

    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        rv = false;
    }
    return rv;
}

void Shader::draw() {
    glUseProgram(_shaderProgram);
}

void Shader::processShader() {
    setName("color");
    setVShader("color.vert");
    //setGShader("color.geom");
    setFShader("color.frag");
    /*std::cout << "path1 " << bg.getVShader();
    std::cout << "path2 " << bg.getFShader();*/

    buildMaterial();
    std::cout << "Vertex shader " << getVShader() << std::endl;
    //std::cout << "Geometry shader " << getGShader() << std::endl;
    std::cout << "Fragment shader " << getFShader() << std::endl;

}

void Shader::setVec4(const std::string& name, const float& x, const float& y, const float& z, const float& w) {
    glUniform4f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z, w);
}

void Shader::setVec3(const std::string name, const float& x, const float& y, const float& z) { // NEW LUCI 
    glUniform3f(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z);
}


void Shader::setI1(const std::string name, const bool& b) { // NEW LUCI NON USATA PERCHé USO QUELLA PER INT
    glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), b);
}

void Shader::setF(const std::string name, const float& f) { // NEWW
    glUniform1f(glGetUniformLocation(_shaderProgram, name.c_str()), f);
}



void Shader::setVec4i(const std::string& name, const int& x, const int& y, const int& z, const int& w) {
    glUseProgram(_shaderProgram); // NEW
    glUniform4i(glGetUniformLocation(_shaderProgram, name.c_str()), x, y, z, w);
}


void Shader::setT1(const std::string name, const int& n) {

    glUniform1i(glGetUniformLocation(_shaderProgram, name.c_str()), n);
}

void Shader::setMat4(const std::string& name, const Mat4d& value) {

    glUniformMatrix4fv(glGetUniformLocation(_shaderProgram, name.c_str()), 1, GL_FALSE, value.m.data());

}

void Shader::updateCameraUniform(const Camera& cam) {

    setMat4("viewMatrix", cam.getViewMatrix());
    setMat4("orthoMatrix", cam.getProjectionMatrix());
    setMat4("transform", cam.getTransform());
}




