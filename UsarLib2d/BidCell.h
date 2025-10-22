#pragma once
#include <vector>
#include <array>

class CFrame;
class BidCell
{
public:
	BidCell(CFrame& mframe);
	~BidCell() = default;
	void SetUp();
	void DrawBorder();
	void DrawAll();
	bool CheckRules(std::array<bool, 8> reglas);
private:
	std::vector<std::vector<bool>> vAutoCell;
	std::vector<std::pair<int, int>> vOnCells;


	CFrame& frame;
};

