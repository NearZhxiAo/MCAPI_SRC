/*===============================================================
*   Copyright (C) 2014 All rights reserved.
*   
*   文件名称：example_sender_pktchan.c
*   创 建 者：张 笑
*   创建日期：2014年12月08日
*   描    述：
*
*   更新日志：
*
================================================================*/
#include <stdlib.h>
#include <mcapi.h>
#include <stdio.h>
#include <string.h>

#define TIMEOUT 5000
#define BUFSIZE 1024

#define NAME "SEND: "

int main(int argc,char argv[])
{
	mcapi_status_t status;				//mcapi状态unsigned int 类型变量
	mcapi_info_t info;				//结构体，包含版本号，id，等基本信息所有的成员变量都是unsigned int类型

	/*#define MCAPI_MAX_STATUS_MSG_LEN 32*/
	char status_msg[MCAPI_MAX_STATUS_MSG_LEN];	//状态信息转化为字符串定义

	mcapi_request_t request;			//用来处理等待调用
	size_t size;					//某些调用中需要用到的参数
	size_t bufsize;
 
	mcapi_pktchan_send_hndl_t handy;		//channel 发送端句柄

	char * sendbuf=NULL;				//传输的buffer
	sendbuf=(char*)malloc(BUFSIZE*sizeof(char));	
	char tempbuf[BUFSIZE]="HelloWorld.";
	memcpy(sendbuf,tempbuf,strlen(tempbuf)+1);	//赋值
	bufsize=strlen(tempbuf);
	
	mcapi_endpoint_t send_point;			//endpoint定义。结构体
//	mcapi_endpoint_t recv_point;

	printf(NAME "Sender here!\n\r");


	/*通过domain_id node_id 来进行初始化*/
	mcapi_initialize(THE_DOMAIN,RED_NODE,0,0,&info,&status);

	/*将mcapi status转化为String*/
	mcapi_display_status(status,status_msg,MCAPI_MAX_STATUS_MSG_LEN);
	
	/*打印status结果*/
	printf(NAME "Result of initialization: %s\n\r",status_msg);
	
	printf(NAME "creating sending endpoint.\n\r");

	/*以port id 为参数创建channel endpoing*/
	send_point=mcapi_endpoint_create(YELLOW_PKT,&status);
#if 0	
	/*通过domain node port id获取通信另一端的endpoint*/
	printf(NAME "obtaining receiving endpoint.\n\r");
	recv_point=mcapi_endpoint_get(THE_DOMAIN,GREEN_NODE,GREEN_PKT,TIMEOUT,&status);
	usleep(1500000);

	/*创建packet channel*/
	printf(NAME "connecting the channel.\n\r");
	mcapi_pktchan_connect_i(send_point,recv_point,&request,&status);
	/*等待操作*/
	mcapi_wait(&request,&size,TIMEOUT,&status);
#endif
	/*发送端打开channel*/
	printf(NAME "opening the sending end of the channel.\n\r");
	mcapi_pktchan_send_open_i(&handy,send_point,&request,&status);
	/*等待操作*/
//	mcapi_wait(&request,&size,TIMEOUT,&status);

	/*传输数据*/
	printf(NAME "sending %s",sendbuf);
	mcapi_pktchan_send(handy,sendbuf,bufsize,&status);
	printf(NAME "sent\n\r");

	/*关闭发送终端*/
	printf(NAME "closing!\n\r");
	mcapi_pktchan_send_close_i(handy,&request,&status);
	/*等待操作*/
	mcapi_wait(&request,&size,TIMEOUT,&status);
	printf(NAME "closed!\n\r");

	/*结束操作*/
	mcapi_finalize(&status);

	return EXIT_SUCCESS;
}
