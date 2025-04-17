#pragma once

class RayTracingRenderer
{
public:
    RayTracingRenderer();
    ~RayTracingRenderer();

    void Update();
    void Render();

    void AddObject(Vector pos, Vector size, Vector color, float reflectivity, int type);
    void SetLight(Vector pos, float intensity);
    void SetShadow(float shadowIntensity, float ambient);
    void SetMaterial(float diffuse, float specular, float shininess);

private:
    void CreateMesh();
    void CreateShaders();

    vector<Vertex_Texture> _vertices;
    vector<UINT> _indices;

    shared_ptr<VertexBuffer> _vertexBuffer;
    shared_ptr<IndexBuffer> _indexBuffer;

    shared_ptr<VertexShader> _vs;
    shared_ptr<PixelShader> _ps;

    shared_ptr<Transform> _transform;
    shared_ptr<RayTracingBuffer> _rayTracingBuffer;
    shared_ptr<RTObjectBuffer> _rtObjectBuffer;

    int _objectCount = 0;
}; 