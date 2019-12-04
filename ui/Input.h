#ifndef INPUT_H
#define INPUT_H

typedef struct _Input {
	int up;
	int down;
	int left;
	int right;
	int close_requested;
} Input;

void process_key_events(Input *pressed_key);

#endif
