/*
 * uart.c
 *
 *  Created on: 18.06.2020
 *      Author:  Daniel Paredes
 */

#include "radio.h"

static const uint8_t cert_ca[] = "-----BEGIN CERTIFICATE-----\r\n"
"MIIDSjCCAjKgAwIBAgIQRK+wgNajJ7qJMDmGLvhAazANBgkqhkiG9w0BAQUFADA/\r\n"
"MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\r\n"
"DkRTVCBSb290IENBIFgzMB4XDTAwMDkzMDIxMTIxOVoXDTIxMDkzMDE0MDExNVow\r\n"
"PzEkMCIGA1UEChMbRGlnaXRhbCBTaWduYXR1cmUgVHJ1c3QgQ28uMRcwFQYDVQQD\r\n"
"Ew5EU1QgUm9vdCBDQSBYMzCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\r\n"
"AN+v6ZdQCINXtMxiZfaQguzH0yxrMMpb7NnDfcdAwRgUi+DoM3ZJKuM/IUmTrE4O\r\n"
"rz5Iy2Xu/NMhD2XSKtkyj4zl93ewEnu1lcCJo6m67XMuegwGMoOifooUMM0RoOEq\r\n"
"OLl5CjH9UL2AZd+3UWODyOKIYepLYYHsUmu5ouJLGiifSKOeDNoJjj4XLh7dIN9b\r\n"
"xiqKqy69cK3FCxolkHRyxXtqqzTWMIn/5WgTe1QLyNau7Fqckh49ZLOMxt+/yUFw\r\n"
"7BZy1SbsOFU5Q9D8/RhcQPGX69Wam40dutolucbY38EVAjqr2m7xPi71XAicPNaD\r\n"
"aeQQmxkqtilX4+U9m5/wAl0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNV\r\n"
"HQ8BAf8EBAMCAQYwHQYDVR0OBBYEFMSnsaR7LHH62+FLkHX/xBVghYkQMA0GCSqG\r\n"
"SIb3DQEBBQUAA4IBAQCjGiybFwBcqR7uKGY3Or+Dxz9LwwmglSBd49lZRNI+DT69\r\n"
"ikugdB/OEIKcdBodfpga3csTS7MgROSR6cz8faXbauX+5v3gTt23ADq1cEmv8uXr\r\n"
"AvHRAosZy5Q6XkjEGB5YGV8eAlrwDPGxrancWYaLbumR9YbK+rlmM6pZW87ipxZz\r\n"
"R8srzJmwN0jP41ZL9c8PDHIyh8bwRLtTcm1D9SZImlJnt1ir/md2cXjbDaJWFBM5\r\n"
"JDGFoqgCWjBH4d1QB7wCCZAA62RjYJsWvIjJEubSfZGL+T0yjWW06XyxV3bqxbYo\r\n"
"Ob8VZRzI9neWagqNdwvYkQsEjgfbKbYK7p2CNTUQ\r\n"
"-----END CERTIFICATE-----\r\n";

#define uart_debug(...) 

#define NCHARS(x)   (strlen(x) + 1)

static int mqtt_broker_port = 8883; //1883;
// static int mqtt_socket_id = 0;
// static int ssl_context = 2;
// static int ssl_version = 4;

// #define MQTT_EOF    (0x1A)
#define CTRL_Z      (0x1A)

#define RETURN_FALSE_IF_NO_OK_IN_xMS(X)  if( !ATparser_is_expected_reply(X, "OK")) {return false;} 
#define CONTINUE_IF_NO_OK_IN_xMS(X)  if( !ATparser_is_expected_reply(X, "OK")) {turn_on = false; continue;} 

bool radio_disconnect_mqtt(void)
{
    uart_debug("> MQTT disconnection");

    ATparser_send_command("AT+QMTDISC=0");
    RETURN_FALSE_IF_NO_OK_IN_xMS(1000); 

    uart_debug("> MQTT closing connection");

    ATparser_send_command("AT+QMTCLOSE=0");
    RETURN_FALSE_IF_NO_OK_IN_xMS(1000); 

    return true;

}

