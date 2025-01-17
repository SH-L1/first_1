#pragma once
class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	// Scene을(를) 통해 상속됨
	void Update() override;
	void Render() override;

private:
	// 정점 정보들
	shared_ptr<VertexBuffer> _vertexBuffer;
	// GPU가 수행할 연산을 적어놓은 곳
	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	// 판박이 만드는 아저씨
	shared_ptr<SRV> _srv;
	// 판박이 붙히는 아저씨
	shared_ptr<SamplerState> _samplerState;
};

