#include "GameMessages.h"
#include "ErrorCode.h"
#include "GameCodeApp.h"//g_pApp
#include "../utilities/Templates.h"
#include "../utilities/StringUtils.h"
#include "../resourceCache/ResourceCache.h"
#include "../resourceCache/ResourceHandle.h"
#include "../resourceCache/MessageResourceExtraData.h"
#include "../debugging/Logger.h"

#include <boost/locale.hpp>
#include <iostream>
#include <exception> // exception
#include <memory> // shared_ptr, dynamic_pointer_cast
#include <sstream>      // std::stringstream
#include <string> // string
#include <vector> // vector
#include <map> // map
#include <boost/filesystem.hpp> // boost::filesystem::path; boost::filesystem::recursive_directory_iterator;
//boost::filesystem::filesystem_error; boost::filesystem::directory_entry; boost::filesystem::exists;
//boost::filesystem::is_directory; boost::filesystem::is_regular_file; boost::filesystem::create_directory
//boost::filesystem::remove_all; boost::filesystem::copy_file; boost::filesystem::ofstream;
#include <boost/iostreams/filtering_streambuf.hpp> // filtering_streambuf
#include <boost/iostreams/copy.hpp> //boost::iostreams::copy
#include <boost/iostreams/device/back_inserter.hpp> // boost::iostreams::back_insert_device
// #include <locale> // std::locale
#include <boost/optional.hpp> // boost::optional

using std::cout;
using std::endl;
using std::locale;
using std::string;
using std::vector;
using std::exception;
using std::stringstream;
using std::ios;
using std::shared_ptr;
using std::dynamic_pointer_cast;
using std::map;

using boost::locale::translate;
using boost::locale::generator;
using boost::locale::message_format;

using boost::locale::gnu_gettext::messages_info;
// using boost::locale::gnu_gettext::messages_info::domain;
using boost::locale::gnu_gettext::create_messages_facet;
using boost::filesystem::path;
using boost::filesystem::ifstream;
using boost::iostreams::filtering_istreambuf;
using boost::locale::gettext;
using boost::optional;

