#include "ProjectSMS.h"

#define SMS_LIST "SMSList.txt"
#define UNSENT_SMS_LIST "UnsentSMSList.txt"
#define SLEEP_2_5 Sleep(2500);
#define MAX_LENGTH_OF_MOBILE_NUMBER 12
#define MAX_LENGTH_OF_MESSAGE 160
#define MAX_LENGTH_OF_ERROR_MESSAGE 100
#define MAX_LENGTH_OF_BUFFER 100
#define FETCH_ERROR_CODE strpbrk(error,"0123456789")
#define POINTER_ON_SMS smsPointer
#define MOBILE_NUMBER POINTER_ON_SMS -> mobileNumber
#define DATA POINTER_ON_SMS -> message
#define NEXT_MOBILENUMBER POINTER_ON_SMS -> next
#define CR "\r"
#define CTRL_Z ""
#define SENT_SMS pointerToPrevious
#define ERROR_RECEIVED !strstr(buffer,"ERROR")

typedef struct SMS SMS;

struct SMS{
    char mobileNumber[ MAX_LENGTH_OF_MOBILE_NUMBER ];
    char message[ MAX_LENGTH_OF_MESSAGE ];
    SMS * next;
};

static SMS start;
static void PrefixZeroToMobileNumber(char *mobileNumber);

