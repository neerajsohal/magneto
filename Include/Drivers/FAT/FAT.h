#include "kore\kmsgs.h"
#include "iostream.h"
#include "drivers\fdc\fdc.h"

#if !defined ( __FAT_H_ )
#define __FAT_H_

/* FAT compatible boot sector data (first 36 bytes) */
typedef struct
{
	unsigned char jmp[3];
	unsigned char oem_name[8];
	unsigned int sec_size;
	unsigned char spc;
	unsigned int res_sec;
	unsigned char num_fats;
	unsigned int tot_rd_ents;
	unsigned int tot_sec16;
	unsigned char media;
	unsigned int fat_size16;
	unsigned int int13_spt;
	unsigned int int13_heads;
	unsigned long hidd_sec;
	unsigned long tot_sec32;
} fat_compat_boot_t;

/* FAT12/FAT16 boot sector structure */
typedef struct
{
	fat_compat_boot_t cb;
	unsigned char int13_drive;
	unsigned char reserved;
	unsigned char boot_sig;
	unsigned long volume_id;
	unsigned char volume_label[11];
	unsigned char fs_type[8];
	unsigned char boot_code[448];
	unsigned int bios_sig;
} fat16_boot_t;

typedef fat16_boot_t fat12_boot_t;

extern const char * FAT_ID;

class FAT
{
 private:
	fat12_boot_t *fat12_boot_info;
 public:
 	FAT();
	~FAT();
	int init();
};

extern FAT fat;

#endif
