#include "ProjectSMS.h"

unsigned short int comportNumber;
unsigned long int boundRate;
unsigned short int maxLendthOfMessage;
unsigned short int operatingSystem;

static  void    GetBoundRateFromUser(void);
static  void    GetOperatingSystemFromUser(void);
static  void    GetComportNumberFromUserForLinux(void);
static  void    GetComportNumberFromUserForWindows(void);
static  void    GetMaxLengthOfMessageFromUser(void);

int GetConfigDataFromUser(void)
{
    GetOperatingSystemFromUser();
    if(operatingSystem) {
        GetComportNumberFromUserForLinux();
    }
    else {
        GetComportNumberFromUserForWindows();
    }
    GetBoundRateFromUser();
    GetMaxLengthOfMessageFromUser();
    if(WriteConfigDetailsToFile()) {
            return 1;
    }
    return 0;
}
static void GetMaxLengthOfMessageFromUser(void) // Tested OK
{
    char tempraryInput[3];

    GoToMessageLength:

    printf("\nPlease Enter the Length of message(MAXIMUM is 160):");
    scanf("%s",tempraryInput);
    fflush(stdin);

    if(atoi(tempraryInput) > 160) {
        printf("\nPlease Enter value below 160.");
        goto GoToMessageLength;
    }
    else if(atoi(tempraryInput) <= 0) {
        printf("\nPlease Enter the value grater than zero(0).");
        goto GoToMessageLength;
    }
    else {
        maxLendthOfMessage = atoi(tempraryInput);
    }
}
static void GetBoundRateFromUser(void) // Tested OK
{
    char tempraryInput;

    GetBRate:

    printf("\nPress 1 to set 2400 bps.");
    printf("\nPress 2 to set 4800 bps.");
    printf("\nPress 3 to set 9600 bps.");
    printf("\nPress 4 to set 19200 bps.\n");

    scanf("%c",&tempraryInput);
    fflush(stdin);

    switch(tempraryInput - 48) {
        case 1:
            boundRate = 2400;
            break;
        case 2:
            boundRate = 4800;
            break;
        case 3:
            boundRate = 9600;
            break;
        case 4:
            boundRate = 19200;
            break;
        default:
            printf("\nPlease Enter any valid Input !");
            goto GetBRate;
            break;
    }
}
static void GetOperatingSystemFromUser(void) //Tested OK
{
    char tempraryInput;

    GotoOperatingSystem:

    printf("\nPress 1 for Windows Operating System");
    printf("\nPress 2 for Linux Operating System\n");

    scanf("%c",&tempraryInput);
    fflush(stdin);

    switch(tempraryInput - 48) {
        case 1:
            operatingSystem=0;
            break;
        case 2:
            operatingSystem=1;
            break;
        default:
            printf("\nPlease Enter any valid input!");
            goto GotoOperatingSystem;
            break;
    }
}
static void GetComportNumberFromUserForLinux(void) //Tested OK
{
    int i;
    char tempraryInput[2];

    GotoGetComport:

    for(i = 0; i < 16; i++)
        printf("\nPress %d for selecting ttyS%d",i+1,i);

    printf("\n");
    scanf("%s",tempraryInput);
    fflush(stdin);

    if((atoi(tempraryInput) >= 1) && (atoi(tempraryInput) <= 16)) {
        comportNumber = atoi(tempraryInput);
    }
    else {
        printf("\nPlease Enter valid input!");
        goto GotoGetComport;
    }
}
static void GetComportNumberFromUserForWindows(void) // Tested OK
{
    int i;
    char tempraryInput[3];

    GotoGetComportFromUser:

    for(i = 0; i < 256; i++)
        printf("\nPress %d for selecting COM%d",i+1,i+1);
    printf("\n");
    scanf("%s",tempraryInput);
    fflush(stdin);

    if((atoi(tempraryInput) >= 1 ) && (atoi(tempraryInput) <= 256)) {
        comportNumber=atoi(tempraryInput);
    }
    else {
        printf("\nPlease Enter valid input!\n");
        goto GotoGetComportFromUser;
    }
}
