#include "PathFinding.h"

#include "Queue.hpp"
#include "Compare.h"
#include "Grid.hpp"
#include "Node.h"
#include "Agent.hpp"



/*template<typename T>
inline Queue_<T, ComparePath<T>>* PathFinding<T>::GetPaths()
{
	if (mPath.Size() > 0) { return &mPath; }
	else { mPath.Clear(); return &mPath; }
}

template<typename T>
PathFinding<T>::~PathFinding()
{
	mPath.Clear();
}


template<typename T>
inline void PathFinding<T>::FindPath(Node<T>* startNode, Node<T>* endNode, Grid* grid, Queue_<T, ComparePath<T>>, ScriptAgent* owner)
{
	ResetNodes<T>();
	Queue<Node<T>> queue;
	startNode->SetDisStart(0.f);
	startNode->SetDisEnd(Utils::DisManhattan(startNode->GetData()->GetPosition(), endNode->GetData()->GetPosition()));
	queue.push(startNode);

	while (queue.empty() == false)
	{
		Node<T>* nodeCurrent = queue.Top();
		queue.Pop();

		T* currentNodeData = nodeCurrent->GetData();

		Agent* currentNodeAgent = currentNodeData->GetAgent();

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
		}

		if (nodeCurrent->GetVisited() == true)
		{
			continue;
		}

		if (nodeCurrent == endNode)
		{
			CreatePath(false, startNode, endNode, allFormerPaths);
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
				nodeN->SetDisEnd(Utils::DisManhattan(nodeN->GetData()->GetPosition(), endPosition));
				nodeN->SetCallMe(nodeCurrent);

				queue.push(nodeN);
			}
		}
	}

	allFormerPaths->Clear();
}


/*template<typename T>
void PathFinding<T>::CreatePath(bool isfinish, Node<T>* startNode, Node<T>* endNode, std::vector<Node<T>*>* allFormerPaths)
{
	std::vector<Node<T>*> allPathEnds = std::vector<Node<T>*>();
	while (endNode != startNode)
	{
		allPathEnds.push_back(endNode);
		endNode = endNode->GetCallMe();
	}

	std::vector<Node<T>*>* allPathStarts = allFormerPaths;
	if (isfinish)
	{
		*allPathStarts = std::vector<Node<T>*>();
	}

	int lenghtAllPathEnds = allPathEnds.size() - 1;
	for (int i = lenghtAllPathEnds; i > -1; i--)
	{
		allPathStarts->push_back(allPathEnds[i]);
	}
}

template<typename T>
void PathFinding<T>::ResetNodes(Grid* grid)
{
	std::vector<Node<T>*> allNodes = grid->GetAllNodes();
	int lenght = allNodes.size();
	for (int i = 0; i < lenght; i++)
	{
		allNodes[i]->SetDisStart(INT_MAX);
		allNodes[i]->SetVisited(false);
		allNodes[i]->SetCallMe(nullptr);
	}
}*/


