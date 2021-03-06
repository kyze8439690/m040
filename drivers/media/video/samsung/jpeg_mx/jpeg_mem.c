/* linux/drivers/media/video/samsung/jpeg_v2x/jpeg_mem.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 * http://www.samsung.com/
 *
 * Managent memory of the jpeg driver for encoder/docoder.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/errno.h>
#include <linux/vmalloc.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/io.h>

#include <asm/page.h>

#include <linux/cma.h>

#include "jpeg_mem.h"
#include "jpeg_core.h"


#if defined(CONFIG_VIDEOBUF2_CMA_PHYS)
void *jpeg_cma_init(struct jpeg_dev *dev)
{
	return vb2_cma_phys_init(&dev->plat_dev->dev, NULL, SZ_8K, false);
}

void jpeg_cma_resume(void *alloc_ctx) {}
void jpeg_cma_suspend(void *alloc_ctx) {}

const struct jpeg_vb2 jpeg_vb2_cma = {
	.ops		= &vb2_cma_phys_memops,
	.init		= jpeg_cma_init,
	.cleanup	= vb2_cma_phys_cleanup,
	.plane_addr	= vb2_cma_phys_plane_paddr,
	.resume		= jpeg_cma_resume,
	.suspend	= jpeg_cma_suspend,
	.cache_flush	= vb2_cma_phys_cache_flush,
	.set_cacheable	= vb2_cma_phys_set_cacheable,
};
#endif



