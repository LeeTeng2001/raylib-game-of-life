#pragma once

#include <raylib.h>
#include <vector>
#include <iostream>
#include "config.hpp"
#include "gameOfLife.hpp"

class MainRender {
private:
    struct BoardRenderInfo {
        Vector2 startBoardPos;
        int lineWidth;
        Vector2 cellSize;
        Color lineColor = DARKBROWN;
        Color boxFillColor = ORANGE;
        Color boxBgColor = BROWN;
    };

    GameOfLife gof{Config::DEFAULT_GRID_COUNT, Config::DEFAULT_GRID_COUNT, Config::DEFAULT_POPULATION};
    BoardRenderInfo boardInfo;
    int rowCount = Config::DEFAULT_GRID_COUNT, colCount = Config::DEFAULT_GRID_COUNT;
    float updateRate = Config::GAME_UPDATE_RATE;
    float accumTime = 0;

    void init() {
        SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
        InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, "Game Of Life");

        SetTargetFPS(40);
        SetExitKey(KEY_DELETE);

        // calculate board position
        int lineWidth = std::min(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT) * Config::BOARD_DIMENSION_PERCENTAGE;
        boardInfo.lineWidth = lineWidth;
        boardInfo.cellSize.x = (float) lineWidth / Config::DEFAULT_GRID_COUNT;
        boardInfo.cellSize.y = (float) lineWidth / Config::DEFAULT_GRID_COUNT;
        boardInfo.startBoardPos.x = ((float) Config::SCREEN_WIDTH - lineWidth) / 2;
        boardInfo.startBoardPos.y = ((float) Config::SCREEN_HEIGHT - lineWidth) / 2;
        // std::cout << boardInfo.lineWidth << " " << boardInfo.startBoardPos.x << " " << boardInfo.startBoardPos.y << std::endl;
    }

    void draw() {
        ClearBackground(LIGHTGRAY);
        DrawText("Game Of Life", 10, 10, 30, DARKGRAY);

        accumTime += GetFrameTime();
        if (accumTime >= updateRate) {
            accumTime -= updateRate;
            // std::cout << "Updating board, new accumTime: " << accumTime << std::endl;
            gof.updateBoard();
        }

        // Draw fill grid
        auto board = gof.getBoard();
        for (int i = 0; i < Config::DEFAULT_GRID_COUNT; ++i) {
            for (int j = 0; j < Config::DEFAULT_GRID_COUNT; ++j) {
                Vector2 curPos = boardInfo.startBoardPos;
                curPos.x += boardInfo.cellSize.x * i;
                curPos.y += boardInfo.cellSize.y * j;
                DrawRectangleV(curPos, boardInfo.cellSize,
                               board[i][j].alive ? boardInfo.boxFillColor : boardInfo.boxBgColor);
            }
        }

        // Draw box line
        for (int dim = 0; dim < 2; ++dim) {
            for (int j = 0; j <= Config::DEFAULT_GRID_COUNT; ++j) {
                if (dim == 0) {
                    Vector2 startPos = boardInfo.startBoardPos;
                    startPos.x += j * ((float) boardInfo.lineWidth / Config::DEFAULT_GRID_COUNT);
                    Vector2 endPos = startPos;
                    endPos.y += (float) boardInfo.lineWidth;
                    DrawLineV(startPos, endPos, boardInfo.lineColor);
                } else {
                    Vector2 startPos = boardInfo.startBoardPos;
                    startPos.y += j * ((float) boardInfo.lineWidth / Config::DEFAULT_GRID_COUNT);
                    Vector2 endPos = startPos;
                    endPos.x += (float) boardInfo.lineWidth;
                    DrawLineV(startPos, endPos, boardInfo.lineColor);
                }
            }
        }
    }

public:
    MainRender() {
        init();
    }

    void run() {
        while (!WindowShouldClose()) {
            // Update (if any)

            // Draw
            BeginDrawing();
            draw();
            EndDrawing();
        }

        CloseWindow();
    }
};
