#include "drivers\FDC\FDC.h"

#if !defined ( __FDC_CPP_ )
#define __FDC_CPP_

unsigned int mtick, motor, done, tmout, statsz, status[7], sr0, fdc_track, dchange;
extern const char * FDC_ID = "FDC";
/* definition of DMA channels */
const static DmaChannel dmainfo[] = {
   { 0x87, 0x00, 0x01 },
   { 0x83, 0x02, 0x03 },
   { 0x81, 0x04, 0x05 },
   { 0x82, 0x06, 0x07 }
};

FDC::FDC()
{
 fdc_track = 0xff;
 mtick = motor = done = tmout = statsz = sr0 = fdc_track = dchange = 0;
}

FDC::~FDC()
{
 ;
}

void FDC::block2hts(int block, int *head, int *track, int *sector)
{
   *head = (block % (geometry.spt * geometry.heads)) / (geometry.spt);
   *track = block / (geometry.spt * geometry.heads);
   *sector = block % geometry.spt + 1;
}

void FDC::dma_xfer(int channel, long physaddr, int length, unsigned char read)
{
   long page,offset;
      
   /* calculate dma page and offset */
   page = physaddr >> 16;
   offset = physaddr & 0xffff;
   length -= 1;  /* with dma, if you want k bytes, you ask for k - 1 */

   //sti();  /* disable irq's */
   
   /* set the mask bit for the channel */
   outportb(0x0a,channel | 4);
   
   /* clear flipflop */
   outportb(0x0c,0);
   
   /* set DMA mode (write+single+r/w) */
   outportb(0x0b,(read ? 0x48 : 0x44) + channel);
   
   /* set DMA page */
   outportb(dmainfo[channel].page,page);
   
   /* set DMA offset */
   outportb(dmainfo[channel].offset,offset & 0xff);  /* low byte */
   outportb(dmainfo[channel].offset,offset >> 8);    /* high byte */
   
   /* set DMA length */
   outportb(dmainfo[channel].length,length & 0xff);  /* low byte */
   outportb(dmainfo[channel].length,length >> 8);    /* high byte */
   
   /* clear DMA mask bit */
   outportb(0x0a,channel);
   
  // cli();  /* enable irq's */
}

int FDC::init()
{
 cout<<endl<<"FDC:";
 int ver;
 mtick=0xffffffff;
 tbaddr = 0x1000;
 interrupts.enable_irq(0x06, FDC_irq, TRAP_GATE|BITS_32|PRESENT|RING_2);
 interrupts.enable_irq(0x1c, INT_1C, TRAP_GATE|BITS_32|PRESENT|RING_2);
 reset();
 /* get floppy controller version */
 sendbyte(CMD_VERSION);
 ver = getbyte();

 if (ver == 0x80)
	cout<<"\n\tNEC765 controller found";
 else
	cout<<"\n\tEnhanced controller found";
 
 return KMSG_SUCCESS;
}

void FDC::motoron(void)
{
   if (!motor) {
      mtick = -1;     /* stop motor kill countdown */
      outportb(FDC_DOR,0x1c);
	  do_delay(100); /* delay 100ms for motor to spin up */
      motor = TRUE;
   }
}

/* this turns the motor off */
void FDC::motoroff(void)
{
   if (motor) {
      mtick = 36;   /* start motor kill countdown: 36 ticks ~ 2s */
   }
}

/* recalibrate the drive */
void FDC::recalibrate(void)
{
   /* turn the motor on */
   motoron();
   
   /* send actual command bytes */
   sendbyte(CMD_RECAL);
   sendbyte(0);

   /* wait until seek finished */
   waitfdc(TRUE);
   
   /* turn the motor off */
   motoroff();
}

/* this gets the FDC to a known state */
int FDC::reset(void)
{
   /* stop the motor and disable IRQ/DMA */
   outportb(FDC_DOR,0);
   
   mtick = 0;
   motor = FALSE;

   /* program data rate (500K/s) */
   outportb(FDC_DRS,0);

   /* re-enable interrupts */
   outportb(FDC_DOR,0x0c);

   /* resetting triggered an interrupt - handle it */
   done = TRUE;
   waitfdc(TRUE);
   /* specify drive timings (got these off the BIOS) */
   sendbyte(CMD_SPECIFY);
   sendbyte(0xdf);  /* SRT = 3ms, HUT = 240ms */
   sendbyte(0x02);  /* HLT = 16ms, ND = 0 */
   
   /* clear "disk change" status */
   seek(1);
   
   recalibrate();

   dchange = FALSE;
   return NULL;
}

