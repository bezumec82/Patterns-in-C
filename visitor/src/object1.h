#ifndef __OBJECT_1__
#define __OBJECT_1__

typedef struct SObjType1 ObjType1;

/* Allocator. */
ObjType1* AllocateObjType1(void);

/* Constructor. */
void InitObjType1(ObjType1 *this, char *data);

/* Public methods. */
#include "object.h"
Object *    ObjType1GetBase (ObjType1 *this);
char *      ObjType1GetData (ObjType1 *this);

#endif /* __OBJECT_1__ */
