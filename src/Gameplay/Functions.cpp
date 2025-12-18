#include "pch.h"
#include "Functions.h"
#include "Agent.hpp"

bool Normalize(gce::Vector3f32& vector)
{
    float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);

    if (magnitude != 0)
    {
        vector.x /= magnitude;
        vector.y /= magnitude;
        vector.z /= magnitude;
        return true;
    }

    return false;
}

float GetDistance(gce::Vector3f32 pos1, gce::Vector3f32 pos2)
{
    int x = pos2.x - pos1.x;
    int y = pos2.y - pos1.y;
    int z = pos2.z - pos1.z;

    return std::sqrt(x * x + y * y + z * z);
}

Entity* GetNearestEntity(gce::Vector3f32 pos)
{
    /*for (Entity* e : GameManager::Get()->GetEntities())
    {
        if (e->IsInside(pos.x, pos.y, pos.z))
        {
            return e;
        }
    }*/

    return nullptr;
}

ScriptAgent* GetNearestAgent(gce::Vector3f32 pos, gce::GameObject* menu)
{
    ScriptAgent* agentNeraest = nullptr;
    gce::Vector3f32 posNeraest = gce::Vector3f32(INT_MAX, INT_MAX, INT_MAX);
    auto* mapGameObject = menu->m_pScene->GetGameObject();
    for (auto& [id, gameObject] : *mapGameObject)
    {
        if (gameObject->HasScript<ScriptAgent>())
        {
            ScriptAgent* agent = gameObject->GetScript<ScriptAgent>();
            gce::Vector3f32 agentPos = agent->GetWorldPosition();
            if (posNeraest.x > agentPos.x && posNeraest.y > agentPos.y && posNeraest.z > agentPos.z)
            {
                agentNeraest = agent;
            }
        }
    }
    return agentNeraest;
}

float DisManhattan(gce::Vector3f32 currentPos, gce::Vector3f32 endPos, int sizeCell)
{
    return (abs(currentPos.x - endPos.x) + abs(currentPos.y - endPos.y)) / sizeCell;
}
