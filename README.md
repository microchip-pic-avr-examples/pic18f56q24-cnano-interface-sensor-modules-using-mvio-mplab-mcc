<!-- Please do not change this logo with link -->

<a target="_blank" href="https://www.microchip.com/" id="top-of-page">
   <picture>
      <source media="(prefers-color-scheme: light)" srcset="images/mchp_logo_light.png" width="350">
      <source media="(prefers-color-scheme: dark)" srcset="images/mchp_logo_dark.png" width="350">
      <img alt="Microchip Technologies Inc." src="https://www.microchip.com/content/experience-fragments/mchp/en_us/site/header/master/_jcr_content/root/responsivegrid/header/logo.coreimg.100.300.png/1605828081463/microchip.png">
   </picture>
</a>

# Interfacing External Sensor Modules with PIC18F56Q24 Microcontroller using MVIO

The PIC18-Q24 microcontroller family is available for various real-time, sensor interfacing applications showcases a wide range peripheral support. This family of microcontrollers particularly focuses on Multi-Voltage I/O (MVIO) interface with multiple I/O pins powered by an alternative V<sub>DD</sub> pin, Enhanced Code Protection features to provide increased security to the firmware and data, 10-bit Analog-to-Digital Converter with Computation (ADCC) capable of 300 ksps and along with these features it also has support for the traditional communication interfaces like Universal Asynchronous Receiver-Transmitter (UART) with support for asynchronous, Serial Peripheral Interface (SPI) and Inter-Integrated Circuit (I<sup>2</sup>C).

The code example intends to showcase the usage of Multi-Voltage I/O (MVIO) interface of PIC18-Q24 microcontroller family, which allows a subset of the I/O pins to be powered by a different I/O voltage domain i.e., V<sub>DDIO2</sub>. Thereby, the MVIO feature eliminates the need for having external level shifters when interfacing the microcontroller with external ICs, operating at a different supply voltage, through a serial communication interface.  In this code example, the MVIO pins are configured as serial communication (I<sup>2</sup>C, SPI and UART) lines for communication with external sensor modules that operate at a different voltage than the PIC18F56Q24 device.

## Related Documentation

