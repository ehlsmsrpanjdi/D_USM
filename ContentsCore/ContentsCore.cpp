#include "PreCompile.h"
#include "ContentsCore.h"
#include "PlayGameMode.h"
#include <EngineCore/EngineSprite.h>
#include "BabaEditor.h"
#include <EngineCore/EngineEditorGUI.h>
#include<EngineCore/EnginePixelShader.h>
#include "SelectGameMode.h"
#include "JellyGameMode.h"
#include "TitleGameMode.h"

APlayGameMode* ContentsCore::GameMode = nullptr;
BabaEditor* ContentsCore::Editor = nullptr;
ContentsCore::ContentsCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::Initialize()
{
	ResourcesInit();

	Editor = UEngineEditorGUI::CreateEditorWindow<BabaEditor>("BabaEditor").get();


	GEngine->CreateLevel<JellyGameMode>("Jelly");
	GEngine->CreateLevel<SelectGameMode>("SelectGameLevel");
	GEngine->CreateLevel<TitleGameMode>("Title");
	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->ChangeLevel("Title");

}

void ContentsCore::ResourcesInit()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Baba");
	std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);

	for (UEngineFile& File : Files)
	{
		UEngineSprite::Load(File.GetFullPath());
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

	UEngineSprite::CreateCutting("ICE.png", 18, 3);
	UEngineSprite::CreateCutting("Wall.png", 18, 3);
	UEngineSprite::CreateCutting("Grass.png", 18, 3);
	UEngineSprite::CreateCutting("Lava.png", 18, 3);
	UEngineSprite::CreateCutting("Water.png", 18, 3);
	UEngineSprite::CreateCutting("Line.png", 18, 3);

	UEngineSprite::CreateCutting("Is.png", 2, 3);

	UEngineSprite::CreateCutting("Pull.png", 3, 3);
	UEngineSprite::CreateCutting("Push.png", 3, 3);
	UEngineSprite::CreateCutting("Move.png", 3, 3);
	UEngineSprite::CreateCutting("Stop.png", 3, 3);
	UEngineSprite::CreateCutting("Baba.png", 3, 1);

	UEngineSprite::CreateCutting("DEFEAT.png", 3, 3);
	UEngineSprite::CreateCutting("Flag.png", 3, 3);
	UEngineSprite::CreateCutting("hot.png", 3, 3);
	UEngineSprite::CreateCutting("Move.png", 3, 3);

	UEngineSprite::CreateCutting("Rock.png", 2, 3);
	UEngineSprite::CreateCutting("Sink.png", 3, 3);
	UEngineSprite::CreateCutting("Skull.png", 2, 3);
	UEngineSprite::CreateCutting("Stop.png", 3, 3);
	UEngineSprite::CreateCutting("Win.png", 3, 3);
	UEngineSprite::CreateCutting("You.png", 3, 3);
	UEngineSprite::CreateCutting("Melt.png", 3, 3);
	
	UEngineSprite::CreateCutting("SkullObj.png", 4, 3);
	UEngineSprite::CreateCutting("RockObj.png", 1, 3);
	UEngineSprite::CreateCutting("FlagObj.png", 2, 3);
	UEngineSprite::CreateCutting("And.png", 3, 3);
	UEngineSprite::CreateCutting("TILE.png", 3, 1);

	UEngineSprite::CreateCutting("Algae.png", 3, 3);
	UEngineSprite::CreateCutting("Box.png", 3, 3);
	UEngineSprite::CreateCutting("Crab.png", 6, 3);
	UEngineSprite::CreateCutting("Door.png", 3, 3);
	UEngineSprite::CreateCutting("Jelly.png", 3, 3);
	UEngineSprite::CreateCutting("Key.png", 3, 3);
	UEngineSprite::CreateCutting("Pillar.png", 3, 3);
	UEngineSprite::CreateCutting("Star.png", 3, 3);
	UEngineSprite::CreateCutting("Has.png", 3, 3);
	UEngineSprite::CreateCutting("Open.png", 3, 3);
	UEngineSprite::CreateCutting("Shut.png", 3, 3);
	
	UEngineSprite::CreateCutting("NumberFont.png", 5, 2);
	UEngineSprite::CreateCutting("SelectMap_background.png", 3, 1);
	UEngineSprite::CreateCutting("SelectObj.png", 3, 1);

	UEngineSprite::CreateCutting("NumbersFont.png", 10, 6);
	UEngineSprite::CreateCutting("Alphabet.png", 14, 12);
	UEngineSprite::CreateCutting("U.png", 1, 3);
	UEngineSprite::CreateCutting("N.png", 1, 3);
	UEngineSprite::CreateCutting("D.png", 1, 3);
	UEngineSprite::CreateCutting("O.png", 1, 3);
	UEngineSprite::CreateCutting("R.png", 1, 3);
	UEngineSprite::CreateCutting("E.png", 1, 3);
	UEngineSprite::CreateCutting("S.png", 1, 3);
	UEngineSprite::CreateCutting("T.png", 1, 3);
	UEngineSprite::CreateCutting("A.png", 1, 3);
	UEngineSprite::CreateCutting("B.png", 1, 3);
	UEngineSprite::CreateCutting("I.png", 1, 3);
	UEngineSprite::CreateCutting("Y.png", 1, 3);


	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsShader");
		UEngineShader::AutoCompile(Dir);
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("CirCleFadeIN");
		Mat->SetPixelShader("CirCleFadeINShader.fx");
		Mat->SetVertexShader("CirCleFadeINShader.fx");
	}

	{
		std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("CirCleFadeOUT");
		Mat->SetPixelShader("CirCleFadeOUTShader.fx");
		Mat->SetVertexShader("CirCleFadeOUTShader.fx");
	}
}