void radio_turn_on(void) 
{
    bool turn_on = false;
    uart_debug("> Radio turning on");

    while (!turn_on)
    {
        gpio_reset_radio();
        sleep_msec(100); //Recommanded Wait before enabling the radio module
        PWRKEY_RADIO_PxOUT |= PWRKEY_RADIO_PIN;
        sleep_sec(1);    //1 sec high forn enabling the radio module
        PWRKEY_RADIO_PxOUT &= ~PWRKEY_RADIO_PIN;

        sleep_sec(5); //Recommendet Wait before first AT

        ATparser_send_command( "AT" );

        if( !ATparser_is_expected_reply(1000, "OK") )
        {
            turn_on = false;
            sleep_msec(500);
            continue;
        }

        // Network time sync with NPT server
        // Germany is GMT+2 in quarters = +08
        ATparser_send_command("AT+CCLK=\"04/01/01,00:00:02+08\"");
        CONTINUE_IF_NO_OK_IN_xMS(300);

        if( !radio_GPRS_network_registration(5) )
        {
            uart_debug("fail to register a gprs network");
            return false;
        }

        ATparser_send_command("AT+QNTP=\"ptbtime1.ptb.de\"");
        CONTINUE_IF_NO_OK_IN_xMS(5000);

        ATparser_send_command("AT+CCLK?");
        CONTINUE_IF_NO_OK_IN_xMS(300);

        ATparser_send_command("AT+QIDEACT");
        CONTINUE_IF_NO_OK_IN_xMS(5000);
        
        turn_on = true;
    }
}


bool radio_GPRS_network_registration(uint8_t number_of_tries)
{
    uint8_t try_count = 0;
    uint8_t *_reply;

    while ( try_count < number_of_tries)
    {
        ATparser_send_command("AT+CGREG?");

        _reply = ATparser_receive_reply(1000);
        // 5: registered (roaming) 
        // 1: registered (home)
        if( (strstr_u8( _reply, "CGREG: 0,5") != NULL ) ||
                (strstr_u8( _reply, "CGREG: 0,1") != NULL ) )
        {
            return true;
        }     

        try_count++;

        sleep_msec(500);
    }
    return false; 
}


bool radio_network_registration(uint8_t number_of_tries)
{
    uint8_t try_count = 0;
    uint8_t *_reply;

    while ( try_count < number_of_tries)
    {
        ATparser_send_command("AT+CREG?");

        _reply = ATparser_receive_reply(1000);
        // 5: registered (roaming) 
        // 1: registered (home)
        if( (strstr_u8( _reply, "CREG: 0,5") != NULL ) ||
                (strstr_u8( _reply, "CREG: 0,1") != NULL ) )
        {
            return true;
        }     

        try_count++;

        sleep_msec(500);
    }
    return false; 
}

static bool radio_mqtt_open(uint8_t number_of_tries, uint8_t *mqtt_broker_url)
{
    uint8_t try_count = 0;
    uint8_t *_reply;

    while( try_count < number_of_tries){

        ATparser_send_command("AT+QMTOPEN=0,\"%s\",\"8883\"", 
                mqtt_broker_url);
        //                 mqtt_broker_port);

        _reply = ATparser_receive_reply(20000);
        uart_debug(_reply);

        // QMTSTAT: 0,1 => Connection closed
        // QMTOPEN: 0,0 => Connection opened  
        if( (strstr_u8( _reply, "QMTSTAT: 0,1") == NULL ) &&
                (strstr_u8( _reply, "QMTOPEN: 0,0") != NULL ) )
        {
            return true;
        }     

        try_count++;
    }
    return false; 
}

bool radio_connect_mqtt(uint8_t *broker, 
        uint8_t *mqtt_client,
        uint8_t *mqtt_userid, 
        uint8_t *mqtt_password)
{
    uart_debug("> MQTT Open Connection");

    ATparser_send_command("AT+QMTCFG=\"VERSION\",0,1");
    RETURN_FALSE_IF_NO_OK_IN_xMS(300);


    if( !radio_mqtt_open(10, broker) )
    {
        return false;
    }

    uart_debug("> MQTT connect to Broker");
    ATparser_send_command("AT+QMTCONN=0,\"%s\",\"%s\",\"%s\"",
            mqtt_client,
            mqtt_userid,
            mqtt_password);

    RETURN_FALSE_IF_NO_OK_IN_xMS(20000);

    return true;
}


inline static int get_value_dateformat(uint8_t *input)
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

/*********************************************/
/* Replacement of mktime                     */
/* code: https://github.com/NuxiNL/cloudlibc */
/*********************************************/

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
/******** End of cloudlibc *********/

