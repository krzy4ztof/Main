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
// #include <typeinfo>       // operator typeid, type_info
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
// using std::type_info;
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
	//rgb8_image = nullptr;
}

JpegResourceExtraData::~JpegResourceExtraData() {
	logger::info("Destroy JpegResourceExtraData");
	//rgb8_image = nullptr;
}

void JpegResourceExtraData::loadImage(char *pRawBuffer,
		boost::uintmax_t rawSize) {

	//namespace bg = boost::gil;

	// 3. Copy in-memory buffer to another.
	// stringstream in_buffer(ios_base::in | ios_base::binary);
	stringstream in_buffer;
	//in_buffer << out_buffer.rdbuf();

	in_buffer.write(pRawBuffer, rawSize);

	/*
	 for (int i = 0; i < rawSize; i++) {
	 in_buffer << *(pRawBuffer + i);
	 }
	 */

	// 4. Read in-memory buffer to gil image
	//rgb8_image_t dst;
	read_image(in_buffer, rgb8_image, jpeg_tag { });

	logger::info("success loading image");

	/*
	 bg::read_image(
	 "../Watermill/assets/graphics/temp_t009_jpeg_gil_texture_view.jpg",
	 rgb8_image, bg::jpeg_tag { });
	 //	bg::read_image("../../../assets/graphics/TempT009jpegGilTextureView.jpg",
	 //			rgb8_image, bg::jpeg_tag { });

	 cout << "Width: " << rgb8_image.width() << "; Height: "
	 << rgb8_image.height() << endl;
	 */

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
//	handle->setExtraData(shared_ptr<XmlResourceExtraData>(pExtraData));

	return true;
}

const string PngResourceExtraData::CLASS_NAME = "PngResourceExtraData";

///////////////////////////
PngResourceExtraData::PngResourceExtraData() {
	logger::info("Create PngResourceExtraData");
	//rgb8_image = nullptr;
}

PngResourceExtraData::~PngResourceExtraData() {
	logger::info("Destroy PngResourceExtraData");
	//rgb8_image = nullptr;
}
void PngResourceExtraData::loadImage(char *pRawBuffer,
		boost::uintmax_t rawSize) {

	stringstream in_buffer;
	in_buffer.write(pRawBuffer, rawSize);

	read_image(in_buffer, rgba8_image, png_tag { });

	logger::info("success loading image");
}

/*
 void PngResourceExtraData::loadImage_222(char *pRawBuffer,
 boost::uintmax_t rawSize) {

 namespace bg = boost::gil;

 //bg::read_image("data/img/T00DpngGilScanlineView-pools-alpha.png",
 //	rgba8_image, bg::png_tag { });

 typedef bg::png_tag tag_t;

 //	typedef bg::scanline_reader<
 //			typename bg::get_read_device<const char*, tag_t>::type, tag_t> reader_t;

 typedef bg::scanline_reader<
 typename bg::get_read_device<const stringstream, tag_t>::type,
 tag_t> reader_t;


 //reader_t reader = bg::make_scanline_reader(
 //		"data/img/T00DpngGilScanlineView-pools-alpha.png", tag_t());

 stringstream ss;

 stringstream in_buffer;
 in_buffer.write(pRawBuffer, rawSize);

 reader_t reader = bg::make_scanline_reader(in_buffer, tag_t());

 ss << "Width: " << reader._info._width << "; Height: "
 << reader._info._height;	// << endl;
 logger::info(ss);

 typedef bg::rgba8_image_t image_t;

 //image_t dst(reader._info._width, reader._info._height);
 rgba8_image = image_t(reader._info._width, reader._info._height);

 bg::fill_pixels(bg::view(rgba8_image), image_t::value_type());

 typedef reader_t::iterator_t iterator_t;

 iterator_t it = reader.begin();
 iterator_t end = reader.end();

 for (int row = 0; it != end; ++it, ++row) {
 bg::copy_pixels(
 bg::interleaved_view(reader._info._width, 1,
 (image_t::view_t::x_iterator) *it,
 reader._scanline_length),
 bg::subimage_view(view(rgba8_image), 0, row,
 reader._info._width, 1));
 }

 }
 */

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
//	handle->setExtraData(shared_ptr<XmlResourceExtraData>(pExtraData));

	return true;
}

////////////////////////

