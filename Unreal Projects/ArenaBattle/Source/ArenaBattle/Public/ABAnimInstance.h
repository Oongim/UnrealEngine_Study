// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "Animation/AnimInstance.h"
#include "ABAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
/**
 * 
 */
UCLASS()
class ARENABATTLE_API UABAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UABAnimInstance();
	//�ִ� �ν��Ͻ� Ŭ�������� �����ϴ� ƽ���� ȣ��Ǵ� �����Լ�
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);

public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	void SetDeadAnim() { IsDead = true; }

private:
	/*AnimNotify_��Ƽ���̸� ���� ��Ƽ���̰� ȣ��Ǹ� ����Լ��� ȣ��
	�̶� ã�� �� �ֵ��� UFUNCTION ��ũ�ΰ� �����ž���, ���̳��� ��������Ʈ�� �����ϴ� �Լ��� ���̴°Ͱ� ���� ����*/
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	FName GetAttackMontageSectionName(int32 Section);

private:
	/*�ִϸ��̼� �������Ʈ�� �ִ� �׷������� ��� - EditAnywhere
	��� ����Ʈ�� �����ϱ� ���� BlueprintReadOnly�߰�*/
	/*ALlowPrivateAccess��� META Ű���带 �߰��ؼ�
	�����Ϳ��� �̸� �����հ� ���ÿ� ���� �����͸� ������ �� �ְ� �Ǿ� ĸ��ȭ�� ����������-> ��������
	�׳� private�� �����Ϳ��� ������ ���� �����ϱ� ���� ���� ������ �����ؾ� �ϱ� ������ ������ �߻�*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pawn, Meta=(AllowPrivateAccess=true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDead;

};
