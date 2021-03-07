#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

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
    memset(this, 0x00, sizeof(struct SObject));

    this->ops = &errorOps;

    return this;
}

void FreeObject(struct SObject *this)
{
    assert(NULL != this);
    free(this);
    this = NULL;
}

void InitObject(struct SObject *this, struct SObjectOps *ops, void *derived)
{
    assert(NULL != derived);
    assert(NULL != ops);

    this->derived = derived;
    this->ops = ops;
}

void FiniObject(struct SObject *this)
{
    /* Restore default ops. */
    this->ops = &errorOps;
    this->derived = NULL;
}

void * ObjectDownCast(struct SObject *this)
{
    assert(NULL != this->derived);
    return this->derived;
}

void Accept(Object *this, Visitor *visitor)
{
    this->ops->accept(this, visitor);
}
