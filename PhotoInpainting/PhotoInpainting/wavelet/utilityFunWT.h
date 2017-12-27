#ifndef _utilityFunWT_H
#define _utilityFunWT_H

#include "stdio.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
//#include <malloc.h>

#define DATA2D(Matrix,m,n,SizeCol) Matrix[(m)*(SizeCol)+(n)]

#define WAVE_DB3 1
#define WAVE_BIOR3_7 2

#define ExtT_ZPD 1
#define ExtT_SYM 2
#define ExtT_PPD 3

#define CONVT_FULL 1
#define CONVT_SAME 2
#define CONVT_VALID 3

#define DIR_ROW 1
#define DIR_COL 2

#define DYAD_EVEN 1
#define DYAD_ODD 2


/* С���任���������ṹ�� */

/* ���������ṹ�� */
typedef struct dbDataPanel2D {
	double * m_pData2D;			// ָ����Ԫ�صĿռ�
	int m_nSizeRow;	// ����
	int m_nSizeCol;	// ����
} DBDataPanel2D;

typedef struct intDataPanel2D {
	int * m_pData2D;
	int m_nSizeRow;
	int m_nSizeCol;
} IntDataPanel2D;

/* С���任��Ϣ�����ṹ�� */
typedef struct wtInfo {
	int m_nWaveType;	// С������
	int m_nExtType;		// ���ط�ʽ
	int m_nWTLevel;		// �任����
	double * m_pC;		// �任�����С��ϵ����[An, Hn, Vn, Dn, H(n-1), V(n-1), D(n-1)..., H1, V1, D1]
	int * m_pS;			// �任���������һ��2*n���飬����n = m_nWTLevel+2��
} WTInfo;

/* С���任��������ṹ�� */
typedef struct WTCoefSet{
	DBDataPanel2D * A_LL;		// ��ͨ����
	DBDataPanel2D * H_LH;		// ˮƽ����
	DBDataPanel2D * V_HL;		// ��ֱ����
	DBDataPanel2D * D_HH;		// �ԽǷ���
} WTCOEFSet;

/* С�������������ṹ�� */
typedef struct waveletBase {
	int nFilterLen;
	double * LO_D;
	double * HI_D;
	double * LO_R;
	double * HI_R;
}WaveletBASE;

/* db3С���˲��� */
double LO_D_db3[6] = {0.0352,   -0.0854,   -0.1350,    0.4599,    0.8069,    0.3327};
double HI_D_db3[6] = {-0.3327,    0.8069,   -0.4599,   -0.1350,    0.0854,    0.0352};
double LO_R_db3[6] = {0.3327,    0.8069,    0.4599,   -0.1350,   -0.0854,    0.0352};
double HI_R_db3[6] = {0.0352,    0.0854,   -0.1350,   -0.4599,    0.8069,   -0.3327};
const WaveletBASE WAVEdb3 = {6, LO_D_db3, HI_D_db3, LO_R_db3, HI_R_db3};

/* bior3.7С���˲��� */
double LO_D_bior3_7[] = {0.0030, -0.0091, -0.0168, 0.0747, 0.0313, -0.3012, -0.0265, 0.9516, 0.9516, -0.0265, -0.3012, 0.0313, 0.0747, -0.0168, -0.0091, 0.0030};
double HI_D_bior3_7[] = {0,  0,  0,  0,  0,  0, -0.1768, 0.5303, -0.5303, 0.1768,  0,  0,  0,  0,  0,  0};
double LO_R_bior3_7[] = {0,  0,  0,  0,  0,  0, 0.1768, 0.5303, 0.5303, 0.1768,  0,  0,  0,  0,  0,  0};
double HI_R_bior3_7[] = {0.0030, 0.0091, -0.0168, -0.0747, 0.0313, 0.3012, -0.0265, -0.9516, 0.9516, 0.0265, -0.3012, -0.0313, 0.0747, 0.0168, -0.0091, -0.0030};
const WaveletBASE WAVEbior3_7 = {16, LO_D_bior3_7, HI_D_bior3_7, LO_R_bior3_7, HI_R_bior3_7};


/* �������� */
double * SerialReverse(double * pSrcSerial, int nSerialLen);


/* �ṹ���ڴ������غ��� */
void DDP_FREE(DBDataPanel2D * pDBDataPanel2D)
{
	if (pDBDataPanel2D != NULL) {
		if (pDBDataPanel2D->m_pData2D != NULL)
			free(pDBDataPanel2D->m_pData2D);
		free(pDBDataPanel2D);
	}
}

