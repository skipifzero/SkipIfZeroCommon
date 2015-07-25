#pragma once
#ifndef SFZ_SCREENS_GAME_LOOP_HPP
#define SFZ_SCREENS_GAME_LOOP_HPP

#include <chrono>
#include <memory>

#include "sfz/screens/BaseScreen.hpp"
#include "sfz/sdl/Window.hpp"

namespace sfz {

using std::shared_ptr;

class GameLoop final {
public:
	// Constructors & destructors
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	GameLoop() = delete;
	GameLoop(const GameLoop&) = delete;
	GameLoop& operator= (const GameLoop&) = delete;

	GameLoop(sdl::Window& window, const shared_ptr<BaseScreen>& initialScreen) noexcept;

	// Public methods
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	void run();

private:
	// Private methods
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	float calculateDelta() noexcept;

	// Private members
	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

	sdl::Window& mWindow;
	std::chrono::high_resolution_clock::time_point mPreviousTime;
	shared_ptr<BaseScreen> mCurrentScreen;
};

} // namesapce sfz

#endif