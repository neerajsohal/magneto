#include "x86.h"
#include "iostream.h"
#include "interrupts.h"
#include "kore\kmsgs.h"
#include "kore\delay.h"

#if !defined ( __FDC_H_ )
#define __FDC_H_

/* datatypes */

/* drive geometry */
typedef struct DrvGeom {
   unsigned char heads;
   unsigned char tracks;
   unsigned char spt;     /* sectors per track */
} DrvGeom;

/* drive geometries */
#define DG144_HEADS       2     /* heads per drive (1.44M) */
#define DG144_TRACKS     80     /* number of tracks (1.44M) */
#define DG144_SPT        18     /* sectors per track (1.44M) */
#define DG144_GAP3FMT  0x54     /* gap3 while formatting (1.44M) */
#define DG144_GAP3RW   0x1b     /* gap3 while reading/writing (1.44M) */

#define DG168_HEADS       2     /* heads per drive (1.68M) */
#define DG168_TRACKS     80     /* number of tracks (1.68M) */
#define DG168_SPT        21     /* sectors per track (1.68M) */
#define DG168_GAP3FMT  0x0c     /* gap3 while formatting (1.68M) */
#define DG168_GAP3RW   0x1c     /* gap3 while reading/writing (1.68M) */

/* IO ports */
#define FDC_DOR  (0x3f2)   /* Digital Output Register */
#define FDC_MSR  (0x3f4)   /* Main Status Register (input) */
#define FDC_DRS  (0x3f4)   /* Data Rate Select Register (output) */
#define FDC_DATA (0x3f5)   /* Data Register */
#define FDC_DIR  (0x3f7)   /* Digital Input Register (input) */
#define FDC_CCR  (0x3f7)   /* Configuration Control Register (output) */

/* command bytes (these are 765 commands + options such as MFM, etc) */
#define CMD_SPECIFY (0x03)  /* specify drive timings */
#define CMD_WRITE   (0xc5)  /* write data (+ MT,MFM) */
#define CMD_READ    (0xe6)  /* read data (+ MT,MFM,SK) */
#define CMD_RECAL   (0x07)  /* recalibrate */
#define CMD_SENSEI  (0x08)  /* sense interrupt status */
#define CMD_FORMAT  (0x4d)  /* format track (+ MFM) */
#define CMD_SEEK    (0x0f)  /* seek track */
#define CMD_VERSION (0x10)  /* FDC version */
#define FDC_TIMER_FREQ 18

/* useful macros */
#define BITFIELD(name,width) unsigned int name : width
#define HIBYTE(x) ((BYTE)((x) >> 8))
#define LOBYTE(x) ((BYTE)((x) & 0xff))
#define ABS(x) ((x) < 0 ? -(x) : (x))    /* NB: multiple evaluations! */

typedef struct DmaChannel {
   unsigned char page;     /* page register */
   unsigned char offset;   /* offset register */
   unsigned char length;   /* length register */
} DmaChannel;

void dma_xfer(int, long, int, unsigned char);

void FDC_irq();
void INT_1C();

static DrvGeom geometry = { DG144_HEADS,DG144_TRACKS,DG144_SPT };

extern unsigned int mtick, motor, done, tmout, statsz, status[7], sr0, fdc_track, dchange;
extern const char * FDC_ID;
class FDC
{
 private:
	long tbaddr;    /* physical address of track buffer located below 1M */
	void block2hts(int , int *, int *, int *);
	void dma_xfer(int, long, int, unsigned char);
	unsigned char fdc_rw(int block,unsigned char *,unsigned char);
	
 public:
    FDC();
    ~FDC();
    int init();
    int reset(void);
    void motoron(void);
    void motoroff(void);
    void recalibrate(void);
    unsigned char waitfdc(unsigned char);
    unsigned char seek(int track);
    unsigned char log_disk(DrvGeom *g);
    unsigned char read_block(int, unsigned char *);
    unsigned char write_block(int, unsigned char *);
    unsigned char format_track(unsigned char, DrvGeom *);
    void sendbyte(int);
    int getbyte();
};

extern FDC fdc;

#endif
