#define SEC_YEAR (365 * 24 * 60 * 60)UL

// macro MIN classic define
#define MIN_c(a, b)  ((a) < (b) ? (a) : (b))

// macro MIN define method with type
#define MIN_t(type, a, b) ({ type _a = a; \
                             type _b = b; \
                             _a < _b ? _a : _b; \
                            })

// macro MIN the most common define method 
#define MIN(a, b) ({ const typeof(a) _a = a; \
                     const typeof(b) _b = b; \
                     (void)(&_a == &_b); \
                     _a < _b ? _a : _b; \
                    })