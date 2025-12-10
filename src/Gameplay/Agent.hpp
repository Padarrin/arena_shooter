#pragma once
#include "Character.hpp"
#include "Queue.hpp"
#include "compare.h"
#include "PathFinding.h"
#include "Grid.h"

DECLARE_SCRIPT(ScriptAgent, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	PathFinding<Cell> mPathFinding;

public:
	ScriptCharacter* mCharacter;

	virtual void Initia() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); mCharacter->Initia(); void SetPathFinding(PathFinding<Cell>()); }
	virtual void Start() { void SetPaths(Queue_<Cell, ComparePath<Cell>>()); }
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) {}
	virtual void CollisionStay(GameObject* other) {}
	virtual void CollisionExit(GameObject* other) {}

	void SetPathFinding(PathFinding<Cell> pathFinding) { mPathFinding = pathFinding; }
	PathFinding<Cell>* GetPathFinding() { return &mPathFinding; }

	void SetPaths(Queue_<Cell, ComparePath<Cell>> path) { mPathFinding.SetPaths(path); }
	Queue_<Cell, ComparePath<Cell>>* GetPaths() { return mPathFinding.GetPaths(); }


	void GoToCell(Cell* cellEnd, Grid* grid)
	{
		gce::Vector2i32 indexRowCol = cellEnd->GetRowCol();
		std::vector<Node<Cell>*>* allNodes = grid->GetAllNodes();
		int lengthCell = grid->GetSizeTabCell();
		GoToNode(GetNodeInTab((int)indexRowCol.x, (int)indexRowCol.y, lengthCell, allNodes), grid);
	}

	void GoToCell(gce::Vector3f32 pos, Grid* grid)
	{
		GoToNode(GetNode<Cell>(pos, grid), grid);
	}

	void GoToNode(Node<Cell>* endNode, Grid* grid)
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
			startNode = GetNode<Cell>(GetWorldPosition(), grid);
		}

		GoToNode(startNode, endNode, grid);
	}

	void GoToNode(Node<Cell>* startNode, Node<Cell>* endNode, Grid* grid)
	{
		//SetStartNode(startNode);
		//SetEndNode(endNode);
		mPathFinding.Find(startNode, endNode, grid, this);
	}

	void SetWorldPosition(gce::Vector3f32 position) { mCharacter->mEntity->SetWorldPosition(position); }
	gce::Vector3f32 GetWorldPosition() { return mCharacter->mEntity->GetWorldPosition(); }
	void WorldTranslate(gce::Vector3f32 position) { mCharacter->mEntity->WorldTranslate(position); }

END_SCRIPT

