// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Components/ActorComponent.h"
#include "ABCharacterStatComponent.generated.h"

/*
액터 컴포넌트가 캐릭터에 의존성을 가지지 않도록, 델리게이트를 선언하고 캐릭터에서 이를 바인딩시키는 형태로 구조를 설계해본다
*/
DECLARE_MULTICAST_DELEGATE(FOnHPIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARENABATTLE_API UABCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

	public:
	// Sets default values for this component's properties
	UABCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	/*
	액터의 PostInitializeComponents에 대응하는 컴포넌트의 함수는 InitializeComponent이다
	이 함수는 PostInitializeComponents함수가 호출되기 바로 전에 호출된다.

	이 함수로 컴포넌트의 초기화 로직을 구현해주는데
	호출되려면 생성자에서 bWantsInitializeComponent을 true로 설정해줘야한다.
	*/
	virtual void InitializeComponent() override;

public:
	void SetNewLevel(int32 NewLevel);
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	float GetAttack();
	float GetHPRatio();

	FOnHPIsZeroDelegate OnHPIsZero;
	FOnHPChangedDelegate OnHPChanged;
private:
	struct FABCharacterData* CurrentStatData = nullptr;

	UPROPERTY(EditInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	int32 Level;
	/*언리얼 오브젝트에는 직렬화 기능이 있어서 오브젝트의 UPROPERTY 속성을 저장하고 로딩할 수 있다.
	하지만 CurrentHP 값은 게임을 시작할 때마다 변경되므로 이 값을 보관하는 것은 의미가 없고
	오히려 저장할 때 필요없는 디스크 공간만 차지한다.
	이러한 속성엔 Transient 키워드를 추가해 해당 속성을 직렬화에서 제외시키는 것이 좋다.*/
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;
};
