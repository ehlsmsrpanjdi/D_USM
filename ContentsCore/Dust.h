#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>


// Ό³Έν :
class Dust : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	Dust();
	~Dust();

	// delete Function
	Dust(const Dust& _Other) = delete;
	Dust(Dust&& _Other) noexcept = delete;
	Dust& operator=(const Dust& _Other) = delete;
	Dust& operator=(Dust&& _Other) noexcept = delete;

	void SetReleaseLocation(char _Input);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetInputBaseLocation(FVector _Scale);

private:
	USpriteRenderer* Renderer = nullptr;
	FVector Scale = FVector::Zero;
	float ReleaseTime = 0.f;
	float TotalTime = 0.f;
	char ReleaseLocation = '0';
};
