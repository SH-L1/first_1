#pragma once

class RayTracingScene : public Scene
{
public:
    RayTracingScene();
    ~RayTracingScene();

    virtual void PreUpdate() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;

    void CreateTorchOnSreen();

private:
    shared_ptr<Mario> _player;
    shared_ptr<Torch> _torch;
    vector<shared_ptr<Wall>> _walls;

private:
    int _wallNum = 3;
}; 