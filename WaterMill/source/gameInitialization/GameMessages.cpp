#include "GameMessages.h"
#include "ErrorCode.h"

#include <boost/locale.hpp>
#include <iostream>
#include <exception> // exception
#include "../debugging/Logger.h"
#include <sstream>      // std::stringstream

using std::cout;
using std::endl;
using std::locale;
using std::string;
using std::exception;
using std::stringstream;
using boost::locale::translate;
using boost::locale::generator;

namespace base_game {

	const string GameMessages::STRINGS_FOLDER = "strings/";
	const string GameMessages::MESSAGE_DOMAIN = "watermill";

	GameMessages::GameMessages(string assetsFolder, string language) {

		logger::info("Create GameMessages");

		stringstream ss;
		ss << "LAN: " << language;
		logger::trace(ss);
		//this->assetsFolder = assetsFolder;
		//this->language = language;
		generator gen;

		// Specify location of dictionaries
		gen.add_messages_path(assetsFolder+STRINGS_FOLDER);
		gen.add_messages_domain(MESSAGE_DOMAIN);

		// Generate locales and imbue them to iostream
		//locale::global(gen(""));
		//locale loc = gen("");

		//locale loc = gen(language);

		locale loc;
		try {
			loc = gen.generate(language);


		} catch (exception& e) {
			logger::warning("EXCEPTIOn1");
			throw ErrorCode("GAME_MESSAGES_PROBLEM", 789);
		}		//locale loc = gen("en.UTF-8");
		//locale loc = gen("pl.UTF-8");

		locale::global(loc);

		//		cout.imbue(locale());
		//cout.imbue(loc);
		ss.imbue(loc);


		//cout << "The language code is " << std::use_facet<boost::locale::info>(some_locale).language() << endl;

		ss << "The language code is " << std::use_facet<boost::locale::info>(loc).language();
		logger::trace(ss);

		ss << "The country code is " << std::use_facet<boost::locale::info>(loc).country();
		logger::trace(ss);

		ss << "name " << loc.name();
		logger::trace(ss);
	}

	GameMessages::~GameMessages() {
		logger::info("Destroy GameMessages");
	}

	void GameMessages::testMessages() {
		stringstream ss;
		// Display a message using current system locale
		ss << translate("hello_world");
		logger::trace(ss);
		ss << translate("hello_world_only_pl_pl");
		logger::trace(ss);
		ss << translate("hello_world_only_pl");
		logger::trace(ss);
		ss << translate("hello_world_only_en");
		logger::trace(ss);
		ss << translate("hello_world_only_default");
		logger::trace(ss);

		ss << "Próba kodowania Cześć Świecie";
		logger::trace(ss);
	}
}
