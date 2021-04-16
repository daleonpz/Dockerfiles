#include <unity.h>
#include <stdio.h>
#include <stdint.h>

#include "app_usart_to_extender.h"
#include "std_casted.h"

#define _VER    (0x01)

// GET command OCD = 0x00
// CMD_EXAMPLE = 0xAABB

#define _LLH0   (0x00)
#define _LLL0   (0x03)
#define _LL0    ( ( ((uint16_t) _LLH0) << 8) + _LLL0)
#define _CMDH0  (0xAA)
#define _CMDL0  (0xBB)
#define _CMD_ID0 ( ( ((uint16_t) _CMDH0) << 8) + _CMDL0 )
#define _CL0    (0x00)


static uint8_t  msg_get[] = { 
    D_FlagHdrStart, _LLH0, _LLL0, _VER, ADDR_CCB , OCD_GET , 0xDE, 0xAD, 0xBE, 0xEF, D_FlagHdrEnd,// Header
    _CMDH0, _CMDL0, _CL0, 
    0xE2, 0x0B }; // CRC, need to be calculated

static uint8_t  msg_get_no_HrdStart[] = { 
    0xFA, 0xAF, _VER, 0x0A, OCD_GET , 0xDE, 0xAD, 0xBE, 0xEF, D_FlagHdrEnd,// Header
    0x00, 0x06, 0x00, 
    0x00, 0x00 }; // CRC, need to be calculated


static uint8_t  msg_get_no_HrdEnd[] = { 
    D_FlagHdrStart, 0xFA, 0xAF, _VER, 0x0A, OCD_GET , 0xDE, 0xAD, 0xBE, 0xEF, // Header
    0x00, 0x06, 0x00, 
    0x00, 0x00 }; // CRC, need to be calculated

void setUp(void)
{
}

void tearDown()
{
}


void test__read_header(void)
{
    t_usart_msg_header header;
    usart_get_header( msg_get,  &header);

    TEST_ASSERT_EQUAL_HEX16( _LL0, header.LL);
    TEST_ASSERT_EQUAL_HEX8( _VER, header.VER); 
    TEST_ASSERT_EQUAL_HEX8( ADDR_CCB, header.ADR);
    TEST_ASSERT_EQUAL_HEX8( OCD_GET, header.OCD);
    TEST_ASSERT_EQUAL_HEX64( 0xDEADBEEF, header.SEQ);
}

void test__read_header_complete(void)
{
    t_usart_msg_header header;
    bool hdr_error;
    hdr_error = usart_get_header( msg_get,  &header);
    
    TEST_ASSERT_TRUE(hdr_error);
}

void test__read_header_no_HdrStart(void)
{
    t_usart_msg_header header;
    bool hdr_error;
    hdr_error = usart_get_header( msg_get_no_HrdStart,  &header);

    TEST_ASSERT_FALSE(hdr_error);
}

void test__read_header_no_HdrEnd(void)
{
    t_usart_msg_header header;
    bool hdr_error;
    hdr_error = usart_get_header( msg_get_no_HrdEnd,  &header);

    TEST_ASSERT_FALSE(hdr_error);
}

void test_usart_get_crc(void)
{
    uint16_t crc = usart_crc_calc( msg_get, sizeof(msg_get)/sizeof(uint8_t) - 2) ; 
    uint16_t result_crc;
    result_crc = usart_get_crc(msg_get, _LL0);

    TEST_ASSERT_EQUAL_UINT16( crc, result_crc);
}


// void test__parse_comands_GET(void)
// {
//     t_usart_msg_cmd commands;
//     _parse_commands( msg_get, &commands);
// 
//     TEST_ASSERT_EQUAL_HEX16( _CMD_ID0, commands.ID);
//     TEST_ASSERT_EQUAL_HEX8 ( _CL0, command.CL);
// }
//
//

