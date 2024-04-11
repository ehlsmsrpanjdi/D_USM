#include "PreCompile.h"
#include "BabaBase.h"
#include "ContentsHelper.h"
#include <EngineCore/SpriteRenderer.h>
//
//void ABabaBase::StateInit() {
//	FSM_State.CreateState("Die");
//	FSM_State.CreateState("Idle");
//	FSM_State.CreateState("Move");
//
//	FSM_State.SetStartFunction("Idle", std::bind(&ABabaBase::IdleStart, this));
//	FSM_State.SetUpdateFunction("Idle", std::bind(&ABabaBase::Idle, this, std::placeholders::_1));
//
//
//	FSM_State.SetStartFunction("Move", std::bind(&ABabaBase::MoveStart, this));
//	FSM_State.SetUpdateFunction("Move", std::bind(&ABabaBase::Move, this, std::placeholders::_1));
//
//}
//
//void ABabaBase::Die(float _DeltaTime)
//{
//}
//
//void ABabaBase::Idle(float _DeltaTime)
//{
//	if (Stack_Input.empty() != true) {
//		if (IsMoving != true) {
//			char Key = Stack_Input.top();
//			IsMoving = true;
//			Stack_Input.pop();
//			switch (Key) {
//			case 'A':
//				AddNextLocation2D(-50, 0);
//				break;
//			case 'D':
//				AddNextLocation2D(50, 0);
//				break;
//			case 'S':
//				AddNextLocation2D(0, -50);
//				break;
//			case 'W':
//				AddNextLocation2D(0, 50);
//				break;
//			case 'Z':
//				GoBack(_DeltaTime);
//				break;
//			default:
//				AddNextLocation2D(0, 0);
//				break;
//			}
//		}
//		FSM_State.ChangeState("Move");
//	}
//}
//
//void ABabaBase::IdleStart()
//{
//	Renderer->ChangeAnimation("Idle");
//}
//
//void ABabaBase::MoveStart()
//{
//	Renderer->ChangeAnimation("Move");
//}
//
//void ABabaBase::Move(float _DeltaTime)
//{
//	LerpMove(_DeltaTime);
//	if (IsMoving == false) {
//		FSM_State.ChangeState("Idle");
//	}
//}
//
//void ABabaBase::MoveEnd()
//{
//	Renderer->ChangeAnimation("Idle");
//}
//
//
