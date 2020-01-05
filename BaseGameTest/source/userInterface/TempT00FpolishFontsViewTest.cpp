/*
 * TempT00FpolishFontsViewTest.cpp
 *
 *  Created on: 1 maj 2019
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

#include "../main/MainTest.h"
//#include "ActorFactoryTest.h"

//#include "../../../BaseGame/source/gameInitialization/GameCodeApp.h"

#include "../../../BaseGame/source/gameInitialization/InitOptions.h"
//#include "../../source/gameLogic/BaseGameLogic.h"
#include "../../../BaseGame/source/utilities/Templates.h"
#include "../../../BaseGame/source/debugging/Logger.h"
#include "../../../BaseGame/source/resourceCache/IResourceFile.h"
#include "../../../BaseGame/source/resourceCache/DevelopmentResourceFolder.h"
#include "../../../BaseGame/source/resourceCache/DevelopmentResourceUnzipFile.h"
#include "../../../BaseGame/source/resourceCache/ResourceZipFile.h"

// --------- START
#include "../testGame/TestGame.h"
#include "../testGame/TestGameLogic.h"
#include "../../../BaseGame/source/gameInitialization/VideoSystemGLFW.h"
#include "../../../BaseGame/source/userInterface/TempT00FpolishFontsView.h"
#include "../../../BaseGame/source/userInterface/TempT009jpegGilTextureView.h"
#include "../../../BaseGame/source/userInterface/TempT004figuresView.h"
#include "../../../BaseGame/source/userInterface/TempT00DpngGilScanlineView.h"
#include "../../../BaseGame/source/userInterface/TempT00FpolishFontsView.h"
#include "../../../BaseGame/source/userInterface/TempCombinedView.h"



#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/graphics3d/ShaderResourceLoader.h"
#include "../../../BaseGame/source/graphics3d/TextureResourceLoader.h"
#include "../../../BaseGame/source/graphics3d/FreeTypeResourceLoader.h"

// --------- STOP

// #define BOOST_TEST_MODULE StringUtilsTestModule
#include <boost/test/unit_test.hpp>

using base_game::InitOptions;
using base_game::IResourceFile;

namespace templates = base_game::templates;
namespace logger = base_game::logger;

// -------- START
namespace temp_t00f_polish_fonts_view = base_game::temp_t00f_polish_fonts_view;
namespace temp_t004_figures_view = base_game::temp_t004_figures_view;
namespace temp_t009_jpeg_gil_texture_view = base_game::temp_t009_jpeg_gil_texture_view;
namespace temp_t00f_polish_fonts_view = base_game::temp_t00f_polish_fonts_view;
namespace temp_t00d_png_gil_scanline_view = base_game::temp_t00d_png_gil_scanline_view;
namespace temp_combined_view = base_game::temp_combined_view;

namespace vertex_shader_resource_loader = base_game::vertex_shader_resource_loader;
namespace fragment_shader_resource_loader = base_game::fragment_shader_resource_loader;
namespace jpeg_resource_loader = base_game::jpeg_resource_loader;
namespace png_resource_loader = base_game::png_resource_loader;
namespace free_type_resource_loader = base_game::free_type_resource_loader;

using base_game::IGameView;
using base_game::VideoSystemGLFW;

using base_game::ResourceCache;

// -------- STOP

using base_game::DevelopmentResourceFolder;
using base_game::DevelopmentResourceUnzipFile;
using base_game::ResourceZipFile;

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::stringstream;

using boost::optional;
using boost::uintmax_t;

namespace unit_test = boost::unit_test;

namespace base_game_test {

struct TempT00FpolishFontsViewFixture {
	shared_ptr<IResourceFile> zipResourceFile;
	shared_ptr<IResourceFile> zip2ResourceFile;
	shared_ptr<IResourceFile> unzipResourceFile;
	shared_ptr<IResourceFile> unzip2ResourceFile;

	// --- START
	InitOptions* pInitOptions;
	shared_ptr<IResourceFile> resourceFolder; // Will be removed in ResourceCache destructor

	shared_ptr<ResourceCache> shrdPtrResourceCache;

	TestGame* pTestGame;

	VideoSystemGLFW *videoSystemGLFW = nullptr;
	//IGameView* gameView = nullptr;
	shared_ptr<IGameView> gameView;


// ---------STOP

	virtual shared_ptr<IResourceFile> createIResourceFile()=0;

	/*
	 virtual shared_ptr<IResourceFile> createIResourceFile() {
	 return shared_ptr<IResourceFile>();
	 }
	 */

	void setup() {
		logger::info("setup TempT00FpolishFontsViewFixture");

		pInitOptions = new InitOptions;
		resourceFolder = this->createIResourceFile();

		shrdPtrResourceCache = make_shared<ResourceCache>(
				pInitOptions->getAssetsFolder(), 50, resourceFolder);

		if (!shrdPtrResourceCache->init()) {
			logger::warning(
					"Failed to initialize resource cache!  Are your paths set up correctly?");
		}

		shrdPtrResourceCache->registerLoader(
				vertex_shader_resource_loader::createVertexShaderResourceLoader());
		shrdPtrResourceCache->registerLoader(
				fragment_shader_resource_loader::createFragmentShaderResourceLoader());
		shrdPtrResourceCache->registerLoader(
				jpeg_resource_loader::createJpegResourceLoader());
		shrdPtrResourceCache->registerLoader(
				png_resource_loader::createPngResourceLoader());
		shrdPtrResourceCache->registerLoader(
				free_type_resource_loader::createFreeTypeResourceLoader());


		pTestGame = new TestGame;

		pTestGame->m_pGame = new TestGameLogic();
		base_game::g_pApp = pTestGame;

		videoSystemGLFW = new VideoSystemGLFW;
		//gameView = temp_t00f_polish_fonts_view::getView(false);
		//		gameView = temp_t004_figures_view::getView(false,
		//			pInitOptions->getAssetsFolder());


	}

	void teardown() {
		logger::info("teardown TempT00FpolishFontsViewFixture");

		shrdPtrResourceCache.reset();
		resourceFolder.reset();

		templates::safe_delete<InitOptions>(pInitOptions);
		gameView.reset();
		//templates::safe_delete<IGameView>(gameView);
		templates::safe_delete<VideoSystemGLFW>(videoSystemGLFW);
		templates::safe_delete<TestGame>(pTestGame);
	}

	TempT00FpolishFontsViewFixture() {
		BOOST_TEST_MESSAGE("Setting up TempT00FpolishFontsViewFixture");
		logger::info("Create TempT00FpolishFontsViewFixture");
	}

	virtual ~TempT00FpolishFontsViewFixture() {
		BOOST_TEST_MESSAGE("Tearing down TempT00FpolishFontsViewFixture");

		logger::info("Destroy TempT00FpolishFontsViewFixture");
//		logger::destroy();
	}

};

