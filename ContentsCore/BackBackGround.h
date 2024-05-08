#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>


// Ό³Έν :
class BackBackGround : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	BackBackGround();
	~BackBackGround();

	// delete Function
	BackBackGround(const BackBackGround& _Other) = delete;
	BackBackGround(BackBackGround&& _Other) noexcept = delete;
	BackBackGround& operator=(const BackBackGround& _Other) = delete;
	BackBackGround& operator=(BackBackGround&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;



private:
	USpriteRenderer* Renderer = nullptr;
};
