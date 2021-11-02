//************************************
//         captureSys.h
//************************************

enum{STANDING_UP, KNOCKED_OFF};

void set_weight_status(int num);
bool read_left_proximity(void);
void capture_callback(void);
bool is_capture_activated();
void captureSys_init(void);
