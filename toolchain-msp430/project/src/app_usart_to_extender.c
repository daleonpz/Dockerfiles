#include "app_usart_to_extender.h"

#ifndef TEST
#include "radio.h"
#endif

#define D_HEADER_LENGTH     (11)
#define RX_TIMEOUT_MS  (5000)

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define NCHARS(x)   (strlen_u8(x) + 1)

#define uart_debug(...) 

#ifdef TEST
#define usart_send_NAK_to_IoT_board(...) 
#define usart_send_ACK_to_IoT_board(...) 
#define usart_send_data_to_cloud(...) 
#define usart_connect_cloud(...) 
#define usart_disconnect_cloud(...) 
#define usart_execute_cmd(...)  
#define usart_init_configuration(...) 
#define usart_check_powermode(...) 
#define usart_send_ACK_with_DATA_to_IoT_board(...)  
#define usart_check_incoming_data_from_cloud(...) 
#define usart_parse_get_data(...) 
#endif

//TODO: replace strstr
// These are configuration values
static uint8_t _powermode_current_state = POWER_ON;
static uint8_t _powermode_previous_state = POWER_ON;
static uint8_t _radio_signal_quality = 0;
static uint8_t _apn_server[100];
static uint8_t _mqtt_broker_url[100] ;
static uint8_t _mqtt_client[100];
static uint8_t _mqtt_userid[100];
static uint8_t _mqtt_password[100];
static uint8_t _serial_number[] = "222";
static uint8_t _error_code[4] = {0, 0, 0, 0};

uint8_t usart_get_powermode(void)
{
    return _powermode_current_state;
}

//TODO: boundary check
uint8_t usart_u32_to_str( uint32_t u32, uint8_t *str)
{
    itoa_u32(u32, str);
    return NCHARS(str);
}


#ifndef TEST
void usart_init_configuration(void)
{
    _radio_signal_quality = 0;

    memcpy(_apn_server,"iot.1nce.net", NELEMS("iot.1nce.net")) ; 
    memcpy(_mqtt_broker_url, "pfeiffer-vacuum.poc.q-loud.de", NELEMS("pfeiffer-vacuum.poc.q-loud.de") );

    uint32_t time;
    rtc_get_time(&time);
    srand( time );
    uint16_t random_number = rand();

    uint8_t random_id[32]; 
    uint8_t len;

    len = usart_u32_to_str((uint32_t)random_number, random_id);

    memcpy(_mqtt_client, random_id, len);
    memcpy(_mqtt_userid, "pfeiffer01", NELEMS("pfeiffer01") );
    memcpy(_mqtt_password, "4PTpqxpZ72DLd9Cf", NELEMS("4PTpqxpZ72DLd9Cf") );

}
#endif

// TODO: find a way to test this function
#ifndef TEST
bool usart_connect_cloud(void)
{
    bool turn_on = false;

    while( !turn_on )
    {
        radio_turn_on();
        if(! radio_connect( _apn_server ) )
        {
            uart_debug("Couldn't connect to apn");
            uart_debug("Restarting Radio....");
            continue;
        }

        if(! radio_connect_mqtt(_mqtt_broker_url,
                    _mqtt_client,
                    _mqtt_userid,
                    _mqtt_password) )
        {
            uart_debug("Couldn't connect to MQTT");
            uart_debug("Restarting Radio....");
            continue;
        }

        turn_on = true;
    }

    LED_BLUE_PxOUT |= LED_BLUE_BIT;

    return true;
}
#endif

#ifndef TEST
bool usart_disconnect_cloud(void)
{
    if( !radio_disconnect_mqtt() )
    {
        uart_debug("Couldn't disconnect MQTT");
    }

    radio_disconnect();
    LED_BLUE_PxOUT &= ~LED_BLUE_BIT;

    return true;
}
#endif

// TODO: Proper test for this function
#ifndef TEST
uint8_t* usart_read_from_IoT_board(void)
{
    return uart_a1_get_rbuf();
}


