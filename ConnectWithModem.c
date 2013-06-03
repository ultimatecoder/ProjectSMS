#include "ProjectSMS.h"

#define TOTAL_LENGTH_OF_COM_PORT 10
#define MAX_DIGIT_OF_COMPORT_NUMBER 3
#define SEC_50 50
#define SEC_10 10

HANDLE hComport;

int ConnectWithModem(void) // Tested OK
{
    char prePath[]="\\\\.\\";
    /*If COM port number is grater than 9,Include "\\.\".Source MSDN.com :"CreateFile()"*/
    char COM[]="COM";
    char comportNumberInString[MAX_DIGIT_OF_COMPORT_NUMBER];
    char prePathAndComportNumber[TOTAL_LENGTH_OF_COM_PORT];

    unsigned long result;

    itoa( comportNumber, comportNumberInString, MAX_DIGIT_OF_COMPORT_NUMBER);

    strcat( prePathAndComportNumber, prePath);
    strcat( prePathAndComportNumber, COM);
    strcat( prePathAndComportNumber, comportNumberInString);

                          /*Ex: If COM32 then : "\\.\COM32" */
    hComport = CreateFile(  prePathAndComportNumber,
                            GENERIC_READ | GENERIC_WRITE,
                            0,
                            0,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            0 );

    result = GetLastError();

    if(hComport == INVALID_HANDLE_VALUE ||
       result == ERROR_FILE_NOT_FOUND ||
       result == ERROR_DEVICE_NOT_CONNECTED) {

        printf("\nValue of GetLastError() :%lu\nReturning while opening %s\n",GetLastError(),COM);
        CloseHandle( hComport );
        return 1;
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if( !GetCommState( hComport, &dcbSerialParams) ) {

        printf("\nReturning while opening device\n");
        CloseHandle( hComport );
        return 1;
    }

    dcbSerialParams.BaudRate = boundRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if( !SetCommState( hComport, & dcbSerialParams) ) {

        printf("\nReturning while setcommState\n");
        CloseHandle( hComport );
        return 1;
    }

    COMMTIMEOUTS timeouts = {0};
    //Let me Try to make this all zero then observ the effect on code.
    timeouts.ReadIntervalTimeout = SEC_50;
    timeouts.ReadTotalTimeoutConstant = SEC_50;
    timeouts.ReadTotalTimeoutMultiplier = SEC_10;
    timeouts.WriteTotalTimeoutConstant = SEC_50;
    timeouts.WriteTotalTimeoutMultiplier = SEC_10;

    if( !SetCommTimeouts( hComport, &timeouts) ) {

        printf("\nReturning while setcommtimeouts\n");
        CloseHandle( hComport );
        return 1;
    }

    return 0;
}

int DissconnectWithModem(void) //Tested OK
{
    if( CloseHandle(hComport) ) {
        return 0;
    }
    else {
        return 1;
    }
}

int SendDataToModem(const char *data) //Tested OK
{
    int lengthOfData = strlen(data);

    DWORD dwBytesWritten = 0;

    //if(!WriteFile(hComport,data,lengthOfData, &dwBytesRead,NULL) || GetLastError() == ERROR_IO_PENDING) {
    //WriteFile(Cport[comport_number], &byte, 1, (LPDWORD)((void *)&n), NULL);
    // Error in communications; report it.
    if( !WriteFile( hComport, data, lengthOfData, &dwBytesWritten, NULL) ) {

        printf("\nReturning from writing%lu\n",GetLastError());
        CloseHandle(hComport);
        return 1;
    }
    if( dwBytesWritten == 0 ) {

        printf("\nReturning from bytes read\n");
        CloseHandle( hComport );
        return 1;
    }
    return 0;
}

int ReceiveDataFromComport(char *receivedData, int numberOfCharacter) //Tested OK but Confusing in size of the character
{
    DWORD dwBytesRead = 0;
    if( !ReadFile( hComport, receivedData, numberOfCharacter, &dwBytesRead, NULL) || GetLastError() == ERROR_IO_PENDING) {
      //ReadFile(Cport[comport_number], buf, size, (LPDWORD)((void *)&n), NULL);
      // Error in communications; report it.
        printf("Returning from Reading File.%lu",GetLastError());

        CloseHandle( hComport );
        return 1;
    }
    if( dwBytesRead == 0 ) {

        printf("Returning from Reading File dwBytesRead.%lu",GetLastError());
        CloseHandle( hComport );
        return 1;
    }
    return 0;
}
