#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace gce
{
    struct float3
    {
        float x, y, z;
        float3() : x(0), y(0), z(0) {}
        float3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    };

    struct MaterialData
    {
        std::string name = "";
        float3 albedoColor = float3(0.5f, 0.5f, 0.5f);
    };

    class MtlLoader
    {
    public:
        // Charge tous les matériaux depuis un fichier .mtl
        static std::vector<MaterialData> LoadFromFile(const std::string& filepath);

        // Charge et retourne un dictionnaire nom -> material pour un accès rapide
        static std::unordered_map<std::string, MaterialData> LoadAsMap(const std::string& filepath);

        // Charge un matériau spécifique par son nom
        static MaterialData LoadMaterial(const std::string& filepath, const std::string& materialName);

    private:
        static bool ParseMtlFile(
            const std::string& filepath,
            std::vector<MaterialData>& materials
        );
    };
}

