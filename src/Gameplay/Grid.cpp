#include "Grid.h"

#include <define.h>
#include <Maths/Vector2.hpp>

#include "Functions.h"
#include "Cell.h"
#include "Node.h"

#include <iostream>
#include <fstream>
#include <string>



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
