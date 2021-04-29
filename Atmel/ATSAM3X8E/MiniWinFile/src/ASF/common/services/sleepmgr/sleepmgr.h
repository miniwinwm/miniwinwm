/**
 * \file
 *
 * \brief Sleep manager
 *
 * Copyright (c) 2010-2020 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#ifndef SLEEPMGR_H
#define SLEEPMGR_H

#include <compiler.h>
#include <parts.h>

#if (SAM3S || SAM3U || SAM3N || SAM3XA || SAM4S || SAM4E || SAM4N || SAM4C || SAMG || SAM4CP || SAM4CM || SAMV71 || SAMV70 || SAMS70 || SAME70)
# include "sam/sleepmgr.h"
#elif XMEGA
# include "xmega/sleepmgr.h"
#elif UC3
# include "uc3/sleepmgr.h"
#elif SAM4L
# include "sam4l/sleepmgr.h"
#elif MEGA
# include "mega/sleepmgr.h"
#elif (SAMD20 || SAMD21 || SAMR21 || SAMD11 || SAMDA1)
# include "samd/sleepmgr.h"
#elif (SAML21 || SAML22 || SAMR30 || SAMR34 || SAMR35 || WLR089)
# include "saml/sleepmgr.h"
#elif (SAMC21)
# include "samc/sleepmgr.h"
#else
# error Unsupported device.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup sleepmgr_group Sleep manager
 *
 * The sleep manager is a service for ensuring that the device is not put to
 * sleep in deeper sleep modes than the system (e.g., peripheral drivers,
 * services or the application) allows at any given time.
 *
 * It is based on the use of lock counting for the individual sleep modes, and
 * will put the device to sleep in the shallowest sleep mode that has a non-zero
 * lock count. The drivers/services/application can change these counts by use
 * of \ref sleepmgr_lock_mode and \ref sleepmgr_unlock_mode.
 * Refer to \ref sleepmgr_mode for a list of the sleep modes available for
 * locking, and the device datasheet for information on their effect.
 *
 * The application must supply the file \ref conf_sleepmgr.h.
 *
 * For the sleep manager to be enabled, the symbol \ref CONFIG_SLEEPMGR_ENABLE
 * must be defined, e.g., in \ref conf_sleepmgr.h. If this symbol is not
 * defined, the functions are replaced with dummy functions and no RAM is used.
 *
 * @{
 */

/**
 * \def CONFIG_SLEEPMGR_ENABLE
 * \brief Configuration symbol for enabling the sleep manager
 *
 * If this symbol is not defined, the functions of this service are replaced
 * with dummy functions. This is useful for reducing code size and execution
 * time if the sleep manager is not needed in the application.
 *
 * This symbol may be defined in \ref conf_sleepmgr.h.
 */
#if defined(__DOXYGEN__) && !defined(CONFIG_SLEEPMGR_ENABLE)
#  define CONFIG_SLEEPMGR_ENABLE
#endif

/**
 * \enum sleepmgr_mode
 * \brief Sleep mode locks
 *
 * Identifiers for the different sleep mode locks.
 */

/**
 * \brief Initialize the lock counts
 *
 * Sets all lock counts to 0, except the very last one, which is set to 1. This
 * is done to simplify the algorithm for finding the deepest allowable sleep
 * mode in \ref sleepmgr_enter_sleep.
 */
static inline void sleepmgr_init(void)
{
#ifdef CONFIG_SLEEPMGR_ENABLE
	uint8_t i;

	for (i = 0; i < SLEEPMGR_NR_OF_MODES - 1; i++) {
		sleepmgr_locks[i] = 0;
	}
	sleepmgr_locks[SLEEPMGR_NR_OF_MODES - 1] = 1;
#endif /* CONFIG_SLEEPMGR_ENABLE */
}

/**
 * \brief Increase lock count for a sleep mode
 *
 * Increases the lock count for \a mode to ensure that the sleep manager does
 * not put the device to sleep in the deeper sleep modes.
 *
 * \param mode Sleep mode to lock.
 */
