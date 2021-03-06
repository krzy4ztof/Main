/*
 * TextureResourceLoader.cpp
 *
 *  Created on: 12 sty 2019
 *      Author: Krzysztof
 */

#include "../graphics3d/TextureResourceLoader.h"

#include "../debugging/Logger.h"
#include <string> // string
#include <memory> // shared_ptr
#include <sstream> // std::stringbuf, std::stringstream
#include <ios> // std::ios_base
#include <boost/cstdint.hpp> // boost::uintmax_t
#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;
#include <boost/gil/extension/numeric/sampler.hpp> // boost::gil::bilinear_sampler;
#include <boost/gil/extension/numeric/resample.hpp> // using boost::gil::resize_view;

using std::string;
using std::shared_ptr;
using std::make_shared;

using std::dynamic_pointer_cast;
using std::stringstream;
using std::ios_base;
using boost::uintmax_t;
using boost::optional;
using boost::filesystem::path;
using boost::gil::read_image;
using boost::gil::jpeg_tag;
using boost::gil::rgb8_image_t;
using boost::gil::rgba8_image_t;
using boost::gil::rgb8_pixel_t;
using boost::gil::rgba8_pixel_t;
using boost::gil::resize_view;
using boost::gil::const_view;
using boost::gil::view;
using boost::gil::bilinear_sampler;
using boost::gil::write_view;
using boost::gil::png_tag;

