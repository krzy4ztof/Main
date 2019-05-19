/*
 * ShaderResourceLoader.cpp
 *
 *  Created on: 3 maj 2019
 *      Author: Krzysztof
 */

#include "ShaderResourceLoader.h"
#include "../debugging/Logger.h"
#include "../utilities/Templates.h"

// #include <GL/glew.h>  // MUST be included before freeglut.h and glfw3.h
#include <GLFW/glfw3.h> // GLuint

#include <boost/cstdint.hpp> // boost::uintmax_t
#include <boost/optional.hpp> // boost::optional
#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;

#include <istream> // std::istream, std::basic_istream<char>
#include <sstream> // std::stringbuf, std::stringstream
#include <fstream> // std::ifstream
#include <memory> // shared_ptr, dynamic_pointer_cast

using boost::uintmax_t;
using boost::optional;
using boost::filesystem::path;

using std::istream;
using std::stringbuf;
using std::stringstream;
using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::string;
using std::ifstream;

namespace base_game {

ShaderResourceExtraData::ShaderResourceExtraData() {
	logger::info("Create ShaderResourceExtraData");
	shaderId = 0;
}

ShaderResourceExtraData::~ShaderResourceExtraData() {
	logger::info("Destroy ShaderResourceExtraData");
	shaderId = 0;
}

void ShaderResourceExtraData::compileShader(char* pRawBuffer,
		uintmax_t rawSize) {
	//return shaderId;

}

VertexShaderResourceExtraData::VertexShaderResourceExtraData() {
	logger::info("Create VertexShaderResourceExtraData");
}

VertexShaderResourceExtraData::~VertexShaderResourceExtraData() {
	logger::info("Destroy VertexShaderResourceExtraData");
}

void VertexShaderResourceExtraData::compileShader(char* pRawBuffer,
		uintmax_t rawSize) {

	stringstream ss;
	logger::info("compileVertexShader");

	/*
	 * 	// Create the shaders
	 GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	 GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	 // Read the Vertex Shader code from the file
	 string VertexShaderCode;
	 ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	 if (VertexShaderStream.is_open()) {
	 stringstream sstr;
	 sstr << VertexShaderStream.rdbuf();
	 VertexShaderCode = sstr.str();
	 VertexShaderStream.close();
	 } else {
	 ss << "Impossible to open " << vertex_file_path
	 << ". Are you in the right directory ?";
	 logger::error(ss);
	 //printf(
	 //	"Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n",
	 //vertex_file_path);

	 getchar();
	 return 0;
	 }

	 char const * VertexSourcePointer = VertexShaderCode.c_str();
	 glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	 glCompileShader(VertexShaderID);

	 // Check Vertex Shader
	 glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	 glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	 if (InfoLogLength > 0) {
	 std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
	 glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL,
	 &VertexShaderErrorMessage[0]);
	 printf("%s\n", &VertexShaderErrorMessage[0]);
	 }
	 
	 */
	
	//GLuint shaderId = glCreateShader(GL_VERTEX_SHADER);
	shaderId = glCreateShader(GL_VERTEX_SHADER);



	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
//	printf("Compiling shader : %s\n", vertex_file_path);
	//ss << "Compiling shader :  " << vertex_file_path;
	//logger::info (ss);

	//glShaderSource(shaderId, 1, &pRawBuffer, rawSize);
	ss << "--------------";
	logger::info(ss);

	string str(pRawBuffer);
	ss << str;
	logger::info(ss);
	ss << "--------------";
	logger::info(ss);
	//char const * shaderBuf = str.c_str();

	glShaderSource(shaderId, 1, &pRawBuffer, NULL);
	//glShaderSource(shaderId, 1, &shaderBuf, NULL);

	glCompileShader(shaderId);

	// Check Vertex Shader
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(shaderId, InfoLogLength, NULL,
				&VertexShaderErrorMessage[0]);

		ss << &VertexShaderErrorMessage[0];
		logger::error(ss);
	}

	//return shaderId;

}

FragmentShaderResourceExtraData::FragmentShaderResourceExtraData() {
	logger::info("Create FragmentShaderResourceExtraData");
}

FragmentShaderResourceExtraData::~FragmentShaderResourceExtraData() {
	logger::info("Destroy FragmentShaderResourceExtraData");
}

