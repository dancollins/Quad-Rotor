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
 * @file    GCC/ARMCMx/chcore_v6m.h
 * @brief   ARMv6-M architecture port macros and structures.
 *
 * @addtogroup ARMCMx_V6M_CORE
 * @{
 */

#ifndef _CHCORE_V6M_H_
#define _CHCORE_V6M_H_

/*===========================================================================*/
/* Port implementation part.                                                 */
/*===========================================================================*/

#if !defined(__DOXYGEN__)
struct extctx {
  regarm_t      r0;
  regarm_t      r1;
  regarm_t      r2;
  regarm_t      r3;
  regarm_t      r12;
  regarm_t      lr_thd;
  regarm_t      pc;
  regarm_t      xpsr;
};

struct intctx {
  regarm_t      r8;
  regarm_t      r9;
  regarm_t      r10;
  regarm_t      r11;
  regarm_t      r4;
  regarm_t      r5;
  regarm_t      r6;
  regarm_t      r7;
  regarm_t      lr;
};
#endif

/**
 * @brief   Platform dependent part of the @p chThdCreateI() API.
 * @details This code usually setup the context switching frame represented
 *          by an @p intctx structure.
 */
#define SETUP_CONTEXT(workspace, wsize, pf, arg) {                          \
  tp->p_ctx.r13 = (struct intctx *)((uint8_t *)workspace +                  \
                                     wsize -                                \
                                     sizeof(struct intctx));                \
  tp->p_ctx.r13->r4 = pf;                                                   \
  tp->p_ctx.r13->r5 = arg;                                                  \
  tp->p_ctx.r13->lr = _port_thread_start;                                   \
}

/**
 * @brief   Stack size for the system idle thread.
 * @details This size depends on the idle thread implementation, usually
 *          the idle thread should take no more space than those reserved
 *          by @p INT_REQUIRED_STACK.
 * @note    In this port it is set to 8 because the idle thread does have
 *          a stack frame when compiling without optimizations. You may
 *          reduce this value to zero when compiling with optimizations.
 */
#ifndef IDLE_THREAD_STACK_SIZE
#define IDLE_THREAD_STACK_SIZE      16
#endif

/**
 * @brief   Per-thread stack overhead for interrupts servicing.
 * @details This constant is used in the calculation of the correct working
 *          area size.
 *          This value can be zero on those architecture where there is a
 *          separate interrupt stack and the stack space between @p intctx and
 *          @p extctx is known to be zero.
 * @note    In this port it is conservatively set to 16 because the function
 *          @p chSchDoRescheduleI() can have a stack frame, expecially with
 *          compiler optimizations disabled.
 */
#ifndef INT_REQUIRED_STACK
#define INT_REQUIRED_STACK          16
#endif

/**
 * @brief   IRQ prologue code.
 * @details This macro must be inserted at the start of all IRQ handlers
 *          enabled to invoke system APIs.
 */
#define PORT_IRQ_PROLOGUE()                                                 \
  regarm_t _saved_lr;                                                       \
  asm volatile ("mov     %0, lr" : "=r" (_saved_lr) : : "memory")

/**
 * @brief   IRQ epilogue code.
 * @details This macro must be inserted at the end of all IRQ handlers
 *          enabled to invoke system APIs.
 */
#define PORT_IRQ_EPILOGUE() _port_irq_epilogue(_saved_lr)

/**
 * @brief   IRQ handler function declaration.
 * @note    @p id can be a function name or a vector number depending on the
 *          port implementation.
 */
#define PORT_IRQ_HANDLER(id) void id(void)

/**
 * @brief   Fast IRQ handler function declaration.
 * @note    @p id can be a function name or a vector number depending on the
 *          port implementation.
 */
#define PORT_FAST_IRQ_HANDLER(id) void id(void)

/**
 * @brief   Port-related initialization code.
 */
#define port_init() {                                                       \
  SCB_AIRCR = AIRCR_VECTKEY | AIRCR_PRIGROUP(0);                            \
  NVICSetSystemHandlerPriority(HANDLER_SYSTICK,                             \
    CORTEX_PRIORITY_MASK(CORTEX_PRIORITY_SYSTICK));                         \
}

/**
 * @brief   Kernel-lock action.
 * @details Usually this function just disables interrupts but may perform
 *          more actions.
 */
#define port_lock() asm volatile ("cpsid   i" : : : "memory")

/**
 * @brief   Kernel-unlock action.
 * @details Usually this function just disables interrupts but may perform
 *          more actions.
 */
#define port_unlock() asm volatile ("cpsie   i" : : : "memory")

/**
 * @brief   Kernel-lock action from an interrupt handler.
 * @details This function is invoked before invoking I-class APIs from
 *          interrupt handlers. The implementation is architecture dependent,
 *          in its simplest form it is void.
 * @note    Same as @p port_lock() in this port.
 */
#define port_lock_from_isr() port_lock()

/**
 * @brief   Kernel-unlock action from an interrupt handler.
 * @details This function is invoked after invoking I-class APIs from interrupt
 *          handlers. The implementation is architecture dependent, in its
 *          simplest form it is void.
 * @note    Same as @p port_lock() in this port.
 */
#define port_unlock_from_isr() port_unlock()

/**
 * @brief   Disables all the interrupt sources.
 */
#define port_disable() asm volatile ("cpsid   i" : : : "memory")

/**
 * @brief   Disables the interrupt sources below kernel-level priority.
 */
#define port_suspend() asm volatile ("cpsid   i" : : : "memory")

/**
 * @brief   Enables all the interrupt sources.
 */
#define port_enable() asm volatile ("cpsie   i" : : : "memory")

/**
 * @brief   Enters an architecture-dependent IRQ-waiting mode.
 * @details The function is meant to return when an interrupt becomes pending.
 *          The simplest implementation is an empty function or macro but this
 *          would not take advantage of architecture-specific power saving
 *          modes.
 * @note    Implemented as an inlined @p WFI instruction.
 */
#if CORTEX_ENABLE_WFI_IDLE || defined(__DOXYGEN__)
#define port_wait_for_interrupt() asm volatile ("wfi" : : : "memory")
#else
#define port_wait_for_interrupt()
#endif

/**
 * @brief   Performs a context switch between two threads.
 * @details This is the most critical code in any port, this function
 *          is responsible for the context switch between 2 threads.
 * @note    The implementation of this code affects <b>directly</b> the context
 *          switch performance so optimize here as much as you can.
 *
 * @param[in] ntp       the thread to be switched in
 * @param[in] otp       the thread to be switched out
 */
#if !defined(CH_DBG_ENABLE_STACK_CHECK) || defined(__DOXYGEN__)
#define port_switch(ntp, otp) _port_switch(ntp, otp)
#else
#define port_switch(ntp, otp) {                                             \
  register struct intctx *r13 asm ("r13");                                  \
  if ((void *)(r13 - 1) < (void *)(otp + 1))                                \
    chDbgPanic("stack overflow");                                           \
  _port_switch(ntp, otp);                                                   \
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
  void port_halt(void);
  void _port_switch(Thread *ntp, Thread *otp);
  void _port_irq_epilogue(regarm_t lr);
  void _port_switch_from_isr(void);
  void _port_thread_start(void);
#ifdef __cplusplus
}
#endif

#endif /* _CHCORE_V6M_H_ */

/** @} */