// bool usart_send_to_IoT_board( uint8_t* data, uint8_t topic)
bool usart_send_to_IoT_board( uint8_t data, uint16_t topic)
{
    uart_debug("Payload to process: %i", data); 

    uint8_t paclet[32];
    memset(paclet, 0, NELEMS(paclet));

    paclet[PosHdrFlagStart] = 0x69;
    paclet[PosHdrVersion] = 0x00;
    paclet[PosHdrRcvAddress] = ADDR_IOTB;
    paclet[PosHdrOcd] = OCD_GET_DATA;
    paclet[PosHrdSeq] = 0xDE;
    paclet[PosHrdSeq + 1 ] = 0xAD;
    paclet[PosHrdSeq + 2 ] = 0xBE;
    paclet[PosHrdSeq + 3 ] = 0xEF;
    paclet[PosHdrFlagEnd] = 0x68;

    // it's just a integer
    paclet[PosPayloadData + 2] = 1;
    paclet[PosPayloadData + 3] = data;

    const uint16_t LL = 17;//11 + 2 + 1 + 2;
    paclet[PosHdrLen] = 0x00;
    paclet[PosHdrLen + 1 ] = 0x11;

    switch(topic)
    {
        case Cmd_MB_EnablePump:
            paclet[PosPayloadData] = 0x05;
            paclet[PosPayloadData + 1] = 0x01;
            break;
        case Cmd_MB_LedOnOff:
        default:
            paclet[PosPayloadData] = 0x05;
            paclet[PosPayloadData + 1] = 0x02; 
            break;
    }

    uint16_t crc;
    crc = usart_crc_calc(paclet, LL-2 );

    /* LSB of CRC first */
    paclet[LL-2] = (uint8_t) (crc & 0x00ff);
    /* MSB of CRC second */
    paclet[LL-1] = (uint8_t) ((crc & 0xff00) >> 8);

    uart_debug("        SEND to IOT BOARD");
    // PRIu32 is a macro to print uint32_t 
    // <inttypes.h> includes PRIu32 
    for( uint8_t i=0; i < LL; i++)
    {
        uart_write( uart_a1, "%" PRIu8 "\r\n", paclet[i]) ;
    }
    uart_debug("    End of Transfer");
    return true;
}

// TODO: It's possible that may conflict with Pfeiffer. Ask
bool usart_send_NAK_to_IoT_board(uint32_t SEQ )
{
    uart_debug("        NAK");
    // PRIu32 is a macro to print uint32_t 
    // <inttypes.h> includes PRIu32 
    uart_write( uart_a1, "%" PRIu32 "\r\n", SEQ) ;
    return true;
}


bool usart_send_ACK_with_DATA_to_IoT_board( uint32_t SEQ, uint8_t data_type, uint8_t *payload, uint8_t len  )
{
    uart_debug("        ACK:");

    switch(data_type)
    {
        case DTYPE_BOOL_OLD:
        case DTYPE_BOOL_NEW:
            uart_write( uart_a1, "%" PRIu32 " %" PRIu8 " %" PRIu8 " \r\n",
                    SEQ,
                    1,
                    payload[0]);
            break;

        case DTYPE_UINT:
        case DTYPE_USHORT :
        case DTYPE_EXPO_N :
        case DTYPE_REAL :
            uart_write( uart_a1, "%" PRIu32 " %" PRIu8 " ",
                    SEQ,
                    len);
            for( uint8_t i=0; i< len; i++ )
            {
                uart_write( uart_a1, "%" PRIu8 , payload[i] );
            }
            uart_write( uart_a1, "\r\n");

            break;
        case DTYPE_STRING :
            uart_write( uart_a1, "%" PRIu32 " %" PRIu8 " %s\r\n",
                    SEQ,
                    len,
                    payload);
    };

    return true;
}

bool usart_send_ACK_to_IoT_board( uint32_t SEQ)
{
    uart_write( uart_a1, "%" PRIu32 " \r\n", SEQ);
    return true;
}

