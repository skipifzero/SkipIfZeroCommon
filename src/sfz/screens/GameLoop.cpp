#include "sfz/screens/GameLoop.hpp"

namespace sfz {

// GameLoop: Constructors & destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

GameLoop::GameLoop(sdl::Window& window, const shared_ptr<BaseScreen>& initialScreen) noexcept
:
	mWindow{window},
	mCurrentScreen{initialScreen}
{ }

// GameLoop: Public methods
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void GameLoop::run()
{
	float delta = calculateDelta();

	while (true) {
		delta = calculateDelta();

		GameLoopOp op = mCurrentScreen->update(delta);
		if (op.type == GameLoopOpType::QUIT_APPLICATION) return;
		if (op.type == GameLoopOpType::SWITCH_SCREEN) {
			mCurrentScreen = op.newScreen;
			continue;
		}

		mCurrentScreen->render(delta);

		SDL_GL_SwapWindow(mWindow.mPtr);
	}
}

// Private methods
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

float GameLoop::calculateDelta() noexcept
{
	using namespace std::chrono;
	high_resolution_clock::time_point currentTime = high_resolution_clock::now();

	float delta = duration_cast<duration<float>>(currentTime - mPreviousTime).count();
	mPreviousTime = currentTime;
	return delta;
}

} // namespace sfz