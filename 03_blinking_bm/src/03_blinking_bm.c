/* Copyright 2016, XXXX
 *
 *  * All rights reserved.
 *
 * This file is part of CIAA Firmware.
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
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief Blinking Bare Metal example source file
 **
 ** This is a mini example of the CIAA Firmware.
 **
 **/

/** \addtogroup CIAA_Firmware CIAA Firmware
 ** @{ */

/** \addtogroup Examples CIAA Firmware Examples
 ** @{ */
/** \addtogroup Baremetal Bare Metal example source file
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 *
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * yyyymmdd v0.0.1 initials initial version
 */

/*==================[inclusions]=============================================*/
#include "03_blinking_bm.h"       /* <= own header */
#include "stdint.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

//void Corre_Izquierda()

/*==================[internal data definition]===============================*/

#define PERIODO_LED   3000000

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/
void Corre_Izquierda(uint8_t *LedPrendido)
{
			switch (*LedPrendido)
				{
				case LED3:
					*LedPrendido=LED2;
					break;
				case LED2:
					*LedPrendido=LED1;
					break;
				case LED1:
					*LedPrendido=LED_R;
					break;
				case LED_R:
					*LedPrendido=LED_G;
					break;
				case LED_G:
					*LedPrendido=LED_B;
					break;
				case LED_B:
					*LedPrendido=LED3;
					break;
				default: break;
				}
}
uint8_t Corre_Derecha(uint8_t LedPrendido)
{
			switch (LedPrendido)
				{
				case LED3:
					return(LED_B);
				case LED_B:
					return(LED_G);
				case LED_G:
					return(LED_R);
				case LED_R:
					return(LED1);
				case LED1:
					return(LED2);
				case LED2:
					return(LED3);
				default: break;
				}
}


/*==================[external functions definition]==========================*/

void delay(uint32_t periodo)
{
	uint32_t i;
	for (i=PERIODO_LED * periodo; i!=0; i--);

	}

/** \brief Main function
 *
 * This is the main entry point of the software.
 *
 * \returns 0
 *
 * \remarks This function never returns. Return value is only to avoid compiler
 *          warnings or errors.
 */



int main(void)
{
   /* inicializaciones */
  //uint32_t periodo_blinking=PERIODO_LED;
   InitLeds();
   Init_Switches();

   uint8_t LedPrendido=LED3, tecla, frecuencia=1;



   /*aca va mi programa principal */
   
    while(1)
    {

    	do{
    		   ToggleLed(LedPrendido);
    		   delay(frecuencia);
    		   tecla=Read_Switches();
    	   }while(tecla==0);
    	ApagarLed(LedPrendido);

    	switch(tecla)
    			{
    			case TEC3:
    				Corre_Izquierda(&LedPrendido);
    				break;
    			case TEC4:
    				LedPrendido=Corre_Derecha(LedPrendido);
    				break;
    			case TEC2:
    				frecuencia++;
    				break;
    			case TEC1:
    				if (frecuencia>1)
    					frecuencia--;
    				else
    					frecuencia=1;
    				break;
    			default:
    				break;
    			}
    		ToggleLed(LedPrendido);
    		delay(frecuencia);
    		    };

   		return 0;


 }

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
