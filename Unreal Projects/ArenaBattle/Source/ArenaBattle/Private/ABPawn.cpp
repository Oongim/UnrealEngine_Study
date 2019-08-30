// Fill out your copyright notice in the Description page of Project Settings.

//이런 역할의 폰을 Character라는 클래스에 상속시켜 놓았으니 거기서 만드는게 나을듯하다

#include "ABPawn.h"

// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);
	//삼인칭 시점을 구현할 때 카메라 컴포넌트를 스프링암 컴포넌트의 자식으로 설정하고 
	//트랜스폼 정보를 초기화하면 카메라는 자동으로 스프링암의 끝에 걸림

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	//캐릭터의 절반 높이와 캐릭터의 몸둘레
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	/*캐릭터를 제작할 때 사용한 소프트웨어의 3차원 좌표계와 언리얼 엔진의 3차원 좌표계가 서로 다르기 때문에
	z축으로 -90도 회전시켜 맞춰준다
	언리얼 엔진에서 액터의 기준 위치는 정중앙 위치이지만 캐릭터 애셋은 주로 발바닥에 기준 위치를 잡기 때문에
	z축으로 절반 높이만큼 내려줘야 한다.*/
	SpringArm->TargetArmLength = 400.0f;
	//카메라 지지대의 길이 4미터
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));
	//컴포넌트의 Y축 회전을 -15도로 설정해 캐릭터 어깨 너머로 배경이 보이도록 삼인칭 시점을 설정

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(
		TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())Mesh->SetSkeletalMesh(SK_CARDBOARD.Object);

	/*애니메이션 블루프린트는 애님 그래프 로직에 따라 동작하는 캐릭터 애니메이션 시스템을 구동시킨다
	이러한 애니메이션 시스템은 C++ 프로그래밍의 애님 인스터스라는 클래스로 관리된다.*/
	Mesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(
		TEXT("/Game/Book/Animations/WarriorAnimBluePrint.WarriorAnimBluePrint_C"));
	if (WARRIOR_ANIM.Succeeded())Mesh->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
{
	Super::BeginPlay();

	//Mesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
	////게임의 실행 중에 애셋을 로드하는 명령어는 LoadObject<타입>
	//UAnimationAsset* AnimAsset = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Book/Animations/WarriorRun.WarriorRun"));
	//if (AnimAsset != nullptr) Mesh->PlayAnimation(AnimAsset, true);
	//이방법을 안쓰고 생성자에서 블루프린트를 통해 설정하기로 함
}

// Called every frame
void AABPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AABPawn::PossessedBy(AController* NewController)
{
	ABLOG_S(Warning);
	Super::PossessedBy(NewController);
}
// Called to bind functionality to input, 입력 설정을 처리하기 위한 오브젝트를 설정하는 함수
void AABPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//InputComponent를 사용해 폰의 멤버 함수와 입력 설정을 연결(Binding)시키면, 입력 신호는 자동으로 폰의 멤버 함수의 인자로 전달 됨
	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AABPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AABPawn::LeftRight);
	/*BindAxis와 BindAction이라는 두가지 함수 제공
	폰이 레버 신호를 받을 수 있도록 BindAxis함수를 사용해 입력 설정의 이름과 
	이와 연동할 언리얼 오브젝트 인스턴스의 함수 포인터를 지정*/
}

void AABPawn::UpDown(float NewAxisValue)
{
	/*이 함수는 폰 무브컴포넌트에 선언돼 있으며 -1부터 1사이의 입력 값을 전달해서 폰을 움직이게 하는 명령
	이동할 방향을 WorldDirection에 지정해야 하므로 액터의 전진 방향의 벡터 데이터는
	GetActorForwardVector 함수를 사용해 가져오고 이 값을 WorldDirection 인자에 넘겨준다.*/
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
	ABLOG(Warning, TEXT("%f"), NewAxisValue);
}

void AABPawn::LeftRight(float NewAxisValue)
{
	AddMovementInput(GetActorRightVector(), NewAxisValue);
	ABLOG(Warning, TEXT("%f"), NewAxisValue);
}
