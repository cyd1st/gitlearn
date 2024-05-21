#include <string>
#include <iostream>

#ifndef __REQUIRE_H__
#define __REQUIRE_H__

#ifdef __cplusplus
extern "C" {
#endif

#define require(condition, message) \
    if (!(condition)) { \
        std::string msg = message; \
        msg += " at "; \
        msg += __FILE__; \
        msg += ":"; \
        msg += std::to_string(__LINE__); \
        std::cerr << "Error: " << msg << std::endl; \
        std::abort(); \
    }

#define assure(condition, errorMessage) \
  do { \
    if (!(condition)) { \
      std::cerr << "Error: " << errorMessage << std::endl; \
      exit(EXIT_FAILURE); \
    } \
  } while (false)

#define requireArgs(ARGC, MIN_ARGS) \
  do { \
      if ((ARGC) < (MIN_ARGS)) { \
          cerr << "Error: At least " << (MIN_ARGS) << " arguments required." << endl; \
          exit(EXIT_FAILURE); \
      } \
  } while(0)


#ifdef __cplusplus
}
#endif
#endif // __REQUIRE_H__