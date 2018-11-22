#ifndef GAMEMESSAGES_H
#define GAMEMESSAGES_H

#include "../resourceCache/ResourceCache.h"
#include "MessageParams.h"

// #include <locale> // std::locale

//#include <boost/locale.hpp> // std::locale
#include <boost/locale.hpp> // messages_info
#include <memory> // shared_ptr

#include <string> // string
#include <vector> // vector
#include <map> // map

namespace base_game {
class GameMessages {
public:
	const static std::string STRINGS_FOLDER;
	const static std::string MESSAGE_DOMAIN;

	GameMessages(std::shared_ptr<ResourceCache> resourceCache,
			std::string currentLanguageCode, std::string languageCodes);
	virtual ~GameMessages();

	void init();
	void initLanguages(std::string currentLanguageCode,
			std::string languageCodes);
	std::shared_ptr<MessageParams> getOrAddLanguage(std::string code);
	std::shared_ptr<MessageParams> addLanguage(std::string code);
	void initMessages(MessageParams* messageParams);
	void switchCurrentLanguage(std::string code);
	void describeYourself();
	void testMessagesGetText();

protected:

private:

	std::shared_ptr<ResourceCache> shrdPtrResourceCache;

	std::shared_ptr<MessageParams> currentLanguage;
	std::map<std::string, std::shared_ptr<MessageParams>> languages;
	std::map<std::string, std::locale> locales;

};

namespace game_messages {

std::vector<char> messages_file_loader(std::string const &fileName,
		std::string const &encoding);
}
}
#endif // GAMEMESSAGES_H
