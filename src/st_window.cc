#include "st_window.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

ST::Window::Window(){
    glWindow = NULL;
    for (int i = 0; i < 4; i++) { color[i] = 0.0f; }
    if (glfwInit()) {
        glWindow = glfwCreateWindow(1080, 720, "Space Turtle", NULL, NULL);
        Focus();
    }

    // Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(glWindow, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

ST::Window::Window(int width, int height){
    glWindow = NULL;
    for (int i = 0; i < 4; i++) { color[i] = 0.0f; }
    if (glfwInit()) {
        glWindow = glfwCreateWindow(width, height, "Space Turtle", NULL, NULL);
        Focus();
    }

    // Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(glWindow, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

ST::Window::Window(const Window& o){}

void ST::Window::Focus() const{
    glfwMakeContextCurrent(glWindow);
}

void ST::Window::Render(){

    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(glWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    deltaTime = clock() - lastTime;
    lastTime = clock();

    glfwSwapBuffers(glWindow);

    glfwPollEvents();
}

void ST::Window::Clear() const{
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT);

    // ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Para que toda la ventana tenga la posibilidad de hacer Dock
    //ImGui::DockSpaceOverViewport();
}

void ST::Window::initImGuiWindow(const char* t){
    ImGui::Begin(t);
}

void ST::Window::textImGui(const char* t){
    ImGui::Text(t);
}

bool ST::Window::buttonImGui(const char* t) {
    return ImGui::Button(t);
}

void ST::Window::endImGuiWindow(){
    ImGui::End();
}

bool ST::Window::inputPressed(ST_INPUT input){
    
    switch (input){
    case ST::ST_INPUT_UP:
        if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS) {
            //if (lastKeyPressed != input) {
            //    lastKeyPressed = input;
                return true;
            //}
            //return false;
        }else if (glfwGetKey(glWindow, GLFW_KEY_UP) == GLFW_PRESS) {
            //if (lastKeyPressed != input) {
            //    lastKeyPressed = input;
                return true;
            //}
            //return false;
        }
        break;
    case ST::ST_INPUT_DOWN:
        if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS) {
            //if (lastKeyPressed != input) {
            //    lastKeyPressed = input;
                return true;
            //}
            //return false;
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
            //if (lastKeyPressed != input) {
            //    lastKeyPressed = input;
                return true;
            //}
            //return false;
        }
        break;
    case ST::ST_INPUT_RIGHT:
        if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS) {
            //if (lastKeyPressed != input) {
            //    lastKeyPressed = input;
                return true;
            //}
            //return false;
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            //if (lastKeyPressed != input) {
            //    lastKeyPressed = input;
                return true;
            //}
            //return false;
        }
        break;
    case ST::ST_INPUT_LEFT:
        if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS) {
            //if (lastKeyPressed != input) {
            //    lastKeyPressed = input;
                return true;
            //}
            //return false;
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
            //if (lastKeyPressed != input) {
            //    lastKeyPressed = input;
                return true;
            //}
            //return false;
        }
        break;
    case ST::ST_INPUT_FIRE:
        if (glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
            //if (lastMousePressed != input) {
            //    lastMousePressed = input;
                return true;
            //}
            //return false;
        }
        break;
    case ST::ST_INPUT_JUMP:
        if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_PRESS) {
            //if (lastKeyPressed != input) {
            //    lastKeyPressed = input;
                return true;
            //}
            //return false;
        }
        break;
    case ST::ST_INPUT_ESCAPE:
        if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            //if (lastKeyPressed != input) {
            //    lastKeyPressed = input;
                return true;
            //}
            //return false;
        }
        break;
    }
    //lastKeyPressed = -1;
    return false;
}

bool ST::Window::inputReleased(ST_INPUT input){
    switch (input) {
    case ST::ST_INPUT_UP:
        if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_RELEASE) {
            return true;
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_UP) == GLFW_RELEASE) {
            return true;
        }
        break;
    case ST::ST_INPUT_DOWN:
        if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_RELEASE) {
            return true;
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_DOWN) == GLFW_RELEASE) {
            return true;
        }
        break;
    case ST::ST_INPUT_RIGHT:
        if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_RELEASE) {
            return true;
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
            return true;
        }
        break;
    case ST::ST_INPUT_LEFT:
        if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_RELEASE) {
            return true;
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_LEFT) == GLFW_RELEASE) {
            return true;
        }
        break;
    case ST::ST_INPUT_FIRE:
        if (glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
            return true;
        }
        break;
    case ST::ST_INPUT_JUMP:
        if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_RELEASE) {
            return true;
        }
        break;
    case ST::ST_INPUT_ESCAPE:
        if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
            return true;
        }
        break;
    }
    //lastKeyPressed = -1;
    return false;
}

