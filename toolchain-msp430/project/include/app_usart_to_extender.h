#ifndef _APP_USART_TO_EXTENDER_H_ 
#define _APP_USART_TO_EXTENDER_H_ 

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "ATparser.h"
#include "uart.h"
#include "std_casted.h"
#include "rtc.h"

#define D_MAX_NUM_COMMANDS      (0)

typedef struct {
    uint16_t    ID;
    uint8_t     CL;
    uint8_t*    PAYLOAD;
} t_usart_msg_cmd;

typedef struct {
    uint16_t    LL;
    uint8_t     VER; 
    uint8_t     ADR;
    uint8_t     OCD;
    uint32_t    SEQ;
} t_usart_msg_header;

typedef struct {
    t_usart_msg_header  header;
    uint8_t     *cmd_list;
    uint16_t    CRC;
} t_usart_msg_to_ext;

#define D_INVALID_BYTE          (0xFF)
#define D_INVALID_QWORD         (0xFFFFFFFF)
#define D_PROT_MESSAGE_VERSION  (0x01)
#define D_PARAM_LEN             (0xFF)
#define D_MinRxTelegramLen      (PosPayloadData + 2)
#define D_FlagHdrStart          (0x68)
#define D_FlagHdrEnd            (0x69)

enum eCmdId{
    Cmd_PV_Heating = 1, 
    Cmd_PV_ActualSpd = 309,
    Cmd_PV_DrvCurrent = 310,
    Cmd_PV_OpHrsPump = 311,
    Cmd_PV_OpHrsElec = 314,
    Cmd_PV_TempElec = 326,
    Cmd_QL_StatusCCB = 1024,
    Cmd_MB_Status = 1280,
    Cmd_MB_EnablePump = 1281,
    Cmd_MB_LedOnOff = 1282
};

enum eRxBytePos {
    PosHdrFlagStart = 0,
    PosHdrLen = 1,
    PosHdrVersion = 3,
    PosHdrRcvAddress = 4,
    PosHdrOcd = 5,
    PosHrdSeq = 6,
    PosHdrFlagEnd = 10,
    PosPayloadData = 11
};


enum eMsgStates {
    StHdrFlagStart = 0,
    StHdrLen = 1,
    StHdrVersion = 2,
    StHdrDstAddress = 3,
    StHdrOcd = 4,
    StHrdSeq = 5,
    StHdrFlagEnd = 6,
    StPayloadData = 7,
    StCrcCalc = 8,
    StError = 9
};


enum eOcdType {
    OCD_GET = 0,
    OCD_SET = 2,
    OCD_ACK = 4,
    OCD_NAK = 5,
    OCD_GET_DATA = 6,
    OCD_SET_DATA = 7
};

enum eDataType {
    DTYPE_BOOL_OLD = 0,
    DTYPE_UINT = 1,
    DTYPE_REAL = 2,
    DTYPE_STRING = 4,
    DTYPE_BOOL_NEW = 6,
    DTYPE_USHORT = 7,
    DTYPE_EXPO_N = 10
};


enum eAddrType {
    ADDR_IOTB = 0,
    ADDR_CCB = 1 
};


enum eACK_states{
    STATE_ACK = 0,
    STATE_NAK = 1
};

enum eConf{
    POWERMODE = 0x400,
    APN = 0x401,
    MQTT_USERNAME = 0x402,
    MQTT_PASSWORD = 0x403,
    MQTT_SERVER = 0x404,
    RADIO_SIGNAL_QUALITY = 0x405,
    ERROR_CODE = 0x406,
    CLR = 0x407
};

enum ePowerStatus{
    POWER_OFF = 0,
    POWER_ON = 2
};


void usart_init_configuration(void);
bool usart_connect_cloud(void);
bool usart_disconnect_cloud(void);

uint8_t*    usart_read_from_IoT_board(void);
bool usart_send_to_IoT_board( uint8_t data, uint16_t topic);

bool usart_send_NAK_to_IoT_board( uint32_t SEQ);
bool usart_send_ACK_to_IoT_board( uint32_t SEQ);
bool usart_send_ACK_with_DATA_to_IoT_board( uint32_t SEQ, uint8_t data_type, uint8_t *payload, uint8_t len );


bool usart_msg2ext( uint8_t *uart_msg, t_usart_msg_to_ext * extender);

bool        usart_get_header( uint8_t *uart_msg, t_usart_msg_header *header);
uint8_t*    usart_get_cmd_list( uint8_t *uart_msg );
uint16_t    usart_get_crc( uint8_t *uart_msg, uint16_t LL);
uint8_t usart_get_powermode(void);

uint8_t * usart_get_apn_server(void);

bool usart_send_data_to_cloud(uint8_t* raw_data, uint16_t data_len, uint8_t* mqtt_topic);
bool usart_check_incoming_data_from_cloud(uint8_t* mqtt_topic, uint32_t *payload);

uint16_t usart_crc_calc (uint8_t *buf, uint16_t data_byte_len);

bool usart_is_valid_ocd (uint8_t ocd_id);
bool usart_is_valid_msg_address (uint8_t dst_addr_id);

bool usart_parse_cmd_list( t_usart_msg_to_ext *extender );
bool usart_parse_ocd( t_usart_msg_to_ext *extender );
bool usart_parse_data_list( uint8_t *data_list, uint16_t list_len);
bool usart_parse_get_data( uint32_t SEQ, uint8_t *input, uint16_t list_len);

// uint8_t usart_execute_cmd( uint8_t OCD, t_usart_msg_cmd *cmd_struct);
bool usart_execute_cmd( t_usart_msg_header *header, t_usart_msg_cmd *cmd_struct);

uint32_t usart_hex_array_to_u32(uint8_t *hex_array, uint8_t len);
uint8_t usart_u32_to_str( uint32_t u32, uint8_t *str);
uint8_t usart_u32_to_hex_array(uint32_t number, uint8_t *hex_array);


#endif // _APP_USART_TO_EXTENDER_H_ 


