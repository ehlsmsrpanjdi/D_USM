#pragma once
#include <Enginecore/Actor.h>
#include <EngineCore/SpriteRenderer.h>


// Ό³Έν :
class JellyBackGround : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	JellyBackGround();
	~JellyBackGround();

	// delete Function
	JellyBackGround(const JellyBackGround& _Other) = delete;
	JellyBackGround(JellyBackGround&& _Other) noexcept = delete;
	JellyBackGround& operator=(const JellyBackGround& _Other) = delete;
	JellyBackGround& operator=(JellyBackGround&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
	USpriteRenderer* Renderer = nullptr;
};
