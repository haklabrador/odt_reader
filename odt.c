#include <stddef.h>
#include <stdlib.h>

#include <zip.h>

#include "odt.h"

struct sODT {
  zip_t *z;
};

ODT* odt_open(char* filename)
{
    ODT* self = malloc(sizeof(ODT));
    int err = 0;
    self->z = zip_open(filename, 0, &err);
    printf("odt_open: err: %d\n", err);
    return self;
}

void odt_close(ODT* self)
{
    zip_close(self->z);
    free(self);
}

int odt_get_creation_date(ODT* self)
{
    return 0;
}

char* odt_get_text(ODT* self)
{
    const char *name = "meta.xml";
    zip_stat_t st;
    zip_stat_init(&st);
    zip_stat(self->z, name, 0, &st);
    
    char* contents = malloc(st.size+1);

    zip_file_t* f = zip_fopen(self->z, name, 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);

    contents[st.size] = 0;

    return contents;
}