namespace base_game {

const string JpegResourceExtraData::CLASS_NAME = "JpegResourceExtraData";

JpegResourceExtraData::JpegResourceExtraData() {
	logger::info("Create JpegResourceExtraData");
}

JpegResourceExtraData::~JpegResourceExtraData() {
	logger::info("Destroy JpegResourceExtraData");
}

void JpegResourceExtraData::loadImage(char *pRawBuffer,
		boost::uintmax_t rawSize) {

	// 3. Copy in-memory buffer to another.
	stringstream in_buffer;
	in_buffer.write(pRawBuffer, rawSize);

	// 4. Read in-memory buffer to gil image
	read_image(in_buffer, rgb8_image, jpeg_tag { });

	logger::info("success loading image");
}

JpegResourceLoader::JpegResourceLoader() {
	logger::info("Create JpegResourceLoader");
}

JpegResourceLoader::~JpegResourceLoader() {
	logger::info("Destroy JpegResourceLoader");
}

bool JpegResourceLoader::vLoadResource(char *rawBuffer, uintmax_t rawSize,
		shared_ptr<ResourceHandle> handle) {

	if (rawSize <= 0) {
		return false;
	}

	shared_ptr<JpegResourceExtraData> pExtraData = shared_ptr<
			JpegResourceExtraData>(new JpegResourceExtraData());
	pExtraData->loadImage(rawBuffer, rawSize);

	handle->setExtraData(pExtraData);

	return true;
}

const string PngResourceExtraData::CLASS_NAME = "PngResourceExtraData";

PngResourceExtraData::PngResourceExtraData() {
	logger::info("Create PngResourceExtraData");
}

PngResourceExtraData::~PngResourceExtraData() {
	logger::info("Destroy PngResourceExtraData");
}
void PngResourceExtraData::loadImage(char *pRawBuffer,
		boost::uintmax_t rawSize) {

	stringstream in_buffer;
	in_buffer.write(pRawBuffer, rawSize);

	read_image(in_buffer, rgba8_image, png_tag { });

	logger::info("success loading image");
}

PngResourceLoader::PngResourceLoader() {
	logger::info("Create PngResourceLoader");
}

PngResourceLoader::~PngResourceLoader() {
	logger::info("Destroy PngResourceLoader");
}

bool PngResourceLoader::vLoadResource(char *rawBuffer, uintmax_t rawSize,
		shared_ptr<ResourceHandle> handle) {

	if (rawSize <= 0) {
		return false;
	}

	shared_ptr<PngResourceExtraData> pExtraData = shared_ptr<
			PngResourceExtraData>(new PngResourceExtraData());
	pExtraData->loadImage(rawBuffer, rawSize);

	handle->setExtraData(pExtraData);

	return true;
}

const string TextureLoader::GRAPHICS_FOLDER = "graphics";

TextureLoader::TextureLoader(shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TextureLoader");
	this->shrdPtrResourceCache = resourceCache;
}

TextureLoader::~TextureLoader() {
	logger::info("Destroy TextureLoader");
}

shared_ptr<IResourceExtraData> TextureLoader::loadImage(string filename) {
	stringstream ss;

	path imgPath { TextureLoader::GRAPHICS_FOLDER };
	imgPath /= filename;
	imgPath = imgPath.make_preferred();

	string imgResourceName = imgPath.string();

	ss << "imgResourceName: " << imgResourceName;
	logger::info(ss);

	Resource imgResource(imgResourceName);
	optional<shared_ptr<ResourceHandle>> pImgResourceHandle =
			shrdPtrResourceCache->getHandle(&imgResource);

	shared_ptr<IResourceExtraData> imgExtraData =
			pImgResourceHandle.get()->getExtraData();

	ss << pImgResourceHandle.get()->getResource().getName();
	logger::info(ss);

	ss << imgExtraData->vToString();
	logger::info(ss);

	return imgExtraData;
}

void TextureLoader::init(string fileName, shared_ptr<SpriteSheet> spriteSheet) {
}

void TextureLoader::activate(std::shared_ptr<SpriteSheet> spriteSheet) {
	// START TEXTURE
	// Now bind it to the context using the GL_TEXTURE_2D binding point
	glBindTexture(GL_TEXTURE_2D, spriteSheet->texture); //texture);
}

void TextureLoader::deactivate() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureLoader::terminate() {
}

JpegTextureLoader::JpegTextureLoader(shared_ptr<ResourceCache> resourceCache) :
		TextureLoader(resourceCache) {
	logger::info("Create JpegTextureLoader");
}

JpegTextureLoader::~JpegTextureLoader() {
	logger::info("Destroy JpegTextureLoader");
}

void JpegTextureLoader::init(string fileName,
		shared_ptr<SpriteSheet> spriteSheet) {
	TextureLoader::init(fileName, spriteSheet);

	stringstream ss;

	shared_ptr<IResourceExtraData> resourceExtraData = this->loadImage(
			fileName);

	if (JpegResourceExtraData::CLASS_NAME.compare(
			resourceExtraData->vToString()) == 0) {
		if (shared_ptr<JpegResourceExtraData> imageData = dynamic_pointer_cast<
				JpegResourceExtraData>(resourceExtraData)) {

			rgb8_image_t rgb8_image = imageData->getImage();
			debugCopyImageJpg(rgb8_image);
			image_to_texture(rgb8_image, spriteSheet);
		}

	} else if (PngResourceExtraData::CLASS_NAME.compare(
			resourceExtraData->vToString()) == 0) {

		logger::info("PNG image");
	}
}

void JpegTextureLoader::activate(shared_ptr<SpriteSheet> spriteSheet) {
	TextureLoader::activate(spriteSheet);

	glTexStorage2D(GL_TEXTURE_2D,   // 2D texture
			1,               // 8 mipmap levels
			GL_RGBA32F,      // 32-bit floating-point RGBA data
			spriteSheet->getWidth(), spriteSheet->getHeight()); // 256 x 256 texels

	// Assume the texture is already bound to the GL_TEXTURE_2D target
	glTexSubImage2D(GL_TEXTURE_2D,  // 2D texture
			0,              // Level 0
			0, 0,           // Offset 0, 0
			spriteSheet->getWidth(), spriteSheet->getHeight(), // 256 x 256 texels, replace entire image
			//	img_width, img_height,     // 256 x 256 texels, replace entire image
			GL_RGBA,// Four channel data
			GL_FLOAT, // Floating point data
			//GL_INT,       // Floating point data
			spriteSheet->data);       //
}

void JpegTextureLoader::image_to_texture(rgb8_image_t rgb8_image,
		shared_ptr<SpriteSheet> spriteSheet) {

	int img_width = rgb8_image.width();
	int img_height = rgb8_image.height();

	spriteSheet->setWidth(img_width);
	spriteSheet->setHeight(img_height);

	spriteSheet->data = new float[img_width * img_height * 4];

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {
			rgb8_pixel_t px = *const_view(rgb8_image).at(x, y);

			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 0] =
					(float) px[0] / 255;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 1] =
					(float) px[1] / 255;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 2] =
					(float) px[2] / 255;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 3] =
					1.0f;
		}
	}
}

void JpegTextureLoader::debugCopyImageJpg(rgb8_image_t imageData) {
	stringstream ss;
	string assetsFolder = shrdPtrResourceCache->getAssetsFolder();
	path outImgPath { assetsFolder };
	outImgPath /= GRAPHICS_FOLDER;
	outImgPath /= "temp_t009_debug_resized.jpg";
	string outImgString = outImgPath.string();
	ss << "Orig Image Width: " << imageData.width() << "; Height: "
			<< imageData.height();
	logger::info(ss);

	ss << "outImage: " << outImgString;
	logger::info(ss);

	rgb8_pixel_t px = *const_view(imageData).at(5, 10);
	ss << "The pixel at 5,10 is " << (int) px[0] << ',' << (int) px[1] << ','
			<< (int) px[2];

	// Scale the image to 100x100 pixels using bilinear resampling
	rgb8_image_t square100x100(100, 100);

	resize_view(const_view(imageData), view(square100x100),
			bilinear_sampler { });

	write_view(outImgString, const_view(square100x100), jpeg_tag { });
}

