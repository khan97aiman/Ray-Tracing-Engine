#pragma once

namespace NCL {
	namespace CSC8599 {
		class PushdownState
		{
		public:
			enum PushdownResult {
				Push, Pop, NoChange, Reset
			};
			PushdownState()  {
			}
			virtual ~PushdownState() {}

			virtual PushdownResult OnUpdate(float dt, PushdownState** pushFunc) = 0;
			virtual void OnAwake() {}
			virtual void OnSleep() {}
			
		protected:
		};
	}
}