void IDP_FREE(IntDataPanel2D * pIntDataPanel2D)
{
	if (pIntDataPanel2D != NULL) {
		if (pIntDataPanel2D->m_pData2D != NULL)
			free(pIntDataPanel2D->m_pData2D);
		free(pIntDataPanel2D);
	}
}

void CS_FREE(WTCOEFSet * pWTCoefSet)
{
	if (pWTCoefSet != NULL) {
		if (pWTCoefSet->A_LL != NULL)
			free(pWTCoefSet->A_LL);
		if (pWTCoefSet->H_LH != NULL)
			free(pWTCoefSet->H_LH);
		if (pWTCoefSet->V_HL != NULL)
			free(pWTCoefSet->V_HL);
		if (pWTCoefSet->D_HH != NULL)
			free(pWTCoefSet->D_HH);
		free(pWTCoefSet);
	}
}

void WB_FREE(WaveletBASE * pWaveletBase)
{
	if (pWaveletBase != NULL) {
		if (pWaveletBase->LO_D != NULL)
			free(pWaveletBase->LO_D);
		if (pWaveletBase->HI_D != NULL)
			free(pWaveletBase->HI_D);
		if (pWaveletBase->LO_R != NULL)
			free(pWaveletBase->LO_R);
		if (pWaveletBase->HI_D != NULL)
			free(pWaveletBase->HI_R);
		free(pWaveletBase);
	}
}

void WI_FREE(WTInfo * pWTInfo)
{
	if (pWTInfo != NULL) {
		if (pWTInfo->m_pC != NULL)
			free(pWTInfo->m_pC);
		if (pWTInfo->m_pS != NULL)
			free(pWTInfo->m_pS);
		free(pWTInfo);
	}
}


/* С���任��غ��� */

WaveletBASE * SetWaveletBase(int nWaveType)
{
	WaveletBASE * pWaveletBase = NULL;

	pWaveletBase = (WaveletBASE *)calloc(1, sizeof(WaveletBASE));
	if (!pWaveletBase)
		exit(1);

	switch (nWaveType) {
	case WAVE_DB3:
		pWaveletBase->nFilterLen = WAVEdb3.nFilterLen;
		pWaveletBase->LO_D = SerialReverse(WAVEdb3.LO_D, WAVEdb3.nFilterLen);
		pWaveletBase->HI_D = SerialReverse(WAVEdb3.HI_D, WAVEdb3.nFilterLen);
		pWaveletBase->LO_R = SerialReverse(WAVEdb3.LO_R, WAVEdb3.nFilterLen);
		pWaveletBase->HI_R = SerialReverse(WAVEdb3.HI_R, WAVEdb3.nFilterLen);
		break;
	case WAVE_BIOR3_7:
		pWaveletBase->nFilterLen = WAVEbior3_7.nFilterLen;
		pWaveletBase->LO_D = SerialReverse(WAVEbior3_7.LO_D, WAVEbior3_7.nFilterLen);
		pWaveletBase->HI_D = SerialReverse(WAVEbior3_7.HI_D, WAVEbior3_7.nFilterLen);
		pWaveletBase->LO_R = SerialReverse(WAVEbior3_7.LO_R, WAVEbior3_7.nFilterLen);
		pWaveletBase->HI_R = SerialReverse(WAVEbior3_7.HI_R, WAVEbior3_7.nFilterLen);
		break;
	default:
		pWaveletBase->nFilterLen = WAVEdb3.nFilterLen;
		pWaveletBase->LO_D = SerialReverse(WAVEdb3.LO_D, WAVEdb3.nFilterLen);
		pWaveletBase->HI_D = SerialReverse(WAVEdb3.HI_D, WAVEdb3.nFilterLen);
		pWaveletBase->LO_R = SerialReverse(WAVEdb3.LO_R, WAVEdb3.nFilterLen);
		pWaveletBase->HI_R = SerialReverse(WAVEdb3.HI_R, WAVEdb3.nFilterLen);
	}
	return pWaveletBase;
}


