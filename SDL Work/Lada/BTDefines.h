/////////////////////////////////////////////////////////////////////////////
//
// NexgenIPL - Next Generation Image Processing Library
// Copyright (C) 1999-2001 Binary Technologies
// All Rights Reserved.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is
// not sold for profit without the authors written consent, and
// providing that this notice and the authors name is included. If
// the source code in this file is used in any commercial application
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Binary Technologies
// http://www.binary-technologies.de
// info@binary-technologies.de
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BTDEFINES_INCLUDED
#define BTDEFINES_INCLUDED

#pragma once

typedef unsigned long		BTCOLORREF;

#define BTRGB(r,g,b)		((unsigned long)(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)))
#define BTRGBA(r,g,b,a)		((unsigned long)(((unsigned char)(r)|((unsigned short)((unsigned char)(g))<<8))|(((unsigned long)(unsigned char)(b))<<16)|(((unsigned long)(a))<<24)))

#define BTGetRValue(rgba)	((unsigned char)(rgba))
#define BTGetGValue(rgba)	((unsigned char)(((unsigned short)(rgba)) >> 8))
#define BTGetBValue(rgba)	((unsigned char)((rgba)>>16))
#define BTGetAValue(rgba)	((unsigned char)((rgba)>>24))

typedef struct tagBTRGBQUAD
{
	unsigned char rgbBlue;
	unsigned char rgbGreen;
	unsigned char rgbRed;
	unsigned char rgbReserved;
} BTRGBQUAD;

typedef struct tagBTHLS
{
	double Hue;
	double Lightness;
	double Saturation;
} BTHLS;

typedef struct tagBTHSB
{
	double Hue;
	double Saturation;
	double Brightness;
} BTHSB;

enum BTFileType
{
	BTFILETYPE_UNKNOWN,
	BTFILETYPE_BMP,
	BTFILETYPE_PCX,
	BTFILETYPE_PNG,
	BTFILETYPE_PPM_BIN,
	BTFILETYPE_PPM_ASCII,
	BTFILETYPE_PGM_BIN,
	BTFILETYPE_PGM_ASCII,
	BTFILETYPE_PBM_BIN,
	BTFILETYPE_PBM_ASCII,
	BTFILETYPE_JPEG,
	BTFILETYPE_TGA,
	BTFILETYPE_TIFF,
	BTFILETYPE_GIF,
	BTFILETYPE_ILBM,
	BTFILETYPE_RAS,
	BTFILETYPE_EPS,
	BTFILETYPE_MNG,
	BTFILETYPE_WMF,
	BTFILETYPE_EMF,
	BTFILETYPE_APM,
	BTFILETYPE_EXTERN
};

enum BTCodecType
{
	BTCODECTYPE_DECODER,
	BTCODECTYPE_ENCODER
};

typedef struct tagBTParamJPEG
{
	enum BTDCTMethod	{	DCT_ISlow,		// Slow but accurate integer algorithm.
							DCT_IFast,		// Faster, less accurate integer method.
							DCT_Float };	// Floating-point: accurate, fast on fast HW.

	int		nQuality;			// [in] Quality of compression on a scale from 0..100 [low..best].
	int		nSmoothingFactor;	// [in] 1..100, or 0 for no input smoothing.
	bool	bOptimizeCoding;	// [in] true = optimize entropy encoding parms.
	int		nDCTMethod;			// [in|out] DCT/IDCT algorithm option.

	tagBTParamJPEG::tagBTParamJPEG()	:	nQuality(0),
											nSmoothingFactor(0),
											bOptimizeCoding(false),
											nDCTMethod(DCT_Float) {};
} BTParamJPEG;

typedef struct tagBTParamPGM
{
	char* pszDescription;	// [in] Text that will be saved in the file. Each line
							// must start with a '#':
							//
							// BTParamPGM Param;
							// Param.pszDescription = "# 1. Line\n# 2. Line\n# 3. Line";
} BTParamPGM;

typedef struct tagBTParamPPM
{
	char* pszDescription;	// [in] Text that will be saved in the file. Each line
							// must start with a '#':
							//
							// BTParamPPM Param;
							// Param.pszDescription = "# 1. Line\n# 2. Line\n# 3. Line";
} BTParamPPM;

typedef struct tagBTParamTIFF
{
	enum BTTIFFCodec	{	None      = 1,
							CCITTRLE  = 2,
							CCITTRLEW = 32771,
							CCITTFAX3 = 3,
							CCITTFAX4 = 4,
							JPEG      = 7,
							PACKBITS  = 32773 };

	char* pszTitle;       // [in]
	char* pszAuthor;      // [in]
	char* pszDescription; // [in]
	char* pszSoftware;    // [in]
	long  lCodec;         // [in]

	tagBTParamTIFF::tagBTParamTIFF() :	pszTitle(NULL),
										pszAuthor(NULL),
										pszDescription(NULL),
										pszSoftware(NULL),
										lCodec(None) {};
} BTParamTIFF;

typedef struct tagBTParamPNG
{
	char* pszTitle;       // [in]
	char* pszAuthor;      // [in]
	char* pszDescription; // [in]
	char* pszCopyright;   // [in]
	char* pszSoftware;    // [in]
	char* pszDisclaimer;  // [in]
	char* pszComment;     // [in]
} BTParamPNG;

typedef struct tagBTParamGIF
{
	int				nTransparentColor;	// [in|out] Palette index of transparent color.
	int				nBackgroundColor;	// [out]
	int				nDelay;				// [out]
	int				nImageIndex;		// [in]		Requested image.
	int				nImageCount;		// [out]	Number of images.
	unsigned char	szComment[256];		// [in|out]

	tagBTParamGIF::tagBTParamGIF()	:	nTransparentColor(-1),
										nBackgroundColor(-1),
										nDelay(0),
										nImageIndex(1),
										nImageCount(0) {};
} BTParamGIF;

#endif // BTDEFINES_INCLUDED
