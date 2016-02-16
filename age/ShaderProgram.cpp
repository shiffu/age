#include "ShaderProgram.h"

#include <iostream>
#include <fstream>
#include <vector>

#include "Error.h"

namespace age {

	ShaderProgram::ShaderProgram() {}

	ShaderProgram::~ShaderProgram() {}

	void ShaderProgram::compileShaders(const std::string& name) {
		m_program = glCreateProgram();

		//TODO: create a proper resource manager
		compileShader(name + ".vs", GL_VERTEX_SHADER);
		compileShader(name + ".fs", GL_FRAGMENT_SHADER);
	}

	void ShaderProgram::linkProgram() {

		// Attach our shaders to our program
		for (unsigned int i = 0; i < NB_SHADER_INDEX; i++) {
			glAttachShader(m_program, m_shaders[i]);
		}

		// Link our program
		glLinkProgram(m_program);

		GLint isLinked = 0;
		glGetProgramiv(m_program, GL_LINK_STATUS, (int *)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_program, maxLength, &maxLength, infoLog.data());

			// We don't need the program anymore.
			glDeleteProgram(m_program);

			// Don't leak shaders either.
			for (unsigned int i = 0; i < NB_SHADER_INDEX; i++) {
				glDeleteShader(m_shaders[i]);
			}

			fatalError("Failed to link the program: " + std::string(infoLog.data()));
		}

		// Always detach and delete shaders after a successful link.
		for (unsigned int i = 0; i < NB_SHADER_INDEX; i++) {
			glDetachShader(m_program, m_shaders[i]);
		}
		for (unsigned int i = 0; i < NB_SHADER_INDEX; i++) {
			glDeleteShader(m_shaders[i]);
		}
	}

	void ShaderProgram::compileShader(const std::string& filename, GLenum shaderType) {

		// Only Vertex and Fragment shaders are managed for the time being
		if (shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER) {
			fatalError("Only Vertex and Fragment shaders are managed");
		}

		GLuint shader = glCreateShader(shaderType);
		if (shader == 0) {
			fatalError("Unable to create shader: " + filename);
		}

		// Read the shader file
		std::ifstream shaderFile(filename);
		if (shaderFile.fail()) {
			perror(filename.c_str());
			fatalError("Failed to open " + filename);
		}

		std::string shaderSource = "";
		std::string line;
		while (std::getline(shaderFile, line)) {
			shaderSource += line + "\n";
		}
		shaderFile.close();

		const GLchar* stringData = shaderSource.c_str();
		const GLchar* const *shaderSrcPtr = (const GLchar* const *)&stringData;
		glShaderSource(shader, 1, shaderSrcPtr, nullptr);

		// Compile the shader and check for errors
		glCompileShader(shader);
		GLint success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE) {
			// Get message length
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// Get the log message
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog.data());

			// Don't leak the shader
			glDeleteShader(shader);

			fatalError("Failed to compile shader " + filename + ": " + std::string(infoLog.data()));
		}

		m_shaders[m_numShaders++] = shader;
	}

	void ShaderProgram::bindAttribute(const std::string& name) {
		glBindAttribLocation(m_program, m_numAttributes++, name.c_str());
	}

	GLint ShaderProgram::getUniformLocation(const std::string& name) {
		GLint location = glGetUniformLocation(m_program, name.c_str());
		if (location == GL_INVALID_INDEX) {
			fatalError("Uniform " + name + " not found in sharder program!");
		}

		return location;
	}

	void ShaderProgram::setUniform(const std::string& name, float value) {
		GLint location = getUniformLocation(name);
		glUniform1f(location, value);
	}

	void ShaderProgram::setUniform(const std::string& name, int value) {
		GLint location = getUniformLocation(name);
		glUniform1i(location, value);
	}

	void ShaderProgram::setUniform(const std::string& name, glm::mat4 value) {
		GLint location = getUniformLocation(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, &(value[0][0]));
	}

	void ShaderProgram::bind() {
		glUseProgram(m_program);
		for (GLuint i = 0; i < m_numAttributes; i++) {
			glEnableVertexAttribArray(i);
		}
	}

	void ShaderProgram::unbind() {
		glUseProgram(0);
		for (GLuint i = 0; i < m_numAttributes; i++) {
			glDisableVertexAttribArray(i);
		}
	}
}