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
	gce::Vector3f32 mOffsetOfGrid;

public:
	ScriptCharacter* mCharacter;

	virtual void Initia() { mCharacter = m_pOwner->AddScript<ScriptCharacter>(); mCharacter->Initia(); SetPathFinding(PathFinding<Cell>()); mPathFinding.SetGrid(nullptr); SetOffsetOfGrid(gce::Vector3f32(0.f, 1.f, 0.f)); }
	virtual void Start() { SetPaths(Queue_<Cell, ComparePath<Cell>>());  }
	virtual void Update() { UpdatePath(); }
	virtual void Destroy() {}

	virtual void CollisionEnter(gce::GameObject* other) {}
	virtual void CollisionStay(gce::GameObject* other) {}
	virtual void CollisionExit(gce::GameObject* other) {}

	void UpdatePath()
	{
		Queue_<Cell, ComparePath<Cell>>* paths = GetPaths();
		if (paths->IsEmpty())
		{
			return;
		}

		if (mCharacter->GetTarget().isSet == true)
		{
			return;
		}

		Node<Cell>* currentNode = paths->Top();
		paths->Pop();

		gce::Vector3f32 positionCurrenteCell = mPathFinding.GetGrid()->GetPosOfCell(currentNode->GetData());
		mCharacter->GoToPosition(gce::Vector3f32(positionCurrenteCell.x, positionCurrenteCell.y + GetOffsetOfGrid().y, positionCurrenteCell.z), mCharacter->GetSpeed());


	}

	bool GoToCell(Cell* cellEnd)
	{
		ScriptGrid* grid = mPathFinding.GetGrid();
		Node<Cell>* endNode = grid->GetNode(cellEnd);
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

	void SetOffsetOfGrid(gce::Vector3f32 offsetOfGrid) { mOffsetOfGrid = offsetOfGrid; }
	gce::Vector3f32 GetOffsetOfGrid() { return mOffsetOfGrid; }

	void SetPathFinding(PathFinding<Cell> pathFinding) { mPathFinding = pathFinding; }
	PathFinding<Cell>* GetPathFinding() { return &mPathFinding; }

	void SetPaths(Queue_<Cell, ComparePath<Cell>> path) { mPathFinding.SetPaths(path); }
	Queue_<Cell, ComparePath<Cell>>* GetPaths() { return mPathFinding.GetPaths(); }

	void SetWorldPosition(gce::Vector3f32 position) { mCharacter->mEntity->SetWorldPosition(position); }
	gce::Vector3f32 GetWorldPosition() { return mCharacter->mEntity->GetWorldPosition(); }
	void WorldTranslate(gce::Vector3f32 position) { mCharacter->mEntity->WorldTranslate(position); }

	int GetLife()
	{
		return mCharacter->GetLife();
	}

END_SCRIPT

