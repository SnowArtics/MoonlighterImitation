#pragma once
#include "..\Engine_SOURCE\snScene.h"

namespace sn
{
	class Dungeon : public Scene
	{
	public:
		Dungeon();
		virtual ~Dungeon();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;
		virtual void OnEnter() override;
		virtual void OnExit() override;

	public:
		void SetPlayerMapPos(int x, int y) { playerMapPos.first = y, playerMapPos.second = x; }
		void SetPlayerMapPos(std::pair<int, int> _playerMapPos) { playerMapPos = _playerMapPos; }
		std::pair<int, int> GetPlayerMapPos() { return playerMapPos; }

	private:
		std::pair<int, int>				playerMapPos;
	};
}