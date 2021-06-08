#pragma once

#include <string>

#define uelog UnrealEasyPrintImpl<false, 0>()
#define uewarn UnrealEasyPrintImpl<false, 1>()
#define ueerror UnrealEasyPrintImpl<false, 2>()

#define ueshow UnrealEasyPrintImpl<true, 0>()
#define ueshowwarn UnrealEasyPrintImpl<true, 1>()
#define ueshowerror UnrealEasyPrintImpl<true, 2>()

template<bool IsShow, int Level>
class UnrealEasyPrintImpl {
public:
	UnrealEasyPrintImpl() {}

	~UnrealEasyPrintImpl() {
		if(!Output.IsEmpty()) {
			constexpr bool IsLog = Level == 0;
			constexpr bool IsWarning = Level == 1;
			constexpr bool IsError = Level == 2;
			if constexpr(IsShow) {
				if(GEngine) {
					const FColor Color = IsLog ? FColor::White : (IsWarning ? FColor::Yellow : FColor::Red);
					GEngine->AddOnScreenDebugMessage(-1, 5.f, Color, Output);
				}
			} else {
				if constexpr(IsLog) UE_LOG(LogTemp, Log, TEXT("%s"), *Output);
				if constexpr(IsWarning) UE_LOG(LogTemp, Warning, TEXT("%s"), *Output);
				if constexpr(IsError) UE_LOG(LogTemp, Error, TEXT("%s"), *Output);
			}
		}
	}

	void AddText(const FString& Input) {
		Output += (Output.IsEmpty() ? "" : " ") + Input;
	}

	template<typename T>
	UnrealEasyPrintImpl& operator<<(const T& Input) {
		AddText(Input.ToString());
		return *this;
	}

	#define AddShiftOperator(Type, Expr)\
	UnrealEasyPrintImpl& operator<<(const Type Input) {\
		AddText(Expr);\
		return *this;\
	}

	// Primitives
	AddShiftOperator(std::nullptr_t, "nullptr")
	AddShiftOperator(bool, Input ? TEXT("true") : TEXT("false"))
	AddShiftOperator(void*, FString::Printf(TEXT("%p"), Input))
	AddShiftOperator(char*, Input != nullptr ? Input : FString(TEXT("nullptr")))

	// Numbers
	AddShiftOperator(int32, FString::FromInt(Input))
	AddShiftOperator(char, FString::Printf(TEXT("%c"), Input))
	AddShiftOperator(unsigned char, FString::Printf(TEXT("%u"), Input))
	AddShiftOperator(short, FString::Printf(TEXT("%hd"), Input))
	AddShiftOperator(unsigned short, FString::Printf(TEXT("%hu"), Input))
	AddShiftOperator(long, FString::Printf(TEXT("%ld"), Input))
	AddShiftOperator(unsigned long, FString::Printf(TEXT("%lu"), Input))
	AddShiftOperator(long long, FString::Printf(TEXT("%lld"), Input))
	AddShiftOperator(unsigned long long, FString::Printf(TEXT("%llu"), Input))
	AddShiftOperator(float, FString::SanitizeFloat(Input))
	AddShiftOperator(double, FString::SanitizeFloat(Input))
	AddShiftOperator(long double, FString::Printf(TEXT("%Lg"), Input))

	// Strings
	AddShiftOperator(FString&, Input)
	AddShiftOperator(TCHAR*, Input)
	AddShiftOperator(std::string&, Input)

	// Unreal Objects
	AddShiftOperator(UObject*, Input != nullptr ? Input->GetName() : FString(TEXT("nullptr")))

	#undef AddShiftOperator
	
	template<typename T>
	UnrealEasyPrintImpl& operator()(T Input) {
		operator<<(Input);
		return *this;
	}
	
	template<typename T, typename ...Args>
	UnrealEasyPrintImpl& operator()(T Input, Args... args) {
		operator<<(Input);
		operator()(args...);
		return *this;
	}
	
	FString Output;
};