PngTextureLoader::PngTextureLoader(shared_ptr<ResourceCache> resourceCache) :
		TextureLoader(resourceCache) {
	logger::info("Create PngTextureLoader");
}

PngTextureLoader::~PngTextureLoader() {
	logger::info("Destroy PngTextureLoader");
}

void PngTextureLoader::init(string fileName,
		shared_ptr<SpriteSheet> spriteSheet) {
	TextureLoader::init(fileName, spriteSheet);

	stringstream ss;

	shared_ptr<IResourceExtraData> resourceExtraData = this->loadImage(
			fileName);

	if (JpegResourceExtraData::CLASS_NAME.compare(
			resourceExtraData->vToString()) == 0) {
		logger::info("JPG image");

	} else if (PngResourceExtraData::CLASS_NAME.compare(
			resourceExtraData->vToString()) == 0) {

		logger::info("PNG image");

		if (shared_ptr<PngResourceExtraData> imageData = dynamic_pointer_cast<
				PngResourceExtraData>(resourceExtraData)) {

			rgba8_image_t rgba8_image = imageData->getImage();
			debugCopyImagePng(rgba8_image);
			image_to_texture(rgba8_image, spriteSheet);
		}
	}
}

void PngTextureLoader::activate(std::shared_ptr<SpriteSheet> spriteSheet) {
	TextureLoader::activate(spriteSheet);

	glTexStorage2D(GL_TEXTURE_2D,   // 2D texture
			1,               // 8 mipmap levels
			GL_RGBA32F,      // 32-bit floating-point RGBA data
			spriteSheet->getWidth(), spriteSheet->getHeight()); // 256 x 256 texels

	// Assume the texture is already bound to the GL_TEXTURE_2D target
	glTexSubImage2D(GL_TEXTURE_2D,  // 2D texture
			0,              // Level 0
			0, 0,           // Offset 0, 0
			spriteSheet->getWidth(), spriteSheet->getHeight(), // 256 x 256 texels, replace entire image
			GL_RGBA,// Four channel data
			GL_FLOAT, // Floating point data
			spriteSheet->data);
}

void PngTextureLoader::image_to_texture(rgba8_image_t rgba8_image,
		shared_ptr<SpriteSheet> spriteSheet) {

	int img_width = rgba8_image.width();
	int img_height = rgba8_image.height();

	spriteSheet->setWidth(img_width);
	spriteSheet->setHeight(img_height);

	spriteSheet->data = new float[img_width * img_height * 4];

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {
			rgba8_pixel_t px = *const_view(rgba8_image).at(x, y);

			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 0] =
					(float) px[0] / 255;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 1] =
					(float) px[1] / 255;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 2] =
					(float) px[2] / 255;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 3] =
					(float) px[3] / 255;

		}
	}

}

void PngTextureLoader::debugCopyImagePng(rgba8_image_t imageData) {
	stringstream ss;
	string assetsFolder = shrdPtrResourceCache->getAssetsFolder();
	path outImgPath { assetsFolder };
	outImgPath /= GRAPHICS_FOLDER;
	outImgPath /= "temp_t00d_png_gil_texture_loader_resized.png";
	string outImgString = outImgPath.string();
	ss << "Orig Image Width: " << imageData.width() << "; Height: "
			<< imageData.height();
	logger::info(ss);

	ss << "outImage: " << outImgString;
	logger::info(ss);

	rgba8_pixel_t px = *const_view(imageData).at(5, 10);
	ss << "The pixel at 5,10 is " << (int) px[0] << ',' << (int) px[1] << ','
			<< (int) px[2];

	// Scale the image to 100x100 pixels using bilinear resampling
	rgba8_image_t square100x100(100, 100);

	resize_view(const_view(imageData), view(square100x100),
			bilinear_sampler { });

	write_view(outImgString, const_view(square100x100), png_tag { });
}

namespace jpeg_resource_loader {
shared_ptr<IResourceLoader> createJpegResourceLoader() {
	JpegResourceLoader *loader = new JpegResourceLoader();
	shared_ptr<IResourceLoader> pointer = shared_ptr<IResourceLoader>(loader);
	return pointer;
}
}

namespace png_resource_loader {
shared_ptr<IResourceLoader> createPngResourceLoader() {
	PngResourceLoader *loader = new PngResourceLoader();
	shared_ptr<IResourceLoader> pointer = shared_ptr<IResourceLoader>(loader);
	return pointer;
}
}

} /* namespace base_game */
