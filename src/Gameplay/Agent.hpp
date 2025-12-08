#pragma once
#include "Character.hpp"
#include "Queue.hpp"
#include "compare.h"
#include "PathFinding.h"
#include "Grid.hpp"
#include "Functions.h"

DECLARE_SCRIPT(ScriptAgent, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	PathFinding<Cell> mPathFinding;

public:
	ScriptCharacter* mCharacter;

	virtual void Initia() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); mCharacter->Initia(); SetPathFinding(PathFinding<Cell>()); mPathFinding.SetGrid(nullptr);}
	virtual void Start() { mCharacter->Start(); SetPaths(Queue_<Cell, ComparePath<Cell>>()); }
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}

	void SetPathFinding(PathFinding<Cell> pathFinding) { mPathFinding = pathFinding; }
	PathFinding<Cell>* GetPathFinding() { return &mPathFinding; }

	void SetPaths(Queue_<Cell, ComparePath<Cell>> path) { mPathFinding.SetPaths(path); }
	Queue_<Cell, ComparePath<Cell>>* GetPaths() { return mPathFinding.GetPaths(); }


	bool GoToCell(Cell* cellEnd)
	{
		ScriptGrid* grid = mPathFinding.GetGrid();
		gce::Vector2i32 indexRowCol = cellEnd->GetRowCol();
		std::vector<Node<Cell>*>* allNodes = grid->GetAllNodes();
		int lengthCell = grid->GetSizeTabCell();
		Node<Cell>* endNode = grid->GetNodeInTab((int)indexRowCol.x, (int)indexRowCol.y, lengthCell, allNodes);
		if (endNode != nullptr)
		{
			return GoToNode(endNode);
		}
		return false;
	}

	bool GoToCell(gce::Vector3f32 pos)
	{ 
		Node<Cell>* endNode = mPathFinding.GetGrid()->GetNode(pos);
		if (endNode != nullptr)
		{
			return GoToNode(endNode);
		}
		return false;
	}

	bool GoToNode(Node<Cell>* endNode)
	{
		Node<Cell>* startNode;
		Queue_<Cell, ComparePath<Cell>>* currentPath = ScriptAgent::GetPaths();
		int length = currentPath->Size();
		if (length > 0)
		{
			//position finale du path precedent
			startNode = (*currentPath)[length - 1];
		}
		else
		{
			//position actuelle
			startNode = mPathFinding.GetGrid()->GetNode(GetWorldPosition());
		}

		if (startNode != nullptr)
		{
			return GoToNode(startNode, endNode);
		}
		return false;
	}
	bool GoToNode(Node<Cell>* startNode, Node<Cell>* endNode) { mPathFinding.Find(startNode, endNode, this); return true; }

	void SetWorldPosition(gce::Vector3f32 position) { mCharacter->mEntity->SetWorldPosition(position); }
	gce::Vector3f32 GetWorldPosition() { return mCharacter->mEntity->GetWorldPosition(); }
	void WorldTranslate(gce::Vector3f32 position) { mCharacter->mEntity->WorldTranslate(position); }

END_SCRIPT

