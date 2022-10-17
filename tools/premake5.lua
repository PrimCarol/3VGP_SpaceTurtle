
ROOT = path.getabsolute("./../")
            -- folders -> SpaceTurtle/tools/premake5.lua

solution("3VGP_SpaceTurtle" .. _ACTION)
    location( ROOT .. "/build/")
    targetdir(ROOT .. "/bin/")
    language "C++"
    startproject "SpaceTurtle"


    configurations { "Debug", "Release" }
    platforms      { "x64" }


    filter "configurations:Debug"    defines { "DEBUG" }  symbols  "On" kind "ConsoleApp" debugdir(ROOT.."/bin")
    filter "configurations:Release"  defines { "NDEBUG" } optimize "On" kind "WindowedApp" debugdir(ROOT.."/bin")
    
    filter { "platforms:*64" } architecture "x64"

    filter {}

    -- Dependiendo de que version de Visual utilice. (Para el GLFW)
    visualVersion = "UNDEFINED"
    if _ACTION == "vs2019" then
        visualVersion = "vc2019"
    elseif _ACTION == "vs2022" then
        visualVersion = "vc2022"        
    end


    project "SpaceTurtle"
        location(ROOT .. "/build/" .. _ACTION)
        entrypoint "mainCRTStartup"
        --ignoredefaultlibraries { "LIBCMT" }


        -- Donde estan los includes
        includedirs{
            --Personal
            "../include",

            --Math Library
            "../deps/glm",
            "../deps/glm/gtx",
            "../deps/glm/gtc",
            
            --GLFW
            "../deps/glfw-3.3.8.bin.WIN64/include",

            --OpenGl - GLAD
            "../deps/OpenGL",

            --ImGui
            "../deps/imgui-docking",
            "../deps/imgui-docking/backends",

            -- MiniAudio
            "../deps/MiniAudio",
        }

        -- Los ficheros a incluir en la solucion
        files {
            "../include/*.h",
            "../src/*.cc",

            -- Includes a mano.
            --"../include/st_engine.h",
            --"../include/st_node.h",
            --"../include/st_emptyobj.h",
            --"../include/st_drawobj.h",
            --"../include/st_window.h",
            --"../include/st_program.h",
            --"../include/st_shader.h",
            --"../include/st_mesh.h",


            --"../src/st_node.cc",
            --"../src/st_emptyobj.cc",
            --"../src/st_drawobj.cc",
            --"../src/st_window.cc",
            --"../src/st_program.cc",
            --"../src/st_shader.cc",
            --"../src/st_mesh.cc",
            --"../src/main.cc",



            "../deps/imgui-docking/*.cpp",
            "../deps/imgui-docking/backends/imgui_impl_glfw.cpp",
            "../deps/imgui-docking/backends/imgui_impl_opengl3.cpp",

            "../deps/OpenGL/glad.c",
        }  

        -- Donde estan las librerias
        libdirs {
            "../deps/glfw-3.3.8.bin.WIN64/lib-"..visualVersion,
        }

        -- Librerias standard y .lib
        links {
            "glfw3_mt", -- Version Multithreading
            "opengl32",
        }

        filter  {"Debug","x64"}
            --targetdir (ROOT .. "bin/Debug/x64")
            targetdir(ROOT .. "/bin/Debug/")
            objdir(ROOT .. "/build/SpaceTurtle/Debug/" )
            targetsuffix "_d"
        filter  {"Release","x64"}
            --targetdir (ROOT .. "bin/Release/x64")
            targetdir(ROOT .. "/bin/Release/")
            objdir(ROOT .. "/build/SpaceTurtle/Release/" )