#ifndef DEFINES_H
#define DEFINES_H

#ifndef NTP_SERVER
#define NTP_SERVER "nl.pool.ntp.org"
#warning "You MUST set an appropriate ntp pool - see http://ntp.org"
#endif

// TODO: default timezone
#ifndef NTP_DEFAULT_TZ
#define NTP_DEFAULT_TZ "CET-1CEST,M3.5.0,M10.5.0/3"
#endif

#define LILYGO_T5_V213


#endif // DEFINES_H