#endif

bool usart_get_header( uint8_t *uart_msg, t_usart_msg_header *header)
{
    if ( uart_msg[0] != D_FlagHdrStart)
    {
        return false;
    }

    header->LL   = ( ((uint16_t) uart_msg[1]) << 8) + uart_msg[2];
    header->VER  = uart_msg[3];
    header->ADR  = uart_msg[4];
    header->OCD  = uart_msg[5];
    header->SEQ  =   ( (uint32_t) uart_msg[6] << 24 ) +
        ( (uint32_t) uart_msg[7] << 16 ) +
        ( (uint32_t) uart_msg[8] << 8 ) +
        ( (uint32_t) uart_msg[9] ) ;

    if ( uart_msg[10] != D_FlagHdrEnd )
    {
        return false;
    } 

    return true;
}

uint8_t * usart_get_cmd_list( uint8_t *uart_msg )
{
    return (uart_msg + 11);
}


uint8_t usart_u32_to_hex_array(uint32_t number, uint8_t *hex_array)
{
    uint8_t len;
    uint8_t temp; 

    for( len = 4; len>0; len--)
    {
        temp = (number >> (8*(len-1))) & 0XFF;
        if( temp != 0)
        {
            break; 
        }
    }

    uint8_t displacement;
    for( uint8_t i=0; i<len; i++)
    {
        displacement = 8*(len - 1 - i);
        hex_array[i] = ( number >> displacement ) & 0XFF;
    } 

    if( len == 0)
    {
        hex_array[0] = 0;
        len = 1;
    }
    return len;
}

uint32_t usart_hex_array_to_u32(uint8_t *hex_array, uint8_t len)
{
    uint32_t sum = 0;
    uint8_t displacement;
    for( uint8_t i=0; i<len; i++)
    {
        displacement = 8*(len - 1 - i);
        sum += ( ((uint32_t)hex_array[i]) << displacement );
    }

    return  sum;
}




static void usart_mqtt_create_path(uint8_t *path,uint16_t size, const char *command, ...)
{
    va_list args;

    uint8_t* str = path;
    va_start(args, command);

    vsnprintf(str, size, command, args);
    va_end(args);

    path = str;
}



// TODO: Proper test for this function
#ifndef TEST
bool usart_send_data_to_cloud(uint8_t* raw_data, uint16_t data_len, uint8_t* mqtt_topic)
{
    uint8_t *_data_for_cloud;
    uint32_t timestamp;
    rtc_get_time(&timestamp);

    uint8_t mqtt_full_topic[100];
    uint8_t mqtt_json_data[100];

    usart_mqtt_create_path(mqtt_full_topic, 100,
            "%s/%s/%s/%" PRIu32, 
            "poc", _serial_number,
            mqtt_topic, 
            timestamp);

    _data_for_cloud = (uint8_t*)calloc( data_len, sizeof(uint8_t)); 
    memcpy(_data_for_cloud, raw_data, data_len);

    usart_mqtt_create_path(mqtt_json_data, 100,
            "{\"time\":%" PRIu32 ", \"value\":%s}",
            timestamp,
            _data_for_cloud);


    if( !radio_send_data_to_cloud(mqtt_json_data, mqtt_full_topic) ) 
    { 
        free(_data_for_cloud);
        return false;
    }

    free(_data_for_cloud);
    return true;
}
#endif

