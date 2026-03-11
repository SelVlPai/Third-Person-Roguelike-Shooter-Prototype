// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsCharacter.h"
#include "InterfacePlayerController.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UStatsCharacter::UStatsCharacter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsCharacter::BeginPlay()
{
	Super::BeginPlay();
	ReferencesMainChar = Cast<ACharacter>(GetOwner());
	BackHealth = MaxHealth;
	FrontHealth = MaxHealth;
	//for (uint8 i = 0; i < MaxPlateArmor; i++)
		//Armor.Add(i + 1, 0);
	/*GetWorld()->GetTimerManager().SetTimerForNextTick(FTimerDelegate::CreateLambda([this]()
		{
			Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetHPInHUD(FrontHealth, BackHealth, MaxHealth);
		})
	);
	*/
	Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetHPInHUD(FrontHealth, BackHealth, MaxHealth);
	Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetArmorInHUD(Armor, MaxPlateArmor, MaxCurrentArmor);
	
	// ...
	
}


void UStatsCharacter::ReduceHealth()
{
	BackHealth += AddToHPBack;
	
	
	if (BackHealth <= FrontHealth)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%f"), AddToHPBack));
		GetWorld()->GetTimerManager().ClearTimer(TSetBack);
		BackHealth = FrontHealth;
		Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetHPInHUD(FrontHealth, BackHealth, MaxHealth);
		//Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetHPInHUD(FrontHealth, BackHealth, MaxHealth);
	}
	else
	{
		Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetHPInHUD(FrontHealth, BackHealth, MaxHealth);
	}
}

void UStatsCharacter::IncreaseHealth()
{
	FrontHealth += AddToHPBack;

	if (BackHealth <= FrontHealth)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%f"), AddToHPBack));
		GetWorld()->GetTimerManager().ClearTimer(TSetBack);
		FrontHealth = BackHealth;
		Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetHPInHUD(FrontHealth, BackHealth, MaxHealth);
		//Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetHPInHUD(FrontHealth, BackHealth, MaxHealth);
	}
	else
	{
		Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetHPInHUD(FrontHealth, BackHealth, MaxHealth);
	}
}


void UStatsCharacter::InflictDamageToHeath(float Damage)
{
	float SetNewHealth = GetFrontHealth() - Damage;
	if (SetNewHealth <= 0) 
	{
		FrontHealth = 0;
		AddToHPBack = (FrontHealth - BackHealth) / (0.5f / 0.01f);
		GetWorld()->GetTimerManager().SetTimer(TSetBack, this, &ThisClass::ReduceHealth, 0.01, true);
		// Death
		
	}
	else if(SetNewHealth <= MaxHealth)
	{
		if(FrontHealth > SetNewHealth)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, TEXT("Reduce"));
		FrontHealth = SetNewHealth;      // тривалість | тік
		AddToHPBack = (FrontHealth - BackHealth) / (0.5f / 0.01f);
		GetWorld()->GetTimerManager().SetTimer(TSetBack, this, &ThisClass::ReduceHealth, 0.01, true);
		//BackHealth = FrontHealth;

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%f"), FrontHealth));
			BackHealth = SetNewHealth;
			AddToHPBack = (BackHealth - FrontHealth) / (0.5f / 0.01f);
			GetWorld()->GetTimerManager().SetTimer(TSetBack, this, &ThisClass::IncreaseHealth, 0.01, true);
		}
	}
	else if(SetNewHealth > MaxHealth)
	{
		BackHealth = MaxHealth;
		AddToHPBack = (BackHealth - FrontHealth) / (0.5f / 0.01f);
		GetWorld()->GetTimerManager().SetTimer(TSetBack, this, &ThisClass::IncreaseHealth, 0.01, true);
	}
	
	//GetWorld()->GetTimerManager().SetTimer(TSetBack, this, &ThisClass::ReduceHealth, 0.01, true);
	
}



uint8 UStatsCharacter::SubstractPlate(float TakedDamage)
{
	float Calculate = TakedDamage * 100 / MaxHealth;
	TArray<uint8> Keys;
	ChoiceCurrentDamage.GetKeys(Keys);
	for (uint8 i = 0; i < Keys.Num(); i++)
	{
		uint8 CurrentPlate = ChoiceCurrentDamage.FindRef(Keys[i]);
		if (i != 0)
		{
			if (Keys[i - 1] < Calculate && Keys[i] > Calculate)
				return CurrentPlate;
		}
		else
		{
			if (Keys[i] > Calculate)
				return CurrentPlate;
		}
	}
	return ChoiceCurrentDamage.FindRef(Keys[Keys.Num() - 1]) + 2;
}

