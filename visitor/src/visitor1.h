#ifndef __VISITOR_1__
#define __VISITOR_1__


typedef struct SVisitor1 Visitor1;

/* Allocator. */
Visitor1 *AllocateVisitor1(void);

/* Constructor. */
void InitVisitor1(Visitor1 *this, char *name);

/* Getters/Setters. */
#include "visitor.h"
Visitor * Visitor1GetBase(Visitor1 *this);

#endif /* __VISITOR_1__*/
