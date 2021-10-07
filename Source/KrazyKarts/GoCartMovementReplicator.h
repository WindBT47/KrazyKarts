// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoCartMovementComponent.h"
#include "GoCartMovementReplicator.generated.h"

USTRUCT()
struct FGoCartState
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY()
		FTransform Tranform;

	UPROPERTY()
		FVector Velocity;

	UPROPERTY()
		FGoCartMove LastMove;
};

struct FHermiteCubicSpline
{
	FVector StartLocation, StartDerivative, TargetLocation, TargetDerivative;

	FVector InterpolateLocation(float LerpRatio) const
	{
		return FMath::CubicInterp(StartLocation, StartDerivative, TargetLocation, TargetDerivative, LerpRatio);
	}
	FVector InterpolateDerivative(float LerpRatio) const
	{
		return FMath::CubicInterpDerivative(StartLocation, StartDerivative, TargetLocation, TargetDerivative, LerpRatio);
	}
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UGoCartMovementReplicator : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGoCartMovementReplicator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void ClearAcknowledgeMoves(FGoCartMove LastMove);

	void UpdateServerState(const FGoCartMove& Move);
	
	void ClientTick(float DeltaTime);

	FHermiteCubicSpline CreateSpline();
	void InterpolateLocation(const FHermiteCubicSpline& Spline, float LerpRatio);
	void InterpolateVelocity(const FHermiteCubicSpline& Spline, float LerpRatio);
	void InterpolateRotation(float LerpRatio);
	float VelocityToDerivative();

	UFUNCTION(Server, Reliable, WithValidation)
		void Server_SendMove(FGoCartMove Move);

	UPROPERTY(ReplicatedUsing = OnRep_ServerState)
		FGoCartState ServerState;

	UFUNCTION()
		void OnRep_ServerState();

	void AutonomousProxy_OnRep_ServerState();
	void SimulatedProxy_OnRep_ServerState();

	TArray<FGoCartMove> UnacknowledgedMoves;

	float ClientTimeSinceUpdate;
	float ClientTimeBetweenLastUpdates;
	FTransform ClientStartTransform;
	FVector ClientStartVelocity;

	float ClientSimulatedTime;

	UPROPERTY()
		UGoCartMovementComponent* MovementComponent;
	UPROPERTY()
		USceneComponent* MeshOffsetRoot;
	UFUNCTION(BlueprintCallable)
		void SetMeshOffsetRoot(USceneComponent* Root) { MeshOffsetRoot = Root; }
};
