#include <iostream>

#define assure(condition, errorMessage)                                                            \
    do {                                                                                           \
        if (!(condition)) {                                                                        \
            std::cerr << "Error: " << errorMessage << std::endl;                                   \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    } while (false)
