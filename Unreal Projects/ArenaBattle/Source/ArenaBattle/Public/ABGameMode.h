// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/GameModeBase.h"
#include "ABGameMode.generated.h"

/* ĳ���� �����Ʈ�� ����ϴ°��� FloatingPawnMovement�� ���� ������ ����

* ������ ���� �߷��� �ݿ��� �������� ����
* �پ��� ������ ����, �ȱ�, ����, ���ư���, ���� �� �����ϰ� ���� �����ӿ� �� ���� ������ ����
* ��Ƽ �÷��� ��Ʈ��ũ ȯ�濡�� ĳ���͵��� �������� �ڵ����� ����ȭ�Ѵ�.

*/
UCLASS()
class ARENABATTLE_API AABGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	AABGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	//�÷��̾ �α����� �Ϸ��ϸ� ȣ��Ǵ� �Լ�, �÷��̾ ������ ���� �����ϰ� �÷��̾� ��Ʈ�ѷ��� �ش� ���� �����ϴ� �۾�
};
