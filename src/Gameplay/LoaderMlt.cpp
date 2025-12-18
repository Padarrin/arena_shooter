#include "LoaderMlt.h"
#include <fstream>
#include <sstream>

namespace gce
{
    std::vector<MaterialData> MtlLoader::LoadFromFile(const std::string& filepath)
    {
        std::vector<MaterialData> materials;
        ParseMtlFile(filepath, materials);
        return materials;
    }

    std::unordered_map<std::string, MaterialData> MtlLoader::LoadAsMap(const std::string& filepath)
    {
        std::vector<MaterialData> materials = LoadFromFile(filepath);
        std::unordered_map<std::string, MaterialData> materialMap;

        for (const auto& mat : materials)
        {
            materialMap[mat.name] = mat;
        }

        return materialMap;
    }

    MaterialData MtlLoader::LoadMaterial(const std::string& filepath, const std::string& materialName)
    {
        std::vector<MaterialData> materials = LoadFromFile(filepath);

        for (const auto& mat : materials)
        {
            if (mat.name == materialName)
            {
                return mat;
            }
        }

        // Retourner un matériau par défaut si non trouvé
        MaterialData defaultMat;
        defaultMat.name = materialName;
        return defaultMat;
    }

    bool MtlLoader::ParseMtlFile(const std::string& filepath,std::vector<MaterialData>& materials)
    {
        std::ifstream file(filepath);
        if (!file.is_open())
        {
            return false;
        }

        MaterialData* currentMaterial = nullptr;
        std::string line;

        while (std::getline(file, line))
        {
            // Ignorer les lignes vides et les commentaires
            if (line.empty() || line[0] == '#')
                continue;

            // Supprimer les espaces en début de ligne
            size_t start = line.find_first_not_of(" \t\r\n");
            if (start == std::string::npos)
                continue;

            line = line.substr(start);

            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            // Nouveau matériau
            if (prefix == "newmtl")
            {
                MaterialData newMat;
                std::string name;

                // Lire le reste de la ligne comme nom (peut contenir des espaces)
                std::getline(iss >> std::ws, name);
                newMat.name = name;

                materials.push_back(newMat);
                currentMaterial = &materials.back();
            }
            // Couleur diffuse (albedo)
            else if (currentMaterial && prefix == "Kd")
            {
                float r, g, b;
                iss >> r >> g >> b;
                currentMaterial->albedoColor = float3(r, g, b);
            }
            // Couleur ambiante (peut servir d'albedo alternatif)
            else if (currentMaterial && prefix == "Ka")
            {
                // Si Kd n'a pas été défini, utiliser Ka
                if (currentMaterial->albedoColor.x == 0.5f &&
                    currentMaterial->albedoColor.y == 0.5f &&
                    currentMaterial->albedoColor.z == 0.5f)
                {
                    float r, g, b;
                    iss >> r >> g >> b;
                    currentMaterial->albedoColor = float3(r, g, b);
                }
            }
            // Autres propriétés MTL (ignorées pour le moment, mais peuvent être ajoutées)
            // Ks : couleur spéculaire
            // Ns : exposant spéculaire (shininess)
            // d ou Tr : transparence
            // illum : modèle d'illumination
            // map_Kd : texture diffuse
            // map_Ks : texture spéculaire
            // map_Bump ou bump : normal map
        }

        file.close();
        return !materials.empty();
    }
}
