#include "Viewer.h"
static Scene scene;
static float deltaTime;	 //Time between current frame and last frame
float lastFrame = 0.0f;
static bool isMoving = false ,rotation = false;
void Viewer::start() {
		init();	
		scene.initScene();
		scene.loadCamera(_windowSize.width, _windowSize.height);

	

		while (!glfwWindowShouldClose(_window) ) {
			//if (_windowSize.width > _windowSize.height && scene.getImgui().itemCurrent == 1) {
			//	glViewport(0, (_windowSize.height - _windowSize.width) / 2, _windowSize.width, _windowSize.width);
			//	//glViewport(0, 0, 2000, 2000/*_windowSize.width, _windowSize.height*/);
			//	/*Mat4d scale = Mat4d::scaleMatrix(_windowSize.height - _windowSize.width, _windowSize.height - _windowSize.width, _windowSize.height - _windowSize.width);
			//	scene.getCamera().updateTransformMatrix(scale);*/
			//	glMatrixMode(GL_PROJECTION);
			//	glLoadIdentity();
			//}
			//else {
				//glViewport(0, 0, 1920,1000/*_windowSize.width, _windowSize.height*/);
				//glViewport((_windowSize.width - _windowSize.height) / 2, 0, _windowSize.height, _windowSize.height);
			//}
			/*scene.getImgui().setW(_windowSize.width);
			scene.getImgui().setH(_windowSize.height);*/
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			processInput();
			scene.checkForTransformations(isMoving, rotation);
			isMoving = false;
			rotation = false;
			
			scene.updateCamera(_windowSize.width, _windowSize.height);
			scene.BG();	
			glfwMakeContextCurrent(_window);
			glClear(GL_COLOR_BUFFER_BIT);
			const float clearDepth = 1.0f;
			glClearBufferfv(GL_DEPTH, 0, &clearDepth);	

			scene.run(deltaTime);			
			
			scene.windowShouldCloseIMGUI(_window);			
			glfwPollEvents();
			glfwSwapBuffers(_window);		

		}		
		scene.clean();
		
		Clean();		
}

bool Viewer::init() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	

	_windowSize.isChanged = false;

	_window = glfwCreateWindow(_windowSize.width, _windowSize.height, "curve", NULL, NULL);
	scene.getImgui().setW(_windowSize.width);
	scene.getImgui().setH(_windowSize.height);
	//glfwGetWindowSize(window, &width, &height);
	
	glfwMakeContextCurrent(_window);
	if (_window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	glfwSetWindowUserPointer(_window, (void*)&_windowSize);
	setupCallbacks();	

	scene.setIMGUI(_window);

	return 1;
}

bool Viewer::processInput() {	
		
	isMoving = false;
		if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(_window, true);
		}
		
		if (glfwGetKey(_window, GLFW_KEY_UP) == GLFW_PRESS) { scene.getCamera().ProcessKeyboard(0, deltaTime); isMoving = true; } //FORWARD,
		if (glfwGetKey(_window, GLFW_KEY_DOWN) == GLFW_PRESS) { scene.getCamera().ProcessKeyboard(1, deltaTime); isMoving = true;} //BACKWARD,
		if (glfwGetKey(_window, GLFW_KEY_Q) == GLFW_PRESS) { scene.getCamera().ProcessKeyboard(2, deltaTime); isMoving = true; //LEFT,
		}
		if (glfwGetKey(_window, GLFW_KEY_E) == GLFW_PRESS) { scene.getCamera().ProcessKeyboard(3, deltaTime); isMoving = true; //RIGHT,
		}
		if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) { 
			scene.getCamera().ProcessKeyboard(5, deltaTime); 
			rotation = true;
			isMoving = true; //ROTATION_SX
		}
		if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) { 
			scene.getCamera().ProcessKeyboard(4, deltaTime); 
			isMoving = true; //ROTATION_DX,
			rotation = true;
		}
		
		return isMoving;
}

bool Viewer::Clean() {	
	glfwTerminate();
	return true;
}

void Viewer::setupCallbacks() {
	glfwSetFramebufferSizeCallback(_window, frameBufferSizeCB);
	glfwSetKeyCallback(_window, keyCallback);	
	glfwSetMouseButtonCallback(_window, mouseButtonCallback);
	glfwSetCursorPosCallback(_window, cursorPosCallback);
	glfwSetScrollCallback(_window, scrollCallback);


}

void Viewer::frameBufferSizeCB(GLFWwindow* window, int width, int height) {
	if (window != nullptr) {
		double w = (double)height * ((double)1920 / (double)1000);
		double h = (double)width / ((double)1920 / (double)1000);
		glViewport(0, 0, w,h/*width, height*/);
		WindowSize* windowSize = (WindowSize*)glfwGetWindowUserPointer(window);
		if (windowSize != nullptr) {
			windowSize->width = w/*width*/;
			windowSize->height = h/*height*/;
			windowSize->isChanged = true;

			glfwSetWindowAspectRatio(window, 1920, 1000);
		}
		
		
	}
}

void Viewer::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	WindowSize* windowSize = (WindowSize*)glfwGetWindowUserPointer(window);
	double xpos, ypos;
	
	glfwGetCursorPos(window, &xpos, &ypos);
	double clipX = (2.0f * (double)xpos / (double)(windowSize->width  /*  -1*/)) - 1.0f;  // clip space [-1,1]. 
	double clipY = 1.0f - (2.0f * (double)ypos / (double)(windowSize->height /*   -1*/));
	if (yoffset > 0) {
		// Mouse wheel up event std::cout << "Mouse wheel up" << std::endl;
		scene.getCamera().ProcessKeyboard(0, deltaTime); isMoving = true;
	}
	else {
		// Mouse wheel down event std::cout << "Mouse wheel down" << std::endl;
		scene.getCamera().ProcessKeyboard(1, deltaTime); isMoving = true;
	}
	
	Vec3f pos = Vec3f(clipX, clipY, 1);
	scene.setMouse(pos);
	scene.checkForTransformations(isMoving, false);
}

void Viewer::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	WindowSize* windowSize = (WindowSize*)glfwGetWindowUserPointer(window);
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	/*ypos = ypos*2 -( (windowSize->height - windowSize->width) );*/
	double clipX = (2.0f * (double)xpos / (double)(windowSize->width  /*  -1*/)) - 1.0f;  // clip space [-1,1]. 
	double clipY = 1.0f - (2.0f * (double)ypos / (double)(windowSize->height /*   -1*/));
	
	scene.handleMouseEvents(button, action, clipX, clipY, windowSize->width, windowSize->height);
}

void Viewer::cursorPosCallback(GLFWwindow* window, double x, double y) {
	WindowSize* windowSize = (WindowSize*)glfwGetWindowUserPointer(window);
	double dotX = (2.0f * (double)x / (double)(windowSize->width /*   - 1*/)) - 1.0f;
	double dotY = 1.0f - (2.0f * (double)y / (double)(windowSize->height  /*  - 1*/));


	scene.updatePointsByMouse( dotX, dotY, deltaTime);	
}

void Viewer::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_RELEASE) {
		return;			
	}
	if (key == GLFW_KEY_ESCAPE || key == GLFW_KEY_X) {
		glfwSetWindowShouldClose(window, true);
	}
	else scene.handleKeyEvents( key);	
}


