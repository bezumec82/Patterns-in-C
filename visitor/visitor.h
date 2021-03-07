#ifndef __VISITOR_COMMON__
#define __VISITOR_COMMON__

#define VISITOR_NAME_MAX    16

typedef struct SVisitor Visitor;

/* Base visitor knows objects. */
#include "object1.h"
#include "object2.h"

/* Visitor abstract interface. */
typedef struct SVisitorOps {
    void (*visitObjType1)(struct SVisitor* , ObjType1* );
    void (*visitObjType2)(struct SVisitor* , ObjType2* );
} VisitorOps;

/* Allocator. */
Visitor * AllocateVisitor(void);

/* Constructor. */
void InitVisitor(Visitor *this, VisitorOps *ops, void *derived);

/* Setters/getters. */
VisitorOps* VisitorGetOps(Visitor *this);
void * VisitorDownCast(struct SVisitor *visitor);

#endif /* __VISITOR_COMMON__ */
