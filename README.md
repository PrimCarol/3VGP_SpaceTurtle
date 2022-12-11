<h1 align="center"> Space Turtle </h1>
<h4 align="center"> An engine built from scratch. </h4>

![Turtle](https://github.com/PrimCarol/3VGP_SpaceTurtle/blob/main/others/icon.png)

<h2>Implemented things</h2>
  · GLFW (https://github.com/glfw/glfw)<br>
  · Glad (https://github.com/Dav1dde/glad)<br>
  · ImGui (https://github.com/ocornut/imgui)<br>
  · MiniAudio (https://github.com/mackron/miniaudio)<br>
  · TyniObj (https://github.com/tinyobjloader/tinyobjloader)<br>
</p>


<h2>Examples</h2>

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
