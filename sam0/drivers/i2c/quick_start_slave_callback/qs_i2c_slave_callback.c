/**
 * \file
 *
 * \brief I2C Slave Quick Start Guide with Callbacks for SAMB
 *
 * Copyright (C) 2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>

//! [packet]
static struct i2c_slave_packet packet;
//! [packet]

//! [packet_data]
#define DATA_LENGTH 10
static uint8_t write_buffer[DATA_LENGTH] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09
};
static uint8_t read_buffer [DATA_LENGTH];
//! [packet_data]

/* Address of the slave */
//! [address]
#define SLAVE_ADDRESS 0x12
//! [address]

/* Init device instance. */
//! [module]
struct i2c_slave_module i2c_slave_instance;
//! [module]

//! [read_request]
static void i2c_read_request_callback(
		struct i2c_slave_module *const module)
{
	/* Init i2c packet. */
	//! [packet_write]
	packet.data_length = DATA_LENGTH;
	packet.data        = write_buffer;
	//! [packet_write]

	/* Write buffer to master */
	//! [write_packet]
	if (i2c_slave_write_packet_job(module, &packet) != STATUS_OK) {
	}
	//! [write_packet]
}
//! [read_request]

//! [write_request]
static void i2c_write_request_callback(
		struct i2c_slave_module *const module)
{
	/* Initial i2c packet. */
	//! [packet_read]
	packet.data_length = DATA_LENGTH;
	packet.data        = read_buffer;
	//! [packet_read]

	/* Read buffer from master */
	//! [interrupt]
	i2c_slave_tx_interrupt(module->hw, false);
	//! [interrupt]
	//! [read_packet]
	if (i2c_slave_read_packet_job(module, &packet) != STATUS_OK) {
	}
	//! [read_packet]
}
//! [write_request]

//! [read_complete]
static void i2c_write_complete_callback(
		struct i2c_slave_module *const module)
{
	//! [interrupt]
	i2c_slave_rx_interrupt(module->hw, false);
	i2c_slave_tx_interrupt(module->hw, true);
	//! [interrupt]
}
//! [read_complete]

//! [write_complete]
static void i2c_read_complete_callback(
		struct i2c_slave_module *const module)
{
	//! [interrupt]
	i2c_slave_tx_interrupt(module->hw, false);
	i2c_slave_rx_interrupt(module->hw, true);
	//! [interrupt]
}
//! [write_complete]
//! [initialize_i2c]
static void configure_i2c_slave(void)
{
	/* Initialize config structure and module instance. */
	//! [init_conf]
	struct i2c_slave_config config_i2c_slave;
	i2c_slave_get_config_defaults(&config_i2c_slave);
	//! [init_conf]
	/* Change address and address_mode. */
	//! [conf_changes]
	config_i2c_slave.address = SLAVE_ADDRESS;
	//! [conf_changes]
	/* Initialize and enable device with config. */
	//! [init_module]
	while(i2c_slave_init(&i2c_slave_instance, CONF_I2C_SLAVE_MODULE, &config_i2c_slave)
			!= STATUS_OK);
	//! [init_module]
	
	//! [enable_module]
	i2c_enable(i2c_slave_instance.hw);
	//! [enable_module]
}
//! [initialize_i2c]

//! [setup_i2c_callback]
static void configure_i2c_slave_callbacks(void)
{
	/* Register and enable callback functions */
	//![reg_en_i2c_callback]
	i2c_slave_register_callback(&i2c_slave_instance, i2c_read_request_callback,
			I2C_SLAVE_CALLBACK_READ_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance,
			I2C_SLAVE_CALLBACK_READ_REQUEST);
	i2c_slave_register_callback(&i2c_slave_instance, i2c_write_request_callback,
			I2C_SLAVE_CALLBACK_WRITE_REQUEST);
	i2c_slave_enable_callback(&i2c_slave_instance,
			I2C_SLAVE_CALLBACK_WRITE_REQUEST);
	i2c_slave_register_callback(&i2c_slave_instance, i2c_write_complete_callback,
			I2C_SLAVE_CALLBACK_WRITE_COMPLETE);
	i2c_slave_enable_callback(&i2c_slave_instance,
			I2C_SLAVE_CALLBACK_WRITE_COMPLETE);
	i2c_slave_register_callback(&i2c_slave_instance, i2c_read_complete_callback,
			I2C_SLAVE_CALLBACK_READ_COMPLETE);
	i2c_slave_enable_callback(&i2c_slave_instance,
			I2C_SLAVE_CALLBACK_READ_COMPLETE);
	//![reg_en_i2c_callback]
	//! [interrupt]
	i2c_slave_rx_interrupt(i2c_slave_instance.hw, true);
	//! [interrupt]
}
//! [setup_i2c_callback]

int main(void)
{
	system_clock_config(CLOCK_RESOURCE_XO_26_MHZ, CLOCK_FREQ_26_MHZ);

	//! [run_initialize_i2c]

	//! [config]
	configure_i2c_slave();
	//! [config]
	//! [config_callback]
	configure_i2c_slave_callbacks();
	//! [config_callback]
	//! [run_initialize_i2c]
	
	//! [while]
	while (true) {
		/* Infinite loop while waiting for I2C master interaction */
	}
	//! [while]
}
