#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "spi-op.h"
#include "spi_tle920x.h"

#define PRINTF_NIBBLE_BINARY_FORMAT "%c%c%c%c"
#define PRINTF_NIBBLE_BINARY(nibble)  \
  ((nibble) & 0x08 ? '1' : '0'), \
  ((nibble) & 0x04 ? '1' : '0'), \
  ((nibble) & 0x02 ? '1' : '0'), \
  ((nibble) & 0x01 ? '1' : '0') 

static void ShowUsage(void)
{
    puts(
            "Usage:\n"
            "  diag\n"
            "  reset\n"
            "  rev\n"
            "  ctrl [<oldis> <sin> <sen> <sdir> <spwm>]\n"
    );
}

static void PrintDiag(unsigned char const diagnosis)
{
    printf("Outputs Enabled: %u\n", diagnosis & TLE920X_DIA_REG_EN_MASK);
    printf("Overtemperature Shutdown: %u\n", diagnosis & TLE920X_DIA_REG_OT_MASK);
    printf("Transmission Validation: %u\n", diagnosis & TLE920X_DIA_REG_TV_MASK);
    printf("Overcurrent Limited: %u\n", diagnosis & TLE920X_DIA_REG_CL_MASK);

    printf("Diagnosis: ");
    unsigned char dia = diagnosis & TLE920X_DIA_REG_DIA_MASK;
    switch (dia)
    {
        case TLE920X_DIA_REG_NO_FAILURE:
            printf("No Failure");
            break;
        case TLE920X_DIA_REG_SCG1:
            printf("OUT1 Short To Ground");
            break;
        case TLE920X_DIA_REG_SCB1:
            printf("OUT1 Short To Battery");
            break;
        case TLE920X_DIA_REG_OL:
            printf("Open Load");
            break;
        case TLE920X_DIA_REG_SCG2:
            printf("OUT2 Short To Ground");
            break;
        case TLE920X_DIA_REG_SCG1_SCG2:
            printf("OUT1 Short To Ground");
            printf("\n           ");
            printf("OUT2 Short To Ground");
            break;
        case TLE920X_DIA_REG_SCB1_SCG2:
            printf("OUT1 Short To Battery");
            printf("\n           ");
            printf("OUT2 Short To Ground");
            break;
        case TLE920X_DIA_REG_SCB2:
            printf("OUT2 Short To Battery");
            break;
        case TLE920X_DIA_REG_SCG1_SCB2:
            printf("OUT1 Short To Ground");
            printf("\n           ");
            printf("OUT2 Short To Battery");
            break;
        case TLE920X_DIA_REG_SCB1_SCB2:
            printf("OUT1 Short To Battery");
            printf("\n           ");
            printf("OUT2 Short To Battery");
            break;
        case TLE920X_DIA_REG_VSUV:
            printf("VS Undervoltage");
            break;
        default:
            printf("Undefined! (" PRINTF_NIBBLE_BINARY_FORMAT ")", PRINTF_NIBBLE_BINARY(dia));
    }
    printf("\n");
}

static void PrintControl(unsigned char const control)
{
    printf("Open Load Disconnect: %u\n", control & TLE920X_CTRL_REG_OLDIS_MASK);
    printf("SPI Control: %u\n", control & TLE920X_CTRL_REG_SIN_MASK);
    printf("SPI Control: !DIS: %u\n", control & TLE920X_CTRL_REG_SEN_MASK);
    printf("SPI Control: DIR: %u\n", control & TLE920X_CTRL_REG_SDIR_MASK);
    printf("SPI Control: PWM: %u\n", control & TLE920X_CTRL_REG_SPWM_MASK);
}

static int DoDiag()
{
    unsigned char diagnosis;
    if (!ReadDiagnosis(diagnosis))
    {
        printf("Operation failed.\n");
        return -EFAULT;
    }

    PrintDiag(diagnosis);

    return 0;
}

