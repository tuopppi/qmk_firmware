#pragma once

#undef OLED_DISPLAY_128X32
#undef SPLIT_OLED_ENABLE
#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS

//#define SMTD_DEBUG_ENABLED
#define MAX_DEFERRED_EXECUTORS 10 // sm_td
#define TAPPING_TERM 250

// This is the time in ms to consider two keys released within that period as a hold action for the first key and a tap action for second.
// If two keys has bigger time between their releases, they will be considered as a tap action for both keys.
#define SMTD_GLOBAL_RELEASE_TERM 30 // avoid E>N to become command N
