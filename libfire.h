/*Author: HENRY ZHANG*/

/* lib8ball.h */

/* below here is from 2 machine generated files */


int microsleep(unsigned int microseconds);
int millisleep(unsigned int milliseconds);
double now();


void fw_bang();
void fw_clear();
int fw_dot(int color, double X, double Y);
void fw_flash();
double fw_get_delta_Y();
int fw_initialize();
void fw_refresh();
int fw_star(int color, double X, double Y);
void fw_status(const char *statstr);
void fw_teardown();
void fw_time(int milliseconds);
