 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Abdelrahman Saeed
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

   
const Port_ConfigType Port_Configuration = {
  PortConf_LED1_PORT_NUM,PortConf_LED1_PIN_NUM,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,OUTPUT,NO_RESISTOR,
  PortConf_SW1_PORT_NUM,PortConf_SW1_PIN_NUM,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_A,PIN0,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,  
  PORT_A,PIN1,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_A,PIN2,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_A,PIN3,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_A,PIN4,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_A,PIN5,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_A,PIN6,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_A,PIN7,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_B,PIN0,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,  
  PORT_B,PIN1,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_B,PIN2,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_B,PIN3,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_B,PIN4,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_B,PIN5,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_B,PIN6,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_B,PIN7,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_C,PIN0,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,  
  PORT_C,PIN1,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_C,PIN2,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_C,PIN3,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_C,PIN4,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_C,PIN5,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_C,PIN6,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_C,PIN7,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_D,PIN0,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,  
  PORT_D,PIN1,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_D,PIN2,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_D,PIN3,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_D,PIN4,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_D,PIN5,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_D,PIN6,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_D,PIN7,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_E,PIN0,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,  
  PORT_E,PIN1,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_E,PIN2,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_E,PIN3,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_E,PIN4,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_E,PIN5,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_F,PIN0,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,  
  PORT_F,PIN2,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
  PORT_F,PIN3,Digital_Fun0,STD_HIGH,STD_OFF,STD_OFF,INPUT,PULL_UP,
};  