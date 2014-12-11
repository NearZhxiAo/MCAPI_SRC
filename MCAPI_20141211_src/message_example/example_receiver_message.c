/*===============================================================
*   Copyright (C) 2014 All rights reserved.
*   
*   文件名称：example_reciver_message.c
*   创 建 者：张 笑
*   创建日期：2014年12月10日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdlib.h>
#include <string.h>
#include <mcapi.h>
#include <stdio.h>
#include <math.h>

#define BUFLEN 30

#define TIMEOUT 5000

#define NAME "RECV: "

int main(int argc,char * argv[])
{
	mcapi_status_t status;
	mcapi_info_t info;

	char status_msg[MCAPI_MAX_STATUS_MSG_LEN];
	size_t size;
	char recv_buf[BUFLEN]="";

	mcapi_request_t request;
	
	mcapi_endpoint_t recv_msg_point;

	mcapi_initialize(THE_DOMAIN,YELLOW_NODE,0,0,&info,&status);
	recv_msg_point=mcapi_endpoint_create(YELLOW_MSG,&status);
	mcapi_msg_recv(recv_msg_point,recv_buf,BUFLEN,&size,&status);
	printf("recvice message: %s\n\r",recv_buf);
	mcapi_finalize(&status);
	return EXIT_SUCCESS;
}
