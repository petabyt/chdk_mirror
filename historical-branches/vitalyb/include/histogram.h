#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#define HISTO_SIZE (128)
void histogram_process();
void histogram_stop();
void histogram_restart();

extern unsigned char histogram[HISTO_SIZE];
extern long exposition_thresh;
extern long under_exposed;
extern long over_exposed;

#endif
