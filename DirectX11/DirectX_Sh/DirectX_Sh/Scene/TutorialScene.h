#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	void Update() override;
	void Render() override;

private:
	shared_ptr<Quad> _quad1;
	shared_ptr<Quad> _quad2;
};