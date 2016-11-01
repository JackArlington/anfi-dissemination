#
# OMNeT++/OMNEST Makefile for Flooding
#
# This file was generated with the command:
#  opp_makemake -f --deep -I../../veins-2.2/src/base/phyLayer -I../../veins-2.2/src/modules/utility -I../../veins-2.2/src/modules/analogueModel -I../../veins-2.2/src/modules/mac/ieee80211p -I../../veins-2.2/src/base/modules -I../../veins-2.2/src/base/utils -I../../veins-2.2/src/modules/phy -I../../veins-2.2/src/base/messages -I../../veins-2.2/src/modules/obstacle -I../../veins-2.2/src/base/connectionManager -I../../veins-2.2/src/modules -I../../veins-2.2/src/modules/application/ieee80211p -I../../veins-2.2/src/modules/messages -I../../veins-2.2/src/modules/mobility/traci -L../../veins-2.2/out/$$\(CONFIGNAME\)/src/base -L../../veins-2.2/out/$$\(CONFIGNAME\)/src/modules -L../../veins-2.2/out/$$\(CONFIGNAME\)/tests/testUtils -lmiximbase -lmiximmodules -lmiximtestUtils -KVEINS_2_2_PROJ=../../veins-2.2
#

# Name of target to be created (-o option)
TARGET = Flooding$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../veins-2.2/src/base/phyLayer \
    -I../../veins-2.2/src/modules/utility \
    -I../../veins-2.2/src/modules/analogueModel \
    -I../../veins-2.2/src/modules/mac/ieee80211p \
    -I../../veins-2.2/src/base/modules \
    -I../../veins-2.2/src/base/utils \
    -I../../veins-2.2/src/modules/phy \
    -I../../veins-2.2/src/base/messages \
    -I../../veins-2.2/src/modules/obstacle \
    -I../../veins-2.2/src/base/connectionManager \
    -I../../veins-2.2/src/modules \
    -I../../veins-2.2/src/modules/application/ieee80211p \
    -I../../veins-2.2/src/modules/messages \
    -I../../veins-2.2/src/modules/mobility/traci \
    -I. \
    -Imessages \
    -Irouting \
    -Irsu

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../veins-2.2/out/$(CONFIGNAME)/src/base -L../../veins-2.2/out/$(CONFIGNAME)/src/modules -L../../veins-2.2/out/$(CONFIGNAME)/tests/testUtils  -lmiximbase -lmiximmodules -lmiximtestUtils
LIBS += -Wl,-rpath,`abspath ../../veins-2.2/out/$(CONFIGNAME)/src/base` -Wl,-rpath,`abspath ../../veins-2.2/out/$(CONFIGNAME)/src/modules` -Wl,-rpath,`abspath ../../veins-2.2/out/$(CONFIGNAME)/tests/testUtils`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = $O/routing/Flooding.o $O/rsu/RSUApplication.o $O/messages/DataMessage_m.o

# Message files
MSGFILES = \
    messages/DataMessage.msg

