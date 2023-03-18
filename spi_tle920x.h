// Copyright © 2023 Nathan Schulte <nmschulte@desmas.net>

// Infineon TLE9201/TLE9202 SPI library
// https://www.infineon.com/dgdl/Infineon-TLE9202ED-DS-v01_00-EN.pdf?fileId=5546d462580663ef01583e8508e71921

#ifndef _SPI_TLE920X_H_
#define _SPI_TLE920X_H_

// NOTE: the first SPI response provided after power up is the device revisision number (RD_REV)
// NOTE: for any unspecified commands the device will respond with the content of the diagnosis register (RD_DIA)

// RD_DIA: Read Diagnosis Register
bool ReadDiagnosis(unsigned char & diagnosis);
// RES_DIA: Reset Diagnosis Register - resets and returns Diagnosis Register values
bool ResetDiagnosis(unsigned char & diagnosis);
// RD_REV: Read Device Revision Number
bool ReadRevision(unsigned char & revision);
// RD_CTRL: Read Control Register
bool ReadControl(unsigned char & control);
// WR_CTRL: Write Control Register - sets and returns Control Register values
bool WriteControl(unsigned char & control);
// WR_CTRL_RD_DIA: Write Control and Read Diagnosis - sets Control Register values and returns Diagnosis Register values
bool WriteControlReadDiagnosis(unsigned char const control, unsigned char & diagnosis);

#define TLE920X_RD_DIA          0b00000000
#define TLE920X_RES_DIA         0b10000000
#define TLE920X_RD_REV          0b00100000
#define TLE920X_RD_CTRL         0b01100000
#define TLE920X_WR_CTRL         0b11100000
#define TLE920X_WR_CTRL_RD_DIA  0b11000000

// Control Register: Command - bits 7:5, rw
#define TLE920X_CTRL_REG_CMD_MASK   0b11100000
// Control Register: Open Load Disconnect - bits 4, rw
#define TLE920X_CTRL_REG_OLDIS_MASK 0b00010000
// Control Register: SPI Control - bits 3, rw
#define TLE920X_CTRL_REG_SIN_MASK   0b00001000
// Control Register: SPI Control: !DIS - bits 2, rw
#define TLE920X_CTRL_REG_SEN_MASK   0b00000100
// Control Register: SPI Control: DIR - bits 1, rw
#define TLE920X_CTRL_REG_SDIR_MASK  0b00000010
// Control Register: SPI Control: PWM - bits 1, rw
#define TLE920X_CTRL_REG_SPWM_MASK  0b00000001

#define TLE920X_CTRL_REG_CMD_RD_CTRL        0b011
#define TLE920X_CTRL_REG_CMD_WR_CTRL_RD_DIA 0b110
#define TLE920X_CTRL_REG_CMD_WR_CTRL        0b111
#define TLE920X_CTRL_REG_OLDIS_CONNECT      0
#define TLE920X_CTRL_REG_OLDIS_DISCONNECT   1
#define TLE920X_CTRL_REG_SIN_OFF    0
#define TLE920X_CTRL_REG_SIN_ON     1
#define TLE920X_CTRL_REG_SEN_DISABLE    0
#define TLE920X_CTRL_REG_SEN_ENABLE     1
#define TLE920X_CTRL_REG_SDIR_FORWARD   0
#define TLE920X_CTRL_REG_SDIR_REVERSE   1
#define TLE920X_CTRL_REG_SPWM_LOW   0
#define TLE920X_CTRL_REG_SPWM_HIGH  1

// Diagnosis Register: Outputs Enabled - bits 7, r
#define TLE920X_DIA_REG_EN_MASK     1 << 7
// Diagnosis Register: Overtemperature Shutdown - bits 6, r
#define TLE920X_DIA_REG_OT_MASK     1 << 6
// Diagnosis Register: Transmission Validation (0) - bits 5, r
#define TLE920X_DIA_REG_TV_MASK     1 << 5
// Diagnosis Register: Overcurrent Limit - bits 4, r
#define TLE920X_DIA_REG_CL_MASK     1 << 4
// Diagnosis Register: Diagnosis Bits - bits 3)0, r
#define TLE920X_DIA_REG_DIA_MASK    0xf

#define TLE920X_DIA_REG_NO_FAILURE  0xf // -
#define TLE920X_DIA_REG_SCG1        0xe // latched
#define TLE920X_DIA_REG_SCB1        0xd // latched
#define TLE920X_DIA_REG_OL          0xc // not latched
#define TLE920X_DIA_REG_SCG2        0xb // latched
#define TLE920X_DIA_REG_SCG1_SCG2   0xa // latched
#define TLE920X_DIA_REG_SCB1_SCG2   0x9 // latched
#define TLE920X_DIA_REG_SCB2        0x7 // latched
#define TLE920X_DIA_REG_SCG1_SCB2   0x6 // latched
#define TLE920X_DIA_REG_SCB1_SCB2   0x5 // latched
#define TLE920X_DIA_REG_VSUV        0x3 // not latched

// Revision Register: Fixed Revision - bits 7:4, r
#define TLE920X_REV_REG_FIXED_MASK  0xf0
// Revision Register: Device Revision - bits 3:0, r
#define TLE920X_REV_REG_REV_MASK    0x0f

#define TLE920X_REV_REG_FIXED       0b0010

#endif /* _SPI_TLE920X_H_ */
