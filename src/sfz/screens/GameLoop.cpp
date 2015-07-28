#include "sfz/screens/GameLoop.hpp"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

#include "sfz/sdl/GameController.hpp"
#include "sfz/math/Vector.hpp"

namespace sfz {

// Typedefs
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

using time_point = std::chrono::high_resolution_clock::time_point;
using std::vector;

// Static helper functions
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

static float calculateDelta(time_point& previousTime) noexcept
{
	time_point currentTime = std::chrono::high_resolution_clock::now();

	using FloatSecond = std::chrono::duration<float>;
	float delta = std::chrono::duration_cast<FloatSecond>(currentTime - previousTime).count();

	previousTime = currentTime;
	return delta;
}

static int initControllers(vector<sdl::GameController>& controllers,
                           vector<SDL_GameController*>& controllerPtrs) noexcept
{
	/*for (SDL_GameController*& c : controllerPtrs) {
		if (c != NULL) {
			SDL_GameControllerClose(c);
		}
		c = NULL;
	}*/

	int numJoysticks = SDL_NumJoysticks();
	if (numJoysticks <= 0) {
		std::cerr << "No joystics connected." << std::endl;
		return 0;
	}

	int numConnected = 0;
	for (int i = 0; i < numJoysticks; ++i) {
		if (!SDL_IsGameController(i)) {
			std::cerr << "Joystick id " << i << " is not a Game Controller." << std::endl;
			continue;
		}

		SDL_GameController* ptr = SDL_GameControllerOpen(i);
		if (ptr == NULL) {
			std::cerr << "Couldn't open Game Controller at id " << i << std::endl;
			continue;
		}
		controllerPtrs.push_back(ptr);
		controllers.emplace_back();

		std::cout << "Added Game Controller [" << numConnected << "] (id " << i << "): "
		          << SDL_GameControllerName(controllerPtrs[numConnected]) << std::endl;
		numConnected++;
	}

	return numConnected;
}

// GameLoop function
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

void runGameLoop(sdl::Window& window, shared_ptr<BaseScreen> currentScreen)
{
	// Initialize controllers
	vector<sdl::GameController> controllers;
	vector<SDL_GameController*> controllerPtrs;
	int numActiveControllers = initControllers(controllers, controllerPtrs);

	// Initialize time delta
	time_point previousTime;
	float delta = calculateDelta(previousTime);

	// Initialize SDL events
	vector<SDL_Event> events;
	SDL_Event event;

	while (true) {
		// Calculate delta
		delta = calculateDelta(previousTime);
		delta = std::max(delta, 0.25f);

		// Starts updating controller structs
		for (size_t i = 0; i < controllerPtrs.size(); i++) {
			if (controllerPtrs[i] == NULL) break;
			sdl::updateStart(controllers[i]);
		}

		// Process events
		events.clear();
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {

			// Quitting and resizing window
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
					events.push_back(event);
					break;
				}
				break;

			// SDL_GameController events
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
			case SDL_CONTROLLERDEVICEREMAPPED:
				// TODO: Should really do something.
				std::cerr << "Controller configuration changed, not yet implemented." << std::endl;
				break;
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
				if (event.cbutton.which >= controllers.size()) break;
				sdl::updateProcessEvent(controllers[event.cbutton.which], event);
				break;
			case SDL_CONTROLLERAXISMOTION:
				if (event.caxis.which >= controllers.size()) break;
				sdl::updateProcessEvent(controllers[event.caxis.which], event);
				break;

			default:
				events.push_back(event);
				break;
			}
		}

		// Finish updating controller structs
		for (size_t i = 0; i < controllers.size(); i++) {
			if (controllerPtrs[i] == NULL) break;
			sdl::updateFinish(controllers[i]);
		}

		// Update current screen
		ScreenUpdateOp op = currentScreen->update(events, controllers, delta);

		// Perform eventual operations requested by screen update
		if (op.type == ScreenUpdateOpType::QUIT_APPLICATION) {
			currentScreen->onQuit();
		} else if (op.type == ScreenUpdateOpType::SWITCH_SCREEN) {
			currentScreen = op.newScreen;
			continue;
		}

		// Render current screen
		currentScreen->render(delta);

		SDL_GL_SwapWindow(window.mPtr);
	}
}

} // namespace sfz