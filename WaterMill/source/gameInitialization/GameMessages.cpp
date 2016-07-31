#include "GameMessages.h"
#include "ErrorCode.hpp"

#include <boost/locale.hpp>
#include <iostream>
#include <exception> // exception

using std::cout;
using std::endl;
using std::locale;
using std::string;
using std::exception;
using boost::locale::translate;
using boost::locale::generator;

//using namespace std;
//using namespace boost::locale;


namespace watermill {

	namespace game_messages {
		void safe_delete(GameMessages* p) {
			if (p) {
				delete (p);
				(p)=nullptr;
			}
		}
	}

	const string GameMessages::STRINGS_FOLDER = "strings/";
	const string GameMessages::MESSAGE_DOMAIN = "watermill";

	GameMessages::GameMessages(string assetsFolder, string language) {

		cout << "LAN: " << language << endl;
		//this->assetsFolder = assetsFolder;
		//this->language = language;
		generator gen;

		// Specify location of dictionaries
		gen.add_messages_path(assetsFolder+STRINGS_FOLDER);
		gen.add_messages_domain(MESSAGE_DOMAIN);

		// Generate locales and imbue them to iostream
		//locale::global(gen(""));
		//locale loc = gen("");

		cout << "LAN1" << endl;
		//locale loc = gen(language);

		locale loc;
		try {
			loc = gen.generate(language);


		} catch (exception& e) {
			cout << "EXCEPTIOn1" << endl;
			throw ErrorCode("GAME_MESSAGES_PROBLEM", 789);
		}		//locale loc = gen("en.UTF-8");
		//locale loc = gen("pl.UTF-8");

		cout << "LAN2" << endl;
		locale::global(loc);

		//		cout.imbue(locale());

		cout << "LAN3" << endl;
		cout.imbue(loc);

		//cout << "The language code is " << std::use_facet<boost::locale::info>(some_locale).language() << endl;

		cout << "The language code is " << std::use_facet<boost::locale::info>(loc).language() << endl;

		cout << "The country code is " << std::use_facet<boost::locale::info>(loc).country() << endl;

		cout << "name " << loc.name() << endl;
	}

	GameMessages::~GameMessages() {
		//dtor
	}

	void GameMessages::testMessages() {


		// Display a message using current system locale
		cout << translate("hello_world") << endl;
		cout << translate("hello_world_only_pl_pl") << endl;
		cout << translate("hello_world_only_pl") << endl;
		cout << translate("hello_world_only_en") << endl;
		cout << translate("hello_world_only_default") << endl;

		cout << "Próba kodowania Cześć Świecie" << endl;
	}
}
