#include "sfz/screens/GameLoop.hpp"

namespace sfz {

// GameLoop: Constructors & destructors
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

GameLoop::GameLoop(sdl::Window& window) noexcept
:
	mWindow{window}
{ }

// GameLoop: Public methods
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void GameLoop::run(shared_ptr<BaseScreen> currentScreen)
{
	float delta = calculateDelta();
	SDL_Event event;

	while (true) {
		// Calculate delta
		delta = calculateDelta();

		// Process events
		mEvents.clear();
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				currentScreen->onQuit();
				return;
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
					currentScreen->onResize(vec2{(float)event.window.data1,
					                             (float)event.window.data1});
					break;
				default:
					mEvents.push_back(event);
					break;
				}
				break;
			default:
				mEvents.push_back(event);
				break;
			}
		}

		// Update current screen
		ScreenUpdateOp op = currentScreen->update(mEvents, delta);

		// Perform eventual operations requested by screen update
		if (op.type == ScreenUpdateOpType::QUIT_APPLICATION) {
			currentScreen->onQuit();
		} else if (op.type == ScreenUpdateOpType::SWITCH_SCREEN) {
			currentScreen = op.newScreen;
			continue;
		}

		// Render current screen
		currentScreen->render(delta);

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