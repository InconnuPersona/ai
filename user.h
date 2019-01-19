#pragma once

#include "unused/audio.h"
#include "input.h"
#include "network.h"
#include "video.h"
#include "view.h"
#include "entity.h"

typedef enum {
 UI_WINDOWS,
 UI_MAC_OS,
 UI_LINUX,
 UI_ANDROID,
 UI_IOS,
} ui_host_e;

typedef enum {
} ui_type_e;

typedef struct {
 ui_host_e host;
 ui_type_e type;
 audio_t* audio;
 input_t* input;
 video_t* video;
 view_t* view;
 network_t* network;
} user_interface_t;

typedef struct {
 user_interface_t* interface;
 string_t title;
 
 entity_p entity;
} user_t, client_t;

void setup_user(user_t* user);