uint32_t radio_get_timestamp(void)
{
    uint8_t *_reply;
    uint8_t* time;

    uint32_t timestamp = 0;
    ATparser_send_command("AT+CCLK?");
    _reply = ATparser_receive_reply( 300 ); 

    uart_debug("Radio Local Time %s",_reply);

    time = strstr_u8(_reply, "+CCLK");

    if( time == NULL ) 
    {
        return 0;
    }

    time += strlen("AT+CCLK?\r\n+CCLK: ");
    uart_debug("time: %s\r\n", time);

    uint8_t *next_value_pos;
    struct tm tm;

    // Get Date
    // Year
    next_value_pos = time;
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

    uart_debug("timestamp: %"PRIu32, timestamp);

    return timestamp;
}

uint8_t radio_get_signal_quality(void)
{
    uint8_t *_reply;

    ATparser_send_command("AT+CSQ");
    _reply = ATparser_receive_reply( 1000 ); 

    uart_debug("Radio Signal Quality %s",_reply);

    uint8_t signal_quality = 0;

    uint8_t dec, units;
    dec     = _reply[8] - '0';
    units   = _reply[9] - '0';

    if( (units > 9) || (units < 0) )
    {
        signal_quality = dec ;
    }
    else
    {
        signal_quality = dec*10+units;
    }

    return signal_quality;
}


bool radio_connect(uint8_t * apn_server)
{
    uint8_t* _reply;
    uart_debug("> Radio Connecting");

    uart_debug("> Configuring Device");
    // Set Echo Mode Off -> 0 
    ATparser_send_command("ATE0");
    RETURN_FALSE_IF_NO_OK_IN_xMS(1000);

    // Set to 1: Full Functionality
    ATparser_send_command("AT+CFUN=1");
    RETURN_FALSE_IF_NO_OK_IN_xMS(5000);

    // Report Error verbose on
    ATparser_send_command("AT+CMEE=2");
    RETURN_FALSE_IF_NO_OK_IN_xMS(300);

    uart_debug("> Check SIM Status");

    ATparser_send_command( "AT+CPIN?" );
    RETURN_FALSE_IF_NO_OK_IN_xMS(5000);

    uart_debug(" > INSTALLING CERTIFICATES");

    ATparser_send_command("AT+QMTCFG=\"SSL\",0,1,2");
    RETURN_FALSE_IF_NO_OK_IN_xMS(1200);

    ATparser_send_command("AT+QSECWRITE=\"RAM:ca_cert.pem\",1220,100");
    if ( !ATparser_is_expected_reply(12000, "CONNECT"))
    {
        uart_debug("failing write certificate");
        return false;
    }

    ATparser_send_certificate(cert_ca);
    RETURN_FALSE_IF_NO_OK_IN_xMS(1200);

    ATparser_send_command("AT+QSECREAD=\"RAM:ca_cert.pem\"");
    RETURN_FALSE_IF_NO_OK_IN_xMS(1200);

    uart_debug("> CONFIGURING SSL");

    ATparser_send_command("AT+QSSLCFG=\"cacert\",2,\"RAM:ca_cert.pem\"");
    RETURN_FALSE_IF_NO_OK_IN_xMS(1200);

    ATparser_send_command("AT+QSSLCFG=\"seclevel\",2,1" );
    RETURN_FALSE_IF_NO_OK_IN_xMS(1200);

    ATparser_send_command("AT+QSSLCFG=\"sslversion\",2,4");
    RETURN_FALSE_IF_NO_OK_IN_xMS(1200);

    ATparser_send_command("AT+QSSLCFG=\"ciphersuite\",2,\"0XFFFF\"");
    RETURN_FALSE_IF_NO_OK_IN_xMS(1200);

    //Ignore the RTC time .
    ATparser_send_command("AT+QSSLCFG=\"ignorertctime\",1");
    RETURN_FALSE_IF_NO_OK_IN_xMS(1200);

    uart_debug("> Config APN");
    if( !radio_network_registration(10) )
    {
        uart_debug("fail to register a network");
        return false;
    }

    ATparser_send_command("AT+CGATT=1");
    RETURN_FALSE_IF_NO_OK_IN_xMS(300);

    ATparser_send_command("AT+QIFGCNT=0");
    RETURN_FALSE_IF_NO_OK_IN_xMS(300);

    uart_debug("> Connecting to APN");

    // check conn state
    ATparser_send_command("AT+COPS?");
    if ( ATparser_is_expected_reply(1200, "ERROR"))
    {
        return false;
    }

    // check quality of the signal 
    ATparser_send_command("AT+CSQ");
    if ( ATparser_is_expected_reply(1200, "ERROR"))
    {
        return false;
    }

    //  Use AT+QIMODE command to select TCPIP Stack mode
    ATparser_send_command("AT+QIMODE=0");
    RETURN_FALSE_IF_NO_OK_IN_xMS(1200);

    // Configure TCP/IP Context
    ATparser_send_command("AT+QICSGP=1,\"%s\"", apn_server);
    RETURN_FALSE_IF_NO_OK_IN_xMS(20000);

    // Start TCP/IP Task
    ATparser_send_command("AT+QIREGAPP");
    RETURN_FALSE_IF_NO_OK_IN_xMS(2000);

    /* 
       Check the current connecting mode
       (1: GPRS connecting mode 
       - 0: CSD connecting mode) */
    ATparser_send_command("AT+QICSGP?");
    RETURN_FALSE_IF_NO_OK_IN_xMS(1500);

    /* Active the GPRS context */
    ATparser_send_command("AT+QIACT");
    RETURN_FALSE_IF_NO_OK_IN_xMS(20000);

    /* Get the local IP address */
    ATparser_send_command("AT+QILOCIP");
    _reply = ATparser_receive_reply( 1500 ); 

    uart_debug("Local IP %s", _reply);

    return true;
}

