
ROOT = path.getabsolute("./../")
            -- folders -> SpaceTurtle/tools/premake5.lua

solution("3VGP_SpaceTurtle" .. _ACTION)
    location( ROOT .. "/build/")
    targetdir(ROOT .. "/bin/")
    language "C++"
    startproject "SpaceTurtle"


    configurations { "Debug", "Release" }
    platforms      { "x64" }

    filter "configurations:Debug"    defines { "DEBUG" }  symbols  "On" kind "ConsoleApp"
    filter "configurations:Release"  defines { "NDEBUG" } optimize "On" kind "WindowedApp"
    
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

        -- Donde estan los includes
        includedirs{
            --Personal
            --path.join(ROOT, "./include"),
            "../include",
            
            --GLFW
            --path.join(ROOT, "./deps/glfw-3.3.8.bin.WIN64/include"),
            "../deps/glfw-3.3.8.bin.WIN64/include",

            --OpenGl - GLAD
            "../deps/OpenGL",

            --ImGui
            --path.join(ROOT, "./deps/imgui-docking"),
            --path.join(ROOT, "./deps/imgui-docking/backends")
            --"../deps/imgui-docking",
            --"../deps/imgui-docking/backends"
        }

        -- Los ficheros a incluir en la solucion
        files {
            --path.join(ROOT, "./include/*.h"),
            --path.join(ROOT, "./src/*.cc")
            "../include/*.h",
            "../src/*.cc",

            "../deps/OpenGL/glad.c"
        }

        --ignoredefaultlibraries { "LIBCMT" }

        -- Donde estan las librerias
        libdirs {
            --path.join(ROOT, "./deps/glfw-3.3.8.bin.WIN64/lib-"..visualVersion)
            "../deps/glfw-3.3.8.bin.WIN64/lib-"..visualVersion
        }

        -- Librerias standard y .lib
        links {
            "glfw3_mt",
            "opengl32",
            --"glew32",
            --"glew32s",
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