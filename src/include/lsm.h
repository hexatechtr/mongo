/*-
 * Copyright (c) 2008-2012 WiredTiger, Inc.
 *	All rights reserved.
 *
 * See the file LICENSE for redistribution information.
 */

struct __wt_cursor_lsm {
	WT_CURSOR iface;

	WT_LSM_TREE *lsmtree;
	uint64_t dsk_gen;

	int nchunks;
	WT_CURSOR **cursors;
	WT_CURSOR *current;     	/* The current cursor for iteration */

#define	WT_CLSM_ITERATE_NEXT    0x01    /* Forward iteration */
#define	WT_CLSM_ITERATE_PREV    0x02    /* Backward iteration */
#define	WT_CLSM_MERGE		0x04    /* Merge cursor, don't update. */
#define	WT_CLSM_MULTIPLE        0x08    /* Multiple cursors have values for the
					   current key */
	uint32_t flags;
};

struct __wt_lsm_tree {
	const char *name, *filename;
	const char *key_format, *value_format, *file_config;

	WT_COLLATOR *collator;

	WT_RWLOCK *rwlock;
	TAILQ_ENTRY(__wt_lsm_tree) q;

	WT_SPINLOCK lock;
	uint64_t dsk_gen, ncursor, old_cursors;
	uint32_t *memsizep;

	uint32_t threshhold;

	WT_CONNECTION_IMPL *conn;	/* Passed to thread_create */
	pthread_t worker_tid;		/* LSM worker thread */

	int nchunks;			/* Number of active chunks */
	int last;			/* Last allocated ID. */
	const char **chunk;		/* Array of chunk URIs */
	size_t chunk_allocated;		/* Space allocated for chunks */

#define	WT_LSM_TREE_OPEN	0x01
	uint32_t flags;
};

struct __wt_lsm_data_source {
	WT_DATA_SOURCE iface;

	WT_RWLOCK *rwlock;

	TAILQ_HEAD(__trees, __wt_lsm_tree) trees;
};
