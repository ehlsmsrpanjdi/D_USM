#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>


// Ό³Έν :
class BackGroundCirCle : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	BackGroundCirCle();
	~BackGroundCirCle();

	// delete Function
	BackGroundCirCle(const BackGroundCirCle& _Other) = delete;
	BackGroundCirCle(BackGroundCirCle&& _Other) noexcept = delete;
	BackGroundCirCle& operator=(const BackGroundCirCle& _Other) = delete;
	BackGroundCirCle& operator=(BackGroundCirCle&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;



private:
	USpriteRenderer* Renderer = nullptr;
};
