#ifndef PROJECTSMS_H_INCLUDED
#define PROJECTSMS_H_INCLUDED

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>



#define NAME_OF_FILE "Config.data"

extern unsigned short int comportNumber;
extern unsigned long int boundRate;
extern unsigned short int maxLendthOfMessage;
extern unsigned short int operatingSystem;

int GetConfigDataFromUser(void);
int WriteConfigDetailsToFile(void);
int GetConfigDataFromFile(void);
int ConnectWithModem(void);
int DissconnectWithModem(void);
int SendDataToModem(const char * data);
int ReceiveDataFromComport(char *receivedData,int numberOfCharacter);
int GetDataFromSMSListFile(void);
int SendSMS(void);
int DeleteSMSFile(void);
int ConfigureModem(void);
int ValidateMobileNumber(const char *mobileNumber);
#endif // PROJECTSMS_H_INCLUDED
