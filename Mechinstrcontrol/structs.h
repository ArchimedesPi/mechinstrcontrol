typedef enum {ABSOLUTE, RELATIVE} relativity_t;
typedef enum {STEPS, MM} unit_t;
typedef struct opSettings_t {
  relativity_t relativity;
  long speed;
  long position;
} opSettings_t;
