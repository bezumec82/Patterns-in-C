#include <stdio.h>

#include "object1.h"
#include "object2.h"

#include "visitor1.h"
#include "visitor2.h"

#include "visitor.h"

int main(int argc, char *argv[])
{
    /* ObjType1 and ObjType2 closed for changes.
     * New functionality must be introduced through visitors. */
    ObjType1 *obj1 = AllocateObjType1();
    InitObjType1(obj1, "some data");

    ObjType2 *obj2 = AllocateObjType2();
    InitObjType2(obj2, 42);

    Visitor1 *vtr1 = AllocateVisitor1();
    InitVisitor1(vtr1, "visitor1");

    Visitor2 *vtr2 = AllocateVisitor2();
    InitVisitor2(vtr2, 108);

    printf("Start visiting objects :\n");
    ObjType1Accept(obj1, Visitor1GetBase(vtr1));
    ObjType1Accept(obj1, Visitor2GetBase(vtr2));

    ObjType2Accept(obj2, Visitor1GetBase(vtr1));
    ObjType2Accept(obj2, Visitor2GetBase(vtr2));
}
