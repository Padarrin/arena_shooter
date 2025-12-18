#pragma once
#include "../Render/Geometry.h"
#include "../Render/Structs.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <limits>
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
        static Geometry* LoadFromFile(const std::string& filepath)
        {
            std::vector<TempVertex> positions;
            std::vector<TempTexCoord> texCoords;
            std::vector<TempNormal> normals;
            std::vector<std::vector<FaceIndex>> faces;

            if (!ParseObjFile(filepath, positions, texCoords, normals, faces))
            {
                return nullptr;
            }

            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;
            BuildGeometryData(positions, texCoords, normals, faces, vertices, indices);

            if (vertices.empty() || indices.empty())
            {
                return nullptr;
            }

            // Calculer les tangentes après avoir construit les vertices
            CalculateTangents(vertices, indices);

            Geometry* geometry = new Geometry();
            geometry->Initialize(vertices.data(), vertices.size(), indices.data(), indices.size());

            return geometry;
        }

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

        static bool ParseObjFile(const std::string& filepath, std::vector<TempVertex>& positions, std::vector<TempTexCoord>& texCoords, std::vector<TempNormal>& normals, std::vector<std::vector<FaceIndex>>& faces)
        {
            std::ifstream file(filepath);
            if (!file.is_open())
            {
                return false;
            }

            std::string line;
            while (std::getline(file, line))
            {
                if (line.empty() || line[0] == '#')
                    continue;

                std::istringstream iss(line);
                std::string prefix;
                iss >> prefix;

                if (prefix == "v")
                {
                    TempVertex v;
                    iss >> v.x >> v.y >> v.z;
                    positions.push_back(v);
                }
                else if (prefix == "vt")
                {
                    TempTexCoord vt;
                    iss >> vt.u >> vt.v;
                    texCoords.push_back(vt);
                }
                else if (prefix == "vn")
                {
                    TempNormal vn;
                    iss >> vn.nx >> vn.ny >> vn.nz;
                    normals.push_back(vn);
                }
                else if (prefix == "f")
                {
                    std::vector<FaceIndex> face;
                    std::string vertexData;

                    while (iss >> vertexData)
                    {
                        FaceIndex faceIndex = { -1, -1, -1 };

                        size_t pos1 = vertexData.find('/');
                        if (pos1 != std::string::npos)
                        {
                            faceIndex.vertexIndex = std::stoi(vertexData.substr(0, pos1)) - 1;

                            size_t pos2 = vertexData.find('/', pos1 + 1);
                            if (pos2 != std::string::npos)
                            {
                                if (pos2 > pos1 + 1)
                                {
                                    faceIndex.texCoordIndex = std::stoi(vertexData.substr(pos1 + 1, pos2 - pos1 - 1)) - 1;
                                }
                                faceIndex.normalIndex = std::stoi(vertexData.substr(pos2 + 1)) - 1;
                            }
                            else if (pos1 + 1 < vertexData.length())
                            {
                                faceIndex.texCoordIndex = std::stoi(vertexData.substr(pos1 + 1)) - 1;
                            }
                        }
                        else
                        {
                            faceIndex.vertexIndex = std::stoi(vertexData) - 1;
                        }

                        face.push_back(faceIndex);
                    }

                    if (face.size() >= 3)
                    {
                        faces.push_back(face);
                    }
                }
            }

            file.close();
            return !positions.empty();
        }
        static void BuildGeometryData(const std::vector<TempVertex>& positions, const std::vector<TempTexCoord>& texCoords, const std::vector<TempNormal>& normals, const std::vector<std::vector<FaceIndex>>& faces, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
        {
            struct VertexKey
            {
                int posIdx;
                int texIdx;
                int normIdx;

                bool operator==(const VertexKey& other) const
                {
                    return posIdx == other.posIdx && texIdx == other.texIdx && normIdx == other.normIdx;
                }
            };

            struct VertexKeyHash
            {
                size_t operator()(const VertexKey& k) const
                {
                    return std::hash<int>()(k.posIdx) ^
                        (std::hash<int>()(k.texIdx) << 1) ^
                        (std::hash<int>()(k.normIdx) << 2);
                }
            };

            std::unordered_map<VertexKey, uint32_t, VertexKeyHash> vertexMap;

            for (const auto& face : faces)
            {
                // On va stocker les vrais indices reconstruits de cette face
                std::vector<uint32_t> builtFace;

                for (const auto& faceIndex : face)
                {
                    VertexKey key = { faceIndex.vertexIndex, faceIndex.texCoordIndex, faceIndex.normalIndex };
                    auto it = vertexMap.find(key);

                    if (it != vertexMap.end())
                    {
                        builtFace.push_back(it->second);
                    }
                    else
                    {
                        Vertex vertex = {};

                        // position
                        const TempVertex& pos = positions[faceIndex.vertexIndex];
                        vertex.pos = { pos.x, pos.y, pos.z };

                        // uv
                        if (faceIndex.texCoordIndex >= 0)
                        {
                            const TempTexCoord& tc = texCoords[faceIndex.texCoordIndex];
                            vertex.uv = { tc.u, tc.v };
                        }

                        // normal
                        if (faceIndex.normalIndex >= 0)
                        {
                            const TempNormal& n = normals[faceIndex.normalIndex];
                            vertex.normal = { n.nx, n.ny, n.nz };
                        }

                        uint32_t newIndex = vertices.size();
                        vertices.push_back(vertex);
                        vertexMap[key] = newIndex;
                        builtFace.push_back(newIndex);
                    }
                }

                // Maintenant builtFace contient les vrais indices de la face

                if (builtFace.size() >= 3)
                {
                    if (builtFace.size() == 3)
                    {
                        // Déjà un triangle, on l'ajoute tel quel
                        indices.push_back(builtFace[0]);
                        indices.push_back(builtFace[1]);
                        indices.push_back(builtFace[2]);
                    }
                    else
                    {
                        // On triangule cette face à partir de builtFace
                        TriangulateBuiltFace(builtFace, indices);
                    }
                }
            }
            /*for (const auto& face : faces)
            {
                uint32_t baseFaceIndex = static_cast<uint32_t>(vertices.size());

                for (const auto& faceIndex : face)
                {
                    VertexKey key = { faceIndex.vertexIndex, faceIndex.texCoordIndex, faceIndex.normalIndex };

                    auto it = vertexMap.find(key);
                    if (it != vertexMap.end())
                    {
                        indices.push_back(it->second);
                    }
                    else
                    {
                        Vertex vertex = {};

                        if (faceIndex.vertexIndex >= 0 && faceIndex.vertexIndex < static_cast<int>(positions.size()))
                        {
                            const TempVertex& pos = positions[faceIndex.vertexIndex];
                            vertex.pos.x = pos.x;
                            vertex.pos.y = pos.y;
                            vertex.pos.z = pos.z;
                        }

                        if (faceIndex.texCoordIndex >= 0 && faceIndex.texCoordIndex < static_cast<int>(texCoords.size()))
                        {
                            const TempTexCoord& tc = texCoords[faceIndex.texCoordIndex];
                            vertex.uv.x = tc.u;
                            vertex.uv.y = tc.v;
                        }
                        else
                        {
                            vertex.uv.x = 0.0f;
                            vertex.uv.y = 0.0f;
                        }

                        if (faceIndex.normalIndex >= 0 && faceIndex.normalIndex < static_cast<int>(normals.size()))
                        {
                            const TempNormal& n = normals[faceIndex.normalIndex];
                            vertex.normal.x = n.nx;
                            vertex.normal.y = n.ny;
                            vertex.normal.z = n.nz;
                        }
                        else
                        {
                            vertex.normal.x = 0.0f;
                            vertex.normal.y = 1.0f;
                            vertex.normal.z = 0.0f;
                        }

                        // Tangente initialisée à zéro, sera calculée plus tard
                        vertex.tangent.x = 0.0f;
                        vertex.tangent.y = 0.0f;
                        vertex.tangent.z = 0.0f;

                        uint32_t newIndex = static_cast<uint32_t>(vertices.size());
                        vertices.push_back(vertex);
                        vertexMap[key] = newIndex;
                        indices.push_back(newIndex);
                    }
                }

                if (face.size() > 3)
                {
                    size_t triCount = face.size() - 2;
                    size_t startIdx = indices.size() - face.size();

                    std::vector<uint32_t> faceIndices;
                    for (size_t i = 0; i < face.size(); ++i)
                    {
                        faceIndices.push_back(indices[startIdx + i]);
                    }

                    indices.erase(indices.begin() + startIdx, indices.begin() + startIdx + face.size());

                    TriangulateFace(face, indices, baseFaceIndex);
                }
            }*/
        }
        static void TriangulateBuiltFace(const std::vector<uint32_t>& face, std::vector<uint32_t>& indices)
        {
            // triangle fan basé sur les bons index déjà produits !
            for (size_t i = 1; i + 1 < face.size(); i++)
            {
                indices.push_back(face[0]);
                indices.push_back(face[i]);
                indices.push_back(face[i + 1]);
            }
        }
        static void TriangulateFace(const std::vector<FaceIndex>& face, std::vector<uint32_t>& indices, uint32_t baseIndex)
        {
            for (size_t i = 1; i < face.size() - 1; ++i)
            {
                indices.push_back(baseIndex);
                indices.push_back(baseIndex + static_cast<uint32_t>(i));
                indices.push_back(baseIndex + static_cast<uint32_t>(i + 1));
            }
        }
        static void CalculateTangents(std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
        {
            // Initialiser les tangentes à zéro
            for (auto& vertex : vertices)
            {
                vertex.tangent.x = 0.0f;
                vertex.tangent.y = 0.0f;
                vertex.tangent.z = 0.0f;
            }

            // Calculer les tangentes pour chaque triangle
            for (size_t i = 0; i < indices.size(); i += 3)
            {
                uint32_t i0 = indices[i];
                uint32_t i1 = indices[i + 1];
                uint32_t i2 = indices[i + 2];

                Vertex& v0 = vertices[i0];
                Vertex& v1 = vertices[i1];
                Vertex& v2 = vertices[i2];

                // Edges du triangle
                float edge1X = v1.pos.x - v0.pos.x;
                float edge1Y = v1.pos.y - v0.pos.y;
                float edge1Z = v1.pos.z - v0.pos.z;

                float edge2X = v2.pos.x - v0.pos.x;
                float edge2Y = v2.pos.y - v0.pos.y;
                float edge2Z = v2.pos.z - v0.pos.z;

                // Delta UV
                float deltaU1 = v1.uv.x - v0.uv.x;
                float deltaV1 = v1.uv.y - v0.uv.y;
                float deltaU2 = v2.uv.x - v0.uv.x;
                float deltaV2 = v2.uv.y - v0.uv.y;

                float det = deltaU1 * deltaV2 - deltaU2 * deltaV1;

                if (std::abs(det) > 1e-6f)
                {
                    float invDet = 1.0f / det;

                    float tangentX = invDet * (deltaV2 * edge1X - deltaV1 * edge2X);
                    float tangentY = invDet * (deltaV2 * edge1Y - deltaV1 * edge2Y);
                    float tangentZ = invDet * (deltaV2 * edge1Z - deltaV1 * edge2Z);

                    // Accumuler les tangentes pour chaque vertex du triangle
                    v0.tangent.x += tangentX;
                    v0.tangent.y += tangentY;
                    v0.tangent.z += tangentZ;

                    v1.tangent.x += tangentX;
                    v1.tangent.y += tangentY;
                    v1.tangent.z += tangentZ;

                    v2.tangent.x += tangentX;
                    v2.tangent.y += tangentY;
                    v2.tangent.z += tangentZ;
                }
            }

            // Normaliser et orthogonaliser les tangentes (Gram-Schmidt)
            for (auto& vertex : vertices)
            {
                float tx = vertex.tangent.x;
                float ty = vertex.tangent.y;
                float tz = vertex.tangent.z;

                float nx = vertex.normal.x;
                float ny = vertex.normal.y;
                float nz = vertex.normal.z;

                // Orthogonaliser : tangent = tangent - (tangent·normal) * normal
                float dot = tx * nx + ty * ny + tz * nz;
                tx -= dot * nx;
                ty -= dot * ny;
                tz -= dot * nz;

                // Normaliser
                float length = std::sqrt(tx * tx + ty * ty + tz * tz);
                if (length > 1e-6f)
                {
                    float invLength = 1.0f / length;
                    vertex.tangent.x = tx * invLength;
                    vertex.tangent.y = ty * invLength;
                    vertex.tangent.z = tz * invLength;
                }
                else
                {
                    // Tangente par défaut si impossible à calculer
                    vertex.tangent.x = 1.0f;
                    vertex.tangent.y = 0.0f;
                    vertex.tangent.z = 0.0f;
                }
            }
        }
    };
}


