#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace gce
{
    class Geometry;
    struct Vertex;

    class ObjLoader
    {
    public:
        // Charge un fichier OBJ et retourne une Geometry compatible avec le moteur
        static Geometry* LoadFromFile(const std::string& filepath);

    private:
        struct TempVertex
        {
            float x, y, z;
        };

        struct TempTexCoord
        {
            float u, v;
        };

        struct TempNormal
        {
            float nx, ny, nz;
        };

        struct FaceIndex
        {
            int vertexIndex;
            int texCoordIndex;
            int normalIndex;
        };

        static bool ParseObjFile(const std::string& filepath,std::vector<TempVertex>& positions,std::vector<TempTexCoord>& texCoords,std::vector<TempNormal>& normals,std::vector<std::vector<FaceIndex>>& faces);

        static void BuildGeometryData(const std::vector<TempVertex>& positions,const std::vector<TempTexCoord>& texCoords,const std::vector<TempNormal>& normals,const std::vector<std::vector<FaceIndex>>& faces,std::vector<Vertex>& vertices,std::vector<uint32_t>& indices);

        static void TriangulateBuiltFace(const std::vector<uint32_t>& face, std::vector<uint32_t>& indices);

        static void TriangulateFace(const std::vector<FaceIndex>& face,std::vector<uint32_t>& indices, uint32_t baseIndex);

        static void CalculateTangents(std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    };
}


