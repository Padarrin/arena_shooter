#pragma once
#include <vector>
#include <string>
#include <define.h>
#include <Maths/Vector2.hpp>
#include <GameObject.h>

#include "Node.h"
#include "Functions.h"

class Cell;
//template<typename T>
//class Node;

DECLARE_SCRIPT(ScriptGrid, ScriptFlag::Start | ScriptFlag::Update | ScriptFlag::Destroy)
protected:
	std::vector<Node<Cell>*> mAllNodes;
	std::vector<std::vector<Cell*>> mAllCells;

	int mCellSize;
	//gce::Vector2i32 mSizeTabCell;

	//position au bord de la fin de la grid 
	/*
		  -z
	-x	center  x
		   z
	*/
	//gce::Vector2f32 mUtmostPositionOnX; // -x, centrer, x
	//gce::Vector2f32 mUtmostPositionOnZ; // -z, centrer, z
public:
	virtual void Initia()
	{
		std::vector<Node<Cell>*> mAllNodes;
		std::vector<std::vector<Cell*>> mAllCells;

		mCellSize = 1;

		SetCenterOfGrid(gce::Vector3f32(0.f, 0.f, 0.f));
	}
	virtual void Start()
	{

	}
	virtual void Update() 
	{
	}
	virtual void Destroy() {}

	void InitTab() { InitTab(GetSizeTabCell()); }
	void InitTab(gce::Vector2i32 rowsCols)
	{
		CleanGrid();
		CreateTab(rowsCols);
		InitNodeNeighbor(rowsCols);
	}
	void InitNodeNeighbor() { InitNodeNeighbor(GetSizeTabCell()); }

	void CleanGrid()
	{
		for (auto it = mAllCells.begin(); it != mAllCells.end(); ++it)
		{
			for (auto it2 = it->begin(); it2 != it->end(); ++it2)
			{
				delete (*it2);
			}
		}

		for (auto& row : mAllCells)
		{
			row.clear();
		}
		mAllCells.clear();


		for (auto it = mAllNodes.begin(); it != mAllNodes.end(); ++it)
		{
			delete* it;
		}
		mAllNodes.clear();
	}

	// SetScale et lance InitTab
	void SetSizeTabCell(gce::Vector2i32 sizeTabCell) { m_pOwner->transform.SetWorldScale(gce::Vector3f32((float)sizeTabCell.x * mCellSize, 0.1f, (float)sizeTabCell.y * mCellSize)); InitTab(sizeTabCell); }
	gce::Vector2i32 GetSizeTabCell() { return gce::Vector2i32(mAllCells.size(), mAllCells[0].size()); }

	std::vector<std::vector<Cell*>>* GetAllCells() { return &mAllCells; }
	std::vector<Node<Cell>*>* GetAllNodes() { return &mAllNodes; }

	void SetCellSize(int cellSize) { mCellSize = cellSize; }
	int GetCellSize() { return mCellSize; }

	//void SetUtmostPositionX(gce::Vector2f32 utmostPosX) { mUtmostPositionOnX = utmostPosX; }
	//gce::Vector2f32 GetUtmostPositionX() { return mUtmostPositionOnX; }
	//void SetUtmostPositionZ(gce::Vector2f32 utmostPosZ) { mUtmostPositionOnZ = utmostPosZ; }
	//gce::Vector2f32 GetUtmostPositionZ() { return mUtmostPositionOnZ; }

	//void SetUtmostPosition(gce::Vector4 utmostPosXZ) { mUtmostPositionOnX = gce::Vector2f32(utmostPosXZ.GetX(), utmostPosXZ.GetY()); mUtmostPositionOnZ = gce::Vector2f32(utmostPosXZ.GetZ(), utmostPosXZ.GetW()); }
	//gce::Vector4 GetUtmostPosition() { return gce::Vector4(mUtmostPositionOnX.x, mUtmostPositionOnX.y, mUtmostPositionOnZ.x, mUtmostPositionOnZ.y); }

	void SetCenterOfGrid(gce::Vector3f32 position) 
	{ 
		//gce::Vector2f32 halfRowsCols = ((gce::Vector2f32)mSizeTabCell) * 0.5f;
		//gce::Vector2f32 moreLess = halfRowsCols * ((float)mCellSize);
		//mUtmostPositionOnX = gce::Vector2f32(position.x - moreLess.x, position.x + moreLess.x);
		//mUtmostPositionOnZ = gce::Vector2f32(position.z - moreLess.y, position.z + moreLess.y);
		m_pOwner->transform.SetWorldPosition(position);
	}
	gce::Vector3f32 GetCenterOfGrid() { return m_pOwner->transform.GetWorldPosition(); } //return gce::Vector2f32((mUtmostPositionOnX.x + mUtmostPositionOnX.y) * 0.5f, (mUtmostPositionOnZ.x + mUtmostPositionOnZ.y) * 0.5f); }

	void SetPosOfIndex00(gce::Vector3f32 position)
	{
		//gce::Vector2f32 moreLess = ((gce::Vector2f32)GetSizeTabCell()) * ((float)mCellSize);
		//mUtmostPositionOnX = gce::Vector2f32(xZ.x, xZ.x + moreLess.x);
		//mUtmostPositionOnZ = gce::Vector2f32(xZ.y - moreLess.y, xZ.y);
		gce::Vector2f32 halfRowsCols = ((gce::Vector2f32)GetSizeTabCell()) * 0.5f;
		gce::Vector2f32 moreLess = halfRowsCols * ((float)mCellSize);
		SetCenterOfGrid(gce::Vector3f32(position.x + moreLess.x, position.y, position.z + moreLess.y));
	}
	//Get TopLeft Pos
	gce::Vector3f32 GetPosOfIndex00() 
	{
		gce::Vector2f32 halfRowsCols = ((gce::Vector2f32)GetSizeTabCell()) * 0.5f;
		gce::Vector2f32 moreLess = halfRowsCols * ((float)mCellSize);
		gce::Vector3f32 position = GetCenterOfGrid();
		return gce::Vector3f32(position.x - moreLess.x, position.y, position.z - moreLess.y);
	}

	gce::Vector3f32 GetPosOfCell(Cell* cell) 
	{
		gce::Vector2f32 index = (gce::Vector2f32)cell->GetRowCol();
		gce::Vector3f32 addPos = gce::Vector3f32(index.x * ((float)mCellSize), 0.f, index.y * ((float)mCellSize));
		return GetPosOfIndex00() + addPos;
	}

	gce::Vector3f32 GetPosOfCell(gce::Vector2f32 index)
	{
		gce::Vector3f32 addPos = gce::Vector3f32(index.x * ((float)mCellSize), 0.f, index.y * ((float)mCellSize));
		return GetPosOfIndex00() + addPos;
	}

	Cell* GetCell(gce::Vector3f32 pos)
	{
		Cell* nearest = GetNearestCell(pos);
		if (nearest != nullptr)
		{
			return nearest;
		}
		return nullptr;
	}

	Node<Cell>* GetNode(gce::Vector3f32 pos) 
	{
		Cell* cell = GetCell(pos);
		if (cell != nullptr)
		{
			return GetNode(cell);
		}
		return nullptr;
	}
	Node<Cell>* GetNode(Cell* cell) 
	{ 
		if (cell != nullptr)
		{
			return GetNodeInTab(cell->GetRowCol(), GetSizeTabCell().y);
		}
		return nullptr;
	}

	Node<Cell>* GetNodeInTab(gce::Vector2i32 rowCol, int lengthCol, std::vector<Node<Cell>*>* allNodes) 
	{ 
		int index = rowCol.x * lengthCol + rowCol.y;
		if (index < allNodes->size())
		{
			return (*allNodes)[index];
		}
		return nullptr;
	}
	Node<Cell>* GetNodeInTab(int row, int col, int lengthCol, std::vector<Node<Cell>*>* allNodes) 
	{ 
		int index = row * lengthCol + col;
		if (index < allNodes->size())
		{
			return (*allNodes)[index];
		}
		return nullptr;
	}
	Node<Cell>* GetNodeInTab(gce::Vector2i32 rowCol, int lengthCol) 
	{ 
		int index = rowCol.x * lengthCol + rowCol.y;
		if (index < mAllNodes.size())
		{
			return mAllNodes[index];
		}
		return nullptr;
	}
	Node<Cell>* GetNodeInTab(int row, int col, int lengthCol) 
	{ 
		int index = row * lengthCol + col;
		if (index < mAllNodes.size())
		{
			return mAllNodes[index];
		}
		return nullptr;
	}

	Cell* GetNearestCell(gce::Vector3f32 pos)
	{
		gce::Vector3f32 diffPos = pos - GetPosOfIndex00();
		gce::Vector2i32 index = gce::Vector2i32(diffPos.x / ((float)mCellSize), diffPos.z / ((float)mCellSize));
		if (index.x < -1 || index.y < -1)
		{
			return nullptr;
		}

		//std::vector<std::vector<Cell*>>* allCells = GetAllCells();
		int lenghtRows = mAllCells.size();
		int lenghtCols = mAllCells[0].size();
		if (index.x > lenghtRows - 1 || index.y > lenghtCols - 1)
		{
			return nullptr;
		}

		return mAllCells[index.x][index.y];
	}

