/******************************************************************************
 * File: data_transport.h
 * Author: Cosiba
 * Date: 2016/10/14
 * Version: 1.0
 * Copyright: QiuMingShanShangLaoSiJi
 * Instruction: Defined the data structure and interfaces in the transportation
 *              between the client and server.
 *****************************************************************************/

#include <stdbool.h>

#define MAX_BUFF_LENGTH		0x8
#define CMD_SET 			0x1
#define CMD_SEND 			0x2

typedef unsigned int 	UINT32;
typedef unsigned char 	UINT8;
typedef unsigned char 	BUF_SIZE;

// Definition of data package
typedef struct data_transport
{
	UINT8 cmd;
	UINT32 addr_dest;
	UINT32 addr_src;
	BUF_SIZE *data_buf;
}Data_Transport;

typedef struct data_control
{
	UINT8 cmd;
	BUF_SIZE *data_buf;
}Data_Control;

typedef union data_package
{
	Data_Control 	dc;
	Data_Transport  dt;
}Data_Package;

/*
 * Function: data_serialization
 * Instruction: Interface of the serializaton of the data package
 * Parameters: (in) cmd: to specify the command type of the data package
 *             (in) addr_dest: to specify the target address which is sent to.
 *             When the parameter cmd is set as CMD_SET, a 0 should be set. 
 *             (in) data: point to the data buffer which is sent.
 *             (in) buf_length: the length of the buffer to be set
 *             (out) pack: point to the datapackage after serializaton
 * Return: ture for success, false for failure
 */
bool data_serialization(UINT8 cmd, UINT32 addr_dest, BUF_SIZE * data, int buf_length, Data_Package * pack);

/*
 * Function: data_unserialization
 * Instruction: Interface of the unserialization of the data package
 * Parameters: (out) cmd: point to an UINT32 that to specify the command type of the data package
 *             (out) addr_src: point to an address that to specify where the resouce address is the data from
 *             When the parameter cmd is read as CMD_SET, 0xffffffff will be return. 
 *             (out) data: point to the data buffer which is sent
 *             (in & out) buf_length: point to an intager that specify the length of
 *             the data recieved
 *             (in) pack: point to the datapackage after serializaton
 * Return: ture for success, false for failure
 */
bool data_unserialization(UINT8 * cmd, UINT32 * addr_src, BUF_SIZE * data, int * buf_length, Data_Package * pack);

/*
 * Function: data_initialization
 * Instruction: Interface for the user to initial the package buffer which to be use
 * Parameter: (in & out) pack_buf: the pointer to point to the package buffer to be initialed
 *            (in) cmd: the command type of the package
 *            (in) length_data: the length of the data to be transport
 * Return: true for success, false for failure
 */
bool data_initialization(Data_Package ** pack_buf, UINT8 cmd, int length_data);

/*
 * Function: data_delete
 * Instruction: Interface for the user to delete the package buffer which to be use
 * Parameter: (in) pack_buf: the pointer to point to the package buffer to be delete
 *            (in) cmd: the command type of the package
 * Return: void
 */
void data_delete(Data_Package ** pack_buf, UINT8 cmd);
