
#include "Grid.h"

#include <define.h>
#include <Maths/Vector2.hpp>

#include "Functions.h"
#include "Node.h"

#include <iostream>
#include <fstream>
#include <string>

void Grid::Start()
{
	int mCellSize = 50;
	std::vector<Node<Cell>*> mAllNodes;
	std::vector<std::vector<Cell*>> mAllCells;

	gce::Vector2i32 mSizeTabCell = gce::Vector2i32(-1,-1);

	MainScene* mCurrentScene;
}

void Grid::InitTab(int _rows, int _cols)
{
	CleanGrid();
	CreateTab(_rows, _cols);
	InitNodeNeighbor(_rows, _cols);
}

void Grid::InitTab()
{
	//std::string strGrid = GetStringFromTxt(fileName);

	//if (strGrid.empty())
	//{
	//	std::cout << "error : file can't be found or read !\n";
	//	return;
	//}

	gce::Vector2i32 size = GetSizeTabCell();
	InitTab(size.x, size.y);
}

void Grid::CreateTab(int _rows, int _cols)
{
	int count = 0;
	float cellSize = (float)mCellSize;
	float space = 5.f;

	for (int r = 0; r < _rows; r++)
	{
		std::vector<Cell*> current;

		for (int c = 0; c < _cols; c++)
		{
			//gce::Vector3f32 setCellPos = gce::Vector3f32(c * (cellSize + space), MIN_HEIGHT, -r * (cellSize + space));
			int setHeight = 1;
			bool isInacessible = false;
			GameObject* haveObject = nullptr;

			Cell* cell = new Cell();
			cell->SetAll(setHeight, gce::Vector2i32(r,c), isInacessible, haveObject);

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

void Grid::InitNodeNeighbor()
{
	InitNodeNeighbor(mSizeTabCell.x, mSizeTabCell.y);
}

void Grid::InitNodeNeighbor(int _rows, int _cols)
{
	for (int r = 0; r < _rows; r++)
	{
		for (int c = 0; c < _cols; c++)
		{
			Node<Cell>* node = GetNodeInTab(r, c, _cols, &mAllNodes);

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
				Node<Cell>* nodeNeighbor = GetNodeInTab<Cell>(r, c - 1, _cols, &mAllNodes);
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
				Node<Cell>* nodeNeighbor = GetNodeInTab(r - 1, c, _cols, &mAllNodes);
				int neighBorCellHeight = nodeNeighbor->GetData()->GetConfigHeight();

				diffLeftHeight = calculateDiffHeight(currentCellHeight, neighBorCellHeight);

				if (nodeNeighbor->GetData()->GetIsInaccessible() == false && diffLeftHeight < nbFloor)
				{
					tabNodeCost.push_back(NeighborsCost<Cell>(nodeNeighbor, r1 + diffLeftHeight));
					left = true;
				}
			}
			if (r != _rows - 1)
			{
				//->
				Node<Cell>* nodeNeighbor = GetNodeInTab(r + 1, c, _cols, &mAllNodes);
				int neighBorCellHeight = nodeNeighbor->GetData()->GetConfigHeight();

				diffRightHeight = calculateDiffHeight(currentCellHeight, neighBorCellHeight);

				if (nodeNeighbor->GetData()->GetIsInaccessible() == false && diffRightHeight < nbFloor)
				{
					tabNodeCost.push_back(NeighborsCost<Cell>(nodeNeighbor, r1 + diffRightHeight));
					right = true;
				}
			}
			if (c != _cols - 1)
			{
				//!
				Node<Cell>* nodeNeighbor = GetNodeInTab(r, c + 1, _cols, &mAllNodes);
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
						Node<Cell>* nodeNeighbor = GetNodeInTab(r - 1, c - 1, _cols, &mAllNodes);
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
					if (r != _rows - 1 && c != 0)
					{
						Node<Cell>* nodeNeighbor = GetNodeInTab(r + 1, c - 1, _cols, &mAllNodes);
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
					if (r != 0 && c != _cols - 1)
					{
						Node<Cell>* nodeNeighbor = GetNodeInTab(r - 1, c + 1, _cols, &mAllNodes);
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
					if (r != _rows - 1 && c != _cols - 1)
					{
						Node<Cell>* nodeNeighbor = GetNodeInTab(r + 1, c + 1, _cols, &mAllNodes);
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

void Grid::CleanGrid()
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

void Grid::Update()
{
	//UpdateCellsStatut();
	//DrawGrid();
}

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