void FragmentShaderResourceExtraData::compileShader(char* pRawBuffer,
		uintmax_t rawSize) {
	//return shaderId;
	stringstream ss;

	shaderId = glCreateShader(GL_FRAGMENT_SHADER);

	/*

	// Read the Fragment Shader code from the file
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	 */

	GLint Result = GL_FALSE;
	int InfoLogLength;


	//char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	//glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);

	//glShaderSource(shaderId, 1, &pRawBuffer, rawSize);
//	string str(pRawBuffer);
//	char const * shaderBuf = str.c_str();

	glShaderSource(shaderId, 1, &pRawBuffer, NULL);
	//glShaderSource(shaderId, 1, &shaderBuf, NULL);

	//glShaderSource(shaderId, 1, &pRawBuffer, NULL);
	glCompileShader(shaderId);

	// Check Fragment Shader
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(shaderId, InfoLogLength, NULL,
				&FragmentShaderErrorMessage[0]);

		ss << &FragmentShaderErrorMessage[0];
		logger::error (ss);
		//printf("%s\n", &FragmentShaderErrorMessage[0]);
	}
}

ShaderResourceLoader::ShaderResourceLoader() {
	logger::info("Create ShaderResourceLoader");
}

ShaderResourceLoader::~ShaderResourceLoader() {
	logger::info("Destroy ShaderResourceLoader");
}

VertexShaderResourceLoader::VertexShaderResourceLoader() {
	logger::info("Create VertexShaderResourceLoader");
}

VertexShaderResourceLoader::~VertexShaderResourceLoader() {
	logger::info("Destroy VertexShaderResourceLoader");
}

string VertexShaderResourceLoader::vGetPattern() {
	return "*.vert";
}

bool VertexShaderResourceLoader::vLoadResource(char *rawBuffer,
		uintmax_t rawSize, shared_ptr<ResourceHandle> handle) {

	if (rawSize <= 0) {
		return false;
	}

	shared_ptr<VertexShaderResourceExtraData> pExtraData = shared_ptr
			< VertexShaderResourceExtraData
			> (new VertexShaderResourceExtraData());
	pExtraData->compileShader(rawBuffer, rawSize);

	handle->setExtraData(pExtraData);
//	handle->setExtraData(shared_ptr<XmlResourceExtraData>(pExtraData));

	return true;
}

FragmentShaderResourceLoader::FragmentShaderResourceLoader() {
	logger::info("Create FragmentShaderResourceLoader");
}

FragmentShaderResourceLoader::~FragmentShaderResourceLoader() {
	logger::info("Destroy FragmentShaderResourceLoader");
}

string FragmentShaderResourceLoader::vGetPattern() {
	return "*.frag";
}

bool FragmentShaderResourceLoader::vLoadResource(char *rawBuffer,
		uintmax_t rawSize,
		shared_ptr<ResourceHandle> handle) {

	if (rawSize <= 0) {
		return false;
	}

	shared_ptr<FragmentShaderResourceExtraData> pExtraData = shared_ptr
			< FragmentShaderResourceExtraData
			> (new FragmentShaderResourceExtraData());
	pExtraData->compileShader(rawBuffer, rawSize);

	handle->setExtraData(pExtraData);
//	handle->setExtraData(shared_ptr<XmlResourceExtraData>(pExtraData));

	return true;
}

ShaderCompiler::ShaderCompiler(shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create ShaderCompiler");
	this->shrdPtrResourceCache = resourceCache;
}

ShaderCompiler::~ShaderCompiler() {
	logger::info("Destroy ShaderCompiler");
	shrdPtrResourceCache.reset();
}

GLuint ShaderCompiler::loadShaders_old(string vertexShaderName,
		string fragmentShaderName) {

	stringstream ss;

	const char * vertex_file_path = vertexShaderName.c_str();
	const char * fragment_file_path = fragmentShaderName.c_str();

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	string VertexShaderCode;
	ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	} else {
		ss << "Impossible to open " << vertex_file_path
				<< ". Are you in the right directory ?";
		logger::error(ss);
		//printf(
		//	"Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n",
		//vertex_file_path);

		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
//	printf("Compiling shader : %s\n", vertex_file_path);
	ss << "Compiling shader :  " << vertex_file_path;
	logger::info(ss);

	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL,
				&VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}


	// Compile Fragment Shader
//	printf("Compiling shader : %s\n", fragment_file_path);
	ss << "Compiling shader :  " << fragment_file_path;
	logger::info(ss);

	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL,
				&FragmentShaderErrorMessage[0]);

		ss << &FragmentShaderErrorMessage[0];
		logger::error(ss);
		//printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	//printf("Linking program\n");
	logger::info("Linking program");

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL,
				&ProgramErrorMessage[0]);
		//printf("%s\n", &ProgramErrorMessage[0]);
		ss << &ProgramErrorMessage[0];
		logger::error(ss);

	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;

}

