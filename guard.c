#include "guard.h"

void warn_with_sys_msg(const char* msg) {
    fprintf(stderr, "%s%s%s: %s\n", ANSI_COLOR_RED, msg, ANSI_RESET_ALL, strerror(errno));

    return ;
}

/* ================================ */

void warn_with_user_msg(const char* msg, const char* details) {
    fprintf(stderr, "%s%s%s %serror%s: %s\n", ANSI_COLOR_YELLOW, msg, ANSI_RESET_ALL, ANSI_COLOR_RED, ANSI_RESET_ALL, details);

    return ;
}