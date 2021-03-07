#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stddef.h>

/* Inheritance. */
#include "visitor.h"

/* Signature check. */
#include "visitor1.h"

/* Concrete visitor knows it's hosts. */
#include "object1.h"
#include "object2.h"

#define VISITOR_NAME_MAX    16

struct SVisitor1 {
    Visitor *visitor; /**< Base object. */
    char name[VISITOR_NAME_MAX];
};
/* Make upcast work. */
_Static_assert(offsetof(struct SVisitor1, visitor) == 0,
               "Wrong object's structure. Base must be the first member.");

/* All objects have diffrent type of data.
 * All visitors have diffrent type of actions. */
static void VisitObjectType1(Visitor *base, Object *obj)
{
    printf("Object type 1 visited be visitor type 1\n");

    /* !!!ATTENTION!!!
     * Getting wrong type here is UB. */
    struct SVisitor1   *visitor = VisitorDownCast(base); 
    ObjType1           *object  = ObjectDownCast(obj);

    printf("%s : Data of object type 1 : %s\n",
           visitor->name, ObjType1GetData(object));
}

static void VisitObjectType2(Visitor *base, Object *obj)
{
    printf("Object type 2 visited be visitor type 1\n");

    struct SVisitor1   *visitor = VisitorDownCast(base); 
    ObjType2           *object  = ObjectDownCast(obj);
    printf("%s : Data of object type 2 : %d\n",
           visitor->name, ObjType2GetVal(object));
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
