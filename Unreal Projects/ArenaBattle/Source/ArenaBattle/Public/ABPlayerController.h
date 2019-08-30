// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/PlayerController.h"
#include "ABPlayerController.generated.h"

/**
 * ���� �÷��̾� ��Ʈ�ѷ��� Ư�� �Է��� ó���ϴ� �ڵ带 �����ϸ� �ش� �Է��� �÷��̾� ��Ʈ�ѷ����� ���͸��� 
 ���� ���̻� ���޵��� �ʴ´�.
 */
UCLASS()
class ARENABATTLE_API AABPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AABPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;

	class UABHUDWidget* GetHUDWidget() const;

protected:
	virtual void BeginPlay() override;
	//�÷��̾� ��Ʈ�ѷ����� UI�� �����ϰ� ���ӿ��Ը� �Է��� �����ϵ��� ����� ������ ���ϰ� ������ �׽�Ʈ �� �� ����
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<class UABHUDWidget> HUDWidgetClass;

private:
	UPROPERTY()
	class UABHUDWidget* HUDWidget;
};