/* ���� */
DBDataPanel2D * WExtend2D(DBDataPanel2D * pSrcData, int nExtType, int nExtSizeRow, int nExtSizeCol)
{
	int i, j;
	DBDataPanel2D * pResultData = NULL;

	pResultData = (DBDataPanel2D *)calloc(1, sizeof(DBDataPanel2D));
	if (!pResultData)
		exit(1);

	pResultData->m_nSizeRow = pSrcData->m_nSizeRow+nExtSizeRow*2;
	pResultData->m_nSizeCol = pSrcData->m_nSizeCol+nExtSizeCol*2;
	pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
	if (!pResultData->m_pData2D) {
		DDP_FREE(pResultData);
		exit(1);
	}

	for (i = 0; i < pSrcData->m_nSizeRow; i++)
		for (j = 0; j < pSrcData->m_nSizeCol; j++)
			DATA2D(pResultData->m_pData2D, i+nExtSizeRow, j+nExtSizeCol, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i, j, pSrcData->m_nSizeCol);

	switch (nExtType) {
	case ExtT_ZPD:	// ������
		for (i = 0; i < nExtSizeRow; i++)
			for (j = 0; j < nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = 0;
				DATA2D(pResultData->m_pData2D, i, pResultData->m_nSizeCol-j-1, pResultData->m_nSizeCol) = 0;
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-i-1, j, pResultData->m_nSizeCol) = 0;
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-i-1, pResultData->m_nSizeCol-j-1, pResultData->m_nSizeCol) = 0;
			}
		for (i = 0; i < nExtSizeRow; i++)
			for (j = nExtSizeCol; j < pResultData->m_nSizeCol-nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = 0;
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-1-i, j, pResultData->m_nSizeCol) = 0;
			}
		for (i = nExtSizeRow; i < pResultData->m_nSizeRow-nExtSizeRow; i++)
			for (j = 0; j < nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = 0;
				DATA2D(pResultData->m_pData2D, i, pResultData->m_nSizeCol-1-j, pResultData->m_nSizeCol) = 0;
			}
		break;
	case ExtT_SYM:	// �Գ�����
		for (i = 0; i < nExtSizeRow; i++)
			for (j = 0; j < nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, nExtSizeRow-i-1, nExtSizeCol-j-1, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, i, pResultData->m_nSizeCol-j-1, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, nExtSizeRow-i-1, pSrcData->m_nSizeCol-(nExtSizeCol-j-1)-1, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-i-1, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, pSrcData->m_nSizeRow-(nExtSizeRow-i-1)-1, nExtSizeCol-j-1, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-i-1, pResultData->m_nSizeCol-j-1, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, pSrcData->m_nSizeRow-(nExtSizeRow-i-1)-1, pSrcData->m_nSizeCol-(nExtSizeCol-j-1)-1, pSrcData->m_nSizeCol);
			}
		for (i = 0; i < nExtSizeRow; i++)
			for (j = nExtSizeCol; j < pResultData->m_nSizeCol-nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, nExtSizeRow-i-1, j-nExtSizeCol, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-1-i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, pSrcData->m_nSizeRow-(nExtSizeRow-i), j-nExtSizeCol, pSrcData->m_nSizeCol);
			}
		for (i = nExtSizeRow; i < pResultData->m_nSizeRow-nExtSizeRow; i++)
			for (j = 0; j < nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i-nExtSizeRow, nExtSizeCol-j-1, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, i, pResultData->m_nSizeCol-1-j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i-nExtSizeRow, pSrcData->m_nSizeCol-(nExtSizeCol-j), pSrcData->m_nSizeCol);
			}
		break;
	case ExtT_PPD:	// ��������
		for (i = 0; i < nExtSizeRow; i++)
			for (j = 0; j < nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, pSrcData->m_nSizeRow-(nExtSizeRow-i-1)-1, pSrcData->m_nSizeCol-(nExtSizeCol-j-1)-1, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, i, pResultData->m_nSizeCol-j-1, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, pSrcData->m_nSizeRow-(nExtSizeRow-i-1)-1, nExtSizeCol-j-1, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-i-1, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, nExtSizeRow-i-1, pSrcData->m_nSizeCol-(nExtSizeCol-j-1)-1, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-i-1, pResultData->m_nSizeCol-j-1, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, nExtSizeRow-i-1, nExtSizeCol-j-1, pSrcData->m_nSizeCol);
			}
		for (i = 0; i < nExtSizeRow; i++)
			for (j = nExtSizeCol; j < pResultData->m_nSizeCol-nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, pSrcData->m_nSizeRow-(nExtSizeRow-i), j-nExtSizeCol, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-1-i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, nExtSizeRow-i-1, j-nExtSizeCol, pSrcData->m_nSizeCol);
			}
		for (i = nExtSizeRow; i < pResultData->m_nSizeRow-nExtSizeRow; i++)
			for (j = 0; j < nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i-nExtSizeRow, pSrcData->m_nSizeCol-(nExtSizeCol-j), pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, i, pResultData->m_nSizeCol-1-j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i-nExtSizeRow, nExtSizeCol-j-1, pSrcData->m_nSizeCol);
			}
		break;
	default:	// Ĭ�϶Գ�����
		for (i = 0; i < nExtSizeRow; i++)
			for (j = 0; j < nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, nExtSizeRow-i-1, nExtSizeCol-j-1, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, i, pResultData->m_nSizeCol-j-1, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, nExtSizeRow-i-1, pSrcData->m_nSizeCol-(nExtSizeCol-j-1)-1, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-i-1, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, pSrcData->m_nSizeRow-(nExtSizeRow-i-1)-1, nExtSizeCol-j-1, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-i-1, pResultData->m_nSizeCol-j-1, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, pSrcData->m_nSizeRow-(nExtSizeRow-i-1)-1, pSrcData->m_nSizeCol-(nExtSizeCol-j-1)-1, pSrcData->m_nSizeCol);
			}
		for (i = 0; i < nExtSizeRow; i++)
			for (j = nExtSizeCol; j < pResultData->m_nSizeCol-nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, nExtSizeRow-i-1, j-nExtSizeCol, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, pResultData->m_nSizeRow-1-i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, pSrcData->m_nSizeRow-(nExtSizeRow-i), j-nExtSizeCol, pSrcData->m_nSizeCol);
			}
		for (i = nExtSizeRow; i < pResultData->m_nSizeRow-nExtSizeRow; i++)
			for (j = 0; j < nExtSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i-nExtSizeRow, nExtSizeCol-j-1, pSrcData->m_nSizeCol);
				DATA2D(pResultData->m_pData2D, i, pResultData->m_nSizeCol-1-j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i-nExtSizeRow, pSrcData->m_nSizeCol-(nExtSizeCol-j), pSrcData->m_nSizeCol);
			}
	}

	return pResultData;
}


