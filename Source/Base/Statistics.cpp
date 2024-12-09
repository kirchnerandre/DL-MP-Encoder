
#include <stdint.h>
#include <stdio.h>

#include "Base/Statistics.h"


namespace Statistics
{
    void summarize(STATISTICS_T& Statistics)
    {
        fprintf(stderr, "*******************\n");
        fprintf(stderr, "PacketDataTotal:            %u\n", Statistics.PacketDataTotal);
        fprintf(stderr, "PacketDataGood:             %u\n", Statistics.PacketDataGood);
        fprintf(stderr, "PacketHashTypeColumnTotal:  %u\n", Statistics.PacketHashTypeColumnTotal);
        fprintf(stderr, "PacketHashTypeColumnGood:   %u\n", Statistics.PacketHashTypeColumnGood);
        fprintf(stderr, "PacketHashTypeColumnBad:    %u\n", Statistics.PacketHashTypeColumnBad);
        fprintf(stderr, "PacketHashTypeRowTotal:     %u\n", Statistics.PacketHashTypeRowTotal);
        fprintf(stderr, "PacketHashTypeRowGood:      %u\n", Statistics.PacketHashTypeRowGood);
        fprintf(stderr, "PacketHashTypeRowBad:       %u\n", Statistics.PacketHashTypeRowBad);
        fprintf(stderr, "*******************\n");

        printf("*******************\n");
        printf("PacketDataTotal:            %u\n", Statistics.PacketDataTotal);
        printf("PacketDataGood:             %u\n", Statistics.PacketDataGood);
        printf("PacketHashTypeColumnTotal:  %u\n", Statistics.PacketHashTypeColumnTotal);
        printf("PacketHashTypeColumnGood:   %u\n", Statistics.PacketHashTypeColumnGood);
        printf("PacketHashTypeColumnBad:    %u\n", Statistics.PacketHashTypeColumnBad);
        printf("PacketHashTypeRowTotal:     %u\n", Statistics.PacketHashTypeRowTotal);
        printf("PacketHashTypeRowGood:      %u\n", Statistics.PacketHashTypeRowGood);
        printf("PacketHashTypeRowBad:       %u\n", Statistics.PacketHashTypeRowBad);
        printf("*******************\n");
    }
}
