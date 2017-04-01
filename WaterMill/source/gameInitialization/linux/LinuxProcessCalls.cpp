#ifdef __linux__

#include "LinuxProcessCalls.h"

#include<iostream> // cout, endl
#include <string> // string

#include <dirent.h> //readdir, opendir, DIR, DT_DIR, dirent
#include <string.h> // strcasestr

#include "../../utilities/StringUtils.h"
#include "../../debugging/Logger.h"
#include <sstream>      // std::stringstream
#include "../../utilities/Templates.h"

using std::string;
using std::stringstream;


namespace base_game {
	LinuxProcessCalls::LinuxProcessCalls() {
		logger::trace("Create LinuxProcessCalls");
	}

	LinuxProcessCalls::~LinuxProcessCalls() {
		logger::trace("Destroy LinuxProcessCalls");
	}


	bool LinuxProcessCalls::isOnlyInstance ( const string& gameTitle ) {
		stringstream ss;
		logger::trace("tutaj");
		char chrarry_CommandLinePath[100]  ;
		char chrarry_NameOfProcess[300]  ;
		char* chrptr_StringToCompare;

		char* gameTitleChar = string_utils::stringToChar(gameTitle);
		//char* gameTitleChar = new char[gameTitle.length() + 1];
		//strcpy ( gameTitleChar, gameTitle.c_str() );

		struct dirent* de_DirEntity = NULL ;
		DIR* dir_proc = NULL ;
		int ( *compareFunction ) ( const char*, const char*, bool ) ;
		compareFunction = &string_utils::compareChars;
		dir_proc = opendir ( "/proc/" ) ;

		if ( dir_proc == NULL ) {
			logger::warning("Couldn't open the  PROC_DIRECTORY directory");
			return ( pid_t ) - 2 ;
		}

		int howMany = 0;

		// Loop while not NULL
		while ( ( de_DirEntity = readdir ( dir_proc ) ) ) {

            memset(chrarry_CommandLinePath,0,sizeof(chrarry_CommandLinePath));
            memset(chrarry_NameOfProcess,0,sizeof(chrarry_NameOfProcess));


			if ( de_DirEntity->d_type == DT_DIR ) {

				if ( string_utils::isCharNumeric ( de_DirEntity->d_name ) ) {
					strcpy ( chrarry_CommandLinePath, "/proc/" ) ;
					strcat ( chrarry_CommandLinePath, de_DirEntity->d_name ) ;
					strcat ( chrarry_CommandLinePath, "/cmdline" ) ;
					FILE* fd_CmdLineFile = fopen ( chrarry_CommandLinePath, "rt" ) ; // open the file for reading text

					if ( fd_CmdLineFile ) {
						fscanf ( fd_CmdLineFile, "%s", chrarry_NameOfProcess ) ; // read from /proc/<NR>/cmdline
						fclose ( fd_CmdLineFile ); // close the file prior to exiting the routine

						if ( strrchr ( chrarry_NameOfProcess, '/' ) ) {
							chrptr_StringToCompare = strrchr ( chrarry_NameOfProcess, '/' ) + 1 ;
						}

						else {
							chrptr_StringToCompare = chrarry_NameOfProcess ;
						}

						if ( compareFunction ( chrptr_StringToCompare, gameTitleChar, false ) ) {
							ss << "proces podobny: " << chrptr_StringToCompare << " // " << "/proc/" <<  de_DirEntity->d_name << "/cmdLine";
							logger::trace(ss);


							howMany++;
						}
					}
				}
			}
		}

		closedir ( dir_proc ) ;
		logger::trace("tutaj 2");

		templates::safe_delete_array<char>(gameTitleChar);
		//string_utils::safe_delete_char_array(gameTitleChar);

		ss << "tutaj howMany: " << howMany;
		logger::trace(ss);

		if ( howMany >= 2 ) {
			logger::trace("tutaj false");

			// First process is this process
			// Second process is second game process
			return false;
		}

		else {
			logger::trace("tutaj true");

			return true;
		}
	}
}


#endif /* __linux__ */
