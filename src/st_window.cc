#include "st_window.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <ImGuizmo.h>
#include <stdio.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

ST::Window::Window(){
    glWindow = NULL;
    for (int i = 0; i < 4; i++) { color[i] = 0.0f; }
    if (glfwInit()) {
        glWindow = glfwCreateWindow(1080, 720, "Space Turtle", NULL, NULL);
        
        GLFWimage images[1];
        images[0].pixels = stbi_load("../others/icon_nobg_big.png", &images[0].width, &images[0].height, 0, 4); 
        glfwSetWindowIcon(glWindow, 1, images);
        stbi_image_free(images[0].pixels);
        
        Focus();
    }

    window_Width_ = 1080;
    window_Height_ = 720;

    srand(time(NULL));

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

    printf("-----------------------------------------\n");
    printf("------------- Space Turtle --------------\n");
    printf("--------- By: Pere Prim Carol -----------\n");
    printf("-----------------------------------------\n");
}

ST::Window::Window(int width, int height){
    glWindow = NULL;
    for (int i = 0; i < 4; i++) { color[i] = 0.0f; }
    if (glfwInit()) {
        glWindow = glfwCreateWindow(width, height, "Space Turtle", NULL, NULL);

        GLFWimage images[1];
        images[0].pixels = stbi_load("../others/icon_nobg_big.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
        glfwSetWindowIcon(glWindow, 1, images);
        stbi_image_free(images[0].pixels);

        Focus();
    }

    window_Width_ = width;
    window_Height_ = height;

    srand(time(NULL));

    // Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();



    // Internal 
    //ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
    //ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_Dockspace); // Add empty node
    //ImGui::DockBuilderSetNodeSize(dockspace_id, dockspace_size);

    //ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
    //ImGuiID dock_id_prop = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, NULL, &dock_main_id);
    //ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, NULL, &dock_main_id);

    //ImGui::DockBuilderDockWindow("Log", dock_id_bottom);
    //ImGui::DockBuilderDockWindow("Properties", dock_id_prop);
    //ImGui::DockBuilderDockWindow("Mesh", dock_id_prop);
    //ImGui::DockBuilderDockWindow("Extra", dock_id_prop);
    //ImGui::DockBuilderFinish(dockspace_id);


    ImGui_ImplGlfw_InitForOpenGL(glWindow, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

ST::Window::Window(const Window& o){}

void ST::Window::Focus() const{
    glfwMakeContextCurrent(glWindow);

    //glfwSwapInterval(0);
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

    /*std::stringstream ss;
    ss << GAME_NAME << " " << VERSION << " [" << fps << " FPS]";

    glfwSetWindowTitle(pWindow, ss.str().c_str());*/

    //glfwSetWindowTitle(glWindow, "UWU");


    glfwSwapBuffers(glWindow);

    glfwGetCursorPos(glWindow, &mouseX, &mouseY);

    glfwPollEvents();
}

void ST::Window::Clear() const{
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ImGui
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

    // Para que toda la ventana tenga la posibilidad de hacer Dock
    ImGui::DockSpaceOverViewport();
}

int ST::Window::getWindowsHeight() const{
    return window_Height_;
}

int ST::Window::getWindowsWidth() const{
    return window_Width_;
}

bool ST::Window::inputPressed(ST_INPUT input){

    //auto& io = ImGui::GetIO();
    //if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
    //    return false;
    //}
    
    switch (input){
    case ST::ST_INPUT_UP:
        if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS) {
            return true;
        }else if (glfwGetKey(glWindow, GLFW_KEY_UP) == GLFW_PRESS) {
            return true;
        }
        break;
    case ST::ST_INPUT_DOWN:
        if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS) {
            return true;
        }else if (glfwGetKey(glWindow, GLFW_KEY_DOWN) == GLFW_PRESS) {
            return true;
        }
        break;
    case ST::ST_INPUT_RIGHT:
        if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS) {
            return true;
        }else if (glfwGetKey(glWindow, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            return true;
        }
        break;
    case ST::ST_INPUT_LEFT:
        if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS) {
            return true;
        }else if (glfwGetKey(glWindow, GLFW_KEY_LEFT) == GLFW_PRESS) {
            return true;
        }
        break;
    case ST::ST_INPUT_FIRE:
        if (glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
            return true;
        }
        break;
    case ST::ST_INPUT_FIRE_SECOND:
        if (glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
            return true;
        }
        break;
    case ST::ST_INPUT_JUMP:
        if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_PRESS) {
            return true;
        }
        break;
    case ST::ST_INPUT_SHIFT:
        if (glfwGetKey(glWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            return true;
        }
        break;
    case ST::ST_INPUT_ESCAPE:
        if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            return true;
        }
        break;
    }
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
    case ST::ST_INPUT_FIRE_SECOND:
        if (glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE) {
            return true;
        }
        break;
    case ST::ST_INPUT_JUMP:
        if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_RELEASE) {
            return true;
        }
        break;
    case ST::ST_INPUT_SHIFT:
        if (glfwGetKey(glWindow, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
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
    //auto& io = ImGui::GetIO();
    //if (io.WantCaptureMouse || io.WantCaptureKeyboard) {
    //    return false;
    //}
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

double ST::Window::mousePosX() const{
    //glfwGetCursorPos(glWindow, &mouseX, &mouseY);
    return mouseX;
}

double ST::Window::mousePosY() const{
    //glfwGetCursorPos(glWindow, &mouseX, &mouseY);
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
