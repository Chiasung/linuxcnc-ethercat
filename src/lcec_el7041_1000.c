//
//    Copyright (C) 2015 Jakob Flierl  <jakob.flierl@gmail.com>
//    Copyright (C) 2011 Sascha Ittner <sascha.ittner@modusoft.de>
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
//

#include "lcec.h"
#include "lcec_el7041_1000.h"

typedef struct {
  hal_bit_t *reset;
  hal_bit_t *ina;
  hal_bit_t *inb;
  hal_bit_t *inc;
  hal_bit_t *inext;
  hal_bit_t *sync_err;
  hal_bit_t *expol_stall;
  hal_bit_t *count_overflow;
  hal_bit_t *count_underflow;
  hal_bit_t *tx_toggle;
  hal_bit_t *set_raw_count;
  hal_s32_t *set_raw_count_val;
  hal_bit_t *latch_c_valid;
  hal_bit_t *latch_ext_valid;
  hal_bit_t *ena_latch_c;
  hal_bit_t *ena_latch_ext_pos;
  hal_bit_t *ena_latch_ext_neg;
  hal_s32_t *raw_count;
  hal_s32_t *raw_latch;
  hal_s32_t *count;
  hal_float_t *pos_scale;
  hal_float_t *pos;

  hal_bit_t *dcm_reset;
  hal_bit_t *dcm_reduce_torque;
  hal_bit_t *dcm_enable;
  hal_bit_t *dcm_absmode;
  hal_float_t *dcm_value;
  hal_float_t *dcm_scale;
  hal_float_t *dcm_offset;
  hal_float_t *dcm_min_dc;
  hal_float_t *dcm_max_dc;
  hal_float_t *dcm_curr_dc;
  hal_s32_t *dcm_raw_val;
  hal_bit_t *dcm_ready_to_enable;
  hal_bit_t *dcm_ready;
  hal_bit_t *dcm_warning;
  hal_bit_t *dcm_error;
  hal_bit_t *dcm_move_pos;
  hal_bit_t *dcm_move_neg;
  hal_bit_t *dcm_torque_reduced;
  hal_bit_t *dcm_din1;
  hal_bit_t *dcm_din2;
  hal_bit_t *dcm_sync_err;
  hal_bit_t *dcm_tx_toggle;
  hal_float_t *dcm_velo_fb;
  hal_float_t *dcm_current_fb;

  unsigned int set_count_pdo_os;
  unsigned int set_count_pdo_bp;
  unsigned int set_count_val_pdo_os;
  unsigned int set_count_done_pdo_os;
  unsigned int set_count_done_pdo_bp;
  unsigned int expol_stall_pdo_os;
  unsigned int expol_stall_pdo_bp;
  unsigned int ina_pdo_os;
  unsigned int ina_pdo_bp;
  unsigned int inb_pdo_os;
  unsigned int inb_pdo_bp;
  unsigned int inc_pdo_os;
  unsigned int inc_pdo_bp;
  unsigned int inext_pdo_os;
  unsigned int inext_pdo_bp;
  unsigned int sync_err_pdo_os;
  unsigned int sync_err_pdo_bp;
  unsigned int tx_toggle_pdo_os;
  unsigned int tx_toggle_pdo_bp;
  unsigned int count_overflow_pdo_os;
  unsigned int count_overflow_pdo_bp;
  unsigned int count_underflow_pdo_os;
  unsigned int count_underflow_pdo_bp;
  unsigned int latch_c_valid_pdo_os;
  unsigned int latch_c_valid_pdo_bp;
  unsigned int latch_ext_valid_pdo_os;
  unsigned int latch_ext_valid_pdo_bp;
  unsigned int ena_latch_c_pdo_os;
  unsigned int ena_latch_c_pdo_bp;
  unsigned int ena_latch_ext_pos_pdo_os;
  unsigned int ena_latch_ext_pos_pdo_bp;
  unsigned int ena_latch_ext_neg_pdo_os;
  unsigned int ena_latch_ext_neg_pdo_bp;
  unsigned int count_pdo_os;
  unsigned int latch_pdo_os;

  unsigned int dcm_ena_pdo_os;
  unsigned int dcm_ena_pdo_bp;
  unsigned int dcm_reset_pdo_os;
  unsigned int dcm_reset_pdo_bp;
  unsigned int dcm_reduce_torque_pdo_os;
  unsigned int dcm_reduce_torque_pdo_bp;
  unsigned int dcm_velo_pdo_os;
  unsigned int dcm_ready_to_enable_pdo_os;
  unsigned int dcm_ready_to_enable_pdo_bp;
  unsigned int dcm_ready_pdo_os;
  unsigned int dcm_ready_pdo_bp;
  unsigned int dcm_warning_pdo_os;
  unsigned int dcm_warning_pdo_bp;
  unsigned int dcm_error_pdo_os;
  unsigned int dcm_error_pdo_bp;
  unsigned int dcm_move_pos_pdo_os;
  unsigned int dcm_move_pos_pdo_bp;
  unsigned int dcm_move_neg_pdo_os;
  unsigned int dcm_move_neg_pdo_bp;
  unsigned int dcm_torque_reduced_pdo_os;
  unsigned int dcm_torque_reduced_pdo_bp;
  unsigned int dcm_din1_pdo_os;
  unsigned int dcm_din1_pdo_bp;
  unsigned int dcm_din2_pdo_os;
  unsigned int dcm_din2_pdo_bp;
  unsigned int dcm_sync_err_pdo_os;
  unsigned int dcm_sync_err_pdo_bp;
  unsigned int dcm_tx_toggle_pdo_os;
  unsigned int dcm_tx_toggle_pdo_bp;

  int enc_do_init;
  int16_t enc_last_count;
  double enc_old_scale;
  double enc_scale_recip;
  double dcm_old_scale;
  double dcm_scale_recip;

  int last_operational;

  hal_bit_t last_dcm_enable;

  hal_bit_t *fault;
  hal_bit_t *fault_reset;

  hal_bit_t internal_fault;

  hal_u32_t fault_reset_retry;
  hal_u32_t fault_reset_state;
  hal_u32_t fault_reset_cycle;

} lcec_el7041_1000_data_t;

