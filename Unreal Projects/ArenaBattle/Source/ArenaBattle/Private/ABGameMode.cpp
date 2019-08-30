// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "ABCharacter.h"
/*ABCharacter 액터를 생성하고 이를 지정하는 것이 아니라 클래스의 정보를 지정한다
멀티 플레이까지 고려한다면 게임에 몇 명의 플레이어가 들어올지 모르기 때문에 
클래스 정보만 저장해놓고 정보를 기반으로 생성한다*/
#include "ABPlayerController.h"
#include "ABPlayerState.h"

AABGameMode::AABGameMode()
{
	DefaultPawnClass = AABCharacter::StaticClass();
	//언리얼 오브젝트도 ABPawn이록 헤더 파일도 ABPawn.h가 되는데 C++의 클래스 이름은 접두사가 붙어서 AABPawn이 됨
	PlayerControllerClass = AABPlayerController::StaticClass();
	PlayerStateClass = AABPlayerState::StaticClass();
}
void AABGameMode::PostLogin(APlayerController* NewPlayer)
{
	ABLOG(Warning, TEXT("PostLogin Begin"));
	Super::PostLogin(NewPlayer);
	ABLOG(Warning, TEXT("PostLogin End"));

	auto ABPlayerState = Cast<AABPlayerState>(NewPlayer->PlayerState);
	ABCHECK(nullptr != ABPlayerState);
	ABPlayerState->InitPlayerData();
}