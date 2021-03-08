#include <stddef.h>
#include <stdio.h>

#include "template.h"
#include "object.h"

int main(int argc, char **argv)
{
    Template * template1 = NULL;
    Template * template2 = NULL;
    Template * template3 = NULL;
    Object * object1     = NULL;
    Object * object2     = NULL;

    printf("\n=== First case - use template by itself ===\n");
    template1 = AllocateTemplate();
    InitTemplate(template1, NULL, NULL);
    Process(template1);
    FiniTemplate(template1);
    FreeTemplate(template1);

    printf("\n=== Second case - step by step omitting store ===\n");
    template2 = AllocateTemplate();
    InitTemplate(template2, NULL, NULL);
    Fetch(template2);
    Treat(template2);
    FiniTemplate(template2);
    FreeTemplate(template2);

    printf("\n=== Third case - derived object ===\n");
    object1 = AllocateObject();
    InitObject(object1);
    Process(ObjectGetBase(object1));
    printf("\nObject's data after precessing : %s\n", ObjectGetData(object1));
    FiniObject(object1);
    FreeObject(object1);

    printf("\n=== Fourth case - derived object step by step ===\n"); 
    object2 = AllocateObject();
    InitObject(object2);
    Fetch(UPCAST_OBJECT(object2));
    Treat(UPCAST_OBJECT(object2));
    Store(UPCAST_OBJECT(object2));
    FiniObject(object2);
    FreeObject(object2);

    printf("\n=== Attempt to use un-initialized template ===\n");
    template3 = AllocateTemplate();
    Process(template3);
}
