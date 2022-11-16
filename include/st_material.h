#ifndef _SPACE_TURTLE_MATERIAL_H_
#define _SPACE_TURTLE_MATERIAL_H_ 1

#include <glm.hpp>
#include <st_program.h>
#include <st_texture.h>

namespace ST {

	class Material{
	public:
		Material();
		
		/*class Settings {
		public:
			Settings();

			void setColor(glm::vec3 rgb);
			const glm::vec3 getColor();

			~Settings();
			Settings(const Settings& o);
		private:
			glm::vec3 color;
		};*/

		//void setSettings(Settings* s);
		//Settings* getSettings() const;

		void setColor(glm::vec3 rgb);
		const glm::vec3 getColor();

		const ST::Program* getProgram();
		void setProgram(ST::Program* program);

		ST::Texture* getAlbedo();
		void setTexture_Albedo(ST::Texture* texAlbedo);

		~Material();
		Material(const Material& o);
	
		bool haveAlbedo;
	private:
		//Settings* settings_;

		ST::Texture* albedo;

		glm::vec3 color;
		ST::Program* program;
	};
}

#endif