#pragma once
#include <EngineCore/EngineEditorGUI.h>
#include <EngineCore/EngineDebugMsgWindow.h>

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
	
	std::string TestNAme = "";

	std::map<TilePoint, std::vector<int>> TileData;

	void EditorSwitch(int _X, int _Y, int _Index);

private:

};
