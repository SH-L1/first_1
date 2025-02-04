#include "framework.h"
#include "ArrowScene.h"

ArrowScene::ArrowScene()
{
	_player = make_shared<Quad>(L"Resource/Player.png");
	_bow = make_shared<Quad>(L"Resource/Bow.png");
	_bullet = make_shared<Quad>(L"Resource/Bullet.png");
	_monster = make_shared<Quad>(L"Resource/monster.png");

	_player->GetTransform()->SetPos(CENTRE);
	_player->GetTransform()->SetScale(Vector(0.5f, 0.5f));
	_arrowTrans = make_shared<Transform>();
	
	_bow->GetTransform()->SetPos({ 50, 50 });
	_bow->GetTransform()->SetParent(_arrowTrans);

}

ArrowScene::~ArrowScene()
{
}

void ArrowScene::Update()
{
	_player->Update();
	_bow->Update();
}

void ArrowScene::Render()
{
	_player->Render();
	_bow->Render();
}
