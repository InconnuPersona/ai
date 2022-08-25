#pragma once

#define DEFINE_UI_WINDOW(Name) \
	struct Name

#define UI_CALLBACK \
virtual void tick()

DEFINE_UI_WINDOW(Main) {
	
	UI_CALLBACK {

	}

}