void test_usart_is_valid_ocd(void)
{
    bool result;
    result = usart_is_valid_ocd( 10 );
    TEST_ASSERT_FALSE(result);

    result = usart_is_valid_ocd( OCD_GET);
    TEST_ASSERT_TRUE(result);

    result = usart_is_valid_ocd( OCD_SET_DATA);
    TEST_ASSERT_TRUE(result);

    result = usart_is_valid_ocd( 0 );
    TEST_ASSERT_TRUE(result);
}

void test_usart_is_valid_msg_address(void)
{
    bool result;
    result = usart_is_valid_msg_address( 10 );
    TEST_ASSERT_FALSE(result);

    result = usart_is_valid_msg_address( ADDR_CCB);
    TEST_ASSERT_TRUE(result);

    result = usart_is_valid_msg_address( ADDR_IOTB);
    TEST_ASSERT_TRUE(result);

    result = usart_is_valid_msg_address( ADDR_CCB +1 );
    TEST_ASSERT_FALSE(result);
}

void test_usart_msg2ext_success(void)
{
    bool result;
    t_usart_msg_to_ext extender; 
    result =  usart_msg2ext( msg_get, &extender);

    TEST_ASSERT_TRUE(result);
}

void test_usart_msg2ext_with_error(void)
{
    bool result;
    t_usart_msg_to_ext extender; 
    result =  usart_msg2ext( msg_get_no_HrdEnd, &extender);

    TEST_ASSERT_FALSE(result);
}

void test_usart_hex_array_to_u32(void)
{
    uint8_t hex[] = {0x4e, 0x5e, 0x75, 0x49};
    uint16_t len = sizeof(hex)/sizeof(uint8_t);
    uint32_t number;

    number = usart_hex_array_to_u32(hex, len);

    TEST_ASSERT_EQUAL_UINT32( 1314813257,  number);
}

void test_usart_hex_array_to_u32_simple(void)
{
    uint8_t hex[] = {0x1, 0x00};
    uint16_t len = sizeof(hex)/sizeof(uint8_t);
    uint32_t number;

    number = usart_hex_array_to_u32(hex, len);

    TEST_ASSERT_EQUAL_UINT32( 256,  number);
}

void test_usart_hex_array_to_u32_simple_2(void)
{
    uint8_t hex[] = {232, 137};
    uint16_t len = sizeof(hex)/sizeof(uint8_t);
    uint32_t number;

    number = usart_hex_array_to_u32(hex, len);

    TEST_ASSERT_EQUAL_UINT32( 59529,  number);
}

void test_usart_hex_array_to_u32_verylongnumber(void)
{
    uint8_t hex[] = {0xF, 0x42, 0x3F };
    uint16_t len = sizeof(hex)/sizeof(uint8_t);
    uint32_t number;

    number = usart_hex_array_to_u32(hex, len);

    TEST_ASSERT_EQUAL_UINT32( 999999,  number);
}


void test_usart_u32_to_str_null(void)
{
    uint32_t num = 0;
    uint8_t str[7];
    uint8_t len;

    len = usart_u32_to_str(num, str);

    TEST_ASSERT_EQUAL_UINT8( 2, len);
}

void test_usart_u32_to_str(void)
{
    uint32_t num = 999999;
    uint8_t str[7];
    uint8_t len;

    len = usart_u32_to_str(num, str);

    TEST_ASSERT_EQUAL_UINT8( 7, len);
}

void test_usart_u32_to_hex_array(void)
{
    uint32_t num = 0xDEADBEEF;
    uint8_t array[4];
    uint8_t len;

    len = usart_u32_to_hex_array(num, array);

    TEST_ASSERT_EQUAL_UINT8( 4, len);
}

void test_usart_u32_to_hex_array_null(void)
{
    uint32_t num = 0;
    uint8_t array[4];
    uint8_t len;

    len = usart_u32_to_hex_array(num, array);

    TEST_ASSERT_EQUAL_UINT8( 1, len);
}

