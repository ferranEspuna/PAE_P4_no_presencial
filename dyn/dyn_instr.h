/*
 * hal_dyn.h
 *
 *  Created on: 18 mar. 2020
 *      Author: droma
 */

#ifndef DYN_INSTR_H_
#define DYN_INSTR_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum _dyn_instr_type
{
    DYN_INSTR__READ = 2,
    DYN_INSTR__WRITE = 3,
} DYN_INSTR_t;

typedef enum _dyn_reg_type
{
    DYN_REG__LED = 0x19,
    DYN_REG__MAX = 0x32,
    DYN_REG__CW_ANGLE_LIMIT_L = 0X06,
    DYN_REG__CW_ANGLE_LIMIT_H = 0X07,
    DYN_REG__CCW_ANGLE_LIMIT_L = 0X08,
    DYN_REG__CCW_ANGLE_LIMIT_H = 0X09,
    DYN_REG__MOVING_SPEED_L = 0X20,
    DYN_REG__MOVING_SPEED_H = 0X21,
    DYN_REG__DISTANCE_LEFT = 0X1A,
    DYN_REG__DISTANCE_CENTER = 0X1B,
    DYN_REG__DISTANCE_RIGHT = 0X1C,
} DYN_REG_t;

int dyn_write_byte(uint8_t module_id, DYN_REG_t reg_addr, uint8_t reg_write_val);
int dyn_read_byte(uint8_t module_id, DYN_REG_t reg_addr, uint8_t* reg_read_val);

int dyn_write(uint8_t module_id, DYN_REG_t reg_addr, uint8_t *val, uint8_t len);

#endif /* DYN_INSTR_H_ */
