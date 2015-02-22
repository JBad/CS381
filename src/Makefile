#
# OMNeT++/OMNEST Makefile for CS381
#
# This file was generated with the command:
#  opp_makemake -f --deep -I/Users/jessebadash/Downloads/inet/src/linklayer/ieee80211/radio -I/Users/jessebadash/Downloads/inet/src/networklayer/routing/aodv -I/Users/jessebadash/Downloads/inet/src/networklayer/common -I/Users/jessebadash/Downloads/inet/src/networklayer/icmpv6 -I/Users/jessebadash/Downloads/inet/src -I/Users/jessebadash/Downloads/inet/src/world/obstacles -I/Users/jessebadash/Downloads/inet/src/networklayer/xmipv6 -I/Users/jessebadash/Downloads/inet/src/networklayer/contract -I/Users/jessebadash/Downloads/inet/src/networklayer/autorouting/ipv4 -I/Users/jessebadash/Downloads/inet/src/util -I/Users/jessebadash/Downloads/inet/src/transport/contract -I/Users/jessebadash/Downloads/inet/src/linklayer/common -I/Users/jessebadash/Downloads/inet/src/status -I/Users/jessebadash/Downloads/inet/src/linklayer/radio/propagation -I/Users/jessebadash/Downloads/inet/src/linklayer/ieee80211/radio/errormodel -I/Users/jessebadash/Downloads/inet/src/linklayer/radio -I/Users/jessebadash/Downloads/inet/src/util/headerserializers/tcp -I/Users/jessebadash/Downloads/inet/src/networklayer/ipv4 -I/Users/jessebadash/Downloads/inet/src/mobility/contract -I/Users/jessebadash/Downloads/inet/src/util/headerserializers/ipv4 -I/Users/jessebadash/Downloads/inet/src/base -I/Users/jessebadash/Downloads/inet/src/util/headerserializers -I/Users/jessebadash/Downloads/inet/src/world/radio -I/Users/jessebadash/Downloads/inet/src/linklayer/ieee80211/mac -I/Users/jessebadash/Downloads/inet/src/networklayer/ipv6 -I/Users/jessebadash/Downloads/inet/src/transport/sctp -I/Users/jessebadash/Downloads/inet/src/util/headerserializers/udp -I/Users/jessebadash/Downloads/inet/src/networklayer/ipv6tunneling -I/Users/jessebadash/Downloads/inet/src/applications/pingapp -I/Users/jessebadash/Downloads/inet/src/battery/models -I/Users/jessebadash/Downloads/inet/src/util/headerserializers/ipv6 -I/Users/jessebadash/Downloads/inet/src/util/headerserializers/sctp -I/Users/jessebadash/Downloads/inet/src/linklayer/contract -I/Users/jessebadash/Downloads/inet/src/transport/tcp_common -I/Users/jessebadash/Downloads/inet/src/networklayer/arp -I/Users/jessebadash/Downloads/inet/src/transport/udp -L/Users/jessebadash/Downloads/inet/out/$$\(CONFIGNAME\)/src -linet -DINET_IMPORT -KINET_PROJ=/Users/jessebadash/Downloads/inet
#

# Name of target to be created (-o option)
TARGET = CS381$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I$(INET_PROJ)/src/linklayer/ieee80211/radio \
    -I$(INET_PROJ)/src/networklayer/routing/aodv \
    -I$(INET_PROJ)/src/networklayer/common \
    -I$(INET_PROJ)/src/networklayer/icmpv6 \
    -I$(INET_PROJ)/src \
    -I$(INET_PROJ)/src/world/obstacles \
    -I$(INET_PROJ)/src/networklayer/xmipv6 \
    -I$(INET_PROJ)/src/networklayer/contract \
    -I$(INET_PROJ)/src/networklayer/autorouting/ipv4 \
    -I$(INET_PROJ)/src/util \
    -I$(INET_PROJ)/src/transport/contract \
    -I$(INET_PROJ)/src/linklayer/common \
    -I$(INET_PROJ)/src/status \
    -I$(INET_PROJ)/src/linklayer/radio/propagation \
    -I$(INET_PROJ)/src/linklayer/ieee80211/radio/errormodel \
    -I$(INET_PROJ)/src/linklayer/radio \
    -I$(INET_PROJ)/src/util/headerserializers/tcp \
    -I$(INET_PROJ)/src/networklayer/ipv4 \
    -I$(INET_PROJ)/src/mobility/contract \
    -I$(INET_PROJ)/src/util/headerserializers/ipv4 \
    -I$(INET_PROJ)/src/base \
    -I$(INET_PROJ)/src/util/headerserializers \
    -I$(INET_PROJ)/src/world/radio \
    -I$(INET_PROJ)/src/linklayer/ieee80211/mac \
    -I$(INET_PROJ)/src/networklayer/ipv6 \
    -I$(INET_PROJ)/src/transport/sctp \
    -I$(INET_PROJ)/src/util/headerserializers/udp \
    -I$(INET_PROJ)/src/networklayer/ipv6tunneling \
    -I$(INET_PROJ)/src/applications/pingapp \
    -I$(INET_PROJ)/src/battery/models \
    -I$(INET_PROJ)/src/util/headerserializers/ipv6 \
    -I$(INET_PROJ)/src/util/headerserializers/sctp \
    -I$(INET_PROJ)/src/linklayer/contract \
    -I$(INET_PROJ)/src/transport/tcp_common \
    -I$(INET_PROJ)/src/networklayer/arp \
    -I$(INET_PROJ)/src/transport/udp \
    -I.

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L$(INET_PROJ)/out/$(CONFIGNAME)/src  -linet
LIBS += -Wl,-rpath,`abspath $(INET_PROJ)/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cpp and .msg files
OBJS = $O/BitTrackerApp.o $O/P2PApp.o $O/CSAppMsg_m.o

# Message files
MSGFILES = \
    CSAppMsg.msg

# Other makefile variables (-K)
INET_PROJ=/Users/jessebadash/Downloads/inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS) -DINET_IMPORT $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cpp

$O/%.o: %.cpp $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cpp %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cpp $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f CS381 CS381.exe libCS381.so libCS381.a libCS381.dll libCS381.dylib
	$(Q)-rm -f ./*_m.cpp ./*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cpp

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/BitTrackerApp.o: BitTrackerApp.cpp \
	BitTrackerApp.h \
	CSAppMsg_m.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INET_PROJ)/src/transport/contract/TCPSocketMap.h
$O/P2PApp.o: P2PApp.cpp \
	CSAppMsg_m.h \
	P2PApp.h \
	$(INET_PROJ)/src/base/Compat.h \
	$(INET_PROJ)/src/base/INETDefs.h \
	$(INET_PROJ)/src/networklayer/contract/IPv4Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPv6Address.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddress.h \
	$(INET_PROJ)/src/networklayer/contract/IPvXAddressResolver.h \
	$(INET_PROJ)/src/transport/contract/TCPCommand_m.h \
	$(INET_PROJ)/src/transport/contract/TCPSocket.h \
	$(INET_PROJ)/src/transport/contract/TCPSocketMap.h

