#include <stdio.h>
#include "interface.h"
#include <sys/time.h>
#ifdef _OPENMP
	#include <omp.h>
#else
	#define omp_get_thread_num()  0
	#define omp_get_num_threads() 1
#endif

#define PROGRESS_BAR "=================================================="

double timediff(const timeval &startTime){
	timeval endTime;
	long seconds, useconds;

	gettimeofday(&endTime, NULL);

	seconds  = endTime.tv_sec  - startTime.tv_sec;
	useconds = endTime.tv_usec - startTime.tv_usec;

	return seconds + useconds/1000000.0;
}

double progress_bar(int percent){
	static int old_percent=-2;
	static timeval startTime={0,0};
	double timediffs=0;

	if(omp_get_thread_num()!=0) return 0;

	if(percent==old_percent)
		return 0;
	if(percent==-1){
		timediffs=timediff(startTime);
		gettimeofday(&startTime, NULL);
#ifndef ARCGIS
		fprintf(stderr,"\r\033[2K"); //The ANSI code used in this line clears the entire line
#else
		fprintf(stderr,"P%%c\n"); //This is a control symbol the ArcGIS python script can search for to reset its progress bar
#endif
		old_percent=0;
		return timediffs;
	}
	percent*=omp_get_num_threads();
	if(percent>100)
		percent=100;
#ifndef ARCGIS
	fprintf(stderr,"\r\033[2K[%-50.*s] (%d%% - %.1lfs left - %d thread)", percent/2, PROGRESS_BAR, percent, timediff(startTime)/percent*(100-percent),omp_get_num_threads()); //The ANSI code used in this line clears the entire line
#else
	fprintf(stderr,"P%%%d\n", percent); //This is a control symbol which the ArcGIS python script can search for to adjust its progress bar
#endif
	old_percent=percent;

	return 0;
}
