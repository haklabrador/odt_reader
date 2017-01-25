#include <stdio.h>
#include <stdlib.h>

#include "odt.h"

int main(int argc, char** argv)
{
    ODT* odt = odt_open("doc1.odt");
    char* text = odt_get_text(odt);
    printf("text:\n%s\n", text);
    free(text);
    odt_close(odt);
    return 0;
}