int WriteErrorToFile(char *mobileNumber,char *error)
{
    time_t unixTime;
    struct tm *timeinfo;
    int errorNumber ,lengthOfMobileNumber = strlen(mobileNumber) ;
    char errorMessage[MAX_LENGTH_OF_ERROR_MESSAGE];


    if( FETCH_ERROR_CODE ) {
        errorNumber = atoi( FETCH_ERROR_CODE );
    }
    else if( lengthOfMobileNumber < 11 ) {
        errorNumber = 1000;
        mobileNumber[ lengthOfMobileNumber - 1 ] = '\0';
    }
    else {
        errorNumber = 1999;
    }
    printf("\nErrorNumber:%d\n",errorNumber);
    printf("\nThe Received String :%s\n",error);

    switch( errorNumber ) {
        case 512 :
            strcpy( errorMessage, "Manufacturer specific");
            break;
        case 500 :
            strcpy( errorMessage,"Unknown error");
            break;
        case 340 :
            strcat( errorMessage,"No +CNMA acknowledgement expected");
            break;
        case 332 :
            strcpy( errorMessage,"network timeout");
            break;
        case 331 :
            strcpy( errorMessage,"no network service");
            break;
        case 330 :
            strcpy( errorMessage,"SMSC address unknown");
            break;
        case 318 :
            strcpy( errorMessage,"SIM PUK2 required ");
            break;
        case 317 :
            strcpy( errorMessage,"SIM PIN2 required ");
            break;
        case 315 :
            strcpy( errorMessage,"SIM wrong ");
            break;
        case 314 :
            strcpy( errorMessage,"SIM busy ");
            break;
        case 313 :
            strcpy( errorMessage,"SIM failure ");
            break;
        case 312 :
            strcpy( errorMessage,"PH-SIM PIN required ");
            break;
        case 311 :
            strcpy( errorMessage,"SIM PIN required ");
            break;
        case 310 :
            strcpy( errorMessage,"SIM not inserted ");
            break;
        case 305 :
            strcpy( errorMessage,"invalid text mode parameter ");
            break;
        case 303 :
            strcpy( errorMessage,"invalid text mode parameter ");
            break;
        case 302 :
            strcpy( errorMessage,"Operation now Allowed");
            break;
        case 301 :
            strcpy( errorMessage,"SMS service of ME reserved ");
            break;
        case 300 :
            strcpy( errorMessage,"ME Failure");
            break;
        case 10  :
            strcpy( errorMessage,"Call bared");
            break;
        case 21 :
            strcpy( errorMessage,"Short message transfer rejected");
            break;
        case 27 :
            strcpy( errorMessage,"Destination out of service");
            break;
        case 28 :
            strcpy( errorMessage,"Unindentified subscriber");
            break;
        case 29 :
            strcpy( errorMessage,"Facility rejected");
            break;
        case 30 :
            strcpy( errorMessage,"Unknown subscriber");
            break;
        case 38 :
            strcpy( errorMessage,"Network out of order");
            break;
        case 41 :
            strcpy( errorMessage,"Temporary failure");
            break;
        case 42 :
            strcpy( errorMessage,"Congestion");
            break;
        case 47 :
            strcpy( errorMessage,"Recources unavailable");
            break;
        case 50 :
            strcpy( errorMessage,"Requested facility not subscribed");
            break;
        case 69 :
            strcpy( errorMessage,"Requested facility not implemented");
            break;
        case 81 :
            strcpy( errorMessage,"Invalid short message transfer reference value");
            break;
        case 95 :
            strcpy( errorMessage,"Invalid message unspecified");
            break;
        case 96 :
            strcpy( errorMessage,"Invalid mandatory information");
            break;
        case 97 :
            strcpy( errorMessage,"Message type non existent or not implemented");
            break;
        case 98 :
            strcpy( errorMessage,"Message not compatible with short message protocol");
            break;
        case 99 :
            strcpy( errorMessage,"Information element non-existent or not implemente");
            break;
        case 111 :
            strcpy( errorMessage,"Protocol error, unspecified");
            break;
        case 127 :
            strcpy( errorMessage,"Internetworking , unspecified");
            break;
        case 128:
            strcpy( errorMessage,"Telematic interworking not supported");
            break;
        case 129 :
            strcpy( errorMessage,"Short message Type 0 not supported");
            break;
        case 130 :
            strcpy( errorMessage,"Cannot replace short message");
            break;
        case 143 :
            strcpy( errorMessage,"Unspecified TP-PID error");
            break;
        case 144 :
            strcpy( errorMessage,"Data coding scheme (alphabet) not supported");
            break;
        case 145 :
            strcpy( errorMessage,"Message class not supported");
            break;
        case 159 :
            strcpy( errorMessage,"Unspecified TP-DCS error");
            break;
        case 160 :
            strcpy( errorMessage,"Command cannot be actioned");
            break;
        case 161 :
            strcpy( errorMessage,"Command unsupported");
            break;
        case 175 :
            strcpy( errorMessage,"Unspecified TP-Command error");
            break;
        case 176 :
            strcpy( errorMessage,"TPDU not supported");
            break;
        case 192 :
            strcpy( errorMessage,"SC busy");
            break;
        case 193 :
            strcpy( errorMessage,"No SC subscription");
            break;
        case 194 :
            strcpy( errorMessage,"SC system failure");
            break;
        case 195 :
            strcpy( errorMessage,"Invalid SME address");
            break;
        case 196 :
            strcpy( errorMessage,"Destination SME barred");
            break;
        case 197 :
            strcpy( errorMessage,"SM Rejected-Duplicate SM");
            break;
        case 198 :
            strcpy( errorMessage,"OTP-VPF not supported");
            break;
        case 199 :
            strcpy( errorMessage,"TP-VP not supported");
            break;
        case 208 :
            strcpy( errorMessage,"SIM SMS storage full");
            break;
        case 209 :
            strcpy( errorMessage,"No SMS storage capability in SIM");
            break;
        case 210 :
            strcpy( errorMessage,"Error in MS");
            break;
        case 211 :
            strcpy( errorMessage,"Memory Capacity Exceeded");
            break;
        case 212 :
            strcpy( errorMessage,"SIM Application Toolkit Busy");
            break;
        case 255 :
            strcpy( errorMessage,"Unspecified error cause");
            break;
        case 1 :
            strcpy( errorMessage,"Unassigned (unallocated) number");
            break;
        case 8 :
            strcpy( errorMessage,"Operator determined barring");
            break;
        case 1000:
            strcpy( errorMessage,"Invalid Mobile Number");
            break;
        default :
            strcpy( errorMessage,"Undefined Error occured");
            break;
    }

    printf("\nErrorMessage:%s\n",errorMessage);
    printf("M%s",mobileNumber);

    unixTime = time(NULL);
    timeinfo = localtime(&unixTime);


    FILE *file = fopen( UNSENT_SMS_LIST, "a");

    if(file == NULL) {
        return 1;
    }
    else {
        fputs( mobileNumber, file);
        fputc('\n', file);
        fputs( errorMessage, file);
        fputc('\n', file);
        fputs( asctime(timeinfo), file);
        fputc('\n', file);
        fclose( file );
    }
    return 0;
}

