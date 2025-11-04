#include "BidCell.h"
#include "../saelib2d/Frame.h"
#include "random"
#include "iostream"

BidCell::BidCell(CFrame& mframe)
	: frame{ mframe }
{
}

void BidCell::SetUp()
{
	for (int i = 0; i < 202; i++) {
		std::vector<bool> cols(202, false);
		vAutoCell.push_back(cols);
	}
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<unsigned int>dist(1, 201);

	bool bina = false;
	for (unsigned int i = 0; i < 512; i++)
	{
		unsigned int row = dist(mt);
		unsigned int col = dist(mt);
		if (bina) {
			if (col > 198) { col = 198; }
			vAutoCell[col][row] = true;
			vAutoCell[col + 1][row] = true;
			vAutoCell[col + 2][row] = true;
			bina = false;
		}
		else {
			if (row > 198) { row = 198; }
			vAutoCell[col][row] = true;
			vAutoCell[col][row + 1] = true;
			vAutoCell[col][row + 2] = true;
			bina = true;
		}
	}

}

void BidCell::DrawBorder()
{
	frame.drawLine(60, 20, 260, 20, sRGB{ 200,0,0 });
	frame.drawLine(60, 220, 260, 220, sRGB{ 200,0,0 });
	frame.drawLine(60, 20, 60, 220, sRGB{ 200,0,0 });
	frame.drawLine(260, 20, 260, 220, sRGB{ 200,0,0 });
}

void BidCell::DrawAll()
{
	for (int row = 1; row < 201; row++) {
		for (int col = 1; col < 201; col++)
		{
			if (vAutoCell[col][row]) {
				frame.putPixel(col + 60, row + 20, sRGB{ 0,222,0 });
			}
		}
	}
}

bool BidCell::CheckRules(std::vector<bool> reglas, bool isAlive)
{
	int value = 0;
	for (int i = 0; i < reglas.size(); i++)
	{
		if (reglas[i] == true)
			value++;
	}
	if (isAlive)
	{
		if (value <= 1) return false;
		if (value >= 4) return false;
		if (value == 2 || value == 3) return true;
	}
	else
	{
		if (value == 3) return true;
	}
	return false;
}

void BidCell::Update()
{
	std::vector<std::vector<bool>> newCells = vAutoCell;

	for (int row = 1; row < 201-1; row++)
	{
		for (int col = 1; col < 201-1; col++)
		{
			reglas.clear();
			reglas.push_back(vAutoCell[row - 1][col]); // Arriba
			reglas.push_back(vAutoCell[row + 1][col]); // Abajo
			reglas.push_back(vAutoCell[row][col - 1]); // Izquierda
			reglas.push_back(vAutoCell[row][col + 1]); // Derecha
			reglas.push_back(vAutoCell[row + 1][col + 1]); // Abajo-Derecha
			reglas.push_back(vAutoCell[row + 1][col - 1]); // Abajo-Izquierda
			reglas.push_back(vAutoCell[row - 1][col - 1]); // Arriba-Izquierda
			reglas.push_back(vAutoCell[row - 1][col + 1]); // Arriba-Derecha

			newCells[row][col] = CheckRules(reglas, vAutoCell[row][col]);
		}
	}

	vAutoCell = newCells;
}
