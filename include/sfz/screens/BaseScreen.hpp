#pragma once
#ifndef SFZ_SCREENS_BASE_SCREEN_HPP
#define SFZ_SCREENS_BASE_SCREEN_HPP

#include <memory>

namespace sfz {

using std::shared_ptr;

class BaseScreen; // Forward declaration for GameLoopOp

// GameLoopOp
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

enum class GameLoopOpType {
	NO_OPERATION,
	SWITCH_SCREEN,
	QUIT_APPLICATION
};

struct GameLoopOp final {
	GameLoopOp() noexcept = default;
	GameLoopOp(const GameLoopOp&) noexcept = default;
	GameLoopOp& operator= (const GameLoopOp&) noexcept = default;
	inline GameLoopOp(GameLoopOpType type, shared_ptr<BaseScreen> newScreen = nullptr) noexcept
	:
		type{type},
		newScreen{newScreen}
	{ }

	GameLoopOpType type;
	shared_ptr<BaseScreen> newScreen;
};

// BaseScreen
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

class BaseScreen {
public:
	virtual ~BaseScreen() = default;

	virtual GameLoopOp update(float delta) = 0;
	virtual void render(float delta) = 0;
};

} // namespace sfz

#endif