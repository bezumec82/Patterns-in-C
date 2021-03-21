#include "internal.h"
#include "base.h"

struct SDerived {
    Base *base; /**< Base object will be constructed inside derived object. */
    void *anyData; /**< Some data or method 
                    * that extends base object. */
    void *(anyMethod)(struct SDerived *this, void *context);
};

void * ExtendedFunctionality(struct SDerived *this, void *context)
{
    /* Some extended functionality here. */
}

Derived * AllocateDerived(void)
{
    struct SDerived *derived = malloc(sizeof(struct SDerived));
    /* Check/assert results of allocation here: */
    /* ... */
    memset(derived, 0x00, sizeof(struct SDerived));

    return derived;
}

/*************************/
/* Override mechanism 1. */
/*************************/
void * OverridenMethod1(void *instance, void *context)
{
    struct SDerived *derived = (struct SDerived *)instance;
    derived->anyMethod(derived, derived->anyData);
    /* or */
    derived->anyMethod(derived, context);
}

static Override override = {
    .instance = NULL,
    .overriden = &overriddenMethod,
};

void DerivedConstructor1(struct SDerived *this)
{
    this->base = AllocateBase1();
    /* Assert/check that it actually happened. */
    
    override.instance = this;
    BaseConstructor1(this->base, &override);

    /* Some additional data/method initialization. */
    this->anyMethod = &ExtendedFunctionality;
}

/*************************/
/* Override mechanism 2. */
/*************************/
void DerivedConstructor2(struct SDerived *this)
{
    this->base = AllocateBase();
    /* Assert/check that it actually happened. */

    /* Register ops and itself at base object. */
    BaseConstructor2(this->base, &ops, this); 

    /* Some additional data/method initialization. */
    this->anyMethod = &ExtendedFunctionality;
}

static void * OverriddenMethod2(Base *base, void *context)
{
    /* This is kind of c++ dynamic cast - receiving derived object
     * from base at runtime. */
    struct SDerived * derived = BaseGetDerived(base);
    derived->anyMethod(derived, derived->anyData);
}

static Ops ops {
    .overridden = &OverriddenMethod2,
};

void DerivedConstructor2(struct SDerived *this)
{
    this->base = AllocateBase2();
    /* Assert/check that it actually happened. */

    /* Register ops and itself at base object. */
    BaseConstructor2(this->base, &ops, this); 

    /* Some additional data/method initialization. */
    this->anyMethod = &ExtendedFunctionality;
}
