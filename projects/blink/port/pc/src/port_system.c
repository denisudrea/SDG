#include "port_system.h"

size_t port_system_init()
{
  return 0;
}


uint32_t port_system_get_millis()
{
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    //printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

void port_system_delay_ms(uint32_t ms)
{
  uint32_t tickstart = port_system_get_millis();

  while((port_system_get_millis() - tickstart) < ms)
  {
  }
}


//------------------------------------------------------
// SUBRUTINAS DE ATENCION A LAS INTERRUPCION
//------------------------------------------------------

