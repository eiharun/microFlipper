/*
 * Bitmaps.c
 *
 *  Created on: Apr 30, 2024
 *      Author: harun
 */

#include "Bitmaps.h"

uint8_t z_iter=0;


screens menu_item[icon_len]={
  {Idle_bits,"Idle"},
  {SubGhz_bits,"Sub-GHz"},
  {RFID_bits,"RFID"},
  {NFC_bits,"NFC"},
  {Game_bits,"Game"},
  {Settings_bits,"Settings"},
};
