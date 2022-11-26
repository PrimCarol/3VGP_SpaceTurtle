#include <stdio.h>
#include <stdlib.h>

#include <imgui.h>

#include <st_engine.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f);

	srand(time(0));
	// ----------------------------------------------------------------
	
	// ************** Temporal ****************
	bool firtsMouse = true; 
	float lastX = 0.0f;
	float lastY = 0.0f;

	ST::GameObj* objSelected = nullptr;
	// ************** Temporal ****************

	printf("-----------------------------------------\n");
	printf("------------- Space Turtle --------------\n");
	printf("--------- By: Pere Prim Carol -----------\n");
	printf("-----------------------------------------\n");
	ST::GameObj_Manager gm;

	ST::Triangle triangle;
	ST::Quad quad;
	ST::Circle circle;
	ST::Cube cube;

	ST::Texture textureTest;
	textureTest.loadSource("../others/Cat_diffuse.jpg");
	
	// *************************** Test ***********************
	ST::Geometry geometry;
	geometry.loadFromFile("../others/cat.obj");
	// *************************** Test ***********************

	const int numObjs = 1;

	std::unique_ptr<ST::GameObj> obj1[numObjs];

	for (size_t i = 0; i < numObjs; i++){
		std::vector<ST::ComponentId> c1;
		c1.push_back(gm.createTransformComponent());
		c1.push_back(gm.createRenderComponent());

		obj1[i] = gm.createGameObj(c1);
		ST::TransformComponent* t = (ST::TransformComponent*)obj1[i]->getComponent(ST::kComp_Trans);
		if (t) {
			//float randomScale = ST::Engine::getRandom(0.01f, 0.1f);
			//t->setScale(glm::vec3(randomScale, randomScale, randomScale));
		
			float randomPosX = ST::Engine::getRandom(-10.0f, 10.0f);
			float randomPosY = ST::Engine::getRandom(-10.0f, 10.0f);
			float randomPosZ = ST::Engine::getRandom( 2.0f,  20.0f);
			t->setPosition(glm::vec3(randomPosX, randomPosY, randomPosZ));
		
		
			//float randomRotX = ST::Engine::getRandom(-3.14f, 3.14f);
			//t->RotateX(randomRotX);
			//float randomRotY = ST::Engine::getRandom(-3.14f, 3.14f);
			//t->RotateY(randomRotY);
			//float randomRotZ = ST::Engine::getRandom(-3.14f, 3.14f);
			//t->RotateZ(randomRotZ);
		
			//float randomVelY = getRandom(0.1f, 0.7f);
			//t->setVelocity(glm::vec3(0.0f, -randomVelY, 0.0f));
		}

		ST::RenderComponent* r = (ST::RenderComponent*)obj1[i]->getComponent(ST::kComp_Render);
		if (r) {

			int randomGeometry = rand() % 4;
			switch (randomGeometry){
			case 0:
				r->setMesh(&geometry);
				break;
			case 1:
				r->setMesh(&geometry);
				break;
			case 2:
				r->setMesh(&geometry);
				break;
			case 3:
				r->setMesh(&geometry);
				break;
			}

			//if ((rand() % 2) == 0) {
				r->material->setTexture_Albedo(&textureTest);
			//}
			//else
			//{
			//	float randomR = ST::Engine::getRandom(0.0f,1.0f);
			//	float randomG = ST::Engine::getRandom(0.0f,1.0f);
			//	float randomB = ST::Engine::getRandom(0.0f,1.0f);
			//	r->material->setColor(glm::vec3(randomR, randomG, randomB));
			//}

			//r->material->setColor(glm::vec3(0.0f, 0.0f, 0.0f));
		}
	}
	
	// --------------------------

	float timerForInput = 0.0f;
	float timerForSomething = 0.0f;
	while (w.isOpen() && !w.inputPressed(ST::ST_INPUT_ESCAPE)) {
		
		w.Clear();

		// ----------------------------------------------------------------
		timerForInput += w.DeltaTime();
		if (timerForInput >= 1.0f/60) {
			//printf("Input\n");

			glm::vec2 mousePos = {w.mousePosX(), w.mousePosY()};

			float extra_speed = 1.0f;
			if (w.inputPressed(ST::ST_INPUT_SHIFT)) {
				extra_speed = 4.0f;
			}

			if (w.inputPressed(ST::ST_INPUT_UP)) {
				//gm.cam_->transform_.Move(glm::vec3(0.0f, 0.0f, (-3.0f * w.DeltaTime()) * extra_speed));
				gm.cam_->transform_.Move(glm::vec3(0.0f, (3.0f * w.DeltaTime() * extra_speed), 0.0f) );
			}
			if (w.inputPressed(ST::ST_INPUT_DOWN)) {
				//gm.cam_->transform_.Move(glm::vec3(0.0f, 0.0f, (3.0f  * w.DeltaTime()) * extra_speed));
				gm.cam_->transform_.Move(glm::vec3(0.0f, (-3.0f * w.DeltaTime() * extra_speed), 0.0f));
			}
			if (w.inputPressed(ST::ST_INPUT_LEFT) ){
				gm.cam_->transform_.Move(glm::vec3((-3.0f * w.DeltaTime()) * extra_speed, 0.0f, 0.0f));
			}
			if (w.inputPressed(ST::ST_INPUT_RIGHT)) {
				gm.cam_->transform_.Move(glm::vec3((3.0f * w.DeltaTime()) * extra_speed, 0.0f, 0.0f));
			}

			/*
			if (firtsMouse) {
				lastX = mousePos.x;
				lastY = mousePos.y;
				firtsMouse = false;
			}

			float yoffset = mousePos.x - lastX;
			float xoffset = mousePos.y - lastY;
			lastX = mousePos.x;
			lastY = mousePos.y;

			if (w.inputPressed(ST::ST_INPUT_FIRE_SECOND)) {
				gm.cam_->transform_.RotateX(gm.cam_->transform_.getRotation().x - xoffset * 0.5f * w.DeltaTime());
				gm.cam_->transform_.RotateY(gm.cam_->transform_.getRotation().y - yoffset * 0.5f * w.DeltaTime());
			}
			*/
			// ---- Picking ---
			if (w.inputPressed(ST::ST_INPUT_FIRE)) {
				objSelected = gm.tryPickObj();
				//if (objSelected) {
				//	printf("Selecciono el objeto -> %d \n", objSelected->getID());
				//	ST::TransformComponent* t = (ST::TransformComponent*)objSelected->getComponent(ST::kComp_Trans);
				//	if (t) {
				//		printf("Esta en la posicion -> %f / %f / %f \n", t->getPosition().x, t->getPosition().y, t->getPosition().z);
				//	}
				//}
			}

			timerForInput = 0.0f;
		} // End Input Tick

		gm.UpdateTransforms();
		gm.UpdateRender();

		//timerForSomething += w.DeltaTime();
		//if (timerForSomething >= 1.0f/10) {
		//	//printf("Something\n");
		//
		//
		//	timerForSomething = 0.0f;
		//}


		// ---------------------------- ImGui -------------------------------
		ImGui::BeginMainMenuBar();
		ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 0.8f, 0.9f, 1.0f });
		ImGui::Text("| Space Turtle | by: Pere Prim / ESAT");
		ImGui::PopStyleColor();
		ImGui::SameLine(525);
		if (w.FPS(w.DeltaTime()) >= 50) {
			ImGui::PushStyleColor(ImGuiCol_Text, { 0, 1, 0, 1 });
		}
		else if (w.FPS(w.DeltaTime()) < 50 && w.FPS(w.DeltaTime()) >= 30) {
			ImGui::PushStyleColor(ImGuiCol_Text, { 1, 0.5f, 0, 1 });
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Text, { 1, 0, 0, 1 });
		}
		ImGui::Text("%d", (int)w.FPS(w.DeltaTime()));
		ImGui::PopStyleColor();
		ImGui::EndMainMenuBar();


		//ImGui::Begin("Info");
		//ImGui::Text("GameObjects: %d", gm.getGameObjNum() );
		//ImGui::Spacing();
		//ImGui::Text("UV->"); ImGui::SameLine(150); ImGui::Text("1,1");
		//ImGui::Image((void*)(intptr_t)textureTest.getID(), ImVec2(144, 144));
		//ImGui::Text("0,0");
		//ImGui::End();

		ImGui::Begin("Object Seleected");
		if (objSelected) {
			ImGui::Text("Obj ID -> %d ", objSelected->getID());
			ST::TransformComponent* trans = (ST::TransformComponent*)objSelected->getComponent(ST::kComp_Trans);
			if (trans) {
				//ImGui::BeginChild("Transform");
				ImGui::Text("---- Transform ----");
				glm::vec3 pos = trans->getPosition();
				ImGui::DragFloat3("##Pos", &pos.x, 0.5f);
				trans->setPosition(pos);
				glm::vec3 rot = trans->getRotation();
				ImGui::DragFloat3("##Rot", &rot.x, 0.05f);
				trans->RotateX(rot.x);
				trans->RotateY(rot.y);
				trans->RotateZ(rot.z);

				//ImGui::EndChild();
			}
			ST::RenderComponent* render = (ST::RenderComponent*)objSelected->getComponent(ST::kComp_Render);
			if (render) {
				//ImGui::BeginChild("Render");
				ImGui::Text("---- Render ----");
				
				ImGui::Text("- Color -");
				glm::vec3 c = render->material->getColor();
				ImGui::ColorEdit3("Color", &c.x);
				render->material->setColor(c);

				ImGui::Text("- Texture -");
				if (render->material->haveAlbedo) {
					ImGui::Image((void*)(intptr_t)render->material->getAlbedo()->getID(), ImVec2(144, 144));
				}
				else {
					ImGui::Text("None");
				}

				ImGui::Text("---- Mesh ----");
				ImGui::Text("Mesh: "); ImGui::SameLine();
				switch (render->mesh->meshType_){
				case ST::kMeshType_Triangle:
					ImGui::Text("Triangle");
					break;
				case ST::kMeshType_Quad:
					ImGui::Text("Quad");
					break;
				case ST::kMeshType_Circle:
					ImGui::Text("Circle");
					break;
				case ST::kMeshType_Cube:
					ImGui::Text("Cube");
					break;
				}

				//ImGui::EndChild();
			}
		}
		ImGui::End();

		// ----------------------------

		w.Render();	

	}

	return 0;
}

