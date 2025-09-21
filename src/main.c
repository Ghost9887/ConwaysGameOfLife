#include "common.h"
#include "grid.h"
#include "camera.h"
#include "ui.h"
#include "cell.h"


bool play = false;
float speedTimer = 0.0f;
float speed = 0.5f;


void updateGameState(Camera2D *camera, Cell *cellArr);

int main(){

  InitWindow(SCREENWIDTH, SCREENHEIGHT, "conways game of life");

  Camera2D camera;
  initCamera(&camera);

  Cell *cellArr = malloc(sizeof(Cell) * (GRIDWIDTH * GRIDHEIGHT));
  initCellArr(cellArr);

  SetTargetFPS(TARGETFPS);   
  while (!WindowShouldClose()) {
    BeginDrawing();
      BeginMode2D(camera);
        ClearBackground(DARKGRAY);
        updateGameState(&camera, cellArr);
        if(play){
          speedTimer += GetFrameTime();
          if (speedTimer >= speed) {
            cellBehaviour(cellArr); 
            speedTimer = 0.0f;
          }
        }
        drawGrid();
        updateUI(&camera, cellArr);
      EndMode2D();
    EndDrawing();
  }
  free(cellArr);
  CloseWindow();
}

void updateGameState(Camera2D *camera, Cell *cellArr){
  updateCamera(camera);
  updateCellArr(cellArr, camera);
}
