# This Makefile defines how to build a unix host application connected to an
# EM260 EZSP uart device.  This also works for Windows machines running Cygwin.
#

# Variables

CC = gcc
LD = gcc
SHELL = /bin/sh

INCLUDES= \
  -I. \
  -I./app/ezsp-uart-host \
  -I./app/framework/cli \
  -I./app/framework/cluster \
  -I./app/framework/gen \
  -I./app/framework/report \
  -I./app/framework/security \
  -I./app/framework/util \
  -I./app/framework/module \
  -I./app/builder/_replace_projectName_ \
  -I./app/util \
  -I./app/util/common \
  -I./app/util/concentrator \
  -I./app/util/ezsp \
  -I./app/util/gateway \
  -I./app/util/serial \
  -I./app/util/zigbee-framework \
  -I./app/framework/plugin/bacnet-protocol-tunnel \
  -I./app/framework/plugin/basic \
  -I./app/framework/plugin/color-control \
  -I./app/framework/plugin/commissioning \
  -I./app/framework/plugin/drlc \
  -I./app/framework/plugin/drlc-server \
  -I./app/framework/plugin/general-response-commands \
  -I./app/framework/plugin/generic-tunnel \
  -I./app/framework/plugin/groups-client \
  -I./app/framework/plugin/groups-server \
  -I./app/framework/plugin/ias-ace-zone \
  -I./app/framework/plugin/ias-wd-server \
  -I./app/framework/plugin/ias-zone-server \
  -I./app/framework/plugin/identify \
  -I./app/framework/plugin/interpan \
  -I./app/framework/plugin/key-establishment \
  -I./app/framework/plugin/level-control \
  -I./app/framework/plugin/messaging-client \
  -I./app/framework/plugin/messaging-server \
  -I./app/framework/plugin/network-find \
  -I./app/framework/plugin/on-off \
  -I./app/framework/plugin/ota-bootload \
  -I./app/framework/plugin/ota-client \
  -I./app/framework/plugin/ota-client-policy \
  -I./app/framework/plugin/ota-common \
  -I./app/framework/plugin/ota-server \
  -I./app/framework/plugin/ota-server-policy \
  -I./app/framework/plugin/ota-storage-common \
  -I./app/framework/plugin/ota-storage-posix-filesystem \
  -I./app/framework/plugin/ota-storage-simple \
  -I./app/framework/plugin/ota-storage-simple-eeprom \
  -I./app/framework/plugin/ota-storage-simple-ram \
  -I./app/framework/plugin/partner-link-key-exchange \
  -I./app/framework/plugin/price-client \
  -I./app/framework/plugin/price-server \
  -I./app/framework/plugin/scenes \
  -I./app/framework/plugin/scenes-client \
  -I./app/framework/plugin/simple-metering-client \
  -I./app/framework/plugin/simple-metering-server \
  -I./app/framework/plugin/smart-energy-registration \
  -I./app/framework/plugin/temperature-measurement \
  -I./app/framework/plugin/test \
  -I./app/framework/plugin/test-harness \
  -I./app/framework/plugin/thermostat \
  -I./app/framework/plugin/time-client \
  -I./app/framework/plugin/time-server \
  -I./app/framework/plugin/trust-center-keepalive \
  -I./app/framework/plugin/tunneling-client \
  -I./app/framework/plugin/tunneling-server \
  -I./hal \
  -I./hal/micro/generic \
  -I./hal/micro/unix/host \
  -I./stack

APP_BUILDER_OUTPUT_DIRECTORY=app/builder/_replace_projectName_
APP_BUILDER_CONFIG_HEADER=$(APP_BUILDER_OUTPUT_DIRECTORY)/_replace_projectName_.h
APP_BUILDER_STORAGE_FILE=$(APP_BUILDER_OUTPUT_DIRECTORY)/_replace_projectName__endpoint_config.h

DEFINES= \
  -DPHY_EM250 \
  -DAF_UART_HOST \
  -DUNIX \
  -DUNIX_HOST \
  -DPHY_NULL \
  -DBOARD_HOST \
  -DCONFIGURATION_HEADER=\"app/framework/util/config.h\" \
  -DEMBER_SERIAL1_MODE=EMBER_SERIAL_FIFO \
  -DEMBER_SERIAL1_TX_QUEUE_SIZE=128 \
  -DEMBER_SERIAL1_RX_QUEUE_SIZE=128 \
  -DEZSP_HOST \
  -DGATEWAY_APP \
  -DZA_GENERATED_HEADER=\"$(APP_BUILDER_CONFIG_HEADER)\" \
  -DATTRIBUTE_STORAGE_CONFIGURATION=\"$(APP_BUILDER_STORAGE_FILE)\" \
  -DPLATFORM_HEADER=\"hal/micro/unix/compiler/gcc.h\" \
  -DBOARD_HEADER=\"hal/micro/unix/host/board/host.h\" \
  _replace_dashDMacros_