#ifndef TEST
bool usart_check_incoming_data_from_cloud(uint8_t* mqtt_topic, uint32_t *payload)
{
    uint8_t *data; 
    uint8_t *_temp;
    bool recieved_data = false;

    if( _powermode_current_state == POWER_OFF)
    {
        uart_debug("Radio is off. No receiving from Cloud");
        return true;
    }

    uint8_t mqtt_topic_full_path[100];

    usart_mqtt_create_path(mqtt_topic_full_path, 100,
            "%s/%s/%s", 
            "poc", _serial_number, mqtt_topic);

    if( !radio_subscribe_topic_and_get_data(mqtt_topic_full_path, &data) )
    {
        uart_debug("no data from Cloud");
        return false;
    }


    _temp = strstr_u8( data, mqtt_topic);
    uint8_t *json_value;
    if ( _temp != NULL )
    {
        _temp += NCHARS(mqtt_topic) ;
        json_value = strstr_u8( _temp, "value");
        json_value += NCHARS("value:");

        (*payload) = atoi_u32(json_value);
        uart_debug("Payload from %s: %d",mqtt_topic_full_path, *payload); 
        recieved_data = true;
    }

    if( !radio_unsubscribe_topic(mqtt_topic_full_path))
    {
        uart_debug("Couldn't unsubscribe or there is an error");
    }


    return recieved_data;
}
#endif

// TODO: Proper test for this function
// TODO: Nicht getestet
bool usart_parse_ocd( t_usart_msg_to_ext *extender )
{
    uint8_t ocd = extender->header.OCD;

    switch(ocd)
    {
        case OCD_GET:
            uart_debug("GET");
            break;
        case OCD_SET: 
            uart_debug("SET");
            break;
        case OCD_GET_DATA:
            uart_debug("GET_DATA");
            usart_parse_get_data( extender->header.SEQ, extender->cmd_list, extender->header.LL );
            return true;
        case OCD_SET_DATA: 
            uart_debug("SET_DATA");
            usart_send_ACK_to_IoT_board( extender->header.SEQ );
            usart_parse_data_list( extender->cmd_list , extender->header.LL);
            return true;
        default:
            uart_debug("This is exceptional. Shouldn't occur");
            return false;
    }

    usart_parse_cmd_list( extender ); 
    return true;
}

// TODO: Proper test for this function
bool usart_parse_cmd_list( t_usart_msg_to_ext *extender)
{
    uint16_t i = 0;
    uint8_t cmdid_h, cmdid_l;
    uint16_t cmd_id;
    uint8_t cmd_cl; 
    uint8_t *cmd_payload;

    t_usart_msg_cmd cmd_struct;

    uint8_t *cmd_list = extender->cmd_list;
    uint16_t list_len = extender->header.LL; 

    while( i < list_len )
    {
        cmdid_h = cmd_list[i];
        cmdid_l = cmd_list[i+1];

        cmd_id = ( ((uint16_t) cmdid_h) << 8 ) + cmdid_l;
        cmd_cl = cmd_list[i+2];

        if( extender->header.OCD == OCD_SET) 
        {
            cmd_payload = cmd_list+(i+3); 
        }
        // TODO: there is more posibilities MGET/MSET, but we dont support it yet
        else
        {
            cmd_payload = NULL;
        }

        i += (3+ cmd_cl);

        cmd_struct.ID = cmd_id;
        cmd_struct.CL = cmd_cl;
        cmd_struct.PAYLOAD = cmd_payload;

        usart_execute_cmd( &extender->header, &cmd_struct);
    }

    return true;
}

#ifndef TEST
// TODO: test this function
bool usart_check_powermode(void)
{
    switch(_powermode_current_state)
    {
        case POWER_OFF:
            if( _powermode_previous_state == POWER_ON)
            {
                if( !usart_disconnect_cloud() )
                {
                    uart_debug("Couldn't turn off. Radio still off");
                    _powermode_current_state = POWER_ON;
                }
            }
            break;
        case POWER_ON:
            if( _powermode_previous_state == POWER_OFF)
            {
                if( !usart_connect_cloud())
                {
                    uart_debug("Couldn't turn off. Radio still on");
                    _powermode_current_state = POWER_OFF;
                }
            }
            break;
        default:
            break;
    }
    return true;
}
#endif

