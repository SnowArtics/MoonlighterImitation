#pragma once
#include "snComponent.h"
#include "snCollider2D.h"

namespace sn
{
	class Script : public Component
	{
	public:
		Script();
		~Script();
	
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider2D* other, Collider2D* me) {};
		virtual void OnCollisionStay(Collider2D* other, Collider2D* me) {};
		virtual void OnCollisionExit(Collider2D* other, Collider2D* me) {};
	
	private:
	
	};
}