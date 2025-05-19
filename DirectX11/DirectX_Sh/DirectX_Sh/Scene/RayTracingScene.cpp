#include "framework.h"
#include "RayTracingScene.h"

RayTracingScene::RayTracingScene()
{
	_player = make_shared<Mario>();
	
	for (int i = 0; i < _torchNum; i++)
	{
		shared_ptr<Torch> torch = make_shared<Torch>();
		_torches.push_back(torch);
	}

	for (int i = 0; i < _wallNum; i++)
	{
		shared_ptr<Wall> wall = make_shared<Wall>();
		_walls.push_back(wall);
	}

	_player->SetPos(Vector(CENTRE.x, WIN_HEIGHT * 0.4f));
	_player->Update();
}

RayTracingScene::~RayTracingScene()
{
}

void RayTracingScene::PreUpdate()
{
	for (auto torch : _torches)
		torch->PreUpdate();
	
	_player->PreUpdate();
}

void RayTracingScene::Update()
{
	for (auto torch : _torches)
		torch->Update();

	_player->Update();

}

void RayTracingScene::Render()
{
	for (auto torch : _torches)
		torch->Render();

	_player->Render();
}

void RayTracingScene::PostRender()
{
	for (auto torch : _torches)
		torch->PostRender();

	_player->PostRender();
}

void RayTracingScene::CreateTorchOnSreen()
{
	auto deactiveTorch = find_if(_torches.begin(), _torches.end(), [](const auto& a)->bool {
		return !(a->GetActive());
		});

	if (deactiveTorch != _torches.end())
	{
		(*deactiveTorch)->SetActive(true);
		(*deactiveTorch)->GetTransform()->SetPos(mousePos);
	}
}