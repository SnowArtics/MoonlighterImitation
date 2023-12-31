#pragma once
#include "snScript.h"

namespace sn {
	class PlayerMove : public Script
	{
	public:
		PlayerMove();
		~PlayerMove();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void Complete();

		virtual void OnCollisionEnter(Collider2D* other, sn::Collider2D* me);
		virtual void OnCollisionStay(Collider2D* other, sn::Collider2D* me);
		virtual void OnCollisionExit(Collider2D* other, sn::Collider2D* me);

	private:

	};
}


