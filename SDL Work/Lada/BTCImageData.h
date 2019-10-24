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

#ifndef BTCIMAGEDATA_INCLUDED
#define BTCIMAGEDATA_INCLUDED

#pragma once

#include "BTNexgenIPL.h"
#include "BTDefines.h"

class BTNEXGENIPL_CLASS_EXPORT BTCHistogram
{
public:
	enum BTChannel	{	Red,
						Green,
						Blue };

	BTCHistogram();
	virtual ~BTCHistogram();

	double GetMeanValue(const enum BTChannel& Channel);

public:
	long	m_r[256];
	long	m_g[256];
	long	m_b[256];

	long	m_lNumPixel; // Total number of pixels in image.
};

class BTNEXGENIPL_CLASS_EXPORT BTCImageData
{
public:
	enum BTChannel			{	Red,
								Green,
								Blue,
								Alpha };

	enum BTDirection		{	Left,
								Right };

	enum BTFilter			{	Box,
								Bilinear,
								Gaussian,
								Hamming,
								Blackman };

	enum BTDeInterlaceType	{	Interpolate,
								Duplicate };

	enum {	BTCMP_IMAGE      = 0x00000001,		// Images are different.
			BTCMP_NUMCOLORS  = 0x00000002,		// Number of colours in palette differ.
			BTCMP_COLOR      = 0x00000004,		// Image colours differ.
			BTCMP_SIZE_X     = 0x00000008,		// Image width differs.
			BTCMP_SIZE_Y     = 0x00000010 };	// Image heights differ.

	static int GetNumColorEntries(int nBitsPerPixel);
	static long GetBytesPerLine(int nWidth, int nBitsPerPixel);
	static unsigned short GetColorTableSize(int nNumColorEntries);
	static long GetImageSize(int nWidth, int nHeight, int nBitsPerPixel);

	static BTHSB RGBtoHSB(BTCOLORREF col);
	static BTCOLORREF HSBtoRGB(const BTHSB& hsb);
	static BTCOLORREF HSBtoRGB(double H, double S, double B);

	static BTHLS RGBtoHLS(BTCOLORREF col);
	static BTCOLORREF HLStoRGB(const BTHLS& hls);
	static BTCOLORREF HLStoRGB(double H, double L, double S);

	static double GetBrightness(BTCOLORREF col);

	static double GetHLSValue(double m1, double m2, double hue);
	static double GetHue(BTCOLORREF col);
	static double GetLightness(BTCOLORREF col);
	static double GetSaturation(BTCOLORREF col);

	int Stretch( HDC hdc, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, int nSrcWidth, int nSrcHeight, int iMode = COLORONCOLOR, unsigned long dwRop = SRCCOPY);
	int Draw( HDC hdc, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, int iMode = COLORONCOLOR, unsigned long dwRop = SRCCOPY);
	int DrawDithered( HDC hdc, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc);

	bool DrawTransparent( HDC hdc, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, BTCOLORREF crColor);
	bool DrawSemiTransparent( HDC hdc, int xDest, int yDest, int nDestWidth, int nDestHeight, int xSrc, int ySrc, BTCOLORREF crColor);

	LPBITMAPINFO GetBitmapInfo();
	LPBITMAPINFOHEADER GetBitmapInfoHeader();

	int GetPlanes() const;
	int GetDepth() const;
	int GetBytesPerPixel() const;
	int GetBitsPerPixel() const;
	long GetBytesPerLine() const;
	long GetImageSize() const;
	long GetWidth() const;
	long GetHeight() const;

	bool GetHistogram(BTCHistogram* pHistogram);

	bool GetChannel(const enum BTChannel& Channel, BTCImageData& Image);	// Destination image given as parameter will be created automatically.
	bool CombineChannels(BTCImageData* pRedImage, BTCImageData* pGreenImage, BTCImageData* pBlueImage);	// All images must have same size and color depth. Destination image (current object) must be initialized with Create(...) before using his method.

	int FindNearestPaletteColor(BTCOLORREF col);

	int GetIndexFromColor(BTCOLORREF col);
	int GetIndexFromPixel(int x, int y);
	BTCOLORREF GetColorFromIndex(int nIndex);
	BTCOLORREF GetColorFromPixel(int x, int y);

	bool SetColorForIndex(int nIndex, BTCOLORREF col);
	bool SetColorForPixel(int x, int y, int nIndex);
	bool SetColorForPixel(int x, int y, BTCOLORREF col);
	bool SetColorForColor(BTCOLORREF oldCol, BTCOLORREF newCol);

	bool IsColorInColorTable(BTCOLORREF col);

