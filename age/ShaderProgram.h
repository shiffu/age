#pragma once

#include <string>

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

#include <glm/glm.hpp>

namespace age {

	class ShaderProgram
	{
	public:
		ShaderProgram();
		~ShaderProgram();

		void compileShaders(const std::string& name);
		void linkProgram();

		void bindAttribute(const std::string& name);
		GLint getUniformLocation(const std::string& name);

		// Set Uniform methods
		void setUniform(const std::string& name, int value);
		void setUniform(const std::string& name, float value);
		void setUniform(const std::string& name, glm::mat4 value);

		void bind() const;
		void unbind() const;

	private:
		static const GLuint NB_SHADER_INDEX = 2;

		void compileShader(const std::string& filename, GLenum shaderType);

		GLuint m_program = 0;
		GLuint m_numShaders = 0;
		// Only Vertex and Fragment shaders are managed for the time being
		GLuint m_shaders[NB_SHADER_INDEX];
		unsigned short m_numAttributes = 0;
	};
}