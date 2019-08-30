// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Components/ActorComponent.h"
#include "ABCharacterStatComponent.generated.h"

/*
���� ������Ʈ�� ĳ���Ϳ� �������� ������ �ʵ���, ��������Ʈ�� �����ϰ� ĳ���Ϳ��� �̸� ���ε���Ű�� ���·� ������ �����غ���
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
	������ PostInitializeComponents�� �����ϴ� ������Ʈ�� �Լ��� InitializeComponent�̴�
	�� �Լ��� PostInitializeComponents�Լ��� ȣ��Ǳ� �ٷ� ���� ȣ��ȴ�.

	�� �Լ��� ������Ʈ�� �ʱ�ȭ ������ �������ִµ�
	ȣ��Ƿ��� �����ڿ��� bWantsInitializeComponent�� true�� ����������Ѵ�.
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
	/*�𸮾� ������Ʈ���� ����ȭ ����� �־ ������Ʈ�� UPROPERTY �Ӽ��� �����ϰ� �ε��� �� �ִ�.
	������ CurrentHP ���� ������ ������ ������ ����ǹǷ� �� ���� �����ϴ� ���� �ǹ̰� ����
	������ ������ �� �ʿ���� ��ũ ������ �����Ѵ�.
	�̷��� �Ӽ��� Transient Ű���带 �߰��� �ش� �Ӽ��� ����ȭ���� ���ܽ�Ű�� ���� ����.*/
	UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = true))
	float CurrentHP;
};
