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
        
        glfwSetWindowUserPointer(glWindow, this);
        glfwSetScrollCallback(glWindow, scroll_callback);

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

    setImGuiTheme();

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

        glfwSetWindowUserPointer(glWindow, this);
        glfwSetScrollCallback(glWindow, scroll_callback);

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

    ImGui_ImplGlfw_InitForOpenGL(glWindow, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    setImGuiTheme();

    printf("-----------------------------------------\n");
    printf("------------- Space Turtle --------------\n");
    printf("--------- By: Pere Prim Carol -----------\n");
    printf("-----------------------------------------\n");
}

ST::Window::Window(const Window& o){}

void ST::Window::scroll_callback(GLFWwindow* w, double x, double y){
    ST::Window* instance = static_cast<ST::Window*>(glfwGetWindowUserPointer(w));
    instance->scroll_callback(x, y);
}

void ST::Window::scroll_callback(double x, double y){
    mouseWheelX_ = x;
    mouseWheelY_ = y;
}

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
    mouseWheelX_ = 0.0f;
    mouseWheelY_ = 0.0f;

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
    ImGui::DockSpaceOverViewport(); // <----- Modificado
}

void ST::Window::setImGuiTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.08f, 0.50f, 0.72f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.39f);
    style.Colors[ImGuiCol_Separator] = style.Colors[ImGuiCol_Border];
    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41f, 0.42f, 0.44f, 1.00f);
    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.29f, 0.30f, 0.31f, 0.67f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    style.Colors[ImGuiCol_Tab] = ImVec4(0.08f, 0.08f, 0.09f, 0.83f);
    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.33f, 0.34f, 0.36f, 0.83f);
    style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.24f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.09f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
    style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.26f, 0.59f, 0.98f, 0.70f);
    style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.11f, 0.64f, 0.92f, 1.00f);
    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    style.GrabRounding = style.FrameRounding = 2.3f;
    /*ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(8.00f, 8.00f);
    style.FramePadding = ImVec2(5.00f, 2.00f);
    style.CellPadding = ImVec2(6.00f, 6.00f);
    style.ItemSpacing = ImVec2(6.00f, 6.00f);
    style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
    style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
    style.IndentSpacing = 25;
    style.ScrollbarSize = 15;
    style.GrabMinSize = 10;
    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 1;
    style.TabBorderSize = 1;
    style.WindowRounding = 7;
    style.ChildRounding = 4;
    style.FrameRounding = 3;
    style.PopupRounding = 4;
    style.ScrollbarRounding = 9;
    style.GrabRounding = 3;
    style.LogSliderDeadzone = 4;
    style.TabRounding = 4;*/
}

int ST::Window::getWindowsHeight() const{
    return window_Height_;
}

int ST::Window::getWindowsWidth() const{
    return window_Width_;
}

bool ST::Window::inputPressed(ST_INPUT input){

    auto& io = ImGui::GetIO();
    if ((io.WantCaptureMouse) || io.WantTextInput) {
        return false;
    }
    
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
    auto& io = ImGui::GetIO();
    if (io.WantCaptureMouse || io.WantTextInput) {
        return false;
    }
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
    return mouseX;
}

double ST::Window::mousePosY() const{
    return mouseY;
}

double ST::Window::mouseWheelX() const {
    return mouseWheelX_;
}

double ST::Window::mouseWheelY() const {
    return mouseWheelY_;
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
    glfwDestroyWindow(glWindow);
}
