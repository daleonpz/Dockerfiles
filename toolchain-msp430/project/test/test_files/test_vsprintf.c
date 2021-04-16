#include <unity.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static char _buffer[256];

void get_command(char* buf, const char *command, ...)
{
    va_list args;
    va_start(args, command);
    vsprintf(buf, command, args);
    va_end(args);
}

void setUp(void)
{
}

void tearDown()
{
}

void test_vsprintf_noArgs()
{
    get_command(_buffer, "AT+CFUN=1");
    TEST_ASSERT_EQUAL_STRING("AT+CFUN=1", _buffer);
}

void test_vsprinft_withArgs()
{
    char mqtt_broker_url[] = "broker.hivemq.com";
    int mqtt_broker_port = 1883;
    get_command(_buffer, "AT+QMTOPEN=0,\"%s\",%d",mqtt_broker_url, mqtt_broker_port);
    TEST_ASSERT_EQUAL_STRING("AT+QMTOPEN=0,\"broker.hivemq.com\",1883", _buffer);
}

void test_vsprintf_ResultSize()
{
    size_t strlenght; 
    get_command(_buffer, "12345");
    strlenght = strlen(_buffer);
    TEST_ASSERT_EQUAL_INT(5, strlenght);

}

void test_strstr_NULL()
{
    char inputStr[] = " Quectel_Ltd\r\n Quectel_M95\r\n\r\n Revision: M95FAR02A08\r\n\r\nOK\r\n";
    char pattern[] = "";

    char *pos ;
    pos =  strstr(inputStr, pattern);
    TEST_ASSERT_NOT_NULL(pos);
}

void test_strstr_found()
{
    char inputStr[] = " Quectel_Ltd\r\n Quectel_M95\r\n\r\n Revision: M95FAR02A08\r\n\r\nOK\r\n";
    char pattern[] = "\r\nOK\r\n";

    char *pos ;
    pos =  strstr(inputStr, "\r\nOK\r\n");
    TEST_ASSERT_NOT_NULL(pos);
}

void test_strstr_notfound()
{
    char inputStr[] = " Quectel_Ltd\r\n  \
                       Quectel_M95\r\n\r\n Revision: M95FAR02A08\r\n\r\nO K\r\n";
    char pattern[] = "\r\nOK\r\n";

    char *pos ;
    pos =  strstr(inputStr, pattern);
    TEST_ASSERT_NULL(pos);
}


void test_strstr_LongString()
{
    char inputStr[] =" Call Ready\r\n \
                      \r\n \
                      +QOPS: 1,\"Telekom Deutschland GmbH\",\"TDG\",\"26201\"\r\n \
                      \r\n \
                      1,972D,0592,17,21,57\r\n \
                      \r\n \
                      2,972D,5344,0F,7,61\r\n \
                      \r\n \
                      3,972D,F336,3E,7,77\r\n \
                      \r\n \
                      4,972D,DE21,3E,4,64\r\n \
                      \r\n \
                      5,972D,2BD6,12,3,72\r\n \
                      \r\n \
                      +QOPS: 1,\"Vodafone\",\"Vodafone\",\"26202\"\r\n \
                      \r\n \
                      1,10AC,5265,37,16,42\r\n \
                      \r\n \
                      2,10AC,1DBB,1C,28,6\r\n \
                      \r\n \
                      3,10AC,1DC6,1E,14,44\r\n \
                      \r\n \
                      4,10AC,5318,3B,15,43\r\n \
                      \r\n \
                      5,10AC,0AE8,34,12,45\r\n \
                      \r\n \
                      6,10AC,525B,2A,11,48\r\n \
                      \r\n \
                      7,10AC,52C7,2F,11,49\r\n \
                      \r\n \
                      8,10AC,1DBC,31,10,2\r\n \
                      \r\n \
                      +QOPS: 1,\"E-Plus\",\"E-Plus\",\"26203\"\r\n \
                      \r\n \
                      1,8CDC,6724,3E,26,983\r\n \
                      \r\n \
                      2,8CDC,5793,1E,16,755\r\n \
                      \r\n \
                      3,8CDD,5980,18,23,669\r\n \
                      \r\n \
                      4,8CDD,0B60,3A,17,753\r\n \
                      \r\n \
                      5,8CDC,1904,3A,13,1000\r\n \
                      \r\n \
                      6,8CDC,678B,3B,14,668\r\n \
                      \r\n \
                      7,8CDC,5791,1F,13,977\r\n \
                      \r\n \
                      8,8CDD,B506,1C,9,985\r\n \
                      \r\nOK\r\n \
                      \r\n \
                      \r\n \
                      ";

    char pattern[] = "\r\nOK\r\n";

    char *pos ;
    pos =  strstr(inputStr, pattern);
    TEST_ASSERT_NOT_NULL(pos);
}


#include <inttypes.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define NCHARS(x)   (strlen(x) + 1)

void mqtt_create_path(uint8_t *path,uint16_t size, const char *command, ...)
{
    va_list args;

    uint8_t* str = path;
    va_start(args, command);

    vsnprintf(str, size, command, args);
    va_end(args);

    path = str;
}


void test_strncat_mqtt(void)
{
    uint8_t mqtt_topic[] = "Heating";
    uint8_t mqtt_topic_prefix[] = "poc/1/";
    uint32_t timestamp = 15678915;

    uint8_t mqtt_full_topic[100];
    mqtt_create_path(mqtt_full_topic, 100,"%s/%s/%s/%" PRIu32, "poc", "serial",mqtt_topic, timestamp);

    TEST_ASSERT_EQUAL_STRING("poc/serial/Heating/15678915", mqtt_full_topic);
}

