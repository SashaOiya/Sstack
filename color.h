#include <windows.h>

//{----------------------------------------------------------------------------
//!
//! Enumeration of color values
//!
//}----------------------------------------------------------------------------
enum Color_t {
    COLOR_GREEN = 10,
    COLOR_WHITE = 15,
    COLOR_RED   =  4,
    COLOR_PINK  = 12,
    COLOR_BLUE  =  9
};

//{----------------------------------------------------------------------------
//!
//! Prints the specified line with the specified color
//!
//! @param *line Pointer to the printed line
//! @param COLOR Element of the structure of colors
//!
//}----------------------------------------------------------------------------
void print_color ( const char *line, enum Color_t COLOR, ... );
