/*
 * General form of the PARTITION2 (start, size, id, flags)
 *
 * \[start]  The physical start address of the partition entry in Flash
 * \[size]   The size of the partition entry in bytes. Since the underlying flash consists of
 *           4K sectors, a partition entry should be multiple of 4 kBytes (0x1000)
 *
 * \[id]     A value from the [nvms_partition_id_t] enumerator or a custom one.
 * \[flags]  Indicates the permission attributes. Valid values are:
 *
 *           0, PARTITION_FLAG_READ_ONLY, PARTITION_FLAG_VES
 */

PARTITION2( 0x000000 , 0x07F000 , NVMS_FIRMWARE_PART        , 0 )
PARTITION2( 0x07F000 , 0x001000 , NVMS_PARTITION_TABLE      , PARTITION_FLAG_READ_ONLY )
PARTITION2( 0x080000 , 0x010000 , NVMS_PARAM_PART           , 0 )
PARTITION2( 0x090000 , 0x010000 , NVMS_BIN_PART             , 0 )
PARTITION2( 0x0A0000 , 0x001000 , NVMS_CUSTOM_ENTRY_ONE     , 0 )
PARTITION2( 0x0A1000 , 0x001000 , NVMS_CUSTOM_ENTRY_TWO     , 0 )
PARTITION2( 0x0A2000 , 0x020000 , NVMS_LOG_PART             , 0 )
PARTITION2( 0x0C2000 , 0x020000 , NVMS_GENERIC_PART         , PARTITION_FLAG_VES )

