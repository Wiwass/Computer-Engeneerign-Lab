#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN_ROW 255
#define MAX_LEN_MUN 32
#define MAX_NUM_MUN 100
#define DAYS_IN_YEAR 366

typedef struct {
    unsigned int day; /* between 1 and 31 */
    unsigned int month; /* between 1 and 12 */
    double levelF; /* rain fall */
} measure;

typedef struct {
    char municipality[MAX_LEN_MUN]; /*name of municipality*/
    measure surveys[DAYS_IN_YEAR]; /* max 366 findings, it is not certain that surveys take place on a daily basis */
    int nSurveys; /* actual number of data recorded in surveys */
} measuresMunicipality; /* data monitored during the year for a single municipality */
typedef measuresMunicipality surveysGlobal[MAX_NUM_MUN]; /* data monitored during the year for all 100 municipalities */


