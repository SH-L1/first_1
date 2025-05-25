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
	void SetGround(const shared_ptr<RectCollider>& ground) { _ground = ground; }

	shared_ptr<Transform> GetTransform() { return _torch->GetTransform(); }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	bool GetActive() { return _isActive; }

	void SetLightData(const RayTracingBuffer::Data& data) { _rayData = data; }
	RayTracingBuffer::Data GetLightData() { return _rayData; }
	void SetObjectData(const ObjectData& data) { _objData = data; }
	ObjectData GetObjectData() { return _objData; }

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

	weak_ptr<RectCollider> _ground;

	RayTracingBuffer::Data _rayData;
	ObjectData _objData;

private:
	bool _isActive = false;

	Vector _velocity = Vector(0, 0);

	float _gravity = 8.0f;
};