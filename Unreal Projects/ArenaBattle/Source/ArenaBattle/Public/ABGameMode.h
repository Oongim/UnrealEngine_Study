// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/GameModeBase.h"
#include "ABGameMode.generated.h"

/* 캐릭터 무브먼트를 사용하는것이 FloatingPawnMovement에 비해 가지는 장점

* 점프와 같은 중력을 반영한 움직임을 제공
* 다양한 움직임 설정, 걷기, 기어가기, 날아가기, 수영 등 설정하고 현재 움직임에 더 많은 정보를 전달
* 멀티 플레이 네트워크 환경에서 캐릭터들의 움직임을 자동으로 동기화한다.

*/
UCLASS()
class ARENABATTLE_API AABGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	AABGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	//플레이어가 로그인을 완료하면 호출되는 함수, 플레이어가 조종할 폰을 생성하고 플레이어 컨트롤러가 해당 폰에 빙의하는 작업
};
