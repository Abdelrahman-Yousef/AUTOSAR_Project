/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Abdelrahman Saeed
 ******************************************************************************/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)

/* MUC Ports IDs */
#define PORT_A  (uint8)0
#define PORT_B  (uint8)1
#define PORT_C  (uint8)2
#define PORT_D  (uint8)3
#define PORT_E  (uint8)4
#define PORT_F  (uint8)5

/* MUC Pins IDs */
#define PIN0    (uint8)0
#define PIN1    (uint8)1
#define PIN2    (uint8)2
#define PIN3    (uint8)3
#define PIN4    (uint8)4
#define PIN5    (uint8)5
#define PIN6    (uint8)6
#define PIN7    (uint8)7

/* Total number of pins */
#define PORT_TOTAL_NUMBER_OF_PINS              (43U)

/* Port pins Functions */
#define Digital_Fun0    (uint8)0
#define Digital_Fun1    (uint8)1
#define Digital_Fun2    (uint8)2
#define Digital_Fun3    (uint8)3
#define Digital_Fun4    (uint8)4
#define Digital_Fun5    (uint8)5
#define Digital_Fun6    (uint8)6
#define Digital_Fun7    (uint8)7
#define Digital_Fun8    (uint8)8
#define Digital_Fun9    (uint8)9
#define Digital_Fun10   /* not implemented */
#define Digital_Fun11   /* not implemented */
#define Digital_Fun12   /* not implemented */ 
#define Digital_Fun13   /* not implemented */
#define Digital_Fun14    (uint8)14
#define Digital_Fun15    (uint8)15
#define Analog_Fun       (uint8)16


/* Port pin Index in the array of structures in PORT_PBcfg.c */
#define PortConf_LED1_PIN_ID_INDEX        (uint8)0x00
#define PortConf_SW1_PIN_ID_INDEX         (uint8)0x01

/* PORT Configured Port ID's  */
#define PortConf_LED1_PORT_NUM                PORT_F /* PORTF */
#define PortConf_SW1_PORT_NUM                 PORT_F /* PORTF */

/* PORT Configured Port Pin ID's */
#define PortConf_LED1_PIN_NUM             PIN1 /* Pin 1 in PORTF */
#define PortConf_SW1_PIN_NUM              PIN4 /* Pin 4 in PORTF */


#endif /* PORT_CFG_H_ */