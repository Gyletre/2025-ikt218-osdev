#include "libc/stdint.h"
#include "libc/string.h"
int charNr = 0;
int lineNr = 0;
int test = 0;
size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
    {
        len++;
    }
    return len;
}
void write_to_console(char *string)
{
    test++;
    size_t len = strlen(string);

    char *video_memory = (char *)0xb8000;
    // Write to video memory
    for (size_t i = 0; i < len; i++)
    {
        if (string[i] == '\n')
        {
            lineNr += 1;
            charNr = 0;
            continue;
        }
        video_memory[(80 * lineNr + charNr) * 2] = string[i];
        video_memory[(80 * lineNr + charNr) * 2 + 1] = 0x07;
        charNr++;
    }
}