/******************************************************************************/
/*                                                                            */
/*                               HEADER FILES                                 */
/*                                                                            */
/******************************************************************************/
#include "application.h"

/******************************************************************************/
/*                                                                            */
/*                           USER DEFINED VARIABLES                           */
/*                                                                            */
/******************************************************************************/
uint8_t readUserInput;

/******************************************************************************/
/*                                                                            */
/*                    USER DEFINED FUNCTION DEFINITIONS                       */
/*                                                                            */
/******************************************************************************/
void Application(void)
{
    if(UART2_IsRxReady())
    {
        // Accept user input using UART2
        readUserInput = UART2_Read();            
        switch(toupper(readUserInput))              // Accepts lower case as well as upper case user inputs
        {
            case 'A':
            {
                printf("\n\t\r The option selected is I2C Communication with SHT Click over MVIO...\n\n");

                // Check if the VDDIO2 voltage is within the operating range of SHT Click
                if(Get_VDDIO2Voltage() > SHT_MIN_VTG)
                {
                    I2C_Application();
                }
                else
                {
                    printf("\n\t\r The VDDIO2 voltage is not within the operating range...\n\n");
                }
                break;
            }
            case 'B':
            {
                printf("\n\t\r The option selected is UART Communication with GPS3 Click over MVIO...\n\n");

                // Check if the VDDIO2 voltage is within the operating range of GPS3 Click
                if(Get_VDDIO2Voltage() > GPS_MIN_VTG)
                {
                    UART_Application();
                }
                else
                {
                    printf("\n\t\r The VDDIO2 voltage is not within the operating range...\n\n");
                }
                break;
            }
            case 'C':
            {
                printf("\n\t\r The option selected is SPI Communication with UV Click over MVIO...\n\n");

                // Check if the VDDIO2 voltage is within the operating range of UV Click
                if(Get_VDDIO2Voltage() > UV_MIN_VTG)
                {
                    SPI_Application();
                }
                else
                {
                    printf("\n\t\r The VDDIO2 voltage is not within the operating range...\n\n");
                }
                break;
            }
            case 'D':
            {
                printf("\n\t\r The option selected is to check if VDDIO2 Voltage is within operating range...\n\n");

                // Check the VDDIO2 voltage applied on VDDIO2 pin
                printf("\n\t\r The voltage applied is: %.2f V. \n\t\r", Get_VDDIO2Voltage());
                break;
            }

            default:
            {
                printf("\n\t\r INVALID INPUT...!!!\n\n");
                break;
            }
        }
        DefaultDisplayMessage();
    }
}

float Get_VDDIO2Voltage(void)
{
    uint16_t adcData_VDDIO2 = VARIABLE_INIT;
    float mvioVoltage = VARIABLE_INIT;
    
    adcData_VDDIO2 = ADCC_GetSingleConversion(channel_VDDIO2_by_10);     // ADC Input Channel: VDDIO2   
    mvioVoltage = ((float)adcData_VDDIO2 * MVIO_COMP_FACTOR);
    
    return mvioVoltage;
}

void DefaultDisplayMessage(void)
{
    __delay_ms(WAITTIME);
    printf("\n\t\r --------------------------------------------------------------------\n\n");
    printf("\n\t\r Interfacing sensors with PIC18F56Q24 using MVIO at 2.8V...!!!\n\n");
    printf("\n\t\r Select one of the below options to view the feature: \n\n");
    printf("\n\t\r A - Display SHT Click data via I2C Communication \n\n\t\r B - Display GPS3 Click data via UART Communication \n");
    printf("\n\t\r C - Display UV Click data via SPI Communication \n\n\t\r D - Display if the VDDIO2 Voltage is within operating range \n");
    printf("\n\t\r Any other input apart from A,B,C,D - Invalid Input \n\n");
    printf("\n\t\r --------------------------------------------------------------------\n\n");
}
