/******************************************************************************
*
* Module: Port
*
* File Name: Port.c
*
* Description: Source file for TM4C123GH6PM Microcontroller - Port Driver
*
* Author: Abdelrahman Saeed
******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
|| (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
  || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port module.
************************************************************************************/
void Port_Init(const Port_ConfigType* configPtr){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* detect error when calling the API with null pointer */
  if(configPtr == NULL_PTR){
    Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_SID,PORT_E_PARAM_CONFIG);
  }
#endif
  
  /* pointer to hold the configuration array */
  volatile const Port_ConfigPortPin * Port_PortPins = configPtr->portPins;
  /* pinter to hold the base address of the port */
  volatile uint32 * ptr = NULL_PTR;
  /* change the port module to initialized */
  Port_Status = PORT_INITIALIZED;
  /* loop counter */
  uint8 i;
  volatile uint32 delay = 0;
  
  for(i = 0;i < PORT_TOTAL_NUMBER_OF_PINS; i++){
    
    /* Enable clock for PORT and allow time for clock to start*/
    SYSCTL_REGCGC2_REG |= (1<<Port_PortPins->Port_Num);
    delay = SYSCTL_REGCGC2_REG;
    
    switch(Port_PortPins->Port_Num){
    case PORT_A:
      ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
      break;
    case PORT_B:
      ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
      break;
    case PORT_C:
      ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
      break;
    case PORT_D:
      ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
      break;
    case PORT_E:
      ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
      break;
    case PORT_F:
      ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
      break;
    default:
#if (PORT_DEV_ERROR_DETECT == STD_ON)
      /* detect error when configure a pin with wrong port ID */
      Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_SID,PORT_E_PARAM_CONFIG);
#endif
    }
    
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* detect error when configuring wrong port pin */
    if((Port_PortPins->Port_Num == PORT_A || Port_PortPins->Port_Num == PORT_B
        || Port_PortPins->Port_Num == PORT_C || Port_PortPins->Port_Num == PORT_D) && (Port_PortPins->Port_PinNum > PIN7)){
          Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_SID,PORT_E_PARAM_CONFIG);
        }
    if(Port_PortPins->Port_Num == PORT_E && Port_PortPins->Port_PinNum > PIN5){
      Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_SID,PORT_E_PARAM_CONFIG);
    }
    if(Port_PortPins->Port_Num == PORT_F && Port_PortPins->Port_PinNum > PIN4){
      Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_SID,PORT_E_PARAM_CONFIG);
    }
#endif
    
    if((Port_PortPins->Port_PinNum <= PIN3) && (Port_PortPins->Port_Num == PORT_C)){
      /* do nothin .... pins of JTAG */
    }else if((Port_PortPins->Port_PinNum == PIN7 && Port_PortPins->Port_Num == PORT_D) || (Port_PortPins->Port_PinNum == PIN0 && Port_PortPins->Port_Num == PORT_F)){
      /* unlock the lock on these pins */
      *(volatile uint32 *)((volatile uint8 *)ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_COMMIT_REG_OFFSET),Port_PortPins->Port_PinNum);   
    }
    
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* detect error when configure a port pin with wrong direction */
    if(Port_PortPins->Port_PinDirection != INPUT && Port_PortPins->Port_PinDirection != OUTPUT){
      Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_SID,PORT_E_PARAM_CONFIG);
    }
#endif
    
    /* configure the pin as input or output */
    if(Port_PortPins->Port_PinDirection == OUTPUT){
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DIR_REG_OFFSET),Port_PortPins->Port_PinNum);
    }else{
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DIR_REG_OFFSET),Port_PortPins->Port_PinNum);
#if (PORT_DEV_ERROR_DETECT == STD_ON)
      /* detect error when configuring the pin with wrong internal resistor */
      if(Port_PortPins->Port_PinResistor != PULL_UP && Port_PortPins->Port_PinResistor != PULL_DOWN
         && Port_PortPins->Port_PinResistor != NO_RESISTOR){
           Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_SID,PORT_E_PARAM_CONFIG);
         }
