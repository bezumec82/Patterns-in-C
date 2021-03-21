#include "internal.h"

struct SBase {
    /** Mechanism 1. */
    Override *override;

    /** Mechanism 2. */
    void *derived;
    Ops *ops;
};

/*************************/
/* Override mechanism 1. */
/*************************/
void * DefaultMethod1(void *instance, void *context)
{
    /* If base object just an interface, and must no provide any functionality,
     * this method must exit with error about un-initialized interface usage.
     * If base object can provide some functionality, that can be overridden,
     * this is where such base functionality must be implemented. */

    return NULL;
}

static Override defaultOverride = {
    .instance = NULL,
    .overriden = &defaultMethod1,
};

Base *AllocateBase1(void)
{
    Base *base = malloc(sizeof(struct SBase));
    /* Check/assert results of allocation here: */
    /* ... */
    memset(base, 0x00, sizeof(struct SBase));

    defaultOverride.insance = this;
    base->override = defaultOverride; 

    return base;
}

void BaseCostructor1(Base *this, Override *override)
{
    if (override != NULL) {
        assert(override->instance != NULL);
        this-override = override;
    } else {
        /* If base is an interface this is an error. */
    }
}

void *Overriden1(Base *this, void *context)
{
    return this->override->overridden(this->override->instance, context);
}

/*************************/
/* Override mechanism 2. */
/*************************/
void * DefaultMethod2(struct SBase *this, void *context)
{
    /* As before. */

    return NULL;
}

static Ops defaultOps = {
    .overridden = &DefaultMethod2,
};

Base *AllocateBase2(void)
{
    Base *base = malloc(sizeof(struct SBase));
    /* Check/assert results of allocation here: */
    /* ... */
    memset(base, 0x00, sizeof(struct SBase));

    base->ops = &defaultOps; 

    return base;
}

void BaseConstructor2(struct SBase *this, Ops *ops, void *derived)
{
    /* If base is not an interface, it must be legitimate
     * to instantiate base object by itself. */
    if (NULL != ops && NULL != derived) {
        this->ops = ops;
        this->derived = derived;
    }

    /* All half-initialisations in any case are erroneous. */
    if ((NULL == ops && derived != NULL) ||
        (NULL != ops && derived == NULL)) {
        /* Kill this Frankenstein. */
    }
}

void * Overriden2(Base *this, void *context)
{
    return this->ops->overriden(this, context);
}

void * BaseGetDerived(struct SBase *this)
{
    return this->derived;
}
