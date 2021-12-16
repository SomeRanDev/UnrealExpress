#pragma once

#include "UObject/ConstructorHelpers.h"

#define iload(VariableName, Path) \
	static ConstructorHelpers::FObjectFinder<std::remove_pointer_t<decltype(VariableName)>> Raw ## VariableName (TEXT("/Game/" Path));\
	if((Raw ## VariableName).Object != nullptr) {\
		VariableName = (Raw ## VariableName).Object;\
	}

#define load(UEClass, Path) LoadObject<UEClass>(nullptr, TEXT("/Game/" Path))
