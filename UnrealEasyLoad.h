#pragma once

#include "UObject/ConstructorHelpers.h"

// Based on https://stackoverflow.com/a/58658301
namespace UnrealEasyLoad {
	template<typename T> struct FirstTemplateTypeTempStruct;

	template<template<typename T, typename ...> class t, typename T, typename ...Args>
	struct FirstTemplateTypeTempStruct<t<T, Args...>> {
		typedef T first_type;
	};

	template<typename T>
	using first_template_type = typename FirstTemplateTypeTempStruct<T>::first_type;
};

#define iload(VariableName, Path) \
	static ConstructorHelpers::FObjectFinder<std::remove_pointer_t<decltype(VariableName)>> Raw ## VariableName (TEXT("/Game/" Path));\
	if((Raw ## VariableName).Object != nullptr) {\
		VariableName = (Raw ## VariableName).Object;\
	} else {\
		VariableName = nullptr;\
	}

#define iloadclass(VariableName, Path) \
	static ConstructorHelpers::FClassFinder<UnrealEasyLoad::first_template_type<decltype(VariableName)>> Raw ## VariableName (TEXT("/Game/" Path));\
	if((Raw ## VariableName).Class != nullptr) {\
		VariableName = (Raw ## VariableName).Class;\
	} else {\
		VariableName = nullptr;\
	}

#define load(UEClass, Path) LoadObject<UEClass>(nullptr, TEXT("/Game/" Path))
