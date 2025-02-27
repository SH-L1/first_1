#pragma once

class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	virtual void PreUpdate() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

private:
	shared_ptr<class DunBullet> test;
};