#ifndef LOGGER_H
#define LOGGER_H

#define BOOST_LOG_DYN_LINK 1
//#define BOOST_ALL_DYN_LINK 1

#include <boost/log/sinks.hpp> // boost::log::sinks
#include <boost/smart_ptr/shared_ptr.hpp> // boost::shared_ptr
#include <string>//string
#include <boost/log/trivial.hpp>//boost::log::trivial
#include <boost/log/sources/severity_logger.hpp>//severity_level, boost::log::keywords::severity
#include <boost/log/utility/formatting_ostream.hpp>// boost::log::formatting_ostream
#include <sstream>      // std::stringstream, std::stringbuf

namespace base_game {

	//        typedef boost::log::sinks::synchronous_sink< boost::log::sinks::text_ostream_backend > text_sink;
	typedef boost::log::sinks::asynchronous_sink< boost::log::sinks::text_ostream_backend > text_sink;

	typedef boost::log::sinks::asynchronous_sink<boost::log::sinks::text_ostream_backend> ostream_sink;
	//typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> ostream_sink;

	class Logger {
		public:
			static Logger* s_Logger;

			virtual ~Logger();
			Logger();
			void init();

			void trace(std::string text);
			void debug(std::string text);
			void info(std::string text);
			void warning(std::string text);
			void error(std::string text);

			void fatal(std::string text);

			void test();
		protected:

		private:
			const static std::string LOG_FILENAME;
			void log(std::string text, boost::log::trivial::severity_level sevLevel);

			boost::log::sources::severity_logger< boost::log::trivial::severity_level > severityLogger;

			boost::shared_ptr<ostream_sink> outputstream;
			boost::shared_ptr< text_sink > logfile;
	};

	namespace logger {
		void init();
		void test();
		void destroy();
		void trace(std::string text);
		void trace(std::stringstream& ss);
		void debug(std::string text);
		void debug(std::stringstream& ss);
		void info(std::string text);
		void info(std::stringstream& ss);
		void warning(std::string text);
		void warning(std::stringstream& ss);
		void error(std::string text);
		void error(std::stringstream& ss);
		void fatal(std::string text);
		void fatal(std::stringstream& ss);
	}
}
#endif // LOGGER_H
