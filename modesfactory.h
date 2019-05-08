#ifndef MODES_FACTORY_H
#define MODES_FACTORY_H

#include "mode.h"

class ArgumentParser;

Mode* createMode(const ArgumentParser& argParser);

#endif