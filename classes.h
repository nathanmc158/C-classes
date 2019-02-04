#ifndef CLASSES_H
#define CLASSES_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

//-------------define basic structures----------------\\

// method base object
typedef void (*Stub)();

// Variable types
typedef void* ArbitraryPointer;
typedef struct 
{
  ArbitraryPointer data;
  size_t Type;
} MemberVariable;

// bundling methods
typedef struct
{
  Stub* Methods;
  size_t size;
} MethodBundle;

// VTable to store methods and handle some inheritance
typedef struct
{
  // access modifiers
  MethodBundle Public;
  MethodBundle Protected;
  MethodBundle Private;
} VTable;


// class implementation:
// Yes, this can be changed but support is
// added through the helper funcs
typedef struct 
{
  MemberVariable* MemberVariables;
  VTable* MethodLookup;
  bool Abstract;
  bool Interface;
} Class;


// helper functions
// class implementation specific
/*
void MakeAbstract(Class* c)
{
  if (!c->Interface)
    c->Abstract = true;
}

void MakeInterface(Class* c)
{
  if (c->Abstract)
    return;
  c->MemberVariables = NULL;
  c->Interface = true;
}*/
// returns a class with all of the right stuff
Class* MakeClass();
// set VTable and variables respectively
// this is initiate here however
VTable* MakeVTable(size_t pubSize, Stub* pubInitList, size_t priSize, Stub* priInitList, size_t proSize, Stub* proInitList);
void MakeMemberVariables(Class* c, size_t pubNum, size_t priNum, size_t proNum);
// get VTables from parents and compile them
void Inherit(Class* c, Class** parents, short num);
// allocate heap space
void InitiateVTable();
void InitiateMemberVariables();
// generic method appendage
void BindMethod(Class* c, void* fn, void* fnb);
// Access modifiers allowing selective running
void AddPublicMethodBinding(Class* c, void* fn, void* fnb);
void AddPrivateMethodBinding(Class* c, void* fn, void* fnb);
void AddProtectedMethodBinding(Class* c, void* fn, void* fnb);
// override a virt func
void overideMethod(Class* c, short location, size_t id, void* fn);
#endif
