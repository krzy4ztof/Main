#ifndef IGAMEVIEW_H
#define IGAMEVIEW_H

namespace base_game {
	class IGameView {
		public:
			virtual ~IGameView();

			virtual void vOnRestore()=0;
			virtual void vOnRender(double fTime, float fElapsedTime)=0;
			virtual void vOnAttach(unsigned int vid, unsigned int aid)=0;

		protected:

		private:
	};
}

#endif // IGAMEVIEW_H
