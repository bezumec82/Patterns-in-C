/* This is the object's interface,
 * it forces its derived objects
 * to choose what visitor's method to use. */
#ifndef __OBJECT__
#define __OBJECT__

typedef struct SObject Object;

/* Pointer to the base type is the first 
 * member of derived object.
 * This is how to get it not knowing object's implementation */
#define UPCAST_OBJECT(derived) (*((Object **)(derived)))

#include "visitor.h"
typedef struct SObjectOps {
    void (*accept)(struct SObject * , Visitor *);
} ObjectOps;

/* Allocator. */
Object *AllocateObject(void);

/* Constructor. */
void InitObject(Object *this, ObjectOps *ops, void *derived);

/* Public methods. */
void *  ObjectDownCast  (Object *this);
void    Accept          (Object *this, Visitor *visitor);

/* Destructor. */
void FiniObject(Object *this);

/* De-allocator. */
void FreeObject(Object *this);

#endif /* __OBJECT__ */
