#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "pc.h"

void usage() {
    printf("Usage: program [-f xor -p] filename\nKeys: -f for formatted output, -p for passenger selection\n");
}

int compare(pc_components pc1, pc_components pc2) {
	if (strcmp(pc1.surname, pc2.surname) != 0) return 0;
    if (strcmp(pc1.processor_type, pc2.processor_type) != 0) return 0;
    if (strcmp(pc1.video_controller_type, pc2.video_controller_type) != 0) return 0;
    if (strcmp(pc1.storage_interface_type, pc2.storage_interface_type) != 0) return 0;
    if (strcmp(pc1.operating_system, pc2.operating_system) != 0) return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    FILE *in;
    int f = 0, p = 0;
    if (argc != 3) {
        usage();
        return 1;
    }
    if (strcmp(argv[1], "-f") == 0) {
        f = 1;
    } else if (strcmp(argv[1], "-p") == 0) {
        p = 1;
    } else {
        usage();
        return 2;
    }
    in = fopen(argv[2], "rb");
    pc_components pc;
    if (!in) {
        perror("Can not open file\n");
        return 3;
    }
    
    printf("__________________________________________________________________________________________________________________________________________________________________________________________________\n");
    printf("|        SURNAME          |CPU CNT|         CPU TYPE        |RAM SIZE|         GPU TYPE        |GPU MEM SIZE| ROM TYPE | ROM CNT | ROM SIZE |INT CONTR CNT|EX CONTR CNT|         OS TYPE         |\n");
    printf("__________________________________________________________________________________________________________________________________________________________________________________________________\n");
	if (f) {
		while (fread(&pc, sizeof(pc), 1, in) == 1) {
            printf("|%-25s|%-7d|%-25s|%-8d|%-25s|%-12d|%-10s|%-9d|%-10d|%-13d|%-12d|%-25s|\n", pc.surname, pc.num_processors, pc.processor_type, pc.memory_size, pc.video_controller_type, 	pc.video_memory_size, pc.storage_interface_type, pc.num_hard_drives, pc.hard_drive_capacity, pc.num_integrated_controllers, pc.num_external_controllers, pc.operating_system);
    	}	
    } else {
    	if (p) {
    		pc_components people[100];
        	int num_people = 0;
        	while (fread(&pc, sizeof(pc), 1, in) == 1) {
		    	people[num_people] = pc;
		    	num_people++;
        	}
        	int ans[num_people][num_people];
        	int is_printed[num_people];
        	for (int i = 0; i < num_people; i ++) {
        		for (int j = 0; j < num_people; j ++) {
        			ans[i][j] = 0;
        		}
        		is_printed[i] = 0;
        	}
        	for (int i = 0; i < num_people; i ++) {
        		for (int j = i + 1; j < num_people; j ++) {
        			pc_components p1 = people[i];
        			pc_components p2 = people[j];
        			if (compare(p1, p2)) {
        				ans[i][i] = 1;
        				ans[i][j] = 1;
        				ans[j][j] = 1;
        				ans[j][i] = 1;
        				
        			}
        		}
        	}
        	for (int i = 0; i < num_people; i ++) {
        		for (int j = 0; j < num_people; j ++) {
        			if (ans[i][j] && is_printed[j] == 0) {
        				is_printed[j] = 1;
        				pc_components p1 = people[j];
        				printf("|%-25s|%-7d|%-25s|%-8d|%-25s|%-12d|%-10s|%-9d|%-10d|%-13d|%-12d|%-25s|\n", p1.surname, p1.num_processors, p1.processor_type, p1.memory_size, p1.video_controller_type, 	p1.video_memory_size, p1.storage_interface_type, p1.num_hard_drives, p1.hard_drive_capacity, p1.num_integrated_controllers, p1.num_external_controllers, p1.operating_system);
        			}
        		}
        	}
    	}	
	}
			printf("__________________________________________________________________________________________________________________________________________________________________________________________________\n");
    	
}