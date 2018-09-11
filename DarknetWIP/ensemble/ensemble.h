#ifndef ENS_H
#define ENS_H

#include "../darknet/include/darknet.h"

#define NUM_CLASSES             6
#define TOPK                    1
#define NUM_NETS                1

// Initialisation functions
void initNets();
void initPredictData();
void destructNets();
void destructData(); 
void tryBackup();
void userInput();
void predictInput();

#endif