void UStatsCharacter::InflictDamage(float DamageCurrent)
{
	uint8 SubstractArmor = SubstractPlate(DamageCurrent);
	uint8 DefaultCurrentSubstract = SubstractArmor;
	bool CauseDamage = true;
	TArray<uint8> Keys;
	Armor.GetKeys(Keys);
	//Algo::Reverse(Keys);
	for (uint8 i = Keys.Num(); i >= 1; i--)
	{
		int8 FoundValue = Armor.FindRef(i);
		if (FoundValue != 0) 
		{
				FoundValue -= SubstractArmor;
				//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("%i"), FoundValue));
				if (FoundValue < 0) 
				{
					SubstractArmor = FoundValue * -1;
					FoundValue = 0;
					
					Armor.Add(i, FoundValue);
					if (i == 1 && SubstractArmor > 0) 
					{
						CauseDamage = true;
						//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("%i"), SubstractArmor));
					}
					
				}
				else
				{
					CauseDamage = false;
					SubstractArmor = 0;
					Armor.Add(i, FoundValue);
					break;
				}
		}
	}
	Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetArmorInHUD(Armor, MaxPlateArmor, MaxCurrentArmor);
	if (CauseDamage) 
	{
		//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("%i"), DefaultCurrentSubstract));
		float Damage = static_cast<float>(SubstractArmor) * DamageCurrent / static_cast<float>(DefaultCurrentSubstract);
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("%f"), Damage));
		InflictDamageToHeath(Damage);
	}
}

void UStatsCharacter::AddNewPlate()
{
	MaxPlateArmor++;
	
	//TMap SaveArmor = Armor;
	TArray<uint8> Keys;
	Armor.GetKeys(Keys);
	Armor.Add(Keys[Keys.Num() - 1], 0);
	//Armor.Reset();
	/*Armor.Add(Keys[0] + 1, 0);
	for (const TPair<uint8, uint8>& element : SaveArmor)
	{
		Armor.Add(element);
	}
	*/
	Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetArmorInHUD(Armor, MaxPlateArmor, MaxCurrentArmor);

}

void UStatsCharacter::RecoveryPlate(uint8 CurrentArmor)
{
	//TArray<uint8> Keys;
	//Armor.GetKeys(Keys);
	//Algo::Reverse(Keys);
	for (const TPair<uint8, uint8> element : Armor)
	{
		
		//uint8 FoundValue = Armor.FindRef(i);
		uint8 PartsArmor = element.Value;
		if (PartsArmor < MaxCurrentArmor)
		{
			
			uint8 AddArmor = PartsArmor + CurrentArmor;
			if (AddArmor > MaxCurrentArmor) 
			{
				GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%i"), AddArmor));
				CurrentArmor = AddArmor % MaxCurrentArmor;
				AddArmor = MaxCurrentArmor;
				Armor.Add(element.Key, AddArmor);
				continue;
			}
			else
			{
				
				Armor.Add(element.Key, AddArmor);
				break;
			};
			
		};
	}
	//GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, FString::Printf(TEXT("%i"), Armor.FindRef(1)));
	Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetArmorInHUD(Armor, MaxPlateArmor, MaxCurrentArmor);

}

void UStatsCharacter::BuffRecoveryHealth(float HP)
{
	InflictDamageToHeath(-HP);
}

void UStatsCharacter::BuffRecoveryArmor(float PartsOfArmor)
{
	uint8 AddArmor = static_cast<uint8>(PartsOfArmor);
	for (const TPair<uint8, uint8> elem : Armor) 
	{
		uint8 PartPlate = elem.Value;
		if (PartPlate != MaxCurrentArmor) 
		{
			if (MaxCurrentArmor - PartPlate < AddArmor) 
			{
				AddArmor -= MaxCurrentArmor - PartPlate;
				Armor.Add(elem.Key, MaxCurrentArmor);
			}
			else
			{
				PartPlate += AddArmor;
				Armor.Add(elem.Key, PartPlate);
				break;
			}
		}
	}
	Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetArmorInHUD(Armor, MaxPlateArmor, MaxCurrentArmor);
}

void UStatsCharacter::SetAttributesPlayer(const FStatsStruct& Attributes)
{
	 BackHealth = Attributes.BackHealth;
	 FrontHealth = Attributes.FrontHealth;
	 MaxHealth = Attributes.MaxHealth;
	 Armor = Attributes.ArmorNow;
	 MaxCurrentArmor = Attributes.MaxCurrentArmor;
	 MaxPlateArmor = Attributes.MaxPlateArmor;
	 Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetHPInHUD(FrontHealth, BackHealth, MaxHealth);
	 Cast<IInterfacePlayerController>(ReferencesMainChar->GetController())->SetArmorInHUD(Armor, MaxPlateArmor, MaxCurrentArmor);

}

// Called every frame
void UStatsCharacter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

