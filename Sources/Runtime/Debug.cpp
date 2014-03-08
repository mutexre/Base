#include <iostream>
#ifdef __APPLE__
    #include <execinfo.h>
#endif
#include <Runtime/Runtime.h>

void Rt::dump(const void* buf, u4 nbytes) {
    int i, j;
    int rows = nbytes > 16 ? nbytes / 16 + 1 : 1;
    int nbytes_printed = 0;
    int nbytes_curr_row = 0;
    bool row_is_all_zero = false;
    bool zero_rows = false;

    RtLog("Dump:\n");

    for (i = 0; i < rows; i++)
    {
        nbytes_curr_row = nbytes - nbytes_printed > 16 ? 16 : nbytes - nbytes_printed;

        if (i) {
            row_is_all_zero = true;
            for (j = 0; j < nbytes_curr_row; j++) {
                if (*((u1*)buf + 16 * i + j) != 0)
                    row_is_all_zero = false;
            }
        }

        if (i == rows-1 && zero_rows && row_is_all_zero)
            RtLog("*\n");

        if (!row_is_all_zero)
        {
            if (zero_rows) {
                RtLog("*\n");
                zero_rows = false;
            }

            RtLog("%04x: ", 16 * i);
            for (j = 0; j < 16; j++)
            {
                if (j < nbytes_curr_row) {
                    RtLog("%02x ", *((u1*) buf + 16 * i + j));
                    if (7 == j) RtLog(" ");
                }
                else
                    if (rows > 1) RtLog("   ");
            }
            RtLog(" ");
            for (j = 0; j < nbytes_curr_row; j++)
            {
                if ((*((char*)buf + 16 * i + j) >= 32) && (*((u1*)buf + 16 * i + j) <= 126))
                    RtLog("%c", *((u1*)buf + 16 * i + j));
                else 
                    RtLog(".");
            }
            RtLog("\n");
        }
        else
            zero_rows = true;

        nbytes_printed += nbytes_curr_row;
    }
}

std::string Rt::stringFormat(const char* fmt, va_list args) {
    s4 size = 1 << 7;
    std::string str;

    while (1) {
        str.resize(size);
        auto n = vsnprintf((char*)str.c_str(), size, fmt, args);

        if (n > -1) {
            if (n < size) {
                str.resize(n);
                return str;
            }

            size = n + 1;
        }
        else
            size *= 2;
    }

    return str;
}

void Rt::error(u4 ID) {
    Rt::printBacktrace(STDERR_FILENO);
    throw ID;
}

void Rt::error(u4 ID, const char* fmt, ...) {
    va_list args;
    auto str = std::to_string(ID);
    str += " ";

    va_start(args, fmt);
    str += stringFormat(fmt, args);
    va_end(args);

    Rt::printBacktrace(STDERR_FILENO);
    throw str;
}

void Rt::printBacktrace(int fileno) {
    #ifdef __APPLE__
    void* array[128];
    auto size = backtrace(array, 100);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    #endif
}