unsigned char FDC::waitfdc(unsigned char sensei)
{
   tmout = 18;   /* set timeout to 1 second */
     
   /* wait for IRQ6 handler to signal command finished */
   while (!done && tmout);
   
   /* read in command result bytes */
   statsz = 0;
   while ((statsz < 7) && (inportb(FDC_MSR) & (1<<4))) {
      status[statsz++] = getbyte();
   }
   

   if (sensei) {
      /* send a "sense interrupt status" command */
      sendbyte(CMD_SENSEI);
      sr0 = getbyte();
      fdc_track = getbyte();
   }
   
   done = FALSE;
   
   if (!tmout) {
      /* timed outportb! */
      if (inportb(FDC_DIR) & 0x80)  /* check for diskchange */
	dchange = TRUE;
      return FALSE;
   } else	{
     return TRUE;
    }
}

/* seek to track */
unsigned char FDC::seek(int track)
{
   if (fdc_track == track)  /* already there? */
     return TRUE;
	motoron();
   /* send actual command bytes */
   sendbyte(CMD_SEEK);
   sendbyte(0);
   sendbyte(track);
  
   /* wait until seek finished */
   if (!waitfdc(TRUE))
     return FALSE;     /* timeout! */
   
   /* now let head settle for 15ms */
   do_delay(15);
   
   motoroff();
   
   /* check that seek worked */
   if ((sr0 != 0x20) || (fdc_track != track))
     return FALSE;
   else
     return TRUE;
}

/* sendbyte() routine from intel manual */
void FDC::sendbyte(int byte)
{
   volatile int msr;
   int tmo;
   
   for (tmo = 0;tmo < 128;tmo++) {
      msr = inportb(FDC_MSR);
      if ((msr & 0xc0) == 0x80) {
	 outportb(FDC_DATA,byte);
	 return;
      }
      inportb(0x80);   /* delay */
   }
}

/* getbyte() routine from intel manual */
int FDC::getbyte()
{
   volatile int msr;
   int tmo;
   
   for (tmo = 0;tmo < 128;tmo++) {
      msr = inportb(FDC_MSR);
      if ((msr & 0xd0) == 0xd0) {
	 return inportb(FDC_DATA);
      }
      inportb(0x80);   /* delay */
   }

   return -1;   /* read timeout */
}

/* read block (blockbuff is 512 byte buffer) */
unsigned char FDC::read_block(int block, unsigned char *blockbuff)
{
   return fdc_rw(block, blockbuff, TRUE);
}

/* write block (blockbuff is 512 byte buffer) */
unsigned char FDC::write_block(int block, unsigned char *blockbuff)
{
   return fdc_rw(block, blockbuff, FALSE);
}

/*
 * since reads and writes differ only by a few lines, this handles both.  This
 * function is called by read_block() and write_block()
 */