/*bool ST::Window::isDown(ST_INPUT input) {
    switch (input) {
    case ST::ST_INPUT_UP:
        if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS) {
            lastKeyPressed = input;
            return true;
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_UP) == GLFW_PRESS) {
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
    case ST::ST_INPUT_ESCAPE:
        if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            lastKeyPressed = input;
            return true;
        }
        break;
    }

    return false;
}*/

/*bool ST::Window::isUp(ST_INPUT input) {
    switch (input) {
    case ST::ST_INPUT_UP:
        if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_RELEASE) {
            if (lastKeyPressed == input) {
                lastKeyPressed = -1;
                return true;
            }
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_UP) == GLFW_RELEASE) {
            if (lastKeyPressed == input) {
                lastKeyPressed = -1;
                return true;
            }
        }
        break;
    case ST::ST_INPUT_DOWN:
        if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_RELEASE) {
            if (lastKeyPressed == input) {
                lastKeyPressed = -1;
                return true;
            }
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_DOWN) == GLFW_RELEASE) {
            if (lastKeyPressed == input) {
                lastKeyPressed = -1;
                return true;
            }
        }
        break;
    case ST::ST_INPUT_RIGHT:
        if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_RELEASE) {
            if (lastKeyPressed == input) {
                lastKeyPressed = -1;
                return true;
            }
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_RIGHT) == GLFW_RELEASE) {
            if (lastKeyPressed == input) {
                lastKeyPressed = -1;
                return true;
            }
        }
        break;
    case ST::ST_INPUT_LEFT:
        if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_RELEASE) {
            if (lastKeyPressed == input) {
                lastKeyPressed = -1;
                return true;
            }
        }
        else if (glfwGetKey(glWindow, GLFW_KEY_LEFT) == GLFW_RELEASE) {
            if (lastKeyPressed == input) {
                lastKeyPressed = -1;
                return true;
            }
        }
        break;
    case ST::ST_INPUT_FIRE:
        if (glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
            if (lastMousePressed == input) {
                lastMousePressed = -1;
                return true;
            }
        }
        break;
    case ST::ST_INPUT_JUMP:
        if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_RELEASE) {
            if (lastKeyPressed == input) {
                lastKeyPressed = -1;
                return true;
            }
        }
        break;
    case ST::ST_INPUT_ESCAPE:
        if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_RELEASE) {
            if (lastKeyPressed == input) {
                lastKeyPressed = -1;
                return true;
            }
        }
        break;
    }

    return false;
}
*/

//bool ST::Window::isDown(const char key){
//    if (glfwGetKey(glWindow, key) == GLFW_PRESS) {
//        lastKeyPressed = key;
//        return true;
//    }
//}

//bool ST::Window::isPressed(const char key){
//    if (glfwGetKey(glWindow, key) == GLFW_PRESS) {
//        if (lastKeyPressed != key) {
//            lastKeyPressed = key;
//            return true;
//        }
//        return false;
//    }
//     
//    return false;
//}

bool ST::Window::inputPressed(const char key) {
    return (glfwGetKey(glWindow, key) == GLFW_PRESS);
}

bool ST::Window::inputReleased(const char key) {
    return (glfwGetKey(glWindow, key) == GLFW_RELEASE);
}

//bool ST::Window::isUp(const char key){
//    if (glfwGetKey(glWindow, key) == GLFW_RELEASE) {
//        if (lastKeyPressed == key) {
//            lastKeyPressed = -1;
//            return true;
//        }
//    }
//    return false;
//}

double ST::Window::mousePosX(){
    glfwGetCursorPos(glWindow, &mouseX, &mouseY);
    return mouseX;
}

double ST::Window::mousePosY(){
    glfwGetCursorPos(glWindow, &mouseX, &mouseY);
    return mouseY;
}

bool ST::Window::isOpen() const{
    if (glWindow == NULL) { return false; }
    return !glfwWindowShouldClose(glWindow);
}

void ST::Window::ColorBg(float c[4]) {
    for (int i = 0; i < 4; i++){
        color[i] = c[i];
    }
}

void ST::Window::ColorBg(float r, float g, float b, float a){
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

float ST::Window::DeltaTime() const{
    return ((float)deltaTime)/1000;
}

double ST::Window::FPS(const float time) const{
    return (1.0f / time);// * 1000.0f;
}

ST::Window::~Window(){
    glfwTerminate();
}
