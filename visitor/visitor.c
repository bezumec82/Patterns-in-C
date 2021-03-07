#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

#include "visitor.h"

struct SVisitorOps;
struct SVisitor {
    struct SVisitorOps *ops;
    void               *derived;
};

/* Error porn. */
static void ErrorOp1(struct SVisitor *this, ObjType1 *obj)
{
    printf("ERROR : Usage of not constructed visitor\n");
    exit(EXIT_FAILURE);
}

static void ErrorOp2(struct SVisitor *this, ObjType2 *obj)
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

void InitVisitor(struct SVisitor *this, struct SVisitorOps *ops, void *derived)
{
    if(NULL == derived)
        exit(EXIT_FAILURE);
    else
        this->derived = derived;

    if(NULL != ops)
        this->ops = ops;
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