// TODO: Test this function
#ifndef TEST
bool usart_execute_cmd( t_usart_msg_header *header, t_usart_msg_cmd *cmd_struct)
{
    enum eDataType data_type ; 

    if( header->OCD == OCD_SET)
    {
        switch ( cmd_struct->ID )
        {
            case POWERMODE :
                _powermode_previous_state = _powermode_current_state;
                _powermode_current_state = *(cmd_struct->PAYLOAD);
                break;
            case APN:
                memcpy(_apn_server, cmd_struct->PAYLOAD, cmd_struct->CL);
                break;
            case MQTT_USERNAME:
                memcpy(_mqtt_userid, cmd_struct->PAYLOAD, cmd_struct->CL);
                break;
            case MQTT_PASSWORD:
                memcpy(_mqtt_password, cmd_struct->PAYLOAD, cmd_struct->CL);
                break;
            case MQTT_SERVER:
                memcpy(_mqtt_broker_url, cmd_struct->PAYLOAD, cmd_struct->CL);
                break;
            case RADIO_SIGNAL_QUALITY:
                break;
            case ERROR_CODE:
                break;
            case CLR:
                memset(_error_code, 0, NELEMS(_error_code));
                break;
            default:
                return true;
        }

        usart_send_ACK_to_IoT_board( header->SEQ ) ;

        if(  cmd_struct->ID == POWERMODE)
        {
            usart_check_powermode();
        }
        return true;
    }


    switch ( cmd_struct->ID )
    {
        case POWERMODE :
            cmd_struct->PAYLOAD = &_powermode_current_state;
            cmd_struct->CL  = 1;
            data_type = DTYPE_BOOL_NEW;
            break;
        case APN:
            cmd_struct->PAYLOAD = _apn_server;
            cmd_struct->CL  = NCHARS(_apn_server);
            data_type = DTYPE_STRING;
            break;
        case MQTT_USERNAME:
            cmd_struct->PAYLOAD = _mqtt_userid;
            cmd_struct->CL  = NCHARS(_mqtt_userid);
            data_type = DTYPE_STRING;
            break;
        case MQTT_PASSWORD:
            cmd_struct->PAYLOAD = _mqtt_password;
            cmd_struct->CL = NCHARS(_mqtt_password);
            data_type = DTYPE_STRING;
            break;
        case MQTT_SERVER:
            cmd_struct->PAYLOAD = _mqtt_broker_url;
            cmd_struct->CL = NCHARS(_mqtt_broker_url);
            data_type = DTYPE_STRING;
            break;
        case RADIO_SIGNAL_QUALITY:
            _radio_signal_quality = radio_get_signal_quality();
            cmd_struct->PAYLOAD = &_radio_signal_quality;
            cmd_struct->CL = 1;
            data_type = DTYPE_UINT;
            break;
        case ERROR_CODE:
        case CLR:
            cmd_struct->PAYLOAD = _error_code;
            cmd_struct->CL = NELEMS(_error_code);
            data_type = DTYPE_UINT;
            break;
        default:
            usart_send_NAK_to_IoT_board(header->SEQ);
            return false;
    }

    usart_send_ACK_with_DATA_to_IoT_board(
            header->SEQ,
            data_type,
            cmd_struct->PAYLOAD,
            cmd_struct->CL);

    return true;
}
#endif

