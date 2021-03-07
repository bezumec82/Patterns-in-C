#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "object1.h"

struct SObjType1 {
    char data[256];
};

struct SObjType1 *AllocateObjType1(void)
{
    struct SObjType1 *obj = malloc(sizeof(struct SObjType1));
    if (NULL == obj)
        exit(EXIT_FAILURE);
    else
        memset(obj, 0x00, sizeof(struct SObjType1));
    return obj;
}

void InitObjType1(struct SObjType1 *this, char *data)
{
    snprintf(this->data, sizeof(this->data), "%s", data);
    printf("Initialized object of type 1\n");
}

/* Pure getter/setter. */
char * ObjType1GetData(struct SObjType1 *this)
{
    return this->data;
}

/* Main idea here. */
void ObjType1Accept(struct SObjType1 *this, Visitor* visitor)
{
    printf("Object of type 1 accepting visitor\n");
    VisitorGetOps(visitor)->visitObjType1(visitor, this);
}
