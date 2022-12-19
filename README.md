<h1 align="center"><img src="https://github.com/PrimCarol/3VGP_SpaceTurtle/blob/main/others/icon.png" width="30" height="30"> Space Turtle <img src="https://github.com/PrimCarol/3VGP_SpaceTurtle/blob/main/others/icon.png" width="30" height="30"></h1>

<h2>Implemented things</h2>
  · GLFW (https://github.com/glfw/glfw)<br>
  · Glad (https://github.com/Dav1dde/glad)<br>
  · ImGui (https://github.com/ocornut/imgui)<br>
  · MiniAudio (https://github.com/mackron/miniaudio)<br>
  · TyniObj (https://github.com/tinyobjloader/tinyobjloader)<br>
</p>

<h2>Generate Visual Solution</h2>

```
click -> ./tools/compile_vs[version].bat
open -> ./build/3VGP_SpaceTurtlevs[version].sln
```

<h2>Examples</h2>
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