static int DoReset()
{
    unsigned char diagnosis;
    if (!ResetDiagnosis(diagnosis))
    {
        printf("Operation failed.\n");
        return -EFAULT;
    }

    PrintDiag(diagnosis);

    return 0;
}

static int DoRev()
{
    unsigned char revision;
    if (!ReadRevision(revision))
    {
        printf("Operation failed.\n");
        return -EFAULT;
    }

    unsigned char fixed = revision & TLE920X_REV_REG_FIXED_MASK;
    if (fixed != TLE920X_REV_REG_FIXED)
        printf("Fixed Revision Mismatch! (" PRINTF_NIBBLE_BINARY_FORMAT " != " PRINTF_NIBBLE_BINARY_FORMAT ")\n",
                PRINTF_NIBBLE_BINARY(fixed), PRINTF_NIBBLE_BINARY(TLE920X_REV_REG_FIXED));

    printf("Revision: %01x.\n", revision & TLE920X_REV_REG_REV_MASK);

    return 0;
}

static int DoCtrlRead()
{
    unsigned char control;
    if (!ReadControl(control))
    {
        printf("Operation failed.\n");
        return -EFAULT;
    }

    PrintControl(control);

    return 0;
}

static int DoCtrlWrite(int argc, char * const argv[])
{
    unsigned char control;

    if (!isdigit(argv[0][0]))
    {
        fprintf(stderr, "Please input a 0 or 1 Open Load Disconnect value!\n");
        return -EINVAL;
    }
    if (!isdigit(argv[1][0]))
    {
        fprintf(stderr, "Please input a 0 or 1 SPI Control value!\n");
        return -EINVAL;
    }
    if (!isdigit(argv[2][0]))
    {
        fprintf(stderr, "Please input a 0 or 1 SPI Control: !DIS value!\n");
        return -EINVAL;
    }
    if (!isdigit(argv[3][0]))
    {
        fprintf(stderr, "Please input a 0 or 1 SPI Control: DIR value!\n");
        return -EINVAL;
    }
    if (!isdigit(argv[4][0]))
    {
        fprintf(stderr, "Please input a 0 or 1 SPI Control: PWM value!\n");
        return -EINVAL;
    }

    control = (argv[0][0] << 4) &
        (argv[1][0] << 3) &
        (argv[2][0] << 2) &
        (argv[3][0] << 1) &
        (argv[4][0] << 0);

    if (!WriteControl(control))
    {
        printf("Operation failed.\n");
        return -EFAULT;
    }

    PrintControl(control);

    return 0;
}

int main(int const argc, char * const argv[])
{
    int argv_c = argc - 1, argv_p = 1;
    int ret = 0;

    printf("Simple CH347 SPI TLE920x Diagnosis Commander\n"
           "Forked from ch347-nor-prog by Chuanhong Guo <gch981213@gmail.com>\n"
           "Based on ch341prog by HackPascal <hackpascal@gmail.com>\n\n");

    int clk_khz = 500;
    SPIDeviceInit(&clk_khz);

    if (argc == 1)
    {
_show_usage:
        ShowUsage();
        goto cleanup;
    }

    if (!strcmp(argv[argv_p], "diag"))
    {
        ret = DoDiag();
        goto cleanup;
    }

    if (!strcmp(argv[argv_p], "reset"))
    {
        ret = DoReset();
        goto cleanup;
    }

    if (!strcmp(argv[argv_p], "rev"))
    {
        ret = DoRev();
        goto cleanup;
    }

    if (!strcmp(argv[argv_p], "ctrl"))
    {
        argv_c--;
        argv_p++;

        if (argv_c < 1)
        {
            ret = DoCtrlRead();
            goto cleanup;
        }

        if (argv_c < 5)
            goto _show_usage;

        ret = DoCtrlWrite(argv_c, argv + argv_p);
        goto cleanup;
    }

    goto _show_usage;

cleanup:
    SPIDeviceRelease();

    return ret;
}