protected:
	void CreateTab(gce::Vector2i32 rowsCols)
	{
		int count = 0;
		//float cellSize = (float)mCellSize;
		//float space = 5.f;

		for (int r = 0; r < rowsCols.x; r++)
		{
			std::vector<Cell*> current;
			for (int c = 0; c < rowsCols.y; c++)
			{
				//gce::Vector3f32 setCellPos = gce::Vector3f32(c * (cellSize + space), MIN_HEIGHT, -r * (cellSize + space));
				int setHeight = 1;
				bool isInacessible = false;
				gce::GameObject* haveObject = nullptr;

				Cell* cell = new Cell();
				cell->SetAll(setHeight, gce::Vector2i32(r, c), isInacessible, haveObject);

				current.push_back(cell);


				Node<Cell>* node = new Node<Cell>();
				bool visited = false;
				Node<Cell>* callMe = nullptr;
				std::vector<NeighborsCost<Cell>> neighbors = std::vector<NeighborsCost<Cell>>();
				int disStart = 0;
				int disEnd = 0;
				node->SetAll(cell, visited, callMe, neighbors, disStart, disEnd);
				mAllNodes.push_back(node);
			}

			mAllCells.push_back(current);
		}

	}
	void InitNodeNeighbor(gce::Vector2i32 rowsCols)
	{
		for (int r = 0; r < rowsCols.x; r++)
		{
			for (int c = 0; c < rowsCols.y; c++)
			{
				Node<Cell>* node = GetNodeInTab(r, c, rowsCols.y);

				std::vector<NeighborsCost<Cell>>& tabNodeCost = node->GetNeighborsCost();
				tabNodeCost.clear();

				if (node->GetData()->GetIsInaccessible() == true)
				{
					continue;
				}

				bool right = false;
				int diffRightHeight = 0;

				bool left = false;
				int diffLeftHeight = 0;

				bool up = false;
				int diffUpHeight = 0;

				bool down = false;
				int diffDownHeight = 0;


				float r1 = 1;
				float r2 = RACINE;

				float nbFloor = 2;

				int currentCellHeight = node->GetData()->GetConfigHeight();

				auto calculateDiffHeight = [](int currentH, int neighborH) -> int
					{
						return abs(neighborH - currentH);
					};

				if (c != 0)
				{
					//î
					Node<Cell>* nodeNeighbor = GetNodeInTab(r, c - 1, rowsCols.y);
					int neighBorCellHeight = nodeNeighbor->GetData()->GetConfigHeight();

					diffUpHeight = calculateDiffHeight(currentCellHeight, neighBorCellHeight);

					if (nodeNeighbor->GetData()->GetIsInaccessible() == false && diffUpHeight < nbFloor)
					{
						tabNodeCost.push_back(NeighborsCost<Cell>(nodeNeighbor, r1 + diffUpHeight));
						up = true;
					}
				}
				if (r != 0)
				{
					//<-
					Node<Cell>* nodeNeighbor = GetNodeInTab(r - 1, c, rowsCols.y);
					int neighBorCellHeight = nodeNeighbor->GetData()->GetConfigHeight();

					diffLeftHeight = calculateDiffHeight(currentCellHeight, neighBorCellHeight);

					if (nodeNeighbor->GetData()->GetIsInaccessible() == false && diffLeftHeight < nbFloor)
					{
						tabNodeCost.push_back(NeighborsCost<Cell>(nodeNeighbor, r1 + diffLeftHeight));
						left = true;
					}
				}
				if (r != rowsCols.x - 1)
				{
					//->
					Node<Cell>* nodeNeighbor = GetNodeInTab(r + 1, c, rowsCols.y);
					int neighBorCellHeight = nodeNeighbor->GetData()->GetConfigHeight();

					diffRightHeight = calculateDiffHeight(currentCellHeight, neighBorCellHeight);

					if (nodeNeighbor->GetData()->GetIsInaccessible() == false && diffRightHeight < nbFloor)
					{
						tabNodeCost.push_back(NeighborsCost<Cell>(nodeNeighbor, r1 + diffRightHeight));
						right = true;
					}
				}
				if (c != rowsCols.y - 1)
				{
					//!
					Node<Cell>* nodeNeighbor = GetNodeInTab(r, c + 1, rowsCols.y);
					int neighBorCellHeight = nodeNeighbor->GetData()->GetConfigHeight();

					diffDownHeight = calculateDiffHeight(currentCellHeight, neighBorCellHeight);

					if (nodeNeighbor->GetData()->GetIsInaccessible() == false && diffDownHeight < nbFloor)
					{
						tabNodeCost.push_back(NeighborsCost<Cell>(nodeNeighbor, r1 + diffDownHeight));
						down = true;
					}
				}


				if (up && diffUpHeight == 0)
				{
					if (left && diffLeftHeight == 0)
					{
						if (r != 0 && c != 0)
						{
							Node<Cell>* nodeNeighbor = GetNodeInTab(r - 1, c - 1, rowsCols.y);
							int neighBorCellHeight = nodeNeighbor->GetData()->GetConfigHeight();

							int diffUpLeftHeight = calculateDiffHeight(currentCellHeight, neighBorCellHeight);

							if (nodeNeighbor->GetData()->GetIsInaccessible() == false && diffUpLeftHeight == 0)
							{
								tabNodeCost.push_back(NeighborsCost<Cell>(nodeNeighbor, r2));
							}

						}
					}

					if (right && diffRightHeight == 0)
					{
						if (r != rowsCols.x - 1 && c != 0)
						{
							Node<Cell>* nodeNeighbor = GetNodeInTab(r + 1, c - 1, rowsCols.y);
							int neighBorCellHeight = nodeNeighbor->GetData()->GetConfigHeight();

							int diffUpRightHeight = calculateDiffHeight(currentCellHeight, neighBorCellHeight);

							if (nodeNeighbor->GetData()->GetIsInaccessible() == false && diffUpRightHeight == 0)
							{
								tabNodeCost.push_back(NeighborsCost<Cell>(nodeNeighbor, r2));
							}
						}
					}
				}

				if (down && diffDownHeight == 0)
				{
					if (left && diffLeftHeight == 0)
					{
						if (r != 0 && c != rowsCols.y - 1)
						{
							Node<Cell>* nodeNeighbor = GetNodeInTab(r - 1, c + 1, rowsCols.y);
							int neighBorCellHeight = nodeNeighbor->GetData()->GetConfigHeight();

							int diffDownLeftHeight = calculateDiffHeight(currentCellHeight, neighBorCellHeight);

							if (nodeNeighbor->GetData()->GetIsInaccessible() == false && diffDownLeftHeight == 0)
							{
								tabNodeCost.push_back(NeighborsCost<Cell>(nodeNeighbor, r2));
							}
						}
					}

					if (right && diffRightHeight == 0)
					{
						if (r != rowsCols.x - 1 && c != rowsCols.y - 1)
						{
							Node<Cell>* nodeNeighbor = GetNodeInTab(r + 1, c + 1, rowsCols.y);
							int neighBorCellHeight = nodeNeighbor->GetData()->GetConfigHeight();

							int diffDownRightHeight = calculateDiffHeight(currentCellHeight, neighBorCellHeight);

							if (nodeNeighbor->GetData()->GetIsInaccessible() == false && diffDownRightHeight == 0)
							{
								tabNodeCost.push_back(NeighborsCost<Cell>(nodeNeighbor, r2));
							}
						}
					}
				}
			}
		}
	}