// TODO: Proper test for this function
bool usart_parse_data_list( uint8_t *data_list, uint16_t list_len)
{
    uint16_t i = 0;
    uint8_t data_topic_h, data_topic_l;
    uint16_t mqtt_topic;
    uint8_t data_cl; 
    uint8_t *data_payload;

    uint32_t data_payload_u32; 
    uint8_t data_payload_str[7]; //max 999 999 + '\0'

    while( i < list_len)
    {
        data_topic_h = data_list[i];
        data_topic_l = data_list[i+1];

        mqtt_topic = ( ((uint16_t) data_topic_h) << 8 ) + data_topic_l;
        data_cl = data_list[i+2];

        data_payload = data_list+(i+3); 

        i += (3+ data_cl);

        data_payload_u32 = usart_hex_array_to_u32( data_payload, data_cl); 

        data_cl = usart_u32_to_str(data_payload_u32, data_payload_str);

        uart_debug("Number: %s", data_payload_str);

        // TODO: Hashtable for Topics remove case here
        switch( mqtt_topic)
        {
            case Cmd_PV_Heating:
                usart_send_data_to_cloud(data_payload_str, data_cl, "heating");
                break; 
            case Cmd_PV_ActualSpd :
                usart_send_data_to_cloud(data_payload_str, data_cl, "actual_spd");
                break;
            case Cmd_PV_DrvCurrent :
                usart_send_data_to_cloud(data_payload_str, data_cl, "drv_current");
                break;
            case Cmd_PV_OpHrsPump :
                usart_send_data_to_cloud(data_payload_str, data_cl, "op_hrs_pump");
                break;
            case Cmd_PV_OpHrsElec :
                usart_send_data_to_cloud(data_payload_str, data_cl, "op_hrs_elec");
                break;
            case Cmd_PV_TempElec :
                usart_send_data_to_cloud(data_payload_str, data_cl, "temp_elec" );
                break;
            case Cmd_QL_StatusCCB :
                usart_send_data_to_cloud(data_payload_str, data_cl, "status_ccb");
                break;
            case Cmd_MB_Status :
                usart_send_data_to_cloud(data_payload_str, data_cl, "status");
                break;
            default:
                uart_debug("Invalid Topic \r\n");
                break;
        }
    }
    return true;
}

//TODO: Multiple data at the same time
//TODO: test
#ifndef TEST
bool usart_parse_get_data( uint32_t SEQ, uint8_t *input, uint16_t list_len)
{
    // TOPIC1_H | TOPIC1_L | TOPICx_H | TOPICx_L.... 
    uint16_t i = 0;
    uint8_t data_topic_h, data_topic_l;
    uint16_t mqtt_topic;
    uint32_t data_payload;
    uint8_t payload_array[4];
    uint8_t payload_len;
    enum eDataType data_type ;

    uart_debug("list_len %i", list_len);

    while( i < list_len)
    {
        data_topic_h = input[i];
        data_topic_l = input[i+1];

        mqtt_topic = ( ((uint16_t) data_topic_h) << 8 ) + data_topic_l;

        i += 3;

        uart_debug("MQTT Number: %" PRIu16, mqtt_topic);

        // TODO: Hashtable for Topics remove case here
        switch( mqtt_topic)
        {
            case Cmd_PV_Heating:
                if( !usart_check_incoming_data_from_cloud("Heating", &data_payload))
                {
                    return false;
                }
                data_type = DTYPE_UINT;
                break; 
            case Cmd_PV_ActualSpd :
                if( !usart_check_incoming_data_from_cloud("ActualSpd", &data_payload))
                {
                    return false;
                }
                data_type = DTYPE_UINT;
                break;
            case Cmd_PV_DrvCurrent :
                if( !usart_check_incoming_data_from_cloud("DrvCurrent", &data_payload))
                {
                    return false;
                }
                data_type = DTYPE_UINT;
                break;
            case Cmd_PV_OpHrsPump :
                if( !usart_check_incoming_data_from_cloud("OpHrsPump", &data_payload))
                {
                    return false;
                }
                data_type = DTYPE_UINT;
                break;
            case Cmd_PV_OpHrsElec :
                if( !usart_check_incoming_data_from_cloud("OpHrsElec", &data_payload))
                {
                    return false;
                }
                data_type = DTYPE_UINT;
                break;
            case Cmd_PV_TempElec :
                if( !usart_check_incoming_data_from_cloud("TempElec", &data_payload ))
                {
                    return false;
                }
                data_type = DTYPE_UINT;
                break;
            case Cmd_QL_StatusCCB :
                if( !usart_check_incoming_data_from_cloud("StatusCCB", &data_payload))
                {
                    return false;
                }
                data_type = DTYPE_UINT;
                break;
            case Cmd_MB_Status :
                if( !usart_check_incoming_data_from_cloud("Status", &data_payload))
                {
                    return false;
                }
                data_type = DTYPE_UINT;
                break;
            case Cmd_MB_EnablePump:
                if( !usart_check_incoming_data_from_cloud("enable_pump", &data_payload))
                {
                    return false;
                }
                data_type = DTYPE_BOOL_NEW;
                break;
            case Cmd_MB_LedOnOff:
                if( !usart_check_incoming_data_from_cloud("led_on_off", &data_payload) )
                {
                    return false;
                }
                data_type = DTYPE_UINT;
                break;
            default:
                usart_send_NAK_to_IoT_board( SEQ );
                uart_debug("Invalid Topic \r\n");
                break;
        }

        uart_debug("payload %"PRIu32, data_payload);
        payload_len = usart_u32_to_hex_array(data_payload, payload_array); 
        usart_send_ACK_with_DATA_to_IoT_board( SEQ, data_type, payload_array, payload_len );

    }
    return true;
}
#endif

