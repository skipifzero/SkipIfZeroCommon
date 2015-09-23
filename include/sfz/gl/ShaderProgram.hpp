#pragma once
#ifndef SFZ_GL_SHADER_PROGRAM_HPP
#define SFZ_GL_SHADER_PROGRAM_HPP

#include <cstdint>
#include <string>

namespace gl {

using std::string;
using std::uint32_t;

// ShaderProgram class
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

class ShaderProgram final {
public:
	// Constructor functions
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	ShaderProgram fromSource(const char* vertexSrc, const char* geometrySrc, const char* fragmentSrc) noexcept;
	ShaderProgram fromSource(const string& vertexSrc, const string& geometrySrc, const string& fragmentSrc) noexcept;
	ShaderProgram fromSource(const char* vertexSrc, const char* fragmentSrc) noexcept;
	ShaderProgram fromSource(const string& vertexSrc, const string& fragmentSrc) noexcept;
	ShaderProgram postProcessFromSource(const char* postProcessSrc) noexcept;
	ShaderProgram postProcessFromSource(const string& postProcessSrc) noexcept;

	ShaderProgram fromFile(const char* vertexPath, const char* geometryPath, const char* fragmentPath) noexcept;
	ShaderProgram fromFile(const string& vertexPath, const string& geometryPath, const string& fragmentPath) noexcept;
	ShaderProgram fromFile(const char* vertexPath, const char* fragmentPath) noexcept;
	ShaderProgram fromFile(const string& vertexPath, const string& fragmentPath) noexcept;
	ShaderProgram postProcessFromFile(const char* postProcessPath) noexcept;
	ShaderProgram postProcessFromFile(const string& postProcessPath) noexcept;

	// Public methods
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	inline uint32_t handle() const noexcept { return mHandle; }
	inline bool isValid() const noexcept { return (mHandle != 0); }
	bool reload() noexcept;

	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator= (const ShaderProgram&) = delete;

	ShaderProgram() noexcept;
	ShaderProgram(ShaderProgram&& other) noexcept;
	ShaderProgram& operator= (ShaderProgram&& other) noexcept;
	~ShaderProgram() noexcept;

private:
	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	uint32_t mHandle = 0;
	string mVertexPath, mGeometryPath, mFragmentPath;
};

} // namespace gl
#endif