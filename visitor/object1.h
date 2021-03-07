#ifndef __OBJECT_1__
#define __OBJECT_1__

typedef struct SObjType1 ObjType1;

/* Allocator. */
ObjType1* AllocateObjType1(void);

/* Constructor. */
void InitObjType1(ObjType1 *this, char *data);

/* Public methods. */
char *ObjType1GetData(ObjType1 *this);

/* Objects know about base visitor, but not about concrete visitors. */
#include "visitor.h"
void ObjType1Accept(ObjType1 *this, Visitor* visitor);

#endif /* __OBJECT_1__ */
