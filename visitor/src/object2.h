#ifndef __OBJECT_2__
#define __OBJECT_2__

typedef struct SObjType2 ObjType2;

/* Allocator. */
ObjType2* AllocateObjType2(void);

/* Constructor. */
void InitObjType2(ObjType2 *this, int);

/* Public methods. */
#include "object.h"
Object *    ObjType2GetBase (ObjType2 *this);
int         ObjType2GetVal  (ObjType2 *this);

/* Destructor. */
void FiniObjType2(ObjType2 *this);

/* De-allocator. */
void FreeObjType2(ObjType2 *this);

#endif /* __OBJECT_2__ */
