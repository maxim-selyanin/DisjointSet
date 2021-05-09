#include "common.h"

s_debug &no_space(s_debug &d) {
#ifndef NO_DEBUG
    d.no_space();
#endif
    return d;
}
s_debug &enable_space(s_debug &d) {
#ifndef NO_DEBUG
    d.enable_space();
#endif
    return d;
}
s_debug &no_newline(s_debug &d) {
#ifndef NO_DEBUG
    d.no_newline();
#endif
    return d;
}
s_debug &enable_newline(s_debug &d) {
#ifndef NO_DEBUG
    d.enable_newline();
#endif
    return d;
}

s_debug &s_debug::no_space() {
#ifndef NO_DEBUG
    space = false;
#endif
    return *this;
}

s_debug &s_debug::enable_space() {
#ifndef NO_DEBUG
    space = true;
#endif
    return *this;
}

s_debug &s_debug::no_newline() {
#ifndef NO_DEBUG
    newline = false;
#endif
    return *this;
}

s_debug &s_debug::enable_newline() {
#ifndef NO_DEBUG
    newline = true;
#endif
    return *this;
}

s_debug::~s_debug()
#ifndef NO_DEBUG
{
    if (newline) {
        std::cout << '\n';
    }
};
#else
    = default;
#endif