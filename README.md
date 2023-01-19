<h1 align="center"> 🐢 Space Turtle 🐢</h1>

<p align="center"><img src="https://github.com/PrimCarol/3VGP_SpaceTurtle/blob/main/others/icon.png" width="250" height="250"></p>
<p align="center">My personal Engine from scratch with C++ and OpenGl.</p>
<p align="center">© 2023 Pere Prim Carol</p>

<h2>🔶 Implemented things</h2>

  - Entity Component System (ECS)<br>
  - Hierarchy Transformations <br>
  - Load OBJ<br>
  - Camera Movement (FPS style)<br>
  - Load Textures<br>
  - Material Configuration<br>
  - Picking System<br>

<h2>🔶 Prerequisites</h2>
Visual Studio 2019/2022

<h2>🔶 Generate Visual Solution</h2>

Thanks to the use of Premake you only have to do the following
- Run the file that you will find in -> ./tools/compile_vs[version].bat <br>
- Then open the visual solution that has been created in -> ./build/3VGP_SpaceTurtlevs[version].sln <br>

<h2>🔶 Build</h2>
<p>Inside the solution, press 'F5' to build and run.</p>
<img src="https://github.com/PrimCarol/3VGP_SpaceTurtle/blob/main/others/screenshots/Demo_00.png">

<h2>🔶 Examples</h2>
<h4>Render Window</h4>

```cpp
#include <st_engine.h>

int main() {
 ST::Window w;
 w.ColorBg(0.2f, 0.2f, 0.2f); // Optional

 // ----------------------------------------------------------------

 // Here Your Awesome Start Code!

 // --------------------------

 while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
	 w.Clear();

	 // ----------------------------------------------------------------

	 // Here Your Awesome Loop Code!

	 // ----------------------------

	 w.Render();	
  }
  return 0;
 }
  
```
<h2>🔶 Libraries Used</h2>

<p>
  · GLFW (https://github.com/glfw/glfw)<br>
  · Glad (https://github.com/Dav1dde/glad)<br>
  · ImGui (https://github.com/ocornut/imgui)<br>
  · MiniAudio (https://github.com/mackron/miniaudio)<br>
  · STB (https://github.com/nothings/stb)<br>
  · TyniObj (https://github.com/tinyobjloader/tinyobjloader)<br>
</p>
