#include "PreCompile.h"
#include "Text.h"
#include <EngineCore/DefaultSceneComponent.h>

Text::Text()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(3.0f, true);
}

Text::~Text()
{
}

void Text::TextChange(std::string_view _TextName)
{
	Renderer->ChangeAnimation(_TextName);
}

void Text::BeginPlay()
{
	Super::BeginPlay();
	Renderer->CreateAnimation("U", "U.png");
	Renderer->CreateAnimation("N", "N.png");
	Renderer->CreateAnimation("D", "D.png");
	Renderer->CreateAnimation("O", "O.png");

	Renderer->CreateAnimation("R", "R.png");
	Renderer->CreateAnimation("E", "E.png");
	Renderer->CreateAnimation("S", "S.png");
	Renderer->CreateAnimation("T", "T.png");
	Renderer->CreateAnimation("A", "A.png");

	Renderer->CreateAnimation("B", "B.png");
	Renderer->CreateAnimation("I", "I.png");
	Renderer->CreateAnimation("Y", "Y.png");

	Renderer->CreateAnimation("C", "Alphabet.png");
	Renderer->CreateAnimation("G", "Alphabet.png");
	Renderer->CreateAnimation("L", "Alphabet.png");
	Renderer->CreateAnimation("Baba", "Baba_Right_1.png");
	Renderer->ChangeAnimation("R");
}

void Text::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
