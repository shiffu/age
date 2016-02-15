#pragma once

#include <string>

#include <GL/glew.h>

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
		void setUniform(const std::string& name, int value);
		void setUniform(const std::string& name, float value);

		void bind();
		void unbind();

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