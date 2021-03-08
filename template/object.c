#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "template.h"
#include "object.h"

struct SObject {
    Template *base;
    char data[256]; /* For example. */
};
/* Make upcast work.
 * Not necessary but sometimes useful. */
_Static_assert(offsetof(struct SObject, base) == 0,
               "Wrong object's structure. Base must be the first member.");

/* Protected methods of template. */
extern void * DefaultFetch(Template *this);
extern void * DefaultTreat(Template *this);
extern void * DefaultStore(Template *this);

void * ObjectTreat(Template *base)
{
    printf("Object's treat is calling for default treat :\n");
    /* Actually we even can extend default implementation : */
    DefaultTreat(base);
    /* with custom treatment : */
    struct SObject *this = TemplateDownCast(base);
    printf("Data before treatment : %s\n", this->data);
    memset(this->data, 0x00, sizeof(this->data));
    snprintf(this->data, sizeof(this->data), "%s", "treated data");
    return NULL;
}

static TemplateOps objectOps = {
    /* Leave fetch default. */
    .fetch = DefaultFetch,
    /* Redefine treat. */
    .treat = ObjectTreat,
    /* Disable store. */
    .store = NULL,
};

struct SObject * AllocateObject(void)
{
    struct SObject *this = malloc(sizeof(struct SObject));
    assert(NULL != this);
    memset(this, 0x00, sizeof(struct SObject));
    return this;
}

void InitObject(struct SObject *this)
{
    this->base = AllocateTemplate();
    InitTemplate(this->base, &objectOps, this);
    /* Initialize data. */
    snprintf(this->data, sizeof(this->data), "%s", "initialized data");
}

/* Getters/setters. */
char * ObjectGetData(struct SObject *this)
{
    return this->data;
}

Template * ObjectGetBase(struct SObject *this)
{
    return this->base;
}

void FiniObject(struct SObject *this)
{
   FiniTemplate(this->base);    
   FreeTemplate(this->base);
   memset(this, 0x00, sizeof(struct SObject));
}

void FreeObject(struct SObject *this)
{
    assert(NULL != this);
    free(this);
    this = NULL;
}
