/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 *
 * @author      Martine Lenders <mlenders@inf.fu-berlin.de>
 * @author      Aymeric Brochier <aymeric.brochier@univ-grenoble-alpes.fr>
 * @}
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "common.h"
#include "od.h"
#include "net/af.h"
#include "net/sock/async/event.h"
#include "net/sock/udp.h"
#include "net/sock/util.h"
#include "shell.h"
#include "test_utils/expect.h"
#include "thread.h"
#include "ztimer.h"


#ifdef MODULE_LWIP_HTTPCLIENT

#include "lwip/apps/http_client.h"

/* GLOBAL */
httpc_connection_t http_settings;
httpc_state_t *connection;
ip4_addr_t host;

/* callback called each time we received some data */
err_t get_http_cb(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err){

    (void)arg;
    (void)err;

	for(uint16_t i = 0; i < p->len; i++){
		printf("%c", ((char*) p->payload)[i]);
    }

	/*
    printf("%d bytes received\n",p->len);
    simulate workload 1 sec
    ztimer_spin(ZTIMER_USEC,1000000);
    printf("%d bytes treated\n",p->len);
    */

    altcp_recved(tpcb, p->tot_len);
    pbuf_free(p);
	return ERR_OK;
}

/*if the download succeeds srv_res should be 200, httpc_result 0 (HTTPC_RESULT_OK) and rx_content_len!=0 */
void my_httpc_result_fn(void *arg, httpc_result_t httpc_result, u32_t rx_content_len, u32_t srv_res, err_t err)
{
    (void)arg;
    (void)err;

	printf("my_httpc_result_fn %d %ld %ld\n", httpc_result, rx_content_len, srv_res);

}
int http_cmd(int argc, char **argv)
{
    //TODO add check params

    uint8_t adress_array[4];
    split_adress(adress_array, argv[2]);
    IP4_ADDR(&host, adress_array[0], adress_array[1], adress_array[2], adress_array[3]);
    int port = atoi(argv[3]);
    char *uri = argv[4];

    http_settings.headers_done_fn = NULL;
    http_settings.result_fn = my_httpc_result_fn;
    http_settings.use_proxy = 0;

    if (argc < 2) {
        printf("usage: %s [GET|POST|PUT|DELETE]\n", argv[0]);
        return 1;
    }

    //see https://community.st.com/s/question/0D53W0000037blwSAA/how-to-use-httpcgetfile

    if (strcmp(argv[1], "GET") == 0 || strcmp(argv[1], "DELETE") == 0) {
    
        if (argc < 3) {
            printf("usage: %s %s <server_addr> <port> <uri>\n",
                   argv[0], argv[1]);
            return 1;
        }

        LOCK_TCPIP_CORE();
        /* body, boundary,filename empty in this case */
        err_t err = httpc_method_file(argv[1],&host, port, uri,"","","", &http_settings, get_http_cb, 0, &connection);
        UNLOCK_TCPIP_CORE();
        printf("err httpc_method_file %d\n", err);
    }
    else if (strcmp(argv[1], "PUT") == 0 || strcmp(argv[1], "POST") == 0) {

        if (argc < 7) {
            printf("usage: %s %s <server_addr> <port> <uri> <body> <filename>\n",
                   argv[0], argv[1]);
            return 1;
        }
        char* body = argv[5];
        //Can be anything
        char* boundary = "77c3bb86f7bf16daca9aa7acb34188d9";
        char* filename = argv[6];
        LOCK_TCPIP_CORE();
        int err = httpc_method_file(argv[1],&host, port, uri, body, boundary,filename, &http_settings, get_http_cb, 0, &connection);
        UNLOCK_TCPIP_CORE();

        printf("err httpc_method_file %d\n", err);
    }
    else {
        puts("error: invalid command");
        return 1;
    }
    return 0;
}
#else
typedef int dont_be_pedantic;
#endif

/** @} */
