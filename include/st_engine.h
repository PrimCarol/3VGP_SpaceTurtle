#ifndef _SPACE_TURTLE_ENGINE_H_
#define _SPACE_TURTLE_ENGINE_H_ 1

#include <iostream>
#include <sys/stat.h>
#include <assert.h>

#include <st_window.h>
#include <st_gameobj_manager.h>
#include <st_rendertarget.h>

#include <components/st_transform.h>
#include <components/st_hierarchy.h>
#include <components/st_name.h>
#include <components/st_render.h>
#include <components/st_collider.h>
#include <components/st_light.h>
#include <components/st_camera.h>

#include <systems/st_system_transform.h>
#include <systems/st_system_render.h>
#include <systems/st_system_light.h>
#include <systems/st_system_picking.h>
#include <systems/st_system_hud.h>
#include <systems/st_system_camera.h>
#include <systems/st_system_assets.h>

/*! \mainpage SpaceTurtle
 *
 * \section features_sec Project Features
 * 
 * - Entity Component System (ECS) \n
 * - Obj Instancing \n
 * - Hierarchy Transformations \n
 * - Load OBJ \n
 * - Lights (Directional, Point & Spot) \n
 * - ShadowMapping (Directional and Spotlight) \n
 * - Load Textures \n
 * - Texture Atlas \n
 * - Skybox/CubeMap \n
 * - Material Configuration \n
 * - Translucent \n
 * - Picking System \n
 * - Deferred Pipeline \n
 * - PBR Materials \n
 * - Normal Mapping \n
 * - Assets System \n
 * - SSAO \n
 * 
 * \section prereq_sec Prerequisites
 *
 * - Visual Studio 2019/2022 \n
 *
 * \section howto_sec Generate Visual Solution
 *
 * Thanks to the use of Premake you only have to do the following
 * 
 * - Run the file that you will find in -> ./tools/compile_vs[version].bat \n
 * - Then open the visual solution that has been created in -> ./build/3VGP_SpaceTurtlevs[version].sln \n
 *
 * \section libraries_sec Libraries Used
 *  · GLFW (https://github.com/glfw/glfw) \n
 *  · Glad (https://github.com/Dav1dde/glad) \n
 *  · ImGui (https://github.com/ocornut/imgui) \n
 *  · ImGuizmo (https://github.com/CedricGuillemet/ImGuizmo) \n
 *  · MiniAudio (https://github.com/mackron/miniaudio) \n
 *  · STB (https://github.com/nothings/stb) \n
 *  · TyniObj (https://github.com/tinyobjloader/tinyobjloader) \n
 *  · FastNoiseLite (https://github.com/Auburn/FastNoiseLite) \n
 */

namespace ST {

	class Engine{
	public:
	
		/* Get a random float value between the min and max. */
		static const float getRandom(float min, float max);
		/* Read the file in the path you pass */
		static const unsigned char* readFile(const char* filename);

		static void createEmptyObj(ST::GameObj_Manager& gm);
		static void createTriangle(ST::GameObj_Manager& gm);
		static void createQuad(ST::GameObj_Manager& gm);
		static void createCircle(ST::GameObj_Manager& gm);
		static void createCube(ST::GameObj_Manager& gm);
		static void createSphere(ST::GameObj_Manager& gm);

		static void createDirectLight(ST::GameObj_Manager& gm);
		static void createPointLight(ST::GameObj_Manager& gm);
		static void createSpotLight(ST::GameObj_Manager& gm);

		static void createCamera(ST::GameObj_Manager& gm);
	private:
		Engine();
		~Engine();
	};
}

#endif