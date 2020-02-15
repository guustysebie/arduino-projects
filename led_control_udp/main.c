#include <stdio.h>
#include "../custom_libs/network_custom.h"
#include <unistd.h> 

void light_off()
{
    send_command("off");
}

void light_on()
{
    send_command("on");
}

void light_party()
{
    for (int i = 0; i < 3; i++)
    {
      light_on(),
      sleep(1);
      light_off();
      sleep(1);
    }
}

int main(int argc,char* argv[]) 
{ 
    printf("available commands\n");
    printf("-1. End program\n");
    printf("1. Leds on\n");
    printf("2. Leds off\n");
    printf("3. party time\n");
    while (1)
    {
    int choice;
    printf("Keuze: ");
    int result_temp = scanf("%d", &choice);

    switch (choice)
    {
    case -1: 
        return 0;
    case 1:
         light_on();
        break;
    
    case 2:
         light_off();
        break;
    case 3: 
        light_party();
        break;
    default:
        break;
    }
    }
    return 0;
}