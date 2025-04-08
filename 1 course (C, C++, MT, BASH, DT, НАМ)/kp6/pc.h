#ifndef LAABS_PC_COMPONENTS_H
#define LAABS_PC_COMPONENTS_H
typedef struct{
	char surname[25];
	int num_processors;
	char processor_type[20];
	int memory_size;
	char video_controller_type[20];
	int video_memory_size;
	char storage_interface_type[20];
	int num_hard_drives;
	int hard_drive_capacity;
	int num_integrated_controllers;
	int num_external_controllers;
	char operating_system[50];
} pc_components;
#endif