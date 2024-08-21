#include <stdlib.h>

#include <MDK/Application.h>
#include <MDK/Application/StartEvent.h>
#include <MDK/Event.h>
#include <MDK/EventLoop.h>
#include <MDK/EventLoop/StopEvent.h>
#include <MDK/Object.h>
#include <MDK/RingBufferEventLoop.h>
#include <MDK/Shorthand.h>

static MDK_EventLoop* globalEventLoop;

static MDK_Object* startEventTarget = NULL;
static MDK_Application_StartEvent_Handler startEventHandler = NULL;

static void quitRequestEventDefaultHandler(MDK_Object* this, MDK_Event* event) {
  MDK_Application_quit();
}

static MDK_Object* quitRequestEventTarget = NULL;
static MDK_Event_Handler quitRequestEventHandler = quitRequestEventDefaultHandler;

int MDK_Application_start(int argc, char** argv) {
  MDK_EventLoop* eventLoop = (MDK_EventLoop*)MDK_RingBufferEventLoop_create();
  return MDK_Application_startWithEventLoop(argc, argv, eventLoop);
}

int MDK_Application_startWithEventLoop(int argc, char** argv, MDK_EventLoop* eventLoop) {
  globalEventLoop = eventLoop;
  REF(globalEventLoop);
  
  MDK_Application_StartEvent* startEvent = MDK_Application_StartEvent_create(startEventTarget, startEventHandler, argc, argv);
  MDK_Application_sendEvent(EVT(startEvent));
  
  MDK_EventLoop_run(globalEventLoop);
  
  UNREF(globalEventLoop);
  
  return 0;
}

void MDK_Application_pause() {
  MDK_EventLoop_pause(globalEventLoop);
}

void MDK_Application_resume() {
  MDK_EventLoop_resume(globalEventLoop);
}

void MDK_Application_sendEvent(MDK_Event* event) {
  MDK_EventLoop_sendEvent(globalEventLoop, event);
}

void MDK_Application_quit() {
  MDK_EventLoop_StopEvent* stopEvent = MDK_EventLoop_StopEvent_create();
  MDK_Application_sendEvent(EVT(stopEvent));
}

void MDK_Application_requestQuit() {
  MDK_Event* quitRequestEvent = MDK_Event_create(NULL, quitRequestEventTarget, quitRequestEventHandler);
  MDK_Application_sendEvent(quitRequestEvent);
}

void MDK_Application_onStart(MDK_Object* target, MDK_Application_StartEvent_Handler handler) {
  startEventTarget = target;
  startEventHandler = handler;
}

void MDK_Application_onQuitRequest(MDK_Object* target, MDK_Event_Handler handler) {
  quitRequestEventTarget = target;
  quitRequestEventHandler = handler;
}
