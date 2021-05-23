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
					constexpr FColor Color = IsLog ? FColor::White : (IsWarning ? FColor::Yellow : FColor::Red);
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

	UnrealEasyPrintImpl& operator<<(const FString& Input) {
		AddText(Input);
		return *this;
	}

	UnrealEasyPrintImpl& operator<<(const std::nullptr_t) {
		AddText("nullptr");
		return *this;
	}
	
	UnrealEasyPrintImpl& operator<<(const int Input) {
		AddText(FString::FromInt(Input));
		return *this;
	}

	UnrealEasyPrintImpl& operator<<(const float Input) {
		AddText(FString::SanitizeFloat(Input));
		return *this;
	}

	UnrealEasyPrintImpl& operator<<(const bool Input) {
		AddText(Input ? TEXT("true") : TEXT("false"));
		return *this;
	}

	UnrealEasyPrintImpl& operator<<(const char* Input) {
		AddText(Input);
		return *this;
	}

	UnrealEasyPrintImpl& operator<<(const std::string& Input) {
		AddText(Input);
		return *this;
	}
	
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
