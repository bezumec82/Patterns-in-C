#ifndef __TEMPLATE__
#define __TEMPLATE__

typedef struct STemplate Template;

/* Suppose we have some common algorithm/mechanism,
 * that can be divided into several distinctive methods.
 * This algorithm/mechanism encountered often enough,
 * but has some 'flavours' some time - the same at first glance,
 * but not completely.
 * For example : fetch/treat/store or prepare/execute/evaluate ...
 * Template approach let to re-implement some of the methods,
 * while other methods will be left in generic view.
 * To make method more generic, additional parameters to methods will
 * be contained inside object itself and return value will be saved there.
 * In other words, if derived object want to pass
 * additional parameters, or return something it must be saved in object.
 * If nothing can be returned from template/concrete method,
 * NULL must be passed. 
 * Some methods can be discarded completer, by setting pointer to NULL. */
typedef struct STemplateOps {
    void * (*fetch)(Template *);
    void * (*treat)(Template *);
    void * (*store)(Template *);
    /* ... whatever ... */
} TemplateOps;

/* Allocator. */
Template * AllocateTemplate(void);
/* Constructor. */
void InitTemplate(Template *this, TemplateOps *ops, void *derived);

/* Public methods. */
/* Returns derived object from base. */
void * TemplateDownCast(Template *this);

void * Fetch(Template *this);
void * Treat(Template *this);
void * Store(Template *this);

/* This method is the composition of previous three,
 * it calls full method chain one by one.
 * It is at user consideration how to use template. */
void * Process(Template *this);

/* Destructor. */
void FiniTemplate(Template *this);
/* De-allocator. */
void FreeTemplate(Template *this);

#endif /* __TEMPLATE__ */
