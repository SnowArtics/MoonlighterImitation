#pragma once

namespace sn::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		FSM,
		Mesh,
		Collider2D,
		Particle,
		MeshRenderer,
		Animator,
		RigidBody,
		Script,
		MonsterHPBar,
		Light,
		Camera,
		AudioListener,
		AudioSource,
		AI,
		End,
	};

	enum class eLayerType
	{
		Grid,
		Background,
		BackObject,
		Obstacle,
		DesObstacle,
		Door,
		Monster,
		MonsterHPBar,
		Projectile,
		HitEffect,
		InteractionDoor,
		Item,
		Player,
		InteractionUI,
		Light,
		UI,

		Camera,
		End = 18,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		ComputeShader,
		AudioClip,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	enum class eEventType {
		CREATE_OBJECT,
		DELETE_OBJECT,
		SCENE_CHANGE,
		CHANGE_AI_STATE,




		END,
	};

	enum class eItemType {
		NONE,

		Broken_Sword,
		Crystal_Energy,
		GolemKing_Crystal_Energy,
		Fabric,
		Golem_Core,
		Golem_King_Design,
		Golem_Pieces,
		Reinforced_Steel,
		Slime_Jelly,
		
		END,
	};
}