unsigned char FDC::fdc_rw(int block, unsigned char *blockbuff, unsigned char read)
{
   int head,track,sector,tries,i;

   /* convert logical address into physical address */
   block2hts(block,&head,&track,&sector);
   
   /* spin up the disk */
   motoron();

   if (!read && blockbuff) {
      /* copy data from data buffer into track buffer */
      memcpy((void *)tbaddr,(void *)blockbuff,512);
   }
   
   for (tries = 0; tries < 3; tries++) {
      /* check for diskchange */
      if (inportb(FDC_DIR) & 0x80) {
	 dchange = TRUE;
	 seek(1);  /* clear "disk change" status */
	 recalibrate();
	 motoroff();
	 return FALSE;
      }
         
      /* move head to right track */
      if (!seek(track)) {
	 motoroff();
	 return FALSE;
      }
      
      /* program data rate (500K/s) */
      outportb(FDC_CCR, 0);
      
      /* send command */
      if (read) {
	 dma_xfer(2, tbaddr, 512, FALSE);
	 sendbyte(CMD_READ);
      } else {
	 dma_xfer(2, tbaddr, 512, TRUE);
	 sendbyte(CMD_WRITE);
      }
      
      sendbyte(head << 2);
      sendbyte(track);
      sendbyte(head);
      sendbyte(sector);
      sendbyte(2);               /* 512 bytes/sector */
      sendbyte(geometry.spt);
      if (geometry.spt == DG144_SPT)
	sendbyte(DG144_GAP3RW);  /* gap 3 size for 1.44M read/write */
      else
	sendbyte(DG168_GAP3RW);  /* gap 3 size for 1.68M read/write */
      sendbyte(0xff);            /* DTL = unused */
      
      /* wait for command completion */
      /* read/write don't need "sense interrupt status" */
      if (!waitfdc(FALSE))	{
		return FALSE;   /* timed outportb! */ 
	}
      
      if ((status[0] & 0xc0) == 0) break;   /* worked! outta here! */
   
      recalibrate();  /* oops, try again... */
   }
   
   /* stop the motor */
   motoroff();

   if (read && blockbuff) {
    /* copy data from track buffer into data buffer */
    memcpy((void *)blockbuff,(void *)tbaddr,512);
   }

   return (tries != 3);
}

/* this formats a track, given a certain geometry */
unsigned char FDC::format_track(unsigned char track,DrvGeom *g)
{
   int i,h,r,r_id,split;
   unsigned char tmpbuff[256];

   /* check geometry */
   if (g->spt != DG144_SPT && g->spt != DG168_SPT)	{
     return FALSE;
    }
   
   /* spin up the disk */
   motoron();

   /* program data rate (500K/s) */
   outportb(FDC_CCR,0);

   seek(track);  /* seek to track */

   /* precalc some constants for interleave calculation */
   split = g->spt / 2;
   if (g->spt & 1) split++;
   
   for (h = 0;h < g->heads;h++) {
      /* for each head... */
      
      /* check for diskchange */
      if (inportb(FDC_DIR) & 0x80) {
	 dchange = TRUE;
	 seek(1);  /* clear "disk change" status */
	 recalibrate();
	 motoroff();
	 return FALSE;
      }

      i = 0;   /* reset buffer index */
      for (r = 0;r < g->spt;r++) {
	 /* for each sector... */

	 /* calculate 1:2 interleave (seems optimal in my system) */
	 r_id = r / 2 + 1;
	 if (r & 1) r_id += split;
	 
	 /* add some head skew (2 sectors should be enough) */
	 if (h & 1) {
	    r_id -= 2;
	    if (r_id < 1) r_id += g->spt;
	 }
      
	 /* add some track skew (1/2 a revolution) */
	 if (track & 1) {
	    r_id -= g->spt / 2;
	    if (r_id < 1) r_id += g->spt;
	 }
	 
	 /**** interleave now calculated - sector ID is stored in r_id ****/

	 /* fill in sector ID's */
	 tmpbuff[i++] = track;
	 tmpbuff[i++] = h;
	 tmpbuff[i++] = r_id;
	 tmpbuff[i++] = 2;
      }

      /* copy sector ID's to track buffer */
      memcpy((void *)tbaddr,(void *)tmpbuff,i);
      
      /* start dma xfer */
      dma_xfer(2,tbaddr,i,TRUE);
      
      /* prepare "format track" command */
      sendbyte(CMD_FORMAT);
      sendbyte(h << 2);
      sendbyte(2);
      sendbyte(g->spt);
      if (g->spt == DG144_SPT)      
	sendbyte(DG144_GAP3FMT);    /* gap3 size for 1.44M format */
      else
	sendbyte(DG168_GAP3FMT);    /* gap3 size for 1.68M format */
      sendbyte(0);     /* filler byte */
	 
      /* wait for command to finish */
      if (!waitfdc(FALSE))	{
	return FALSE; 
	}
      
      if (status[0] & 0xc0) {
	 motoroff();
	 return FALSE;
      }
   }
   
   motoroff();
   
   return TRUE;
}

FDC fdc;

#endif
