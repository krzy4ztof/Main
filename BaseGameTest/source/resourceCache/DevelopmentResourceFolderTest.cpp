/*
 * DevelopmentResourceFolderTest.cpp
 *
 *  Created on: 15 wrz 2018
 *      Author: Krzysztof
 */

/*
 * ResourceCacheTest.cpp
 *
 *  Created on: 13 sie 2018
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
//#include "../../../BaseGame/source/resourceCache/XmlResourceLoader.h"
//#include "../../../BaseGame/source/resourceCache/TextFileLoader.h"
//#include "../../../BaseGame/source/resourceCache/Resource.h"
//#include "../../../BaseGame/source/resourceCache/ResourceHandle.h"

// #define BOOST_TEST_MODULE StringUtilsTestModule
#include <boost/test/unit_test.hpp>
//#include <boost/optional.hpp> // boost::optional
//#include <boost/cstdint.hpp> // boost::uintmax_t
//#include <memory> // shared_ptr, weak_ptr
//#include <sstream>      // std::stringstream
//#include <string> // string

using base_game::InitOptions;
using base_game::IResourceFile;
//using base_game::ResourceCache;
//using base_game::Resource;
//using base_game::ResourceHandle;

//using base_game::BaseGameLogic;
namespace templates = base_game::templates;
namespace logger = base_game::logger;
//namespace xml_resource_loader = base_game::xml_resource_loader;
//namespace text_file_loader = base_game::text_file_loader;

//using base_game::templates::safe_delete;
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

struct DevelopmentResourceFolderFixture {

	InitOptions* pInitOptions;
	shared_ptr<IResourceFile> resourceFolder; // Will be removed in ResourceCache destructor
	shared_ptr<IResourceFile> zipResourceFile;
	shared_ptr<IResourceFile> zip2ResourceFile;
	shared_ptr<IResourceFile> unzipResourceFile;
	shared_ptr<IResourceFile> unzip2ResourceFile;

	DevelopmentResourceFolderFixture() {
		BOOST_TEST_MESSAGE("Setting up DevelopmentResourceFolderFixture");

		logger::info("Create DevelopmentResourceFolderFixture");

		pInitOptions = new InitOptions;

		resourceFolder = make_shared<DevelopmentResourceFolder>(
				pInitOptions->getRootFolder(), pInitOptions->getAssetsFolder());
	}

	virtual ~DevelopmentResourceFolderFixture() {
		BOOST_TEST_MESSAGE("Tearing down DevelopmentResourceFolderFixture");

		resourceFolder.reset();
		zipResourceFile.reset();
		zip2ResourceFile.reset();
		unzipResourceFile.reset();
		unzip2ResourceFile.reset();

//		templates::safe_delete<IResourceFile>(pZipFile);
		templates::safe_delete<InitOptions>(pInitOptions);

		logger::info("Destroy ResourceCacheZipFileFixture");
//		logger::destroy();
	}

};

BOOST_FIXTURE_TEST_SUITE(DevelopmentResourceFolderSuite, DevelopmentResourceFolderFixture)

//BOOST_AUTO_TEST_CASE(folderToFolder, * unit_test::enable_if<DEVELOPMENT_RESOURCE_FOLDER_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(folderToFolder, * unit_test::enable_if<true>()) {
BOOST_AUTO_TEST_CASE(folderToFolder, * unit_test::enable_if<false>()) {
	resourceFolder->vOpen();
	resourceFolder->vSave(IResourceFile::ASSETS_SAVE_MODE_FOLDER,
			IResourceFile::ASSETS_FOLDER_TO_FOLDER);
	BOOST_TEST(true);
}

//BOOST_AUTO_TEST_CASE(folderToUnzipToFolder, * unit_test::enable_if<DEVELOPMENT_RESOURCE_FOLDER_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(folderToUnzipToFolder, * unit_test::enable_if<true>()) {
BOOST_AUTO_TEST_CASE(folderToUnzipToFolder, * unit_test::enable_if<false>()) {
	resourceFolder->vOpen();
	resourceFolder->vSave(IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE,
			IResourceFile::ASSETS_UNZIP_FILE);

	unzipResourceFile = make_shared<DevelopmentResourceUnzipFile>(
			pInitOptions->getRootFolder(), IResourceFile::ASSETS_UNZIP_FILE);
	unzipResourceFile->vOpen();
	unzipResourceFile->vSave(IResourceFile::ASSETS_SAVE_MODE_FOLDER,
			IResourceFile::ASSETS_UNZIP_TO_FOLDER);

	BOOST_TEST(true);
}

//BOOST_AUTO_TEST_CASE(folderToZipToFolder, * unit_test::enable_if<DEVELOPMENT_RESOURCE_FOLDER_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(folderToZipToFolder, * unit_test::enable_if<true>()) {
BOOST_AUTO_TEST_CASE(folderToZipToFolder, * unit_test::enable_if<false>()) {
	resourceFolder->vOpen();
	resourceFolder->vSave(IResourceFile::ASSETS_SAVE_MODE_ZIPFILE,
			IResourceFile::ASSETS_ZIP_FILE);

	zipResourceFile = make_shared<ResourceZipFile>(
			pInitOptions->getRootFolder(), IResourceFile::ASSETS_ZIP_FILE);
	zipResourceFile->vOpen();
	zipResourceFile->vSave(IResourceFile::ASSETS_SAVE_MODE_FOLDER,
			IResourceFile::ASSETS_ZIP_TO_FOLDER);

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(folderToUnzipToZipToFolder, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(folderToUnzipToZipToFolder, * unit_test::enable_if<true>()) {
	resourceFolder->vOpen();
	resourceFolder->vSave(IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE,
			IResourceFile::ASSETS_UNZIP_FILE);

	unzipResourceFile = make_shared<DevelopmentResourceUnzipFile>(
			pInitOptions->getRootFolder(), IResourceFile::ASSETS_UNZIP_FILE);
	unzipResourceFile->vOpen();
	unzipResourceFile->vSave(IResourceFile::ASSETS_SAVE_MODE_ZIPFILE,
			IResourceFile::ASSETS_UNZIP_TO_ZIP);

	zipResourceFile = make_shared<ResourceZipFile>(
			pInitOptions->getRootFolder(), IResourceFile::ASSETS_UNZIP_TO_ZIP);
	zipResourceFile->vOpen();
	zipResourceFile->vSave(IResourceFile::ASSETS_SAVE_MODE_FOLDER,
			"assetsUnzipToZipToFolder");

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(folderToZipToUnzipToFolder, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(folderToZipToUnzipToFolder, * unit_test::enable_if<true>()) {
	resourceFolder->vOpen();
	resourceFolder->vSave(IResourceFile::ASSETS_SAVE_MODE_ZIPFILE,
			IResourceFile::ASSETS_ZIP_FILE);

	zipResourceFile = make_shared<ResourceZipFile>(
			pInitOptions->getRootFolder(), IResourceFile::ASSETS_ZIP_FILE);
	zipResourceFile->vOpen();
	zipResourceFile->vSave(IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE,
			IResourceFile::ASSETS_ZIP_TO_UNZIP);

	unzipResourceFile = make_shared<DevelopmentResourceUnzipFile>(
			pInitOptions->getRootFolder(), IResourceFile::ASSETS_ZIP_TO_UNZIP);
	unzipResourceFile->vOpen();
	unzipResourceFile->vSave(IResourceFile::ASSETS_SAVE_MODE_FOLDER,
			"assetsZipToUnzipToFolder");

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(folderToUnzipToUnzipToFolder, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(folderToUnzipToUnzipToFolder, * unit_test::enable_if<true>()) {
	resourceFolder->vOpen();
	resourceFolder->vSave(IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE,
			IResourceFile::ASSETS_UNZIP_FILE);

	unzipResourceFile = make_shared<DevelopmentResourceUnzipFile>(
			pInitOptions->getRootFolder(), IResourceFile::ASSETS_UNZIP_FILE);
	unzipResourceFile->vOpen();
	unzipResourceFile->vSave(IResourceFile::ASSETS_SAVE_MODE_UNZIPFILE,
			IResourceFile::ASSETS_UNZIP_TO_UNZIP);

	unzip2ResourceFile = make_shared<DevelopmentResourceUnzipFile>(
			pInitOptions->getRootFolder(),
			IResourceFile::ASSETS_UNZIP_TO_UNZIP);
	unzip2ResourceFile->vOpen();
	unzip2ResourceFile->vSave(IResourceFile::ASSETS_SAVE_MODE_FOLDER,
			"assetsUnzipToUnzipToFolder");

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_CASE(folderToZipToZipToFolder, * unit_test::enable_if<MAIN_TEST_ENABLE>()) {
//BOOST_AUTO_TEST_CASE(folderToZipToZipToFolder, * unit_test::enable_if<true>()) {
	resourceFolder->vOpen();
	resourceFolder->vSave(IResourceFile::ASSETS_SAVE_MODE_ZIPFILE,
			IResourceFile::ASSETS_ZIP_FILE);

	zipResourceFile = make_shared<ResourceZipFile>(
			pInitOptions->getRootFolder(), IResourceFile::ASSETS_ZIP_FILE);
	zipResourceFile->vOpen();
	zipResourceFile->vSave(IResourceFile::ASSETS_SAVE_MODE_ZIPFILE,
			IResourceFile::ASSETS_ZIP_TO_ZIP);

	zip2ResourceFile = make_shared<ResourceZipFile>(
			pInitOptions->getRootFolder(), IResourceFile::ASSETS_ZIP_TO_ZIP);
	zip2ResourceFile->vOpen();
	zip2ResourceFile->vSave(IResourceFile::ASSETS_SAVE_MODE_FOLDER,
			"assetsZipToZipToFolder");

	BOOST_TEST(true);
}

BOOST_AUTO_TEST_SUITE_END()

}