/* ���е�ת */
double * SerialReverse(double * pSrcSerial, int nSerialLen)
{
	int i;
	double * pResult = NULL;

	pResult = (double *) calloc(nSerialLen, sizeof(double));
	if (!pResult)
		exit(1);

	for (i = 0; i < nSerialLen; i++)
		pResult[i] = pSrcSerial[nSerialLen-i-1];
	return pResult;
}

/* һά��� */
DBDataPanel2D * CONV(double * pSerialA, double * pSerialB, int nLengthA, int nLengthB, int nConvType)
{
	int i, j, k;
	int nLengthC;
	int nLenTemp;
	double * pSerialTemp = NULL;
	double * pResultTemp = NULL;
	DBDataPanel2D * pResultData = NULL;

	pResultData = (DBDataPanel2D *)calloc(1, sizeof(DBDataPanel2D));
	if (!pResultData)
		exit(1);

	/* �������������󳤶ȡ���������A�ĳ��� */
	nLengthC = nLengthA+nLengthB-1;
	nLenTemp = nLengthA+nLengthB*2-2;

	pSerialTemp = (double * )calloc(nLenTemp, sizeof(double));
	pResultTemp = (double * )calloc(nLengthC, sizeof(double));
	if (!pResultTemp || !pSerialTemp) {
		if (!pSerialTemp)	free(pSerialTemp);
		if (!pResultTemp)	free(pResultTemp);
		DDP_FREE(pResultData);
		exit(1);
	}

	pResultData->m_nSizeRow = 1;
	if (nConvType == CONVT_SAME) 
		pResultData->m_nSizeCol = nLengthA;
	else
		pResultData->m_nSizeCol = nLengthC;
	pResultData->m_pData2D = (double * )calloc(pResultData->m_nSizeCol, sizeof(double));
	if (!pResultData->m_pData2D) {
		if (!pSerialTemp)	free(pSerialTemp);
		if (!pResultTemp)	free(pResultTemp);
		DDP_FREE(pResultData);
		exit(1);
	}

	/* ��������A������pSerialTemp */
	for (i = 0; i < nLengthB-2; i++) {
		pSerialTemp[i] = 0;
		pSerialTemp[nLenTemp-i-1] = 0;
	}
	for (i = 0; i < nLengthA; i++) {
		pSerialTemp[i+nLengthB-1] = pSerialA[i];
	}
	
	/* ������ */
	for (k = 0; k < nLengthC; k++) {
		pResultTemp[k] = 0;
		for (j = 0; j < nLengthB; j++) {
			pResultTemp[k] += pSerialTemp[j+k]*pSerialB[j];
		}
	}

	switch (nConvType) {
	case CONVT_FULL:
		for (i = 0; i < nLengthC; i++)
			pResultData->m_pData2D[i] = pResultTemp[i];
		break;
	case CONVT_SAME:
		for (i = 0; i < nLengthA; i++)
			pResultData->m_pData2D[i] = pResultTemp[(nLengthC-nLengthA)/2+i];
		break;
	case CONVT_VALID:
		i = 0;
		while (i < nLengthC && pResultTemp[i] == 0)	i++;
		j = 0;
		while (j < nLengthC && pResultTemp[nLengthC-j-1] == 0)	j++;
		pResultData->m_nSizeCol = nLengthC-i-j;
		for (k = 0; k < pResultData->m_nSizeCol; k++)
			pResultData->m_pData2D[k] = pResultTemp[k+i];
		break;
	default:
		for (i = 0; i < nLengthC; i++)
			pResultData->m_pData2D[i] = pResultTemp[i];
	}

	free(pSerialTemp);
	free(pResultTemp);
	return pResultData;
}