void test_usart_u32_to_hex_array_null_inbetween(void)
{
    uint32_t num = 0x00AA00BB;
    uint8_t array[4];
    uint8_t len;

    len = usart_u32_to_hex_array(num, array);

    TEST_ASSERT_EQUAL_UINT8( 3, len);
}

void test_usart_u32_to_hex_array_one_byte(void)
{
    uint32_t num = 0x000000BB;
    uint8_t array[4];
    uint8_t len;

    len = usart_u32_to_hex_array(num, array);

    TEST_ASSERT_EQUAL_UINT8( 1, len);
}
/* kommentiert die folgenden Linien aus, wenn du usart_parse_cmd_list testen will*/
/*
void test_usart_parse_cmd_list_1cmd(void)
{
    bool result;
    uint8_t cmd_list[] = { 0x00, 0x01, 0x03, 'a','b','\0'};
    uint16_t LL = sizeof(cmd_list)/sizeof(uint8_t);

    result = usart_parse_cmd_list( cmd_list, LL);

    TEST_IGNORE();

}

void test_usart_parse_cmd_list_1Cmd_NoPayload(void)
{
    bool result;
    uint8_t cmd_list[] = { 0x00, 0x01, 0x00};
    uint16_t LL = sizeof(cmd_list)/sizeof(uint8_t);

    result = usart_parse_cmd_list( cmd_list, LL );
    TEST_IGNORE();

}

void test_usart_parse_cmd_list_2cmds(void)
{
    bool result;
    uint8_t cmd_list[] = { 0x01, 0x01, 0x03, 'a','b','\0',0x02,0x02,0x02,'B','\0'};
    uint16_t LL = sizeof(cmd_list)/sizeof(uint8_t);

    result = usart_parse_cmd_list( cmd_list, LL );
    TEST_IGNORE();
}
*/


/* kommentiert die folgenden Linien aus, wenn du usart_parse_data_list testen will*/
/*
void test_usart_parse_data_list_1data(void)
{
    bool result;
    uint8_t data_list[] = {0x00, 0x01, 0x06, '3', '8', '8', '9', '3', '\0' }; 
    uint16_t LL = sizeof(data_list)/sizeof(uint8_t);

    result = usart_parse_data_list( data_list, LL);

    TEST_IGNORE();

}

void test_usart_parse_data_list_1data_with_overflow(void)
{
    bool result;
    uint8_t data_list[ ]= {0x00, 0x01, 0x06, '3', '8', '8', '9', '3', '\0','A','B','\0'};
    uint16_t LL = sizeof(data_list)/sizeof(uint8_t) - 3 ;

    result = usart_parse_data_list( data_list, LL);

    TEST_IGNORE();
}

void test_usart_parse_data_list_3topics(void)
{
    // 0x0101 = 257
    // 0x0505 = 1285
    bool result;
    uint8_t data_list[] = {0x01, 0x35, 0x06, '5', '5', '3', '3', '6', '\0', 0x01, 0x36, 0x06, '2', '1', '3', '3', '6', '\0', 0x01, 0x37, 0x05, '8', '8', '7', '1', '\0' };
    uint16_t LL = sizeof(data_list)/sizeof(uint8_t);

    result = usart_parse_data_list( data_list, LL );
    TEST_IGNORE();
}

void test_usart_parse_data_list_2topics_with_overflow(void)
{
    bool result;
    uint8_t data_list[] = {0x04, 0x00, 0x06, '3', '1', '6', '0', '3', '\0' , 0x01, 0x35, 0x06, '5', '4', '2', '4', '8', '\0', 'A', 'B','\0' };
    uint16_t LL = sizeof(data_list)/sizeof(uint8_t) - 3;

    result = usart_parse_data_list( data_list, LL );
    TEST_IGNORE();
}
*/
/***************************************/
/* end of usart_parse_data_list tests */
/***************************************/

