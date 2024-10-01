#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TP_TopDownCharacter.generated.h"

class UMaterialInstanceDynamic;

UCLASS(Blueprintable)
class ATP_TopDownCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATP_TopDownCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	void OnSprint();
	void OffSprint();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UPostProcessComponent* PostProcessComp;

	UPROPERTY(VisibleAnywhere, Category = "Smear")
	UMaterialInterface* OriginMaterial;

	UPROPERTY(EditDefaultsOnly, Category = "Smear")
	UMaterialInterface* SmearMaterial;

	UPROPERTY(VisibleAnywhere, Category = "Smear")
	UMaterialInstanceDynamic* SmearMaterialDynamic;

	UPROPERTY(EditDefaultsOnly, Category = "Smear")
	float SmearWeight;

	//UPROPERTY(EditDefaultsOnly, Category = "SphereMask")
	//UMaterialInterface* SphereMaskMaterial;
};

