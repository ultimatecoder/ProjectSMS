#include "ProjectSMS.h"


int WriteConfigDetailsToFile(void)
{
    FILE *file = fopen(NAME_OF_FILE,"w");

    if( file == NULL ) {

        return 1;
    }
    else {
        putw(operatingSystem,file);
        putc('\n',file);
        putw(comportNumber,file);
        putc('\n',file);
        putw(boundRate,file);
        putc('\n',file);
        putw(maxLendthOfMessage,file);
    }
    fclose(file);
    return 0;
}