uint16_t usart_get_crc( uint8_t *uart_msg, uint16_t LL)
{
    uint8_t CRCH, CRCL;
    CRCL = uart_msg[10+LL+1];
    CRCH = uart_msg[10+LL+2];

    return ( ((uint16_t) CRCH) << 8) + CRCL; 
}


bool usart_msg2ext( uint8_t *uart_msg, t_usart_msg_to_ext * extender)
{
    if( !usart_get_header( uart_msg, &(extender->header) ) ) 
    {
        uart_debug("invalid header");
        return false; 
    }

    if( !usart_is_valid_ocd ( extender->header.OCD ) )
    {
        uart_debug("invalid ocd");
        return false; 
    }

    if( ! usart_is_valid_msg_address ( extender->header.ADR ) )
    {
        uart_debug("invalid address");
        return false; 
    }

    extender->cmd_list = usart_get_cmd_list( uart_msg );
    extender->CRC = usart_get_crc( uart_msg, extender->header.LL );

    uint16_t crc_check = 0;
    uint16_t data_for_crc = D_HEADER_LENGTH + extender->header.LL;  

    crc_check = usart_crc_calc( uart_msg, data_for_crc );

    if ( extender->CRC != crc_check )
    {
        uart_debug("invalid crc");
        return false;
    }

    uart_debug("correct datagram");

    return true;
}

// TODO: Proper test for this function
uint16_t usart_crc_calc (uint8_t *buf, uint16_t data_byte_len)
{
    uint16_t crc = 0xFFFF;

    for (uint16_t pos = 0; pos < data_byte_len; pos++) 
    {
        crc ^= (uint16_t)buf[pos];
        /* xor byte into least sig.  byte of crc */
        for (int i = 8; i != 0; i--) 
        {
            /* loop over each bit */
            if ((crc & 0x0001) != 0) 
            {
                /* if the lsb is set */
                crc >>= 1;
                /* shift right and xor
                   0xA001 */
                crc ^= 0xA001;
            } 
            else  /* else lsb is not set */
            {
                crc >>= 1; /* just shift right */
            }
        }
    }

    return crc;
}


bool usart_is_valid_ocd (uint8_t ocd_id)
{
    bool valid = false;

    switch(ocd_id) 
    {
        case OCD_GET:
        case OCD_GET_DATA:
        case OCD_SET:
        case OCD_SET_DATA: 
        case OCD_ACK: 
        case OCD_NAK: 
            valid = true;
            break;
        default:
            uart_debug("OCD: This is exceptional. Shouldn't occur");
            valid = false;
            break;
    };
    return valid;
}

bool usart_is_valid_msg_address (uint8_t dst_addr_id)
{
    bool valid = false;

    switch(dst_addr_id) 
    {
        case ADDR_IOTB: 
        case ADDR_CCB: 
            valid = true;
            break;
        default:
            uart_debug("ADDR: This is exceptional. Shouldn't occur");
            valid = false;
            break;

    };
    return valid;
}



