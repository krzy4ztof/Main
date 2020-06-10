/*
 * MainMenuViewTest.cpp
 *
 *  Created on: 1 maj 2019
 *      Author: Krzysztof
 */

#define BOOST_TEST_DYN_LINK

//#include "../main/MainTest.h"
#include "../main/MainWatermillTest.h"

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
//#include "../testGame/TestGame.h"
//#include "../testGame/TestGameLogic.h"
#include "../../../WatermillBase/source/watermillGame/WatermillGame.h"
#include "../../../WatermillBase/source/watermillGame/WatermillLogic.h"

#include "../../../BaseGame/source/gameInitialization/VideoSystemGLFW.h"
/*
#include "../../../BaseGame/source/userInterface/TempT00FpolishFontsView.h"
#include "../../../BaseGame/source/userInterface/TempT009jpegGilTextureView.h"
#include "../../../BaseGame/source/userInterface/TempT004figuresView.h"
#include "../../../BaseGame/source/userInterface/TempT00DpngGilScanlineView.h"
#include "../../../BaseGame/source/userInterface/TempT00FpolishFontsView.h"
#include "../../../BaseGame/source/userInterface/TempCombinedView.h"
 */
#include "../../../WatermillBase/source/userInterface/MainMenuView.h"
//#include "../../../WatermillBase/source/userInterface/WatermillHumanView.h"



#include "../../../BaseGame/source/resourceCache/ResourceCache.h"
#include "../../../BaseGame/source/graphics3d/ShaderResourceLoader.h"
#include "../../../BaseGame/source/graphics3d/TextureResourceLoader.h"
#include "../../../BaseGame/source/graphics3d/FreeTypeResourceLoader.h"
#include "../../../BaseGame/source/graphics3d/OpenGLRenderer.h"

// --------- STOP

// #define BOOST_TEST_MODULE StringUtilsTestModule
#include <boost/test/unit_test.hpp>

using std::stringstream;

using base_game::InitOptions;
using base_game::IResourceFile;

namespace templates = base_game::templates;
namespace logger = base_game::logger;

// -------- START
//namespace temp_t00f_polish_fonts_view = base_game::temp_t00f_polish_fonts_view;
//namespace temp_t004_figures_view = base_game::temp_t004_figures_view;
//namespace temp_t009_jpeg_gil_texture_view = base_game::temp_t009_jpeg_gil_texture_view;
//namespace temp_t00f_polish_fonts_view = base_game::temp_t00f_polish_fonts_view;
//namespace temp_t00d_png_gil_scanline_view = base_game::temp_t00d_png_gil_scanline_view;
//namespace temp_combined_view = base_game::temp_combined_view;

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
using base_game::OpenGLRenderer;
/*
using base_game::TempT004figuresView;
using base_game::TempT009jpegGilTextureView;
using base_game::TempT00FpolishFontsView;
using base_game::TempT00DpngGilScanlineView;
using base_game::TempCombinedView;
 */
using watermill_base::MainMenuView;
using watermill_base::WatermillGame;
using watermill_base::WatermillLogic;
namespace unit_test = boost::unit_test;

using std::shared_ptr;
using std::make_shared;

namespace watermill_base_test {

struct MainMenuViewFixture {
	shared_ptr<IResourceFile> zipResourceFile;
	shared_ptr<IResourceFile> zip2ResourceFile;
	shared_ptr<IResourceFile> unzipResourceFile;
	shared_ptr<IResourceFile> unzip2ResourceFile;

	// --- START
	InitOptions* pInitOptions;
	shared_ptr<IResourceFile> resourceFolder; // Will be removed in ResourceCache destructor

	shared_ptr<ResourceCache> shrdPtrResourceCache;

	//TestGame* pTestGame;
	WatermillGame *pWatermillGame;

	// VideoSystemGLFW *videoSystemGLFW = nullptr;
	shared_ptr<VideoSystemGLFW> videoSystemGLFW;

	shared_ptr<OpenGLRenderer> openGLRenderer;
	//IGameView* gameView = nullptr;
	shared_ptr<IGameView> gameView;
	shared_ptr<IGameView> gameView2;


// ---------STOP

