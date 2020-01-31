/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);
void display_trait(int line, char *s);
void dispaly_clear();

/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const pig_standard[128];
extern const uint8_t const pig_hungry[128];
extern const uint8_t const pig_hungry_tired[128];
extern const uint8_t const pig_sleeping[128];
extern const uint8_t const pig_tired[128];
extern const uint8_t const pig_sad[128];
extern const uint8_t const pig_hungry_sad[128];
extern const uint8_t const pig_sad_tired[128];
extern const uint8_t const pig_hungry_sad_tired[128];
extern const uint8_t const pig_dead[128];
extern const uint8_t const soup[128];
extern const uint8_t const empty[128];
extern const uint8_t const playing[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];



/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);