/*
 TextureData::TextureData() :
 width(0), height(0), data(nullptr) {
 logger::info("Create TextureData");
 }

 TextureData::~TextureData() {
 logger::info("Destroy TextureData");
 }
 */

const string TextureLoader::GRAPHICS_FOLDER = "graphics";

TextureLoader::TextureLoader(shared_ptr<ResourceCache> resourceCache) {
	logger::info("Create TextureLoader");
	this->shrdPtrResourceCache = resourceCache;
}

TextureLoader::~TextureLoader() {
	logger::info("Destroy TextureLoader");
	// spriteSheet.reset();
}

shared_ptr<IResourceExtraData> TextureLoader::loadImage(string filename) {
	stringstream ss;

	path imgPath { TextureLoader::GRAPHICS_FOLDER };
	imgPath /= filename;
	imgPath = imgPath.make_preferred();

	string imgResourceName = imgPath.string();

	//string vertexShaderResourceName = ShaderCompiler::SHADERS_FOLDER + "/" + vertexShaderName; //OK dla developmentFolder
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
//	glGenTextures(1, &(spriteSheet->texture));	// &texture);
}

void TextureLoader::activate(std::shared_ptr<SpriteSheet> spriteSheet) {
	// START TEXTURE
	// Now bind it to the context using the GL_TEXTURE_2D binding point
	glBindTexture(GL_TEXTURE_2D, spriteSheet->texture); //texture);
}

void TextureLoader::deactivate() {
	glBindTexture(GL_TEXTURE_2D, 0);
	// spriteSheet.reset();
}

void TextureLoader::terminate() {
	//glDeleteTextures(1, &(spriteSheet->texture));//&texture);
//	delete[] data;
}


/*
 TextureResourceLoader::TextureResourceLoader() {
 logger::info("Create TextureResourceLoader");

 }

 TextureResourceLoader::~TextureResourceLoader() {
 logger::info("Destroy TextureResourceLoader");
 }

 bool TextureResourceLoader::vUseRawFile() {
 return false;
 }

 bool TextureResourceLoader::vDiscardRawBufferAfterLoad() {
 return true;
 //return false;
 }

 uintmax_t TextureResourceLoader::vGetLoadedResourceSize(char *rawBuffer,
 uintmax_t rawSize) {
 // This will keep the resource cache from allocating memory for the texture, so DirectX can manage it on it's own.
 return 0;
 }
 */

JpegTextureLoader::JpegTextureLoader(shared_ptr<ResourceCache> resourceCache) :
		TextureLoader(resourceCache) {
	// TextureLoader::TextureLoader(resourceCache);
	logger::info("Create JpegTextureLoader");
	// this->shrdPtrResourceCache = resourceCache;
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

			// rgb8_image_t
			rgb8_image_t rgb8_image = imageData->getImage();
			debugCopyImageJpg (rgb8_image);
			//FragmentShaderID = vertexShaderExtraData->getShaderId();
			image_to_texture(rgb8_image, spriteSheet);
		}

	} else if (PngResourceExtraData::CLASS_NAME.compare(
			resourceExtraData->vToString()) == 0) {

		logger::info("PNG image");
	}

	//return rgb8_image;
}

void JpegTextureLoader::activate(shared_ptr<SpriteSheet> spriteSheet) {
	// START TEXTURE
	// Now bind it to the context using the GL_TEXTURE_2D binding point
	// glBindTexture(GL_TEXTURE_2D, texture);
	// Specify the amount of storage we want to use for the texture
	TextureLoader::activate(spriteSheet);

	//int img_width = rgb8_image.width();
	//int img_height = rgb8_image.height();

	//const int texSize = 100; //128
	glTexStorage2D(GL_TEXTURE_2D,   // 2D texture
			1,               // 8 mipmap levels
			GL_RGBA32F,      // 32-bit floating-point RGBA data
			spriteSheet->getWidth(), spriteSheet->getHeight()); // 256 x 256 texels

//			img_width, img_height);       // 256 x 256 texels


	// Assume the texture is already bound to the GL_TEXTURE_2D target
	glTexSubImage2D(GL_TEXTURE_2D,  // 2D texture
			0,              // Level 0
			0, 0,           // Offset 0, 0
			spriteSheet->getWidth(), spriteSheet->getHeight(), // 256 x 256 texels, replace entire image
			//	img_width, img_height,     // 256 x 256 texels, replace entire image
			GL_RGBA,        // Four channel data
			GL_FLOAT, // Floating point data
			//GL_INT,       // Floating point data
			spriteSheet->data);       //

	// Free the memory we allocated before - \GL now has our data
//	delete[] data;
	// STOP TEXTURE
}