/* ��ά��� */
DBDataPanel2D * CONV2D(DBDataPanel2D * pSrcData, double * pFilter, int nFilterLen, int nRowOrCol, int nConvType)
{
	int i, j;
	DBDataPanel2D * pResultData = NULL;
	double * pTempSerialA = NULL, * pTempSerialB = NULL;
	DBDataPanel2D * pTempSerialC = NULL;

	if (!pSrcData || !pFilter)
		exit(1);

	pResultData = (DBDataPanel2D *)calloc(1, sizeof(DBDataPanel2D));
	if (!pResultData)
		exit(1);
	
	if (nConvType == CONVT_FULL && nRowOrCol == DIR_ROW) {
		pTempSerialA = (double *) calloc(pSrcData->m_nSizeCol, sizeof(double));
		pResultData->m_nSizeRow = pSrcData->m_nSizeRow;
		pResultData->m_nSizeCol = pSrcData->m_nSizeCol+nFilterLen-1;
	} else if (nConvType == CONVT_FULL && nRowOrCol == DIR_COL) {
		pTempSerialA = (double *) calloc(pSrcData->m_nSizeRow, sizeof(double));
		pResultData->m_nSizeRow = pSrcData->m_nSizeRow+nFilterLen-1;
		pResultData->m_nSizeCol = pSrcData->m_nSizeCol;
	} else if (nConvType == CONVT_SAME && nRowOrCol == DIR_ROW) {
		pTempSerialA = (double *) calloc(pSrcData->m_nSizeCol, sizeof(double));
		pResultData->m_nSizeRow = pSrcData->m_nSizeRow;
		pResultData->m_nSizeCol = pSrcData->m_nSizeCol;
	} else if (nConvType == CONVT_SAME && nRowOrCol == DIR_COL) {
		pTempSerialA = (double *) calloc(pSrcData->m_nSizeRow, sizeof(double));
		pResultData->m_nSizeRow = pSrcData->m_nSizeRow;
		pResultData->m_nSizeCol = pSrcData->m_nSizeCol;
	}
	pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));	
	if (!pResultData->m_pData2D || !pTempSerialA) {
		DDP_FREE(pResultData);
		exit(1);
	}
	pTempSerialB = pFilter;

	if (nRowOrCol == DIR_ROW) {
		for (i = 0; i < pResultData->m_nSizeRow; i++) {
			for (j = 0; j < pSrcData->m_nSizeCol; j++)
				pTempSerialA[j] = DATA2D(pSrcData->m_pData2D, i, j, pSrcData->m_nSizeCol);
			pTempSerialC = CONV(pTempSerialA, pTempSerialB, pSrcData->m_nSizeCol, nFilterLen, nConvType);
			for (j = 0; j < pResultData->m_nSizeCol; j++)
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = pTempSerialC->m_pData2D[j];
			DDP_FREE(pTempSerialC);
		}
	} else {
		for (j = 0; j < pResultData->m_nSizeCol; j++) {
			for (i = 0; i < pSrcData->m_nSizeRow; i++)
				pTempSerialA[i] = DATA2D(pSrcData->m_pData2D, i, j, pSrcData->m_nSizeCol);
			pTempSerialC = CONV(pTempSerialA, pTempSerialB, pSrcData->m_nSizeRow, nFilterLen, nConvType);
			for (i = 0; i < pResultData->m_nSizeRow; i++)
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = pTempSerialC->m_pData2D[i];
			DDP_FREE(pTempSerialC);
		}
	}

	free(pTempSerialA);
	return pResultData;
}


