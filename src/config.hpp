#pragma once

// Global configuration
class Config {
public:
    static constexpr int SCREEN_WIDTH = 900;
    static constexpr int SCREEN_HEIGHT = 800;

    static constexpr int DEFAULT_GRID_COUNT = 30;
    static constexpr float DEFAULT_POPULATION = .1f;  // [0, 1], init population

    static constexpr float BOARD_DIMENSION_PERCENTAGE = .8f;
    static constexpr float GAME_UPDATE_RATE = .15f;
};