# SPDX-License-Identifier: GPL-2.0
#
# Makefile for x86-compatible CPU details, features and quirks
#

# Don't trace early stages of a secondary CPU boot
ifdef CONFIG_FUNCTION_TRACER
CFLAGS_REMOVE_common.o = -pg
CFLAGS_REMOVE_perf_event.o = -pg
endif

# If these files are instrumented, boot hangs during the first second.
KCOV_INSTRUMENT_common.o := n
KCOV_INSTRUMENT_perf_event.o := n

# Make sure load_percpu_segment has no stackprotector
nostackp := $(call cc-option, -fno-stack-protector)
CFLAGS_common.o		:= $(nostackp)

obj-y			:= cacheinfo.o scattered.o topology.o
obj-y			+= common.o
obj-y			+= rdrand.o
obj-y			+= match.o
obj-y			+= bugs.o
obj-y			+= aperfmperf.o
obj-y			+= cpuid-deps.o

obj-$(CONFIG_PROC_FS)	+= proc.o
obj-$(CONFIG_X86_FEATURE_NAMES) += capflags.o powerflags.o

obj-$(CONFIG_CPU_SUP_INTEL)		+= intel.o intel_pconfig.o
obj-$(CONFIG_CPU_SUP_AMD)		+= amd.o
obj-$(CONFIG_CPU_SUP_HYGON)		+= hygon.o
obj-$(CONFIG_CPU_SUP_CYRIX_32)		+= cyrix.o
obj-$(CONFIG_CPU_SUP_CENTAUR)		+= centaur.o
obj-$(CONFIG_CPU_SUP_TRANSMETA_32)	+= transmeta.o
obj-$(CONFIG_CPU_SUP_UMC_32)		+= umc.o

obj-$(CONFIG_X86_MCE)			+= mce/
obj-$(CONFIG_MTRR)			+= mtrr/
obj-$(CONFIG_MICROCODE)			+= microcode/
obj-$(CONFIG_X86_CPU_RESCTRL)		+= resctrl/
obj-$(CONFIG_INTEL_SGX_CORE)		+= sgx/

obj-$(CONFIG_X86_LOCAL_APIC)		+= perfctr-watchdog.o

obj-$(CONFIG_HYPERVISOR_GUEST)		+= vmware.o hypervisor.o mshyperv.o

ifdef CONFIG_X86_FEATURE_NAMES
quiet_cmd_mkcapflags = MKCAP   $@
      cmd_mkcapflags = $(CONFIG_SHELL) $(srctree)/$(src)/mkcapflags.sh $< $@

cpufeature = $(src)/../../include/asm/cpufeatures.h

targets += capflags.c
$(obj)/capflags.c: $(cpufeature) $(src)/mkcapflags.sh FORCE
	$(call if_changed,mkcapflags)
endif
clean-files += capflags.c
