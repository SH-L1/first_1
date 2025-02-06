#include "framework.h"
#include "ArrowScene.h"

ArrowScene::ArrowScene()
{
	_player = make_shared<Player>(L"Resource/Player.png");
	_bow = make_shared<Bow>(L"Resource/Bow.png");
	_bullet = make_shared<Quad>(L"Resource/Bullet.png");
	_monster = make_shared<Quad>(L"Resource/monster.png");

	_bow->GetTransform()->SetPos({ 50, 50 });
	_bow->GetTransform()->SetScale({ 0.5f, 0.5f });
	
	_arrowTrans = make_shared<Transform>();
	_bow->GetTransform()->SetParent(_arrowTrans);
}

ArrowScene::~ArrowScene()
{
}

void ArrowScene::Update()
{
	_bow->Update();
	
	/*{
		Vector dis = mousePos - _bow->GetTransform()->GetPos();

		float angle = atan2(dis.y, dis.x) * 90.0f / 3.14f;

		_bow->GetTransform()->SetAngle(angle);
	}*/
}

void ArrowScene::Render()
{
	_bow->Render();
}
