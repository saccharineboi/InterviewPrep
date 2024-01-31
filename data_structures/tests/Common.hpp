#pragma once

////////////////////////////////////////
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_RESET    "\x1b[0m"

////////////////////////////////////////
#define TEST(EXPR, MESSAGE) \
    if (EXPR) \
        std::cout << (ANSI_COLOR_GREEN "[OK]\t" ANSI_COLOR_RESET); \
    else \
        std::cout << (ANSI_COLOR_RED "[ERROR]\t" ANSI_COLOR_RESET); \
    std::cout << (ANSI_COLOR_YELLOW MESSAGE ANSI_COLOR_RESET) << '\n'
