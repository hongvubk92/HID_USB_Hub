#include "HC05_HID.h"


void HC05_HID_COM_Init(void)
{
	/* Initialize USART1 at 115200 baud, TX: PB6, RX: PB7 */
	TM_USART_Init(USART1, TM_USART_PinsPack_2, 115200);
}

void HC05_HID_SendKeyboardState(uint8_t *pbuf)
{
	uint8_t ui8Idx= 0;
	HC05_HID_WRITE(0xFD);
	HC05_HID_WRITE(9);
	HC05_HID_WRITE(1);
	HC05_HID_WRITE(pbuf[0]);
	HC05_HID_WRITE(0);
	for(ui8Idx = 0 ; ui8Idx < 6 ; ui8Idx ++)
	{
		HC05_HID_WRITE(pbuf[ui8Idx + 2]);

	}
}

void HC05_HID_SendMouseState(uint8_t *pbuf)
{
	HC05_HID_WRITE((uint8_t)0xFD);
	HC05_HID_WRITE((uint8_t)0x05);
	HC05_HID_WRITE((uint8_t)0x02);
	HC05_HID_WRITE(pbuf[0]);//Button
	HC05_HID_WRITE(pbuf[1]);//X-stop
	HC05_HID_WRITE(pbuf[2]);//Y-stop
	HC05_HID_WRITE(pbuf[3]);//Wheel
}