* [Getting Started with Multi-Voltage I/O (MVIO)](https://ww1.microchip.com/downloads/en/Appnotes/GettingStarted-MVIO-AVRDB-DS90003287A.pdf)
* [PIC18F56Q24 Product Page](https://www.microchip.com/en-us/product/pic18f56q24)
* [PIC18F56Q24 Data Sheet](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/PIC18F26-45-46-55-56Q24-Microcontroller-Data-Sheet-XLP-DS40002503.pdf)
* [PIC18F56Q24 Code Examples on MPLAB Discover](https://mplab-discover.microchip.com/v2?dsl=PIC18F56Q24)

## Description

The code example uses a UV click, GPS click and SHT click, which communicate with the PIC18F56Q24 microcontroller using SPI, UART and I<sup>2</sup>C communication interfaces, respectively. These click boards are powered by a 2.8V supply, and the PIC18F56Q24 microcontroller is powered by a 5V supply. However, the microcontroller pins with MVIO interface capability, used for interfacing the click boards, are powered by 2.8V through the V<sub>DDIO2</sub> pin. The block diagram below shows an overview of the various microcontroller peripherals used in this code example and the pins configured for interfacing with the click boards. The data visualizer tool is used to interact with users, accept user inputs and transmit them to the microcontroller over a UART interface. Additionally, it is used to display the data requested by the user on its terminal window.

In this code example, the application firmware continuously monitors the supply voltage on the V<sub>DDIO2</sub> pin of the microcontroller and checks for valid user input if the voltage detected on the V<sub>DDIO2</sub> pin is within the permissible operating voltage range of the click boards. Based on the received user input, the application requests data from the respective click board, through the serial communication interface and displays the received data on the terminal window of the data visualizer tool. If the voltage detected on the V<sub>DDIO2</sub> pin is outside the recommended operating voltage of the click boards, then the application prompts the user to supply a recommended voltage on the V<sub>DDIO2</sub> pin. Similarly, if the user-entered input data is invalid, then the application prompts the user to input valid data.

<p align="center">
  <img width=auto height=auto src="images/blkdiagram.png">
  <br>Figure 1: Block Diagram<br>
</p>

## Software Used

This application uses MPLAB<sup>®</sup> X IDE compiler and graphical code generator to provide an easy and hassle-free user experience.

The following tools are used for this demo application:

* [MPLAB® X IDE](https://www.microchip.com/mplab/mplab-x-ide) v6.20 or newer
* [XC8 compiler](https://www.microchip.com/mplab/compilers) v2.46 or newer
* [MPLAB® Code Configurator(MCC)](https://www.microchip.com/mplab/mplab-code-configurator) v5.7.1 or newer
* [MPLAB® Data Visualizer 1.3.1665](https://www.microchip.com/en-us/tools-resources/debug/mplab-data-visualizer) or newer
* [Microchip PIC18F-Q Series Device Support](https://packs.download.microchip.com) 1.25.433 or newer
* [Data Visualizer](https://www.microchip.com/en-us/tools-resources/debug/mplab-data-visualizer) v1.3.1665 or newer
* ADCC MCC Melody Driver 1.0.6
* SPI MCC Melody Driver 1.2.0
* DMA Driver 1.1.1
* I2C Driver 6.1.2
* UART Driver 1.10.0
* MVIO Driver 1.0.0

## Hardware Used

* [PIC18F56Q24 Curiosity Nano board](https://www.microchip.com/en-us/development-tool/EV01E86A")
* [Curiosity Nano base for Click boards](https://www.microchip.com/developmenttools/ProductDetails/AC164162)
* [GPS3 Click](https://www.mikroe.com/gps-3-click)

The GPS 3 Click board provides users with positioning, navigation, and timing features. This Click board is interfaced with the microcontroller using the UART interface.

<p align="center">
  <img width=auto height=auto src="images/gpsclick.png">
  <br>Figure 2: GPS3 Click Board<br>
</p>

* [SHT Click](https://www.mikroe.com/sht-click)

The SHT Click is a compact board for high reliability and long-term stability for measuring humidity and temperature, which uses the [SHT31-DIS](https://sensirion.com/products/catalog/SHT31-DIS-B/) sensor. This Click board is interfaced with the microcontroller using the I<sup>2</sup>C interface.

<p align="center">
  <img width=auto height=auto src="images/shtclick.png">
  <br>Figure 3: SHT Click Board<br>
</p>

* [UV Click](https://www.mikroe.com/uv-click)

The UV Click board is used for sending an alert to the users indicating excessive ultraviolet (UV) radiation levels. This Click board is interfaced with the microcontroller using the SPI interface.

<p align="center">
  <img width=auto height=auto src="images/uvclick.png">
  <br>Figure 4: UV Click Board<br>
</p>

* Female-Female Jumper cables 

## Hardware Setup

The PIC18F56Q24 Curiosity Nano and Curiosity Nano Base for Click Boards are used as a development platform. The Curiosity Nano Base board is used to interface the UV, GPS3 and SHT Clicks with the PIC18F56Q24 microcontroller using the mikroBUS slots 1, 2 and 3 respectively.

<p align="center">
  <img width=auto height=auto src="images/hardwaresetup.png">
  <br>Figure 5: Hardware Setup<br>
</p>

## Pin Connections

In this code example, the click boards along with the MVIO pins of PIC18F56Q24 microcontroller, which are used for serial communication, are supplied with 2.8V through VDDIO2 pin and by using an external bench power supply. The table below shows the necessary connections between the PIC18F56Q24 microcontroller and the click boards. As explained in the table below, connect the PIC18F56Q24 Curiosity Nano board and Click boards using female-female jumper wires.

| Signal Description                                                                                 | MCU Pin  | Click Board Pin Description | Sensor Details             |
|----------------------------------------------------------------------------------------------------|----------|-----------------------------|----------------------------|
| SPI2 (SS)                                                                                          | RD1      | SS                          | UV Click mikroBUS Slot-1   |
| SPI2 (MISO/SDI)                                                                                    | RD1      | MOSI                        | UV Click mikroBUS Slot-1   |
| SPI2 (SCK)                                                                                         | RD0      | SCK                         | UV Click mikroBUS Slot-1   |
| UART1 (RX)                                                                                         | RC5      | TX                          | GPS3 Click mikroBUS Slot-2 |
| I<sup>2</sup>C1 (SCL)                                                                                         | RC3      | SCL                         | SHT Click mikroBUS Slot-3  |
| I<sup>2</sup>C1 (SDA)                                                                                         | RC4      | SDA                         | SHT Click mikroBUS Slot-3  |
| UART2 (RX)                                                                                         | RB4      | -                           | -                          |
| UART2 (TX)                                                                                         | RB5      | -                           | -                          |
| LED                                                                                                | RF2      | -                           | -                          |
| Pin provides power to the MVIO pins. Supply 2.8V to this pin using an external power supply source | V<sub>DDIO2</sub>   | -                           | -                          |



**Note:**
- *The Curiosity Nano Base Board can supply either 3.3V or 5V to the three mikroBUS slots through its power supply circuitry. Since it is not possible to power the click boards with 2.8V using the Curiosity Nano Base board power circuitry, isolate the 5V and 3.3V pins on the click boards from the Curiosity Nano Base board power circuitry, by removing these male pins from the pin header of the click boards*
- *Supply 2.8V to the click boards and V<sub>DDIO2</sub> pin of the microcontroller through an external power supply and using female-female jumper wires*


## Demonstration Setup

The application firmware is developed on a PIC18F56Q24 microcontroller and generated using MCC Melody and MPLAB X IDE. The implemented firmware runs on the PIC18F56Q24 Curiosity Nano development board. The microcontroller peripherals, SPI, UART, I2C, DMA, ADCC, and MVIO are used to implement the functions of the code example. These peripherals, which are configured as part of the peripheral initialization, do not require any changes to their configuration during the run-time.

The SPI peripheral is configured as Host with a 2 MHz clock, used to interface with the UV Click to receive environmental UV radiation data. The I2C peripheral is configured in Standard Mode (100 kHz), used to interface with the SHT Click to receive temperature and relative humidity data. The UART1 peripheral instance is used to interface with the GPS3 Click to receive positioning and navigation data. The data received on UART1 Receive register (U1RXB) is stored in a temporary buffer using the DMA module. The ADCC peripheral is configured in Basic mode with Fosc as clock source and “VDDIO2/10” is selected as its positive input channel, used to monitor voltage on the V<sub>DDIO2</sub> pin. The UART2 peripheral instance is used to input data from users via the terminal window of the data visualizer tool.

The below figure shows the firmware flow of the code example.

<p align="center">
  <img width=auto height=auto src="images/flowchart.png">
  <br>Figure 6: Firmware Flowchart<br>
</p>


## Details for Communication with Click Boards

### Communication with SHT Click

The raw data received from the sensor is then converted to human understandable data using below formulae.

<p align="center">
  <img width=auto height=auto src="images/formula.png">
  <br>Figure 7: Data Conversion Formulae<br>
</p>

where, S<sub>RH</sub> and S<sub>T</sub> represent the raw Relative Humidity and Temperature.

### Communication with GPS3 Click

In this code example, only GPRMC commands are considered. The respective bitfields are explained using an example as given below.

225446         : Time of fix 22:54:46 UTC
A              : Navigation receiver warning A = OK, V = warning
4916.45,N      : Latitude 49 deg. 16.45 min North
12311.12,W 	   : Longitude 123 deg. 11.12 min West
000.5	 	   : Speed over ground, Knots
054.7          : Course Made Good, True
191194         : Date of fix  19 November 1994
020.3,E        : Magnetic variation 20.3 deg East
*68            : Mandatory checksum

### Communication with UV Click

The data captured by the sensor is displayed in its raw form and is verified if it falls in the UV acceptable range of defined thresholds.

## Microcontroller Peripheral Configuration

| Peripherals               | Configuration                                                                                                                                                                                                                                                                                                                                                                                                  | Usage                                                                         |
|---------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------|
|    Clock Control   	 |Clock source –   HFINTOSC<br>HF Internal Clock – 64 MHz<br>Clock Divider   – 1 <br>Active Clock Tuning Update: Enabled                                                                                                                                                                                                                                                                                                        |    System  clock                                                                     |
|    ADCC	|Operating Mode: Basic Mode <br>Result Alignment: right<br>Positive Reference: VDD<br>Negative Reference: VSS<br>Positive Input Channel: VDDIO2_by_10<br>Clock Source: FOSC<br> Clock source Fosc<br>Clock Divider: FOSC/30<br>ADC Clock: 2.133 MHz | Used for monitoring V<sub>DDIO2</sub> voltage|
|UART1		|  Requested Baudrate: 9600<br>Enable Receive: Enabled   |   Used for receiving GPS sensor Data <br>  |                                                              
|UART2		| Requested Baudrate: 9600<br> Redirect printf to UART: Enabled<br>Enable Transmit: Enabled<br>Enable Receive: Enabled   | Used for sending and receiving data from terminal
|	 DMA1		  |    Start Trigger: U1RX<br>Abort Trigger: Software Interrupt<br>Source Region: SFR <br>Source Module: UART1<br>Source SFR: U1RXB<br>Source Message Size: 1<br>Destination Region: GPR<br>Destination Variable: destinationbuffer<br>Destination Size: 512<br>Destination Mode: incremented<br>Destination Message Size: 512<br>Interrupt Driven: Enabled<br>DMA Destination Count Interrupt: Enabled	|Used for saving the GPS data in a local buffer|																																																										
| I2C| Clock Source: Fosc<br>Fast Mode: Standard Mode<br>Requested Speed: 100 kHz<br>Interrupt Driven: Enabled<br>| Used for sending commands and receiving data from SHT sensor|
| SPI	| Requested Speed: 2 MHz<br>Mode: Mode 0<br>Data Input Sampled At: Middle<br>Clock Source: HFINTOSC<br>Clock Frequency: 64 MHz<br>			| Used for receiving data from UV sensor|
| MVIO| I/O Monitor Enable: Enabled<br>Hysteresis Enable: Enabled<br>LVD Trip point selection: disabled| Used for supplying the V<sub>DDIO2</sub> voltage to the microcontroller|

## Operation

1.	Interfacing sensors with PIC18F56Q24 using MVIO pins demonstration needs input from the user in the form of number to perform the defined functionality. The user gets an option to select input to provide respective functionalities depending on the input provided as seen in the firmware flowchart.
2.	The hardware connections are made as shown in the Hardware Setup. Power up the Curiosity Nano Adapter board using micro USB cable and provide external power to the MVIO pins via V<sub>DDIO2</sub>.
3.	Download the firmware available from the GitHub page link.
4.	Build the project using the latest version of tools as mentioned in the Software Tools section and load the generated hexadecimal file to the PIC18F56Q24 microcontroller.
5.	After running the program, the user will observe the default screen as shown in the below image.

<p align="center">
  <img width=auto height=auto src="images/defaultoutput.png">
  <br>Figure 8: Default Output Screen<br>
</p>

6.	The output will be displayed as shown in the below image if the user enters ‘A’.

<p align="center">
  <img width=auto height=auto src="images/i2coutput.png">
  <br>Figure 9: I2C Sensor Output<br>
</p>

7.	The output will be displayed as shown in the below image if the user enters ‘B’.
 
<p align="center">
  <img width=auto height=auto src="images/uartoutput1.png">
  <br>Figure 10: UART Sensor Output<br>
</p>

8.	The output will be displayed as shown in the below image if the user enters ‘C’.

<p align="center">
  <img width=auto height=auto src="images/spioutput.png">
  <br>Figure 11: SPI Sensor Output<br>
</p>

9.	The output will be displayed as shown in the below image if the user enters ‘D’.

<p align="center">
  <img width=auto height=auto src="images/vddiooutput.png">
  <br>Figure 12: V,sub>DDIO2</sub> Operating Voltage Output<br>
</p>

10.	The output will be displayed as shown in the below image if the user enters anything other than the provided inputs.

<p align="center">
  <img width=auto height=auto src="images/invalidoutput.png">
  <br>Figure 13: Invalid Input<br>
</p>

Note: 
*The input provided by the user are not case sensitive, so both upper and lower case are accepted as valid inputs.*

## Conclusion

The code example demonstrates the usage of the MVIO feature of the PIC18-Q24 microcontroller family by configuring these pins as serial communication pins for communication with external sensor modules, powered at a different voltage (Vsub>DDIO2</sub>) than the operating voltage supplied to PIC18F56Q24 microcontroller, without the need for an external level shifter. The integrated MVIO interface of PIC18-Q24 family greatly helps in reducing the BOM cost of end products by eliminating the need for an on-board level shifter IC.
