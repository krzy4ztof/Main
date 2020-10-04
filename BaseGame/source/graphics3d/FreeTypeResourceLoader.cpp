/*
 * FreeTypeResourceLoader.cpp
 *
 *  Created on: 10 lis 2019
 *      Author: Krzysztof
 */

#include "FreeTypeResourceLoader.h"
#include "../debugging/Logger.h"
#include "FreeTypeCharacter.h"

#include <sstream> // std::stringbuf, std::stringstream
#include <memory> // shared_ptr, dynamic_pointer_cast
#include <string> // string
#include <glm/glm.hpp> // glm::ivec2

#include <boost/optional.hpp> // boost::optional
#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;

using std::stringstream;
using std::shared_ptr;
using std::make_shared;
using std::string;
using std::map;
using std::dynamic_pointer_cast;

using boost::optional;
using boost::filesystem::path;


namespace base_game {

FreeTypeResourceExtraData::FreeTypeResourceExtraData() {
	logger::info("Create FreeTypeResourceExtraData");
	characters = make_shared<map<GLushort, FreeTypeCharacter>>();

}

FreeTypeResourceExtraData::~FreeTypeResourceExtraData() {
	logger::info("Destroy FreeTypeResourceExtraData");
	characters.reset();
}

void FreeTypeResourceExtraData::loadFtNewFace(char *rawBuffer,
		uintmax_t rawSize) {
	FT_Library ft = nullptr;
	FT_Face face = nullptr;
	FT_Error ft_error = FT_Init_FreeType(&ft);

	if (ft_error) {
		logger::error("ERROR::FREETYPE: Could not init FreeType Library");
	}

	const FT_Byte *ftByteBuffer = (unsigned char*) rawBuffer;

	ft_error = FT_New_Memory_Face(ft, ftByteBuffer, rawSize, 0, &face);

	if (ft_error == FT_Err_Unknown_File_Format) {
		logger::error("ERROR::FREETYPE: Failed to load font");
		logger::error(
				"... the font file could be opened and read, but it appears");
		logger::error("... that its font format is unsupported");
	} else if (ft_error) {
		logger::error("ERROR::FREETYPE: Failed to load font");
		logger::error(
				"... another error code means that the font file could not");
		logger::error("... be opened or read, or that it is broken...");
	}


	 ft_error = FT_Set_Pixel_Sizes(face, // handle to face object
			0, // pixel_width
			FreeTypeCharacter::PIXEL_HEIGHT); // pixel_height


	//ft_error = FT_Set_Pixel_Sizes(face, // handle to face object
	//		0, // pixel_width
	//		48 * 3); // pixel_height

	if (ft_error) {
		logger::error("ERROR::FREETYPE: Could not set pixel sizes");
	}

	initFreetypeCharacters (face);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

}


void FreeTypeResourceExtraData::initCharacter(FT_Face face,
		FT_ULong char_code) {
	this->initCharacter(face, char_code, char_code);
}

void FreeTypeResourceExtraData::initFreetypeCharacters(FT_Face face) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	stringstream ss;

	for (GLubyte c = 0; c < FreeTypeCharacter::MAX_STD_CHAR; c++) {
		initCharacter(face, c);
	}
	logger::info("");
	logger::info("-----------------------");

//	FT_ULong codes[18] = { 260, 261, 262, 263, 280, 281, 321, 322, 323, 324, 211,
	//		243, 346, 347, 377, 378, 379, 380 };

	FT_ULong codes[18] = { 177, 230, 234, 179, 241, 243, 182, 188, 191, 161,
			198, 202, 163, 209, 211, 166, 172, 175 };

	for (FT_ULong code : codes) {
		ss << "[" << (int) (code) << "]:[" << char(code) << "] ";

	}
	logger::info(ss);

	// A
	this->initCharacter(face, 0x0104, 0xc484);
	// a
	this->initCharacter(face, 0x0105, 0xc485);

	// C
	this->initCharacter(face, 0x0106, 0xc486);
	// c
	this->initCharacter(face, 0x0107, 0xc487);

	// E
	this->initCharacter(face, 0x0118, 0xc498);
	// e
	this->initCharacter(face, 0x0119, 0xc499);

	// L
	this->initCharacter(face, 0x0141, 0xc581);
	// l
	this->initCharacter(face, 0x0142, 0xc582);

	// N
	this->initCharacter(face, 0x0143, 0xc583);
	// n
	this->initCharacter(face, 0x0144, 0xc584);

	// O
	this->initCharacter(face, 0x00D3, 0xc393);
	// o
	this->initCharacter(face, 0x00F3, 0xc3b3);

	// S
	this->initCharacter(face, 0x015A, 0xc59a);
	// s
	this->initCharacter(face, 0x015B, 0xc59b);

	// X
	this->initCharacter(face, 0x0179, 0xc5b9);
	// x
	this->initCharacter(face, 0x017A, 0xc5ba);

	// Z
	this->initCharacter(face, 0x017B, 0xc5bb);
	// z
	this->initCharacter(face, 0x017C, 0xc5bc);

	glBindTexture(GL_TEXTURE_2D, 0);

}