#endif
      /* configure the pin with pull up or pull down or with no resistor */
      if(Port_PortPins->Port_PinResistor == PULL_UP){
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_PULL_UP_REG_OFFSET),Port_PortPins->Port_PinNum);
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins->Port_PinNum);
      }else if(Port_PortPins->Port_PinResistor == PULL_DOWN){
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_PULL_DOWN_REG_OFFSET),Port_PortPins->Port_PinNum);
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_PULL_UP_REG_OFFSET ),Port_PortPins->Port_PinNum);
      }else{
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_PULL_UP_REG_OFFSET),Port_PortPins->Port_PinNum);
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_PULL_DOWN_REG_OFFSET ),Port_PortPins->Port_PinNum);
      }
    }
    
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* detect error when configure pin with wrong mode */
    if((Port_PortPins->Port_PinMode > Analog_Fun) ||
       (Port_PortPins->Port_PinMode > Digital_Fun9 && Port_PortPins->Port_PinMode < Digital_Fun14)){
         Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_INIT_SID,PORT_E_PARAM_CONFIG);
       }
#endif
    
    /* configure the pin as digital or analog function */
    if(Port_PortPins->Port_PinMode < Analog_Fun){
      
      if(Port_PortPins->Port_PinMode == Digital_Fun0){
        /* disable the alternate function when the pin is GPIO */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_ALT_FUNC_REG_OFFSET),Port_PortPins->Port_PinNum);
        /* configure the pin with initial value when the pin is GPIO */
        if(Port_PortPins->Port_PinInitialValue == STD_HIGH){
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DATA_REG_OFFSET),Port_PortPins->Port_PinNum);
        }else{
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DATA_REG_OFFSET),Port_PortPins->Port_PinNum);
        }
      }else{
        /* enable the alternate function when the pin is not GPIO */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_ALT_FUNC_REG_OFFSET),Port_PortPins->Port_PinNum);
      }
      
      /* configure the pin with its mode */
      *(volatile uint32 *)((volatile uint8 *)ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << 4 * Port_PortPins->Port_PinNum);
      *(volatile uint32 *)((volatile uint8 *)ptr + PORT_CTL_REG_OFFSET) |=  (((uint32)Port_PortPins->Port_PinMode) << 4 * Port_PortPins->Port_PinNum);
      
      /* enable digital function */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),Port_PortPins->Port_PinNum);
      /* disable analog function */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_PortPins->Port_PinNum);
    }else{
      /* disable digital function */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),Port_PortPins->Port_PinNum);
      /* enable analog function */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_PortPins->Port_PinNum);
    }
    
    /* go to next pin */
    Port_PortPins++;
  }
}

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID , direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the port pin direction.
************************************************************************************/
void Port_SetPinDirection(Port_PinType pin, Port_PinDirectionType direction){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* detect error when calling the API with not initialized Module */
  if(Port_Status == PORT_NOT_INITIALIZED){
    Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_DIRECTION_SID,PORT_E_UNINIT);
  }
  
  /* detect error when calling the API with wrong pin ID */
  if(pin >= PORT_TOTAL_NUMBER_OF_PINS){
    Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_DIRECTION_SID,PORT_E_PARAM_PIN);
  }
  
  /* detect error when trying to change direction to unchangeable pin */
  if(Port_Configuration.portPins[pin].Port_PinDirChangeable == STD_OFF){
    Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_DIRECTION_SID,PORT_E_DIRECTION_UNCHANGEABLE);
  }
#endif
  
  /* pinter the hold the base address of the port */
  volatile uint32 * ptr = NULL_PTR;
  
  switch(Port_Configuration.portPins[pin].Port_Num){
  case PORT_A:
    ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
    break;
  case PORT_B:
    ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
    break;
  case PORT_C:
    ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
    break;
  case PORT_D:
    ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
    break;
  case PORT_E:
    ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
    break;
  case PORT_F:
    ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
    break;
  }
  
  /* configure the pin with the selected direction */
  if(direction == OUTPUT){
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DIR_REG_OFFSET),Port_Configuration.portPins[pin].Port_PinNum);
  }else{
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DIR_REG_OFFSET),Port_Configuration.portPins[pin].Port_PinNum);
  }
}

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to refresh Port Direction.
************************************************************************************/
void Port_RefreshPortDirection(void){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* detect error when calling the API with not initialized module */
  if(Port_Status == PORT_NOT_INITIALIZED){
    Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_REFRESH_PORT_DIRECTION_SID,PORT_E_UNINIT);
  }