# Other makefile variables (-K)
VEINS_2_2_PROJ=../../veins-2.2

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

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
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

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f Flooding Flooding.exe libFlooding.so libFlooding.a libFlooding.dll libFlooding.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h
	$(Q)-rm -f messages/*_m.cc messages/*_m.h
	$(Q)-rm -f routing/*_m.cc routing/*_m.h
	$(Q)-rm -f rsu/*_m.cc rsu/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc messages/*.cc routing/*.cc rsu/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/messages/DataMessage_m.o: messages/DataMessage_m.cc \
	messages/DataMessage_m.h \
	$(VEINS_2_2_PROJ)/src/base/utils/Coord.h \
	$(VEINS_2_2_PROJ)/src/base/utils/FWMath.h \
	$(VEINS_2_2_PROJ)/src/base/utils/MiXiMDefs.h \
	$(VEINS_2_2_PROJ)/src/base/utils/miximkerneldefs.h
$O/routing/Flooding.o: routing/Flooding.cc \
	messages/DataMessage_m.h \
	routing/Flooding.h \
	$(VEINS_2_2_PROJ)/src/base/connectionManager/BaseConnectionManager.h \
	$(VEINS_2_2_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(VEINS_2_2_PROJ)/src/base/connectionManager/NicEntry.h \
	$(VEINS_2_2_PROJ)/src/base/messages/MacPkt_m.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseApplLayer.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseBattery.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseLayer.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseMobility.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseModule.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BatteryAccess.h \
	$(VEINS_2_2_PROJ)/src/base/utils/Coord.h \
	$(VEINS_2_2_PROJ)/src/base/utils/FWMath.h \
	$(VEINS_2_2_PROJ)/src/base/utils/FindModule.h \
	$(VEINS_2_2_PROJ)/src/base/utils/HostState.h \
	$(VEINS_2_2_PROJ)/src/base/utils/MiXiMDefs.h \
	$(VEINS_2_2_PROJ)/src/base/utils/Move.h \
	$(VEINS_2_2_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(VEINS_2_2_PROJ)/src/base/utils/PassedMessage.h \
	$(VEINS_2_2_PROJ)/src/base/utils/SimpleAddress.h \
	$(VEINS_2_2_PROJ)/src/base/utils/miximkerneldefs.h \
	$(VEINS_2_2_PROJ)/src/modules/application/ieee80211p/BaseWaveApplLayer.h \
	$(VEINS_2_2_PROJ)/src/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h \
	$(VEINS_2_2_PROJ)/src/modules/messages/Mac80211Pkt_m.h \
	$(VEINS_2_2_PROJ)/src/modules/messages/WaveShortMessage_m.h \
	$(VEINS_2_2_PROJ)/src/modules/mobility/traci/TraCIColor.h \
	$(VEINS_2_2_PROJ)/src/modules/mobility/traci/TraCIMobility.h \
	$(VEINS_2_2_PROJ)/src/modules/mobility/traci/TraCIScenarioManager.h \
	$(VEINS_2_2_PROJ)/src/modules/obstacle/Obstacle.h \
	$(VEINS_2_2_PROJ)/src/modules/obstacle/ObstacleControl.h \
	$(VEINS_2_2_PROJ)/src/modules/utility/Consts80211p.h \
	$(VEINS_2_2_PROJ)/src/modules/world/annotations/AnnotationManager.h
$O/rsu/RSUApplication.o: rsu/RSUApplication.cc \
	messages/DataMessage_m.h \
	rsu/RSUApplication.h \
	$(VEINS_2_2_PROJ)/src/base/connectionManager/ChannelAccess.h \
	$(VEINS_2_2_PROJ)/src/base/messages/MacPkt_m.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseApplLayer.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseBattery.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseLayer.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseMobility.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseModule.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BaseWorldUtility.h \
	$(VEINS_2_2_PROJ)/src/base/modules/BatteryAccess.h \
	$(VEINS_2_2_PROJ)/src/base/utils/Coord.h \
	$(VEINS_2_2_PROJ)/src/base/utils/FWMath.h \
	$(VEINS_2_2_PROJ)/src/base/utils/FindModule.h \
	$(VEINS_2_2_PROJ)/src/base/utils/HostState.h \
	$(VEINS_2_2_PROJ)/src/base/utils/MiXiMDefs.h \
	$(VEINS_2_2_PROJ)/src/base/utils/Move.h \
	$(VEINS_2_2_PROJ)/src/base/utils/NetwToMacControlInfo.h \
	$(VEINS_2_2_PROJ)/src/base/utils/PassedMessage.h \
	$(VEINS_2_2_PROJ)/src/base/utils/SimpleAddress.h \
	$(VEINS_2_2_PROJ)/src/base/utils/miximkerneldefs.h \
	$(VEINS_2_2_PROJ)/src/modules/application/ieee80211p/BaseWaveApplLayer.h \
	$(VEINS_2_2_PROJ)/src/modules/mac/ieee80211p/WaveAppToMac1609_4Interface.h \
	$(VEINS_2_2_PROJ)/src/modules/messages/Mac80211Pkt_m.h \
	$(VEINS_2_2_PROJ)/src/modules/messages/WaveShortMessage_m.h \
	$(VEINS_2_2_PROJ)/src/modules/utility/Consts80211p.h

