// Fill out your copyright notice in the Description page of Project Settings.


#include "ABAnimInstance.h"

UABAnimInstance::UABAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsInAir = false;
	IsDead = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(TEXT(
		"/Game/Book/Animations/SK_Mannequin_Skeleton_Montage.SK_Mannequin_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded()) AttackMontage = ATTACK_MONTAGE.Object;
}

void UABAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	//애님 인스턴스에서 폰의 정보를 얻어온후 업데이트
	Super::NativeUpdateAnimation(DeltaSeconds);

	/*게임 엔지은 틱마다 입력시스템->게임 로직->애니메이션 시스템 순으로 로직 실행
	만일 게임 로직단계에서 폰이 제거 명령을 내리면 애니메이션 로직에서는 더 이상 유효하지 않은 폰 객체를 참조할 것이다
	그래서 폰에 접근할 때 유효한지 점검하기 위해 TryGetPawnOwner를 사용*/
	auto Pawn = TryGetPawnOwner(); 
	if (!::IsValid(Pawn)) return;

	if (!IsDead) { 
		CurrentPawnSpeed = Pawn->GetVelocity().Size(); 

		/*
		IsFalling(): 현재 공중에 떠있는지
		IsSwimming(): 수영중인지
		IsCrouching(): 앉아있는지
		IsMoveOnGround(): 땅 위에서 이동중인지
		*/
		auto Character = Cast<ACharacter>(Pawn);
		if (Character) IsInAir = Character->GetMovementComponent()->IsFalling();
	}
}

void UABAnimInstance::PlayAttackMontage()
{
	ABCHECK(!IsDead);
	/*
	if (!Montage_IsPlaying(AttackMontage)) Montage_Play(AttackMontage, 1.0f);
	델리게이트에 의해 공격의 시작과 종료가 감지되므로 사용하지 않아도 됨
	*/
	Montage_Play(AttackMontage, 1.0f);
}

void UABAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	ABCHECK(!IsDead);
	ABCHECK(Montage_IsPlaying(AttackMontage));
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void UABAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast();
}
void UABAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UABAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	ABCHECK(FMath::IsWithinInclusive<int32>(Section, 1, 4), NAME_None);
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}