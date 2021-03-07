#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#include "object2.h"
#include "object.h"

struct SObjType2 {
    Object *object;
    int     val;
};
_Static_assert(offsetof(struct SObjType2, object) == 0,
               "Wrong object's structure. Base must be the first member.");

static void ObjType1Accept(Object *base, Visitor* visitor)
{
    printf("Object of type 1 accepting visitor\n");

    VisitorGetOps(visitor)->visitObjType2(visitor, base);
}

static ObjectOps ops = {
    .accept = ObjType1Accept,
};

struct SObjType2 *AllocateObjType2(void)
{
    struct SObjType2 *obj = malloc(sizeof(struct SObjType2));
    assert(NULL != obj);
    memset(obj, 0x00, sizeof(struct SObjType2));

    return obj;
}

void FreeObjType2(struct SObjType2 *this)
{
    assert(NULL != this);
    free(this);
    this = NULL;
}

void InitObjType2(struct SObjType2 *this, int val)
{
    this->object = AllocateObject();
    InitObject(this->object, &ops, this);
    this->val = val;
    printf("Initialized object of type 2\n");
}

void FiniObjType2(struct SObjType2 *this)
{
    this->val = 0;
    FiniObject(this->object);
    FreeObject(this->object);
}

Object * ObjType2GetBase(struct SObjType2 *this)
{
    return this->object;
}

int ObjType2GetVal(struct SObjType2 *this)
{
    return this->val;
}

