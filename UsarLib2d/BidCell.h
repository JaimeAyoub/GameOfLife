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
	bool CheckRules(std::vector<bool> reglas,bool isAlive);
	void Update();
private:
	std::vector<std::vector<bool>> vAutoCell;
	std::vector<std::pair<int, int>> vOnCells;
	std::vector<bool> reglas;


	CFrame& frame;
};

