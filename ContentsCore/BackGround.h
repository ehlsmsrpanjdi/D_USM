#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>


// Ό³Έν :
class BackGround : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;

	void AddRenderSize(float4 _Size);
	float4 Size = {};
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;



private:
	USpriteRenderer* Renderer = nullptr;
};

class BackGroundImage {
public:
	static BackGround* Back;
};

