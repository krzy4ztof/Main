#include "GameMessages.h"

#include <boost/locale.hpp>
#include <iostream>


using std::cout;

using std::endl;
using std::locale;
using std::string;
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

	GameMessages::GameMessages(string assetsFolder, string language) {

		cout << "LAN: " << language << endl;
		//this->assetsFolder = assetsFolder;
		//this->language = language;
		generator gen;

		// Specify location of dictionaries
		gen.add_messages_path(assetsFolder+"/strings");
		gen.add_messages_domain("watermill");

		// Generate locales and imbue them to iostream
		//locale::global(gen(""));
		//locale loc = gen("");

		locale loc = gen(language);

		//locale loc = gen("en.UTF-8");
		//locale loc = gen("pl.UTF-8");

		locale::global(loc);

		//		cout.imbue(locale());
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
