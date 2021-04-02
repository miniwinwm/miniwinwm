/*""FILE COMMENT""*******************************************************************
* File Name		: r_tfat_lib.h
* Version      	: 1.01
* Device(s)    	: Renesas MCUs
* Tool-Chain 	:
* H/W Platform 	:
* Description	: TFAT File System library header file
*************************************************************************************
* History	: DD.MM.YYYY Version Description
*""FILE COMMENT END""****************************************************************/
#ifndef _R_TFAT_LIB_H_
#define	_R_TFAT_LIB_H_

#include "r_stdint.h"
#include "r_mw_version.h"
/***********************************************************************************
Macro definitions
***********************************************************************************/
/* File access control and file status flags (FIL.flag) */
#define	TFAT_FA_OPEN_EXISTING	0x00
#define	TFAT_FA_READ			0x01
#define TFAT_FA__ERROR			0x80

#define	TFAT_FA_WRITE			0x02
#define	TFAT_FA_CREATE_NEW		0x04
#define	TFAT_FA_CREATE_ALWAYS	0x08
#define	TFAT_FA_OPEN_ALWAYS		0x10
#define TFAT_FA__WRITTEN		0x20
#define TFAT_FA__DIRTY			0x40

/* File attribute bits for directory entry */
#define	TFAT_AM_RDO				0x01	/* Read only */
#define	TFAT_AM_HID				0x02	/* Hidden */
#define	TFAT_AM_SYS				0x04	/* System */
#define	TFAT_AM_VOL				0x08	/* Volume label */
#define TFAT_AM_LFN				0x0F	/* LFN entry */
#define TFAT_AM_DIR				0x10	/* Directory */
#define TFAT_AM_ARC				0x20	/* Archive */
#define TFAT_AM_MASK			0x3F	/* Mask of defined bits */

/* Disk Status Bits (DSTATUS) */
#define TFAT_STA_NOINIT			0x01	/* Drive not initialized */
#define TFAT_STA_NODISK			0x02	/* No medium in the drive */
#define TFAT_STA_PROTECT		0x04	/* Write protected */


/************************************************************************************
Type Definitions
************************************************************************************/
/* Status of Disk Functions */
typedef uint8_t DSTATUS;

/* File system object structure */
typedef struct {
	uint8_t		fs_type;		/* FAT sub-type (0:Not mounted) */
	uint8_t		drv;			/* Physical drive number */
	uint8_t		csize;			/* Sectors per cluster (1,2,4...128) */
	uint8_t		n_fats;			/* Number of FAT copies (1,2) */
	uint8_t		wflag;			/* win[] dirty flag (1:must be written back) */
	uint8_t		fsi_flag;		/* fsinfo dirty flag (1:must be written back) */
	uint16_t	id;				/* File system mount ID */
	uint16_t	n_rootdir;		/* Number of root directory entries (FAT12/16) */
	uint32_t	last_clust;		/* Last allocated cluster */
	uint32_t	free_clust;		/* Number of free clusters */
	uint32_t	fsi_sector;		/* fsinfo sector (FAT32) */
	uint32_t	n_fatent;		/* Number of FAT entries (= number of clusters + 2) */
	uint32_t	fsize;			/* Sectors per FAT */
	uint32_t	volbase;		/* Volume start sector */
	uint32_t	fatbase;		/* FAT start sector */
	uint32_t	dirbase;		/* Root directory start sector (FAT32:Cluster#) */
	uint32_t	database;		/* Data start sector */
	uint32_t	winsect;		/* Current sector appearing in the win[] */
	uint8_t		win[512];		/* Disk access window for Directory, FAT (and Data on tiny cfg) */
} FATFS;

/* Directory object structure */
typedef struct {
	FATFS*		fs;				/* Pointer to the owner file system object (**do not change order**) */
	uint16_t	id;				/* Owner file system mount ID (**do not change order**) */
	uint16_t	index;			/* Current read/write index number */
	uint32_t	sclust;			/* Table start cluster (0:Root dir) */
	uint32_t	clust;			/* Current cluster */
	uint32_t	sect;			/* Current sector */
	uint8_t*	dir;			/* Pointer to the current SFN entry in the win[] */
	uint8_t*	fn;				/* Pointer to the SFN (in/out) {file[8],ext[3],status[1]} */
#if _USE_TFAT_LFN
	uint16_t*	lfn;			/* Pointer to the LFN working buffer */
	uint16_t	lfn_idx;		/* Last matched LFN index number (0xFFFF:No LFN) */
#endif /* _USE_TFAT_LFN */
} DIR;

/* File object structure */
typedef struct {
	FATFS*		fs;				/* Pointer to the related file system object (**do not change order**) */
	uint16_t	id;				/* Owner file system mount ID (**do not change order**) */
	uint8_t		flag;			/* File status flags */
	uint8_t		pad1;
	uint32_t	fptr;			/* File read/write pointer (0ed on file open) */
	uint32_t	fsize;			/* File size */
	uint32_t	sclust;			/* File data start cluster (0:no data cluster, always 0 when fsize is 0) */
	uint32_t	clust;			/* Current cluster of fpter */
	uint32_t	dsect;			/* Current data sector of fpter */
	uint32_t	dir_sect;		/* Sector containing the directory entry */
	uint8_t*	dir_ptr;		/* Pointer to the directory entry in the window */
} FIL;

