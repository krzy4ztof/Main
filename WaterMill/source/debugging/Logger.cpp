#include "Logger.h"

#include <iostream> //ostream
#include <iomanip>//setw, setfill
#include <string>//string
#include <sstream>// std::stringstream, std::stringbuf
#include <fstream>// std::ofstream
#include <boost/shared_ptr.hpp> //boost::make_shared
#include <boost/core/null_deleter.hpp> // boost::null_deleter
#include <boost/log/core.hpp> // add_sink()
#include <boost/log/expressions.hpp> // boost::log::expressions
#include <boost/log/trivial.hpp> // BOOST_LOG_TRIVIAL
#include <boost/log/utility/setup/common_attributes.hpp> // add_common_attributes
#include <boost/log/sinks/text_ostream_backend.hpp> //add_stream()
#include <boost/log/sources/severity_logger.hpp> //boost::log::trivial::severity_level
#include <boost/log/sources/logger.hpp> // boost::log::sources::logger
#include <boost/log/sources/record_ostream.hpp> // BOOST_LOG
#include <boost/log/support/date_time.hpp> //expr::format_date_time< boost::posix_time::ptime >
#include <boost/smart_ptr/shared_ptr.hpp> // boost::shared_ptr<>
#include <boost/smart_ptr/make_shared_object.hpp> // boost::make_shared<>()

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

// end
using std::cout;
using std::endl;
using std::setw;
using std::setfill;
using std::string;
using std::stringstream;
using std::ofstream;
//using std::ostream;
//using std::clog;

namespace base_game {

	const string Logger::LOG_FILENAME = "watermill.log";

	Logger* Logger::s_Logger = nullptr;


	namespace logger {

		void init() {

			if (!Logger::s_Logger) {
				Logger::s_Logger = new Logger();
			}

			Logger::s_Logger->init();

		}

		void test() {
			Logger::s_Logger->test();
		}


		void destroy() {
			if (Logger::s_Logger) {
				delete (Logger::s_Logger);
				(Logger::s_Logger)=nullptr;
			}
		}

		void trace(string text) {
			Logger::s_Logger->trace(text);
		}

		void trace(stringstream& ss) {
			Logger::s_Logger->trace(ss.str());
			ss.str("");
			ss.clear();
		}

		void debug(string text) {
			Logger::s_Logger->debug(text);
		}

		void debug(stringstream& ss) {
			Logger::s_Logger->debug(ss.str());
			ss.str("");
			ss.clear();
		}

		void info(string text) {
			Logger::s_Logger->info(text);
		}

		void info(stringstream& ss) {
			Logger::s_Logger->info(ss.str());
			ss.str("");
			ss.clear();
		}

		void warning(string text) {
			Logger::s_Logger->warning(text);
		}

		void warning(stringstream& ss) {
			Logger::s_Logger->warning(ss.str());
			ss.str("");
			ss.clear();
		}

		void error(string text) {
			Logger::s_Logger->error(text);
		}

		void error(stringstream& ss) {
			Logger::s_Logger->error(ss.str());
			ss.str("");
			ss.clear();
		}

		void fatal(string text) {
			Logger::s_Logger->fatal(text);
		}

		void fatal(stringstream& ss) {
			Logger::s_Logger->fatal(ss.str());
			ss.str("");
			ss.clear();
		}

	}


	Logger::Logger() {
		cout <<"Create Logger" << endl;
	}

	Logger::~Logger() {
		cout <<"Destroy Logger" << endl;
		boost::shared_ptr< logging::core > core = logging::core::get();

		// Remove the sink from the core, so that no records are passed to it
		core->remove_sink(outputstream);
		core->remove_sink(logfile);

		// Break the feeding loop
		outputstream->stop();
		logfile->stop();

		// Flush all log records that may have left buffered
		outputstream->flush();
		logfile->flush();

		// Delete shared_ptr
		outputstream.reset();
		logfile.reset();
	}

	void Logger::init() {
		logfile = boost::make_shared< text_sink >();

		// Add a stream to write log to
		logfile->locked_backend()->add_stream(
			boost::make_shared<ofstream >(LOG_FILENAME));

		logfile->set_formatter( expr::stream

								<< "["
								// line id will be 5-digits, zero-filled
								<< setw(5) << setfill('0') << expr::attr< unsigned int >("LineID")
								<< "|"
								<< expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
								<< "|"
								<< setw(7) << setfill(' ') <<  logging::trivial::severity
								<< "] : " << expr::smessage);


		// Register the logfile in the logging core
		logging::core::get()->add_sink(logfile);

		outputstream = boost::make_shared<ostream_sink>();
		boost::shared_ptr<std::ostream> clog{&std::clog,
											 boost::null_deleter{}};

		outputstream->locked_backend()->add_stream(clog);

		outputstream->set_filter(
			logging::trivial::severity >= logging::trivial::info

		);

		//		ostream->set_formatter(&logger::custom_formatter);
		outputstream->set_formatter( expr::stream

									 << "["
									 << setw(7) << setfill(' ') << logging::trivial::severity
									 << "] : " << expr::smessage);


		// Register the ostream in the logging core
		logging::core::get()->add_sink(outputstream);

		// Add TimeStamp, LineID to log records
		logging::add_common_attributes();
	}

	void Logger::trace(string text) {
		log(text,logging::trivial::trace);
	}

	void Logger::debug(string text) {
		log(text,logging::trivial::debug);
	}

	void Logger::info(string text) {
		log(text,logging::trivial::info);
	}

	void Logger::warning(string text) {
		log(text,logging::trivial::warning);
	}

	void Logger::error(string text) {
		log(text,logging::trivial::error);
	}

	void Logger::fatal(string text) {
		log(text,logging::trivial::fatal);
	}

	void Logger::log(string text, logging::trivial::severity_level sevLevel) {
		BOOST_LOG_SEV(severityLogger,sevLevel) << text;

		// ostream->flush() needed for
		//typedef boost::log::sinks::asynchronous_sink<boost::log::sinks::text_ostream_backend> ostream_sink;
		// ostream->flush() NOT needed for
		// typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> ostream_sink;

		// when asynchronous_sink is used MingW64 application does not end process unless
		// ostream->flush(); and logfile->flush(); is used

		outputstream->flush();
		logfile->flush();
	}

	void Logger::test() {
		src::logger lg;
		BOOST_LOG(lg) << "Hello world!";

		BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
		BOOST_LOG_TRIVIAL(trace) << "A trace severity message " << 2 ;

		// ostream->flush() needed for
		//typedef boost::log::sinks::asynchronous_sink<boost::log::sinks::text_ostream_backend> ostream_sink;
		// ostream->flush() NOT needed for
		// typedef boost::log::sinks::synchronous_sink<boost::log::sinks::text_ostream_backend> ostream_sink;

		// when asynchronous_sink is used MingW64 application does not end process unless
		// ostream->flush(); and logfile->flush(); is used

		outputstream->flush();
		logfile->flush();
	}
}