/* �³��� */
DBDataPanel2D * DYADDOWN(DBDataPanel2D * pSrcData, int nEvenOrOdd, int nRowOrCol)
{
	int i, j;
	DBDataPanel2D * pResultData = NULL;

	pResultData = (DBDataPanel2D *)calloc(1, sizeof(DBDataPanel2D));
	if (!pResultData)
		exit(1);
	
	if (nEvenOrOdd == DYAD_EVEN && nRowOrCol == DIR_ROW) {
		pResultData->m_nSizeRow = pSrcData->m_nSizeRow/2;
		pResultData->m_nSizeCol = pSrcData->m_nSizeCol;
		pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
		if (!pResultData->m_pData2D) {
			DDP_FREE(pResultData);
			exit(1);
		}
		for (i = 0; i < pResultData->m_nSizeRow; i++)
			for (j = 0; j < pResultData->m_nSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i*2+1, j, pSrcData->m_nSizeCol);
			}
	} else if (nEvenOrOdd == DYAD_EVEN && nRowOrCol == DIR_COL) {
		pResultData->m_nSizeRow = pSrcData->m_nSizeRow;
		pResultData->m_nSizeCol = pSrcData->m_nSizeCol/2;
		pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
		if (!pResultData->m_pData2D) {
			DDP_FREE(pResultData);
			exit(1);
		}
		for (i = 0; i < pResultData->m_nSizeRow; i++)
			for (j = 0; j < pResultData->m_nSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i, j*2+1, pSrcData->m_nSizeCol);
			}
	} else if (nEvenOrOdd == DYAD_ODD && nRowOrCol == DIR_ROW) {
		pResultData->m_nSizeRow = (pSrcData->m_nSizeRow+1)/2;
		pResultData->m_nSizeCol = pSrcData->m_nSizeCol;
		pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
		if (!pResultData->m_pData2D) {
			DDP_FREE(pResultData);
			exit(1);
		}
		for (i = 0; i < pResultData->m_nSizeRow; i++)
			for (j = 0; j < pResultData->m_nSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i*2, j, pSrcData->m_nSizeCol);
			}
	} else if (nEvenOrOdd == DYAD_ODD && nRowOrCol == DIR_COL) {
		pResultData->m_nSizeRow = pSrcData->m_nSizeRow;
		pResultData->m_nSizeCol = (pSrcData->m_nSizeCol+1)/2;
		pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
		if (!pResultData->m_pData2D) {
			DDP_FREE(pResultData);
			exit(1);
		}
		for (i = 0; i < pResultData->m_nSizeRow; i++)
			for (j = 0; j < pResultData->m_nSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i, j*2, pSrcData->m_nSizeCol);
			}
	}
	return pResultData;
}