/* File status structure */
typedef struct {
	uint32_t	fsize;			/* File size */
	uint16_t	fdate;			/* Last modified date */
	uint16_t	ftime;			/* Last modified time */
	uint8_t		fattrib;		/* Attribute */
	char		fname[13];		/* Short file name (8.3 format) */
#if _USE_TFAT_LFN
	char*		lfname;			/* Pointer to the LFN buffer */
	uint16_t 	lfsize;			/* Size of LFN buffer in TCHAR */
#endif /* _USE_TFAT_LFN */
} FILINFO;


/* File function return code (FRESULT) */
typedef enum
{
	TFAT_FR_OK = 0,				/* 0 */
	TFAT_FR_DISK_ERR,			/* 1 */
	TFAT_FR_INT_ERR,			/* 2 */
	TFAT_FR_NOT_READY,			/* 3 */
	TFAT_FR_NO_FILE,			/* 4 */
	TFAT_FR_NO_PATH,			/* 5 */
	TFAT_FR_INVALID_NAME,		/* 6 */
	TFAT_FR_DENIED,				/* 7 */
	TFAT_FR_EXIST,				/* 8 */
	TFAT_FR_INVALID_OBJECT,		/* 9 */
	TFAT_FR_WRITE_PROTECTED,	/* 10 */
	TFAT_FR_INVALID_DRIVE,		/* 11 */
	TFAT_FR_NOT_ENABLED,		/* 12 */
	TFAT_FR_NO_FILESYSTEM,		/* 13 */
	TFAT_FR_MKFS_ABORTED,		/* 14 */
	TFAT_FR_TIMEOUT,			/* 15 */
	TFAT_FR_LOCKED,				/* 16 */
	TFAT_FR_NOT_ENOUGH_CORE,	/* 17 */
	TFAT_FR_TOO_MANY_OPEN_FILES, /* 18 */
	TFAT_FR_INVALID_PARAMETER	/* 19 */
} FRESULT;

/* Results of Disk Functions */
typedef enum
{
	TFAT_RES_OK = 0,			/* 0: Successful */
	TFAT_RES_ERROR,				/* 1: R/W Error */
	TFAT_RES_WRPRT,				/* 2: Write Protected */
	TFAT_RES_NOTRDY,			/* 3: Not Ready */
	TFAT_RES_PARERR				/* 4: Invalid Parameter */
} DRESULT;

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
/* Library functions */

/* Mount/Unmount a logical drive */
FRESULT R_tfat_f_mount(uint8_t, FATFS*);
/* Open or create a file */
FRESULT R_tfat_f_open(FIL*, const char*, uint8_t);
/* Read data from a file */
FRESULT R_tfat_f_read(FIL*, void*, uint16_t, uint16_t*);
/* Write data to a file */
FRESULT R_tfat_f_write(FIL*, const void*, uint16_t, uint16_t*);
/* Move file pointer of a file object */
FRESULT R_tfat_f_lseek(FIL*, uint32_t);
/* Close an open file object */
FRESULT R_tfat_f_close(FIL*);
/* Open an existing directory */
FRESULT R_tfat_f_opendir(DIR*, const char*);
/* Read a directory item */
FRESULT R_tfat_f_readdir(DIR*, FILINFO*);
/* Get file status */
FRESULT R_tfat_f_stat(const char*, FILINFO*);
/* Get number of free clusters on the drive */
FRESULT R_tfat_f_getfree(const char*, uint32_t*, FATFS**);
/* Truncate file */
FRESULT R_tfat_f_truncate(FIL*);
/* Flush cached data of a writing file */
FRESULT R_tfat_f_sync(FIL*);
/* Delete an existing file or directory */
FRESULT R_tfat_f_unlink(const char*);
/* Create a new directory */
FRESULT R_tfat_f_mkdir(const char*);
/* Change file/dir attriburte */
FRESULT R_tfat_f_chmod(const char*, uint8_t, uint8_t);
/* Change file/dir timestamp */
FRESULT R_tfat_f_utime(const char*, const FILINFO*);
/* Rename/Move a file or directory */
FRESULT R_tfat_f_rename(const char*, const char*);
/* Forward data to the stream */
#if defined(__K0R__)
FRESULT R_tfat_f_forward(FIL*, uint16_t(*)(const uint8_t*, uint16_t), unsigned short, uint16_t*);
#else
FRESULT R_tfat_f_forward(FIL*, uint16_t(*)(const uint8_t*, uint16_t), uint16_t, uint16_t*);
#endif
/* Memory driver interface functions */
DSTATUS R_tfat_disk_initialize(uint8_t);
DRESULT R_tfat_disk_read(uint8_t, uint8_t*, uint32_t, uint8_t);
DRESULT R_tfat_disk_write(uint8_t, const uint8_t*, uint32_t, uint8_t);
DRESULT R_tfat_disk_ioctl(uint8_t, uint8_t, void*);
DSTATUS R_tfat_disk_status(uint8_t);
/* User defined function to give a current time to fatfs module */
/* 31-25: Year(0-127 +1980), 24-21: Month(1-12), 20-16: Day(1-31)
   15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */
uint32_t R_tfat_get_fattime(void);

/* TFAT library version */
extern const mw_version_t R_tfat_version;

#endif	/*	_R_TFAT_LIB_H_ 	*/
