##
## This file is part of the coreboot project.
##
## Copyright 2018 Google LLC
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; version 2 of the License.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##

bootblock-y += bootblock.c
bootblock-$(CONFIG_CHROMEOS) += chromeos.c

ramstage-y += ramstage.c
ramstage-$(CONFIG_CHROMEOS) += chromeos.c

romstage-y += romstage.c
romstage-$(CONFIG_CHROMEOS) += chromeos.c

verstage-$(CONFIG_CHROMEOS) += chromeos.c
smm-$(CONFIG_HAVE_SMI_HANDLER) += smihandler.c

subdirs-y += variants/baseboard
CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/variants/baseboard/include

VARIANT_DIR:=$(call strip_quotes,$(CONFIG_VARIANT_DIR))
subdirs-y += variants/$(VARIANT_DIR)
CPPFLAGS_common += -I$(src)/mainboard/$(MAINBOARDDIR)/variants/$(VARIANT_DIR)/include