void FreeTypeResourceExtraData::initCharacter(FT_Face face, FT_ULong char_code,
		GLushort char_code_out) {
	stringstream ss;

	ss << "[" << (int) (char_code) << "]:[" << char(char_code) << "] ";
	logger::info(ss);

	// Load character glyph
	if (FT_Load_Char(face, char_code, FT_LOAD_RENDER)) {
		logger::error("ERROR::FREETYTPE: Failed to load Glyph");
		return;
	}
	// Generate texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
			face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer);
	// Set texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Now store character for later use
	FreeTypeCharacter character = { texture, glm::ivec2(
			face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(
			face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x };
	//, face->size->metrics.height };
	characters->insert(
			std::pair<GLushort, FreeTypeCharacter>(char_code_out, character));
}

void FreeTypeResourceExtraData::debugCharacters() {
	stringstream ss;
	logger::info("--------- DEBUG START FreeTypeLoader -------");

	ss << "debug: " << characters->size();
	logger::info(ss);

	std::map<GLushort, FreeTypeCharacter>::iterator it;
	for (it = characters->begin(); it != characters->end(); ++it) {
		ss << "Key: " << std::hex << it->first;
		logger::info(ss);

	}

	logger::info("--------- DEBUG END FreeTypeLoader -------");
}



FreeTypeResourceLoader::FreeTypeResourceLoader() {
	logger::info("Create FreeTypeResourceLoader");
}

FreeTypeResourceLoader::~FreeTypeResourceLoader() {
	logger::info("Destroy FreeTypeResourceLoader");
}

string FreeTypeResourceLoader::vGetPattern() {
	return "*.ttf";
}

bool FreeTypeResourceLoader::vLoadResource(char *rawBuffer, uintmax_t rawSize,
		shared_ptr<ResourceHandle> handle) {

	if (rawSize <= 0) {
		return false;
	}

	shared_ptr<FreeTypeResourceExtraData> pExtraData = shared_ptr<
			FreeTypeResourceExtraData>(new FreeTypeResourceExtraData());
	pExtraData->loadFtNewFace(rawBuffer, rawSize);

	 handle->setExtraData(pExtraData);

	return true;
}

const string FreeTypeLoader::FONTS_FOLDER = "fonts";

FreeTypeLoader::FreeTypeLoader(shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create FreeTypeLoader");
	this->shrdPtrResourceCache = resourceCache;
}

FreeTypeLoader::~FreeTypeLoader() {
	logger::info("Destroy FreeTypeLoader");
	shrdPtrResourceCache.reset();
	characters.reset();
}

shared_ptr<IResourceExtraData> FreeTypeLoader::loadFont(string fontFileName) {
	stringstream ss;

	path fontResourcePath { FreeTypeLoader::FONTS_FOLDER };
	fontResourcePath /= fontFileName;
	fontResourcePath = fontResourcePath.make_preferred();

	string fontResourceName = fontResourcePath.string();

	ss << "fontResourcePath: " << fontResourceName;
	logger::info(ss);

	Resource fontResource(fontResourceName);
	optional<shared_ptr<ResourceHandle>> pFontResourceHandle =
			shrdPtrResourceCache->getHandle(&fontResource);

	shared_ptr<IResourceExtraData> fontExtraData =
			pFontResourceHandle.get()->getExtraData();

	ss << pFontResourceHandle.get()->getResource().getName();
	logger::info(ss);

	ss << fontExtraData->vToString();
	logger::info(ss);

	return fontExtraData;
}


shared_ptr<map<GLushort, FreeTypeCharacter>> FreeTypeLoader::initFreetype() {
	stringstream ss;

	//string fontName = "gochi-hand-regular.ttf"; -- missing polish letters
	//string fontName = "fonts-arialif.ttf";
	string fontName = "segoeprb.ttf";



	//shared_ptr<IResourceExtraData> fontExtraData = loadFont(
	//		"gochi-hand-regular.ttf");

	shared_ptr<IResourceExtraData> fontExtraData = loadFont(
				fontName);

	if (shared_ptr<FreeTypeResourceExtraData> freeTypeExtraData =
			dynamic_pointer_cast < FreeTypeResourceExtraData
					>(fontExtraData)) {
		characters = freeTypeExtraData->getCharacters();
	}

	return characters;
}

void FreeTypeLoader::debugCharacters() {
	stringstream ss;
	logger::info("--------- DEBUG START FreeTypeLoader -------");
	ss << "debug: " << characters->size();
	logger::info(ss);

	std::map<GLushort, FreeTypeCharacter>::iterator it;
	for (it = characters->begin(); it != characters->end(); ++it) {
		ss << "Key: " << std::hex << it->first;
		logger::info(ss);

	}

	logger::info("--------- DEBUG END FreeTypeLoader -------");
}


namespace free_type_resource_loader {
shared_ptr<IResourceLoader> createFreeTypeResourceLoader() {
	FreeTypeResourceLoader *loader = new FreeTypeResourceLoader();
	shared_ptr<IResourceLoader> pointer = shared_ptr<IResourceLoader>(loader);
	return pointer;
}
}

} /* namespace base_game */
