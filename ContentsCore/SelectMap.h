#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class SelectMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	SelectMap();
	~SelectMap();

	// delete Function
	SelectMap(const SelectMap& _Other) = delete;
	SelectMap(SelectMap&& _Other) noexcept = delete;
	SelectMap& operator=(const SelectMap& _Other) = delete;
	SelectMap& operator=(SelectMap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* Renderer;
	float4 Color;
};
