void print_color ( const char *line, enum Color_t COLOR, ... )
{
    HANDLE hConsole = GetStdHandle ( STD_OUTPUT_HANDLE );

    va_list args;
    va_start ( args, COLOR );

    SetConsoleTextAttribute ( hConsole, COLOR );

    vprintf ( line, args );

    SetConsoleTextAttribute ( hConsole, COLOR_WHITE );

    va_end ( args );
}
