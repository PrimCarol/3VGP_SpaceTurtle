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

		void setColor(glm::vec4 rgb);
		void setColor(float r, float g, float b, float a = 1.0f);
		const glm::vec4 getColor() const;

		const ST::Program* getProgram();
		void setProgram(std::shared_ptr<ST::Program>& p);

		ST::Texture* getAlbedo();
		void setTexture_Albedo(ST::Texture* texAlbedo);

		const glm::ivec2 getTexIndex() const;
		void setTexIndex(glm::ivec2 texIndex);

		~Material();
	
		bool haveAlbedo;
		bool translucent;
	private:
		ST::Texture* albedo;

		glm::ivec2 texIndex_;

		glm::vec4 color;
		std::shared_ptr<ST::Program> program;
	};
}

#endif