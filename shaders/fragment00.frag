#version 330

out vec4 FragColor;

// Camera
uniform vec3 u_view_pos;

in vec4 color;
in vec3 normals;
in vec2 texCoords;

in vec3 modelPosition;

// Texture
uniform bool u_haveAlbedo;
uniform sampler2D u_tex_Albedo;


void main() { 
	
	vec3 normal_ = normalize(normals);
	vec4 TextureColor = texture(u_tex_Albedo, texCoords);

	//---------- Light ---------
	//float material_shine = 64.0;

	vec3 light_dir = normalize(vec3(-1.0, -1.0, 0.5));
	vec3 light_color = vec3(1.0,1.0,1.0);
	vec3 ambient_color = vec3(color.x * 0.1, color.y * 0.1, color.z * 0.1);

	//diffuse
	float diffuse_light = max(dot(-light_dir, normal_), 0.0);

	//specular
	int material_shine = 64; // <---- uniform
	vec3 light_bounce = reflect(light_dir, normal_);
	vec3 camera_dir = normalize(modelPosition - u_view_pos);
	float specular_light = pow(max(dot(-light_bounce, camera_dir), 0.0), material_shine);

	vec4 specular_color = vec4(1,1,1,1);

	// ---- Color Base/Textura -----	
	vec4 albedo;
	if(u_haveAlbedo){ albedo = (TextureColor * color); }
	else { albedo = color; }

	// ---- Resultado -----	
	//FragColor = vec4((((albedo * diffuse_light) + (specular_light * specular_color)) * light_color) + ambient_color, 1.0);
	
	//FragColor = vec4((ambient_color * albedo) + (light_color * diffuse_light * albedo) + (specular_color * specular_light * albedo), 1.0);
	vec4 a = (vec4(ambient_color, 1.0) * albedo);
	vec4 b = (vec4(light_color, 1.0) * diffuse_light * albedo);
	vec4 c = (specular_color * specular_light * albedo);
	FragColor =  a + b + c;
	
	//FragColor = vec4(normals, 1.0);
	
	//if(u_haveAlbedo){ FragColor = texture(u_tex_Albedo, texCoords) * color; }
	//else { FragColor = color; }
	
}