END_SCRIPT

/*void Grid::SaveGrid(std::string fileName)
{
	std::ofstream file("../../res/Grids/" + fileName, std::ios::out);

	if (file.is_open() == false)
		return;

	for (int r = 0; r < pCurrentScene->GetGridRows(); r++)
	{
		for (int c = 0; c < pCurrentScene->GetGridCols(); c++)
		{
			Cell* currentCell = mAllCells[r][c];

			std::string toAdd = "0";

			int i = currentCell->GetConfigHeight();

			switch (i)
			{
			case 0:
				toAdd = "0";
				break;
			case 1:
				toAdd = "1";
				break;
			case 2:
				toAdd = "2";
				break;
			case 3:
				toAdd = "3";
				break;
			default:
				toAdd = "0";
				break;
			}

			file << toAdd + " ";
		}

		file << std::endl;
	}

	file.close();
}*/

/*std::string Grid::GetStringFromTxt(std::string fileName)
{
	std::string txtOutput;
	std::ifstream file("../../res/Grids/" + fileName);

	if (file.is_open() == false)
	{
		std::cerr << fileName + " can't be open !" << std::endl;
		return "";
	}

	std::string line;
	int rowsCount = 0;

	while (std::getline(file, line))
	{
		for (auto it = line.begin(); it != line.end();)
		{
			if (*it == ' ')
			{
				it = line.erase(it);
				continue;
			}
			else
			{
				++it;
			}
		}

		txtOutput += line;

		pCurrentScene->SetGridCols(line.size());

		rowsCount++;
	}

	pCurrentScene->SetGridRows(rowsCount);
	file.close();

	return txtOutput;
}*/