/* Main

int main{

	// Node -> EmptyObj - DrawObj

	EmptyObj Scene;

	DrawObj obj; // Como saber si es dibujable o no?
	Scene.setChild(obj);

	obj.setCustomShader(); // Que por defecto sera el basico.
	obj.setMesh(Mesh::Cube());


	while(w.Open()){


		// Camera.Render(scene);
		obj.getMesh().render();


	}

	return 0;
}


*/





/*
class Component {
	//void enable();
	//void disable();
	//bool isEnabled();
};

// Entity component system

// Entity tiene referencia a las listas de los componentes ??

// Shaders fuera de todo. <<<<-------------

class Entity{
public:
	Entity(std::initializer_list<Component>); 
	int getId() const;

	Entity& getParent();
	std::vector<Entity&> getChildrens();

	//addComponent(Component&&);
	//std::optional<Component> getComponent() const;


	~Entity();
private:
	int id;
};

class RenderComponent : public Component{

};

class TransformComponent : public Component {

};

class MaterialComponet : public Component {

};

// Crear un manager.

class EntityManager{
public:
	//EntityManager();
	//Se le puede pasar todos los componentes que se quieran
		template<typename... Patata>
	Entity& createEntity(Patata... patata);
	Entity &root();
	//~EntityManager();
private:
	std::vector<RenderComponent> renders;
	std::vector<TransformComponent> transforms;
	std::vector<MaterialComponet> materials;
};

template<typename... Patata>
Entity& EntityManager::createEntity(Patata... patata) {
	static_assert(true && ... && std::is_base_of<Component,Patata>::value); // En tiempo de compilacion    // SFINAE
	Entity e{ std::fordware<Patata>(patata)... };
}

void main() {
	EntityManager em;

	auto entity = em.createEntity(MaterialComponet{}, RenderComponent{});

	auto& tri_mat = triangle.GetComponent<TriangleMaterialComponent>();
	tri_mat.apply(program); // el program pide las variables que necesita, el material vera si se las puede dar.
	if(tri_mat.apply(program)){} // Para comprobar si el material le puede dar todos los valores que necesita el program.

	//program.apply(tri_mat); esta no; Seria como que el material se apunta para que este shader lo renderice.
	//program.renderList();

	triangle.render();
}
*/