static ec_pdo_entry_info_t lcec_el7041_1000_channel1_enc_out[] = {
    {0x7000, 0x01,  1}, /* Enable latch C */
    {0x7000, 0x02,  1}, /* Enable latch extern on positive edge */
    {0x7000, 0x03,  1}, /* Set counter */
    {0x7000, 0x04,  1}, /* Enable latch extern on negative edge */
    {0x0000, 0x00,  4}, /* Gap */
    {0x0000, 0x00,  8}, /* Gap */
    {0x7000, 0x11, 16}  /* Set counter value */
};

static ec_pdo_entry_info_t lcec_el7041_1000_channel1_dcm_out[] = {
    {0x7010, 0x01,  1}, /* Enable */
    {0x7010, 0x02,  1}, /* Reset */
    {0x7010, 0x03,  1}, /* Reduce torque */
    {0x0000, 0x00,  5}, /* Gap */
    {0x0000, 0x00,  8}  /* Gap */
};

static ec_pdo_entry_info_t lcec_el7041_1000_channel1_vel_out[] = {
    {0x7010, 0x21, 16}  /* Velocity */
};

static ec_pdo_entry_info_t lcec_el7041_1000_channel1_enc_in[] = {
    {0x6000, 0x01,  1}, /* Latch C valid */
    {0x6000, 0x02,  1}, /* Latch extern valid */
    {0x6000, 0x03,  1}, /* Set counter done */
    {0x6000, 0x04,  1}, /* Counter underflow */
    {0x6000, 0x05,  1}, /* Counter overflow */
    {0x0000, 0x00,  2}, /* Gap */
    {0x6000, 0x08,  1}, /* Extrapolation stall */
    {0x6000, 0x09,  1}, /* Status of input A */
    {0x6000, 0x0a,  1}, /* Status of input B */
    {0x6000, 0x0b,  1}, /* Status of input C */
    {0x0000, 0x00,  1}, /* Gap */
    {0x6000, 0x0d,  1}, /* Status of extern latch */
    {0x6000, 0x0e,  1}, /* Sync error */
    {0x0000, 0x00,  1}, /* Gap */
    {0x6000, 0x10,  1}, /* TxPDO Toggle */
    {0x6000, 0x11, 16}, /* Counter value */
    {0x6000, 0x12, 16}  /* Latch value */
};

static ec_pdo_entry_info_t lcec_el7041_1000_channel1_dcm_in[] = {
    {0x6010, 0x01,  1}, /* Ready to enable */
    {0x6010, 0x02,  1}, /* Ready */
    {0x6010, 0x03,  1}, /* Warning */
    {0x6010, 0x04,  1}, /* Error */
    {0x6010, 0x05,  1}, /* Moving positive */
    {0x6010, 0x06,  1}, /* Moving negative */
    {0x6010, 0x07,  1}, /* Torque reduced */
    {0x0000, 0x00,  4}, /* Gap */
    {0x6010, 0x0c,  1}, /* Digital input 1 */
    {0x6010, 0x0d,  1}, /* Digital input 2 */
    {0x6010, 0x0e,  1}, /* Sync error */
    {0x0000, 0x00,  1}, /* Gap */
    {0x6010, 0x10,  1}  /* TxPDO Toggle */
};

