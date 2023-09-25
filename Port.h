/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Abdelrahman Saeed
 ******************************************************************************/

#ifndef PORT_H_
#define PORT_H_

/* Id for the company in the AUTOSAR
 * for example Mohamed Tarek's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT Init */
#define PORT_INIT_SID   (uint8)0x00

/* Service ID for PORT Set Pin Direction */
#define PORT_SET_PIN_DIRECTION_SID    (uint8)0x01

/* Service ID for PORT Refresh Port Direction */
#define PORT_REFRESH_PORT_DIRECTION_SID    (uint8)0x02

/* Service ID for PORT Get Version Info */
#define PORT_GET_VERSION_INFO_SID    (uint8)0x03

/* Service ID for PORT Set Pin Mode */
#define PORT_SET_PIN_MODE_SID    (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/

/* DET Error to detect invalid Port Pin ID */
#define PORT_E_PARAM_PIN   (uint8)0x0A

/* DET Error to detect change direction for unchangeable Port Pin */
#define PORT_E_DIRECTION_UNCHANGEABLE     (uint8)0x0B

/* DET Error to detect calling Port_Init with wrong parameters */
#define PORT_E_PARAM_CONFIG   (uint8)0x0C

/* DET Error to detect invalid mode */
#define PORT_E_PARAM_INVALID_MODE   (uint8)0x0D

/* DET Error to detect change mode for unchangeable Port Pin */
#define PORT_E_MODE_UNCHANGEABLE   (uint8)0x0E

/* DET Error to detect Calling API without module initialization */
#define PORT_E_UNINIT  (uint8)0x0F

/* DET Error to detect calling API with NULL pointer */
#define PORT_E_PARAM_POINTER  (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for port number */
typedef uint8 Port_PortType;

/* Type definition for Port Pin number */
typedef uint8 Port_PinType;

/* Type definition for Port Pin Mode */
typedef uint8 Port_PinModeType;

/* Type definition for Port Pin initial Value */
typedef uint8 Port_PinLevelInitValue;

/* Type definition for Port pin Direction Changeable during run time */
typedef uint8 Port_PinDirectionChangeable;

/* Type definition for Port pin Mode Changeable during run time */
typedef uint8 Port_PinModeChangeable;

/* Enum for Port Pin Direction */
typedef enum{
  INPUT,OUTPUT
}Port_PinDirectionType;

/* Enum for Port Pin internal Resistor */
typedef enum{
  NO_RESISTOR,PULL_UP,PULL_DOWN
}Port_PinInternalResistor;

/* Structure to configure Port Pin */
typedef struct{
  Port_PortType Port_Num;
  Port_PinType Port_PinNum;
  Port_PinModeType Port_PinMode;
  Port_PinLevelInitValue Port_PinInitialValue;
  Port_PinDirectionChangeable Port_PinDirChangeable;
  Port_PinModeChangeable Port_PinMoChangeable;
  Port_PinDirectionType Port_PinDirection;
  Port_PinInternalResistor Port_PinResistor;
}Port_ConfigPortPin;

/* Structure to initialize the Port */
typedef struct{
  Port_ConfigPortPin portPins[PORT_TOTAL_NUMBER_OF_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* API for initialize Port */
void Port_Init(const Port_ConfigType* configPtr);

/* API for set Port Pin direction */
void Port_SetPinDirection(Port_PinType pin, Port_PinDirectionType direction);

/* API for refresh Port Pin Direction */
void Port_RefreshPortDirection(void);

/* API for get the version info */
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);

/* API for set port pin mode */
void Port_SetPinMode(Port_PinType pin, Port_PinModeType mode);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* external Structure to configure Port pins */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H_ */