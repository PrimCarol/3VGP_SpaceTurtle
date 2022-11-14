
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
            -- Personal
            "../include",
            "../include/components",

            -- Math Library
            "../deps/glm",
            "../deps/glm/gtx",
            "../deps/glm/gtc",
            
            -- GLFW
            "../deps/glfw-3.3.8.bin.WIN64/include",

            -- OpenGl - GLAD
            "../deps/OpenGL",

            -- ImGui
            "../deps/imgui-docking",
            "../deps/imgui-docking/backends",

            -- MiniAudio
            "../deps/MiniAudio",
        }

        -- Los ficheros a incluir en la solucion
        files {
            "../include/*.h",
            "../include/components/*.h",
            "../src/*.cc",
            "../src/components/*.cc",

            -- ImGui
            "../deps/imgui-docking/*.cpp",
            "../deps/imgui-docking/backends/imgui_impl_glfw.cpp",
            "../deps/imgui-docking/backends/imgui_impl_opengl3.cpp",

            -- OpenGl - GLAD
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
            links {"glfw3d"}
            targetdir(ROOT .. "/bin/Debug/")
            objdir(ROOT .. "/build/SpaceTurtle/Debug/" )
            targetsuffix "_d"
        filter  {"Release","x64"}
            --targetdir (ROOT .. "bin/Release/x64")
            targetdir(ROOT .. "/bin/Release/")
            objdir(ROOT .. "/build/SpaceTurtle/Release/" )