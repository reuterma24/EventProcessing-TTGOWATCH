// => Hardware select
// #define LILYGO_WATCH_2019_WITH_TOUCH     // To use T-Watch2019 with touchscreen, please uncomment this line
// #define LILYGO_WATCH_2019_NO_TOUCH          // To use T-Watch2019 Not touchscreen , please uncomment this line
// #define LILYGO_WATCH_2020_V1             //To use T-Watch2020, please uncomment this line
#define LILYGO_WATCH_2020_V2             //To use T-Watch2020 V2, please uncomment this line
// #define LILYGO_WATCH_2020_V3             //To use T-Watch2020 V3, please uncomment this line

// => Function select
#define LILYGO_WATCH_LVGL                   //To use LVGL, you need to enable the macro LVGL

#ifndef HEADER_FILE
#define HEADER_FILE

#include <LilyGoWatch.h>
#include <WiFi.h>

static const char terminator = '\1';
enum Event { A, B, C, D, E, F, None };
static const char events[] = { 'A', 'B', 'C', 'D', 'E', 'F' };

#endif
