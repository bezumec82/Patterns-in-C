#ifndef __INTERNAL_H__
#define __INTERNAL_H__

/* This is header for the internal usage.
 * Users application must not include it and rely
 * on some interfaces described here. */

/*************************/
/* Override mechanism 1. */
/*************************/
/* As it appears more de-typing here. */
typedef struct {
    void *instance; /**< Derived object - object must set self here. */
    /** Derived object is passed here. */
    void * (*overridden) (void *instance, void *context);
} Override;

/*************************/
/* Override mechanism 2. */
/*************************/
/* Less de-typing, but dynamic cast is needed. */
void * BaseGetDerived(void);
typedef struct {
    void * (*overridden) (Base *this, void *context);
} Ops;

#endif /* __INTERNAL_H__ */
