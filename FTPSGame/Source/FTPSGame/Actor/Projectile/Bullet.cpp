#include "Actor/Projectile/Bullet.h"

#include "Utilities/Helper.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"


ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	Scene = Helper::CreateSceneComponent<USceneComponent>(this, "Scene");

	Collision = Helper::CreateSceneComponent<UCapsuleComponent>(this, "Collision", Scene);
	// Catch from Blueprint Example Class
	Collision->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	Collision->SetRelativeScale3D(FVector(1.75f, 0.125f, 1.125f));
	Collision->SetCollisionProfileName("OverlapAllDynamic");

	Mesh = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "Mesh", Collision);
	Mesh->SetStaticMesh(Helper::GetAssetFromConstructor<UStaticMesh>("/Script/Engine.StaticMesh'/Game/Weapons/2_Projectile/Sphere.Sphere'"));
	// Catch from Blueprint Example Class
	Mesh->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f));
	Mesh->SetRelativeScale3D(FVector(0.6f, 0.4f, 0.04f));
	Mesh->SetMaterial(0, Helper::GetAssetFromConstructor<UMaterial>("/Script/Engine.Material'/Game/Weapons/2_Projectile/M_Bullet.M_Bullet'"));
	Mesh->SetCollisionProfileName("NoCollision");

	ProjectileMovementComponent = Helper::CreateActorComponent<UProjectileMovementComponent>(this, "Projectile Comp");
	ProjectileMovementComponent->InitialSpeed = 10000;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABullet::HitSomething);

	SetLifeSpan(5);
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::HitSomething(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(15, 1, FColor::Blue, OtherActor->GetActorLabel());
	// Ignore
	if (OtherActor == GetOwner() || OtherActor->StaticClass() == this->StaticClass()) return;

	// Action


	// Destroy self
	Destroy();
}

