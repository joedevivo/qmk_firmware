/*
Copyright 2016 Fred Sundvik <fsundvik@gmail.com>
Jun Wako <wakojun@gmail.com>

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
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "hal.h"
#include "timer.h"
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "matrix.h"


/*
 * Infinity ErgoDox Pinusage:
 * Column pins are input with internal pull-down. Row pins are output and strobe with high.
 * Key is high or 1 when it turns on.
 *
 *     col: { PTD1(14), PTD2(7), PTD3(8), PTD4(6), PTD5(20), PTD6(21), PTD7(5) }
 *     row: { PTB2(19), PTB3(18), PTB18(32), PTB19(25), PTC0(15), PTC9(27), PTC10(29), PTC11(30), PTD0(2) }
 */
/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];
static bool debouncing = false;
static uint16_t debouncing_time = 0;

void matrix_init(void)
{
    /* Column(sense) */
    palSetPadMode(GPIOD, 1,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 2,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 3,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 4,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 5,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 6,  PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOD, 7,  PAL_MODE_OUTPUT_PUSHPULL);

    /* Row(strobe) */
    //TODO: Backlight
    //palSetPadMode(GPIOB, 2,  PAL_MODE_INPUT_PULLDOWN);
    //palSetPadMode(GPIOB, 3,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 18, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 19, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 0,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 9,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 10, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOC, 11, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOD, 0,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 12, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 13, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 4,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOE, 1,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOE, 0,  PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOA, 5,  PAL_MODE_INPUT_PULLDOWN);

    memset(matrix, 0, MATRIX_ROWS);
    memset(matrix_debouncing, 0, MATRIX_ROWS);

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    for (int row = 0; row < MATRIX_ROWS; row++) {
        matrix_row_t data = 0;

        // strobe row
        switch (row) {
            case 0:  palSetPad(GPIOD, 1);    break;
            case 1:  palSetPad(GPIOD, 2);    break;
            case 2:  palSetPad(GPIOD, 3);    break;
            case 3:  palSetPad(GPIOD, 4);    break;
            case 4:  palSetPad(GPIOD, 5);    break;
            case 5:  palSetPad(GPIOD, 6);    break;
            case 6:  palSetPad(GPIOD, 7);    break;
            /*
            case 0:  palSetPad(GPIOB, 2);    break;
            case 1:  palSetPad(GPIOB, 3);    break;
            case 2:  palSetPad(GPIOB, 18);   break;
            case 3:  palSetPad(GPIOB, 19);   break;
            case 4:  palSetPad(GPIOC, 0);    break;
            case 5:  palSetPad(GPIOC, 9);    break;
            case 6:  palSetPad(GPIOC, 10);   break;
            case 7:  palSetPad(GPIOC, 11);   break;
            case 8:  palSetPad(GPIOD, 0);    break;
            case 9:  palSetPad(GPIOA, 12);   break;
            case 10: palSetPad(GPIOA, 13);   break;
            case 11: palSetPad(GPIOA, 4);    break;
            case 12: palSetPad(GPIOE, 1);    break;
            case 13: palSetPad(GPIOE, 0);    break;
            case 14: palSetPad(GPIOA, 5);    break;
            */
        }

        // need wait to settle pin state
        // if you wait too short, or have a too high update rate
        // the keyboard might freeze, or there might not be enough
        // processing power to update the LCD screen properly.
        // 20us, or two ticks at 100000Hz seems to be OK
        wait_us(20);

        // read col data: { PTD1, PTD2, PTD3, PTD4, PTD5, PTD6, PTD7 }
        //data = (palReadPort(GPIOC) >> 4) & 64;
       
        data = (
         // TODO: Used these pins for both matrix and backlight!
         //   ((palReadPad(GPIOB, 2)       ) )  
         //|  ((palReadPad(GPIOB, 3)  <<  1) )  
            ((palReadPad(GPIOB, 18) <<  2) )  
         |  ((palReadPad(GPIOB, 19) <<  3) )  
         |  ((palReadPad(GPIOC, 0)  <<  4) )   
         |  ((palReadPad(GPIOC, 9)  <<  5) )   
         |  ((palReadPad(GPIOC, 10) <<  6) )   
         |  ((uint32_t)(palReadPad(GPIOC, 11) <<  7) )    
         |  ((uint32_t)(palReadPad(GPIOD, 0)  <<  8) )    
         |  ((uint32_t)(palReadPad(GPIOA, 12) <<  9) )    
         |  ((uint32_t)(palReadPad(GPIOA, 13) << 10) )     
         |  ((uint32_t)(palReadPad(GPIOA, 4)  << 11) )     
         |  ((uint32_t)(palReadPad(GPIOE, 1)  << 12) )     
         |  ((uint32_t)(palReadPad(GPIOE, 0)  << 13) )     
         |  ((uint32_t)(palReadPad(GPIOA, 5)  << 14) )      
        );
//        data = palReadPad(GPIOC, 10) << 5;

//        data = (palReadPort(GPIOD) >> 1);

        // un-strobe row
        switch (row) {
            case 0:  palClearPad(GPIOD, 1);    break;
            case 1:  palClearPad(GPIOD, 2);    break;
            case 2:  palClearPad(GPIOD, 3);    break;
            case 3:  palClearPad(GPIOD, 4);    break;
            case 4:  palClearPad(GPIOD, 5);    break;
            case 5:  palClearPad(GPIOD, 6);    break;
            case 6:  palClearPad(GPIOD, 7);    break;
            /*
            case 0:  palClearPad(GPIOB, 2);  break;
            case 1:  palClearPad(GPIOB, 3);  break;
            case 2:  palClearPad(GPIOB, 18); break;
            case 3:  palClearPad(GPIOB, 19); break;
            case 4:  palClearPad(GPIOC, 0);  break;
            case 5:  palClearPad(GPIOC, 9);  break;
            case 6:  palClearPad(GPIOC, 10); break;
            case 7:  palClearPad(GPIOC, 11); break;
            case 8:  palClearPad(GPIOD, 0);  break;
            case 9:  palClearPad(GPIOA, 12); break;
            case 10: palClearPad(GPIOA, 13); break;
            case 11: palClearPad(GPIOA, 4);  break;
            case 812: palClearPad(GPIOE, 1);  break;
            case 13: palClearPad(GPIOE, 0);  break;
            case 14: palClearPad(GPIOA, 5);  break;
            */
        }
        if (matrix_debouncing[row] != data) {
            matrix_debouncing[row] = data;
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            matrix[row] = matrix_debouncing[row];
        }
        debouncing = false;
    }
    matrix_scan_quantum();
    return 1;
}

bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    xprintf("\nr/c 01234567\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%02X: ");
        matrix_row_t data = matrix_get_row(row);
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (data & (1<<col))
                xprintf("1");
            else
                xprintf("0");
        }
        xprintf("\n");
    }
}
