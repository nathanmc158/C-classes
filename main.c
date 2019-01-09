#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


typedef struct _VTable
{
  struct _VTable* parentLookup;
  void** Methods;
  unsigned long size;
} VTable;

typedef struct _Class
{
  VTable lookup;
} Class;

void initiateVTable(Class *c, Class *parent)
{
  c->lookup.size = 0;
  if (parent != NULL)
    c->lookup.parentLookup = &(parent->lookup);
  c->lookup.Methods = (void**)malloc(16 * sizeof(void*));
}

void callMethodDirectly(VTable *v, unsigned long id, void* args)
{
  if (id < v->size)
    return ((void(*)())v->Methods[id])();
  else if (v->parentLookup != NULL)
    return callMethodDirectly(v->parentLookup, id - v->size, args);
}

void callMethod(Class *c, unsigned long id, int args, ...)
{
  return callMethodDirectly(&c->lookup, id, (void*)c);
  /*
  if (id < c->lookup.size)
  {
    // used as a reference to the stack
    int i = 3;
    printf("first: %d", (int)(*(&i-sizeof(c)-sizeof(id)-sizeof(args)-sizeof(id))));
    printf("calling\n");
    return ((void(*)())c->lookup.Methods[id])();
  } else if (c->lookup.parentLookup != NULL){
    // only one level of recursion
    return ((void(*)())c->lookup.parentLookup->Methods[id - c->lookup.size])();
  }*/
}

void addMethod(Class *c, void* fn)
{
  printf("addMethod running...\n");
  printf("c, mt size: %d   %d\n", sizeof(*c), sizeof(c->lookup));
  c->lookup.Methods[c->lookup.size] = fn;
  c->lookup.size++;
  printf("added method\n");
}

void print()
{
  printf("Oooh it kind of works! this line probably won't get called\n");
}

int main(void) {
  Class* parent = malloc(sizeof(Class));
  initiateVTable(parent, NULL);
  addMethod(parent, print);
  Class* clas = malloc(sizeof(Class));
  printf("memory allocated\nsetting vtable size to zero");
  initiateVTable(clas, parent);
  printf("calling addMethod from main\n");
  callMethod(clas, 0, 192, 12);
  printf("Hello World\n");
  free(clas);
  return 0;
}
