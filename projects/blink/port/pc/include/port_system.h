/**
 ******************************************************************************
 * @file           : port_system.h
 * @brief          : Header for port_system.c file.
 ******************************************************************************
 * @attention
 *
 * Josue Pagán Ortiz (j.pagan@upm.es)
 * Sistemas Digitales II
 *
 ******************************************************************************
 */

#ifndef PORT_SYSTEM_H_
#define PORT_SYSTEM_H_

/* Includes del sistema */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>

size_t port_system_init(void);
uint32_t port_system_get_millis(void);
void port_system_delay_ms(uint32_t ms);
void port_system_delay_until_ms(uint32_t *p_t, uint32_t ms);

#endif /* PORT_SYSTEM_H_ */