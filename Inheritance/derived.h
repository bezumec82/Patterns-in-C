#ifndef __DERIVED_H__
#define __DERIVED_H__

typedef struct SDerived Derived;

Derrived * AllocateDerived(void);
void DerivedConstructor1(Derived *this);
void DerivedConstructor2(Derived *this);

#endif /* __DERIVED_H__ */