namespace base_game {

const string GameMessages::STRINGS_FOLDER = "strings";
const string GameMessages::MESSAGE_DOMAIN = "watermill";

GameMessages::GameMessages(shared_ptr<ResourceCache> resourceCache,
		string currentLanguageCode, string currentLanguageCodes) {
	logger::trace("Create GameMessages");
	this->shrdPtrResourceCache = resourceCache;

	this->initLanguages(currentLanguageCode, currentLanguageCodes);
}

GameMessages::~GameMessages() {
	logger::trace("Destroy GameMessages");
	// templates::safe_delete<messages_info>(messagesInfo);
	languages.clear();
	currentLanguage.reset();
	locales.clear();

}

void GameMessages::initLanguages(string currentLanguageCode, string languageCodes) {
	stringstream ss;
	ss << "LAN: " << currentLanguageCode;
	logger::info(ss);
	ss << "LANS: " << languageCodes;
	logger::info(ss);

	vector<string> currentParamsVector;
	string_utils::splitString(currentParamsVector, currentLanguageCode, '.');

	vector<string> languagesVector;
	string_utils::splitString(languagesVector, languageCodes, ';');
	for (string code : languagesVector) {
		getOrAddLanguage(code);
	}

	this->currentLanguage = getOrAddLanguage(currentLanguageCode);

	//TODO: language powinno wskazywac pozycje z listy language

	describeYourself();
	// ss << "END: " << this->languages;
	// logger::info(ss);
}

shared_ptr<MessageParams> GameMessages::getOrAddLanguage(string code) {
	map<string, shared_ptr<MessageParams>>::iterator languageIterator =
			this->languages.find(code);

	if (languageIterator != this->languages.end()) {
		shared_ptr<MessageParams> language = languageIterator->second;
		return language;
	} else {
		shared_ptr<MessageParams> language = this->addLanguage(code);
		return language;
	}
}

shared_ptr<MessageParams> GameMessages::addLanguage(string code) {
	stringstream ss;

	vector<string> codeVector;
	string_utils::splitString(codeVector, code, '.');

	string languageParam = "";
	string encodingParam = "";

	if (codeVector.size() > 0) {
		languageParam = codeVector.at(0);
		ss << "PARAM[0]: " << languageParam;
		logger::info (ss);

		if (codeVector.size() > 1) {
			encodingParam = codeVector.at(1);
			ss << "PARAM[1]: " << encodingParam;
			logger::info(ss);

		}

		MessageParams* messageParams = new MessageParams(languageParam,
				encodingParam);
		shared_ptr<MessageParams> messageParamsPointer = shared_ptr<
				MessageParams>(messageParams);
		this->languages[code] = messageParamsPointer;
		return messageParamsPointer;
	} else {
		return shared_ptr<MessageParams>();
	}
}

void GameMessages::describeYourself() {
	stringstream ss;
	ss << "GameMessages->languages:";
	logger::info(ss);

	for (map<string, shared_ptr<MessageParams>>::iterator it =
			this->languages.begin(); it != this->languages.end(); ++it) {
		it->second->describeYourself();
	}

	ss << "GameMessages->currentLanguage:";
	logger::info(ss);
	this->currentLanguage->describeYourself();
}

void GameMessages::init() {
	stringstream ss;
	ss << "GameMessages:language " << this->currentLanguage;
	logger::info(ss);

	for (map<string, shared_ptr<MessageParams>>::iterator it =
			this->languages.begin(); it != this->languages.end(); ++it) {
		initMessages(it->second.get());
	}
	//TODO: inicjalizacja wszystkich locale; przekierowanie do temp_messages_file_loader; messaage_file_loader musi odczytywac z resourceCache i z messageLoader

//	Resource resource(resourceName);
//	optional<shared_ptr<ResourceHandle>> pResourceHandle =
//			shrdPtrResourceCache->getHandle(&resource);

}

void GameMessages::switchCurrentLanguage(string code) {
	stringstream ss;

	map<string, shared_ptr<MessageParams>>::iterator languageIterator =
			this->languages.find(code);

	if (languageIterator != this->languages.end()) {
		shared_ptr<MessageParams> language = languageIterator->second;
		this->currentLanguage = language;
	} else {
		ss << "Cannot find language with code: " << code;
		logger::error (ss);

	}
}

void GameMessages::initMessages(MessageParams* messageParams) {
	stringstream ss;

	messages_info info;
	info.language = messageParams->getLanguage();
	info.encoding = messageParams->getEncoding();

	info.paths.push_back("");
	info.domains.push_back(messages_info::domain(GameMessages::MESSAGE_DOMAIN));
	info.callback = game_messages::messages_file_loader;

	generator gen;
	locale base_locale = gen("");

	message_format<char>* messagesFormat = create_messages_facet<char>(info);

	string code = messageParams->getCode();
	locales[code] = locale(base_locale, messagesFormat);
}

void GameMessages::temp_testMessagesGetText() {

	string code = currentLanguage->getCode();
	locale currentLocale = locales[code];

	auto helloWorld = gettext("hello_world", currentLocale);
	logger::info(helloWorld);

	string helloWorldOnlyPlPl = gettext("hello_world_only_pl_pl",
			currentLocale);
	logger::info(helloWorldOnlyPlPl);

	string helloWorldOnlyPl = gettext("hello_world_only_pl", currentLocale);
	logger::info(helloWorldOnlyPl);

	string helloWorldOnlyEn = gettext("hello_world_only_en", currentLocale);
	logger::info(helloWorldOnlyEn);

	string helloWorldOnlyDefault = gettext("hello_world_only_default",
			currentLocale);
	logger::info(helloWorldOnlyDefault);
}



namespace game_messages {

vector<char> messages_file_loader(string const &fileName,
		string const &encoding) {
	stringstream ss;
	vector<char> result;

	ss << "fileName: " << fileName;
	logger::info(ss);
	ss << "fileName[0]: " << fileName.at(0);
	logger::info(ss);
	ss << "fileName[1]: " << fileName.at(1);
	logger::info(ss);
	ss << "fileName[2]: " << fileName.at(2);
	logger::info(ss);
	ss << "fileName[3]: " << fileName.at(3);
	logger::info(ss);
	ss << "encoding: " << encoding;
	logger::info(ss);

	/*
	 fileName: /pl/LC_MESSAGES/watermill.mo
	 encoding: UTF-8

	 originally LC_MESSAGES should be written in uppercase
	 however Resource(fileName) changes folder names to lowercase

	 for consistency LC_MESSAGES folder is changed to lowercase

	 */

	if (fileName.at(0) == '/') {
		ss << "fileAt[0] == '/'";
		logger::info(ss);

	}

	if (g_pApp != nullptr) {
		logger::info("check g_APP");

		shared_ptr<ResourceCache> shrdPtrResourceCache =
				g_pApp->getResourceCache();

		path resourcePath { GameMessages::STRINGS_FOLDER };
		resourcePath /= fileName;
		resourcePath = resourcePath.make_preferred();

		ss << "resourcePath: " << resourcePath.string();
		logger::info(ss);

		string resourceName = resourcePath.string();

		Resource resource(resourceName);
		optional<shared_ptr<ResourceHandle>> pResourceHandle =
				shrdPtrResourceCache->getHandle(&resource);

		// stringstream ss;

		ss << "resourceNameXXX: " << pResourceHandle.get()->getName();
		logger::info(ss);


		shared_ptr<IResourceExtraData> extraData =
				pResourceHandle.get()->getExtraData();

		ss << "extraData: " << extraData->vToString();
		logger::info(ss);

		if (shared_ptr<MessageResourceExtraData> messageResourceExtraData =
				dynamic_pointer_cast<MessageResourceExtraData>(extraData)) {
			result = messageResourceExtraData->getData();
		}

	}

	return result;
}
}
}
