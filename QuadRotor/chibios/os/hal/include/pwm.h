/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,2011 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.

                                      ---

    A special exception to the GPL can be applied should you wish to distribute
    a combined work that includes ChibiOS/RT, without being obliged to provide
    the source code for any proprietary components. See the file exception.txt
    for full details of how and when the exception can be applied.
*/

/**
 * @file    pwm.h
 * @brief   PWM Driver macros and structures.
 *
 * @addtogroup PWM
 * @{
 */

#ifndef _PWM_H_
#define _PWM_H_

#if HAL_USE_PWM || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Driver state machine possible states.
 */
typedef enum {
  PWM_UNINIT = 0,                   /**< Not initialized.                   */
  PWM_STOP = 1,                     /**< Stopped.                           */
  PWM_READY = 2,                    /**< Ready.                             */
} pwmstate_t;

/**
 * @brief PWM logic mode.
 */
typedef enum {
  PWM_OUTPUT_DISABLED = 0,          /**< Output not driven, callback only.  */
  PWM_OUTPUT_ACTIVE_HIGH = 1,       /**< Idle is logic level 0.             */
  PWM_OUTPUT_ACTIVE_LOW = 2         /**< Idle is logic level 1.             */
} pwmmode_t;

#include "pwm_lld.h"

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/**
 * @brief   Enables a PWM channel.
 * @details Programs (or reprograms) a PWM channel.
 * @note    This function has to be invoked from a lock zone.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] channel   PWM channel identifier
 * @param[in] width     PWM pulse width as clock pulses number
 *
 * @iclass
 */
#define pwmEnableChannelI(pwmp, channel, width)                             \
  pwm_lld_enable_channel(pwmp, channel, width)

/**
 * @brief Disables a PWM channel.
 * @details The channel is disabled and its output line returned to the
 *          idle state.
 * @note    This function has to be invoked from a lock zone.
 *
 * @param[in] pwmp      pointer to a @p PWMDriver object
 * @param[in] channel   PWM channel identifier
 *
 * @iclass
 */
#define pwmDisableChannelI(pwmp, channel)                                   \
  pwm_lld_disable_channel(pwmp, channel)

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
  void pwmInit(void);
  void pwmObjectInit(PWMDriver *pwmp);
  void pwmStart(PWMDriver *pwmp, const PWMConfig *config);
  void pwmStop(PWMDriver *pwmp);
  void pwmEnableChannel(PWMDriver *pwmp,
                        pwmchannel_t channel,
                        pwmcnt_t width);
  void pwmDisableChannel(PWMDriver *pwmp, pwmchannel_t channel);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_PWM */

#endif /* _PWM_H_ */

/** @} */
