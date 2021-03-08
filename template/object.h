#ifndef __OBJECT__
#define __OBJECT__

typedef struct SObject Object;

/* Allocator. */
Object * AllocateObject(void);

/* Constructor. */
void InitObject(Object *this);

/* Public methods. */
#include "template.h"
Template *  ObjectGetBase  (Object *this);
char *      ObjectGetData  (Object *this);

/* Destructor. */
void FiniObject(Object *this);

/* De-allocator. */
void FreeObject(Object *this);

/* Pointer to the base type is the first member of derived object.
 * This is how to get it not knowing object's implementation */
#define UPCAST_OBJECT(derived) (*((Template **)(derived)))

#endif /* __OBJECT__ */
