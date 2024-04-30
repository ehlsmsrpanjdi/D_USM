#pragma once
#include <EngineCore/EngineCore.h>

class APlayGameMode;
// Ό³Έν :
class ContentsCore : public UserCore
{
public:
	// constrcuter destructer
	ContentsCore();
	~ContentsCore();

	// delete Function
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

	static APlayGameMode* GameMode;

protected:
	void Initialize() override;
	void ResourcesInit();
private:

};

