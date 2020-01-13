/*
Copyright 2017 Alex Ong<the.onga@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
Basic global debounce algorithm. Used in 99% of keyboards at time of implementation
When no state changes have occured for DEBOUNCE milliseconds, we push the state.
*/
#include "debounce.h"
#include "matrix.h"
#include "timer.h"
#ifndef DEBOUNCE
  #define DEBOUNCE 5
#endif

static bool debouncing = false;
static uint16_t debouncing_time;

void debounce_init(uint8_t num_rows) {}

#if DEBOUNCE > 0
void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed)
{
  if (changed) {
    debouncing = true;
    debouncing_time = timer_read();
  }

  if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
    for (int i = 0; i < num_rows; i++) {
      cooked[i] = raw[i];
    }
    debouncing = false;
  }
}
#else //no debouncing.
void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed)
{
  for (int i = 0; i < MATRIX_ROWS; i++) {
    cooked[i] = raw[i];
  }
}
#endif

bool debounce_active() {
  return debouncing;
}

