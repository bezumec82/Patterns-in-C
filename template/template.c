#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "template.h"

/* Avoiding of use compound statement - ISO C. */
#define CALL_OP(instance, opName)                                   \
    do {                                                            \
        if (NULL != instance && NULL != instance->ops->opName)      \
            return instance->ops->opName(instance);                 \
        else                                                        \
            printf("Method %s is discarded\n", #opName);            \
    } while(0)

struct STemplate {
    struct STemplateOps    *ops;
    void                   *derived;
    /* Any common additional data goes here. */
};

/* Exportable, but not part of public interface. */
void * DefaultFetch(struct STemplate *this)
{
    printf("%s : Default, not re-implemented method is called\n", __func__);
    return this;
}

void * DefaultTreat(struct STemplate *this)
{
    printf("%s : Default, not re-implemented method is called\n", __func__);
    return this;
}

void * DefaultStore(struct STemplate *this)
{
    printf("%s : Default, not re-implemented method is called\n", __func__);
    return this;
}

/* Default ops is used when template instantiated by itself. */
static struct STemplateOps defaultOps = {
    .fetch = DefaultFetch,
    .treat = DefaultTreat,
    .store = DefaultStore
};

void * ErrorFetch(struct STemplate *this)
{
    printf("%s : Un-initialized template is used\n", __func__);
    exit(EXIT_FAILURE);
}

void * ErrorTreat(struct STemplate *this)
{
    printf("%s : Un-initialized template is used\n", __func__);
    exit(EXIT_FAILURE);
}

void * ErrorStore(struct STemplate *this)
{
    printf("%s : Un-initialized template is used\n", __func__);
    exit(EXIT_FAILURE);
}

/* Error ops is used when template isn't instantiated properly. */
static struct STemplateOps errorOps = {
    .fetch = ErrorFetch,
    .treat = ErrorTreat,
    .store = ErrorStore,
};

struct STemplate * AllocateTemplate(void)
{
    struct STemplate *template = malloc(sizeof(struct STemplate));
    assert(NULL != template);
    memset(template, 0x00, sizeof(struct STemplate));
    template->ops = &errorOps;
    return template;
}

void InitTemplate(struct STemplate *this, struct STemplateOps *ops, void *derived)
{
    /* Assume template can be used by itself. 
     * So we do not insist on inheritance. */
    if (NULL == ops)
        this->ops = &defaultOps;
    else
        this->ops = ops;

    this->derived = derived;
}

/* Public methods. */
void * Fetch(struct STemplate *this)
{
    CALL_OP(this, fetch);
    return this;
}

void * Treat(struct STemplate *this)
{
    CALL_OP(this, treat);
    return this;
}

void * Store(struct STemplate *this)
{
    CALL_OP(this, store);
    return this;
}

void * Process(struct STemplate *this)
{
    Fetch(this);
    Treat(this);
    Store(this); 
    return this;
}

/* Inheritance mechanism. */
void * TemplateDownCast(struct STemplate *this)
{
    return this->derived;
}

void FiniTemplate(struct STemplate *this)
{
    this->ops = &errorOps;
    this->derived = NULL;
}

void FreeTemplate(struct STemplate *this)
{
    assert(NULL != this);
    free(this);
    this = NULL;
}
