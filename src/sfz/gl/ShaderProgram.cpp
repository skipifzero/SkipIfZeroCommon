#include "sfz/gl/ShaderProgram.hpp"

#include <algorithm>
#include <iostream>
#include <new>

#include "sfz/gl/OpenGL.hpp"

namespace gl {

// Static function
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

static void printShaderInfoLog(GLuint shader) noexcept
{
	int logLength;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	char* log = new (std::nothrow) char[(size_t)logLength+1];
	glGetShaderInfoLog(shader, logLength, NULL, log);
	std::cerr << log << std::endl;
	delete[] log;
}

/* Returns 0 if shader compilation failed. */
static GLuint compileShader(const char* source, GLenum shaderType) noexcept
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int compileSuccess;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
	if (!compileSuccess) {
		printShaderInfoLog(shader);
		glDeleteShader(shader);
		return 0;
	}
	
	return shader;
}

/* Returns false if linking failed. */
static bool linkProgram(GLuint program) noexcept
{
	glLinkProgram(program);
	GLint linkSuccess = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &linkSuccess);
	if (!linkSuccess) {
		printShaderInfoLog(program);
		return false;
	}
	return true;
}

// ShaderProgram: Constructor functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

ShaderProgram ShaderProgram::fromSource(const char* vertexSrc, const char* geometrySrc, const char* fragmentSrc) noexcept
{
	GLuint vertexShader = compileShader(vertexSrc, GL_VERTEX_SHADER);
	if (vertexShader == 0) {
		std::cerr << "Couldn't compile vertex shader." << std::endl;
		return ShaderProgram{};
	}

	GLuint geometryShader = compileShader(geometrySrc, GL_GEOMETRY_SHADER);
	if (geometryShader == 0) {
		std::cerr << "Couldn't compile geometry shader." << std::endl;
		return ShaderProgram{};
	}
	
	GLuint fragmentShader = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);
	if (fragmentShader == 0) {
		std::cerr << "Couldn't compile fragment shader." << std::endl;
		return ShaderProgram{};
	}

	GLuint shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, geometryShader);
	glAttachShader(shaderProgram, fragmentShader);

	// TODO: glBindAttribLocation() & glBindFragDataLocation() here?

	bool linkSuccess = linkProgram(shaderProgram);

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, geometryShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);

	if (!linkSuccess) {
		glDeleteProgram(shaderProgram);
		std::cerr << "Couldn't link shader program." << std::endl;
		return ShaderProgram{};
	}
	
	ShaderProgram temp;
	temp.mHandle = shaderProgram;
	return std::move(temp);
}

ShaderProgram ShaderProgram::fromSource(const string& vertexSrc, const string& geometrySrc, const string& fragmentSrc) noexcept
{
	return fromSource(vertexSrc.c_str(), geometrySrc.c_str(), fragmentSrc.c_str());
}

ShaderProgram ShaderProgram::fromSource(const char* vertexSrc, const char* fragmentSrc) noexcept
{
	GLuint vertexShader = compileShader(vertexSrc, GL_VERTEX_SHADER);
	if (vertexShader == 0) {
		std::cerr << "Couldn't compile vertex shader." << std::endl;
		return ShaderProgram{};
	}
	
	GLuint fragmentShader = compileShader(fragmentSrc, GL_FRAGMENT_SHADER);
	if (fragmentShader == 0) {
		std::cerr << "Couldn't compile fragment shader." << std::endl;
		return ShaderProgram{};
	}

	GLuint shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// TODO: glBindAttribLocation() & glBindFragDataLocation() here?

	bool linkSuccess = linkProgram(shaderProgram);

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	if (!linkSuccess) {
		glDeleteProgram(shaderProgram);
		std::cerr << "Couldn't link shader program." << std::endl;
		return ShaderProgram{};
	}
	
	ShaderProgram temp;
	temp.mHandle = shaderProgram;
	return temp;
}

ShaderProgram ShaderProgram::fromSource(const string& vertexSrc, const string& fragmentSrc) noexcept
{
	return fromSource(vertexSrc.c_str(), fragmentSrc.c_str());
}

ShaderProgram ShaderProgram::postProcessFromSource(const char* postProcessSrc) noexcept
{
	// TODO: Implement
	return ShaderProgram{};
}

ShaderProgram ShaderProgram::postProcessFromSource(const string& postProcessSrc) noexcept
{
	return postProcessFromSource(postProcessSrc.c_str());
}


ShaderProgram ShaderProgram::fromFile(const char* vertexPath, const char* geometryPath, const char* fragmentPath) noexcept
{
	// TODO: Implement
	return ShaderProgram{};
}

ShaderProgram ShaderProgram::fromFile(const string& vertexPath, const string& geometryPath, const string& fragmentPath) noexcept
{
	return fromFile(vertexPath.c_str(), geometryPath.c_str(), fragmentPath.c_str());
}

ShaderProgram ShaderProgram::fromFile(const char* vertexPath, const char* fragmentPath) noexcept
{
	// TODO: Implement
	return ShaderProgram{};
}

ShaderProgram ShaderProgram::fromFile(const string& vertexPath, const string& fragmentPath) noexcept
{
	return fromFile(vertexPath.c_str(), fragmentPath.c_str());
}

ShaderProgram ShaderProgram::postProcessFromFile(const char* postProcessPath) noexcept
{
	// TODO: Implement
	return ShaderProgram{};
}

ShaderProgram ShaderProgram::postProcessFromFile(const string& postProcessPath) noexcept
{
	return postProcessFromFile(postProcessPath.c_str());
}

// ShaderProgram: Public methods
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

bool ShaderProgram::reload() noexcept
{
	// TODO: Implement
	return false;
}


// ShaderProgram: Constructors & destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

ShaderProgram::ShaderProgram() noexcept
:
	mVertexPath{""},
	mGeometryPath{""},
	mFragmentPath{""}
{ }

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
{
	std::swap(this->mHandle, other.mHandle);
	std::swap(this->mVertexPath, other.mVertexPath);
	std::swap(this->mGeometryPath, other.mGeometryPath);
	std::swap(this->mFragmentPath, other.mFragmentPath);
}

ShaderProgram& ShaderProgram::operator= (ShaderProgram&& other) noexcept
{
	std::swap(this->mHandle, other.mHandle);
	std::swap(this->mVertexPath, other.mVertexPath);
	std::swap(this->mGeometryPath, other.mGeometryPath);
	std::swap(this->mFragmentPath, other.mFragmentPath);
	return *this;
}

ShaderProgram::~ShaderProgram() noexcept
{
	glDeleteProgram(mHandle); // Silently ignored if mHandle == 0.
}

} // namespace gl