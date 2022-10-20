#include <stdio.h>
#include <stdlib.h>

#include <random.hpp>

#include <st_window.h>
#include <st_drawobj.h>

void RandomPos(ST::DrawObj obj[], int size) {
	for (int i = 0; i < size; i++){
		obj[i].setPosition({glm::linearRand(-1.0f,1.0f), glm::linearRand(-1.0f,1.0f), 1.0f});
		obj[i].setScale({ glm::linearRand(0.01f,0.3f), glm::linearRand(0.01f,0.3f), 1.0f });
	}
}

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f);

	// ----------------------------------------------------------------
	srand(time(0));

	ST::DrawObj a;
	ST::Triangle geometry;
	//ST::Material mat;
	//ST::Material::Settings settings;
	a.setMesh(&geometry);
	//a.setMaterial(&mat);
	//a.getMaterial()->setSettings(&settings);
	a.setScale({ 0.1f, 0.1f, 0.1f });
	//a.getMaterial()->getSettings()->setColor({1.0f, 0.7f, 0.9f});
	a.setName("A");

	const int howManyObjs = 500;
	ST::DrawObj b[howManyObjs];
	//ST::Material::Settings settings_b[howManyObjs];
	ST::Circle circle;
	ST::Quad quad;
	for (int i = 0; i < howManyObjs; i++){
		int geometry = glm::linearRand(0,1);
		switch (geometry){
		case 0: b[i].setMesh(&circle); break;
		case 1: b[i].setMesh(&quad); break;
		}
		
		//b[i].setMaterial(&mat);
		//b[i].getMaterial()->setSettings(&settings_b[i]);
		//b[i].getMaterial()->getSettings()->setColor({ glm::linearRand(0.0f,1.0f), glm::linearRand(0.0f,1.0f), glm::linearRand(0.0f,1.0f) });
		b[i].getMaterial()->setColor({glm::linearRand(0.0f,1.0f), glm::linearRand(0.0f,1.0f), glm::linearRand(0.0f,1.0f)});
	}
	RandomPos(b,howManyObjs);

	a.addChild(&b[0]);
	printf("Parent-> %s \n", b[0].getParent()->getName());
	// ----------------------------------------------------------------

	float timerForInput = 0.0f;
	float timerForSomething = 0.0f;
	while (w.isOpen() && !w.isPressed(ST::ST_INPUT_ESCAPE)) {
		
		w.Clear();

		timerForInput += w.DeltaTime();
		if (timerForInput >= 1.0f/60) {
			//printf("Input FPS: %d \n", (int)w.FPS(timerForInput));
			printf("Input\n");
			if (w.isDown(ST::ST_INPUT_RIGHT)) { a.RotateZ({-8.0f * w.DeltaTime()}); }
			if (w.isDown(ST::ST_INPUT_LEFT)) { a.RotateZ({ 8.0f * w.DeltaTime() }); }
			if (w.isDown(ST::ST_INPUT_UP)) { a.Move({ 0.0f, 20.0f * w.DeltaTime(),0.0f }); }
			if (w.isDown(ST::ST_INPUT_DOWN)) { a.Move({ 0.0f, -20.0f * w.DeltaTime(),0.0f }); }
			timerForInput = 0.0f;
		}

		// ----------------------------------------------------------------
		//printf("Normal FPS: %d\n", (int)w.FPS(w.DeltaTime()));

		for (int i = 0; i < howManyObjs; i++){
			b[i].draw();
		}

		a.draw();
		//printf("NumChilds: %d \n", a.getChildCount());
		if (w.isPressed('P')) {
			printf("Parent-> %s \n", b[0].getParent()->getName());
			printf("NumChilds: %d \n", a.getChildCount());
		}
		
		timerForSomething += w.DeltaTime();
		if (timerForSomething >= 1.0f/10) {
			printf("AI\n");
			timerForSomething = 0.0f;
		}

		w.initImGuiWindow("Ventana Guay");
		if (w.buttonImGui("ReGenerate")) {
			RandomPos(b,howManyObjs);
		}
		w.endImGuiWindow();
		// ----------------------------------------------------------------

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