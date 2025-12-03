#include "pch.h"
#include "Functions.h"

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

Entity* GetNearestAgent(gce::Vector3f32 pos)
{
    /*for (Entity* e : GameManager::Get()->GetEntities())
    {
        if (e->IsType(Tag::AGENT) == false)
            continue;

        if (e->IsInside(pos.x, pos.y, pos.z))
        {
            return e;
        }
    }*/

    return nullptr;
}

float DisManhattan(gce::Vector3f32 currentPos, gce::Vector3f32 endPos, int sizeCell)
{
    return (abs(currentPos.x - endPos.x) + abs(currentPos.y - endPos.y)) / sizeCell;
}

gce::Vector2f32 GetCellInPos(gce::Vector3f32 pos, int sizeCell)
{
    //Cell* nearest = GetNearestCell<Cell>(pos, GameManager::Get()->GetScene<MainScene>()->GetGrid()->GetAllCells());

    //if (!nearest)
    //    return { 0, 0 };

    //return 	nearest->GetRowCol();
    return gce::Vector2f32();
}
