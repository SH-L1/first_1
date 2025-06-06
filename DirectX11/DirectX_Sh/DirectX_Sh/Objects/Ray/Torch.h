#pragma once

class Torch
{
public:
	Torch();
	~Torch();

	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	void Falling();

	void SetActive(bool active) { _isActive = active; }
	void SetGrounds(const vector<shared_ptr<RectCollider>>& grounds) { _grounds = grounds; }

	shared_ptr<Transform> GetTransform() { return _torch->GetTransform(); }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	bool GetActive() { return _isActive; }
	RayTracingBuffer::Data GetLightData() { return _rayData; }
	shared_ptr<Quad> GetQuad() { return _torch; }
	ObjectData GetObjectData() { return _objData; }

	bool IsPickedUp() { return _isPickedUp; }

	void SetLightData(const RayTracingBuffer::Data& data) { _rayData = data; }
	void SetObjectData(const ObjectData& data) { _objData = data; }
	void SetPickedUp(bool picked) { _isPickedUp = picked; }
	void SetRayTracingData(const RayTracingBuffer::Data& data) { _rayData = data; }
	void SetObjectData(const ObjectData* objects, UINT count) { _torch->SetObjectData(objects, count); }

	void SetPosition(Vector pos) {
		_collider->SetPos(pos);
		_objData.pos = pos;
		_velocity = Vector(0, 0);
	}

private:
	shared_ptr<Quad> _torch;
	shared_ptr<RectCollider> _collider;

	vector<shared_ptr<RectCollider>> _grounds;

	RayTracingBuffer::Data _rayData;
	ObjectData _objData;

private:
	bool _isPickedUp = false;

	Vector _textureScale = Vector(300.0f, 120.0f);
	Vector _colliderScale = Vector(0.1f, 0.2f);

	Vector _velocity = Vector(0, 0);
	bool _isActive = false;
	float _gravity = 100.0f;
};