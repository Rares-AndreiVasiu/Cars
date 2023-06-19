#ifndef VARS
#define VARS

char magic[4];

char systemFormat; //32-bit or 64-bit

char endianness; // little or big endian

char versionELF;

char versionOS;

char versionABI;

/*
    Reserved padding bytes. Currently unused. 
    Should be filled with zeros and ignored when read. 
*/
char paddingBytes[8]; 

short int objType; //Identifies object file type. 

short int setArchitecture;

int originalVersionELF;

int targetArchitecture;

short int headerSize;

short int sizeofTableEntry;

short int numberEntriesHeaderTable;

short int sizeOfSectionHeaderEntry;

short int numberOfEntriesSectionHeaderTable;

short int indexOfSectionHeaderTableEntryWithSectionNames;

#endif //here we close the definition of the VARS