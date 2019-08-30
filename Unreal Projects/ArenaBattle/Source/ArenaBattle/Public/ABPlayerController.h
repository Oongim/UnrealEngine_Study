// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/PlayerController.h"
#include "ABPlayerController.generated.h"

/**
 * 만일 플레이어 컨트롤러에 특정 입력을 처리하는 코드를 구현하면 해당 입력은 플레이어 컨트롤러에서 필터링돼 
 폰에 더이상 전달되지 않는다.
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
	//플레이어 컨트롤러에게 UI를 배제하고 게임에게만 입력을 전달하도록 명령을 내려서 편리하게 게임을 테스트 할 수 있음
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<class UABHUDWidget> HUDWidgetClass;

private:
	UPROPERTY()
	class UABHUDWidget* HUDWidget;
};
