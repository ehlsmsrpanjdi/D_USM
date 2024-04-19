#pragma once
#include <EngineCore/EngineEditorGUI.h>
#include <EngineCore/EngineDebugMsgWindow.h>

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

private:

};
