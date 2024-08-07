#include <MDK/Event.h>
#include <MDK/Object.h>
#include <MDK/Shorthand.h>

MDK_Event* MDK_Event_create(MDK_Object* source, MDK_Object* target, MDK_Event_Handler handler) {
  MDK_Event* this = OBJ_CREATE(MDK_Event);
  MDK_Event_init(this, source, target, handler);
  return this;
}

void MDK_Event_init(MDK_Event* this, MDK_Object* source, MDK_Object* target, MDK_Event_Handler handler) {
  this->sig = MDK_Event_typeSig;
  
  this->source = source;
  if (source) {
    REF(source);
  }
  
  this->target = target;
  REF(target);
  
  this->handler = handler;
}

void MDK_Event_destroy(MDK_Event* this) {
  MDK_TypeSig_ensure(this->sig, MDK_Event_typeSig);
  
  if (this->source) {
    UNREF(this->source);
  }
  
  UNREF(this->target);
}
