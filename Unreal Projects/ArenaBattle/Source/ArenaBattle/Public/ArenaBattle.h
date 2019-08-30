// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h" //다양한 엔진 기능이 필요해서 엔진 클래스 선언을 모아둔 파일

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	PREINIT,
	LOADING,
	READY,
	DEAD
};

//ArenaBattle이라는 로그 카테고리를 정의하는 듯
DECLARE_LOG_CATEGORY_EXTERN(ArenaBattle, Log, All);

#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(")+FString::FromInt(__LINE__)+TEXT(")"))
#define ABLOG_S(Verbosity) UE_LOG(ArenaBattle, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
//코드가 들어있는 파일 이름과 함수, 라인 정보를 추가해 로그로 남김
#define ABLOG(Verbosity, Format, ...) UE_LOG(ArenaBattle, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))
//ABLOG_S 정보에 형식 문자열로 추가 정보를 지정해 로그를 남김

#define ABCHECK(Expr,...){if(!(Expr)){ABLOG(Error, TEXT("ASSERTION : %s"),TEXT("'"#Expr"'")); return __VA_ARGS__;}}