#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <zip.h>

#include "ezxml/ezxml.h"

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
    const char *name = "content.xml";
    
    zip_stat_t st;
    zip_stat_init(&st);
    zip_stat(self->z, name, 0, &st);
    
    char* contents = malloc(st.size+1);

    zip_file_t* f = zip_fopen(self->z, name, 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);

    contents[st.size] = 0;

    char* text = strdup("");

    ezxml_t doc = ezxml_parse_str(contents, strlen(contents));

    for (ezxml_t el1 = ezxml_child(doc, "office:body"); el1; el1 = el1->next) {
      for (ezxml_t el2 = ezxml_child(el1, "office:text"); el2; el2 = el2->next) {
	for (ezxml_t el3 = ezxml_child(el2, "text:p"); el3; el3 = el3->next) {
	  //printf("txt: %s\n", el3->txt);
	  char* s = malloc(strlen(text) + strlen(el3->txt));
	  strcpy(s, text);
	  strcat(s, el3->txt);
	  free(text);
	  text = s;
	}
      }
    }

    ezxml_free(doc);
    
    free(contents);

    return text;
}