/*
 void JpegTextureLoader::activate() {
 // START TEXTURE
 // Now bind it to the context using the GL_TEXTURE_2D binding point
 // glBindTexture(GL_TEXTURE_2D, texture);
 // Specify the amount of storage we want to use for the texture
 TextureLoader::activate();

 int img_width = rgb8_image.width();
 int img_height = rgb8_image.height();

 //const int texSize = 100; //128
 glTexStorage2D(GL_TEXTURE_2D,   // 2D texture
 1,               // 8 mipmap levels
 GL_RGBA32F,      // 32-bit floating-point RGBA data
 img_width, img_height);       // 256 x 256 texels

 float *data = new float[img_width * img_height * 4];

 // generate_texture() is a function that fills memory with image data
 //generate_texture(data, texSize, texSize);

 image_to_texture(data);

 // Assume the texture is already bound to the GL_TEXTURE_2D target
 glTexSubImage2D(GL_TEXTURE_2D,  // 2D texture
 0,              // Level 0
 0, 0,           // Offset 0, 0
 img_width, img_height,     // 256 x 256 texels, replace entire image
 GL_RGBA,        // Four channel data
 GL_FLOAT, // Floating point data
 //GL_INT,       // Floating point data
 data);       //

 // Free the memory we allocated before - \GL now has our data
 delete[] data;
 // STOP TEXTURE
 }
 */

void JpegTextureLoader::image_to_texture(rgb8_image_t rgb8_image,
		shared_ptr<SpriteSheet> spriteSheet) {

	int img_width = rgb8_image.width();
	int img_height = rgb8_image.height();

	// spriteSheet = make_shared<SpriteSheet>(img_width, img_height);
	spriteSheet->setWidth(img_width);
	spriteSheet->setHeight(img_height);

	spriteSheet->data = new float[img_width * img_height * 4];
//	data = new float[spriteSheet->getWidth() * spriteSheet->getHeight() * 4];


	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {

			//for (int y = 0; y < spriteSheet->getHeight(); y++) {
			//for (int x = 0; x < spriteSheet->getWidth(); x++) {
			rgb8_pixel_t px = *const_view(rgb8_image).at(x, y);

			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 0] =
					(float) px[0]
					/ 255;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 1] =
					(float) px[1]
					/ 255;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 2] =
					(float) px[2]
					/ 255;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 3] =
					1.0f;

		}
	}

}

/*
void JpegTextureLoader::image_to_texture(float *data) {

	int img_width = rgb8_image.width();
	int img_height = rgb8_image.height();

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {
			rgb8_pixel_t px = *const_view(rgb8_image).at(x, y);

			data[((img_height - y - 1) * img_width + x) * 4 + 0] = (float) px[0]
					/ 255;
			data[((img_height - y - 1) * img_width + x) * 4 + 1] = (float) px[1]
					/ 255;
			data[((img_height - y - 1) * img_width + x) * 4 + 2] = (float) px[2]
					/ 255;
			data[((img_height - y - 1) * img_width + x) * 4 + 3] = 1.0f;

		}
	}

}
 */

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

	/*
	 // TEMPORARY COMMENTED
	 namespace bg = boost::gil;

	 bg::read_image(
	 "../Watermill/assets/graphics/temp_t009_jpeg_gil_texture_view.jpg",
	 rgb8_image, bg::jpeg_tag { });
	 //	bg::read_image("../../../assets/graphics/TempT009jpegGilTextureView.jpg",
	 //			rgb8_image, bg::jpeg_tag { });

	 cout << "Width: " << rgb8_image.width() << "; Height: "
	 << rgb8_image.height() << endl;
	 // Width: 136; Height: 98

	 bg::rgb8_pixel_t px = *const_view(rgb8_image).at(5, 10);
	 cout << "The pixel at 5,10 is " << (int) px[0] << ',' << (int) px[1] << ','
	 << (int) px[2] << endl;

	 // Scale the image to 100x100 pixels using bilinear resampling
	 bg::rgb8_image_t square100x100(100, 100);

	 bg::resize_view(bg::const_view(rgb8_image), bg::view(square100x100),
	 bg::bilinear_sampler { });

	 bg::write_view(
	 "../Watermill/assets/graphics/temp_t009_jpeg_gil_texture_view-resized.jpg",
	 bg::const_view(square100x100), bg::jpeg_tag { });
	 */

}