static ec_pdo_info_t lcec_el7041_1000_pdos_out[] = {
    {0x1600, 7, lcec_el7041_1000_channel1_enc_out}, /* ENC RxPDO-Map Control compact */
    {0x1602, 5, lcec_el7041_1000_channel1_dcm_out}, /* STM RxPDO-Map Control */
    {0x1604, 1, lcec_el7041_1000_channel1_vel_out}  /* STM RxPDO-Map Velocity */
};

static ec_pdo_info_t lcec_el7041_1000_pdos_in[] = {
    {0x1a00, 17, lcec_el7041_1000_channel1_enc_in}, /* ENC TxPDO-Map Status compact */
    {0x1a03, 13, lcec_el7041_1000_channel1_dcm_in}  /* STM TxPDO-Map Status */
};

static ec_sync_info_t lcec_el7041_1000_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL},
    {1, EC_DIR_INPUT,  0, NULL},
    {2, EC_DIR_OUTPUT, 3, lcec_el7041_1000_pdos_out},
    {3, EC_DIR_INPUT,  2, lcec_el7041_1000_pdos_in},
    {0xff}
};

void lcec_el7041_1000_read(struct lcec_slave *s, long period);
void lcec_el7041_1000_write(struct lcec_slave *s, long period);

int lcec_el7041_1000_init(int comp_id, struct lcec_slave *s, ec_pdo_entry_reg_t *r) {
  lcec_master_t *m = s->master;
  lcec_el7041_1000_data_t *hd;
  int err;

  // initialize callbacks
  s->proc_read  = lcec_el7041_1000_read;
  s->proc_write = lcec_el7041_1000_write;

  // alloc hal memory
  if ((hd = hal_malloc(sizeof(lcec_el7041_1000_data_t))) == NULL) {
    rtapi_print_msg(RTAPI_MSG_ERR, LCEC_MSG_PFX "hal_malloc() for slave %s.%s failed\n", m->name, s->name);
    return -EIO;
  }
  memset(hd, 0, sizeof(lcec_el7041_1000_data_t));
  s->hal_data = hd;

  // initialize sync info
  s->sync_info = lcec_el7041_1000_syncs;

  // initialize global data
  hd->last_operational = 0;

  // initialize PDO entries

#define pdo(...) LCEC_PDO_INIT(r, s->index, s->vid, s->pid, ##__VA_ARGS__)

  pdo(0x7000, 0x01, &hd->ena_latch_c_pdo_os,         &hd->ena_latch_c_pdo_bp);
  pdo(0x7000, 0x02, &hd->ena_latch_ext_pos_pdo_os,   &hd->ena_latch_ext_pos_pdo_bp);
  pdo(0x7000, 0x03, &hd->set_count_pdo_os,           &hd->set_count_pdo_bp);
  pdo(0x7000, 0x04, &hd->ena_latch_ext_neg_pdo_os,   &hd->ena_latch_ext_neg_pdo_bp);
  pdo(0x7000, 0x11, &hd->set_count_val_pdo_os,       NULL);

  pdo(0x7010, 0x01, &hd->dcm_ena_pdo_os,             &hd->dcm_ena_pdo_bp);
  pdo(0x7010, 0x02, &hd->dcm_reset_pdo_os,           &hd->dcm_reset_pdo_bp);
  pdo(0x7010, 0x03, &hd->dcm_reduce_torque_pdo_os,   &hd->dcm_reduce_torque_pdo_bp);

  pdo(0x7010, 0x21, &hd->dcm_velo_pdo_os, NULL);

  pdo(0x6000, 0x01, &hd->latch_c_valid_pdo_os,   &hd->latch_c_valid_pdo_bp);
  pdo(0x6000, 0x02, &hd->latch_ext_valid_pdo_os, &hd->latch_ext_valid_pdo_bp);
  pdo(0x6000, 0x03, &hd->set_count_done_pdo_os,  &hd->set_count_done_pdo_bp);
  pdo(0x6000, 0x04, &hd->count_underflow_pdo_os, &hd->count_overflow_pdo_bp);
  pdo(0x6000, 0x05, &hd->count_overflow_pdo_os,  &hd->count_underflow_pdo_bp);
  pdo(0x6000, 0x08, &hd->expol_stall_pdo_os,     &hd->expol_stall_pdo_bp);
  pdo(0x6000, 0x09, &hd->ina_pdo_os,             &hd->ina_pdo_bp);
  pdo(0x6000, 0x0a, &hd->inb_pdo_os,             &hd->inb_pdo_bp);
  pdo(0x6000, 0x0b, &hd->inc_pdo_os,             &hd->inc_pdo_bp);
  pdo(0x6000, 0x0d, &hd->inext_pdo_os,           &hd->inext_pdo_bp);
  pdo(0x6000, 0x0e, &hd->sync_err_pdo_os,        &hd->sync_err_pdo_bp);
  pdo(0x6000, 0x10, &hd->tx_toggle_pdo_os,       &hd->tx_toggle_pdo_bp);
  pdo(0x6000, 0x11, &hd->count_pdo_os, NULL);
  pdo(0x6000, 0x12, &hd->latch_pdo_os, NULL);

  pdo(0x6010, 0x01, &hd->dcm_ready_to_enable_pdo_os, &hd->dcm_ready_to_enable_pdo_bp);
  pdo(0x6010, 0x02, &hd->dcm_ready_pdo_os,           &hd->dcm_ready_pdo_bp);
  pdo(0x6010, 0x03, &hd->dcm_warning_pdo_os,         &hd->dcm_warning_pdo_bp);
  pdo(0x6010, 0x04, &hd->dcm_error_pdo_os,           &hd->dcm_error_pdo_bp);
  pdo(0x6010, 0x05, &hd->dcm_move_pos_pdo_os,        &hd->dcm_move_pos_pdo_bp);
  pdo(0x6010, 0x06, &hd->dcm_move_neg_pdo_os,        &hd->dcm_move_neg_pdo_bp);
  pdo(0x6010, 0x07, &hd->dcm_torque_reduced_pdo_os,  &hd->dcm_torque_reduced_pdo_bp);
  pdo(0x6010, 0x0c, &hd->dcm_din1_pdo_os,            &hd->dcm_din1_pdo_bp);
  pdo(0x6010, 0x0d, &hd->dcm_din2_pdo_os,            &hd->dcm_din2_pdo_bp);
  pdo(0x6010, 0x0e, &hd->dcm_sync_err_pdo_os,        &hd->dcm_sync_err_pdo_bp);
  pdo(0x6010, 0x10, &hd->dcm_tx_toggle_pdo_os,       &hd->dcm_tx_toggle_pdo_bp);

#undef pdo

#define msg(H, format) \
  rtapi_print_msg(RTAPI_MSG_ERR, LCEC_MSG_PFX, "exporting "#H" %s.%s.%s." format " failed\n", \
                  LCEC_MODULE_NAME, m->name, s->name)

#define hal_pin_bit(IO, V, P)       hal_pin_bit_newf(IO, V, comp_id, "%s.%s.%s." P, LCEC_MODULE_NAME, m->name, s->name)
#define hal_pin_s32(IO, V, P)       hal_pin_s32_newf(IO, V, comp_id, "%s.%s.%s." P, LCEC_MODULE_NAME, m->name, s->name)
#define hal_pin_u32(IO, V, P)       hal_pin_u32_newf(IO, V, comp_id, "%s.%s.%s." P, LCEC_MODULE_NAME, m->name, s->name)
#define hal_pin_flt(IO, V, P)     hal_pin_float_newf(IO, V, comp_id, "%s.%s.%s." P, LCEC_MODULE_NAME, m->name, s->name)

#define e(H, T, IO, V, N) if ((err = hal_##H##_##T(IO, V, N)) != 0) { msg(#H, N); return err; }

  // export encoder pins
  e(pin, bit, HAL_IN,  &(hd->reset),             "enc-reset");
  e(pin, bit, HAL_OUT, &(hd->ina),               "enc-ina");
  e(pin, bit, HAL_OUT, &(hd->inb),               "enc-inb");
  e(pin, bit, HAL_OUT, &(hd->inc),               "enc-inc");
  e(pin, bit, HAL_OUT, &(hd->inext),             "enc-inext");
  e(pin, bit, HAL_OUT, &(hd->sync_err),          "enc-sync-error");
  e(pin, bit, HAL_OUT, &(hd->expol_stall),       "enc-expol-stall");
  e(pin, bit, HAL_OUT, &(hd->tx_toggle),         "enc-tx-toggle");
  e(pin, bit, HAL_OUT, &(hd->count_overflow),    "enc-count-overflow");
  e(pin, bit, HAL_OUT, &(hd->count_underflow),   "enc-count-underflow");
  e(pin, bit, HAL_OUT, &(hd->latch_c_valid),     "enc-latch-c-valid");
  e(pin, bit, HAL_OUT, &(hd->latch_ext_valid),   "enc-latch-ext-valid");
  e(pin, bit, HAL_IO,  &(hd->set_raw_count),     "enc-set-raw-count");
  e(pin, bit, HAL_IO,  &(hd->ena_latch_c),       "enc-latch-c-enable");
  e(pin, bit, HAL_IO,  &(hd->ena_latch_ext_pos), "enc-index-ext-pos-enable");
  e(pin, bit, HAL_IO,  &(hd->ena_latch_ext_neg), "enc-index-ext-neg-enable");
  e(pin, s32, HAL_IN,  &(hd->set_raw_count_val), "enc-set-raw-count-val");
  e(pin, s32, HAL_OUT, &(hd->raw_count),         "enc-raw-count");
  e(pin, s32, HAL_OUT, &(hd->count),             "enc-count");
  e(pin, s32, HAL_OUT, &(hd->raw_latch),         "enc-raw-latch");
  e(pin, flt, HAL_OUT, &(hd->pos),               "enc-pos");
  e(pin, flt, HAL_IO,  &(hd->pos_scale),         "enc-pos-scale");

  // export servo pins
  e(pin, flt, HAL_IO,  &(hd->dcm_scale),     "srv-scale");
  e(pin, flt, HAL_IO,  &(hd->dcm_offset),    "srv-offset");
  e(pin, flt, HAL_IO,  &(hd->dcm_min_dc),    "srv-min-dc");
  e(pin, flt, HAL_IO,  &(hd->dcm_max_dc),    "srv-max-dc");
  e(pin, flt, HAL_OUT, &(hd->dcm_curr_dc),   "srv-curr-dc");
  e(pin, bit, HAL_IN,  &(hd->dcm_enable),    "srv-enable");
  e(pin, bit, HAL_IN,  &(hd->dcm_absmode),   "srv-absmode");
  e(pin, flt, HAL_IN,  &(hd->dcm_value),     "srv-cmd");
  e(pin, s32, HAL_OUT, &(hd->dcm_raw_val),   "srv-raw-cmd");
  e(pin, bit, HAL_IN,  &(hd->dcm_reset),     "srv-reset");
  e(pin, bit, HAL_IN,  &(hd->dcm_reduce_torque), "srv-reduce-torque");
  e(pin, bit, HAL_OUT, &(hd->dcm_ready_to_enable), "srv-ready-to-enable");
  e(pin, bit, HAL_OUT, &(hd->dcm_ready),     "srv-ready");
  e(pin, bit, HAL_OUT, &(hd->dcm_warning),   "srv-warning");
  e(pin, bit, HAL_OUT, &(hd->dcm_error),     "srv-error");
  e(pin, bit, HAL_OUT, &(hd->dcm_move_pos),  "srv-move-pos");
  e(pin, bit, HAL_OUT, &(hd->dcm_move_neg),  "srv-move-neg");
  e(pin, bit, HAL_OUT, &(hd->dcm_torque_reduced), "srv-torque-reduced");
  e(pin, bit, HAL_OUT, &(hd->dcm_din1),      "srv-din1");
  e(pin, bit, HAL_OUT, &(hd->dcm_din2),      "srv-din2");
  e(pin, bit, HAL_OUT, &(hd->dcm_sync_err),  "srv-sync-error");
  e(pin, bit, HAL_OUT, &(hd->dcm_tx_toggle), "srv-tx-toggle");

  e(pin, bit, HAL_OUT, &(hd->fault),       "srv-fault");
  e(pin, bit, HAL_IN,  &(hd->fault_reset), "srv-fault-reset");

#undef msg
#undef hal_pin_bit
#undef hal_pin_s32
#undef hal_pin_u32
#undef hal_pin_flt
#undef e

  // initialize pins
  *(hd->reset) = 0;
  *(hd->ina) = 0;
  *(hd->inb) = 0;
  *(hd->inc) = 0;
  *(hd->inext) = 0;
  *(hd->sync_err) = 0;
  *(hd->expol_stall) = 0;
  *(hd->tx_toggle) = 0;
  *(hd->count_overflow) = 0;
  *(hd->count_underflow) = 0;
  *(hd->latch_c_valid) = 0;
  *(hd->latch_ext_valid) = 0;
  *(hd->ena_latch_c) = 0;
  *(hd->ena_latch_ext_pos) = 0;
  *(hd->ena_latch_ext_neg) = 0;
  *(hd->set_raw_count) = 0;
  *(hd->set_raw_count_val) = 0;
  *(hd->raw_count) = 0;
  *(hd->raw_latch) = 0;
  *(hd->count) = 0;
  *(hd->pos) = 0;
  *(hd->pos_scale) = 1.0;

  *(hd->dcm_scale) = 1.0;
  *(hd->dcm_offset) = 0.0;
  *(hd->dcm_min_dc) = -1.0;
  *(hd->dcm_max_dc) = 1.0;
  *(hd->dcm_curr_dc) = 0.0;
  *(hd->dcm_enable) = 0;
  *(hd->dcm_absmode) = 0;
  *(hd->dcm_value) = 0.0;
  *(hd->dcm_raw_val) = 0;
  *(hd->dcm_reset) = 0;
  *(hd->dcm_reduce_torque) = 0;
  *(hd->dcm_ready_to_enable) = 0;
  *(hd->dcm_ready) = 0;
  *(hd->dcm_warning) = 0;
  *(hd->dcm_error) = 0;
  *(hd->dcm_move_pos) = 0;
  *(hd->dcm_move_neg) = 0;
  *(hd->dcm_torque_reduced) = 0;
  *(hd->dcm_din1) = 0;
  *(hd->dcm_din2) = 0;
  *(hd->dcm_sync_err) = 0;
  *(hd->dcm_tx_toggle) = 0;

  *(hd->fault) = 0;
  *(hd->fault_reset) = 0;

  // initialize variables
  hd->enc_do_init = 1;
  hd->enc_last_count = 0;
  hd->enc_old_scale = *(hd->pos_scale) + 1.0;
  hd->enc_scale_recip = 1.0;

  hd->dcm_old_scale = *(hd->dcm_scale) + 1.0;
  hd->dcm_scale_recip = 1.0;

  hd->internal_fault = 0;

  hd->fault_reset_retry = 0;
  hd->fault_reset_state = 0;
  hd->fault_reset_cycle = 0;

  hd->last_dcm_enable   = 0;

  return 0;
}

