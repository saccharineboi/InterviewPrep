#include <string>
#include <iostream>
#include <cassert>
#include <cstring>

////////////////////////////////////////
#define IN_SPACE  1
#define OUT_SPACE 0

////////////////////////////////////////
void urlify(char* str, int length)
{
    // Time: O(n)
    // Space: O(1)
    assert(nullptr != str && "str cannot be NULL");
    int state{ OUT_SPACE };
    int i{}, j{};
    while (i < length && str[i] == ' ')
        ++i;
    for (; i < length; ++i) {
        if (str[i] == ' ') {
            state = IN_SPACE;
        }
        else if (state == IN_SPACE) {
            state = OUT_SPACE;
            str[j++] = '%';
            str[j++] = str[i];
        }
        else {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

////////////////////////////////////////
int main(int argc, char** argv)
{
    if (argc > 1) {
        std::cout << "You entered: " << argv[1] << '\n';

        int length = std::strlen(argv[1]);
        urlify(argv[1], length);

        std::cout << "URLified: " << argv[1] << '\n';
    }
    else {
        std::cout << "Usage: " << argv[0] << " <string>\n";
    }
}
