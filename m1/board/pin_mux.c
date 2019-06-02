/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v5.0
processor: LPC54114J256
package_id: LPC54114J256BD64
mcu_data: ksdk2_0
processor_version: 5.0.1
board: LPCXpresso54114
pin_labels:
- {pin_num: '59', pin_signal: PIO0_19/FC5_SCK/SCT0_OUT1/CTIMER0_MAT1, label: 'J1[9]/J2[8]/U5[6]/P0_19-FC5_SCK-SPIFI_CSn', identifier: SPI_FLASH_SCK;L_SPEED}
- {pin_num: '61', pin_signal: PIO0_21/CLKOUT/FC0_TXD_SCL_MISO/CTIMER3_MAT0, label: 'J2[2]/P0_21-CLKOUT-SPIFI_CLK', identifier: R_SPEED}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_iocon.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: cm4, enableClock: 'true'}
- pin_list:
  - {pin_num: '31', peripheral: FLEXCOMM0, signal: RXD_SDA_MOSI, pin_signal: PIO0_0/FC0_RXD_SDA_MOSI/FC3_CTS_SDA_SSEL0/CTIMER0_CAP0/SCT0_OUT3, mode: inactive, invert: disabled,
    glitch_filter: disabled, slew_rate: standard, open_drain: disabled}
  - {pin_num: '32', peripheral: FLEXCOMM0, signal: TXD_SCL_MISO, pin_signal: PIO0_1/FC0_TXD_SCL_MISO/FC3_RTS_SCL_SSEL1/CTIMER0_CAP1/SCT0_OUT1, mode: inactive, invert: disabled,
    glitch_filter: disabled, slew_rate: standard, open_drain: disabled}
  - {pin_num: '30', peripheral: SCT0, signal: 'OUT, 4', pin_signal: PIO1_10/FC6_TXD_SCL_MISO_WS/SCT0_OUT4/FC1_SCK/USB0_FRAME, mode: inactive, invert: disabled, glitch_filter: disabled,
    slew_rate: standard, open_drain: disabled}
  - {pin_num: '11', peripheral: SCT0, signal: 'OUT, 2', pin_signal: PIO0_29/FC1_RXD_SDA_MOSI/SCT0_OUT2/CTIMER0_MAT3/CTIMER0_CAP1/CTIMER0_MAT1/ADC0_0, mode: inactive,
    invert: disabled, glitch_filter: disabled, open_drain: disabled}
  - {pin_num: '57', peripheral: SCT0, signal: 'OUT, 7', pin_signal: PIO1_14/FC2_RXD_SDA_MOSI/SCT0_OUT7/FC7_TXD_SCL_MISO_WS}
  - {pin_num: '62', peripheral: SCT0, signal: 'OUT, 5', pin_signal: PIO1_15/PDM0_CLK/SCT0_OUT5/CTIMER1_CAP3/FC7_CTS_SDA_SSEL0}
  - {pin_num: '58', peripheral: GPIO, signal: 'PIO0, 18', pin_signal: PIO0_18/FC5_TXD_SCL_MISO/SCT0_OUT0/CTIMER0_MAT0, direction: INPUT, mode: pullUp}
  - {pin_num: '59', peripheral: GPIO, signal: 'PIO0, 19', pin_signal: PIO0_19/FC5_SCK/SCT0_OUT1/CTIMER0_MAT1, identifier: L_SPEED, direction: INPUT}
  - {pin_num: '61', peripheral: GPIO, signal: 'PIO0, 21', pin_signal: PIO0_21/CLKOUT/FC0_TXD_SCL_MISO/CTIMER3_MAT0, direction: INPUT}
  - {pin_num: '60', peripheral: GPIO, signal: 'PIO0, 20', pin_signal: PIO0_20/FC5_RXD_SDA_MOSI/FC0_SCK/CTIMER3_CAP0, direction: INPUT}
  - {pin_num: '4', peripheral: GPIO, signal: 'PIO0, 26', pin_signal: PIO0_26/FC4_CTS_SDA_SSEL0/CTIMER0_CAP3, direction: INPUT}
  - {pin_num: '3', peripheral: GPIO, signal: 'PIO0, 25', pin_signal: PIO0_25/FC4_RTS_SCL_SSEL1/FC6_CTS_SDA_SSEL0/CTIMER0_CAP2/CTIMER1_CAP1, direction: INPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
/* Function assigned for the Cortex-M4F */
void BOARD_InitPins(void)
{
    /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */
    CLOCK_EnableClock(kCLOCK_Iocon);
    /* Enables the clock for the GPIO0 module */
    CLOCK_EnableClock(kCLOCK_Gpio0);

    gpio_pin_config_t SPI_FLASH_MISO_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_18 (pin 58)  */
    GPIO_PinInit(BOARD_INITPINS_SPI_FLASH_MISO_GPIO, BOARD_INITPINS_SPI_FLASH_MISO_PORT, BOARD_INITPINS_SPI_FLASH_MISO_PIN, &SPI_FLASH_MISO_config);

    gpio_pin_config_t L_SPEED_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_19 (pin 59)  */
    GPIO_PinInit(BOARD_INITPINS_L_SPEED_GPIO, BOARD_INITPINS_L_SPEED_PORT, BOARD_INITPINS_L_SPEED_PIN, &L_SPEED_config);

    gpio_pin_config_t SPI_FLASH_MOSI_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_20 (pin 60)  */
    GPIO_PinInit(BOARD_INITPINS_SPI_FLASH_MOSI_GPIO, BOARD_INITPINS_SPI_FLASH_MOSI_PORT, BOARD_INITPINS_SPI_FLASH_MOSI_PIN, &SPI_FLASH_MOSI_config);

    gpio_pin_config_t R_SPEED_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_21 (pin 61)  */
    GPIO_PinInit(BOARD_INITPINS_R_SPEED_GPIO, BOARD_INITPINS_R_SPEED_PORT, BOARD_INITPINS_R_SPEED_PIN, &R_SPEED_config);

    gpio_pin_config_t FC4_SCLX_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_25 (pin 3)  */
    GPIO_PinInit(BOARD_INITPINS_FC4_SCLX_GPIO, BOARD_INITPINS_FC4_SCLX_PORT, BOARD_INITPINS_FC4_SCLX_PIN, &FC4_SCLX_config);

    gpio_pin_config_t FC4_SDAX_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PIO0_26 (pin 4)  */
    GPIO_PinInit(BOARD_INITPINS_FC4_SDAX_GPIO, BOARD_INITPINS_FC4_SDAX_PORT, BOARD_INITPINS_FC4_SDAX_PIN, &FC4_SDAX_config);

    const uint32_t port0_pin0_config = (/* Pin is configured as FC0_RXD_SDA_MOSI */
                                        IOCON_PIO_FUNC1 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN0 (coords: 31) is configured as FC0_RXD_SDA_MOSI */
    IOCON_PinMuxSet(IOCON, 0U, 0U, port0_pin0_config);

    const uint32_t port0_pin1_config = (/* Pin is configured as FC0_TXD_SCL_MISO */
                                        IOCON_PIO_FUNC1 |
                                        /* No addition pin function */
                                        IOCON_PIO_MODE_INACT |
                                        /* Input function is not inverted */
                                        IOCON_PIO_INV_DI |
                                        /* Enables digital function */
                                        IOCON_PIO_DIGITAL_EN |
                                        /* Input filter disabled */
                                        IOCON_PIO_INPFILT_OFF |
                                        /* Standard mode, output slew rate control is enabled */
                                        IOCON_PIO_SLEW_STANDARD |
                                        /* Open drain is disabled */
                                        IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN1 (coords: 32) is configured as FC0_TXD_SCL_MISO */
    IOCON_PinMuxSet(IOCON, 0U, 1U, port0_pin1_config);

    IOCON->PIO[0][18] = ((IOCON->PIO[0][18] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_MODE_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT018 (pin 58) is configured as PIO0_18. */
                         | IOCON_PIO_FUNC(PIO018_FUNC_ALT0)

                         /* Selects function mode (on-chip pull-up/pull-down resistor control).
                          * : Pull-up.
                          * Pull-up resistor enabled. */
                         | IOCON_PIO_MODE(PIO018_MODE_PULL_UP)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO018_DIGIMODE_DIGITAL));

    IOCON->PIO[0][19] = ((IOCON->PIO[0][19] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT019 (pin 59) is configured as PIO0_19. */
                         | IOCON_PIO_FUNC(PIO019_FUNC_ALT0)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO019_DIGIMODE_DIGITAL));

    IOCON->PIO[0][20] = ((IOCON->PIO[0][20] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT020 (pin 60) is configured as PIO0_20. */
                         | IOCON_PIO_FUNC(PIO020_FUNC_ALT0)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO020_DIGIMODE_DIGITAL));

    IOCON->PIO[0][21] = ((IOCON->PIO[0][21] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT021 (pin 61) is configured as PIO0_21. */
                         | IOCON_PIO_FUNC(PIO021_FUNC_ALT0)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO021_DIGIMODE_DIGITAL));

    IOCON->PIO[0][25] = ((IOCON->PIO[0][25] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT025 (pin 3) is configured as PIO0_25. */
                         | IOCON_PIO_FUNC(PIO025_FUNC_ALT0)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO025_DIGIMODE_DIGITAL));

    IOCON->PIO[0][26] = ((IOCON->PIO[0][26] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT026 (pin 4) is configured as PIO0_26. */
                         | IOCON_PIO_FUNC(PIO026_FUNC_ALT0)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO026_DIGIMODE_DIGITAL));

    const uint32_t port0_pin29_config = (/* Pin is configured as SCT0_OUT2 */
                                         IOCON_PIO_FUNC2 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT0 PIN29 (coords: 11) is configured as SCT0_OUT2 */
    IOCON_PinMuxSet(IOCON, 0U, 29U, port0_pin29_config);

    const uint32_t port1_pin10_config = (/* Pin is configured as SCT0_OUT4 */
                                         IOCON_PIO_FUNC3 |
                                         /* No addition pin function */
                                         IOCON_PIO_MODE_INACT |
                                         /* Input function is not inverted */
                                         IOCON_PIO_INV_DI |
                                         /* Enables digital function */
                                         IOCON_PIO_DIGITAL_EN |
                                         /* Input filter disabled */
                                         IOCON_PIO_INPFILT_OFF |
                                         /* Standard mode, output slew rate control is enabled */
                                         IOCON_PIO_SLEW_STANDARD |
                                         /* Open drain is disabled */
                                         IOCON_PIO_OPENDRAIN_DI);
    /* PORT1 PIN10 (coords: 30) is configured as SCT0_OUT4 */
    IOCON_PinMuxSet(IOCON, 1U, 10U, port1_pin10_config);

    IOCON->PIO[1][14] = ((IOCON->PIO[1][14] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT114 (pin 57) is configured as SCT0_OUT7. */
                         | IOCON_PIO_FUNC(PIO114_FUNC_ALT3)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO114_DIGIMODE_DIGITAL));

    IOCON->PIO[1][15] = ((IOCON->PIO[1][15] &
                          /* Mask bits to zero which are setting */
                          (~(IOCON_PIO_FUNC_MASK | IOCON_PIO_DIGIMODE_MASK)))

                         /* Selects pin function.
                          * : PORT115 (pin 62) is configured as SCT0_OUT5. */
                         | IOCON_PIO_FUNC(PIO115_FUNC_ALT2)

                         /* Select Analog/Digital mode.
                          * : Digital mode. */
                         | IOCON_PIO_DIGIMODE(PIO115_DIGIMODE_DIGITAL));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
