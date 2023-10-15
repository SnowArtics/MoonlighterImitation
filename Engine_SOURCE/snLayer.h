#pragma once
#include "snGameObject.h"
#include "snEnums.h"

namespace sn {
	class Layer
	{
	public:
		Layer();
		~Layer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destory();

		void DestroyAll();

		void SetLayerType(eLayerType _ownLayerType) { ownLayerType = _ownLayerType; }
		eLayerType GetLayerType() { return ownLayerType; }

		void AddGameObject(GameObject* gameObj);
		const std::vector<GameObject*> GetGameObjects()
		{
			return mGameObjects;
		}

	private:
		std::vector<GameObject*> mGameObjects;
		eLayerType	ownLayerType;
	};
}

