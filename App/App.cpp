#include <Windows.h>
#include <string_view>

#include <EngineCore/EngineCore.h>
#include <ContentsCore/ContentsCore.h>
// EnginePlatform�� �����ϴ� enginewindow����� �翬�� �̿��ϰ� ���� ���̴�.

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")
#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "ContentsCore.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UEngineCore::Start<ContentsCore>(hInstance);
}