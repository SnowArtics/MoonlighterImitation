#include "MazeMaker.h"
#include <random>
#include <algorithm>

MazeMaker::MazeMaker()
	: arr()
	, dirArr()
	, startPos{ 0,0 }
	, currentPos{0,0}
{

}

MazeMaker::~MazeMaker() 
{

}

void MazeMaker::BackTracking(int row, int column)
{
	std::vector<std::vector<int>>& arr = MazeMaker::GetInst()->GetArr();

	for (int i = 0; i < row; i++) {
		std::vector<int> Iarr;
		std::vector<int> Darr;
		for (int j = 0; j < column; j++) {
			Iarr.push_back(-1);
			Darr.push_back(0);
		}
		arr.push_back(Iarr);
		dirArr.push_back(Darr);
	}

	CellRandomSelect((row<column)?row:column);
	MazeProcess();
}

void MazeMaker::CellRandomSelect(int range)
{
	std::random_device rd;

	std::mt19937 gen(rd());

	std::uniform_int_distribution<int> dis(0, range-1);

	currentPos = std::make_pair<int, int>(dis(gen), dis(gen));
	startPos = currentPos;
}

void MazeMaker::MazeProcess()
{
	//if (!CellSearch()) {
	//	MoveToPreviousCell();
	//}
	//else {
	//	MoveToMerge();
	//}

	CellSearch(currentPos.second, currentPos.first);
}

bool MazeMaker::CellSearch(int x, int y)
{
	std::vector<int> moveDirection;
	moveDirection.push_back(1);
	moveDirection.push_back(2);
	moveDirection.push_back(3);
	moveDirection.push_back(4);

	std::shuffle(moveDirection.begin(), moveDirection.end(), std::default_random_engine());

	if (y > -1 && y<arr.size() && x>-1 && x<arr[0].size() && arr[y][x] == -1) {
		arr[y][x] = 0;
		for (int i = 0; i < 4; i++) {
			switch (moveDirection[i])
			{
			case 1:
				if (CellSearch(x, y + 1)) {
					dirArr[y][x] += DIRDOWN;
					dirArr[y + 1][x] += DIRUP;
				}
				break;
			case 2:
				if (CellSearch(x, y - 1)) {
					dirArr[y][x] += DIRUP;
					dirArr[y - 1][x] += DIRDOWN;
				}
				break;
			case 3:
				if (CellSearch(x - 1, y)) {
					dirArr[y][x] += DIRLEFT;
					dirArr[y][x - 1] += DIRRIGHT;
				}
				break;
			case 4:
				if (CellSearch(x + 1, y)) {
					dirArr[y][x] += DIRRIGHT;
					dirArr[y][x + 1] += DIRLEFT;
				}
				break;
			default:
				break;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

void MazeMaker::MoveToMerge()
{
}

void MazeMaker::MoveToPreviousCell()
{
}

void MazeMaker::Init()
{
	std::vector<std::vector<int>>& arr = MazeMaker::GetInst()->GetArr();
	arr.clear();
	arr.shrink_to_fit();

	dirArr.clear();
	dirArr.shrink_to_fit();

	currentPos = std::make_pair<int, int>(0, 0);
	startPos = std::make_pair<int, int>(0, 0);
}
