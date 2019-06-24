/*
 * Copyright (C) 2016 MediaTek Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See http://www.gnu.org/licenses/gpl-2.0.html for more details.
 */
#include <asm/page.h>
#include <linux/dma-mapping.h>
#include <linux/err.h>
#include <linux/highmem.h>
#include <linux/mm.h>
#include <linux/scatterlist.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/fdtable.h>
#include <linux/mutex.h>
#include <mmprofile.h>
#include <linux/debugfs.h>
#include <linux/kthread.h>
#include "mtk/mtk_ion.h"
#include "ion_profile.h"
#include "ion_drv_priv.h"
#include "ion_priv.h"
#include "mtk/ion_drv.h"
#include "ion_sec_heap.h"

#ifdef CONFIG_MTK_IN_HOUSE_TEE_SUPPORT
#include "tz_cross/trustzone.h"
#include "tz_cross/ta_mem.h"
#include "trustzone/kree/system.h"
#include "trustzone/kree/mem.h"
#endif

#if defined(CONFIG_MTK_LEGACY_SECMEM_SUPPORT)
#include "secmem.h"
#elif defined(CONFIG_MTK_SECURE_MEM_SUPPORT)
#include "secmem_api.h"
#endif

#ifdef CONFIG_MTK_PROT_MEM_SUPPORT
#include "pmem_api.h"
#endif

