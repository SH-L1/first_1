#pragma once

class SolarSystemScene : public Scene
{
public:
	SolarSystemScene();
	~SolarSystemScene();

	void Update() override;
	void Render() override;

private:
	shared_ptr<Quad> _sun;
	shared_ptr<Quad> _earth;
	shared_ptr<Quad> _moon;

	shared_ptr<Transform> _sunTrans;
	shared_ptr<Transform> _earthTrans;
};