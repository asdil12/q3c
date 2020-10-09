int status_init(const char *sd);
void status_write(const char *fn, const char *content);
void status_writef(const char *fn, const char *fmt, float value);
void status_writef2(const char *fn, const char *fmt, float value1, float value2);
void status_unlink(const char *fn);
void status_cleanup();
