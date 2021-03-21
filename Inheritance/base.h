#ifndef __BASE_H__
#define __BASE_H__

typedef struct SBase Base;

Base * AllocateBase(void);

#include "internal.h"
/* Inheritance mechanism 1:
 * Base object provides de-typed interface #Override
 * that derived object must define and register
 * in base object at base object's construction time.
 * It is not so dangerous as it seems, cause sub-objects
 * don't know about each other, so it is impossible situation
 * to have different instance and method inside this structure. */
Base * AllocateBase1(void);
void BaseCostructor1(Base *this, Override *override)
void * Overriden1(Base *this, void *context);

/* Inheritance mechanism 2:
 * Derived object must register itself at base object construction time.
 * When application calls for base object overridden method - #Overriden2,
 * base object calls for overridden function pointer
 * and passes itself as this.
 * Derived object overrides method that takes base object pointer as 'this',
 * inside implementation, sub-object casts back base object pointer to itself.
 * This mechanism is close to the c++ implementation,
 * when object has virtual methods table and remembers what 'this' is.
 * */
Base * AllocateBase2(void);
void BaseConstructor2(Base *this, Ops *ops, void *derived);
void * Overriden2(Base *this, void *context);

#endif /* __BASE_H__ */
