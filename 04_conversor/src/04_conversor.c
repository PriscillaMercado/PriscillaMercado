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
#include "04_conversor.h"       /* <= own header */

const 	uint16_t senial[] = {512,544,576,608,639,670,700,730,759,786,813,838,862,885,907,926,944,961,975,988,999,1008,1015,1020,1023,1024,1023,1020,1015,1008,999,988,975,961,944,926,907,885,862,838,813,786,759,730,700,670,639,608,576,544,512,480,448,416,385,354,324,294,265,238,211,186,162,139,117,98,80,63,49,36,25,16,9,4,1,0,1,4,9,16,25,36,49,63,80,98,117,139,162,186,211,238,265,294,324,354,385,416,448,480};
float amplitud=1;
uint8_t Frecuencia=10;
uint8_t ContFrec=10;
/*==================[macros and definitions]=================================*/
void Generar_senial(void)
{
	static uint8_t i=0;
	uint16_t dato;

	ContFrec--;
	if (ContFrec==0){
	  ContFrec=Frecuencia;
      dato=amplitud*senial[i];
	  update_DAC_value(dato);
	  i++;
	  if(i==100){
			i=0;
			ToggleLed(LED1);

	  }
	}
}

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
#define PERIODO_LED 200000

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

 void delay(uint32_t periodo)
 {
 	uint32_t i;
 	for (i=periodo; i!=0; i--);

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

	void (*pfunc)(); //forma de definir un puntero a funcion
	uint8_t tecla; // frecuencia=100;
	uint32_t periodo_blinking=PERIODO_LED;

   Init_Switches();
   init_DAC_EDUCIAA();
   InitLeds();

   pfunc= &Generar_senial; // asigno a pfunc la direccion de memoria de Generar_Señal
   timer0Init(1,pfunc); //el uno es por que trabaja con frecuencias en microsegundos
   uint8_t periodo_muestreo=100;

   while(1)
   {
	do{
	   tecla=Read_Switches();
     }while(tecla==0);

	delay(PERIODO_LED);

	//if (tecla==Read_Switches())

   switch (tecla)
   {
   case TEC1:
	   amplitud=amplitud-0.1;
	   break;
   case TEC2: amplitud=amplitud+0.1;
	   break;
   case TEC3:Frecuencia--;
         ContFrec=0;
	   break;
   case TEC4:Frecuencia++;
         ContFrec=0;
	   break;
   default: break;
   }

   };


    
	return 0;


}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

