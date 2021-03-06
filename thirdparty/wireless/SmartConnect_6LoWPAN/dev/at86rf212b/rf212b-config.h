/*
 * Copyright (c) 2013, Thingsquare, http://www.thingsquare.com/.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _RF212_CONFIG_H_
#define _RF212_CONFIG_H_
/*---------------------------------------------------------------------------*/
/* Set radio channel, default channel 26 as it is not overlapping with Wi-Fi */
#ifdef RF_CHANNEL
#if  RF_CHANNEL > 10
#error RF_CHANNEL must be between 1 and 10.
#endif
#define PHY_CC_CCA_CONF      (RF_CHANNEL | PHY_CC_CCA_MODE_CS_OR_ED)
#else   /* RF_CHANNEL */
#define PHY_CC_CCA_CONF      (10 | PHY_CC_CCA_MODE_CS_OR_ED)
#endif  /* RF_CHANNEL */
/*---------------------------------------------------------------------------*/
/* 
 * Define whether to use hardware (RF212) CRC/FCS check. If >0, the radio FCS is
 * taken into account and the frame is dropped if not CRC/FCS passes.
 * If 0, the frame is passed to higher layers even if corrupt. This setting is
 * used if the radio is used with non-802.15.4-2006 frames, or if the FCS check
 * is performed in layers above this.
 */
#define USE_HW_FCS_CHECK                  1
/*---------------------------------------------------------------------------*/
// #define RF212_REG_TRX_CTRL_0_CONF      ()
#if USE_HW_FCS_CHECK
#define RF212_REG_TRX_CTRL_1_CONF      (TRX_CTRL_1_DIG34_RXTX_INDICATOR | TRX_CTRL_1_SPI_CMD_TRX_STATUS | TRX_CTRL_1_AUTO_CRC)
#else   /* USE_HW_FCS_CHECK */
#define RF212_REG_TRX_CTRL_1_CONF      (TRX_CTRL_1_DIG34_RXTX_INDICATOR | TRX_CTRL_1_SPI_CMD_TRX_STATUS)
#endif  /* USE_HW_FCS_CHECK */

#define RF212_REG_PHY_TX_PWR_CONF      (TXP_0)
// #define RF212_REG_PHY_RSSI_CONF        ()
// #define RF212_REG_PHY_ED_LEVEL_CONF    ()
#define RF212_REG_PHY_CC_CCA_CONF      (PHY_CC_CCA_CONF)  /* see above */
// #define RF212_REG_CCA_THRES_CONF       ()
// #define RF212_REG_RX_CTRL_CONF         ()
// #define RF212_REG_SFD_VALUE_CONF       ()
#define RF212_REG_TRX_CTRL_2_CONF      (TRX_CTRL_2_RX_SAFE_MODE | DATA_RATE)  /* disallow overwriting rxfifo until prev has been read */
// #define RF212_REG_ANT_DIV_CONF         ()
#define RF212_REG_IRQ_MASK_CONF        (IRQ_TRXBUF_ACCESS_VIOLATION | IRQ_TRX_DONE) // IRQ_TRX_DONE
// #define RF212_REG_VREG_CTRL_CONF       ()
// #define RF212_REG_BATMON_CONF          ()
// #define RF212_REG_XOSC_CTRL_CONF       ()
// #define RF212_REG_CC_CTRL_0_CONF       ()
// #define RF212_REG_CC_CTRL_1_CONF       ()
// #define RF212_REG_RX_SYN_CONF          ()
// #define RF212_REG_TRX_RPC_CONF         ()
// #define RF212_REG_XAH_CTRL_1_CONF      ()
// #define RF212_REG_FTN_CTRL_CONF        ()
// #define RF212_REG_XAH_CTRL_2_CONF      ()
// #define RF212_REG_PLL_CF_CONF          ()
// #define RF212_REG_PLL_DCU_CONF         ()
// #define RF212_REG_PART_NUM_CONF        ()
// #define RF212_REG_VERSION_NUM_CONF     ()
// #define RF212_REG_MAN_ID_0_CONF        ()
// #define RF212_REG_MAN_ID_1_CONF        ()
// #define RF212_REG_SHORT_ADDR_0_CONF    ()
// #define RF212_REG_SHORT_ADDR_1_CONF    ()
// #define RF212_REG_PAN_ID_0_CONF        ()
// #define RF212_REG_PAN_ID_1_CONF        ()
// #define RF212_REG_IEEE_ADDR_0_CONF     ()
// #define RF212_REG_IEEE_ADDR_1_CONF     ()
// #define RF212_REG_IEEE_ADDR_2_CONF     ()
// #define RF212_REG_IEEE_ADDR_3_CONF     ()
// #define RF212_REG_IEEE_ADDR_4_CONF     ()
// #define RF212_REG_IEEE_ADDR_5_CONF     ()
// #define RF212_REG_IEEE_ADDR_6_CONF     ()
// #define RF212_REG_IEEE_ADDR_7_CONF     ()
// #define RF212_REG_XAH_CTRL_0_CONF      ()
// #define RF212_REG_CSMA_SEED_0_CONF     ()
// #define RF212_REG_CSMA_SEED_1_CONF     ()
// #define RF212_REG_CSMA_BE_CONF         ()
// #define RF212_REG_TST_CTRL_DIGI_CONF   ()
// #define RF212_REG_TST_AGC_CONF         ()
// #define RF212_REG_TST_SDM_CONF         ()
// #define RF212_REG_PHY_TX_TIME_CONF     ()

#endif  /* _RF212_CONFIG_H_ */
