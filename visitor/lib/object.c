#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "object.h"

#include "visitor.h"

struct SObject {
    struct SObjectOps  *ops;
    void               *derived;
};

/* This method must be overrided by derived object. */
static void ErrorAccept(struct SObject * this, Visitor *visitor)
{
    printf("ERROR : Usage of not constructed object\n");
    exit(EXIT_FAILURE);
}

static struct SObjectOps errorOps = {
    .accept = ErrorAccept,
};

struct SObject * AllocateObject(void)
{
    struct SObject *this = malloc(sizeof(struct SObject));
    if (NULL == this)
        exit(EXIT_FAILURE);
    else
        memset(this, 0x00, sizeof(struct SObject));

    this->ops = &errorOps;

    return this;
}

void InitObject(struct SObject *this, struct SObjectOps *ops, void *derived)
{
    if(NULL == derived)
        exit(EXIT_FAILURE);
    else
        this->derived = derived;

    if(NULL != ops)
        this->ops = ops;
}

void * ObjectDownCast(struct SObject *this)
{
    return this->derived;
}

void Accept(Object *this, Visitor *visitor)
{
    this->ops->accept(this, visitor);
}
