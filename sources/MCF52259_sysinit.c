/*
 * File:		mcf52259_sysinit.c
 * Purpose:		Reset configuration of the MCF52259
 *
 * Notes:
 */
#include "support_common.h"
#include "exceptions.h"

/************************************************************/
/*                  ��ʼ��ϵͳ��ƵΪ40MHz                   */
/************************************************************/
void pll_init_40M(void)
{
	//fsys ������ʽ��fsys = fref �� 2 �� (MFD + 2) �� (2 ^ RFD);
	//fref ���㹫ʽ��fref= fosc / (CCHR+1);
	//MCF_CLOCK_CCHR Ĭ��ֵΪ5	
	//MFD=3,RFD=1��ϵͳƵ�ʼ��㣺
	//fsys=48MHz / (CCHR+1) �� 2 �� (MFD + 2) �� (2^RFD) = 40Mhz.
	
    MCF_CLOCK_SYNCR =  MCF_CLOCK_SYNCR_MFD(3) 
                     | MCF_CLOCK_SYNCR_RFD(1)
                     | MCF_CLOCK_SYNCR_CLKSRC
                     | MCF_CLOCK_SYNCR_PLLMODE 
                     | MCF_CLOCK_SYNCR_PLLEN ;
    while (!(MCF_CLOCK_SYNSR & MCF_CLOCK_SYNSR_LOCK))   //�ȴ����໷����
    {
    }
}

/************************************************************/
/*                  ��ʼ��ϵͳ��ƵΪ80MHz                   */
/************************************************************/
void pll_init_80M(void)
{
	//fsys ������ʽ��fsys = fref �� 2 �� (MFD + 2) �� (2 ^ RFD);
	//fref ���㹫ʽ��fref= fosc / (CCHR+1);
	//MCF_CLOCK_CCHR Ĭ��ֵΪ5	
	//MFD=3,RFD=0��ϵͳƵ�ʼ��㣺
	//fsys=48MHz / (CCHR+1) �� 2 �� (MFD + 2) �� (2^RFD) = 80Mhz.
	
    MCF_CLOCK_SYNCR =  MCF_CLOCK_SYNCR_MFD(3) 
                     | MCF_CLOCK_SYNCR_RFD(0)
                     | MCF_CLOCK_SYNCR_CLKSRC
                     | MCF_CLOCK_SYNCR_PLLMODE 
                     | MCF_CLOCK_SYNCR_PLLEN ;
    while (!(MCF_CLOCK_SYNSR & MCF_CLOCK_SYNSR_LOCK))   //�ȴ����໷����
    {
    }
}

/************************************************************/
/*                  ��ʼ��ϵͳ��ƵΪ96MHz                   */
/************************************************************/
void pll_init_96M(void)
{
	//fsys ������ʽ��fsys = fref �� 2 �� (MFD + 2) �� (2 ^ RFD);
	//fref ���㹫ʽ��fref= fosc / (CCHR+1);
	//MCF_CLOCK_CCHR Ĭ��ֵΪ5	
	//MFD=4,RFD=0��ϵͳƵ�ʼ��㣺
	//fsys=48MHz / (CCHR+1) �� 2 �� (MFD + 2) �� (2^RFD) = 96Mhz.
	
    MCF_CLOCK_SYNCR =  MCF_CLOCK_SYNCR_MFD(4) 
                     | MCF_CLOCK_SYNCR_RFD(0)
                     | MCF_CLOCK_SYNCR_CLKSRC
                     | MCF_CLOCK_SYNCR_PLLMODE 
                     | MCF_CLOCK_SYNCR_PLLEN ;
    while (!(MCF_CLOCK_SYNSR & MCF_CLOCK_SYNSR_LOCK))   //�ȴ����໷����
    {
    }
}

/************************************************************/
/*                  ��ʼ��ϵͳ��ƵΪ112MHz                   */
/************************************************************/
void pll_init_112M(void)
{
	//fsys ������ʽ��fsys = fref �� 2 �� (MFD + 2) �� (2 ^ RFD);
	//fref ���㹫ʽ��fref= fosc / (CCHR+1);
	//MCF_CLOCK_CCHR Ĭ��ֵΪ5	
	//MFD=5,RFD=0��ϵͳƵ�ʼ��㣺
	//fsys=48MHz / (CCHR+1) �� 2 �� (MFD + 2) �� (2^RFD) = 112Mhz.
	
    MCF_CLOCK_SYNCR =  MCF_CLOCK_SYNCR_MFD(5) 
                     | MCF_CLOCK_SYNCR_RFD(0)
                     | MCF_CLOCK_SYNCR_CLKSRC
                     | MCF_CLOCK_SYNCR_PLLMODE 
                     | MCF_CLOCK_SYNCR_PLLEN ;
    while (!(MCF_CLOCK_SYNSR & MCF_CLOCK_SYNSR_LOCK))   //�ȴ����໷����
    {
    }
}

