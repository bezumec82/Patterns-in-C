#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#include "visitor.h"
#include "object.h"

struct SVisitor {
    struct SVisitorOps *ops;
    void               *derived;
};

/* Error porn. */
/* This is what happend if derived object not override methods. */
static void ErrorOp1(struct SVisitor *visitor, Object *object)
{
    printf("ERROR : Usage of not constructed visitor\n");
    exit(EXIT_FAILURE);
}

static void ErrorOp2(struct SVisitor *visitor, Object *object)
{
    printf("ERROR : Usage of not constructed visitor\n");
    exit(EXIT_FAILURE);
}

static struct SVisitorOps errorOps = {
    .visitObjType1 = ErrorOp1,
    .visitObjType2 = ErrorOp2,
};

struct SVisitor * AllocateVisitor(void)
{
    struct SVisitor *visitor = malloc(sizeof(struct SVisitor));
    if (NULL == visitor)
        exit(EXIT_FAILURE);
    else
        memset(visitor, 0x00, sizeof(struct SVisitor));

    visitor->ops = &errorOps;

    return visitor;
}

void FreeVisitor(struct SVisitor *this)
{
    assert(NULL != this);
    free(this);
    this = NULL;
}

void InitVisitor(struct SVisitor *this, struct SVisitorOps *ops, void *derived)
{
    assert(NULL != derived);
    assert(NULL != ops);

    this->derived = derived;
    this->ops = ops;
}

void FiniVisitor(struct SVisitor *this)
{
    /* Restore default ops. */
    this->ops = &errorOps;
    this->derived = NULL;
}

struct SVisitorOps * VisitorGetOps(struct SVisitor *visitor)
{
    printf("Returning visitor ops\n");
    return visitor->ops;
}

void * VisitorDownCast(struct SVisitor *visitor)
{
    return visitor->derived;
}
