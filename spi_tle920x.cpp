// Copyright © 2023 Nathan Schulte <nmschulte@desmas.net>

// Infineon TLE9201/TLE9202 SPI library
// https://www.infineon.com/dgdl/Infineon-TLE9202ED-DS-v01_00-EN.pdf?fileId=5546d462580663ef01583e8508e71921

#include <time.h>
#include <cstring>

#include "spi-op.h"
#include "spi_tle920x.h"

bool ReadDiagnosis(unsigned char & diagnosis)
{
    unsigned char const command = TLE920X_RD_DIA;
    return SPIWriteThenRead(&command, 1, &diagnosis, 1);
}

bool ResetDiagnosis(unsigned char & diagnosis)
{
    unsigned char const command = TLE920X_RES_DIA;
    return SPIWriteThenRead(&command, 1, &diagnosis, 1);
}

bool ReadRevision(unsigned char & revision)
{
    unsigned char const command = TLE920X_RD_REV;
    return SPIWriteThenRead(&command, 1, &revision, 1);
}

bool ReadControl(unsigned char & control)
{
    unsigned char const command = TLE920X_RD_CTRL;
    return SPIWriteThenRead(&command, 1, &control, 1);
}

bool WriteControl(unsigned char & control)
{
    unsigned char const command = TLE920X_WR_CTRL | (control & ~TLE920X_WR_CTRL);
    return SPIWriteThenRead(&command, 1, &control, 1);
}

bool WriteControlReadDiagnosis(unsigned char control, unsigned char & diagnosis)
{
    unsigned char const command = TLE920X_WR_CTRL_RD_DIA | (control & ~TLE920X_WR_CTRL_RD_DIA);
    return SPIWriteThenRead(&command, 1, &diagnosis, 1);
}
