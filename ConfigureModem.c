#include "ProjectSMS.h"

#define MAX_LENGTH_OF_DATA_RECEIVING 50
#define SLEEP_1 Sleep(1000);
#define REPLAY_HAS_SOME_ERROR !strstr(buffer,"OK")
#define HANDSHAK "AT\r"
#define SET_ECHO_OFF "ATE0\r"
#define SELECT_TEXT_MODE "AT+CMGF=1\r"
#define SAVE_CHANGIES "AT&W\r"
#define DISPLAY_ERROR_CODE "AT+CMEE=1\r"

int ConfigureModem(void)
{
    char buffer[MAX_LENGTH_OF_DATA_RECEIVING];

    if( ConnectWithModem() ) {
        printf("\nUnable To connect %lu\n",GetLastError());
        return 1;
    }
    else {
        SendDataToModem( HANDSHAK );
        SLEEP_1
        ReceiveDataFromComport( buffer, MAX_LENGTH_OF_DATA_RECEIVING);
        if( REPLAY_HAS_SOME_ERROR ) {

            printf("\nReturning while first AT:%s GetLastError:%lu\n",buffer,GetLastError());
            return 1;
        }

        SendDataToModem( SET_ECHO_OFF );
        SLEEP_1
        ReceiveDataFromComport( buffer, MAX_LENGTH_OF_DATA_RECEIVING);
        if( REPLAY_HAS_SOME_ERROR ) {
            printf("\nReturning while setting echo off :%s GetLastError:%lu\n",buffer,GetLastError());
            return 1;
        }

        SendDataToModem( SELECT_TEXT_MODE );
        SLEEP_1
        ReceiveDataFromComport( buffer, MAX_LENGTH_OF_DATA_RECEIVING);
        if( REPLAY_HAS_SOME_ERROR ) {
            printf("\nReturning while CMGF %s..GetLastError() %lu :\n",buffer,GetLastError());
            return 1;
        }
        /*SendDataToModem( DISPLAY_ERROR_CODE );
        Sleep(1000);
        ReceiveDataFromComport(buffer,50);
        if( REPLAY_HAS_SOME_ERROR ) {
            printf("\nReturning while CMEE %s..GetLastError() %lu :\n",buffer,GetLastError());
            return 1;
        }
        */
        SendDataToModem( SAVE_CHANGIES );
        SLEEP_1
        ReceiveDataFromComport( buffer, MAX_LENGTH_OF_DATA_RECEIVING);
        if( REPLAY_HAS_SOME_ERROR ) {
            printf("\nReturning while saving %s GetLastError:%lu\n",buffer,GetLastError());
            return 1;
        }
    }

    if( DissconnectWithModem() ) {
        printf("\nReturning while disconnecting %lu\n",GetLastError());
        return 1;
    }
    return 0;
}
