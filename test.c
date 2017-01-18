#include <stdio.h>
#include <stdlib.h>

#include "odt.h"

int main(int argc, char** argv)
{
    ODT* odt = odt_open("doc1.odt");
    char* meta = odt_get_text(odt);
    printf("meta:\n%s\n", meta);
    free(meta);
    odt_close(odt);
    return 0;
}
