/**
 *	Keil project for USB HID Host
 *
 *	Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@ide		Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *	@stdperiph	STM32F4xx Standard peripheral drivers version 1.4.0 or greater required
 */
/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_usb_hid_host.h"

#include "HC05_HID.h"
#include <stdio.h>

int main(void) {
	TM_USB_HIDHOST_Result_t USB_HID_Status;		/* USB HID Host status */
	TM_USB_HIDHOST_Mouse_t Mouse_Data;			/* Mouse handler */
	
	/* Initialize system */
	SystemInit();
	
	/* Leds init */
	TM_DISCO_LedInit();
	
	/* Delay init */
	TM_DELAY_Init();
	
	/*
	 * Init Uart for HC05
	 * */
	HC05_HID_COM_Init();
	/* Init USB HID */
	TM_USB_HIDHOST_Init();

	while (1) {
		/* Process USB HID */
		/* This must be called periodically */
		TM_USB_HIDHOST_Process();
		
		/* Get connected device */
		USB_HID_Status = TM_USB_HIDHOST_Device();
		
		/* Switch status */
		switch (USB_HID_Status) {
			/* Keyboard connected */
			case TM_USB_HIDHOST_Result_KeyboardConnected:
				
				/* GREEN led ON */
				TM_DISCO_LedOn(LED_GREEN);

				break;
			
			/* Mouse connected */
			case TM_USB_HIDHOST_Result_MouseConnected:
				
				/* RED led ON */
				TM_DISCO_LedOn(LED_RED);
			
				/* Get mouse data */
				TM_USB_HIDHOST_ReadMouse(&Mouse_Data);

				/* Check buttons */
				if (Mouse_Data.LeftButton == TM_USB_HIDHOST_Button_Pressed) {	/* Left button */
					TM_DISCO_LedOn(LED_GREEN);									/* Toggle GREEN led */
				}
				if (Mouse_Data.RightButton == TM_USB_HIDHOST_Button_Pressed) {	/* Right button */
					TM_DISCO_LedOff(LED_GREEN);									/* Toggle GREEN led */
				}
				if (Mouse_Data.MiddleButton == TM_USB_HIDHOST_Button_Pressed) {	/* Middle button */
					TM_DISCO_LedToggle(LED_GREEN);								/* Toggle GREEN led */
				}
				if (Mouse_Data.DiffX != 0 || Mouse_Data.DiffY != 0) {
					/* If there is a difference for mouse movement at any coordinate */
					TM_DISCO_LedToggle(LED_GREEN);								/* Toggle RED led */

					/* If you need to move cursor now at fix position */
					/* Positions are stored like this */
					//Mouse_Data.AbsoluteX //Absolute X position for LCD
					//Mouse_Data.AbsoluteY //Absolute Y position for LCD
				}

				break;
			
			/* No device connected */
			case TM_USB_HIDHOST_Result_Disconnected:
				
				/* Turn off leds */
				TM_DISCO_LedOff(LED_RED | LED_GREEN);
			
				break;
			
			/* Device is not supported */
			case TM_USB_HIDHOST_Result_DeviceNotSupported:
				
				/* Device is not supported */
				/* Toggle leds forever */
				TM_DISCO_LedToggle(LED_RED | LED_GREEN);
				/* Delay */
				Delayms(50);
			
				break;
			
			/* Error occurred somewhere */
			case TM_USB_HIDHOST_Result_Error:
				
				/* Error occurred */
				/* Toggle RED LED forever */
				TM_DISCO_LedToggle(LED_RED);
				/* Delay */
				Delayms(50);
			
				break;
			
			/* Library is not initialized */
			case TM_USB_HIDHOST_Result_LibraryNotInitialized:
				
				/* Library is not initialized */
				/* Toggle GREEN LED */
				TM_DISCO_LedToggle(LED_GREEN);
				/* Delay */
				Delayms(50);
			
				break;
		}
	}
}
