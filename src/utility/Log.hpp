#ifndef NJOY_UTILITY_LOG
#define NJOY_UTILITY_LOG

// system includes

// other includes
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace njoy {
namespace utility {

/**
 *  @brief A singleton logger for njoy components
 */
class Log {

  static auto initialize_logger() {

    auto instance = spdlog::stdout_color_st( "njoy" );
    instance->set_pattern( "[%^%l%$] %v" );
    #ifndef NDEBUG
    instance->set_level( spdlog::level::debug );
    #endif
    return instance;
  }

  static auto& logger() {

    static auto instance = initialize_logger();
    return instance;
  }

  /* constructors */
  Log() {}; // private to avoid creation of Log instances

public:

  Log( const Log& ) = delete;
  void operator=( const Log& ) = delete;

  /**
   *  @brief Print a message at the info level
   *
   *  For example:
   *
   *  int value = 10;
   *  utility::Log::info( "Some message with a value {}", value );
   */
  template< typename... Args >
  static void info( Args... args ) {

    logger()->info( std::forward< Args >( args )... );
  }

  /**
   *  @brief Print a message at the warning level
   *
   *  For example:
   *
   *  int value = 10;
   *  utility::Log::warning( "Some message with a value {}", value );
   */
  template< typename... Args >
  static void warning( Args... args ) {

    logger()->warn( std::forward< Args >( args )... );
  }

  /**
   *  @brief Print a message at the error level
   *
   *  For example:
   *
   *  int value = 10;
   *  utility::Log::info( "Some message with a value {}", value );
   */
  template< typename... Args >
  static void error( Args... args ) {

    logger()->error( std::forward< Args >( args )... );
  }

  /**
   *  @brief Print a message at the debug level
   *
   *  This only prints when NDEBUG is defined when compiling this code.
   *
   *  For example:
   *
   *  int value = 10;
   *  utility::Log::debug( "Some message with a value {}", value );
   */
  #ifdef NDEBUG
    template< typename... Args >
    static void debug( Args... ) {}
  #else
    template< typename... Args >
    static void debug( Args... args ) {

      logger()->debug( std::forward< Args >( args )... );
    }
  #endif
};

} // utility namespace

/* type alias - for backwards compatibility reasons */
using Log = utility::Log;

} // njoy namespace

#endif
