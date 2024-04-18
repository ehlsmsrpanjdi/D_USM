#include "PreCompile.h"
#include "ContentsCore.h"
#include "PlayGameMode.h"
#include <EngineCore/EngineSprite.h>

ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Initialize()
{
	ResourcesInit();


	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->ChangeLevel("PlayLevel");


}

void ContentsCore::ResourcesInit()
{
	// 파일의 헤더
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Image");
	std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
	for (UEngineFile& File : Files)
	{
		// CuttingTest.png texture로도 한장이 로드가 됐고
		// 스프라이트로도 1장짜리로 로드가 된 상황이야.
		UEngineSprite::Load(File.GetFullPath());
	}
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Baba");
	Files = Dir.GetAllFile({ ".png" }, true);
	for (UEngineFile& File : Files)
	{
		// CuttingTest.png texture로도 한장이 로드가 됐고
		// 스프라이트로도 1장짜리로 로드가 된 상황이야.
		UEngineSprite::Load(File.GetFullPath());
	}
	//Dir.MoveParent();
	//Dir.Move("Wall");
	//Files = Dir.GetAllFile({ ".png" }, true);
	//for (UEngineFile& File : Files)
	//{
	//	// CuttingTest.png texture로도 한장이 로드가 됐고
	//	// 스프라이트로도 1장짜리로 로드가 된 상황이야.
	//	UEngineSprite::Load(File.GetFullPath());
	//}
	// 로드폴더는 이렇게 한다고 칩시다.
	std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
	for (size_t i = 0; i < Directorys.size(); i++)
	{
		std::string Name = Directorys[i].GetFolderName();
		UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
	}





	// 특정 스프라이트나 
	// 특정 텍스처를 찾아서
	// 만약 스프라이트가 존재하지 않는다면
	// 이걸 사용하는 순간 만들어내고 자른다.
	// 이미 이 이름을 가진 스프라이트가 존재한다.
	// 그러면 기존의 스프라이트 데이터는 날려버리고
	// 자른 스프라이트 데이터 변경한다.



	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Sound");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav" });
		for (UEngineFile& File : Files)
		{
			//File.Open(EIOOpenMode::Read, EIODataType::Binary);

			//char Arr[100];
			//File.Read(Arr, 100);

			UEngineSound::Load(File.GetFullPath());
		}
		// UEngineSound::SoundPlay("anipang_ingame_wav.wav");
	}

	UEngineSprite::CreateCutting("Baba_Down_1.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Down_2.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Down_3.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Down_4.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Right_1.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Right_2.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Right_3.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Right_4.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Left_1.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Left_2.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Left_3.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Left_4.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Up_1.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Up_2.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Up_3.png", 3, 1);
	UEngineSprite::CreateCutting("Baba_Up_4.png", 3, 1);

	UEngineSprite::CreateCutting("Wall.png", 18, 3);
	UEngineSprite::CreateCutting("Is.png", 2, 3);

	UEngineSprite::CreateCutting("Pull.png", 3, 3);
	UEngineSprite::CreateCutting("Push.png", 3, 3);
	UEngineSprite::CreateCutting("Move.png", 3, 3);
	UEngineSprite::CreateCutting("Stop.png", 3, 3);
	UEngineSprite::CreateCutting("Baba.png", 3, 1);
	
}

