#ifndef _richdem_constants_
#define _richdem_constants_

//D8 Directions
///x offsets of D8 neighbours, from a central cell
const int dx[9]={0, -1, -1,  0,  1, 1, 1, 0, -1};
const int dy[9]={0,  0, -1, -1, -1, 0, 1, 1,  1};

//234
//105
//876
const int d8_inverse[9] = {0,5,6,7,8,1,2,3,4};

//ArcGIS uses:
//32 64 128
//16  0   1
// 8  4   2
const uint8_t d8_arcgis[9] = {0,16,32,64,128,1,2,4,8};

const uint8_t FLOWDIR_NO_DATA = 255;

const uint8_t NO_FLOW = 0;

const int32_t ACCUM_NO_DATA = -1;

#endif