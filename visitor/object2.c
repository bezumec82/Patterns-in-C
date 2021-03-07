#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "object2.h"

struct SObjType2 {
    int val;
};

struct SObjType2 *AllocateObjType2(void)
{
    struct SObjType2 *obj = malloc(sizeof(struct SObjType2));
    if (NULL == obj)
        exit(EXIT_FAILURE);
    else
        memset(obj, 0x00, sizeof(struct SObjType2));
    return obj;
}

void InitObjType2(struct SObjType2 *this, int val)
{
    this->val = val;
    printf("Initialized object of type 2\n");
}

/* Pure getter/setter. */
int ObjType2GetVal(struct SObjType2 *this)
{
    return this->val;
}

/* Main idea here. */
void ObjType2Accept(struct SObjType2 *this, Visitor* visitor)
{
    printf("Object of type 2 accepting visitor\n");
    VisitorGetOps(visitor)->visitObjType2(visitor, this);
}
