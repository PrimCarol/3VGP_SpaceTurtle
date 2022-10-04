#include "st_window.h"

ST::Window::Window(){
    glWindow = NULL;
    for (int i = 0; i < 4; i++) { color[i] = 0.0f; }
    if (glfwInit()) {
        glWindow = glfwCreateWindow(1080, 720, "Space Turtle", NULL, NULL);
    }
}

ST::Window::Window(int width, int height){
    glWindow = NULL;
    for (int i = 0; i < 4; i++) { color[i] = 0.0f; }
    if (glfwInit()) {
        glWindow = glfwCreateWindow(width, height, "Space Turtle", NULL, NULL);
    }
}

//GLFWwindow* ST::Window::GetWindow(){
//    return glWindow;
//}

ST::Window::Window(const Window& o){
    glWindow = o.glWindow;
    for (int i = 0; i < 4; i++){
        color[i] = o.color[i];
    }
}

void ST::Window::Focus() {
    glfwMakeContextCurrent(glWindow);
}

void ST::Window::Render(){
    
    glfwSwapBuffers(glWindow);

    glfwPollEvents();
}

bool ST::Window::isPressed(ST_INPUT input){
    
    switch (input){
    case ST::ST_INPUT_UP:
        if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS) {
            lastKeyPressed = input;
            return true;
        }else if (glfwGetKey(glWindow, GLFW_KEY_UP) == GLFW_PRESS) {
            lastKeyPressed = input;
            return true;
        }
        break;
    case ST::ST_INPUT_DOWN:
        if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS) {
            lastKeyPressed = input;
            return true;
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
            lastKeyPressed = input;
            return true;
        }
        break;
    case ST::ST_INPUT_RIGHT:
        if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS) {
            lastKeyPressed = input;
            return true;
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            lastKeyPressed = input;
            return true;
        }
        break;
    case ST::ST_INPUT_LEFT:
        if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS) {
            lastKeyPressed = input;
            return true;
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
            lastKeyPressed = input;
            return true;
        }
        break;
    case ST::ST_INPUT_FIRE:
        if (glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
            lastMousePressed = input;
            return true;
        }
        break;
    case ST::ST_INPUT_JUMP:
        if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_PRESS) {
            lastKeyPressed = input;
            return true;
        }
        break;
    }
    
    return false;
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
