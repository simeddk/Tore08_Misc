#include "CDebuggerCategory.h"
#include "GameFramework/PlayerController.h"
#include "CanvasItem.h"

CDebuggerCategory::CDebuggerCategory()
{
    UE_LOG(LogTemp, Error, TEXT(__FUNCTION__));

    bShowOnlyWithDebugActor = false;
}

CDebuggerCategory::~CDebuggerCategory()
{
    UE_LOG(LogTemp, Error, TEXT(__FUNCTION__));
}

TSharedRef<FGameplayDebuggerCategory> CDebuggerCategory::MakeInstance()
{
    return MakeShareable(new CDebuggerCategory());
}

void CDebuggerCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
    FGameplayDebuggerCategory::CollectData(OwnerPC, DebugActor);

    //Player
    APawn* PlayerPawn = OwnerPC->GetPawn();
    {
        PlayerData.Name = PlayerPawn->GetName();
        PlayerData.Loation = PlayerPawn->GetActorLocation();
        PlayerData.Forward = PlayerPawn->GetActorForwardVector();
    }

    //ForwardActor
    {
        FVector Start = PlayerPawn->GetActorLocation();
        FVector End = Start + PlayerPawn->GetActorForwardVector() * 1e+4f;

        FCollisionQueryParams QueryParam;
        QueryParam.AddIgnoredActor(PlayerPawn);

        FHitResult Hit;
        PlayerPawn->GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, QueryParam);

        if (Hit.bBlockingHit)
        {
            ForwardActorData.Name = Hit.GetActor()->GetName();
            ForwardActorData.Loation = Hit.GetActor()->GetActorLocation();
            ForwardActorData.Forward = Hit.GetActor()->GetActorForwardVector();
        }
        else
        {
            ForwardActorData.Name = "No exist forward actor";
            ForwardActorData.Loation = FVector::ZeroVector;
            ForwardActorData.Forward = FVector::ZeroVector;
        }
    }

    //DebugActor
    if (DebugActor)
    {
        DebugActorData.Name = DebugActor->GetName();
        DebugActorData.Loation = DebugActor->GetActorLocation();
        DebugActorData.Forward = DebugActor->GetActorForwardVector();
    }
    else
    {
        DebugActorData.Name = "No exist debug actor";
        DebugActorData.Loation = FVector::ZeroVector;
        DebugActorData.Forward = FVector::ZeroVector;
    }
}

void CDebuggerCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
    FGameplayDebuggerCategory::DrawData(OwnerPC, CanvasContext);

    FCanvasTileItem Item(FVector2D(10, 10), FVector2D(300, 220), FLinearColor(1, 0, 0, 0.3f));
    Item.BlendMode = SE_BLEND_AlphaBlend;
    CanvasContext.DrawItem(Item, CanvasContext.CursorX, CanvasContext.CursorY);

    CanvasContext.Printf(FColor::Green, TEXT("--Player--"));
    CanvasContext.Printf(FColor::Yellow, TEXT(" > Name : %s"), *PlayerData.Name);
    CanvasContext.Printf(FColor::Yellow, TEXT(" > Location : %s"), *PlayerData.Loation.ToString());
    CanvasContext.Printf(FColor::Yellow, TEXT(" > Forward : %s"), *PlayerData.Forward.ToString());
    CanvasContext.Printf(FColor::Green, TEXT(""));

    CanvasContext.Printf(FColor::Green, TEXT("--Forward Actor--"));
    CanvasContext.Printf(FColor::Yellow, TEXT(" > Name : %s"), *ForwardActorData.Name);
    CanvasContext.Printf(FColor::Yellow, TEXT(" > Location : %s"), *ForwardActorData.Loation.ToString());
    CanvasContext.Printf(FColor::Yellow, TEXT(" > Forward : %s"), *ForwardActorData.Forward.ToString());
    CanvasContext.Printf(FColor::Green, TEXT(""));

    CanvasContext.Printf(FColor::Green, TEXT("--Debug Actor--"));
    CanvasContext.Printf(FColor::Yellow, TEXT(" > Name : %s"), *DebugActorData.Name);
    CanvasContext.Printf(FColor::Yellow, TEXT(" > Location : %s"), *DebugActorData.Loation.ToString());
    CanvasContext.Printf(FColor::Yellow, TEXT(" > Forward : %s"), *DebugActorData.Forward.ToString());
    CanvasContext.Printf(FColor::Green, TEXT(""));
}