OPTIONS= \
  -Wcast-align \
  -Wformat \
  -Wimplicit \
  -Wimplicit-int \
  -Wimplicit-function-declaration \
  -Winline \
  -Wlong-long \
  -Wmain \
  -Wnested-externs \
  -Wno-import \
  -Wparentheses \
  -Wpointer-arith \
  -Wredundant-decls \
  -Wreturn-type \
  -Wstrict-prototypes \
  -Wswitch \
  -Wunused-label \
  -Wunused-value \
  -ggdb \
  -O0

APPLICATION_FILES= \
  app/builder/_replace_projectName_/_replace_projectName__callbacks.c \
  app/ezsp-uart-host/ash-host-io.c \
  app/ezsp-uart-host/ash-host-queues.c \
  app/ezsp-uart-host/ash-host-ui.c \
  app/ezsp-uart-host/ash-host.c \
  app/framework/cli/core-cli.c \
  app/framework/cli/network-cli.c \
  app/framework/cli/ota-cli-client.c \
  app/framework/cli/ota-cli-common.c \
  app/framework/cli/ota-cli-server.c \
  app/framework/cli/plugin-cli.c \
  app/framework/cli/security-cli.c \
  app/framework/cli/zcl-cli.c \
  app/framework/cli/zdo-cli.c \
  app/framework/gen/call-command-handler.c \
  app/framework/gen/callback-stub.c \
  app/framework/gen/stack-handler-stub.c \
  app/framework/report/report-table.c \
  app/framework/security/af-node.c \
  app/framework/security/af-security-common.c \
  app/framework/security/af-trust-center.c \
  app/framework/security/crypto-state.c \
  app/framework/util/af-eeprom.c \
  app/framework/util/af-event-host.c \
  app/framework/util/af-event.c \
  app/framework/util/af-main-common.c \
  app/framework/util/af-main-host.c \
  app/framework/util/attribute-size.c \
  app/framework/util/attribute-storage.c \
  app/framework/util/attribute-table.c \
  app/framework/util/client-api.c \
  app/framework/util/fragmentation.c \
  app/framework/util/message.c \
  app/framework/util/print.c \
  app/framework/util/process-cluster-message.c \
  app/framework/util/process-global-message.c \
  app/framework/util/service-discovery-common.c \
  app/framework/util/service-discovery-host.c \
  app/framework/util/util.c \
  app/util/common/form-and-join-host-adapter.c \
  app/util/common/form-and-join-host-callbacks.c \
  app/util/common/form-and-join.c \
  app/util/common/library.c \
  app/util/concentrator/concentrator.c \
  app/util/ezsp/ezsp-callbacks.c \
  app/util/ezsp/ezsp-enum-decode.c \
  app/util/ezsp/ezsp-frame-utilities.c \
  app/util/ezsp/ezsp.c \
  app/util/ezsp/serial-interface-uart.c \
  app/util/gateway/backchannel.c \
  app/util/gateway/gateway.c \
  app/util/serial/command-interpreter2.c \
  app/util/serial/ember-printf-convert.c \
  app/util/serial/linux-serial.c \
  app/util/source-route-common.c \
  app/util/source-route-host.c \
  app/util/zigbee-framework/zigbee-device-common.c \
  app/util/zigbee-framework/zigbee-device-host.c \
  hal/micro/generic/ash-common.c \
  hal/micro/generic/buzzer-stub.c \
  hal/micro/generic/crc.c \
  hal/micro/generic/led-stub.c \
  hal/micro/generic/mem-util.c \
  hal/micro/generic/random.c \
  hal/micro/generic/system-timer.c \
  hal/micro/unix/host/micro.c \
_replace_includeFiles__replace_pluginFiles_ 

OUTPUT_DIR= build/_replace_projectName_
OUTPUT_DIR_CREATED= $(OUTPUT_DIR)/created
# Build a list of object files from the source file list, but all objects
# live in the $(OUTPUT_DIR) above.  The list of object files
# created assumes that the file part of the filepath is unique
# (i.e. the bar.c of foo/bar.c is unique across all sub-directories included).
APPLICATION_OBJECTS= $(shell echo $(APPLICATION_FILES) | xargs -n1 echo | sed -e 's^.*/\(.*\)\.c^$(OUTPUT_DIR)/\1\.o^')

APP_FILE= $(OUTPUT_DIR)/_replace_projectName_

