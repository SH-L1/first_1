#pragma once

class Bow : public Quad
{
public:
	Bow(wstring textFile);
	~Bow();

	void Update() override;
	void Render() override;

	void CreateMesh() override;
};