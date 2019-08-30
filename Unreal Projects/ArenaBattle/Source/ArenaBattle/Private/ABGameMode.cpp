// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameMode.h"
#include "ABCharacter.h"
/*ABCharacter ���͸� �����ϰ� �̸� �����ϴ� ���� �ƴ϶� Ŭ������ ������ �����Ѵ�
��Ƽ �÷��̱��� ����Ѵٸ� ���ӿ� �� ���� �÷��̾ ������ �𸣱� ������ 
Ŭ���� ������ �����س��� ������ ������� �����Ѵ�*/
#include "ABPlayerController.h"
#include "ABPlayerState.h"

AABGameMode::AABGameMode()
{
	DefaultPawnClass = AABCharacter::StaticClass();
	//�𸮾� ������Ʈ�� ABPawn�̷� ��� ���ϵ� ABPawn.h�� �Ǵµ� C++�� Ŭ���� �̸��� ���λ簡 �پ AABPawn�� ��
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