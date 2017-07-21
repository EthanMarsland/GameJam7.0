// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "FroggoCharacter.generated.h"

UCLASS(config=Game)
class AFroggoCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	AFroggoCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	// add pull force to player
	UFUNCTION(BlueprintCallable)
	void addPullForce(int32 force);

	UFUNCTION(BlueprintCallable)
		void pullTimerStart();

	UFUNCTION(BlueprintCallable)
		void pullTimerEnd();

	UFUNCTION(BlueprintCallable)
		void AttackTimerStart();

	UFUNCTION(BlueprintCallable)
		void AttackTimerEnd();

	UFUNCTION(BlueprintCallable)
		bool GetPlayerAlive();

	UFUNCTION(BlueprintCallable)
		FTimerHandle GetPullTimerHandle();

	UFUNCTION()
		void PullTimer();

	UFUNCTION()
		void AttackTimer();

protected:

	// pull timer handle
	FTimerHandle m_PullTimerHandle;

	// pull timer handle
	FTimerHandle m_AttackTimerHandle;

	// how long the player takes to charge attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
		float m_AttackChargeTime;


	// how much the player is being pulled
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
	float m_pullForce;

	// how long the player has to break free
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float m_MaxPullTime;

	// the amount of pull needed to kill player
	UPROPERTY(EditAnywhere)
	int32 m_PullLossAmount;

	// how much to decrease time each time the player breaks free
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float m_TimeLoss;

	bool m_playerAlive;

	// if the player can move 	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool m_CanMove;

	// if the player is attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_Attacking;

	// if the player is charged
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool m_AttackCharged;
};
