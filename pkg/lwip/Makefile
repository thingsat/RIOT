PKG_NAME=lwip
PKG_URL=https://github.com/lwip-tcpip/lwip.git
# lwIP v2.1.3
PKG_VERSION=6ca936f6b588cee702c638eee75c2436e6cf75de
PKG_LICENSE=BSD-3-Clause

include $(RIOTBASE)/pkg/pkg.mk

LWIP_MODULES         = lwip_api lwip_core lwip_ipv4 lwip_ipv6 \
                       lwip_netif lwip_netif_ppp lwip_polarssl
## ADD LWIP_APPS
LWIP_MODULES +=        lwip_httpclient lwip_altcp_tls
LWIP_MODULES +=        lwip_mqtt

LWIP_USEMODULE       = $(filter $(LWIP_MODULES),$(USEMODULE))
LWIP_MODULE_MAKEFILE = $(RIOTBASE)/Makefile.base

.PHONY: $(LWIP_MODULES)

CFLAGS += -Wno-address
# When compiled e.g. with `CFLAGS += -DIP6_DEBUG=LWIP_DBG_ON`, debug output
# does not use the correct format specifiers and compilation fails. (All
# instances were differently named but same sized integer types, e.g. %lx
# for printing int when sizeof(int) == sizeof(long int).)
CFLAGS += -Wno-format

make_module = +$(QQ)"$(MAKE)" -C $(2) -f $(LWIP_MODULE_MAKEFILE) MODULE=$(1)

all: lwip

lwip: $(LWIP_USEMODULE)
	$(call make_module,$@,$(PKG_SOURCE_DIR))

lwip_api:
	$(call make_module,$@,$(PKG_SOURCE_DIR)/src/api)

lwip_core:
	$(call make_module,$@,$(PKG_SOURCE_DIR)/src/core)

lwip_ipv4:
	$(call make_module,$@,$(PKG_SOURCE_DIR)/src/core/ipv4)

lwip_ipv6:
	$(call make_module,$@,$(PKG_SOURCE_DIR)/src/core/ipv6)

lwip_netif:
	$(call make_module,$@,$(PKG_SOURCE_DIR)/src/netif)

lwip_netif_ppp:
	$(call make_module,$@,$(PKG_SOURCE_DIR)/src/netif/ppp)

lwip_polarssl:
	$(call make_module,$@,$(PKG_SOURCE_DIR)/src/netif/ppp/polarssl)

## ADD LWIP_APPS
lwip_httpclient:
	mkdir -p $(PKG_SOURCE_DIR)/src/apps/httpclient
	cp $(PKG_SOURCE_DIR)/src/apps/http/http_client.c $(PKG_SOURCE_DIR)/src/apps/httpclient
	$(call make_module,$@,$(PKG_SOURCE_DIR)/src/apps/httpclient)

lwip_altcp_tls:
	$(call make_module,$@,$(PKG_SOURCE_DIR)/src/apps/altcp_tls)

lwip_mqtt:
	$(call make_module,$@,$(PKG_SOURCE_DIR)/src/apps/mqtt)
