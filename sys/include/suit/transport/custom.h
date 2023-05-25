/*
 * Copyright (C) 2019 Kaspar Schleiser <kaspar@schleiser.de>
 *               2019 Inria
 *               2019 Freie Universität Berlin
 *               2023 Université Grenoble Alpes
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     sys_suit
 * @defgroup    sys_suit_transport_custom SUIT firmware Custom transport
 * @brief       SUIT secure firmware updates over custom protocols
 *
 * @{
 *
 * @brief       SUIT Custom helper API
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Francisco Molina <francois-xavier.molina@inria.fr>
 * @author      Alexandre Abadie <alexandre.abadie@inria.fr>
 * @author      Didier Donsez <@donsez>
 *
 */

#ifndef SUIT_TRANSPORT_CUSTOM_H
#define SUIT_TRANSPORT_CUSTOM_H

#ifndef SUIT_TRANSPORT_CUSTOM_ROOTDIR
#error "SUIT_TRANSPORT_CUSTOM_ROOTDIR should be defined"
#endif

#include "net/nanocoap.h"
#include "suit.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief url handler for worker.c
 *
 * @param[in]   url    				  suit manifest context
 * @param[in]   manifest_buf          buffer for the manifest
 * @param[in]   manifest_buf_size     max size of the buffer for the manifest
 *
 * @returns     the size if successful
 * @returns     negative otherwise
 */
int suit_transport_custom_handle_url(const char *url, uint8_t *manifest_buf, const size_t manifest_buf_size);

/**
 * @brief fetch a payload with custom protocol
 *
 * @param[in]   manifest    suit manifest context
 * @param[in]   cb          filesystem block callback
 * @param[in]   ctx         callback context
 *
 * @returns     SUIT_OK if valid
 * @returns     negative otherwise
 */
int suit_transport_custom_fetch(const suit_manifest_t *manifest, coap_blockwise_cb_t cb, void *ctx);


#ifdef __cplusplus
}
#endif

#endif /* SUIT_TRANSPORT_CUSTOM_H */
/** @} */
