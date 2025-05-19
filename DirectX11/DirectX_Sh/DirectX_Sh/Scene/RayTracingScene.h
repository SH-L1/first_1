#pragma once

class RayTracingScene : public Scene
{
public:
    RayTracingScene();
    ~RayTracingScene();

    virtual void PreUpdate() override {}
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override {}

    void CreateTorchOnSreen();

private:
    shared_ptr<Mario> _player;
    vector<shared_ptr<Torch>> _torches;
    vector<shared_ptr<Wall>> _walls;

private:
    int _torchNum = 30;
    int _wallNum = 3;
}; 