static inline void sleepmgr_lock_mode(enum sleepmgr_mode mode)
{
#ifdef CONFIG_SLEEPMGR_ENABLE
	irqflags_t flags;

	if(sleepmgr_locks[mode] >= 0xff) {
		while (true) {
			// Warning: maximum value of sleepmgr_locks buffer is no more than 255.
			// Check APP or change the data type to uint16_t.
		}
	}

	// Enter a critical section
	flags = cpu_irq_save();

	++sleepmgr_locks[mode];

	// Leave the critical section
	cpu_irq_restore(flags);
#else
	UNUSED(mode);
#endif /* CONFIG_SLEEPMGR_ENABLE */
}

/**
 * \brief Decrease lock count for a sleep mode
 *
 * Decreases the lock count for \a mode. If the lock count reaches 0, the sleep
 * manager can put the device to sleep in the deeper sleep modes.
 *
 * \param mode Sleep mode to unlock.
 */
static inline void sleepmgr_unlock_mode(enum sleepmgr_mode mode)
{
#ifdef CONFIG_SLEEPMGR_ENABLE
	irqflags_t flags;

	if(sleepmgr_locks[mode] == 0) {
		while (true) {
			// Warning: minimum value of sleepmgr_locks buffer is no less than 0.
			// Check APP.
		}
	}

	// Enter a critical section
	flags = cpu_irq_save();

	--sleepmgr_locks[mode];

	// Leave the critical section
	cpu_irq_restore(flags);
#else
	UNUSED(mode);
#endif /* CONFIG_SLEEPMGR_ENABLE */
}

 /**
 * \brief Retrieves the deepest allowable sleep mode
 *
 * Searches through the sleep mode lock counts, starting at the shallowest sleep
 * mode, until the first non-zero lock count is found. The deepest allowable
 * sleep mode is then returned.
 */
static inline enum sleepmgr_mode sleepmgr_get_sleep_mode(void)
{
	enum sleepmgr_mode sleep_mode = SLEEPMGR_ACTIVE;

#ifdef CONFIG_SLEEPMGR_ENABLE
	uint8_t *lock_ptr = sleepmgr_locks;

	// Find first non-zero lock count, starting with the shallowest modes.
	while (!(*lock_ptr)) {
		lock_ptr++;
		sleep_mode = (enum sleepmgr_mode)(sleep_mode + 1);
	}

	// Catch the case where one too many sleepmgr_unlock_mode() call has been
	// performed on the deepest sleep mode.
	Assert((uintptr_t)(lock_ptr - sleepmgr_locks) < SLEEPMGR_NR_OF_MODES);

#endif /* CONFIG_SLEEPMGR_ENABLE */

	return sleep_mode;
}

/**
 * \fn sleepmgr_enter_sleep
 * \brief Go to sleep in the deepest allowed mode
 *
 * Searches through the sleep mode lock counts, starting at the shallowest sleep
 * mode, until the first non-zero lock count is found. The device is then put to
 * sleep in the sleep mode that corresponds to the lock.
 *
 * \note This function enables interrupts before going to sleep, and will leave
 * them enabled upon return. This also applies if sleep is skipped due to ACTIVE
 * mode being locked.
 */

static inline void sleepmgr_enter_sleep(void)
{
#ifdef CONFIG_SLEEPMGR_ENABLE
	enum sleepmgr_mode sleep_mode;

	cpu_irq_disable();

	// Find the deepest allowable sleep mode
	sleep_mode = sleepmgr_get_sleep_mode();
	// Return right away if first mode (ACTIVE) is locked.
	if (sleep_mode==SLEEPMGR_ACTIVE) {
		cpu_irq_enable();
		return;
	}
	// Enter the deepest allowable sleep mode with interrupts enabled
	sleepmgr_sleep(sleep_mode);
#else
	cpu_irq_enable();
#endif /* CONFIG_SLEEPMGR_ENABLE */
}


//! @}

#ifdef __cplusplus
}
#endif

#endif /* SLEEPMGR_H */
