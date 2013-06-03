#include "ProjectSMS.h"

#define MAX_LENGTH_OF_MOBILE_NUMBER 11
#define NUMBER_HAS_TEXT !strpbrk(mobileNumber,"0123456789")

int ValidateMobileNumber(const char *mobileNumber)
{
    int lengthOfMobileNumber = strlen( mobileNumber );

    if( NUMBER_HAS_TEXT ) {
        return 1;
    }

    if((lengthOfMobileNumber != MAX_LENGTH_OF_MOBILE_NUMBER )
                                &&
        (lengthOfMobileNumber != MAX_LENGTH_OF_MOBILE_NUMBER - 1)) {
        return 1;
    }
    return 0;
}
