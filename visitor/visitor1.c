#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

/* Inheritance. */
#include "visitor.h"

/* Signature check. */
#include "visitor1.h"

/* Visitor knows it's hosts. */
#include "object1.h"
#include "object2.h"

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

struct SVisitor1 {
    Visitor *visitor; /**< base class */
    char name[VISITOR_NAME_MAX];
};
_Static_assert(offsetof(struct SVisitor1, visitor) == 0,
              "Wrong structure of visitor object");

/* All objects has diffrent type of data.
 * All visitors has diffrent type of actions. */
static void VisitObjectType1(Visitor *base, ObjType1 *obj)
{
    printf("Object type 1 visited be visitor type 1\n");

    struct SVisitor1 *visitor = VisitorDownCast(base); 
    printf("%s : Data of object type 1 : %s\n",
           visitor->name, ObjType1GetData(obj));
}

static void VisitObjectType2(Visitor *base, ObjType2 *obj)
{
    printf("Object type 2 visited be visitor type 1\n");

    struct SVisitor1 *visitor = VisitorDownCast(base); 
    printf("%s : Data of object type 2 : %d\n",
           visitor->name, ObjType2GetVal(obj));
}

/* Each type of object has dedicated operation. */
static VisitorOps Visitor1Ops = {
    .visitObjType1 = VisitObjectType1,
    .visitObjType2 = VisitObjectType2,
};

struct SVisitor1 *AllocateVisitor1(void)
{
    struct SVisitor1 *visitor = malloc(sizeof(struct SVisitor1));
    if (NULL == visitor)
        exit(EXIT_FAILURE);
    else
        memset(visitor, 0x00, sizeof(struct SVisitor1));

    return visitor;
}

void InitVisitor1(struct SVisitor1 *this, char *name)
{
    this->visitor = AllocateVisitor();
    InitVisitor(this->visitor, &Visitor1Ops, this);
    snprintf(this->name, sizeof(this->name), "%s", name);
    printf("Initialized visitor of type 1 with name %s\n", this->name);
}

Visitor * Visitor1GetBase(struct SVisitor1 *this)
{
    return this->visitor;
}
