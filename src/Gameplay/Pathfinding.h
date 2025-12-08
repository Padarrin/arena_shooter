#pragma once
#include "Queue.hpp"
#include "Compare.h"
#include "Functions.h"

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
			Node<T*> node = path.Top();
			path.Pop();
			mPath.Puch(node);
		}
	}
	Queue_<T, ComparePath<T>>* GetPaths();

	void SetGrid(ScriptGrid* grid) { mGrid = grid; }
	ScriptGrid* GetGrid() { return mGrid; }

	~PathFinding()
	{
		mPath.Clear();
	}
protected:
	void FindPath(Node<T>* startNode, Node<T>* endNode, Queue_<T, ComparePath<T>>* allFormerPaths, ScriptAgent* owner);
	void ResetNodes();

#include "Grid.hpp"
#include "Node.h"
#include "Agent.hpp"

	template<typename T>
	inline Queue_<T, ComparePath<T>>* GetPaths()
	{
		if (mPath.Size() > 0) { return &mPath; }
		else { mPath.Clear(); return &mPath; }
	}


	template<typename T>
	inline void FindPath(Node<T>* startNode, Node<T>* endNode, Queue_<T, ComparePath<T>>* allFormerPaths, ScriptAgent* owner)
	{
		ResetNodes<T>();
		Queue<Node<T>> queue;
		startNode->SetDisStart(0.f);
		startNode->SetDisEnd(DisManhattan(startNode->GetData()->GetPosition(), endNode->GetData()->GetPosition()));
		queue.push(startNode);

		while (queue.empty() == false)
		{
			Node<T>* nodeCurrent = queue.Top();
			queue.Pop();

			T* currentNodeData = nodeCurrent->GetData();

			/*ScriptAgent* currentNodeAgent = currentNodeData->GetHaveObject();

			if (currentNodeData->HasAgent() == true && currentNodeAgent != owner) // Ignore if agent and not owner
			{
				if (owner->IsGhost() && currentNodeAgent->IsGhost() == false)
				{
					// Allowed to pass through it
				}
				else
				{
					continue;
				}
			}*/

			if (nodeCurrent->GetVisited() == true)
			{
				continue;
			}

			if (nodeCurrent == endNode)
			{
				Queue_<T, ComparePath<T>> path = Queue_<T, ComparePath<T>>();
				while (endNode != startNode)
				{
					path.push_back(endNode);
					endNode = endNode->GetCallMe();
				}
				path.Swap();
				AddPaths(path);
				return;
			}

			nodeCurrent->SetVisited(true);

			gce::Vector3f32 endPosition = endNode->GetData()->GetPosition();

			for (NeighborsCost<T>& nodeNC : nodeCurrent->GetNeighborsCost())
			{
				Node<T>* nodeN = nodeNC.GetNeighbor();

				T* tNeighbor = nodeN->GetData();

				float minimalDist = nodeCurrent->GetDisStart() + nodeNC.GetCost();

				if (minimalDist < nodeN->GetDisStart())
				{
					nodeN->SetDisStart(minimalDist);
					nodeN->SetDisEnd(DisManhattan(nodeN->GetData()->GetPosition(), endPosition));
					nodeN->SetCallMe(nodeCurrent);

					queue.push(nodeN);
				}
			}
		}

		allFormerPaths->Clear();
	}

	template<typename T>
	void ResetNodes()
	{
		std::vector<Node<T>*> allNodes = mGrid->GetAllNodes();
		int lenght = allNodes.size();
		for (int i = 0; i < lenght; i++)
		{
			allNodes[i]->SetDisStart(INT_MAX);
			allNodes[i]->SetVisited(false);
			allNodes[i]->SetCallMe(nullptr);
		}
	}
};

//#include "PathFinding.inl"
//#include "Queue.hpp"
//#include "Compare.h"
