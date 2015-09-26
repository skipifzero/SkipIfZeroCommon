#pragma once
#ifndef SFZ_GL_SHADER_PROGRAM_HPP
#define SFZ_GL_SHADER_PROGRAM_HPP

#include <cstdint>
#include <string>

#include "sfz/math/Matrix.hpp"
#include "sfz/math/Vector.hpp"

namespace gl {

using sfz::vec2;
using sfz::vec3;
using sfz::vec4;
using sfz::mat2;
using sfz::mat3;
using sfz::mat4;

using std::string;
using std::uint32_t;

// Program class
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

class Program final {
public:
	// Constructor functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	static Program fromSource(const char* vertexSrc, const char* geometrySrc, const char* fragmentSrc,
	                          void(*bindAttribFragFunc)(uint32_t shaderProgram) = nullptr) noexcept;
	
	static Program fromSource(const char* vertexSrc, const char* fragmentSrc,
	                          void(*bindAttribFragFunc)(uint32_t shaderProgram) = nullptr) noexcept;

	static Program fromFile(const char* vertexPath, const char* geometryPath, const char* fragmentPath,
	                        void(*bindAttribFragFunc)(uint32_t shaderProgram) = nullptr) noexcept;
	
	static Program fromFile(const string& vertexPath, const string& geometryPath, const string& fragmentPath,
	                        void(*bindAttribFragFunc)(uint32_t shaderProgram) = nullptr) noexcept;
	
	static Program fromFile(const char* vertexPath, const char* fragmentPath,
	                        void(*bindAttribFragFunc)(uint32_t shaderProgram) = nullptr) noexcept;
	
	static Program fromFile(const string& vertexPath, const string& fragmentPath,
	                        void(*bindAttribFragFunc)(uint32_t shaderProgram) = nullptr) noexcept;

	// Public methods
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	inline uint32_t handle() const noexcept { return mHandle; }
	inline bool isValid() const noexcept { return (mHandle != 0); }
	bool reload() noexcept;

	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	Program() = default;
	Program(const Program&) = delete;
	Program& operator= (const Program&) = delete;

	Program(Program&& other) noexcept;
	Program& operator= (Program&& other) noexcept;
	~Program() noexcept;

private:
	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	// The handle to the current OpenGL program
	uint32_t mHandle = 0;

	// Optional paths to shader source files
	string mVertexPath = "";
	string mGeometryPath = "";
	string mFragmentPath = "";

	// Optional function used to call glBindAttribLocation() & glBindFragDataLocation()
	void(*mBindAttribFragFunc)(uint32_t shaderProgram) = nullptr;
};

// Program compilation & linking helper functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

/** 
 * @brief Compiles shader
 * @param shaderType is a GLenum and can for example be of type GL_FRAGMENT_SHADER
 * @return the compiled shader, 0 if failed.
 */
uint32_t compileShader(const char* source, uint32_t shaderType) noexcept;

/** Links an OpenGL program and returns whether succesful or not. */
bool linkProgram(uint32_t program) noexcept;

/** Prints the shader info log, typically called if compilation (or linking) failed. */
void printShaderInfoLog(uint32_t shader) noexcept;

// Uniform setters
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void setUniform(int location, int i) noexcept;
void setUniform(const Program& program, const char* name, int i) noexcept;
void setUniform(int location, const int* intArray, size_t count) noexcept;
void setUniform(const Program& program, const char* name, const int* intArray, size_t count) noexcept;

void setUniform(int location, float f) noexcept;
void setUniform(const Program& program, const char* name, float f) noexcept;
void setUniform(int location, const float* floatArray, size_t count) noexcept;
void setUniform(const Program& program, const char* name, const float* floatArray, size_t count) noexcept;

void setUniform(int location, vec2 vector) noexcept;
void setUniform(const Program& program, const char* name, vec2 vector) noexcept;
void setUniform(int location, const vec2* vectorArray, size_t count) noexcept;
void setUniform(const Program& program, const char* name, const vec2* vectorArray, size_t count) noexcept;

void setUniform(int location, const vec3& vector) noexcept;
void setUniform(const Program& program, const char* name, const vec3& vector) noexcept;
void setUniform(int location, const vec3* vectorArray, size_t count) noexcept;
void setUniform(const Program& program, const char* name, const vec3* vectorArray, size_t count) noexcept;

void setUniform(int location, const vec4& vector) noexcept;
void setUniform(const Program& program, const char* name, const vec4& vector) noexcept;
void setUniform(int location, const vec4* vectorArray, size_t count) noexcept;
void setUniform(const Program& program, const char* name, const vec4* vectorArray, size_t count) noexcept;

void setUniform(int location, const mat3& matrix) noexcept;
void setUniform(const Program& program, const char* name, const mat3& matrix) noexcept;
void setUniform(int location, const mat3* matrixArray, size_t count) noexcept;
void setUniform(const Program& program, const char* name, const mat3* matrixArray, size_t count) noexcept;

void setUniform(int location, const mat4& matrix) noexcept;
void setUniform(const Program& program, const char* name, const mat4& matrix) noexcept;
void setUniform(int location, const mat4* matrixArray, size_t count) noexcept;
void setUniform(const Program& program, const char* name, const mat4* matrixArray, size_t count) noexcept;

} // namespace gl
#endif