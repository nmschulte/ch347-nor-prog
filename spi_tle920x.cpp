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
    if (SPIWrite(&command, 1))
        return SPIRead(&diagnosis, 1);
    return false;
}

bool ResetDiagnosis(unsigned char & diagnosis)
{
    unsigned char const command = TLE920X_RES_DIA;
    if (SPIWrite(&command, 1))
        return SPIRead(&diagnosis, 1);
    return false;
}

bool ReadRevision(unsigned char & revision)
{
    unsigned char const command = TLE920X_RD_REV;
    if (SPIWrite(&command, 1))
        return SPIRead(&revision, 1);
    return false;
}

bool ReadControl(unsigned char & control)
{
    unsigned char const command = TLE920X_RD_CTRL;
    if (SPIWrite(&command, 1))
        return SPIRead(&control, 1);
    return false;
}

bool WriteControl(unsigned char & control)
{
    unsigned char const command = TLE920X_WR_CTRL | (control & ~TLE920X_WR_CTRL);
    if (SPIWrite(&command, 1))
        return SPIRead(&control, 1);
    return false;
}

bool WriteControlReadDiagnosis(unsigned char control, unsigned char & diagnosis)
{
    unsigned char const command = TLE920X_WR_CTRL_RD_DIA | (control & ~TLE920X_WR_CTRL_RD_DIA);
    if (SPIWrite(&command, 1))
        return SPIRead(&diagnosis, 1);
    return false;
}