void lcec_el7041_1000_read(struct lcec_slave *s, long period) {
  lcec_master_t *m = s->master;
  lcec_el7041_1000_data_t *hd = (lcec_el7041_1000_data_t *) s->hal_data;
  uint8_t *pd = m->process_data;
  int16_t raw_count, raw_latch, raw_delta;

  // wait for slave to be operational
  if (!s->state.operational) {
    hd->last_operational = 0;
    return;
  }

  // check inputs

  // check for change in scale value
  if (*(hd->pos_scale) != hd->enc_old_scale) {
      // scale value has changed, test and update it
      if ((*(hd->pos_scale) < 1e-20) && (*(hd->pos_scale) > -1e-20)) {
              // value too small, divide by zero is a bad thing
              *(hd->pos_scale) = 1.0;
      }
      // save new scale to detect future changes
      hd->enc_old_scale = *(hd->pos_scale);
      // we actually want the reciprocal
      hd->enc_scale_recip = 1.0 / *(hd->pos_scale);
  }

  // get bit states
  *(hd->ina) = EC_READ_BIT(&pd[hd->ina_pdo_os], hd->ina_pdo_bp);
  *(hd->inb) = EC_READ_BIT(&pd[hd->inb_pdo_os], hd->inb_pdo_bp);
  *(hd->inc) = EC_READ_BIT(&pd[hd->inc_pdo_os], hd->inc_pdo_bp);
  *(hd->inext) = EC_READ_BIT(&pd[hd->inext_pdo_os], hd->inext_pdo_bp);
  *(hd->sync_err) = EC_READ_BIT(&pd[hd->sync_err_pdo_os], hd->sync_err_pdo_bp);
  *(hd->expol_stall) = EC_READ_BIT(&pd[hd->expol_stall_pdo_os], hd->expol_stall_pdo_bp);
  *(hd->tx_toggle) = EC_READ_BIT(&pd[hd->tx_toggle_pdo_os], hd->tx_toggle_pdo_bp);
  *(hd->count_overflow) = EC_READ_BIT(&pd[hd->count_overflow_pdo_os], hd->count_overflow_pdo_bp);
  *(hd->count_underflow) = EC_READ_BIT(&pd[hd->count_underflow_pdo_os], hd->count_underflow_pdo_bp);
  *(hd->latch_c_valid) = EC_READ_BIT(&pd[hd->latch_c_valid_pdo_os], hd->latch_c_valid_pdo_bp);
  *(hd->latch_ext_valid) = EC_READ_BIT(&pd[hd->latch_ext_valid_pdo_os], hd->latch_ext_valid_pdo_bp);

  *(hd->dcm_ready_to_enable) = EC_READ_BIT(&pd[hd->dcm_ready_to_enable_pdo_os], hd->dcm_ready_to_enable_pdo_bp);
  *(hd->dcm_ready) = EC_READ_BIT(&pd[hd->dcm_ready_pdo_os], hd->dcm_ready_pdo_bp);
  *(hd->dcm_warning) = EC_READ_BIT(&pd[hd->dcm_warning_pdo_os], hd->dcm_warning_pdo_bp);
  *(hd->dcm_error) = EC_READ_BIT(&pd[hd->dcm_error_pdo_os], hd->dcm_error_pdo_bp);
  *(hd->dcm_move_pos) = EC_READ_BIT(&pd[hd->dcm_move_pos_pdo_os], hd->dcm_move_pos_pdo_bp);
  *(hd->dcm_move_neg) = EC_READ_BIT(&pd[hd->dcm_move_neg_pdo_os], hd->dcm_move_neg_pdo_bp);
  *(hd->dcm_torque_reduced) = EC_READ_BIT(&pd[hd->dcm_torque_reduced_pdo_os], hd->dcm_torque_reduced_pdo_bp);
  *(hd->dcm_din1) = EC_READ_BIT(&pd[hd->dcm_din1_pdo_os], hd->dcm_din1_pdo_bp);
  *(hd->dcm_din2) = EC_READ_BIT(&pd[hd->dcm_din2_pdo_os], hd->dcm_din2_pdo_bp);
  *(hd->dcm_sync_err) = EC_READ_BIT(&pd[hd->dcm_sync_err_pdo_os], hd->dcm_sync_err_pdo_bp);
  *(hd->dcm_tx_toggle) = EC_READ_BIT(&pd[hd->dcm_tx_toggle_pdo_os], hd->dcm_tx_toggle_pdo_bp);

  hd->internal_fault = *(hd->dcm_error);

  // read raw values
  raw_count = EC_READ_S16(&pd[hd->count_pdo_os]);
  raw_latch = EC_READ_S16(&pd[hd->latch_pdo_os]);

  // check for operational change of slave
  if (!hd->last_operational) {
      hd->enc_last_count = raw_count;
  }

  // check for counter set done
  if (EC_READ_BIT(&pd[hd->set_count_done_pdo_os], hd->set_count_done_pdo_bp)) {
      hd->enc_last_count = raw_count;
      *(hd->set_raw_count) = 0;
  }

  // update raw values
  if (! *(hd->set_raw_count)) {
      *(hd->raw_count) = raw_count;
  }

  // handle initialization
  if (hd->enc_do_init || *(hd->reset)) {
      hd->enc_do_init = 0;
      hd->enc_last_count = raw_count;
      *(hd->count) = 0;
  }

  // clear pending fault reset if no fault
  if (!hd->internal_fault) {
    hd->fault_reset_retry = 0;
  }

  // generate gated fault
  if (hd->fault_reset_retry > 0) {
    if (hd->fault_reset_cycle < 1) {
      hd->fault_reset_cycle++;
    } else {
      hd->fault_reset_cycle = 0;
      hd->fault_reset_state = !hd->fault_reset_state;
      if (hd->fault_reset_state) {
        hd->fault_reset_retry--;
      }
    }
    *(hd->fault) = 0;
  } else {
    *(hd->fault) = hd->internal_fault;
  }

  // handle index
  if (*(hd->latch_ext_valid)) {
      *(hd->raw_latch) = raw_latch;
      hd->enc_last_count = raw_latch;
      *(hd->count) = 0;
      *(hd->ena_latch_ext_pos) = 0;
      *(hd->ena_latch_ext_neg) = 0;
  }

  // compute net counts
  raw_delta = raw_count - hd->enc_last_count;
  hd->enc_last_count = raw_count;
  *(hd->count) += raw_delta;

  // scale count to make floating point position
  *(hd->pos) = *(hd->count) * hd->enc_scale_recip;

  hd->last_operational = 1;
}