/*
 // ----------------- Apuntes punteros ------------------
// Tener en cuenta, lectura o escritura, owner, tiempo de vida...
class A
{
public:
	void A1(int); // Hace una copia. No modifica al original
	void A2(int*); // No crea una copia.  Es el original, podiendo modificarlo. Normalmente usado como salida.
	void A3(int&); // No puede ser null. Salidas.
	void A3_1(int&&); // Solo puede recibir objetos temporales, y se lo puede quedar. Se llama MUR. Mas eficiente que una copia. Se mueve.
	void A4(const int*); // No es una copia. Te asegura que no la cambiara. Normalmente usado como entrada
	void A5(const int&); // 
	void A6(std::unique_ptr<int>); // No pueden existir 2 referencias de ese puntero. Tienes que hacer std::move(). Se mueve. Mejor este que el share.
	
	//A a;
	//auto myint = std::make_unique<int>()
	//auto myint_2 = std::move(myint);
	//a.A6(std::move(myint));
	
	void A7(std::shared_ptr<int>); // Crea una copia, crea un conteo de referencias. Mientras haya una copia activa, no se destruye. Hace que sea mas lento.
	void A8(std::weak_ptr<int>); // Parecido al shared pointer, pero no augmenta el contador. Dar acceso, pero no dar propiedad.
	
	//std::weak_ptr<int> R8(void);
	//auto weak_return = a.R8();
	//auto strong_return = weak_return.lock();
	

	//compile_shader(const std::string&)
	class Program
	{
	public:
		void add_shader(Shader&&);

		
		//Shader s;
		//program.add_shader(std::move(s));
		
	};


};

std::optional<float> divide_2_numeros(float, float);
auto res = divide_2_numeros(3.0f,0.0f);

// Puede ser null. puedes tener mas cuidado.

*/

/*
Recorrer un Template ...  

	?????
	(mi(packDeComponentes),...);

*/