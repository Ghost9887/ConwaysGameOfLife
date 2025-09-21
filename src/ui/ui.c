#include "ui.h"

extern bool play;
extern float speed;

void drawPlayButton(Camera2D *camera) {
    const int buttonWidth = 300;
    const int buttonHeight = 50;
    Rectangle button = {
        (GRIDWIDTH * CELLSIZE / 2 -  buttonWidth / 2),
        -100,
        buttonWidth,
        buttonHeight
    };
    DrawRectangleRec(button, WHITE);
    Color textColor = play ? GREEN : RED;
    char *buttonPlaying = "Playing";
    char *buttonStopped = "Stopped";
    char *buttonText = play ? buttonPlaying : buttonStopped;
    int fontSize = 30;
    int textWidth = MeasureText(buttonText, fontSize);
    int textX = button.x + (button.width - textWidth) / 2;
    int textY = button.y + (button.height - fontSize) / 2;
    DrawText(buttonText, textX, textY, fontSize, textColor);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
        if (CheckCollisionPointRec(mousePos, button)) {
            play = !play;
        }
    }
}

void drawRandomizeButton(Camera2D *camera, Cell *cellArr){
    const int buttonWidth = 200;
    const int buttonHeight = 40;
    Rectangle button = {
        (GRIDWIDTH * CELLSIZE / 2 -  buttonWidth / 2),
        -150,
        buttonWidth,
        buttonHeight
    };
    DrawRectangleRec(button, WHITE);
    char *name = "Randomize";
    int fontSize = 30;
    int textWidth = MeasureText(name, fontSize);
    int textX = button.x + (button.width - textWidth) / 2;
    int textY = button.y + (button.height - fontSize) / 2;
    DrawText(name, textX, textY, fontSize, BLACK);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
        if (CheckCollisionPointRec(mousePos, button)) {
          randomizeGrid(cellArr);
        }
    }
}

void drawClearButton(Camera2D *camera, Cell *cellArr){
    const int buttonWidth = 200;
    const int buttonHeight = 40;
    Rectangle button = {
        (GRIDWIDTH * CELLSIZE / 2 -  buttonWidth / 2),
        -200,
        buttonWidth,
        buttonHeight
    };
    DrawRectangleRec(button, WHITE);
    char *name = "Clear";
    int fontSize = 30;
    int textWidth = MeasureText(name, fontSize);
    int textX = button.x + (button.width - textWidth) / 2;
    int textY = button.y + (button.height - fontSize) / 2;
    DrawText(name, textX, textY, fontSize, BLACK);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
        if (CheckCollisionPointRec(mousePos, button)) {
          clearGrid(cellArr);
        }
    }
}

void drawSpeedUpButtons(Camera2D *camera) {
    const int buttonWidth = 50;
    const int buttonHeight = 50;
    const float step = 0.1f;
    const float minSpeed = 0.0f;
    const float maxSpeed = 1.0f;
    int centerX = (GRIDWIDTH * CELLSIZE) / 2;
    int buttonY = -100;
    Rectangle downButton = {
        centerX - 300 / 2 - buttonWidth - 10,
        buttonY,
        buttonWidth,
        buttonHeight
    };
    Rectangle upButton = {
        centerX + 300 / 2 + 10,
        buttonY,
        buttonWidth,
        buttonHeight
    };
    DrawRectangleRec(downButton, WHITE);
    DrawRectangleRec(upButton, WHITE);
    DrawText("-", downButton.x + 18, downButton.y + 5, 30, RED);
    DrawText("+", upButton.x + 15, upButton.y + 5, 30, GREEN);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), *camera);
        if (CheckCollisionPointRec(mousePos, downButton)) {
            speed = Clamp(speed - step, minSpeed, maxSpeed);
        } else if (CheckCollisionPointRec(mousePos, upButton)) {
            speed = Clamp(speed + step, minSpeed, maxSpeed);
        }
    }
    DrawText(TextFormat("Speed: %.2f", speed), centerX / 2 + 100, buttonY + buttonHeight + 10, 20, WHITE);
}
void updateUI(Camera2D *camera, Cell *cellArr){
  drawPlayButton(camera);
  drawSpeedUpButtons(camera);
  drawRandomizeButton(camera, cellArr);
  drawClearButton(camera, cellArr);
}
