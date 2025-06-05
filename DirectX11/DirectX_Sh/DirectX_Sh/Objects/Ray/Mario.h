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
	void SetGrounds(const vector<shared_ptr<RectCollider>>& grounds) { _grounds = grounds; }
	void SetTorch(const shared_ptr<Torch>& torch) { _torch = torch; }
	void SetPos(Vector pos) { _collider->GetTransform()->SetPos(pos); }
	void SetObjectData(ObjectData objData) { _objData = objData; }
	void SetLightData(RayTracingBuffer::Data rayData, int size) { _rayData = rayData; }
	
	bool IsEquipped() { return _isEquip; }
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
	vector<shared_ptr<RectCollider>> _grounds;

	RayTracingBuffer::Data _rayData;
	ObjectData _objData;

private:
	Vector _textureScale = Vector(8.0f, 16.0f);  
	Vector _colliderScale = Vector(4.0f, 3.0f);

	Vector _velocity = Vector(0, 0);
	bool _isJumping = false;
	bool _isEquip = false;

	float _playerSpeed = 400.0f;
	float _jumpHeight = 30.0f;
	float _gravity = 500.0f;	
};