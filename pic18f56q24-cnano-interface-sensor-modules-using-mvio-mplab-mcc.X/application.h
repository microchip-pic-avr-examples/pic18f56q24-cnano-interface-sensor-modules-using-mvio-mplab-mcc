#ifndef APPLICATION_H_
#define	APPLICATION_H_

/******************************************************************************/
/*                                                                            */
/*                               HEADER FILES                                 */
/*                                                                            */
/******************************************************************************/
#include <xc.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>

#include "mcc_generated_files/system/system.h"
#include "i2c_application.h"
#include "spi_application.h"
#include "uart_application.h"

/******************************************************************************/
/*                                                                            */
/*                            USER DEFINED MACROS                             */
/*                                                                            */
/******************************************************************************/
#define VDDIO2_CHANNEL   (0x39)
#define WAITTIME         (1000)
#define COM_PORT_DELAY   (2000)
#define DATA_PROCESSTIME (200)
#define MVIO_COMP_FACTOR (0.0322)
#define SHT_MIN_VTG      (2.4)
#define GPS_MIN_VTG      (2.8)
#define UV_MIN_VTG       (2.7)

/******************************************************************************/
/*                                                                            */
/*                    USER DEFINED FUNCTION DECLARATION                       */
/*                                                                            */
/******************************************************************************/

/**
 * void Application(void)
 * 
 * @brief API to run the main application. It accepts input from the user and depending on the
 *        input performs the respective function.
 * 
 * @param None.
 * @return None.
 */
void Application(void);

/**
 * void DefaultDisplayMessage(void)
 * 
 * @brief API to display the default menu card for the user to provide the input.
 * 
 * @param None.
 * @return None.
 */
void DefaultDisplayMessage(void);

/**
 * float Get_VDDIO2Voltage(void)
 * 
 * @brief API to read the VDDIO2 voltage provided to the MVIO pins.
 * 
 * @param None.
 * @return mvioVoltage
 */
float Get_VDDIO2Voltage(void);

#endif /* APPLICATION_H_ */