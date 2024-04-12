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
	{
		// ������ ���
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Image");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			// CuttingTest.png texture�ε� ������ �ε尡 �ư�
			// ��������Ʈ�ε� 1��¥���� �ε尡 �� ��Ȳ�̾�.
			UEngineSprite::Load(File.GetFullPath());
		}
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Baba");
		Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			// CuttingTest.png texture�ε� ������ �ε尡 �ư�
			// ��������Ʈ�ε� 1��¥���� �ε尡 �� ��Ȳ�̾�.
			UEngineSprite::Load(File.GetFullPath());
		}

		// �ε������� �̷��� �Ѵٰ� Ĩ�ô�.
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
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

		// Ư�� ��������Ʈ�� 
		// Ư�� �ؽ�ó�� ã�Ƽ�
		// ���� ��������Ʈ�� �������� �ʴ´ٸ�
		// �̰� ����ϴ� ���� ������ �ڸ���.
		// �̹� �� �̸��� ���� ��������Ʈ�� �����Ѵ�.
		// �׷��� ������ ��������Ʈ �����ʹ� ����������
		// �ڸ� ��������Ʈ ������ �����Ѵ�.
	}


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

	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->ChangeLevel("PlayLevel");


}

