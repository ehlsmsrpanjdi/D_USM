#pragma once
#include <EngineCore/EngineEditorGUI.h>
#include <EngineCore/EngineDebugMsgWindow.h>
#include <EngineBase/EngineDirectory.h>

class APlayGameMode;
// Ό³Έν :
class BabaEditor : public UEngineDebugMsgWindow
{
public:
	// constructor destructor
	BabaEditor();
	~BabaEditor();

	// delete Function
	BabaEditor(const BabaEditor& _Other) = delete;
	BabaEditor(BabaEditor&& _Other) noexcept = delete;
	BabaEditor& operator=(const BabaEditor& _Other) = delete;
	BabaEditor& operator=(BabaEditor&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Tick(ULevel* Level, float _Delta) override;
	void OnGui(ULevel* Level, float _Delta) override;

	APlayGameMode* GameMode = nullptr;

	int Location[2] = { 0, };
	
	char FileName[255] = "";

	UEngineDirectory Dir;
	std::vector<int> TileData;
	std::vector<class ABabaBase*> Tiles;
	std::string str = "";

	bool FileState = false;
	float _DeltaTime = 0.f;

	void EditorSwitch(int _X, int _Y, int _Index);
private:

};
