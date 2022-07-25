#include "main.h"

void proc_args(int argc, char** argv) {
 arg_s arg;
 string_t s;
 int i;
 bool is_client, is_host;
 string_t ip;
 int port;
 
 if (argc < 2) {
  return;
 }
 
 is_client = false;
 is_host = false;
 
 for (i = 1; i < argc; i++) {
  arg = argv[i];
  
  s = arg.til_next(':');
  
  if (s == "console") {
   use_console = true;
  }
  elif (s == "tag") {
   // Select tag.
  }
  elif (s == "nogui") {
   use_gui = false;
   use_console = true;
  }
  elif (s == "host") {
   // Define port
   if (is_client) {
	ERROR("arg %i - client state already selected.", i);
   }
   
   is_host = true;
  }
  elif (s == "join") {
   // Ip and port
   if (is_host) {
	ERROR("arg %i - host state already selected.", i);
   }
   
   is_client = true;
  }
 }
 
 //printf("is_client %i\n", is_client);
 //printf("is_host %i\n", is_host);
}

void proc_cmds(const char* text) {
 line_s line;
 arg_s arg;
 int i, j;
 
 if (!text) {
  return;
 }
 
 i = 0;
 
 while (line.next(text, &i)) {
  if (line[0] == "exec" || line[0] == "load") {
   if (line.size() < 2) {
	printf("specify files to execute.\n");
	continue;
   }
   
   for (j = 1; j < line.size(); j++) {
	exec_file(line[j].c_str());
   }
  }
  elif (line[0] == "exit" || line[0] == "quit") {
   exit(0);
  }
  elif (line[0] == "tag") {
   //map.add_tag(line);
  }
  else {
   printf("unknown command '%s'\n", line[0].c_str());
  }
  
 }
}

void exec_file(const char* path) {
 FILE* file;
 char* text;
 int size;
 
 file = fopen(path, "rb");
 
 if (!file) {
  ERROR("unable to open file %s.", path);
 }
 
 fseek(file, 0, SEEK_END);
 size = (int) ftell(file);
 fseek(file, 0, SEEK_SET);
 
 text = new char[size + 1];
 
 text[size] = '\0';
 
 fread(text, sizeof(char), size, file);
 
 fclose(file);
 
 proc_cmds(text);
 
 delete[] text;
 
 printf("finished processing '%s'.\n", path);
}

void exec_file(FILE* file) {
 char* text;
  int size;
  
  if (!file) {
   ERROR("invalid FILE* received.");
  }
  
  fseek(file, 0, SEEK_END);
  size = (int) ftell(file);
  fseek(file, 0, SEEK_SET);
  
  text = new char[size + 1];
  
  text[size] = '\0';
  
  fread(text, sizeof(char), size, file);
  
  proc_cmds(text);
  
  delete[] text;
  
  fseek(file, 0, SEEK_SET);
}