	RGBQUAD* GetColorTable();
	unsigned short GetColorTableSize() const;
	bool FillColorTable(RGBQUAD* pPalette, int iEntries);

	HPALETTE GetPalette() const;
	int SetPalette(HPALETTE hPal);

	HANDLE GetDIB();     // Must be freed after usage.
	HBITMAP GetBitmap(); // Must be freed after usage.

	unsigned char* GetBits( int x, int y);
	unsigned char* GetBits() const;

	int GetNumColorEntries() const;

	bool ConvertTo24BPP();
	bool ConvertTo32BPP();

	bool Quantize(int nBitsPerPixel = 8); // Convert to 8, 4, 1 bits per pixel

	bool Resize(int nWidth, int nHeight, const enum BTFilter& Filter = Bilinear); // Only available for 32 bpp images.
	bool Resize(BTCImageData& DestImage, int nWidth, int nHeight, const enum BTFilter& Filter = Bilinear); // Only available for 32 bpp images.

	bool Crop(RECT& rect);
	bool Crop(int x, int y, int nWidth, int nHeight);
	bool Copy(BTCImageData& SrcImage, RECT& rect);
	bool Copy(BTCImageData& SrcImage, int x, int y, int nWidth, int nHeight);
	bool Fill(int x, int y, int w, int h, BTCOLORREF col);
	bool Fill(RECT& rect, BTCOLORREF col);
	bool Add(BTCImageData& ImageData, int x, int y);
	bool Paste(BTCImageData& ImageData, int x, int y);
	bool Difference(BTCImageData& ImageData, int x, int y);
	bool Multiply(BTCImageData& ImageData, int x, int y);
	bool Blend(BTCImageData& ImageData, int x, int y, int a, BTCOLORREF colProtect = 0x01000000);

	bool AdjustBrightness(int nPercentage);	// -100 ... +100
	bool AdjustContrast(int nPercentage);	//    0 ... +100
	bool AdjustHighlight(int nPercentage);	//    0 ... +100
	bool AdjustMidtone(int nPercentage);	//    0 ... +100
	bool AdjustShadow(int nPercentage);		//    0 ... +100
	bool AdjustGamma(double dRedValue = 1.0, double dGreenValue = 1.0, double dBlueValue = 1.0);
	bool AdjustHue(int nDegrees);			// -180 ... +180
	bool AdjustLightness(int nPercentage);	// -100 ... +100
	bool AdjustSaturation(int nPercentage);	// -100 ... +100
	bool AdjustHLS(int nHueDegrees = 0, int nLightnessPercentage = 0, int nSaturationPercentage = 0);
	bool AdjustRed(int nPercentage);		// -100 ... +100
	bool AdjustGreen(int nPercentage);		// -100 ... +100
	bool AdjustBlue(int nPercentage);		// -100 ... +100
	bool AdjustRGB(int nRedPercentage = 0, int nGreenPercentage = 0, int nBluePercentage = 0);
	bool Blur(); // Only available for 32 bpp images.
	bool Grayscale();
	bool Negate();
	bool Flip();
	bool Mirror();
	bool Rotate90(const enum BTDirection& Direction = Right);

	bool Smooth(int nMaskSize = 3);
	bool Normalize();
	bool Embose();
	bool Edge();
	bool FindEdge(double dFactor = 60.0);	// 0.0 - 99.9%
	bool Sharpen(double dFactor = 86.0);	// 0.0 - 99.9%
	bool Solarize(double dFactor = 0.0);	// 0.0 - 99.9%
	bool Antialias(double dWeight = 1.0 / 3.0, int nSameThreshold = 25, int nDiffThreshold = 25); // Only for 24 and 32BPP
	bool DeInterlace(bool bRetainOdd = true, const enum BTDeInterlaceType& Type = Interpolate);

	bool Convolve(float* pMatrix, int nMatrixSize, bool bAbs, BTCOLORREF colBase = 0x01000000);

	bool FromDC(HDC hdc, int x, int y, int w, int h);
	bool FromHandle(HBITMAP hBitmap);
	bool FromDIB(HANDLE hDib);

	int Compare(BTCImageData* pImageData);

	BTCImageData& operator=(BTCImageData& ImageData);

	bool IsLoaded() const;
	void DeleteObject();

	bool Create(int nWidth, int nHeight, int nBitsPerPixel = 8);

	BTCImageData();
	virtual ~BTCImageData();

public:
	void*			m_pPrivate;		// Pointer to private data.

protected:
	BITMAPINFO*		m_pBitmapInfo;	// Pointer to bitmap info.
    unsigned char*	m_pBits;		// Pointer to bitmap bits.
};

#endif // BTCIMAGEDATA_INCLUDED