	virtual shared_ptr<IResourceFile> createIResourceFile()=0;

	/*
	 virtual shared_ptr<IResourceFile> createIResourceFile() {
	 return shared_ptr<IResourceFile>();
	 }
	 */

	void setup() {
		stringstream ss;
		logger::info("setup MainMenuViewFixture");

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


		//pTestGame = new TestGame;
		pWatermillGame = new WatermillGame;

		//videoSystemGLFW = new VideoSystemGLFW;
		videoSystemGLFW = make_shared<VideoSystemGLFW>();

		openGLRenderer = make_shared<OpenGLRenderer>(videoSystemGLFW);

		//pTestGame->m_pGame = new TestGameLogic(openGLRenderer);
		pWatermillGame->m_pGame = new WatermillLogic(openGLRenderer);
		// base_game::g_pApp = pTestGame;
		base_game::g_pApp = pWatermillGame;


		//gameView = temp_t00f_polish_fonts_view::getView(false);
		//		gameView = temp_t004_figures_view::getView(false,
		//			pInitOptions->getAssetsFolder());

		ss << "resourceCacheUseCount: " << shrdPtrResourceCache.use_count();
		logger::info (ss);
		logger::info("END SETUP");


	}

	void teardown() {
		stringstream ss;
		logger::info("teardown MainMenuViewFixture");

		ss << "resourceCacheUseCount: " << shrdPtrResourceCache.use_count();
		logger::info(ss);


		gameView2.reset();
		ss << "resourceCacheUseCount: " << shrdPtrResourceCache.use_count();
		logger::info(ss);

		gameView.reset();
		ss << "resourceCacheUseCount: " << shrdPtrResourceCache.use_count();
		logger::info(ss);

		//templates::safe_delete<IGameView>(gameView);
		openGLRenderer.reset();
		// templates::safe_delete<VideoSystemGLFW>(videoSystemGLFW);
		videoSystemGLFW.reset();

		//templates::safe_delete<TestGame>(pTestGame);
		templates::safe_delete<WatermillGame>(pWatermillGame);

		ss << "resourceCacheUseCount: " << shrdPtrResourceCache.use_count();
		logger::info(ss);

		shrdPtrResourceCache.reset();
		resourceFolder.reset();
		templates::safe_delete<InitOptions>(pInitOptions);

		ss << "resourceCacheUseCount: " << shrdPtrResourceCache.use_count();
		logger::info(ss);
		logger::info("END TearDown");
	}

	MainMenuViewFixture() {
		BOOST_TEST_MESSAGE("Setting up MainMenuViewFixture");
		logger::info("Create TempT00FpolishFontsViewFixture");
	}

	virtual ~MainMenuViewFixture() {
		BOOST_TEST_MESSAGE("Tearing down MainMenuViewFixture");

		logger::info("Destroy MainMenuViewFixture");
//		logger::destroy();
	}

};

struct MainMenuViewDevFolderFixture: public MainMenuViewFixture {
	MainMenuViewDevFolderFixture() {
		logger::info("Create MainMenuViewDevFolderFixture");

	}

	~MainMenuViewDevFolderFixture() {
		logger::info("Destroy MainMenuViewDevFolderFixture");

	}

	void setup() {
		logger::info("setup MainMenuViewDevFolderFixture");
		MainMenuViewFixture::setup();
	}

	void teardown() {
		logger::info("teardown MainMenuViewDevFolderFixture");
		MainMenuViewFixture::teardown();
	}

	virtual shared_ptr<IResourceFile> createIResourceFile() {
		shared_ptr<IResourceFile> resourceFolder = make_shared<
				DevelopmentResourceFolder>(pInitOptions->getRootFolder(),
				pInitOptions->getAssetsFolder());
		return resourceFolder;
	}
};

struct MainMenuViewUnzipFileFixture: public MainMenuViewFixture {
	MainMenuViewUnzipFileFixture() {
		logger::info("Create MainMenuViewUnzipFileFixture");

	}

	~MainMenuViewUnzipFileFixture() {
		logger::info("Destroy MainMenuViewUnzipFileFixture");

	}

