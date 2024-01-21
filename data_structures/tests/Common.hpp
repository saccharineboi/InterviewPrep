#pragma once

////////////////////////////////////////
#define TEST(EXPR, MESSAGE) \
    if (EXPR) \
        std::cout << "[OK] "; \
    else \
        std::cout << "[ERROR] "; \
    std::cout << MESSAGE << '\n'
