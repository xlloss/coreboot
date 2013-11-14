/*
 * This file is part of the coreboot project.
 *
 * Copyright 2010 Google Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

#include <arch/cache.h>
#include <arch/exception.h>
#include <arch/hlt.h>
#include <arch/stages.h>
#include <bootblock_common.h>
#include <cbfs.h>
#include <console/console.h>
#include <smp/node.h>

void main(void)
{
	const char *stage_name = "fallback/romstage";
	void *entry;
	uint32_t sctlr;

	/* Globally disable MMU, caches, and branch prediction (these should
	 * be disabled by default on reset) */
	sctlr = read_sctlr();
	sctlr &= ~(SCTLR_M | SCTLR_C | SCTLR_Z | SCTLR_I);
	write_sctlr(sctlr);

	arm_invalidate_caches();

	/*
	 * Re-enable icache and branch prediction. MMU and dcache will be
	 * set up later.
	 */
	sctlr = read_sctlr();
	sctlr |= SCTLR_Z | SCTLR_I;
	write_sctlr(sctlr);

	bootblock_cpu_init();
	bootblock_mainboard_init();

#if CONFIG_BOOTBLOCK_CONSOLE
	console_init();
	exception_init();
#endif

	entry = cbfs_load_stage(CBFS_DEFAULT_MEDIA, stage_name);

	if (entry) stage_exit(entry);
	hlt();
}
