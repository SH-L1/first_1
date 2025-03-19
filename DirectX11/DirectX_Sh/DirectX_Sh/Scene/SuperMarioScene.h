#pragma once

class SuperMarioScene : public Scene
{
public:
	SuperMarioScene();
	~SuperMarioScene();

	virtual void PreUpdate() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	
private:

};