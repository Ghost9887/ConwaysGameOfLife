#ifndef CELL_H
#define CELL_H

#include "common.h"

  void initCellArr(Cell *cellArr);
  void updateCellArr(Cell *cellArr, Camera2D *camera);
  void cellBehaviour(Cell *cellArr);
  void randomizeGrid(Cell *cellArr);
  void clearGrid(Cell *cellArr);

#endif
