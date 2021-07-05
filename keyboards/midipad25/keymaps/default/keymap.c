/* Copyright 2021 umi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
extern MidiDevice midi_device;

enum custom_layers {
	_BASE,
	_NOTE,
};
 
enum custom_keycodes {
    MI_NOTEMIN = SAFE_RANGE,
    MI_NOTE001 = MI_NOTEMIN,
    MI_NOTE002,
    MI_NOTE003,
    MI_NOTE004,
    MI_NOTE005,
    MI_NOTE006,
    MI_NOTE007,
    MI_NOTE008,
    MI_NOTE009,
    MI_NOTE010,
    MI_NOTE011,
    MI_NOTE012,
    MI_NOTE013,
    MI_NOTE014,
    MI_NOTE015,
    MI_NOTE016,
    MI_NOTE017,
    MI_NOTE018,
    MI_NOTE019,
    MI_NOTE020,
    MI_NOTE021,
    MI_NOTE022,
    MI_NOTE023,
    MI_NOTE024,
    MI_NOTE025,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        MI_C,    MI_Db,   MI_D,   MI_Eb,   MI_E,
        MI_F,    MI_Gb,   MI_G,   MI_Ab,   MI_A,
        MI_Bb,   MI_B,   MI_C_1,  MI_Db_1, MI_D_1,
        MI_Eb_1, MI_E_1, MI_F_1,  MI_Gb_1, MI_G_1,
        MI_Ab_1, MI_A_1, MI_Bb_1, MI_B_1,  DF(_NOTE)
    ),
    [_NOTE] = LAYOUT(
        MI_NOTE001, MI_NOTE002, MI_NOTE003, MI_NOTE004, MI_NOTE005,
        MI_NOTE006, MI_NOTE007, MI_NOTE008, MI_NOTE009, MI_NOTE010,
        MI_NOTE011, MI_NOTE012, MI_NOTE013, MI_NOTE014, MI_NOTE015,
        MI_NOTE016, MI_NOTE017, MI_NOTE018, MI_NOTE019, MI_NOTE020,
        MI_NOTE021, MI_NOTE022, MI_NOTE023, MI_NOTE024, DF(_BASE)
    ),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
	case MI_Db:
	case MI_D:
	case MI_Eb:
	case MI_E:
    case MI_F:
	case MI_Gb:
	case MI_G:
	case MI_Ab:
	case MI_A:
    case MI_Bb:
	case MI_B:
	case MI_C_1:
	case MI_Db_1:
	case MI_D_1:
	case MI_Eb_1:
	case MI_E_1:
	case MI_F_1:
	case MI_Gb_1:
	case MI_G_1:
	case MI_Ab_1:
	case MI_A_1:
	case MI_Bb_1:
	case MI_B_1:
      if (record->event.pressed) {
	    uint8_t channel = 1;
	    uint8_t note = keycode + 1;
		uint8_t velocity = 127;
	    midi_send_noteon(&midi_device, channel, note, velocity);
      } else {
	    uint8_t channel = 1;
	    uint8_t note = keycode + 1;
		uint8_t velocity = 127;
	    midi_send_noteoff(&midi_device, channel, note, velocity);
      }
	  return false;
    case MI_NOTE001 ... MI_NOTE025:
      if (record->event.pressed) {
	    uint8_t channel = 1;
	    uint8_t note = keycode - MI_NOTEMIN;
		uint8_t velocity = 127;
	    midi_send_cc(&midi_device, channel, note, velocity);
      } else {
	    uint8_t channel = 1;
	    uint8_t note = keycode - MI_NOTEMIN;
		uint8_t velocity = 0;
	    midi_send_cc(&midi_device, channel, note, velocity);
      }
      return false;
    default:
      return true;
  }
}
