#pragma once

class RayTracingScene : public Scene
{
public:
    RayTracingScene();
    ~RayTracingScene();

    virtual void Update() override;
    virtual void Render() override;

    virtual void PreUpdate() override {}
    virtual void PostRender() override {}

private:
    shared_ptr<RayTracingRenderer> _rayTracer;
    bool _isLightMoving = true;
    float _lightAngle = 0.0f;
}; 