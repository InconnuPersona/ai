#pragma once

#include "base.h"

struct cmd_scope_i {

};

struct cmd_i {

	virtual void set_scope(cmd_scope_i* scope) = 0;
};

struct cmd_proc_s {


	//void 
};
