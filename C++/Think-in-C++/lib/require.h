#define require(condition, message) \
    if (!(condition)) { \
        std::string msg = message; \
        msg += " at "; \
        msg += __FILE__; \
        msg += ":"; \
        msg += std::to_string(__LINE__); \
        std::abort(); \
    }
