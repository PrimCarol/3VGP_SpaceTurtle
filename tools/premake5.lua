solution("3VGP_SpaceTurtle" .. _ACTION)
    ROOT = path.getabsolute("./../")
    -- folders -> SpaceTurtle/tools/premake5.lua

    location( ROOT .. "/build/")
    cppdialect "C++17"
    startproject "Test"


    configurations { "Debug", "Release" }
    platforms      { "x64" }


    -- Dependiendo de que version de Visual utilice. (Para el GLFW)
    visualVersion = "UNDEFINED"
    if _ACTION == "vs2019" then
        visualVersion = "vc2019"
    elseif _ACTION == "vs2022" then
        visualVersion = "vc2022"        
    end


    project "SpaceTurtle"

        targetdir(ROOT .. "ST_Engine/")

        filter "configurations:Debug"    defines { "DEBUG" }  symbols  "On" kind "StaticLib" debugdir(ROOT.."/bin")
        filter "configurations:Release"  defines { "NDEBUG" } optimize "On" kind "StaticLib" debugdir(ROOT.."/bin")
        
        filter { "platforms:*64" } architecture "x64"

        filter {}

        location(ROOT .. "/build/" .. _ACTION)
        --entrypoint "mainCRTStartup"
        ignoredefaultlibraries { "LIBCMT" }


        -- Donde estan los includes
        includedirs{
            -- Personal
            "../include",
            "../include/components",
            "../include/systems",

            -- STD Extras
            "../deps/stb_extras",

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

            -- TinyObj
            "../deps/tiny_obj/include",

            -- MiniAudio
            "../deps/MiniAudio",
        }

        -- Los ficheros a incluir en la solucion
        files {
            "../include/*.h",
            "../include/components/*.h",
            "../include/systems/*.h",
            "../src/*.cc",
            "../src/components/*.cc",
            "../src/systems/*.cc",

            -- Shaders
            "../shaders/**",

            -- ImGui
            "../deps/tiny_obj/src/tiny_obj_loader.cc",

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

    --    filter  {"Debug","x64"}
    --        --targetdir (ROOT .. "bin/Debug/x64")
    --        links {"glfw3d"}
    --        targetdir(ROOT .. "/bin/Debug/")
    --        objdir(ROOT .. "/build/SpaceTurtle/Debug/" )
    --        targetsuffix "_d"
    --    filter  {"Release","x64"}
    --        --targetdir (ROOT .. "bin/Release/x64")
    --        targetdir(ROOT .. "/bin/Release/")
    --        objdir(ROOT .. "/build/SpaceTurtle/Release/" )


    project "Test"
    
        targetdir(ROOT .. "/bin/")
    
        filter "configurations:Debug"    defines { "DEBUG" }  symbols  "On" kind "ConsoleApp" debugdir(ROOT.."/bin")
        filter "configurations:Release"  defines { "NDEBUG" } optimize "On" kind "WindowedApp" debugdir(ROOT.."/bin")
        
        filter { "platforms:*64" } architecture "x64"
    
        filter {}
    
        location(ROOT .. "/build/" .. _ACTION)
        entrypoint "mainCRTStartup"
        ignoredefaultlibraries { "LIBCMT" }
    
        includedirs{
           -- Personal
            "../include",
            "../include/components",
            "../include/systems",
    
            -- STD Extras
            "../deps/stb_extras",
    
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
    
            -- TinyObj
            "../deps/tiny_obj/include",
    
            -- MiniAudio
            "../deps/MiniAudio",
        }
    
        --libdirs {
        --    "../deps/glfw-3.3.8.bin.WIN64/lib-"..visualVersion,
        --}
        --
        ---- Librerias standard y .lib
        --links {
        --    "glfw3_mt", -- Version Multithreading
        --    "opengl32",
        --}
    
        links {
            "SpaceTurtle",
        }
    
        files {
            "../demo/main.cc",
        }
    