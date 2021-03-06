#ifndef __VISITOR_2__
#define __VISITOR_2__

typedef struct SVisitor2 Visitor2;

/* Allocator. */
Visitor2 *AllocateVisitor2(void);

/* Constructor. */
void InitVisitor2(Visitor2 *this, int id);

/* Getters/Setters. */
#include "visitor.h"
Visitor * Visitor2GetBase(Visitor2 *this);

/* Destructor. */
void FiniVisitor2(Visitor2 *this);

/* De-allocator. */
void FreeVisitor2(Visitor2 *this);

#endif /* __VISITOR_2__*/