#endif
  
  /* pointer to hold the base address of the port */
  volatile uint32 * ptr = NULL_PTR;
  /* loop counter */
  uint8 i;
  
  for(i = 0;i < PORT_TOTAL_NUMBER_OF_PINS;i++){
    switch(Port_Configuration.portPins[i].Port_Num){
    case PORT_A:
      ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
      break;
    case PORT_B:
      ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
      break;
    case PORT_C:
      ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
      break;
    case PORT_D:
      ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
      break;
    case PORT_E:
      ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
      break;
    case PORT_F:
      ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
      break;
    }
    
    /* refresh the port pin direction */
    if(Port_Configuration.portPins[i].Port_PinDirection == OUTPUT){
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DIR_REG_OFFSET),Port_Configuration.portPins[i].Port_PinNum);
    }else{
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DIR_REG_OFFSET),Port_Configuration.portPins[i].Port_PinNum);
    } 
  }
}


/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): versioninfo - pointer the version info structure
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to get the version info.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)

void Port_GetVersionInfo(Std_VersionInfoType* versioninfo){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* detect error the calling the API with not initialized module */
  if(Port_Status == PORT_NOT_INITIALIZED){
    Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_GET_VERSION_INFO_SID,PORT_E_UNINIT);
  }
  
  /* detect error when calling the API with null pointer */
  if(versioninfo == NULL_PTR){
    Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_GET_VERSION_INFO_SID,PORT_E_PARAM_POINTER);
  }
#endif
  
  /* Copy the vendor Id */
  versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
  /* Copy the module Id */
  versioninfo->moduleID = (uint16)PORT_MODULE_ID;
  /* Copy Software Major Version */
  versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
  /* Copy Software Minor Version */
  versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
  /* Copy Software Patch Version */
  versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
}

#endif


/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): pin - Port Pin ID , mode - Port Pin Mode
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set Pin mode.
************************************************************************************/
void Port_SetPinMode(Port_PinType pin, Port_PinModeType mode){
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* detect error when calling the API with not initialized module */
  if(Port_Status == PORT_NOT_INITIALIZED){
    Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_MODE_SID,PORT_E_UNINIT);
  }
  
  /* detect error when calling the API with wrong pin ID */
  if(pin >= PORT_TOTAL_NUMBER_OF_PINS){
    Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_MODE_SID,PORT_E_PARAM_PIN);
  }
  
  /* detect error when trying to set mode to unchangeable pin */
  if(Port_Configuration.portPins[pin].Port_PinMoChangeable == STD_OFF){
    Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_MODE_SID,PORT_E_MODE_UNCHANGEABLE);
  }
  
  /* detect error whne calling the API with wrong mode */
  if((mode > Analog_Fun) ||
     (mode > Digital_Fun9 && mode < Digital_Fun14)){
       Det_ReportError(PORT_MODULE_ID,PORT_INSTANCE_ID,PORT_SET_PIN_MODE_SID,PORT_E_PARAM_INVALID_MODE);
     }
#endif
  
  /* pointer to hold the base address of the port */
  volatile uint32 * ptr = NULL_PTR;
  
  switch(Port_Configuration.portPins[pin].Port_Num){
  case PORT_A:
    ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
    break;
  case PORT_B:
    ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS;
    break;
  case PORT_C:
    ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS;
    break;
  case PORT_D:
    ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS;
    break;
  case PORT_E:
    ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS;
    break;
  case PORT_F:
    ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS;
    break;
  }
  
  /* configure the pin with the selected mode */
  if(mode < Analog_Fun){
    
    if(mode == Digital_Fun0){
      /* disable alternate function */
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_ALT_FUNC_REG_OFFSET),Port_Configuration.portPins[pin].Port_PinNum);
    }else{
      /* enable alternate function */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_ALT_FUNC_REG_OFFSET),Port_Configuration.portPins[pin].Port_PinNum);
    }
    
    /* configure the pin function */
    *(volatile uint32 *)((volatile uint8 *)ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << 4 * Port_Configuration.portPins[pin].Port_PinNum);
    *(volatile uint32 *)((volatile uint8 *)ptr + PORT_CTL_REG_OFFSET) |=  (((uint32)mode) << 4 * Port_Configuration.portPins[pin].Port_PinNum);
    
    /* enable digital function */
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),Port_Configuration.portPins[pin].Port_PinNum);
    /* diable analog function */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Configuration.portPins[pin].Port_PinNum);
  }else{
    /* disable digital function */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),Port_Configuration.portPins[pin].Port_PinNum);
    /* enable analog function */
    SET_BIT(*(volatile uint32 *)((volatile uint8 *)ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Configuration.portPins[pin].Port_PinNum);
  }
}