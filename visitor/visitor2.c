#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

/* Inheritance. */
#include "visitor.h"

/* Signature check. */
#include "visitor2.h"

/* Visitor knows it's hosts. */
#include "object1.h"
#include "object2.h"

struct SVisitor2 {
    Visitor *visitor; /**< base class */
    int id;
};
_Static_assert(offsetof(struct SVisitor2, visitor) == 0,
              "Wrong structure of structure");

static void VisitObjectType1(Visitor *base, ObjType1 *obj)
{
    printf("Object type 1 visited by visitor type 2\n");

    struct SVisitor2 *visitor = VisitorDownCast(base); 
    printf("Visitor ID %i : Data of object type 2 : %s\n",
           visitor->id, ObjType1GetData(obj));
}

static void VisitObjectType2(Visitor *base, ObjType2 *obj)
{
    printf("Object type 2 visited be visitor type 2\n");

    struct SVisitor2 *visitor = VisitorDownCast(base); 
    printf("Visitor ID %i : Data of object type 2 : %d\n",
           visitor->id, ObjType2GetVal(obj));
}

/* Each type of object has dedicated operation. */
static VisitorOps Visitor2Ops = {
    .visitObjType1 = VisitObjectType1,
    .visitObjType2 = VisitObjectType2,
};

struct SVisitor2 *AllocateVisitor2(void)
{
    struct SVisitor2 *visitor = malloc(sizeof(struct SVisitor2));
    if (NULL == visitor)
        exit(EXIT_FAILURE);
    else
        memset(visitor, 0x00, sizeof(struct SVisitor2));

    return visitor;
}

void InitVisitor2(struct SVisitor2 *this, int id)
{
    this->visitor = AllocateVisitor();
    InitVisitor(this->visitor, &Visitor2Ops, this);
    this->id = id;
    printf("Initialized visitor of type 2 with ID %i\n", this->id);
}

Visitor * Visitor2GetBase(struct SVisitor2 *this)
{
    return this->visitor;
}
