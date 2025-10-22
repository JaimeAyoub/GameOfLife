#include "UniCell.h"
#include "../saelib2d/Frame.h"

bool CelulaRules(bool a, bool b, bool c)
{
	if (a && b && c) { return false; }
	if (a && b && !c) { return false; }
	if (a && !b && c) { return false; }
	if (a && !b && !c) { return true; }
	if (!a && b && c) { return true; }
	if (!a && b && !c) { return true; }
	if (!a && !b && c) { return true; }
	if (!a && !b && !c) { return false; }

	return false;



}


UniCell::UniCell(CFrame& mframe)
	: frame{ mframe }
{
}

void UniCell::Setup()
{
	for (int i = 0; i < 200; i++) {
		std::vector<bool> cols(202, false);
		vAutoCell.push_back(cols);
	}
	vAutoCell[0][101] = true;
	vOnCells.push_back(std::make_pair(0, 101));
	

	for (int row = 0; row < 199; row++) {
		for (int col = 0; col < 200; col++) {
			bool la = vAutoCell[row][col];
			bool lb = vAutoCell[row][col + 1];
			bool lc =  vAutoCell[row][col + 2];
			bool rule = CelulaRules(la, lb, lc);
			vAutoCell[row + 1][col + 1] = rule;
			if (rule) {
				vOnCells.push_back(std::make_pair(row + 1, col + 1));
			}

		}
	}
}

void UniCell::Draw()
{
	frame.drawLine(60, 20, 260, 20, sRGB{ 200,0,0 });
	frame.drawLine(60, 220, 260, 220, sRGB{ 200,0,0 });
	frame.drawLine(60, 20, 60, 220, sRGB{ 200,0,0 });
	frame.drawLine(260, 20, 260, 220, sRGB{ 200,0,0 });

	if (isCellOn) {
		for (int idx = 0; idx < maxCell; idx++) {
			auto cello = vOnCells[idx];
			frame.putPixel(cello.second + 60, cello.first + 20, sRGB{ 0,255,0 });
		}
		maxCell++;
		if (maxCell > vOnCells.size()) {
			isCellOn = false;
		}
	}

}