struct TempT00FpolishFontsViewDevFolderFixture: public TempT00FpolishFontsViewFixture {
	TempT00FpolishFontsViewDevFolderFixture() {
		logger::info("Create TempT00FpolishFontsViewDevFolderFixture");

	}

	~TempT00FpolishFontsViewDevFolderFixture() {
		logger::info("Destroy TempT00FpolishFontsViewDevFolderFixture");

	}

	void setup() {
		logger::info("setup TempT00FpolishFontsViewDevFolderFixture");
		TempT00FpolishFontsViewFixture::setup();
	}

	void teardown() {
		logger::info("teardown TempT00FpolishFontsViewDevFolderFixture");
		TempT00FpolishFontsViewFixture::teardown();
	}

	virtual shared_ptr<IResourceFile> createIResourceFile() {
		shared_ptr<IResourceFile> resourceFolder = make_shared<
				DevelopmentResourceFolder>(pInitOptions->getRootFolder(),
				pInitOptions->getAssetsFolder());
		return resourceFolder;
	}
};

struct TempT00FpolishFontsViewUnzipFileFixture: public TempT00FpolishFontsViewFixture {
	TempT00FpolishFontsViewUnzipFileFixture() {
		logger::info("Create TempT00FpolishFontsViewUnzipFileFixture");

	}

	~TempT00FpolishFontsViewUnzipFileFixture() {
		logger::info("Destroy TempT00FpolishFontsViewUnzipFileFixture");

	}

	void setup() {
		logger::info("setup TempT00FpolishFontsViewUnzipFileFixture");
		TempT00FpolishFontsViewFixture::setup();
	}

	void teardown() {
		logger::info("teardown TempT00FpolishFontsViewUnzipFileFixture");
		TempT00FpolishFontsViewFixture::teardown();
	}