	void setup() {
		logger::info("setup MainMenuViewUnzipFileFixture");
		MainMenuViewFixture::setup();
	}

	void teardown() {
		logger::info("teardown MainMenuViewUnzipFileFixture");
		MainMenuViewFixture::teardown();
	}

	virtual shared_ptr<IResourceFile> createIResourceFile() {
		shared_ptr<IResourceFile> resourceFolder = make_shared<
				DevelopmentResourceUnzipFile>(pInitOptions->getRootFolder(),
				IResourceFile::ASSETS_UNZIP_FILE);
		return resourceFolder;
	}
};

struct MainMenuViewZipFileFixture: public MainMenuViewFixture {
	MainMenuViewZipFileFixture() {
		logger::info("Create MainMenuViewZipFileFixture");

	}

	~MainMenuViewZipFileFixture() {
		logger::info("Destroy MainMenuViewZipFileFixture");

	}

	void setup() {
		logger::info("setup MainMenuViewZipFileFixture");
		MainMenuViewFixture::setup();
	}

	void teardown() {
		logger::info("teardown MainMenuViewZipFileFixture");
		MainMenuViewFixture::teardown();
	}

	virtual shared_ptr<IResourceFile> createIResourceFile() {
		shared_ptr<IResourceFile> resourceFolder = make_shared<ResourceZipFile>(
				pInitOptions->getRootFolder(), IResourceFile::ASSETS_ZIP_FILE);
		return resourceFolder;
	}
};

BOOST_FIXTURE_TEST_SUITE(MainMenuViewDevFolderSuite, MainMenuViewDevFolderFixture)

BOOST_AUTO_TEST_CASE(viewDevFolder, * unit_test::enable_if<true>()) {
//BOOST_AUTO_TEST_CASE(viewDevFolder, * unit_test::enable_if<false>()) {
//BOOST_AUTO_TEST_CASE(viewDevFolder, * unit_test::enabled()) {

	videoSystemGLFW->initialize();

	//gameView = temp_t004_figures_view::getView(false, shrdPtrResourceCache,
	//		openGLRenderer);
	//gameView = temp_t009_jpeg_gil_texture_view::getView(false,
	//		shrdPtrResourceCache, openGLRenderer);
	//gameView = temp_t00d_png_gil_scanline_view::getView(false,
	//		shrdPtrResourceCache, openGLRenderer);

	//gameView = temp_t00f_polish_fonts_view::getView(false,
	//		shrdPtrResourceCache,
	//		openGLRenderer);

	//gameView = temp_combined_view::getView(false, shrdPtrResourceCache, openGLRenderer);

	//pTestGame->m_pGame->tempAddView(gameView);
	//gameView = make_shared<TempT004figuresView>(shrdPtrResourceCache,
	//		openGLRenderer);
	//gameView = make_shared<TempT009jpegGilTextureView>(shrdPtrResourceCache,
	//		openGLRenderer);
	//gameView = make_shared<TempT00DpngGilScanlineView>(shrdPtrResourceCache,
	//		openGLRenderer);
	gameView = make_shared < MainMenuView
			> (shrdPtrResourceCache,
			openGLRenderer);
	//gameView = make_shared<TempCombinedView>(shrdPtrResourceCache,
	//		openGLRenderer);

	gameView->tempVLoadGameDelegate();
	//pTestGame->m_pGame->vAddView(gameView);
	pWatermillGame->m_pGame->vAddView(gameView);
	//pTestGame->m_pGame->removeAllViews();
	pWatermillGame->m_pGame->removeAllViews();

	//gameView2 = make_shared<TempT004figuresView>(shrdPtrResourceCache,
	//		openGLRenderer);
	//gameView2 = make_shared<TempT009jpegGilTextureView>(shrdPtrResourceCache,
	//		openGLRenderer);
	//gameView2 = make_shared<TempT00DpngGilScanlineView>(shrdPtrResourceCache,
	//		openGLRenderer);
	gameView2 = make_shared < MainMenuView
			> (shrdPtrResourceCache,
			openGLRenderer);

	//gameView2 = make_shared<TempCombinedView>(shrdPtrResourceCache,
	//		openGLRenderer);

	gameView2->tempVLoadGameDelegate();
	//pTestGame->m_pGame->vAddView(gameView2);
	pWatermillGame->m_pGame->vAddView(gameView2);


	// gameView->vActivate();

	videoSystemGLFW->mainLoop();

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(MainMenuViewUnzipFileSuite, MainMenuViewUnzipFileFixture)

//BOOST_AUTO_TEST_CASE(viewUnzipFile, * unit_test::enable_if<true>()) {
BOOST_AUTO_TEST_CASE(viewUnzipFile, * unit_test::enable_if<false>()) {
//BOOST_AUTO_TEST_CASE(viewUnzipFile, * unit_test::enabled()) {

	videoSystemGLFW->initialize();

	// gameView = temp_t004_figures_view::getView(false, shrdPtrResourceCache, openGLRenderer);
//	gameView = temp_t009_jpeg_gil_texture_view::getView(false,
//			shrdPtrResourceCache, openGLRenderer);
//	gameView = temp_t00d_png_gil_scanline_view::getView(false,
//			shrdPtrResourceCache, openGLRenderer);

	//gameView = temp_t00f_polish_fonts_view::getView(false,
	//		shrdPtrResourceCache,
	//		openGLRenderer);


	//pTestGame->m_pGame->tempAddView(gameView);
	//gameView->vActivate();

	//gameView = make_shared<TempT004figuresView>(shrdPtrResourceCache,
	//		openGLRenderer);
//	gameView = make_shared<TempT009jpegGilTextureView>(shrdPtrResourceCache,
//			openGLRenderer);
	//gameView = make_shared<TempT00DpngGilScanlineView>(shrdPtrResourceCache,
	//		openGLRenderer);
	gameView = make_shared < MainMenuView
			> (shrdPtrResourceCache,
			openGLRenderer);
	//gameView = make_shared<TempCombinedView>(shrdPtrResourceCache,
	//		openGLRenderer);

	gameView->tempVLoadGameDelegate();
	//pTestGame->m_pGame->vAddView(gameView);
	pWatermillGame->m_pGame->vAddView(gameView);


	videoSystemGLFW->mainLoop();

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(MainMenuViewZipFileSuite, MainMenuViewZipFileFixture)

//BOOST_AUTO_TEST_CASE(viewZipFile, * unit_test::enable_if<true>()) {
BOOST_AUTO_TEST_CASE(viewZipFile, * unit_test::enable_if<false>()) {
//BOOST_AUTO_TEST_CASE(viewZipFile, * unit_test::enabled()) {

	videoSystemGLFW->initialize();

	// gameView = temp_t004_figures_view::getView(false, shrdPtrResourceCache, openGLRenderer);
	//gameView = temp_t009_jpeg_gil_texture_view::getView(false,
	//		shrdPtrResourceCache, openGLRenderer);
//	gameView = temp_t00d_png_gil_scanline_view::getView(false,
//			shrdPtrResourceCache, openGLRenderer);
//	gameView = temp_t00f_polish_fonts_view::getView(false,
//			shrdPtrResourceCache, openGLRenderer);

	//pTestGame->m_pGame->tempAddView(gameView);
	//gameView->vActivate();
	//gameView = make_shared<TempT004figuresView>(shrdPtrResourceCache,
	//		openGLRenderer);
	//gameView = make_shared<TempT009jpegGilTextureView>(shrdPtrResourceCache,
	//		openGLRenderer);
	//gameView = make_shared<TempT00DpngGilScanlineView>(shrdPtrResourceCache,
	//		openGLRenderer);
	gameView = make_shared < MainMenuView
			> (shrdPtrResourceCache,
			openGLRenderer);
	//gameView = make_shared<TempCombinedView>(shrdPtrResourceCache,
	//		openGLRenderer);

	gameView->tempVLoadGameDelegate();
	//pTestGame->m_pGame->vAddView(gameView);
	pWatermillGame->m_pGame->vAddView(gameView);


	videoSystemGLFW->mainLoop();

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

}
