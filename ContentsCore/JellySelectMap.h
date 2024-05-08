#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class USpriteRenderer;
class JellySelectMap : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	JellySelectMap();
	~JellySelectMap();

	// delete Function
	JellySelectMap(const JellySelectMap& _Other) = delete;
	JellySelectMap(JellySelectMap&& _Other) noexcept = delete;
	JellySelectMap& operator=(const JellySelectMap& _Other) = delete;
	JellySelectMap& operator=(JellySelectMap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	USpriteRenderer* Renderer;
	float4 Color;
};
