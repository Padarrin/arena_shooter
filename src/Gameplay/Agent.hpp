#pragma once
#include "Character.hpp"
#include "Queue.hpp"
#include "compare.h"
#include "PathFinding.h"
#include "Grid.h"
#include "Functions.h"

DECLARE_SCRIPT(ScriptAgent, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy | ScriptFlag::CollisionEnter | ScriptFlag::CollisionStay | ScriptFlag::CollisionExit)

protected:
	PathFinding<Cell> mPathFinding;

public:
	ScriptCharacter* mCharacter;

	virtual void Start() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); mCharacter->Start(); }
	virtual void Update() {}
	virtual void Destroy() {}

	virtual void CollisionEnter() {}
	virtual void CollisionStay() {}
	virtual void CollisionExit() {}

	//void GoToCell(Cell* cellEnd, Grid* grid);
	//void GoToCell(gce::Vector3f32 pos, Grid* grid);
	//void GoToNode(Node<Cell>* endNode, Grid* grid);
	//void GoToNode(Node<Cell>* startNode, Node<Cell>* endNode, Grid* grid);


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
			//startNode = GetNode<Cell>(GetPosition(), grid);
		}

		GoToNode(startNode, endNode, grid);
	}

	void GoToNode(Node<Cell>* startNode, Node<Cell>* endNode, Grid* grid)
	{
		//SetStartNode(startNode);
		//SetEndNode(endNode);
		mPathFinding.Find(startNode, endNode, grid, this);
	}

END_SCRIPT