/* ��ֵ */
DBDataPanel2D * DYADUP(DBDataPanel2D * pSrcData, int nEvenOrOdd, int nRowOrCol)
{
	int i, j;
	DBDataPanel2D * pResultData = NULL;

	pResultData = (DBDataPanel2D *)calloc(1, sizeof(DBDataPanel2D));
	if (!pResultData)
		exit(1);
	
	if (nEvenOrOdd == DYAD_EVEN && nRowOrCol == DIR_ROW) {
		pResultData->m_nSizeRow = pSrcData->m_nSizeRow*2;
		pResultData->m_nSizeCol = pSrcData->m_nSizeCol;
		pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
		if (!pResultData->m_pData2D) {
			DDP_FREE(pResultData);
			exit(1);
		}
		for (i = 0; i < pResultData->m_nSizeRow; i++)
			for (j = 0; j < pResultData->m_nSizeCol; j++) {
				if (i%2 == 0)
					DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i/2, j, pSrcData->m_nSizeCol);
				else
					DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = 0;
			}
	} else if (nEvenOrOdd == DYAD_EVEN && nRowOrCol == DIR_COL) {
		pResultData->m_nSizeRow = pSrcData->m_nSizeRow;
		pResultData->m_nSizeCol = pSrcData->m_nSizeCol*2;
		pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
		if (!pResultData->m_pData2D) {
			DDP_FREE(pResultData);
			exit(1);
		}
		for (i = 0; i < pResultData->m_nSizeRow; i++)
			for (j = 0; j < pResultData->m_nSizeCol; j++) {
				if (j%2 == 0)
					DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i, j/2, pSrcData->m_nSizeCol);
				else
					DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = 0;
			}
	} else if (nEvenOrOdd == DYAD_ODD && nRowOrCol == DIR_ROW) {
		pResultData->m_nSizeRow = pSrcData->m_nSizeRow*2;
		pResultData->m_nSizeCol = pSrcData->m_nSizeCol;
		pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
		if (!pResultData->m_pData2D) {
			DDP_FREE(pResultData);
			exit(1);
		}
		for (i = 0; i < pResultData->m_nSizeRow; i++)
			for (j = 0; j < pResultData->m_nSizeCol; j++) {
				if (i%2 != 0)
					DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i/2, j, pSrcData->m_nSizeCol);
				else
					DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = 0;
			}
	} else if (nEvenOrOdd == DYAD_ODD && nRowOrCol == DIR_COL) {
		pResultData->m_nSizeRow = pSrcData->m_nSizeRow;
		pResultData->m_nSizeCol = pSrcData->m_nSizeCol*2;
		pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
		if (!pResultData->m_pData2D) {
			DDP_FREE(pResultData);
			exit(1);
		}
		for (i = 0; i < pResultData->m_nSizeRow; i++)
			for (j = 0; j < pResultData->m_nSizeCol; j++) {
				if (j%2 != 0)
					DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, i, j/2, pSrcData->m_nSizeCol);
				else
					DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = 0;
			}
	}
	return pResultData;
}


/* �����ض��������� */
DBDataPanel2D * ReShape(DBDataPanel2D * pSrcData, int nNewSizeRow, int nNewSizeCol)
{
	int i, j, k;
	DBDataPanel2D * pResultData = NULL;
	
	if (nNewSizeRow*nNewSizeCol != (pSrcData->m_nSizeRow)*(pSrcData->m_nSizeCol))
		exit(1);

	pResultData = (DBDataPanel2D *)calloc(1, sizeof(DBDataPanel2D));
	if (!pResultData)
		exit(1);

	pResultData->m_nSizeRow = nNewSizeRow;
	pResultData->m_nSizeCol = nNewSizeCol;
	pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
	if (!pResultData->m_pData2D) {
		DDP_FREE(pResultData);
		exit(1);
	}
	
	k = 0;
	for (i = 0; i < pResultData->m_nSizeRow; i++)
		for (j = 0; j < pResultData->m_nSizeCol; j++) {
			DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = pSrcData->m_pData2D[k];
			k++;
		}

	return pResultData;
}


/* ��ȡ�Ӿ��� */
DBDataPanel2D * GetSubMatrix(DBDataPanel2D * pSrcData, int nSubSizeRow, int nSubSizeCol)
{
	int i, j;
	int nOffsetRow, nOffsetCol;
	DBDataPanel2D * pResultData = NULL;

	if (!(nSubSizeRow <= pSrcData->m_nSizeRow && nSubSizeCol <= pSrcData->m_nSizeCol))
		exit(1);

	pResultData = (DBDataPanel2D *)calloc(1, sizeof(DBDataPanel2D));
	if (!pResultData)
		exit(1);

	pResultData->m_nSizeRow = nSubSizeRow;
	pResultData->m_nSizeCol = nSubSizeCol;
	pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
	if (!pResultData->m_pData2D) {
		DDP_FREE(pResultData);
		exit(1);
	}
	
	nOffsetRow = (pSrcData->m_nSizeRow-nSubSizeRow)/2;
	nOffsetCol = (pSrcData->m_nSizeCol-nSubSizeCol)/2;
	for (i = 0; i < pResultData->m_nSizeRow; i++)
		for (j = 0; j < pResultData->m_nSizeCol; j++) {
			DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcData->m_pData2D, nOffsetRow+i, nOffsetCol+j, pSrcData->m_nSizeCol);
		}

	return pResultData;
}


/* �������� */
DBDataPanel2D * CopyMatrix(DBDataPanel2D * pSrcMatrix)
{
	return(GetSubMatrix(pSrcMatrix, pSrcMatrix->m_nSizeRow, pSrcMatrix->m_nSizeCol));
}


