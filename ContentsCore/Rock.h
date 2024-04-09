#pragma once

#include "BabaBase.h"
// Ό³Έν :
class AActor;
class ARock : public ABabaBase
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ARock();
	~ARock();

	// delete Function
	ARock(const ARock& _Other) = delete;
	ARock(ARock&& _Other) noexcept = delete;
	ARock& operator=(const ARock& _Other) = delete;
	ARock& operator=(ARock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

};
