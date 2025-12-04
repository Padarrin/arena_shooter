#pragma once
#include <vector>
#include <string>
#include <define.h>
#include <Maths/Vector2.hpp>

class Cell;
template<typename T>
class Node;

class MainScene;

class Grid
{
protected:
	int mCellSize;
	std::vector<Node<Cell>*> mAllNodes;
	std::vector<std::vector<Cell*>> mAllCells;

	gce::Vector2i32 mSizeTabCell;

	MainScene* mCurrentScene;
public:
	Grid() { Start(); }

	void Start();
	void InitTab();
	void InitTab(int _rows, int _cols);
	void InitNodeNeighbor();

	void CleanGrid();

	void Update();

	void SetSizeTabCell(gce::Vector2i32 sizeTabCell) { mSizeTabCell = sizeTabCell; }
	gce::Vector2i32 GetSizeTabCell() { return mSizeTabCell; }

	std::vector<std::vector<Cell*>>* GetAllCells() { return &mAllCells; }

	std::vector<Node<Cell>*>* GetAllNodes() { return &mAllNodes; }

	void SetMainScene(MainScene* currentScene) { mCurrentScene = currentScene; }
	MainScene* GetMainScene() { return mCurrentScene; }

protected:
	void CreateTab(int _rows, int _cols);
	void InitNodeNeighbor(int rows, int cols);

};