/* ƴ�Ӿ��� */
DBDataPanel2D * SpliceMatrix(DBDataPanel2D * pSrcMatrixA, DBDataPanel2D * pSrcMatrixB, int nRowOrCol)
{
	int i, j;
	DBDataPanel2D * pResultData = NULL;
	
	if (!pSrcMatrixA || !pSrcMatrixB)
		exit(1);

	pResultData = (DBDataPanel2D *)calloc(1, sizeof(DBDataPanel2D));
	if (!pResultData)
		exit(1);

	if (nRowOrCol == DIR_ROW) {
		if (pSrcMatrixA->m_nSizeRow != pSrcMatrixB->m_nSizeRow) {
			DDP_FREE(pResultData);
			exit(1);
		}

		pResultData->m_nSizeRow = pSrcMatrixA->m_nSizeRow;
		pResultData->m_nSizeCol = pSrcMatrixA->m_nSizeCol+pSrcMatrixB->m_nSizeCol;
		pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
		if (!pResultData->m_pData2D) {
			DDP_FREE(pResultData);
			exit(1);
		}
	
		for (i = 0; i < pResultData->m_nSizeRow; i++)
			for (j = 0; j < pSrcMatrixA->m_nSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcMatrixA->m_pData2D, i, j, pSrcMatrixA->m_nSizeCol);
			}
		for (i = 0; i < pResultData->m_nSizeRow; i++)
			for (j = 0; j < pSrcMatrixB->m_nSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j+pSrcMatrixA->m_nSizeCol, pResultData->m_nSizeCol) = DATA2D(pSrcMatrixB->m_pData2D, i, j, pSrcMatrixB->m_nSizeCol);
			}

	} else {
		if (pSrcMatrixA->m_nSizeCol != pSrcMatrixB->m_nSizeCol) {
			DDP_FREE(pResultData);
			exit(1);
		}

		pResultData->m_nSizeRow = pSrcMatrixA->m_nSizeRow+pSrcMatrixB->m_nSizeRow;
		pResultData->m_nSizeCol = pSrcMatrixA->m_nSizeCol;
		pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
		if (!pResultData->m_pData2D) {
			DDP_FREE(pResultData);
			exit(1);
		}
	
		for (i = 0; i < pSrcMatrixA->m_nSizeRow; i++)
			for (j = 0; j < pResultData->m_nSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = DATA2D(pSrcMatrixA->m_pData2D, i, j, pSrcMatrixA->m_nSizeCol);
			}
		for (i = 0; i < pSrcMatrixB->m_nSizeRow; i++)
			for (j = 0; j < pResultData->m_nSizeCol; j++) {
				DATA2D(pResultData->m_pData2D, i+pSrcMatrixA->m_nSizeRow, j, pResultData->m_nSizeCol) = DATA2D(pSrcMatrixB->m_pData2D, i, j, pSrcMatrixB->m_nSizeCol);
			}
	}

	return pResultData;
}


/* ������� */
DBDataPanel2D * SumMatrix(DBDataPanel2D * pSrcMatrixA, DBDataPanel2D * pSrcMatrixB)
{
	int i, j;
	DBDataPanel2D *pResultData = NULL;
	
	if (!pSrcMatrixA || !pSrcMatrixB)
		exit(1);

	if ((pSrcMatrixA->m_nSizeRow != pSrcMatrixB->m_nSizeRow) ||
		(pSrcMatrixA->m_nSizeCol != pSrcMatrixB->m_nSizeCol))
		exit(1);

	pResultData = (DBDataPanel2D *)calloc(1, sizeof(DBDataPanel2D));
	if (!pResultData)
		exit(1);

	pResultData->m_nSizeRow = pSrcMatrixA->m_nSizeRow;
	pResultData->m_nSizeCol = pSrcMatrixA->m_nSizeCol;
	
	pResultData->m_pData2D = (double *) calloc(pResultData->m_nSizeRow*pResultData->m_nSizeCol, sizeof(double));
	if (!pResultData->m_pData2D) {
		DDP_FREE(pResultData);
		exit(1);
	}
	
	for (i = 0; i < pResultData->m_nSizeRow; i++)
		for (j = 0; j < pResultData->m_nSizeCol; j++) {
			DATA2D(pResultData->m_pData2D, i, j, pResultData->m_nSizeCol) = 
				DATA2D(pSrcMatrixA->m_pData2D, i, j, pSrcMatrixA->m_nSizeCol)
				+DATA2D(pSrcMatrixB->m_pData2D, i, j, pSrcMatrixB->m_nSizeCol);
		}

	return pResultData;
}

#endif
