#include "ProjectSMS.h"

int main()
{
    if(GetConfigDataFromFile()) {
        if(GetConfigDataFromUser()) {
            printf("\nThere is some error\n");
            getch();
            exit(0);
        }
    }
    else {
        printf("\nThe O.S.:%d\n",operatingSystem);
        printf("\nThe Comport:%d\n",comportNumber);
        printf("\nThe boundRate:%lu",boundRate);
        printf("\nMaximum length of Message:%d\n",maxLendthOfMessage);
    }
  /*  if(ConnectWithModem()) {
        printf("\nThere is some problem while connecting with modem!\n");
    }
    else {
        printf("\nConnected with modem successfully !\n");
    }
    */
    /*if(ConnectWithModem()) {
        printf("There is some problem while connecting with modem");
    }
    else {
        printf("Successfully connected with modem");
    }
    */

    if(GetDataFromSMSListFile()) {
        printf("\nUnable to receive data from SMSList.txt\n");
    }
    else {
        printf("\nData from SMSList Received successfully!\n");
        if(SendSMS()) {
            printf("\nSome Error occured while sending sms \n");
        }
        else {
            printf("\nData sent successfully !\n");

            if(DeleteSMSFile()) {
                printf("There is some error while deleting SMS file");
            }
            else {
                printf("The SMS file is deleted successfully!");
            }
        }
    }

    getchar();
    return 0;
}
