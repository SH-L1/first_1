#pragma once

class DunBow : public Quad
{
public:
	DunBow(wstring textureFile);
	~DunBow();

	void PreUpdate() override;
	void Update() override;
	void Render() override;
	void PostRender() override;

	void CreateMesh() override;

private:
};