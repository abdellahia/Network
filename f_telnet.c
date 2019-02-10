#define TELCMDS
#define TELOPTS
#include <arpa/telnet.h>


void f_telnet(const u_char* packet, int size, int size_c) {

    const unsigned char *end = packet + size_c;
    V_printf(3,"            =====================TELNET====================\n");

    while(packet < end) {
        if(*packet & 0xFF) {
            packet++;
            uint8_t command = *packet++;
            printf("        cmd %s (%u): ", TELCMD_OK(command) ? TELCMD(command) : "CMD?", command);
            switch(command) {
                case DO: printf("Command DO");
                case DONT: printf("Command DONT");
                case WONT: printf("Command WONT");
                case WILL: {
                    uint8_t option = *packet++;
                    printf("%s (%u)", TELOPT(option), option);
                    break;
                }
                case SB: {
                    uint8_t suboption = *packet++;
                    printf("%s (%u)", TELOPT(suboption), suboption);
                    switch(suboption) {
                        case TELOPT_TSPEED:
                            printf(" = %u", *packet++);
                            break;
                        case TELOPT_NAWS:
                            printf(" = %u x %u", ntohs(*(uint16_t*)&packet[0]), ntohs(*(uint16_t*)&packet[2]));
                            packet += 4;
                            break;
                        default:
                            break;
                    }
                    break;
                }
                case SE:
                    printf("End of suboptions");
                    break;
                default:
                    printf("Unknown command %s",packet);
                    break;
            }
            putchar('\n');
            if(command == SE)
                break; // end of options
        }
        else {
            packet++;
        }
    }

}
