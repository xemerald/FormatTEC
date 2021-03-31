/*
 * tec.h
 *
 * Header file for TEC-format binary file.
 *
 * Benjamin Yang
 * Department of Geology
 * National Taiwan University
 *
 * March, 2021
 *
 */

#pragma once

#include <stdint.h>

/*
 * Whole structure description of TEC-format:
 *
 * Whole structure:
 *   -TEC record header
 *   -Station 1 block
 *   -Station 2 block
 *   -Station 3 block
 *          .
 *          .
 *          .
 *   -Station n block
 *
 * Detailed definition of each station block:
 *   -Station information block
 *   -Channel 1 information block
 *   -Channel 2 information block
 *   -Channel 3 information block
 *           .
 *           .
 *           .
 *   -Channel n information block
 *   -The first sample of channel 1
 *   -The first sample of channel 2
 *   -The first sample of channel 3
 *           .
 *           .
 *           .
 *   -The first sample of channel n
 *           .
 *           .
 *           .
 *   -The nth sample of channel n
 *
 */

/*
 *
 */
#define TEC_REC_ID_MAX_LENGTH      16

#define IEEE_SINGLE_PRECISION_REAL 0
#define IEEE_DOUBLE_PRECISION_REAL 1
#define INTEL_16BIT_INTEGER        2
#define INTEL_32BIT_INTEGER        3
#define SPARC_16BIT_INTEGER        4
#define SPARC_32BIT_INTEGER        5

#define	STA_CODE_LEN      8    /* SEED: 5 chars plus terminating NULL & 2 paddings */
#define	NET_CODE_LEN      3    /* SEED: 2 chars plus terminating NULL */
#define	CHAN_CODE_LEN     4    /* SEED: 3 chars plus terminating NULL */
#define	LOC_CODE_LEN      3    /* SEED: 2 chars plus terminating NULL */

#define LOC_NULL_STRING  "--"  /* NULL string for location code field */
/*
 *
 */
typedef struct {
	char     id[TEC_REC_ID_MAX_LENGTH];
	char     version[3];
	uint8_t  data_type;
	uint8_t  padding[4];     /* Just for alignment */
/* */
	double   ev_origin;      /* Unix timestamp with millisecond */
	double   ev_longitude;
	double   ev_latitude;
	double   ev_depth;
/* */
	uint64_t rec_starttime;  /* Unix timestamp */
	uint32_t rec_length;     /* In second */
	uint32_t rec_stations;
} TEC_REC_HEADER;

/*
 *
 */
typedef struct {
	char     sta[STA_CODE_LEN];
	char     net[NET_CODE_LEN];
	char     loc[LOC_CODE_LEN];
	uint8_t  channels;
	uint8_t  padding;
/* */
	double   samprate;
	double   longitude;
	double   latitude;
	double   elevation;
	float    p_arrival;
	float    p_weight;
	float    s_arrival;
	float    s_weight;
	uint64_t data_block_offset;
	uint64_t next_sta_offset;
} TEC_STA_INFO_BLOCK;

/*
 *
 */
typedef struct {
	char    chan[CHAN_CODE_LEN];
	float   scaling;
} TEC_CHAN_INFO_BLOCK;

/*
 *
 */
typedef struct {
	TEC_STA_INFO_BLOCK  *sta_info;
	TEC_CHAN_INFO_BLOCK *chan_info;
	void                *data;
} TEC_PTREE_NODE;

/*
 *
 */
//typedef struct {
//	TEC_REC_HEADER *header;     /* */
//	TEC_PTREE_NODE *pt_nodes;   /* */
//	void           *root;       /* */
//	char           *path;       /* */
//	int             stations;   /* */
//	size_t          file_size;  /* */
//	time_t          timestamp;  /* */
//} TEC_FILE_DESC;
