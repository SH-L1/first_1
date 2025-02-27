#pragma once

class DunBow
{
public:
	DunBow();
	~DunBow();

	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	shared_ptr<Transform> GetTransform() { return _bow->GetTransform(); }

private:
	void SetAim();

private:
	shared_ptr<Quad> _bow;
};