#pragma once

#include <stdbool.h>

typedef struct MDK_BackgroundTask_struct MDK_BackgroundTask;

MDK_BackgroundTask* MDK_BackgroundTask_create(void (*taskMain)(void* data), void* data);
void MDK_BackgroundTask_destroy(MDK_BackgroundTask* task);

bool MDK_BackgroundTask_getIsRunning(MDK_BackgroundTask* task);

void MDK_BackgroundTask_stop(MDK_BackgroundTask* task);