CPPFLAGS= $(INCLUDES) $(DEFINES) $(OPTIONS)
LINK_FLAGS=

ifdef NO_READLINE
  CPPFLAGS += -DNO_READLINE
else
  LINK_FLAGS +=  \
    -lreadline \
    -lncurses
endif

# Rules

all: $(APP_FILE)

ifneq ($(MAKECMDGOALS),clean)
-include $(APPLICATION_OBJECTS:.o=.d)
endif

$(APP_FILE): $(APPLICATION_OBJECTS)
	$(LD) $^ $(LINK_FLAGS) -o $(APP_FILE)
	@echo -e '\n$@ build success'

clean:
	rm -rf $(OUTPUT_DIR)

$(OUTPUT_DIR_CREATED):
	mkdir -p $(OUTPUT_DIR)
	touch $(OUTPUT_DIR_CREATED)

# To facilitate generating all output files in a single output directory, we
# must create separate .o and .d rules for all the different sub-directories
# used by the source files.
# If additional directories are added that are not already in the
# $(APPLICATION_FILES) above, new rules will have to be created below.

# Object File rules

$(OUTPUT_DIR)/%.o: app/ezsp-uart-host/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/cli/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/cluster/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/gen/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/module/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/report/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/security/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/util/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/util/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/util/common/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/util/concentrator/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/util/ezsp/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/util/gateway/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/util/serial/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/util/zigbee-framework/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: hal/micro/generic/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: hal/micro/unix/host/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/bacnet-protocol-tunnel/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/basic/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/color-control/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/commissioning/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/drlc/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/drlc-server/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/general-response-commands/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/generic-tunnel/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/groups-client/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/groups-server/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ias-ace-zone/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ias-wd-server/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ias-zone-server/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/identify/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/interpan/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/key-establishment/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/level-control/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/messaging-client/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/messaging-server/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/network-find/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/on-off/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ota-bootload/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ota-client/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ota-client-policy/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ota-common/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ota-server/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ota-server-policy/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ota-storage-common/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ota-storage-posix-filesystem/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ota-storage-simple/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ota-storage-simple-eeprom/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/ota-storage-simple-ram/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/partner-link-key-exchange/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/price-client/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/price-server/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/scenes/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/scenes-client/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/simple-metering-client/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/simple-metering-server/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/smart-energy-registration/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/temperature-measurement/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/test/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/test-harness/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/thermostat/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/time-client/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/time-server/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/trust-center-keepalive/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/tunneling-client/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/framework/plugin/tunneling-server/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.o: app/builder/_replace_projectName_/%.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)

# Dependency rules

$(OUTPUT_DIR)/%.d: app/ezsp-uart-host/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/cli/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/cluster/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/gen/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/report/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/module/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/security/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/util/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/util/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/util/common/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/util/concentrator/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/util/ezsp/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/util/gateway/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/util/serial/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/util/zigbee-framework/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: hal/micro/generic/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: hal/micro/unix/host/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/bacnet-protocol-tunnel/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/basic/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/color-control/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/commissioning/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/drlc/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/drlc-server/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/general-response-commands/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/generic-tunnel/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/groups-client/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/groups-server/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ias-ace-zone/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ias-wd-server/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ias-zone-server/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/identify/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/interpan/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/key-establishment/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/level-control/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/messaging-client/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/messaging-server/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/network-find/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/on-off/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ota-bootload/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ota-client/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ota-client-policy/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ota-common/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ota-server/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ota-server-policy/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ota-storage-common/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ota-storage-posix-filesystem/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ota-storage-simple/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ota-storage-simple-eeprom/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/ota-storage-simple-ram/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/partner-link-key-exchange/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/price-client/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/price-server/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/scenes/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/scenes-client/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/simple-metering-client/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/simple-metering-server/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/smart-energy-registration/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/temperature-measurement/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/test/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/test-harness/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/thermostat/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/time-client/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/time-server/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/trust-center-keepalive/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/tunneling-client/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/framework/plugin/tunneling-server/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

$(OUTPUT_DIR)/%.d: app/builder/_replace_projectName_/%.c $(OUTPUT_DIR_CREATED)
	@set -e; $(CC) -MM $(CPPFLAGS) $<				\
		| sed 's^\($(*F)\)\.o[ :]*^$(OUTPUT_DIR)/\1.o $(OUTPUT_DIR)/$(@F) : ^g' > $(OUTPUT_DIR)/$(@F);	\
		echo 'created dependency file $(OUTPUT_DIR)/$(@F)';			\
		[ -s $(OUTPUT_DIR)/$(@F) ] || rm -f $(OUTPUT_DIR)/$(@F)

