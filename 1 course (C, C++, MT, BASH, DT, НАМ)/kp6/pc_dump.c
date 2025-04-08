#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "pc.h"

void usage(){
    printf("Usage: program input_filename output_filename\n");
}

int read_pc_components(FILE *in, pc_components *pc){
    return fscanf(in, "%[^\t]\t%d\t%[^\t]\t%d\t%[^\t]\t%d\t%[^\t]\t%d\t%d\t%d\t%d\t%[^\n]\n", pc->surname, &pc->num_processors, pc->processor_type, &pc->memory_size, pc->video_controller_type, &pc->video_memory_size, pc->storage_interface_type, &pc->num_hard_drives, &pc->hard_drive_capacity, &pc->num_integrated_controllers, &pc->num_external_controllers, pc->operating_system) == 12;
}

int main(int argc, char* argv[]){
    if (argc != 3){
        usage();
        return 1;
    }
    pc_components pc;
    FILE *out = fopen(argv[2], "w");
    FILE *in = fopen(argv[1], "r");
    if (!(out&&in)){
        perror("Can't open file");
        return 2;
    }
    while (read_pc_components(in, &pc)){
    	fwrite(&pc, sizeof (pc), 1, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}
