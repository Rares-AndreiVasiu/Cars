#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "vars.h"

#define DBG 0

void fatal(char *msg)
{
    perror(msg);

    exit(EXIT_FAILURE);
}

int main()
{
    FILE *f = fopen("/usr/bin/ls", "rb");

    if (!f)
    {
        fatal("fopen() failed!");
    }

    if (fread(&magic, 4, 1, f) != 1)
    {
        fatal("Error reading from the file");
    }

    /*
        now we check for ELF format
    */
    if ((magic[0] == 0x7F) && (magic[1] == 0x45) && (magic[2] == 0x4c) && (magic[3] == 0x46))
    {
        printf("This file is in ELF format!\n");
    }
    else
    {
        printf("This file is in the wrong format!\n");
    }

    /*
        We check for system settings, 32 or 64 bit format
    */

    if (fread(&systemFormat, 1, 1, f) != 1)
    {
        fatal("Error reading the 32 or 64 bit format!");
    }
    else
    {
        switch (systemFormat)
        {
            case 1:
            {
                printf("The format is 32-bit!\n");
                break;
            }
            case 2:
            {
                printf("The format is 64-bit!\n");
                break;
            }
        }
    }

    if (fread(&endianness, 1, 1, f) != 1)
    {
        fatal("Error reading the endian!\n");
    }
    else
    {
        switch (endianness)
        {
            case 1:
            {
                printf("Little endian\n");
                break;
            }
            case 2:
            {
                printf("Big endian\n");
                break;
            }
        }
    }

    if (fread(&versionELF, 1, 1, f) != 1)
    {
        fatal("Error reading the version of ELF!\n");
    }
    else
    {
        printf("Good version of ELF: 1\n");
    }

    if (fread(&versionOS, 1, 1, f) != 1)
    {
        fatal("Error reading the OS specs\n");
    }
    else
    {

#if DBG == 1
        printf("%x\n", versionOS);
#endif
        switch (versionOS)
        {
            case 0x00:
            {
                printf("System V\n");
                break;
            }

            case 0x01:
            {
                printf("HP-UX\n");
                break;
            }

            case 0x02:
            {
                printf("NetBSD\n");
                break;
            }

            case 0x03:
            {
                printf("Linux\n");
                break;
            }

            case 0x04:
            {
                printf("GNU Hurd\n");
                break;
            }

            case 0x06:
            {
                printf("Solaris\n");
                break;
            }

            case 0x07:
            {
                printf("AIX\n");
                break;
            }

            case 0x08:
            {
                printf("IRIX\n");
                break;
            }

            case 0x09:
            {
                printf("FreeBSD\n");
                break;
            }

            case 0x0A:
            {
                printf("Tru64\n");
                break;
            }

            case 0x0B:
            {
                printf("Novell Modesto\n");
                break;
            }

            case 0x0C:
            {
                printf("OpenBSD\n");
                break;
            }

            case 0x0D:
            {
                printf("OpenVMS\n");

                break;
            }

            case 0x0E:
            {
                printf("NonStop Kernel\n");
                break;
            }

            case 0x0F:
            {
                printf("AROS\n");
                break;
            }

            case 0x10:
            {
                printf("FenixOS\n");
                break;
            }

            case 0x11:
            {
                printf("Nuxi CloudADBI\n");
                break;
            }

            case 0x12:
            {
                printf("Sratus Technologies OpenVOS\n");

                break;
            }
        }
    }

    /*
        We get the ABI version
    */

    if (fread(&versionABI, 1, 1, f) != 1)
    {
        fatal("Error reading the ABI version");
    }
    else
    {
        printf("ABI version: %d\n", versionABI);
    }

    /*
        we ignore the padding bytes
    */

    if (fread(&paddingBytes, 7, 1, f) != 1)
    {
        fatal("Error reading the Padding Bytes");
    }

    if (fread(&objType, 2, 1, f) != 1)
    {
        fatal("Error reading the Object Type");
    }
    else
    {
        switch (objType)
        {
            case 0x00:
            {
                printf("Unknown\n");
                break;
            }

            case 0x01:
            {
                printf("Relocatable file\n");
                break;
            }

            case 0x02:
            {
                printf("Executable file\n");
                break;
            }

            case 0x03:
            {
                printf("Executable file\n");
                break;
            }

            case 0x04:
            {
                printf("Core file\n");
                break;
            }

            case 0xFE00:
            {
                printf("Reserved inclusive range. Operating system specific\n");
                break;
            }

            case 0xFEFF:
            {
                printf("Reserved inclusive range. Operating system specific\n");
                break;
            }

            case 0xFF00:
            {
                printf("Reserved inclusive range. Processor specific\n");
                break;
            }

            case 0xFFFF:
            {
                printf("Reserved inclusive range. Processor specific\n");
                break;
            }
        }
    }

    if(fread(&setArchitecture, 2, 1, f) != 1)
    {
        fatal("Error reading the instruction set architecure!");
    }
    else
    {
        printf("Set architecture: %d\n", setArchitecture);
        switch (setArchitecture)
        {
            case 0x00:
            {
                printf("No specific instruction set");
                break;
            }

            case 0x01:
            {
                printf("At&T WE 32100\n");
                break;
            }

            case 0x02:
            {
                printf("SPARC\n");
                break;
            }

            case 0x03:
            {
                printf("x86\n");
                break;
            }

            case 0x04:
            {
                printf("Motorola 68000(M68k)\n");
                break;
            }

            case 0x05:
            {
                printf("Motorola 88000(M88k)\n");
                break;
            }

            case 0x06:
            {
                printf("Intel MCU\n");
                break;
            }

            case 0x07:
            {
                printf("Intel 80860\n");
                break;
            }

            case 0x08:
            {
                printf("MIPS\n");
                break;
            }
            
            case 0x09:
            {
                printf("IBM System/370\n");
                break;
            }

            case 0x0A:
            {
                printf("MIPS RS3000 Little-endian\n");
                break;
            }

            case 0x0B:
            {
                printf("Reserved for future use\n");
                break;
            }

            case 0x0C:
            {
                printf("Reserved for future use\n");
                break;
            }
            
            case 0x0D:
            {
                printf("Reserved for future use\n");
                break;
            }

            case 0x0E:
            {
                printf("Hewlett-Packard PA-RISC\n");
                break;
            }

            case 0x0F:
            {
                printf("Reserved for future use\n");
                break;
            }

            case 0x13:
            {
                printf("Intel 80960\n");
                break;
            }

            case 0x14:
            {
                printf("PowerPC\n");
                break;
            }

            case 0x15:
            {
                printf("PowerPc (64-bit)\n");
                break;
            }

            case 0x16:
            {
                printf("S390, including S390x\n");
                break;
            }

            case 0x17:
            {
                printf("IBM SPU/SPC\n");
                break;
            }

            case 0x18:
            {
                printf("Reserved for future use\n");
                break;
            }

            case 0x19:
            {
                printf("Reserved for future use\n");
                break;
            }

            case 0x20:
            {
                printf("Reserved for future use\n");
                break;
            }

            case 0x21:
            {
                printf("Reserved for future use\n");
                break;
            }

            case 0x22:
            {
                printf("Reserved for future use\n");
                break;
            }

            case 0x23:
            {
                printf("Reserved for future use\n");
                break;
            }
            
            case 0x24:
            {
                printf("NEC V800\n");
                break;
            }

            case 0x25:
            {
                printf("Fujitsu FR20\n");
                break;
            }

            case 0x26:
            {
                printf("TRW RH-32\n");
                break;
            }

            case 0x27:
            {
                printf("Motorola RCE\n");
                break;
            }

            case 0x28:
            {
                printf("Arm\n");
                break;
            }

            case 0x29:
            {
                printf("Digital Alpha\n");
                break;
            }

            case 0x2A:
            {
                printf("SuperH\n");
                break;
            }

            case 0x2B:
            {
                printf("SPARC Vesion 9\n");
                break;
            }

            case 0x2C:
            {
                printf("Siemens TriCore embedded processor\n");
                break;
            }

            case 0x2D:
            {
                printf("Argonaut RISC Core\n");
                break;
            }

            case 0x2E:
            {
                printf("Hitachi H8/300\n");
                break;
            }

            case 0x2F:
            {
                printf("Hitachi H8/300H\n");
                break;
            }

            case 0x30:
            {
                printf("Hitachi H8S\n");
                break;
            }

            case 0x31:
            {
                printf("Hitachi H8/500\n");
                break;
            }

            case 0x32:
            {
                printf("IA-64\n");
                break;
            }

            case 0x33:
            {
                printf("Stanford MIPS-X\n");
                break;
            }

            case 0x34:
            {
                printf("Motorala ColdFire\n");
                break;
            }

            case 0x35:
            {
                printf("Motorola M68HC12\n");
                break;
            }

            case 0x36:
            {
                printf("Fujitsu MMA Multimedia Accelerator\n");
                break;
            }

            case 0x37:
            {
                printf("Siemens PCP\n");
                break;
            }

            case 0x38:
            {
                printf("Sony nCPU embedded RISC processor\n");
                break;
            }

            case 0x39:
            {
                printf("Denso NDR1 microprocessor\n");
                break;
            }

            case 0x3A:
            {
                printf("Motorola Star*Core processor\n");
                break;
            }

            case 0x3B:
            {
                printf("Toyota ME16 processor\n");
                break;
            }

            case 0x3C:
            {
                printf("STMicroelectronics ST100 processor\n");
                break;
            }

            case 0x3D:
            {
                printf("Advanced Logic Corp. TinyJ embedded processor family\n");
                break;
            }
            
            case 0x3E:
            {
                printf("AMD x86-64\n");
                break;
            }

            case 0x3F:
            {
                printf("Sony DSP Processor\n");
                break;
            }

            case 0x40:
            {
                printf("Digital Equipment Corp. PDP-10\n");
                break;
            }

            case 0x41:
            {
                printf("Digital Equipment Corp. PDP-11\n");
                break;
            }

            case 0x42:
            {
                printf("Siemes FX66 microcontroller\n");
                break;
            }

            case 0x43:
            {
                printf("STMicroelectronics ST9+ 8/16 bit microcontroller\n");
                break;
            }

            case 0x44:
            {
                printf("STMicroelectronics ST7 8-bit microcontroller\n");
                break;
            }

            case 0x45:
            {
                printf("Motorola MC68HC16 Microcontroller\n");
                break;
            }

            case 0x46:
            {
                printf("Motorola MC68HC11 Microcontroller\n");
                break;
            }

            case 0x47:
            {
                printf("Motorola MC68HC08 Microcontroller\n");
                break;
            }

            case 0x48:
            {
                printf("Motorola MC68HC05 Microcontroller\n");
                break;
            }

            case 0x49:
            {
                printf("Silicon Graphics Svx\n");
                break;
            }

            case 0x4A:
            {
                printf("STMicroelectronics ST19 8-bit microcontroller\n");
                break;
            }

            case 0x4B:
            {
                printf("Digital VAX\n");
                break;
            }

            case 0x4C:
            {
                printf("Axis Communications 32-bit embedded processor\n");
                break;
            }

            case 0x4D:
            {
                printf("Infineon Technologies 32-bit embedded processor\n");
                break;
            }

            case 0x4E:
            {
                printf("Element 14 64-bit DSP Processor\n");
                break;
            }

            case 0x4F:
            {
                printf("LSI Logic 16-bit DSP Processor\n");
                break;
            }

            case 0x8C:
            {
                printf("TMS320C6000 Family\n");
                break;
            }

            case 0xAF:
            {
                printf("MCST Elbrus e2k\n");
                break;
            }

            case 0xB7:
            {
                printf("Arm 64-bit (Armv8/AArch64)\n");
                break;
            }

            case 0xDC:
            {
                printf("Zilog Z80\n");
                break;
            }

            case 0xF3:
            {
                printf("RISC-V\n");
                break;
            }

            case 0xF7:
            {
                printf("Berkeley Packet Filter\n");
                break;
            }

            case 0x101:
            {
                printf("WDC 65C816\n");
                break;
            }
        }
    }

    //set to 1 for the original version of ELF
    if(fread(&originalVersionELF, 4, 1, f) != 1)
    {
        fatal("Error while reading the original version of ELF");
    }
    else
    {
        printf("Original version of ELF: 1\n");
    }

    /*
        this is the memory address if the entry point from where the process starts executing.
        The filed is either 32 or 64 bites long, depending on the format defined earlier. 
        If the file doesn't have an associated entry point, then this holds zero
    */
    if(systemFormat == 1)
    {
        int memoryAddress32;

        if(fread(&memoryAddress32, 4, 1, f) != 1)
        {
            fatal("Error reading the memory address point");
        }
        else
        {
            printf("The address of the entry point for 32-bit machine: %x\n", memoryAddress32);
        }
    }
    else
    {
        long long int memoryAddress64;

        if(fread(&memoryAddress64, 8, 1, f) != 1)
        {
            fatal("Error reading the memory address points");
        }
        else
        {
            printf("The address of the entry point for 64-bit machine: %llx\n", memoryAddress64);
        }
    }

    /*
        Points to the start of the program header table. It usually follows the file header
        immediately following this one, making the offset 0x34 or 0x40 for 32-but ELF executables and 64-bit
    */
    if(systemFormat == 1)
    {
        int startHeaderTable32;

        if(fread(&startHeaderTable32, 4, 1, f) != 1)
        {
            fatal("Error while reading the programm header for 32-bit");
        }
        else
        {
            printf("Pointing to the start of the program header table: %d\n", startHeaderTable32);
        }
    }
    else
    {
        long long int startHeaderTable64;

        if(fread(&startHeaderTable64, 8, 1, f) != 1)
        {
            fatal("Error while reading the programm header for 64-bit");
        }
        else
        {
            printf("Pointing to the start of the program header table: %llu\n", startHeaderTable64);
        }
    }

    /*
        points to the start of the start of section header
    */
    if(systemFormat == 1)
    {
        int pointsStartHeader32;

        if(fread(&pointsStartHeader32, 4, 1, f) != 1)
        {
            fatal("Error while reading the section header for 32-bit");
        }
        else
        {
            printf("Pointing to start of the section header table: %d\n", pointsStartHeader32);
        }
    }
    else
    {
        long long int pointsStartHeader64;

        if(fread(&pointsStartHeader64, 8, 1, f) != 1)
        {
            fatal("Error while reading the start of section header for 64-bit");
        }
        else
        {
            printf("Pointing to the start of the section header table: %llu\n", pointsStartHeader64);
        }
    }

    /*
        Interpretation of this filed depends on the target architecture
    */
    if(fread(&targetArchitecture, 4, 1, f) != 1)
    {
        fatal("Error while reading the target architecture");
    }
    else
    {
        printf("The target achitecture: %d\n", targetArchitecture);
    }

    /*
        contains the size of this header,normaly 64 Bytes for 64-bit and 53 Bytes
        for 32-bit format   
    */
    if(fread(&headerSize, 2, 1, f) != 1)
    {
        fatal("Error while reading the size of the header\n");
    }
    else
    {
        printf("The size of the header: %d\n", headerSize);
    }

    /*
        Contains the size of a program header table entry
    */

    if(fread(&sizeofTableEntry, 2, 1, f) != 1)
    {
        fatal("Error while reading the size of a program header table entry");
    }
    else
    {
        printf("The size of a program header entry table is: %d\n", sizeofTableEntry);
    }

    //read the number of entries in the program header table
    if(fread(&numberEntriesHeaderTable, 2, 1, f) != 1)
    {
        fatal("Error while reading the entries in the program header");
    }
    else
    {
        printf("The number of entries in the program header table: %d\n", numberEntriesHeaderTable);
    }

    //read the size of a section header table entry

    if(fread(&sizeOfSectionHeaderEntry, 2, 1, f) != 1)
    {
        fatal("Error while reading the size of a section table entry");
    }
    else
    {
        printf("The size of a section header table entry: %d\n", sizeOfSectionHeaderEntry);
    }

    //reads the number of entries in the section header table
    if(fread(&numberOfEntriesSectionHeaderTable, 2, 1, f) != 1)
    {
        fatal("Error while reading the number of entries in the section header table");
    }
    else
    {
        printf("The number of entries in the section header table: %d\n", numberOfEntriesSectionHeaderTable);
    }

    //reads the index of the section header table entry that contains the section names
    if(fread(&indexOfSectionHeaderTableEntryWithSectionNames, 2, 1, f) != 1)
    {
        fatal("Error while reading the index of the section header table entry that contains the section names");
    }
    else
    {
        printf("The index of the section header table entry that contains the section names: %d\n", indexOfSectionHeaderTableEntryWithSectionNames);
    }

    return 0;
}
