#ifndef __ODT_H__
#define __ODT_H__

struct sODT;
typedef struct sODT ODT;

ODT* odt_open(char* filename);
void odt_close(ODT* pODT);
int odt_get_creation_date(ODT* pODT);
char* odt_get_text(ODT* pODT); // caller must free returned memory

#endif

