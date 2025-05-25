#pragma once

class Torch;

class Mario
{
public:
	Mario();
	~Mario();

	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	void SetGround(const shared_ptr<RectCollider>& ground) { _ground = ground; }
	void SetTorch(const shared_ptr<Torch>& torch) { _torch = torch; }
	void SetPos(Vector pos) { _collider->GetTransform()->SetPos(pos); }
	void SetObjectData(ObjectData objData) { _objData = objData; }
	void SetLightData(RayTracingBuffer::Data rayData, int size) { _rayData = rayData; }

	shared_ptr<Transform> GetTransform() { return _player->GetTransform(); }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	shared_ptr<Quad> GetQuad() { return _player; }
	ObjectData GetObjectData() { return _objData; }
	RayTracingBuffer::Data GetLightData() { return _rayData; }

	void Input();

private:
	void Move();
	void Pick();

private:
	shared_ptr<Quad> _player;
	shared_ptr<RectCollider> _collider;
	shared_ptr<Transform> _equipment;

	weak_ptr<Torch> _torch;
	weak_ptr<RectCollider> _ground;

	RayTracingBuffer::Data _rayData;
	ObjectData _objData;

private:
	Vector _velocity = Vector(0, 0);
	bool _isJumping = false;
	bool _isEquip = false;

	float _playerSpeed = 300.0f;
	float _jumpHeight = 100.0f;
	float _gravity = 8.0f;
};