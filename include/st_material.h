#ifndef _SPACE_TURTLE_MATERIAL_H_
#define _SPACE_TURTLE_MATERIAL_H_ 1

#include <glm.hpp>
#include <st_program.h>
#include <st_texture.h>
#include <memory>

namespace ST {

	class Material{
	public:
		Material();

		void setColor(glm::vec3 rgb);
		void setColor(float r, float g, float b);
		const glm::vec3 getColor();

		const ST::Program* getProgram();
		void setProgram(std::shared_ptr<ST::Program>& p);

		ST::Texture* getAlbedo();
		void setTexture_Albedo(ST::Texture* texAlbedo);

		~Material();
	
		bool haveAlbedo;
	private:
		ST::Texture* albedo;

		glm::vec3 color;
		std::shared_ptr<ST::Program> program;
	};
}

#endif