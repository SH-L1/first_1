#pragma once

struct ObjectData
{
    XMFLOAT2 pos;
    XMFLOAT2 size;
    XMFLOAT2 uvOffset;
    XMFLOAT2 uvScale;
    float reflectivity;
    int type;
    int pad0, pad1;
};

class Quad
{
public:
    Quad(wstring textureFile);
    ~Quad();

    void Update();
    void Render();

    void CreateMaterial(wstring textureFile);
    void CreateMesh();

    Vector GetImageSize() { return _srv->GetImageSize(); }
    shared_ptr<Transform> GetTransform() { return _transform; }
    void SetLeftRight(int value) { _leftRightBuffer->SetData(value); _leftRightBuffer->Update(); }
    void AddColor(XMFLOAT4 color) { _colorBuffer->SetData(color); _colorBuffer->Update(); }
    void SetRayTracingData(const RayTracingBuffer::Data& data) { _rayBuffer->SetData(data); _rayBuffer->Update(); }
    void SetObjectData(const ObjectData* objects, UINT count) { _objects->SetData(objects, count); _objects->Update(); }
    void SetObjectData(const ObjectData& object) { _objects->SetData(&object, 1); _objects->Update(); }

protected:
    vector<Vertex_Texture> _vertices;
    vector<UINT> _indices;

    shared_ptr<VertexBuffer> _vertexBuffer;
    shared_ptr<IndexBuffer> _indexBuffer;

    shared_ptr<VertexShader> _vs;
    shared_ptr<PixelShader> _ps;

    shared_ptr<SRV> _srv;

    shared_ptr<Transform> _transform;
    shared_ptr<LeftRightBuffer> _leftRightBuffer;
    shared_ptr<ColorBuffer> _colorBuffer;
    shared_ptr<RayTracingBuffer> _rayBuffer;
    shared_ptr<StructuredBuffer<ObjectData>> _objects;
};