#define ION_PRINT_LOG_OR_SEQ(seq_file, fmt, args...) \
do {\
	if (seq_file)\
		seq_printf(seq_file, fmt, ##args);\
	else\
		pr_err(fmt, ##args);\
} while (0)

struct ion_sec_heap {
	struct ion_heap heap;
	void *priv;
};

static size_t sec_heap_total_memory;
static unsigned int caller_pid;
static unsigned int caller_tid;

#ifdef CONFIG_MTK_IN_HOUSE_TEE_SUPPORT
static KREE_SESSION_HANDLE ion_session;
KREE_SESSION_HANDLE ion_session_handle(void)
{
	if (ion_session == KREE_SESSION_HANDLE_NULL) {
		TZ_RESULT ret;

		ret = KREE_CreateSession(TZ_TA_MEM_UUID, &ion_session);
		if (ret != TZ_RESULT_SUCCESS) {
			IONMSG("KREE_CreateSession fail, ret=%d\n", ret);
			return KREE_SESSION_HANDLE_NULL;
		}
	}

	return ion_session;
}
#endif

static int ion_sec_heap_allocate(struct ion_heap *heap,
				 struct ion_buffer *buffer, unsigned long size, unsigned long align,
		unsigned long flags) {
	u32 sec_handle = 0;
	struct ion_sec_buffer_info *pbufferinfo = NULL;
	u32 refcount = 0;

	IONDBG("%s enter id %d size 0x%lx align %ld flags 0x%lx\n", __func__, heap->id, size, align, flags);

#ifdef CONFIG_PM
	if (sec_heap_total_memory <= 0)
		shrink_ion_by_scenario(0);
#endif
	caller_pid = (unsigned int)current->pid;
	caller_tid = (unsigned int)current->tgid;

	pbufferinfo = kzalloc(sizeof(*pbufferinfo), GFP_KERNEL);
	if (IS_ERR_OR_NULL(pbufferinfo)) {
		IONMSG("%s Error. Allocate pbufferinfo failed.\n", __func__);
		caller_pid = 0;
		caller_tid = 0;
		return -EFAULT;
	}

#if defined(CONFIG_MTK_PROT_MEM_SUPPORT)
	if (heap->id == ION_HEAP_TYPE_MULTIMEDIA_PROT) {
		if (flags & ION_FLAG_MM_HEAP_INIT_ZERO)
			pmem_api_alloc_zero(align, size, &refcount, &sec_handle, (uint8_t *)heap->name, heap->id);
		else
			pmem_api_alloc(align, size, &refcount, &sec_handle, (uint8_t *)heap->name, heap->id);
		goto prot_alloc;
	}
#endif

#if defined(CONFIG_MTK_SECURE_MEM_SUPPORT)
	if (heap->id == ION_HEAP_TYPE_MULTIMEDIA_SEC) {
		if (flags & ION_FLAG_MM_HEAP_INIT_ZERO)
			secmem_api_alloc_zero_ext(align, size, &refcount, &sec_handle, (uint8_t *)heap->name,
						  heap->id, SECMEM_VIRT_SHARE_REGION_SVP);
		else
			secmem_api_alloc_ext(align, size, &refcount, &sec_handle, (uint8_t *)heap->name,
					     heap->id, SECMEM_VIRT_SHARE_REGION_SVP);
		goto prot_alloc;
	}
#endif

#if defined(CONFIG_MTK_CAM_SECURITY_SUPPORT) && defined(CONFIG_MTK_SECURE_MEM_SUPPORT)
	if (heap->id == ION_HEAP_TYPE_MULTIMEDIA_2D_FR) {
		if (flags & ION_FLAG_MM_HEAP_INIT_ZERO)
			secmem_api_alloc_zero_ext(align, size, &refcount, &sec_handle, (uint8_t *)heap->name,
						  heap->id, SECMEM_VIRT_SHARE_REGION_2D_FR);
		else
			secmem_api_alloc_ext(align, size, &refcount, &sec_handle, (uint8_t *)heap->name,
					     heap->id, SECMEM_VIRT_SHARE_REGION_2D_FR);
		goto prot_alloc;
	}
#endif

#if defined(SECMEM_KERNEL_API)
	if (flags & ION_FLAG_MM_HEAP_INIT_ZERO)
		secmem_api_alloc_zero(align, size, &refcount, &sec_handle, (uint8_t *)heap->name, heap->id);
	else
		secmem_api_alloc(align, size, &refcount, &sec_handle, (uint8_t *)heap->name, heap->id);
#elif defined(CONFIG_MTK_IN_HOUSE_TEE_SUPPORT) && defined(CONFIG_MTK_SEC_VIDEO_PATH_SUPPORT)
	{
		int ret = 0;

		if (flags & ION_FLAG_MM_HEAP_INIT_ZERO)
			ret = KREE_ZallocSecurechunkmemWithTag(ion_session_handle(),
							       &sec_handle, align, size, heap->name);
		else
			ret = KREE_AllocSecurechunkmemWithTag(ion_session_handle(),
							      &sec_handle, align, size, heap->name);
		if (ret != TZ_RESULT_SUCCESS) {
			IONMSG("KREE_AllocSecurechunkmemWithTag failed, ret is 0x%x\n", ret);
			caller_pid = 0;
			caller_tid = 0;
			return -ENOMEM;
		}
	}
	refcount = 0;
#else
	refcount = 0;
#endif
#if defined(CONFIG_MTK_PROT_MEM_SUPPORT) || defined(CONFIG_MTK_SECURE_MEM_SUPPORT)
prot_alloc:
#endif
	if (sec_handle <= 0) {
		IONMSG("%s alloc security memory failed, total size %zu\n", __func__, sec_heap_total_memory);
		kfree(pbufferinfo);
		caller_pid = 0;
		caller_tid = 0;
		return -ENOMEM;
	}

	pbufferinfo->priv_phys = (ion_phys_addr_t)sec_handle;
	pbufferinfo->VA = 0;
	pbufferinfo->MVA = 0;
	pbufferinfo->FIXED_MVA = 0;
	pbufferinfo->iova_start = 0;
	pbufferinfo->iova_end = 0;
	pbufferinfo->module_id = -1;
	pbufferinfo->dbg_info.value1 = 0;
	pbufferinfo->dbg_info.value2 = 0;
	pbufferinfo->dbg_info.value3 = 0;
	pbufferinfo->dbg_info.value4 = 0;
	pbufferinfo->pid = buffer->pid;
	strncpy((pbufferinfo->dbg_info.dbg_name), "nothing", ION_MM_DBG_NAME_LEN);

	buffer->priv_virt = pbufferinfo;
	buffer->flags &= ~ION_FLAG_CACHED;
	buffer->size = size;
	sec_heap_total_memory += size;
	caller_pid = 0;
	caller_tid = 0;
	IONDBG("%s exit priv_virt %p pa 0x%lx(%zu)\n", __func__, buffer->priv_virt,
	       pbufferinfo->priv_phys, buffer->size);
	return 0;
}

void ion_sec_heap_free(struct ion_buffer *buffer)
{
	struct sg_table *table = buffer->sg_table;
	struct ion_sec_buffer_info *pbufferinfo = (struct ion_sec_buffer_info *)buffer->priv_virt;
	u32 sec_handle = 0;

	IONDBG("%s enter priv_virt %p\n", __func__, buffer->priv_virt);
	sec_heap_total_memory -= buffer->size;
	sec_handle = ((struct ion_sec_buffer_info *)buffer->priv_virt)->priv_phys;

#if defined(CONFIG_MTK_PROT_MEM_SUPPORT)
	if (buffer->heap->id == ION_HEAP_TYPE_MULTIMEDIA_PROT) {
		pmem_api_unref(sec_handle, (uint8_t *)buffer->heap->name, buffer->heap->id);
		goto prot_free;
	}
#endif

#if defined(CONFIG_MTK_SECURE_MEM_SUPPORT)
	if (buffer->heap->id == ION_HEAP_TYPE_MULTIMEDIA_SEC) {
		secmem_api_unref_ext(sec_handle, (uint8_t *)buffer->heap->name, buffer->heap->id,
				     SECMEM_VIRT_SHARE_REGION_SVP);
		goto prot_free;
	}
#endif

#if defined(CONFIG_MTK_CAM_SECURITY_SUPPORT) && defined(CONFIG_MTK_SECURE_MEM_SUPPORT)
	if (buffer->heap->id == ION_HEAP_TYPE_MULTIMEDIA_2D_FR) {
		secmem_api_unref_ext(sec_handle, (uint8_t *)buffer->heap->name, buffer->heap->id,
				     SECMEM_VIRT_SHARE_REGION_2D_FR);
		goto prot_free;
	}
#endif
#if defined(SECMEM_KERNEL_API)
	secmem_api_unref(sec_handle, (uint8_t *)buffer->heap->name, buffer->heap->id);

#elif defined(CONFIG_MTK_IN_HOUSE_TEE_SUPPORT) && defined(CONFIG_MTK_SEC_VIDEO_PATH_SUPPORT)
	{
		TZ_RESULT ret = 0;

		ret = KREE_UnreferenceSecurechunkmem(ion_session_handle(), sec_handle);
		if (ret != TZ_RESULT_SUCCESS)
			IONMSG("KREE_UnreferenceSecurechunkmem failed, ret is 0x%x\n", ret);
	}
#endif
#if defined(CONFIG_MTK_PROT_MEM_SUPPORT) || defined(CONFIG_MTK_SECURE_MEM_SUPPORT)
prot_free:
#endif
	kfree(table);
	buffer->priv_virt = NULL;
	kfree(pbufferinfo);

	IONDBG("%s exit, total %zu\n", __func__, sec_heap_total_memory);
}

struct sg_table *ion_sec_heap_map_dma(struct ion_heap *heap,
				      struct ion_buffer *buffer) {
	struct sg_table *table;
	int ret;
#if ION_RUNTIME_DEBUGGER
	struct ion_sec_buffer_info *pbufferinfo = (struct ion_sec_buffer_info *)buffer->priv_virt;
#endif
	IONDBG("%s enter priv_virt %p\n", __func__, buffer->priv_virt);

	table = kzalloc(sizeof(*table), GFP_KERNEL);
	if (!table)
		return ERR_PTR(-ENOMEM);
	ret = sg_alloc_table(table, 1, GFP_KERNEL);
	if (ret) {
		kfree(table);
		return ERR_PTR(ret);
	}

#if ION_RUNTIME_DEBUGGER
#ifdef SECMEM_64BIT_PHYS_SHIFT
	sg_set_page(table->sgl, phys_to_page(pbufferinfo->priv_phys << SECMEM_64BIT_PHYS_SHIFT), buffer->size, 0);
#else
	sg_set_page(table->sgl, phys_to_page(pbufferinfo->priv_phys), buffer->size, 0);
#endif
#else
	sg_set_page(table->sgl, 0, 0, 0);
#endif
	IONDBG("%s exit\n", __func__);
	return table;
}

static void ion_sec_heap_unmap_dma(struct ion_heap *heap, struct ion_buffer *buffer)
{
	IONDBG("%s priv_virt %p\n", __func__, buffer->priv_virt);
	sg_free_table(buffer->sg_table);
}

static int ion_sec_heap_shrink(struct ion_heap *heap, gfp_t gfp_mask, int nr_to_scan)
{
	return 0;
}

static int ion_sec_heap_phys(struct ion_heap *heap, struct ion_buffer *buffer,
			     ion_phys_addr_t *addr, size_t *len)
{
	struct ion_sec_buffer_info *pbufferinfo = (struct ion_sec_buffer_info *)buffer->priv_virt;

	IONDBG("%s priv_virt %p\n", __func__, buffer->priv_virt);
	*addr = pbufferinfo->priv_phys;
	*len = buffer->size;
	IONDBG("%s exit pa 0x%lx(%zu)\n", __func__, pbufferinfo->priv_phys, buffer->size);

	return 0;
}

void ion_sec_heap_add_freelist(struct ion_buffer *buffer)
{
}

int ion_sec_heap_pool_total(struct ion_heap *heap)
{
	return 0;
}

void *ion_sec_heap_map_kernel(struct ion_heap *heap,
			      struct ion_buffer *buffer) {
#if ION_RUNTIME_DEBUGGER
	void *vaddr = ion_heap_map_kernel(heap, buffer);

	IONMSG("%s enter priv_virt %p vaddr %p\n", __func__, buffer->priv_virt, vaddr);
	return vaddr;
#else
	return NULL;
#endif
}

void ion_sec_heap_unmap_kernel(struct ion_heap *heap,
			       struct ion_buffer *buffer)
{
#if ION_RUNTIME_DEBUGGER
	IONMSG("%s enter priv_virt %p\n", __func__, buffer->priv_virt);
	ion_heap_unmap_kernel(heap, buffer);
#else

#endif
}

int ion_sec_heap_map_user(struct ion_heap *heap, struct ion_buffer *buffer,
			  struct vm_area_struct *vma)
{
#if ION_RUNTIME_DEBUGGER
	int ret;

	ret = ion_heap_map_user(heap, buffer, vma);
	IONMSG("%s vm_start=0x%lx, vm_end=0x%lx exit\n", __func__, vma->vm_start, vma->vm_end);
	return ret;
#else
	IONMSG("%s do not suppuprt\n", __func__);
	return	(-ENOMEM);
#endif
}

static struct ion_heap_ops mm_sec_heap_ops = {
		.allocate = ion_sec_heap_allocate,
		.free = ion_sec_heap_free,
		.map_dma = ion_sec_heap_map_dma,
		.unmap_dma = ion_sec_heap_unmap_dma,
		.map_kernel = ion_sec_heap_map_kernel,
		.unmap_kernel = ion_sec_heap_unmap_kernel,
		.map_user = ion_sec_heap_map_user,
		.phys = ion_sec_heap_phys,
		.shrink = ion_sec_heap_shrink,
		/*.add_freelist = ion_sec_heap_add_freelist,*/
		.page_pool_total = ion_sec_heap_pool_total,
};

/*For sec memory heap user dump*/
static size_t ion_debug_sec_heap_total(struct ion_client *client)
{
	size_t size = 0;
	struct rb_node *n;

	if (mutex_trylock(&client->lock)) {
		for (n = rb_first(&client->handles); n; n = rb_next(n)) {
			struct ion_handle *handle = rb_entry(n, struct ion_handle, node);

			if (handle->buffer->heap->id == ION_HEAP_TYPE_MULTIMEDIA_SEC ||
			    handle->buffer->heap->id == ION_HEAP_TYPE_MULTIMEDIA_PROT)
				size += handle->buffer->size;
		}
		mutex_unlock(&client->lock);
	}
	return size;
}

void ion_sec_heap_dump_info(void)
{
	struct ion_device *dev = g_ion_device;
	size_t total_size = 0;
	size_t total_orphaned_size = 0;
	struct rb_node *n;
	bool need_dev_lock = true;

	ION_PRINT_LOG_OR_SEQ(NULL, "%16.s(%16.s) %16.s %16.s %s\n",
			     "client", "dbg_name", "pid", "size", "address");
	ION_PRINT_LOG_OR_SEQ(NULL, "----------------------------------------------------\n");

	if (!down_read_trylock(&dev->lock)) {
		ION_PRINT_LOG_OR_SEQ(NULL, "detail trylock fail, alloc pid(%d-%d)\n", caller_pid, caller_tid);
		ION_PRINT_LOG_OR_SEQ(NULL, "current(%d-%d)\n", (unsigned int)current->pid, (unsigned int)current->tgid);
		if ((caller_pid != (unsigned int)current->pid) || (caller_tid != (unsigned int)current->tgid))
			goto skip_client_entry;
		else
			need_dev_lock = false;
	}

	for (n = rb_first(&dev->clients); n; n = rb_next(n)) {
		struct ion_client
		*client = rb_entry(n, struct ion_client, node);
		size_t size = ion_debug_sec_heap_total(client);

		if (!size)
			continue;
		if (client->task) {
			char task_comm[TASK_COMM_LEN];

			get_task_comm(task_comm, client->task);
			ION_PRINT_LOG_OR_SEQ(NULL, "%16.s(%16.s) %16u %16zu 0x%p\n",
					     task_comm, client->dbg_name, client->pid, size, client);
		} else {
			ION_PRINT_LOG_OR_SEQ(NULL, "%16.s(%16.s) %16u %16zu 0x%p\n",
					     client->name, "from_kernel", client->pid, size, client);
		}
	}

	if (need_dev_lock)
		up_read(&dev->lock);

	ION_PRINT_LOG_OR_SEQ(NULL, "----------------------------------------------------\n");
	ION_PRINT_LOG_OR_SEQ(NULL, "orphaned allocations (info is from last known client):\n");

skip_client_entry:

	if (mutex_trylock(&dev->buffer_lock)) {
		for (n = rb_first(&dev->buffers); n; n = rb_next(n)) {
			struct ion_buffer
			*buffer = rb_entry(n, struct ion_buffer, node);

			if ((1 << buffer->heap->id) & ION_HEAP_MULTIMEDIA_SEC_MASK) {
				/* heap = buffer->heap; */
				total_size += buffer->size;
				if (!buffer->handle_count) {
					ION_PRINT_LOG_OR_SEQ(NULL, "%16.s %16u %16zu %d %d\n",
							     buffer->task_comm, buffer->pid,
							     buffer->size, buffer->kmap_cnt,
							     atomic_read(&buffer->ref.refcount));
					total_orphaned_size += buffer->size;
				}
			}
		}
		mutex_unlock(&dev->buffer_lock);

		ION_PRINT_LOG_OR_SEQ(NULL, "----------------------------------------------------\n");
		ION_PRINT_LOG_OR_SEQ(NULL, "%16.s %16zu\n", "total orphaned", total_orphaned_size);
		ION_PRINT_LOG_OR_SEQ(NULL, "%16.s %16zu\n", "total ", total_size);
		ION_PRINT_LOG_OR_SEQ(NULL, "ion sec heap total: %16zu\n", sec_heap_total_memory);
		ION_PRINT_LOG_OR_SEQ(NULL, "----------------------------------------------------\n");
	} else {
		ION_PRINT_LOG_OR_SEQ(NULL, "ion sec heap total memory: %16zu\n", sec_heap_total_memory);
	}
}

struct dump_fd_data {
	struct task_struct *p;
	struct seq_file *s;
};

static int __do_dump_share_fd(const void *data, struct file *file, unsigned fd)
{
	const struct dump_fd_data *d = data;
	struct seq_file *s = d->s;
	struct task_struct *p = d->p;
	struct ion_buffer *buffer;
	struct ion_sec_buffer_info *bug_info;

	buffer = ion_drv_file_to_buffer(file);
	if (IS_ERR_OR_NULL(buffer))
		return 0;

	bug_info = (struct ion_sec_buffer_info *)buffer->priv_virt;
	if (!buffer->handle_count)
		ION_PRINT_LOG_OR_SEQ(s, "0x%p %9d %16s %5d %5d %16s %4d\n",
				     buffer, bug_info->pid, buffer->alloc_dbg, p->pid, p->tgid, p->comm, fd);

	return 0;
}

static int ion_dump_all_share_fds(struct seq_file *s)
{
	struct task_struct *p;
	int res;
	struct dump_fd_data data;

	/* function is not available, just return */
	if (ion_drv_file_to_buffer(NULL) == ERR_PTR(-EPERM))
		return 0;

	ION_PRINT_LOG_OR_SEQ(s, "%18s %9s %16s %5s %5s %16s %4s\n",
			     "buffer", "alloc_pid", "alloc_client", "pid", "tgid", "process", "fd");
	data.s = s;

	read_lock(&tasklist_lock);
	for_each_process(p) {
		task_lock(p);
		data.p = p;
		res = iterate_fd(p->files, 0, __do_dump_share_fd, &data);
		if (res)
			IONMSG("%s failed somehow\n", __func__);
		task_unlock(p);
	}
	read_unlock(&tasklist_lock);
	return 0;
}

static int ion_sec_heap_debug_show(struct ion_heap *heap, struct seq_file *s, void *unused)
{
	struct ion_device *dev = heap->dev;
	struct rb_node *n;
	int *secur_handle;
	struct ion_sec_buffer_info *bug_info;
	bool has_orphaned = false;
	size_t fr_size = 0;
	size_t sec_size = 0;
	size_t prot_size = 0;

	if (heap->flags & ION_HEAP_FLAG_DEFER_FREE)
		ION_PRINT_LOG_OR_SEQ(s, "sec_heap_freelist total_size=%zu\n", ion_heap_freelist_size(heap));
	else
		ION_PRINT_LOG_OR_SEQ(s, "sec_heap defer free disabled\n");

	ION_PRINT_LOG_OR_SEQ(s, "----------------------------------------------------\n");
	ION_PRINT_LOG_OR_SEQ(s,
			     "%18.s %8.s %4.s %3.s %8.s %8.s %3.s %4.s %4.s %3.s %10.s %10.s\n",
			     "buffer", "size", "kmap", "ref", "hdl-cnt", "sec_hdl",
			     "flag", "port", "heap_id", "pid(alloc)", "comm(client)", "dbg_name");

	mutex_lock(&dev->buffer_lock);
	for (n = rb_first(&dev->buffers); n; n = rb_next(n)) {
		struct ion_buffer
		*buffer = rb_entry(n, struct ion_buffer, node);
		if (buffer->heap->type != heap->type)
			continue;
		secur_handle = (int *)buffer->priv_virt;
		bug_info = (struct ion_sec_buffer_info *)buffer->priv_virt;

		if ((int)buffer->heap->type == (int)ION_HEAP_TYPE_MULTIMEDIA_SEC) {
			ION_PRINT_LOG_OR_SEQ(s,
					     "0x%p %8zu %3d %3d %3d 0x%10.x %3lu %3d %3d %3d %s %s",
					     buffer, buffer->size, buffer->kmap_cnt, atomic_read(&buffer->ref.refcount),
					     buffer->handle_count, *secur_handle,
					     buffer->flags, bug_info->module_id, buffer->heap->id,
					     buffer->pid, buffer->task_comm, bug_info->dbg_info.dbg_name);
			ION_PRINT_LOG_OR_SEQ(s, ")\n");

			if (buffer->heap->id == ION_HEAP_TYPE_MULTIMEDIA_SEC)
				sec_size += buffer->size;
			if (buffer->heap->id == ION_HEAP_TYPE_MULTIMEDIA_PROT)
				prot_size += buffer->size;
			if (buffer->heap->id == ION_HEAP_TYPE_MULTIMEDIA_2D_FR)
				fr_size += buffer->size;

			if (!buffer->handle_count)
				has_orphaned = true;
		}
	}
	if (has_orphaned) {
		ION_PRINT_LOG_OR_SEQ(s, "-----orphaned buffer list:------------------\n");
		ion_dump_all_share_fds(s);
	}
	mutex_unlock(&dev->buffer_lock);
	ION_PRINT_LOG_OR_SEQ(s, "----------------------------------------------------\n");

	ION_PRINT_LOG_OR_SEQ(s, "----------------------------------------------------\n");
	ION_PRINT_LOG_OR_SEQ(s, "%16s %16zu\n", "sec-sz:", sec_size);
	ION_PRINT_LOG_OR_SEQ(s, "%16s %16zu\n", "prot-sz:", prot_size);
	ION_PRINT_LOG_OR_SEQ(s, "%16s %16zu\n", "2d-fr-sz:", fr_size);
	ION_PRINT_LOG_OR_SEQ(s, "----------------------------------------------------\n");

	down_read(&dev->lock);
	for (n = rb_first(&dev->clients); n; n = rb_next(n)) {
		struct ion_client
		*client = rb_entry(n, struct ion_client, node);

		if (client->task) {
			char task_comm[TASK_COMM_LEN];

			get_task_comm(task_comm, client->task);
			ION_PRINT_LOG_OR_SEQ(s,
					     "client(0x%p) %s (%s) pid(%u) ================>\n",
					     client, task_comm, client->dbg_name, client->pid);
		} else {
			ION_PRINT_LOG_OR_SEQ(s,
					     "client(0x%p) %s (from_kernel) pid(%u) ================>\n",
					     client, client->name, client->pid);
		}

		{
			struct rb_node *m;

			mutex_lock(&client->lock);
			for (m = rb_first(&client->handles); m; m = rb_next(m)) {
				struct ion_handle
				*handle = rb_entry(m, struct ion_handle, node);

				if (handle->buffer->heap->id == ION_HEAP_TYPE_MULTIMEDIA_SEC ||
				    handle->buffer->heap->id == ION_HEAP_TYPE_MULTIMEDIA_PROT ||
				    handle->buffer->heap->id == ION_HEAP_TYPE_MULTIMEDIA_2D_FR) {
					ION_PRINT_LOG_OR_SEQ(s,
							     "\thandle=0x%p, buffer=0x%p",
							     handle, handle->buffer);
					ION_PRINT_LOG_OR_SEQ(s, ", heap=%d",
							     handle->buffer->heap->id);
					ION_PRINT_LOG_OR_SEQ(s, "fd=%4d, ts: %lldms\n",
							     handle->dbg.fd, handle->dbg.user_ts);
				}
			}
			mutex_unlock(&client->lock);
		}
	}
	up_read(&dev->lock);

	return 0;
}

struct ion_heap *ion_sec_heap_create(struct ion_platform_heap *heap_data)
{
#if (defined(SECMEM_KERNEL_API) || defined(CONFIG_MTK_SECURE_MEM_SUPPORT)) || \
	(defined(CONFIG_MTK_IN_HOUSE_TEE_SUPPORT) && defined(CONFIG_MTK_SEC_VIDEO_PATH_SUPPORT))

	struct ion_sec_heap *heap;

	IONMSG("%s enter ion_sec_heap_create\n", __func__);

	heap = kzalloc(sizeof(*heap), GFP_KERNEL);
	if (!heap) {
		IONMSG("%s kzalloc failed heap is null.\n", __func__);
		return ERR_PTR(-ENOMEM);
	}
	heap->heap.ops = &mm_sec_heap_ops;
	heap->heap.type = ION_HEAP_TYPE_MULTIMEDIA_SEC;
	heap->heap.flags &= ~ION_HEAP_FLAG_DEFER_FREE;
	heap->heap.debug_show = ion_sec_heap_debug_show;

	return &heap->heap;

#else
	struct ion_sec_heap heap;

	heap.heap.ops = &mm_sec_heap_ops;
	heap.heap.debug_show = ion_sec_heap_debug_show;
	IONMSG("%s error: not support\n", __func__);
	return NULL;
#endif
}

void ion_sec_heap_destroy(struct ion_heap *heap)
{
#if (defined(SECMEM_KERNEL_API) || defined(CONFIG_MTK_SECURE_MEM_SUPPORT)) || \
	(defined(CONFIG_MTK_IN_HOUSE_TEE_SUPPORT) && defined(CONFIG_MTK_SEC_VIDEO_PATH_SUPPORT))

	struct ion_sec_heap *sec_heap;

	IONMSG("%s enter\n", __func__);
	sec_heap = container_of(heap, struct ion_sec_heap, heap);
	kfree(sec_heap);
#else
	IONMSG("%s error: not support\n", __func__);
#endif
}

