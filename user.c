#include "user.h"

void init_user_interface
(user_interface_t* ui, audio_t* audio, input_t* input, video_t* video, view_t* view) {
 
 ui->audio = audio;
 ui->input = input;
 ui->video = video;
 ui->view = view;
 
 return;
}
