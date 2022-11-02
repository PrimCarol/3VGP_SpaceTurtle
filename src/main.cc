#include <stdio.h>
#include <stdlib.h>

#include <random.hpp>

#include <st_window.h>
//#include <st_gameobj.h>
#include <st_gameobj_manager.h>

int main() {
	ST::Window w;
	w.ColorBg(0.2f, 0.2f, 0.2f);

	srand(time(0));
	// ----------------------------------------------------------------
	//ST::GameObj obj1;
	//ST::TransformComponent trans;
	//obj1.addComponent(&trans);
	//ST::MeshComponent mesh;
	//obj1.addComponent(&mesh);
	//
	//printf("Obj1 Components -> %d \n", obj1.numComponents());

	//auto a = obj1.getComponent<ST::TransformComponent>();

	ST::GameObj_Manager gm;
	std::vector<ST::ComponentId> c;
	c.push_back(gm.createMeshComponent());
	c.push_back(gm.createMaterialComponent());

	if (gm.createGameObj(c)) {
		printf("Obj Creado\n");
		printf("Tiene los Componentes de: \n");
		for (int i = 0; i < c.size(); i++){
			
			switch (c[i].type){
			case ST::kComp_Trans:
				printf("Transform\n");
				break;
			case ST::kComp_Mesh:
				printf("Mesh\n");
				break;
			case ST::kComp_Material:
				printf("Material\n");
				break;
			}
		}
	}

	// --------------------------

	float timerForInput = 0.0f;
	float timerForSomething = 0.0f;
	while (w.isOpen() && !w.isPressed(ST::ST_INPUT_ESCAPE)) {
		
		w.Clear();

		// ----------------------------------------------------------------
		timerForInput += w.DeltaTime();
		if (timerForInput >= 1.0f/60) {
			//printf("Input\n");


			timerForInput = 0.0f;
		}


		timerForSomething += w.DeltaTime();
		if (timerForSomething >= 1.0f/10) {
			//printf("AI\n");


			timerForSomething = 0.0f;
		}

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