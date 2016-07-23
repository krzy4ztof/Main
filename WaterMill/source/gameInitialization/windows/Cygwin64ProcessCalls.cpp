#ifdef __CYGWIN__

#include "Cygwin64ProcessCalls.h"

#include<iostream> // cout, endl
#include <string> // string

#include <dirent.h> //readdir, opendir, DIR, DT_DIR, dirent
#include <string.h> // strcasestr

using namespace std;


namespace watermill {
	Cygwin64ProcessCalls::Cygwin64ProcessCalls() {
		//ctor
	}

	Cygwin64ProcessCalls::~Cygwin64ProcessCalls() {
		//dtor
	}

	namespace cygwin64_process_calls {

		int isNumeric ( const char* ccharptr_CharacterList ) {
			for ( ; *ccharptr_CharacterList; ccharptr_CharacterList++ )
				if ( *ccharptr_CharacterList < '0' || *ccharptr_CharacterList > '9' ) {
					return 0;    // false
				}

			return 1; // true
		}

		int strcmp_Wrapper ( const char *s1, const char *s2, bool intCaseSensitive ) {
			if ( intCaseSensitive ) {
				return !strcmp ( s1, s2 );
			}

			else {
				return !strcasecmp ( s1, s2 );
			}
		}
	}

	bool Cygwin64ProcessCalls::isOnlyInstance ( const std::string& gameTitle ) {
		cout << "tutaj" << endl;
		char chrarry_CommandLinePath[100]  ;
		char chrarry_NameOfProcess[300]  ;
		char* chrptr_StringToCompare;
		char* gameTitleChar = new char[gameTitle.length() + 1];
		strcpy ( gameTitleChar, gameTitle.c_str() );
		pid_t pid_ProcessIdentifier = ( pid_t ) - 1 ;
		struct dirent* de_DirEntity = NULL ;
		DIR* dir_proc = NULL ;
		int ( *compareFunction ) ( const char*, const char*, bool ) ;
		compareFunction = &cygwin64_process_calls::strcmp_Wrapper;
		dir_proc = opendir ( "/proc/" ) ;

		if ( dir_proc == NULL ) {
			cout << "Couldn't open the  PROC_DIRECTORY directory" << endl ;
			return ( pid_t ) - 2 ;
		}

		int howMany = 0;

		// Loop while not NULL
		while ( ( de_DirEntity = readdir ( dir_proc ) ) ) {
			if ( de_DirEntity->d_type == DT_DIR ) {

				if ( cygwin64_process_calls::isNumeric ( de_DirEntity->d_name ) ) {
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
							pid_ProcessIdentifier = ( pid_t ) atoi ( de_DirEntity->d_name ) ;
							howMany++;
						}
					}
				}
			}
		}

		closedir ( dir_proc ) ;
		delete [] gameTitleChar;

		if ( howMany >= 2 ) {
			// First process is this process
			// Second process is second game process
			return false;
		}

		else {
			return true;
		}
	}
}

#endif /* __CYGWIN__ */