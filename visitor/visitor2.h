#ifndef __VISITOR_2__
#define __VISITOR_2__

typedef struct SVisitor2 Visitor2;

/* Allocator. */
Visitor2 *AllocateVisitor2(void);

/* Constructor. */
void InitVisitor2(Visitor2 *this, int id);

#include "visitor.h"
/* Getters/Setters. */
Visitor * Visitor2GetBase(Visitor2 *this);

#endif /* __VISITOR_2__*/