#define __USE_XOPEN
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

// input: date -> "09/01/04,00:19:43+00\""
static uint32_t modulo_quotient(uint32_t *numer, uint32_t denom) 
{
    uint32_t quot = *numer / denom;
    *numer %= denom;
    if (*numer < 0) 
    {
        *numer += denom;
        --quot;
    }
    return quot;
}

static inline bool is_leap(uint32_t year) 
{
    year %= 400;
    if (year < 0)
        year += 400;
    return ((year % 4) == 0 && (year % 100) != 0) || year == 100;
}

static inline const short *get_months_cumulative(uint32_t year) 
{
    static const short leap[13] = {
        0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366,
    };
    static const short common[13] = {
        0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365,
    };
    return is_leap(year) ? leap : common;
}

static uint32_t  __mktime_utc(const struct tm *tm) 
{
    // Normalize nanoseconds.
    uint32_t sec = (uint32_t)tm->tm_sec + (uint32_t)tm->tm_min * 60 +
        (uint32_t)tm->tm_hour * 3600;

    // Normalize and eliminate months.
    uint32_t mon = tm->tm_mon;
    uint32_t year = tm->tm_year + modulo_quotient(&mon, 12);
    uint32_t yday = (uint32_t)tm->tm_mday + get_months_cumulative(year)[mon] - 1;

    // We need to ensure that the year is at least 70 for the rounding in
    // the day computation to work properly. Temporarily normalize the
    // year number by using an additional era counter.
    uint32_t era = year / 400 - 2;
    uint32_t local_year = year % 400 + 800;

    // Compute days since epoch.
    uint32_t day = yday + (local_year - 70) * 365 + (local_year - 69) / 4 -
        (local_year - 1) / 100 + (local_year + 299) / 400 + era * 146097;

    // Merge results together.
    return ( sec + day * 86400);
}


int get_value_dateformat(uint8_t *input)
{
    uint32_t value;
    uint32_t dec, units;

    dec     = (uint32_t)(input[0] - '0');
    units   = (uint32_t)(input[1] - '0');

    if( (units > 9) || (units < 0) )
    {
        value = dec ;
    }
    else
    {
        value = dec*10+units;
    }

    return (int)value;
}

time_t time_to_epoch ( const struct tm *ltm, int utcdiff ) 
{
   const int mon_days [] =
      {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
   long tyears, tdays, leaps, utc_hrs;
   int i;

   tyears = ltm->tm_year - 70 ; // tm->tm_year is from 1900.
   leaps = (tyears + 2) / 4; // no of next two lines until year 2100.
   //i = (ltm->tm_year – 100) / 100;
   //leaps -= ( (i/4)*3 + i%4 );
   tdays = 0;
   for (i=0; i < ltm->tm_mon; i++) tdays += mon_days[i];

   tdays += ltm->tm_mday-1; // days of month passed.
   tdays = tdays + (tyears * 365) + leaps;

   utc_hrs = ltm->tm_hour + utcdiff; // for your time zone.
   return (tdays * 86400) + (utc_hrs * 3600) + (ltm->tm_min * 60) + ltm->tm_sec;
}

uint32_t get_timestamp(uint8_t *date)
{
    uint8_t value[] ="00";
    uint8_t *next_value_pos;
    uint32_t timestamp = 0;
    struct tm tm;

    // Get Date
    // Year
    next_value_pos = date; 
    tm.tm_year = get_value_dateformat(next_value_pos) - 1900 + 2000;

    // Month
    next_value_pos += 3; // points to next number  
    tm.tm_mon = get_value_dateformat(next_value_pos) - 1;

    // Day
    next_value_pos += 3; // points to next number  
    tm.tm_mday = get_value_dateformat(next_value_pos); 

    // Hour 
    next_value_pos += 3; // points to next number
    tm.tm_hour = get_value_dateformat(next_value_pos); 

    // Minutes 
    next_value_pos += 3; // points to next number
    tm.tm_min = get_value_dateformat(next_value_pos); 

    // Seconds 
    next_value_pos += 3; // points to next number
    tm.tm_sec = get_value_dateformat(next_value_pos); 

    timestamp = __mktime_utc(&tm);

    return timestamp;

}

void test_find_time(void)
{
    uint8_t reply[] = "+CCLK: \"09/12/04,00:19:43+00\"\r\nOK\r\n";
    uint8_t* time;

    time = strstr(reply, "+CCLK");

    time += strlen("+CCLK: ")+1;

    TEST_ASSERT_EQUAL_STRING( "09/12/04,00:19:43+00\"\r\nOK\r\n", time);
}

void test_get_timestamp_current(void)
{ 
    uint8_t time[] = "2020/08/17,16:54:10+08";
    uint8_t *t = time;
    struct tm tm;
    uint32_t epoch, timestamp;
    if ( strptime(t, "%Y/%m/%d,%H:%M:%S", &tm) != NULL )
        epoch = mktime(&tm);
    else
        printf("fail");

   uint8_t time1[] = "20/08/17,16:54:10+08";

    timestamp = get_timestamp(time1);
    printf("timestamp: %ld", timestamp);
    printf("epoch : %ld", epoch);

    TEST_ASSERT_EQUAL_UINT32(epoch, timestamp);
}