const string ShaderCompiler::SHADERS_FOLDER = "shaders";


shared_ptr<IResourceExtraData> ShaderCompiler::loadShader(
		string vertexShaderName) {
	stringstream ss;
	
	path vertexResourcePath { ShaderCompiler::SHADERS_FOLDER };
	vertexResourcePath /= vertexShaderName;
	vertexResourcePath = vertexResourcePath.make_preferred();

	string vertexShaderResourceName = vertexResourcePath.string();

	//string vertexShaderResourceName = ShaderCompiler::SHADERS_FOLDER + "/" + vertexShaderName; //OK dla developmentFolder
	ss << "vertexResourcePath: " << vertexShaderResourceName;
	logger::info(ss);

	Resource vertexResource(vertexShaderResourceName);
	optional<shared_ptr<ResourceHandle>> pVertexResourceHandle =
			shrdPtrResourceCache->getHandle(&vertexResource);

	shared_ptr<IResourceExtraData> vertexExtraData =
			pVertexResourceHandle.get()->getExtraData();

	ss << pVertexResourceHandle.get()->getResource().getName();
	logger::info(ss);

	ss << vertexExtraData->vToString();
	logger::info(ss);

	return vertexExtraData;
}

GLuint ShaderCompiler::loadVertexShader(string vertexShaderName) {
	stringstream ss;
	// string resourceName = "actors/player_character.xml";

	shared_ptr<IResourceExtraData> vertexExtraData = loadShader(
			vertexShaderName);

	GLuint VertexShaderID = 0;
	if (shared_ptr<VertexShaderResourceExtraData> vertexShaderExtraData =
			dynamic_pointer_cast<VertexShaderResourceExtraData>(
					vertexExtraData)) {
		VertexShaderID = vertexShaderExtraData->getShaderId();
	}

	return VertexShaderID;
}

GLuint ShaderCompiler::loadFragmentShader(string fragmentShaderName) {
	stringstream ss;
	// string resourceName = "actors/player_character.xml";

	shared_ptr<IResourceExtraData> vertexExtraData = loadShader(
			fragmentShaderName);

	GLuint FragmentShaderID = 0;
	if (shared_ptr<FragmentShaderResourceExtraData> vertexShaderExtraData =
			dynamic_pointer_cast<FragmentShaderResourceExtraData>(
					vertexExtraData)) {
		FragmentShaderID = vertexShaderExtraData->getShaderId();
	}

	return FragmentShaderID;
}


GLuint ShaderCompiler::loadShaders(string vertexShaderName,
		string fragmentShaderName) {

	stringstream ss;

	const char * vertex_file_path = vertexShaderName.c_str();
	const char * fragment_file_path = fragmentShaderName.c_str();

	GLuint VertexShaderID = loadVertexShader(vertexShaderName);
	// Create the shaders
//	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	GLuint FragmentShaderID = loadFragmentShader(fragmentShaderName);
	/*
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


	// Read the Fragment Shader code from the file
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;
	 */


	// Compile Fragment Shader
//	printf("Compiling shader : %s\n", fragment_file_path);
//	ss << "Compiling shader :  " << fragment_file_path;
//	logger::info(ss);

	/*
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL,
				&FragmentShaderErrorMessage[0]);

		ss << &FragmentShaderErrorMessage[0];
		logger::error(ss);
		//printf("%s\n", &FragmentShaderErrorMessage[0]);
	}
	 */

	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Link the program
	//printf("Linking program\n");
	logger::info("Linking program");

	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL,
				&ProgramErrorMessage[0]);
		//printf("%s\n", &ProgramErrorMessage[0]);
		ss << &ProgramErrorMessage[0];
		logger::error(ss);


	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;

}


namespace vertex_shader_resource_loader {
shared_ptr<IResourceLoader> createVertexShaderResourceLoader() {
	VertexShaderResourceLoader* loader = new VertexShaderResourceLoader();
	shared_ptr<IResourceLoader> pointer = shared_ptr < IResourceLoader
			> (loader);
	return pointer;
}
}

namespace fragment_shader_resource_loader {
shared_ptr<IResourceLoader> createFragmentShaderResourceLoader() {
	FragmentShaderResourceLoader* loader = new FragmentShaderResourceLoader();
	shared_ptr<IResourceLoader> pointer = shared_ptr < IResourceLoader
			> (loader);
	return pointer;
}
}

} /* namespace opengl_tests */
