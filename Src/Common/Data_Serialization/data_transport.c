/******************************************************************************
 * File: data_transport.c
 * Author: Cosiba
 * Date: 2016/10/14
 * Version: 1.0
 * Copyright: QiuMingShanShangLaoSiJi
 * Instruction: Defined the data structure and interfaces in the transportation
 *              between the client and server.
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_transport.h"

#define __RELEASE__		// CLOSE THIS DEFINE TO PRINT THE TARCE

bool data_serialization(UINT8 cmd, UINT32 addr_dest, BUF_SIZE * data, int buf_length, Data_Package * pack)
{
#ifndef __RELEASE__
	int i = 0;
	printf("--DEBUG: SERRIALIZATION\n");
#endif
	if (!data || !pack)
	{
#ifndef __RELEASE__
		printf("--DEBUG: NULL pointer in.\n");
#endif
		return false;
	}

	if (buf_length > MAX_BUFF_LENGTH)
	{
#ifndef __RELEASE__
		printf("--DEBUG: Out of buffer length.\n");
#endif
		return false;
	}
	
	if (cmd == CMD_SET)
	{
		pack->dc.cmd = cmd;
		memcpy(pack->dc.data_buf, data, buf_length);
#ifndef __RELEASE__
		printf("--DEBUG: ");
		for (i = 0; i < sizeof(Data_Control); i++)
		{
			printf("%d\t", ((char*)pack)[i]);
		}	
		printf("\n--DEBUG: length: %d, buffer: %s\n", strlen(pack->dc.data_buf), pack->dc.data_buf);
#endif	
		return true;
	}
	if (cmd == CMD_SEND)
	{
		pack->dt.cmd = cmd;
		pack->dt.addr_dest = addr_dest;
		memcpy(pack->dt.data_buf, data, buf_length);
#ifndef __RELEASE__
		printf("--DEBUG: ");
		for (i = 0; i < sizeof(Data_Transport); i++)
		{
			printf("%d\t", ((char*)pack)[i]);
		}	
		printf("\n--DEBUG: address: %x, length: %d, buffer: %s\n",pack->dt.addr_dest, strlen(pack->dt.data_buf), pack->dt.data_buf);
#endif	
		return true;
	}
	return false;
}

bool data_unserialization(UINT8 * cmd, UINT32 * addr_src, BUF_SIZE * data, int * buf_length, Data_Package * pack)
{
#ifndef __RELEASE__
	int i = 0;
	printf("--DEBUG: UNSERIALIZATION\n");
#endif
	if (!pack || !data)
	{
#ifndef __RELEASE__
		printf("--DEBUG: NULL pointer in.\n");
#endif
		return false;	
	}
	
	if (*buf_length > MAX_BUFF_LENGTH)
	{
#ifndef __RELEASE__
		printf("--DEBUG: Out of buffer length.\n");
#endif
		return false;
	}

	if (pack->dc.cmd == 0x1)
	{
#ifndef __RELEASE__
		printf("--DEBUG: ");
		for (i = 0; i < sizeof(Data_Package); i++)
		{
			printf("%d\t", ((char*)pack)[i]);
		}
		printf("\n--DEBUG: %s\n", pack->dc.data_buf);
#endif
		*cmd = CMD_SET;
		*buf_length = strlen(pack->dc.data_buf);
		memcpy(data, pack->dc.data_buf, *buf_length);
#ifndef __RELEASE__
		printf("--DEBUG: length: %d, buffer: %s, buffer addr: %p\n", *buf_length, data, pack->dc.data_buf);
#endif
		*addr_src = 0xffffffff;
		return true;
	}
	if (pack->dt.cmd == 0x2)
	{
#ifndef __RELEASE__
		printf("--DEBUG: ");
		for (i = 0; i < sizeof(Data_Package); i++)
		{
			printf("%d\t", ((char*)pack)[i]);
		}
		printf("--DEBUG: \n%s\n", pack->dt.data_buf);
#endif
		*cmd = CMD_SEND;
		*buf_length = strlen(pack->dt.data_buf);
		memcpy(data, pack->dt.data_buf, *buf_length);
		*addr_src = pack->dt.addr_src;
#ifndef __RELEASE__
		printf("--DEBUG: address: %x, length: %d, buffer: %s, buffer addr: %p\n", *addr_src, *buf_length, data, pack->dt.data_buf);
#endif
		return true;
	}
	return false;
}

bool data_initialization(Data_Package ** pack_buf, UINT8 cmd, int length_data)
{
	printf("--DEBUG: INITIALIZATION\n");
	if (!pack_buf)
	{
#ifndef __RELEASE__
		printf("--DEBUG: NULL pointer in.\n");
#endif	
		return false;
	}

	if (length_data < 0)
	{
#ifndef __RELEASE__
		printf("--DEBUG: data length of the initialed paramter could not less than 0.\n");
#endif
		return false;
	}

	if (cmd != CMD_SET && cmd != CMD_SEND)
	{
#ifndef __RELEASE__
		printf("--DEBUG: command unkown.\n");
#endif
		return false;
	}
	
	*pack_buf = (Data_Package*)malloc(sizeof(Data_Package));
	if (! (*pack_buf))
	{
#ifndef __RELEASE__
		printf("--DEBUG: malloc package fail.\n");
#endif
		return false;
	}
	memset(*pack_buf, 0, sizeof(Data_Package));

	if (cmd == CMD_SET)
	{
		(*pack_buf)->dc.data_buf = (char*)malloc(sizeof(char) * length_data);
		if ((*pack_buf)->dc.data_buf == NULL)
		{
#ifndef __RELEASE__
			printf("--DEBUG: malloc data_buf fail.\n");
#endif
			free(*pack_buf);
			return false;
		}
		memset((*pack_buf)->dc.data_buf, 0, length_data);
		return true;
	}
	else
	{
		(*pack_buf)->dt.data_buf = (char*)malloc(sizeof(char) * length_data);
		if ((*pack_buf)->dt.data_buf == NULL)
		{
#ifndef __RELEASE__
			printf("--DEBUG: malloc data_buf fail.\n");
#endif
			free(*pack_buf);
			return false;
		}
		memset((*pack_buf)->dt.data_buf, 0, length_data);
		return true;
	}
	return false;
}

void data_delete(Data_Package ** pack_buf, UINT8 cmd)
{
	printf("--DEBUG: DELETE\n");
	if (*pack_buf)
	{
		switch (cmd)
		{
		case CMD_SET:
			{
				if ((*pack_buf)->dc.data_buf)
				{
					free((*pack_buf)->dc.data_buf);
					(*pack_buf)->dc.data_buf = NULL;
					free(*pack_buf);
					*pack_buf = NULL;
				}
			}
			break;
		case CMD_SEND:
			{
				if ((*pack_buf)->dt.data_buf)
				{
					free((*pack_buf)->dt.data_buf);
					(*pack_buf)->dt.data_buf = NULL;
					free(*pack_buf);
					*pack_buf = NULL;
				}
			}
			break;
		default:
			break;
		}
	}
}