int DeleteSMSFile(void) //Tested OK
{
    FILE *file = fopen( SMS_LIST, "r");

    if(file == NULL) {
        return 1;
    }
    else {
        fclose(file);
        remove(SMS_LIST);
        return 0;
    }
}
int GetDataFromSMSListFile(void) //Tested OK
{
    SMS *POINTER_ON_SMS = &start;

    FILE *file = fopen( SMS_LIST, "r");
    if(file == NULL) {
        return 1;
    }
    else {
        while(fgets( MOBILE_NUMBER, MAX_LENGTH_OF_MOBILE_NUMBER, file) != NULL) {
            printf("-I Read  this :%s-", MOBILE_NUMBER);

            while( ValidateMobileNumber( MOBILE_NUMBER ) ) {
                WriteErrorToFile( MOBILE_NUMBER , "1000");
                fgets( DATA, MAX_LENGTH_OF_MESSAGE, file);
                fgets( MOBILE_NUMBER, MAX_LENGTH_OF_MOBILE_NUMBER, file);
            }

            if( MOBILE_NUMBER[0] != '0' ) {
                printf("-I don't have zero 0 :( :%s-", MOBILE_NUMBER);
                PrefixZeroToMobileNumber( MOBILE_NUMBER );
            }
            else {
                char character;

                character = fgetc( file );
                printf("-I read character %c-",character);
            }

            fgets( MOBILE_NUMBER, 160, file);
            printf("-Message : %s-", DATA );

            NEXT_MOBILENUMBER = malloc( sizeof( SMS ) );
            POINTER_ON_SMS = NEXT_MOBILENUMBER ;
            NEXT_MOBILENUMBER = NULL;
        }
        fclose( file );
    }
    smsPointer = &start;

    return 0;
}
int SendSMS(void) //Tested OK but need some improvement in performance.
{

    if( ConfigureModem() ) {
        printf("\nReturning while Configuring\n");
        return 1;
    }
    if( ConnectWithModem() ) {
        return 1;
        printf("\nReturning while connecting modem\n");
    }
    else {
        char buffer[ MAX_LENGTH_OF_BUFFER ];

        SMS *POINTER_ON_SMS = &start;
        SMS *SENT_SMS;

        do {

            /*if(ValidateMobileNumber(smsPointer->mobileNumber)) {
                printf("Invalid Mobile Number Found While readMobile Number:%s",smsPointer->mobileNumber);
                WriteErrorToFile(smsPointer->mobileNumber,"1000");
                pointerToPrevious = smsPointer;
                smsPointer = smsPointer->next;
                free(pointerToPrevious);
            }
            */
            SendDataToModem( "AT+CMGS=\""  );
            SendDataToModem( MOBILE_NUMBER );
            SendDataToModem( "\""          );
            SendDataToModem( CR            );
            SendDataToModem( DATA          );
            SendDataToModem( CTRL_Z        ); // CTRL + Z : ASCII value 026

            printf("##m:%s##MM%s",smsPointer->mobileNumber,smsPointer->message);
            printf("\nData Sent to modem.\n");

            SLEEP_2_5

            ReceiveDataFromComport( buffer, MAX_LENGTH_OF_BUFFER);
            printf("\nReceived Data From MODEM : %s\n",buffer);

            if( ERROR_RECEIVED ) {
                if( WriteErrorToFile( MOBILE_NUMBER, buffer) ) {
                    return 1;
                }
            }
            SENT_SMS = POINTER_ON_SMS;
            POINTER_ON_SMS = NEXT_MOBILENUMBER;
            free( SENT_SMS );
        }
        while( POINTER_ON_SMS != NULL );

        if( DissconnectWithModem() ) {
            return 1;
            printf("\nReturning while dissconnecting\n");
        }
    }
    return 0;
}

void PrefixZeroToMobileNumber(char *mobileNumber)
{
    mobileNumber[ strlen(mobileNumber) - 1 ] = '\0' ;
    strcpy( mobileNumber, strrev( strcat( strrev( mobileNumber), "0" )));
}
