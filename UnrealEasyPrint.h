#pragma once

#define HBShow(str) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(str)));
#define HBShow1(str, num) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(str), num));
#define HBShow2(str, num1, num2) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(str), num1, num2));
#define HBShow3(str, num1, num2, num3) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(str), num1, num2, num3));
#define HBShow5(str, num1, num2, num3, num4, num5) if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT(str), num1, num2, num3, num4, num5));

#define HBPrint5(str, num1, num2, num3, num4, num5) UE_LOG(LogTemp, Warning, TEXT(str), num1, num2, num3, num4, num5);