/************************************************************/
/*                  ��ʼ��ϵͳ��ƵΪ128MHz                   */
/************************************************************/
void pll_init_128M(void)
{
	//fsys ������ʽ��fsys = fref �� 2 �� (MFD + 2) �� (2 ^ RFD);
	//fref ���㹫ʽ��fref= fosc / (CCHR+1);
	//MCF_CLOCK_CCHR Ĭ��ֵΪ5	
	//MFD=6,RFD=0��ϵͳƵ�ʼ��㣺
	//fsys=48MHz / (CCHR+1) �� 2 �� (MFD + 2) �� (2^RFD) = 128Mhz.
	
    MCF_CLOCK_SYNCR =  MCF_CLOCK_SYNCR_MFD(6) 
                     | MCF_CLOCK_SYNCR_RFD(0)
                     | MCF_CLOCK_SYNCR_CLKSRC
                     | MCF_CLOCK_SYNCR_PLLMODE 
                     | MCF_CLOCK_SYNCR_PLLEN ;
    while (!(MCF_CLOCK_SYNSR & MCF_CLOCK_SYNSR_LOCK))   //�ȴ����໷����
    {
    }
}

/************************************************************/
/*                  ��ʼ��ϵͳ��ƵΪ144MHz                   */
/************************************************************/
void pll_init_144M(void)
{
	//fsys ������ʽ��fsys = fref �� 2 �� (MFD + 2) �� (2 ^ RFD);
	//fref ���㹫ʽ��fref= fosc / (CCHR+1);
	//MCF_CLOCK_CCHR Ĭ��ֵΪ5	
	//MFD=7,RFD=0��ϵͳƵ�ʼ��㣺
	//fsys=48MHz / (CCHR+1) �� 2 �� (MFD + 2) �� (2^RFD) = 144Mhz.
	
    MCF_CLOCK_SYNCR =  MCF_CLOCK_SYNCR_MFD(7) 
                     | MCF_CLOCK_SYNCR_RFD(0)
                     | MCF_CLOCK_SYNCR_CLKSRC
                     | MCF_CLOCK_SYNCR_PLLMODE 
                     | MCF_CLOCK_SYNCR_PLLEN ;
    while (!(MCF_CLOCK_SYNSR & MCF_CLOCK_SYNSR_LOCK))   //�ȴ����໷����
    {
    }
}
/********************************************************************/
void
pll_init(void)
{
//MCF_CLOCK_CCHR =0x05; // The PLL pre divider - 48MHz / 6 = 8MHz 
    /* The PLL pre-divider affects this!!! 
             * Multiply 48Mhz reference crystal /CCHR by 10 to achieve system clock of 80Mhz
             */
    MCF_CLOCK_SYNCR = MCF_CLOCK_SYNCR_MFD(3) | MCF_CLOCK_SYNCR_CLKSRC| MCF_CLOCK_SYNCR_PLLMODE | MCF_CLOCK_SYNCR_PLLEN ;
    while (!(MCF_CLOCK_SYNSR & MCF_CLOCK_SYNSR_LOCK))
    {
    }
}

/********************************************************************/
void
scm_init(void)
{
	/*
	 * Enable on-chip modules to access internal SRAM
	 */
	MCF_SCM_RAMBAR = (0
		| MCF_SCM_RAMBAR_BA(RAMBAR_ADDRESS)
		| MCF_SCM_RAMBAR_BDE);
}
/********************************************************************/
void __initialize_hardware(void)
{
	/*******************************************************
	*	Out of reset, the low-level assembly code calls this 
	*	routine to initialize the MCF52259 modules.
	********************************************************/

	asm 
	{
	    /* Initialize IPSBAR */
	    move.l  #__IPSBAR,d0
	       andi.l  #0xC0000000,d0 // need to mask
	    add.l   #0x1,d0
	    move.l  d0,0x40000000

	    

	    /* Initialize FLASHBAR */
	    move.l  #__FLASHBAR,d0
	       andi.l  #0xFFF80000,d0 // need to mask
	    add.l   #0x61,d0
	    movec   d0,FLASHBAR

	}
   	
	
	pll_init();
	scm_init();	

	initialize_exceptions();
}
