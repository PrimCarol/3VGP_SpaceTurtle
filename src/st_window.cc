#include "st_window.h"

ST::Window::Window(){
    if (glfwInit()) {
        glWindow = glfwCreateWindow(1080, 720, "Space Turtle", NULL, NULL);
    }
}

ST::Window::Window(int width, int height){
    if (glfwInit()) {
        glWindow = glfwCreateWindow(width, height, "Space Turtle", NULL, NULL);
    }
}

//GLFWwindow* ST::Window::GetWindow(){
//    return glWindow;
//}

ST::Window::Window(const Window& o){}

void ST::Window::Focus() {
    glfwMakeContextCurrent(glWindow);
}

void ST::Window::Render(){
    

    glfwSwapBuffers(glWindow);

    glfwPollEvents();
}

//bool ST::Window::isInputDown(ST_INPUT input){
//    if (glfwGetKey(glWindow, input) == GLFW_PRESS) {
//        if (lastInput != input) {
//            lastInput = input;
//            return true;
//        }
//        return false;
//    }
//    return false;
//}
//
//bool ST::Window::isInputPressed(ST_INPUT input){
//    
//    return false;
//}
//
//bool ST::Window::isInputReless(ST_INPUT input){
//    
//    return false;
//}

bool ST::Window::isKeyDown(int key){
    if (glfwGetKey(glWindow, key) == GLFW_PRESS) {
        if (lastKeyPressed != key) {
            lastKeyPressed = key;
            return true;
        }
        return false;
    }
    return false;
}

bool ST::Window::isKeyPressed(int key){
    if (glfwGetKey(glWindow, key) == GLFW_PRESS) {
        lastKeyPressed = key;
        return true;
    }
    return false;
}

bool ST::Window::isKeyReless(int key){
    if (glfwGetKey(glWindow, key) == GLFW_RELEASE) {
        if (lastKeyPressed == key) {
            lastKeyPressed = -1;
            return true;
        }
    }
    
    return false;
}

double ST::Window::mousePosX(){
    glfwGetCursorPos(glWindow, &mouseX, &mouseY);
    return mouseX;
}

double ST::Window::mousePosY(){
    glfwGetCursorPos(glWindow, &mouseX, &mouseY);
    return mouseY;
}

bool ST::Window::isMouseDown(int button){
    if (glfwGetMouseButton(glWindow, button) == GLFW_PRESS) {
        if (lastMousePressed != button) {
            lastMousePressed = button;
            return true;
        }
        return false;
    }
    return false;
}

bool ST::Window::isMousePressed(int button){
    if (glfwGetMouseButton(glWindow, button) == GLFW_PRESS) {
        lastMousePressed = button;
        return true;
    }
    return false;
}

bool ST::Window::isMouseReless(int button){
    if (glfwGetMouseButton(glWindow, button) == GLFW_RELEASE) {
        if (lastMousePressed == button) {
            lastMousePressed = -1;
            return true;
        }
    }

    return false;
}

bool ST::Window::isOpen() {
    if (glWindow == NULL) { return false; }
    return !glfwWindowShouldClose(glWindow);
}

void ST::Window::ColorBg(float c[4]) {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(c[0],c[1],c[2],c[3]);
}

void ST::Window::ColorBg(float r, float g, float b, float a){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(r, g, b, a);
}

ST::Window::~Window(){
    glfwTerminate();
}