void lcec_el7041_1000_write(struct lcec_slave *s, long period) {
  lcec_master_t *m = s->master;
  lcec_el7041_1000_data_t *hd = (lcec_el7041_1000_data_t *) s->hal_data;
  uint8_t *pd = m->process_data;
  double tmpval, tmpdc, raw_val;
  int enable_on_edge;

  // set outputs

  // check for enable edge
  enable_on_edge = *(hd->dcm_enable) && !hd->last_dcm_enable;
  hd->last_dcm_enable = *(hd->dcm_enable);

  // check for autoreset
  if (enable_on_edge && hd->internal_fault) {
    hd->fault_reset_retry = 1;
    hd->fault_reset_state = 1;
    hd->fault_reset_cycle = 0;
  }

  // validate duty cycle limits, both limits must be between
  // 0.0 and 1.0 (inclusive) and max must be greater then min
  if (*(hd->dcm_max_dc) > 1.0) {
      *(hd->dcm_max_dc) = 1.0;
  }
  if (*(hd->dcm_min_dc) > *(hd->dcm_max_dc)) {
      *(hd->dcm_min_dc) = *(hd->dcm_max_dc);
  }
  if (*(hd->dcm_min_dc) < -1.0) {
      *(hd->dcm_min_dc) = -1.0;
  }
  if (*(hd->dcm_max_dc) < *(hd->dcm_min_dc)) {
      *(hd->dcm_max_dc) = *(hd->dcm_min_dc);
  }

  // do scale calcs only when scale changes
  if (*(hd->dcm_scale) != hd->dcm_old_scale) {
      // validate the new scale value
      if ((*(hd->dcm_scale) < 1e-20) && (*(hd->dcm_scale) > -1e-20)) {
              // value too small, divide by zero is a bad thing
              *(hd->dcm_scale) = 1.0;
      }
      // get ready to detect future scale changes
      hd->dcm_old_scale = *(hd->dcm_scale);
      // we will need the reciprocal
      hd->dcm_scale_recip = 1.0 / *(hd->dcm_scale);
  }

  // get command
  tmpval = *(hd->dcm_value);
  if (*(hd->dcm_absmode) && (tmpval < 0)) {
      tmpval = -tmpval;
  }

  // convert value command to duty cycle
  tmpdc = tmpval * hd->dcm_scale_recip + *(hd->dcm_offset);
  if (tmpdc < *(hd->dcm_min_dc)) {
      tmpdc = *(hd->dcm_min_dc);
  }
  if (tmpdc > *(hd->dcm_max_dc)) {
      tmpdc = *(hd->dcm_max_dc);
  }

  // set output values
  if (*(hd->dcm_enable) == 0) {
      raw_val = 0;
      *(hd->dcm_curr_dc) = 0;
  } else {
      raw_val = (double)0x7fff * tmpdc;
      if (raw_val > (double)0x7fff) {
              raw_val = (double)0x7fff;
      }
      if (raw_val < (double)-0x7fff) {
              raw_val = (double)-0x7fff;
      }
      *(hd->dcm_curr_dc) = tmpdc;
  }

  // update value
  *(hd->dcm_raw_val) = (int32_t)raw_val;

  // fault reset
  if (*(hd->fault_reset)) {
    *(hd->dcm_reset) = 1;
  }

  if (hd->fault_reset_retry > 0) {
    if (hd->fault_reset_state) {
      *(hd->dcm_reset) = 1;
    }
  } else {
    if (*(hd->dcm_enable)) {
      *(hd->dcm_reset) = 0;
    }
    *(hd->fault_reset) = 0;
  }

  // set output data
  EC_WRITE_BIT(&pd[hd->set_count_pdo_os], hd->set_count_pdo_bp, *(hd->set_raw_count));
  EC_WRITE_BIT(&pd[hd->ena_latch_c_pdo_os], hd->ena_latch_c_pdo_bp, *(hd->ena_latch_c));
  EC_WRITE_BIT(&pd[hd->ena_latch_ext_pos_pdo_os], hd->ena_latch_ext_pos_pdo_bp, *(hd->ena_latch_ext_pos));
  EC_WRITE_BIT(&pd[hd->ena_latch_ext_neg_pdo_os], hd->ena_latch_ext_neg_pdo_bp, *(hd->ena_latch_ext_neg));
  EC_WRITE_S16(&pd[hd->set_count_val_pdo_os], *(hd->set_raw_count_val));

  EC_WRITE_BIT(&pd[hd->dcm_ena_pdo_os], hd->dcm_ena_pdo_bp, *(hd->dcm_enable));
  EC_WRITE_BIT(&pd[hd->dcm_reset_pdo_os], hd->dcm_reset_pdo_bp, *(hd->dcm_reset));
  EC_WRITE_BIT(&pd[hd->dcm_reduce_torque_pdo_os], hd->dcm_reduce_torque_pdo_bp, *(hd->dcm_reduce_torque));
  EC_WRITE_S16(&pd[hd->dcm_velo_pdo_os], (int16_t)raw_val);
}

