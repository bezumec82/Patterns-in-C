#ifndef __OBJECT_2__
#define __OBJECT_2__

typedef struct SObjType2 ObjType2;

/* Allocator. */
ObjType2* AllocateObjType2(void);

/* Constructor. */
void InitObjType2(ObjType2 *this, int);

/* Public methods. */
int ObjType2GetVal(ObjType2 *this);

#include "visitor.h"
void ObjType2Accept(ObjType2 *this, Visitor* visitor);

#endif /* __OBJECT_2__ */