void radio_disconnect(void)
{
    bool connected = true;
    uart_debug("> Shutdown Radio ");

    while(connected)
    {
        ATparser_send_command("AT+QPOWD=1");
        if ( !ATparser_is_expected_reply( 300, "POWER DOWN") )
        {
            connected = true;
            continue;
        }

        connected = false;
    }

    uart_debug("Disconnected");
}

bool radio_unsubscribe_topic(uint8_t *mqtt_topic)
{
    ATparser_send_command("AT+QMTUNS=0,1,\"%s\"", mqtt_topic);
    RETURN_FALSE_IF_NO_OK_IN_xMS(5000);
    return true;
}

#define RX_CLOUD_TIMEOUT_MS  (5000)
bool radio_subscribe_topic_and_get_data(uint8_t *mqtt_topic, uint8_t **data)
{
    uint8_t *_reply;
    
    uart_debug("> MQTT SUB");
    // TCPConnectID = 0, msgID = 1, topic, qos = 0
    // msgID <1-65535>
    ATparser_send_command("AT+QMTSUB=0,1,\"%s\",0", mqtt_topic);

    // wait for +QMTRECV: 0,0,“topic/example”,“This is the payload related to topic”
    _reply = ATparser_receive_reply( RX_CLOUD_TIMEOUT_MS ); 

    (*data) = _reply ;

    if( (strstr_u8( _reply, "+QMTRECV") != NULL ) )
    {
        return true;
    }

    return false;
}

bool radio_subscribe_topic(uint8_t *mqtt_topic)
{
    uart_debug("> MQTT SUB");
    // TCPConnectID = 0, msgID = 1, topic, qos = 0
    // msgID <1-65535>
    ATparser_send_command("AT+QMTSUB=0,1,\"%s\",0", mqtt_topic);

    // timeout is by default 20s, but it takes to long
    // and it depends on the network as well
    RETURN_FALSE_IF_NO_OK_IN_xMS(1000);
    return true;
}

bool radio_get_data_from_cloud(uint8_t **data)
{
    uint8_t *_reply;

    // wait for +QMTRECV: 0,0,“topic/example”,“This is the payload related to topic”
    _reply = ATparser_receive_reply( RX_CLOUD_TIMEOUT_MS ); 

    (*data) = _reply ;

    if( (strstr_u8( _reply, "+QMTRECV") != NULL ) )
    {
        return true;
    }

    return false;
}


bool radio_send_data_to_cloud(uint8_t *data, uint8_t* mqtt_topic)
{
    uart_debug(">MQTT PUB data");
    ATparser_send_command("AT+QMTPUB=0,0,0,1,\"%s\"", mqtt_topic);

    // timeout is by default 20s, but it takes to long
    // and it depends on the network as well
    if( !ATparser_is_expected_reply( 500, ">") )
    {
        return false;
    }

    ATparser_send_command("%s",data); 
    ATparser_send_command("%c",CTRL_Z);

    RETURN_FALSE_IF_NO_OK_IN_xMS(2000);

    return true;
}

