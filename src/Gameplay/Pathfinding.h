#pragma once
#include "Queue.hpp"
#include "Compare.h"
#include "Functions.h"

#include "Grid.hpp"
#include "Node.h"
#include "Agent.hpp"

template<typename T>
class Node;

class ScriptGrid;
class ScriptAgent;


template<typename T>
class PathFinding
{
protected:
	Queue_<T, ComparePath<T>> mPath;
	ScriptGrid* mGrid;
public:
	PathFinding() { Start(); }

	void Start() { SetPaths(Queue_<T, ComparePath<T>>()); SetGrid(nullptr);  }
	void Find(Node<T>* startNode, Node<T>* endNode, ScriptAgent* owner) { FindPath(startNode, endNode, GetPaths(), owner); }

	void SetPaths(Queue_<T, ComparePath<T>> path) { mPath = path; }
	void AddPaths(Queue_<T, ComparePath<T>> path) 
	{ 
		while (!path.IsEmpty())
		{
			Node<T>* node = path.Top();
			path.Pop();
			mPath.Push(node);
		}
	}
	Queue_<T, ComparePath<T>>* GetPaths()
	{
		if (mPath.Size() > 0) { return &mPath; }
		else { mPath.Clear(); return &mPath; }
	}

	void SetGrid(ScriptGrid* grid) { mGrid = grid; }
	ScriptGrid* GetGrid() { return mGrid; }

	~PathFinding()
	{
		mPath.Clear();
	}

protected:
	void FindPath(Node<T>* startNode, Node<T>* endNode, Queue_<T, ComparePath<T>>* allFormerPaths, ScriptAgent* owner)
	{
		ResetNodes();
		int cellSize = mGrid->GetCellSize();

		Queue_<T, CompareASTAR<T>> queue;
		startNode->SetDisStart(0.f);
		startNode->SetDisEnd(DisManhattan({100.f, 10.f, 1.f}, { 100.f, 1.f, 1.f }, 10));//mGrid->GetPosOfCell(startNode->GetData()), mGrid->GetPosOfCell(endNode->GetData()), cellSize
		queue.Push(startNode);

		while (queue.IsEmpty() == false)
		{
			Node<T>* nodeCurrent = queue.Top();
			queue.Pop();

			T* currentNodeData = nodeCurrent->GetData();

			if (nodeCurrent->GetVisited() == true)
			{
				continue;
			}

			if (nodeCurrent == endNode)
			{
				Queue_<T, ComparePath<T>> path = Queue_<T, ComparePath<T>>();
				while (endNode != startNode)
				{
					path.Push(endNode);
					endNode = endNode->GetCallMe();
				}
				path.Swap(path);
				AddPaths(path);
				return;
			}

			nodeCurrent->SetVisited(true);

			gce::Vector3f32 endPosition = mGrid->GetPosOfCell(endNode->GetData());

			for (NeighborsCost<T>& nodeNC : nodeCurrent->GetNeighborsCost())
			{
				Node<T>* nodeN = nodeNC.GetNeighbor();

				T* tNeighbor = nodeN->GetData();

				float minimalDist = nodeCurrent->GetDisStart() + nodeNC.GetCost();

				if (minimalDist < nodeN->GetDisStart())
				{
					nodeN->SetDisStart(minimalDist);
					nodeN->SetDisEnd(DisManhattan(mGrid->GetPosOfCell(nodeN->GetData()), endPosition, cellSize));
					nodeN->SetCallMe(nodeCurrent);

					queue.Push(nodeN);
				}
			}
		}

		allFormerPaths->Clear();
	}

	void ResetNodes()
	{
		std::vector<Node<T>*>* allNodes = mGrid->GetAllNodes();
		int lenght = allNodes->size();
		for (int i = 0; i < lenght; i++)
		{
			Node<T>* node = (*allNodes)[i];
			node->SetDisStart(INT_MAX);
			node->SetVisited(false);
			node->SetCallMe(nullptr);
		}
	}	
};
