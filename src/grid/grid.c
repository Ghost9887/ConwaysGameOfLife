#include "grid.h"

void drawGrid(){
  for (int x = 0; x <= GRIDWIDTH; x++) {
    DrawLine(x * CELLSIZE, 0, x * CELLSIZE, GRIDHEIGHT * CELLSIZE, GRAY);
  }
  for (int y = 0; y <= GRIDHEIGHT; y++) {
    DrawLine(0, y * CELLSIZE, GRIDWIDTH * CELLSIZE, y * CELLSIZE, GRAY);
  }
}
