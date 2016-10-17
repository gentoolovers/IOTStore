#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_transport.h"

int main()
{
	int i = 0;
	UINT8 cmd = 0xff;
	UINT32 addr = 0xffffffff;
	int buf_length = 8;
	BUF_SIZE buf[8] = {0};
	Data_Package * dp1;
	Data_Package * dp2;
	
	if (!data_initialization(&dp1, CMD_SET, 8))
	{
		printf("fail\n");
		return 0;
	}

	if (!data_initialization(&dp2, CMD_SEND, 8))
	{
		printf("fail\n");
		return 0;
	}

	data_serialization(CMD_SET, 0, "cosiba", 6, dp1);
	printf("test: %d, %s\n", dp1->dc.cmd, dp1->dc.data_buf);
	if (data_unserialization(&cmd, &addr, buf, &buf_length, dp1))
		printf("test: %d, %s\n", cmd, buf);
	data_delete(&dp1, CMD_SET);

	memset(buf, 0, 8);

	data_serialization(CMD_SEND, 0x11111111, "king", 4, dp2);
	printf("test: %d, %x, %s\n", dp2->dt.cmd, dp2->dt.addr_dest, dp2->dt.data_buf);
	if (data_unserialization(&cmd, &addr, buf, &buf_length, dp2))
		printf("test: %d, %x, %s\n", cmd, addr, buf);
	data_delete(&dp2, CMD_SEND);
	return 0;
}
