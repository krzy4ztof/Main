#ifndef HUMANVIEW_H
#define HUMANVIEW_H

#include "IGameView.h"

namespace base_game {
	class HumanView : public IGameView {
		public:
			HumanView();
			virtual ~HumanView();

			virtual void vOnRestore();
			virtual void vOnRender(double fTime, float fElapsedTime);
			virtual void vOnAttach(unsigned int vid, unsigned int aid);

			void tempOnRender(double fTime, float fElapsedTime);

		protected:
			unsigned int m_ViewId;
			unsigned int m_ActorId;

		private:
			float tempAngle;
	};
}

#endif // HUMANVIEW_H
