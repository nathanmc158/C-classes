#include "classes.h"


Class* MakeClass(VTable* v, int type, Class* parent)
{
  Class* c = (Class*)malloc(sizeof(Class));
  if (parent == NULL)
  {
    switch (type)
    {
      case 1:
      // WILL NEED to be made mkre complicated with enforcement
        //MakeAbstract(c);
        break;
    }
  }
  c->MethodLookup = v;
  return c;
}

VTable* MakeVTable(size_t pubSize, Stub* pubInitList, size_t priSize, Stub* priInitList, size_t proSize, Stub* proInitList)
{
  VTable* v = (VTable*)malloc(sizeof(VTable));
  v->Public.Methods = pubInitList;
  v->Public.size = pubSize;
  v->Private.Methods = priInitList;
  v->Private.size = priSize;
  v->Protected.Methods = proInitList;
  v->Protected.size = proSize;
  return v;
}

void InitiateVTable(Class* c, size_t methodNumber)
{
  c->MethodLookup = (VTable*)malloc(methodNumber * sizeof(Stub));
}

/*void InitiateMemberVariables(Class* c, size_t variablesSize)
{
  c->MemberVariables = (MemberVariable**)malloc(variablesSize*sizeof(MemberVariable*));
}*/

/* oid MakeAbstract(Class* c)
{
  if (!c->interface)
    c->abstract = true;
}

void MakeInterface(Class* c)
{ 
  if (!c->abstract)
    c->interface = true;
}*/

int CurrType = 0;
typedef void* Type;
Type* TypeTable;

void EnsureTypeTableSize() {
  if (sizeof(TypeTable)<=CurrType)
  {
    TypeTable = realloc(TypeTable, sizeof(Type) * CurrType * 2 + 1);
  }
}

int SetNewType(void* Class) {
  EnsureTypeTableSize();
  TypeTable[CurrType++] = Class;
  return CurrType - 1;
}

int SetTypeFromInheritance(void* Derived, void** Bases, int Number)
{
  // alter VTable accordingly...
  return CurrType;
}

// assign a class
void AssignType(void* Class, void* Type)
{
  memcpy(Class, Type, sizeof(Type));
}

#define PUBLIC_MODIFIER 0
#define PROTECTED_MODIFIER 1
#define PRIVATE_MODIFIER 2
