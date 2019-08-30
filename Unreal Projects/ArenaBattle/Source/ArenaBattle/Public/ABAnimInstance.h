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
	//애님 인스턴스 클래스에서 제공하는 틱마다 호출되는 가상함수
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);

public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	void SetDeadAnim() { IsDead = true; }

private:
	/*AnimNotify_노티파이명 으로 노티파이가 호출되면 멤버함수를 호출
	이때 찾을 수 있도록 UFUNCTION 매크로가 지정돼야함, 다이내믹 델리게이트와 연동하는 함수에 붙이는것과 같은 이유*/
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	FName GetAttackMontageSectionName(int32 Section);

private:
	/*애니메이션 블루프린트의 애님 그래프에서 사용 - EditAnywhere
	블루 프린트에 접근하기 위해 BlueprintReadOnly추가*/
	/*ALlowPrivateAccess라는 META 키워드를 추가해서
	에디터에서 이를 편집합과 동시에 변수 데이터를 은닉할 수 있게 되어 캡슐화가 가능해진다-> 정보은닉
	그냥 private는 에디터에서 변수의 값을 변경하기 위해 접근 권한을 개방해야 하기 때문에 에러가 발생*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Pawn, Meta=(AllowPrivateAccess=true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDead;

};