	virtual shared_ptr<IResourceFile> createIResourceFile() {
		shared_ptr<IResourceFile> resourceFolder = make_shared<
				DevelopmentResourceUnzipFile>(pInitOptions->getRootFolder(),
				IResourceFile::ASSETS_UNZIP_FILE);
		return resourceFolder;
	}
};

struct TempT00FpolishFontsViewZipFileFixture: public TempT00FpolishFontsViewFixture {
	TempT00FpolishFontsViewZipFileFixture() {
		logger::info("Create TempT00FpolishFontsViewZipFileFixture");

	}

	~TempT00FpolishFontsViewZipFileFixture() {
		logger::info("Destroy TempT00FpolishFontsViewZipFileFixture");

	}

	void setup() {
		logger::info("setup TempT00FpolishFontsViewZipFileFixture");
		TempT00FpolishFontsViewFixture::setup();
	}

	void teardown() {
		logger::info("teardown TempT00FpolishFontsViewZipFileFixture");
		TempT00FpolishFontsViewFixture::teardown();
	}

	virtual shared_ptr<IResourceFile> createIResourceFile() {
		shared_ptr<IResourceFile> resourceFolder = make_shared<ResourceZipFile>(
				pInitOptions->getRootFolder(), IResourceFile::ASSETS_ZIP_FILE);
		return resourceFolder;
	}
};

BOOST_FIXTURE_TEST_SUITE(TempT00FpolishFontsViewDevFolderSuite, TempT00FpolishFontsViewDevFolderFixture)

BOOST_AUTO_TEST_CASE(viewDevFolder, * unit_test::enable_if<true>()) {
//BOOST_AUTO_TEST_CASE(viewDevFolder, * unit_test::enable_if<false>()) {
//BOOST_AUTO_TEST_CASE(viewDevFolder, * unit_test::enabled()) {

	videoSystemGLFW->initialize();

	// gameView = temp_t004_figures_view::getView(false, shrdPtrResourceCache);
	//gameView = temp_t009_jpeg_gil_texture_view::getView(false,
	//	shrdPtrResourceCache);
	//gameView = temp_t00d_png_gil_scanline_view::getView(false,
	//		shrdPtrResourceCache);

	//gameView = temp_t00f_polish_fonts_view::getView(false,
	//		shrdPtrResourceCache);

	gameView = temp_combined_view::getView(false, shrdPtrResourceCache);

	pTestGame->m_pGame->tempAddView(gameView);

	gameView->vActivate();

	videoSystemGLFW->mainLoop();

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(TempT00FpolishFontsViewUnzipFileSuite, TempT00FpolishFontsViewUnzipFileFixture)

//BOOST_AUTO_TEST_CASE(viewUnzipFile, * unit_test::enable_if<true>()) {
BOOST_AUTO_TEST_CASE(viewUnzipFile, * unit_test::enable_if<false>()) {
//BOOST_AUTO_TEST_CASE(viewUnzipFile, * unit_test::enabled()) {

	videoSystemGLFW->initialize();

	// gameView = temp_t004_figures_view::getView(false, shrdPtrResourceCache);
//	gameView = temp_t009_jpeg_gil_texture_view::getView(false,
//			shrdPtrResourceCache);
//	gameView = temp_t00d_png_gil_scanline_view::getView(false,
//			shrdPtrResourceCache);

	gameView = temp_t00f_polish_fonts_view::getView(false,
			shrdPtrResourceCache);


	pTestGame->m_pGame->tempAddView(gameView);

	gameView->vActivate();

	videoSystemGLFW->mainLoop();

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(TempT00FpolishFontsViewZipFileSuite, TempT00FpolishFontsViewZipFileFixture)

//BOOST_AUTO_TEST_CASE(viewZipFile, * unit_test::enable_if<true>()) {
BOOST_AUTO_TEST_CASE(viewZipFile, * unit_test::enable_if<false>()) {
//BOOST_AUTO_TEST_CASE(viewZipFile, * unit_test::enabled()) {

	videoSystemGLFW->initialize();

	// gameView = temp_t004_figures_view::getView(false, shrdPtrResourceCache);
	gameView = temp_t009_jpeg_gil_texture_view::getView(false,
			shrdPtrResourceCache);
//	gameView = temp_t00d_png_gil_scanline_view::getView(false,
//			shrdPtrResourceCache);
//	gameView = temp_t00f_polish_fonts_view::getView(false,
//			shrdPtrResourceCache);

	pTestGame->m_pGame->tempAddView(gameView);

	gameView->vActivate();

	videoSystemGLFW->mainLoop();

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

}
