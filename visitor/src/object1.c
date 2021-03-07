#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

/* Declarations check. */
#include "object1.h"

#include "object.h"
/* Object knows about base visitor, but not about concrete visitors. */
#include "visitor.h"

struct SObjType1 {
    Object *object; /**< Base object. */
    char    data[256];
};
/* Make upcast work.
 * Not necessary but sometimes useful. */
_Static_assert(offsetof(struct SObjType1, object) == 0,
               "Wrong object's structure. Base must be the first member.");

static void ObjType1Accept(Object *base, Visitor* visitor)
{
    printf("Object of type 1 accepting visitor\n");

    /* Object selects its own dedicated function pointer
     * in visitor interface.
     * Visitor at this point is abstract. */
    VisitorGetOps(visitor)->visitObjType1(visitor, base);
}

static ObjectOps ops = {
    .accept = ObjType1Accept,
};

struct SObjType1 *AllocateObjType1(void)
{
    struct SObjType1 *obj = malloc(sizeof(struct SObjType1));
    assert(NULL != obj);
    memset(obj, 0x00, sizeof(struct SObjType1));

    return obj;
}

void FreeObjType1(struct SObjType1 *this)
{
    assert(NULL != this);
    free(this);
    this = NULL;
}

void InitObjType1(struct SObjType1 *this, char *data)
{
    this->object = AllocateObject();
    /* Override ops here. */
    InitObject(this->object, &ops, this);
    snprintf(this->data, sizeof(this->data), "%s", data);
    printf("Initialized object of type 1\n");
}

void FiniObjType1(struct SObjType1 *this)
{
    memset(this->data, 0x00, sizeof(this->data));
    FiniObject(this->object);
    FreeObject(this->object);
}

Object * ObjType1GetBase(struct SObjType1 *this)
{
    return this->object;
}

char * ObjType1GetData(struct SObjType1 *this)
{
    return this->data;
}