/*void Grid::UpdateCellsStatut()
{
	for (auto& row : mAllCells)
	{
		for (auto cell : row)
		{
			cell->CheckStatus(mCellSize);
		}
	}
}*/

/*void Grid::DrawGrid()
{
	DrawColorCell();
}*/

/*void Grid::DrawColorCell()
{
	gce::Vector3f32 red(1.f, 0.5f, 0.5f);
	gce::Vector3f32 grey(0.5f, 0.5f, 0.5f);
	gce::Vector3f32 whiteGreen(0.5f, 1.f, 0.5f); // White Green

	int rows = 0;
	int cols = 0;

	for (auto& row : mAllCells)
	{
		for (auto cell : row)
		{
			gce::Vector3f32 indicatorColor = cell->GetGeo()->GetDefaultColor();

			if (cell->HasAgent() == true)
			{
				indicatorColor = red;
				cell->GetGeo()->SetDefaultColor(whiteGreen);
			}
			else if (cell->IsObstacle() == true)
			{
				indicatorColor = grey;
			}

			cell->GetGeo()->SetColor(indicatorColor);

			cols++;
		}

		rows++;
		cols = 0;
	}
}*/

/*gce::Vector3f32 Grid::GetPositionToView(int rows, int cols, float coef)
{
	float height = cols;

	if (rows > cols)
	{
		height = rows;
	}

	return gce::Vector3f32((float)rows * coef * mCellSize, height * mCellSize * 0.9f, -(float)rows * coef * mCellSize);
}*/

/*void Grid::SetParameters(int cellSize, bool usingTxt)
{
	mCellSize = cellSize;

	int rows = pCurrentScene->GetGridRows();
	int cols = pCurrentScene->GetGridCols();

	if (usingTxt)
		InitTab(GridConfigs::GetConfigString());
	else
		InitTab(rows, cols);
}*/
