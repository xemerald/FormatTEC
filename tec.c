/*
 *
 */

/* */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/* */
#include "tec.h"

/*
 * enrich_tec_rec_header() -
 */
TEC_REC_HEADER *enrich_tec_rec_header(
	TEC_REC_HEADER *header,
	const char     *id,
	const uint8_t   data_type,
	const time_t    rec_starttime,
	const int       rec_length,
	const int       rec_stations,
	const double    ev_origin,
	const double    ev_longitude,
	const double    ev_latitude,
	const double    ev_depth
) {
	strncpy(header->id, id, TEC_REC_ID_MAX_LENGTH);
	header->data_type     = data_type;
	header->rec_starttime = rec_starttime;
	header->rec_length    = rec_length;
	header->rec_stations  = rec_stations;
/* */
	header->version[0] = TEC_FORMAT_VERSION_0;
	header->version[1] = TEC_FORMAT_VERSION_1;
	header->version[2] = TEC_FORMAT_VERSION_2;
/* */
	header->ev_origin    = ev_origin;
	header->ev_longitude = ev_longitude;
	header->ev_latitude  = ev_latitude;
	header->ev_depth     = ev_depth;

	return header;
}

/*
 * enrich_tec_rec_header() -
 */
TEC_STA_INFO_BLOCK *enrich_tec_sta_info(
	TEC_STA_INFO_BLOCK *stainfo,
	const char     *sta,
	const char     *net,
	const char     *loc,
	const int       channels,
	const double    samprate,
	const double    longitude,
	const double    latitude,
	const double    elevation
) {
	strncpy(stainfo->sta, sta, STA_CODE_LEN);
	strncpy(stainfo->net, net, NET_CODE_LEN);
	strncpy(stainfo->loc, loc, LOC_CODE_LEN);
	stainfo->channels  = channels;
	stainfo->samprate  = samprate;
	stainfo->longitude = longitude;
	stainfo->latitude  = latitude;
	stainfo->elevation = elevation;

	return stainfo;
}

/*
 * enrich_tec_sta_pick_info() -
 */
TEC_STA_INFO_BLOCK *enrich_tec_sta_pick_info(
	TEC_STA_INFO_BLOCK *stainfo,
	const float         p_arrival,
	const float         p_weight,
	const float         s_arrival,
	const float         s_weight
) {
	stainfo->p_arrival = p_arrival;
	stainfo->p_weight  = p_weight;
	stainfo->s_arrival = s_arrival;
	stainfo->s_weight  = s_weight;

	return stainfo;
}

/*
 * enrich_tec_rec_header() -
 */
TEC_CHAN_INFO_BLOCK *enrich_tec_chan_info(
	TEC_CHAN_INFO_BLOCK *chaninfo,
	const char          *chan,
	const float          scaling
) {
	strncpy(chaninfo->chan, chan, CHAN_CODE_LEN);
	chaninfo->scaling = scaling;

	return chaninfo;
}

/*
 *
 */
void *compose_channels_data(
	void         *buffer,
	const int     channels,
	const int     samples,
	const uint8_t data_type,
	const float  *data_0,
	const float  *data_1,
	const float  *data_2
) {
	int    i;
	float *bufptr = (float *)buffer;

	for ( i = 0; i < samples; i++ ) {
		*bufptr++ = *data_0++;
		*bufptr++ = *data_1++;
		*bufptr++ = *data_2++;
	}

	return buffer;
}
