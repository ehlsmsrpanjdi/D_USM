#include "PreCompile.h"
#include "BackGround.h"
#include <EngineCore/DefaultSceneComponent.h>

BackGround* BackGroundImage::Back = nullptr;

BackGround::BackGround()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1, true);
	BackGroundImage::Back = this;
}

BackGround::~BackGround()
{
}

void BackGround::AddRenderSize(float4 _Size)
{
	Renderer->AddPosition(_Size);
	GetWorld()->GetMainCamera()->AddActorLocation(_Size);
}

void BackGround::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetSprite("Back_One.png");
	Renderer->SetOrder(-100);
	Renderer->SetScale(FVector(33 * 32, 18 * 32));
	Size = Renderer->GetLocalScale();
	
}

void BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
