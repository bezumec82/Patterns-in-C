/* This is the visitor interface,
 * it forces its derived objects
 * to override methods for handling objects. */
#ifndef __VISITOR_COMMON__
#define __VISITOR_COMMON__

#define UPCAST_VISITOR(derived) (*((Visitor **)(derived)))

typedef struct SVisitor Visitor;

/* Abstract visitor knows about abstract object,
 * but not about concrete. */
#include "object.h"

/* Visitor abstract interface. */
typedef struct SVisitorOps {
    /* Each new type of object will receive dedicated
     * function pointer here.
     * But interface visitor knows only about interface object,
     * not about concrete objects. */
    void (*visitObjType1)(Visitor* , Object* );
    void (*visitObjType2)(Visitor* , Object* );
    /* In this example only the first couple is utilized. */

    void (*visitObjType3)(Visitor* , Object* );
    void (*visitObjType4)(Visitor* , Object* );
    /* ... For each type of object ... */
    void (*visitObjTypeN)(Visitor* , Object* );
} VisitorOps;

/* Allocator. */
Visitor * AllocateVisitor(void);

/* Constructor. */
void InitVisitor(Visitor *this, VisitorOps *ops, void *derived);

/* Setters/getters. */
VisitorOps *    VisitorGetOps   (Visitor *this);
void *          VisitorDownCast (Visitor *visitor);

/* Destructor. */
void FiniVisitor(Visitor *this);

/* De-allocator. */
void FreeVisitor(Visitor *this);

#endif /* __VISITOR_COMMON__ */