//////////////////////////////////

PngTextureLoader::PngTextureLoader(shared_ptr<ResourceCache> resourceCache) :
		TextureLoader(resourceCache) {
	// TextureLoader::TextureLoader(resourceCache);
	logger::info("Create PngTextureLoader");
	// this->shrdPtrResourceCache = resourceCache;
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

			// rgb8_image_t
			rgba8_image_t rgba8_image = imageData->getImage();
			debugCopyImagePng(rgba8_image);
			//FragmentShaderID = vertexShaderExtraData->getShaderId();
			image_to_texture(rgba8_image, spriteSheet);

		}
	}

	//return rgb8_image;
}

void PngTextureLoader::activate(std::shared_ptr<SpriteSheet> spriteSheet) {
	// START TEXTURE
	// Now bind it to the context using the GL_TEXTURE_2D binding point
	// glBindTexture(GL_TEXTURE_2D, texture);
	// Specify the amount of storage we want to use for the texture
	TextureLoader::activate(spriteSheet);

	//int img_width = rgba8_image.width();
	//int img_height = rgba8_image.height();

	//const int texSize = 100; //128
	glTexStorage2D(GL_TEXTURE_2D,   // 2D texture
			1,               // 8 mipmap levels
			GL_RGBA32F,      // 32-bit floating-point RGBA data
			spriteSheet->getWidth(), spriteSheet->getHeight()); // 256 x 256 texels
//	img_width, img_height);       // 256 x 256 texels

	//float *data = new float[img_width * img_height * 4];

	// generate_texture() is a function that fills memory with image data
	//generate_texture(data, texSize, texSize);

	//image_to_texture(data);

	// Assume the texture is already bound to the GL_TEXTURE_2D target
	glTexSubImage2D(GL_TEXTURE_2D,  // 2D texture
			0,              // Level 0
			0, 0,           // Offset 0, 0
			spriteSheet->getWidth(), spriteSheet->getHeight(), // 256 x 256 texels, replace entire image
			//img_width, img_height,     // 256 x 256 texels, replace entire image
			GL_RGBA,        // Four channel data
			GL_FLOAT, // Floating point data
			//GL_INT,       // Floating point data
			spriteSheet->data);
	//data);       //

	// Free the memory we allocated before - \GL now has our data
	// delete[] data;
	// STOP TEXTURE
}

//void PngTextureLoader::image_to_texture(float *data) {
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
					(float) px[0]
					/ 255;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 1] =
					(float) px[1]
					/ 255;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 2] =
					(float) px[2]
					/ 255;
//			data[((img_height - y - 1) * img_width + x) * 4 + 3] = 1.0f;
			spriteSheet->data[((img_height - y - 1) * img_width + x) * 4 + 3] =
					(float) px[3]
					/ 255;

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

	/*
	 // TEMPORARY COMMENTED
	 namespace bg = boost::gil;

	 bg::read_image(
	 "../Watermill/assets/graphics/temp_t009_jpeg_gil_texture_view.jpg",
	 rgb8_image, bg::jpeg_tag { });
	 //	bg::read_image("../../../assets/graphics/TempT009jpegGilTextureView.jpg",
	 //			rgb8_image, bg::jpeg_tag { });

	 cout << "Width: " << rgb8_image.width() << "; Height: "
	 << rgb8_image.height() << endl;
	 // Width: 136; Height: 98

	 bg::rgb8_pixel_t px = *const_view(rgb8_image).at(5, 10);
	 cout << "The pixel at 5,10 is " << (int) px[0] << ',' << (int) px[1] << ','
	 << (int) px[2] << endl;

	 // Scale the image to 100x100 pixels using bilinear resampling
	 bg::rgb8_image_t square100x100(100, 100);

	 bg::resize_view(bg::const_view(rgb8_image), bg::view(square100x100),
	 bg::bilinear_sampler { });

	 bg::write_view(
	 "../Watermill/assets/graphics/temp_t009_jpeg_gil_texture_view-resized.jpg",
	 bg::const_view(square100x100), bg::jpeg_tag { });
	 */

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
