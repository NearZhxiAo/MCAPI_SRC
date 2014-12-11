/*===============================================================
*   Copyright (C) 2014 All rights reserved.
*   
*   文件名称：example_sender_message.c
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
#define NAME "SEND: "

int main(int argc,char*argv[])
{
	mcapi_status_t status;
	mcapi_info_t info;
	char status_msg[MCAPI_MAX_STATUS_MSG_LEN];

	mcapi_request_t request;
	size_t size=1;
	
	mcapi_endpoint_t send_msg_point;
	mcapi_endpoint_t recv_msg_point;

	char send_buf[BUFLEN]="HelloWorld";

	mcapi_initialize(THE_DOMAIN,RED_NODE,0,0,&info,&status);

	send_msg_point=mcapi_endpoint_create(RED_MSG,&status);
	recv_msg_point=mcapi_endpoint_get(THE_DOMAIN,YELLOW_NODE,YELLOW_MSG,TIMEOUT,&status);

	mcapi_msg_send(send_msg_point,recv_msg_point,send_buf,1,0,&status);
	mcapi_finalize(&status);
	return EXIT_SUCCESS;
}
