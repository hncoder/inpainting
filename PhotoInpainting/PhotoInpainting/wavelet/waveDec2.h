#include "utilityFunWT.h"
//#include "malloc.h"
#include <stdlib.h>

WTCOEFSet * SubWaveDec2(DBDataPanel2D * pSrcData, WaveletBASE * pWaveBase, int nExtType);

WTInfo * waveDec2(DBDataPanel2D * pSrcData, int nWTLevel, int nWaveType, int nExtType)
{
	int i, j, k;
	int nCoefLen;
	WTInfo * pDecResult = NULL;

	DBDataPanel2D pTempCoefPanel;
	WTCOEFSet * * pWTCoefSet = NULL;
	WaveletBASE * pWaveletBase = NULL;

	/* Ԥ����Ž���Ľṹ�� */
	if (!(pDecResult = (WTInfo *)calloc(1, sizeof(WTInfo))))
		exit(1);
	pDecResult->m_nExtType = nExtType;
	pDecResult->m_nWaveType = nWaveType;
	pDecResult->m_nWTLevel = nWTLevel;
	pDecResult->m_pC = NULL;
	pDecResult->m_pS = NULL;

	/* ����ռ䣬���ڴ��ָ��С��ϵ����ָ�� */
	pWTCoefSet = (WTCOEFSet * *)calloc(nWTLevel, sizeof(WTCOEFSet *));
	if (!pWTCoefSet) {
		WI_FREE(pDecResult);
		exit(1);
	}

	/* ����nWaveType��ȡС�������˲���ϵ����Ϊ�˽�Ͼ�����㣬���ȶԸ�ϵ�����˵��� */
	if (!(pWaveletBase = SetWaveletBase(nWaveType))) {
		WI_FREE(pDecResult);
		exit(1);
	}


	pTempCoefPanel.m_nSizeRow = pSrcData->m_nSizeRow;
	pTempCoefPanel.m_nSizeCol = pSrcData->m_nSizeCol;
	pTempCoefPanel.m_pData2D = pSrcData->m_pData2D;
	for (i = 0; i < nWTLevel; i++) {
		pWTCoefSet[i] = SubWaveDec2(&pTempCoefPanel, pWaveletBase, nExtType);
		pTempCoefPanel.m_nSizeRow = pWTCoefSet[i]->A_LL->m_nSizeRow;
		pTempCoefPanel.m_nSizeCol = pWTCoefSet[i]->A_LL->m_nSizeCol;
		pTempCoefPanel.m_pData2D = pWTCoefSet[i]->A_LL->m_pData2D;
	}

	/* ͳ��С��ϵ�����ܳ��� */
	nCoefLen = 0;
	for (i = 0; i < nWTLevel; i++) {
		nCoefLen += pWTCoefSet[i]->H_LH->m_nSizeRow*pWTCoefSet[i]->H_LH->m_nSizeCol;
		nCoefLen += pWTCoefSet[i]->V_HL->m_nSizeRow*pWTCoefSet[i]->V_HL->m_nSizeCol;
		nCoefLen += pWTCoefSet[i]->D_HH->m_nSizeRow*pWTCoefSet[i]->D_HH->m_nSizeCol;
		if (i == nWTLevel-1)
			nCoefLen += pWTCoefSet[i]->A_LL->m_nSizeRow*pWTCoefSet[i]->A_LL->m_nSizeCol;
	}

	/* �ռ�С���ֽ�ϵ�� */
	pDecResult->m_pC = (double *)calloc(nCoefLen, sizeof(double));
	pDecResult->m_pS = (int *)calloc((nWTLevel+2)*2, sizeof(int));
	if (pDecResult->m_pC == NULL || pDecResult->m_pS == NULL) {
		WB_FREE(pWaveletBase);
		WI_FREE(pDecResult);
		exit(1);
	}

	/* ��¼��n���ĵ�Ƶ�����Լ���������ˮƽ����ֱ���ԽǷ��� */
	k = 0;
	for (i = nWTLevel-1; i >= 0; i--) {
		if (i == nWTLevel-1) {
			for (j = 0; j < pWTCoefSet[i]->A_LL->m_nSizeRow*pWTCoefSet[i]->A_LL->m_nSizeCol; j++) {
				pDecResult->m_pC[k] = pWTCoefSet[i]->A_LL->m_pData2D[j];
				k++;
			}
			DATA2D(pDecResult->m_pS, 0, 0, 2) = pWTCoefSet[nWTLevel-1]->A_LL->m_nSizeRow;
			DATA2D(pDecResult->m_pS, 0, 1, 2) = pWTCoefSet[nWTLevel-1]->A_LL->m_nSizeCol;
		}
		for (j = 0; j < pWTCoefSet[i]->H_LH->m_nSizeRow*pWTCoefSet[i]->H_LH->m_nSizeCol; j++) {
			pDecResult->m_pC[k] = pWTCoefSet[i]->H_LH->m_pData2D[j];
			k++;
		}
		for (j = 0; j < pWTCoefSet[i]->V_HL->m_nSizeRow*pWTCoefSet[i]->V_HL->m_nSizeCol; j++) {
			pDecResult->m_pC[k] = pWTCoefSet[i]->V_HL->m_pData2D[j];
			k++;
		}
		for (j = 0; j < pWTCoefSet[i]->D_HH->m_nSizeRow*pWTCoefSet[i]->D_HH->m_nSizeCol; j++) {
			pDecResult->m_pC[k] = pWTCoefSet[i]->D_HH->m_pData2D[j];
			k++;
		}
		DATA2D(pDecResult->m_pS, nWTLevel-i, 0, 2) = pWTCoefSet[i]->A_LL->m_nSizeRow;
		DATA2D(pDecResult->m_pS, nWTLevel-i, 1, 2) = pWTCoefSet[i]->A_LL->m_nSizeCol;
	}

	DATA2D(pDecResult->m_pS, nWTLevel+1, 0, 2) = pSrcData->m_nSizeRow;
	DATA2D(pDecResult->m_pS, nWTLevel+1, 1, 2) = pSrcData->m_nSizeCol;

	WB_FREE(pWaveletBase);
	return pDecResult;
}


WTCOEFSet * SubWaveDec2(DBDataPanel2D * pSrcData, WaveletBASE * pWaveBase, int nExtType)
{
	WTCOEFSet * pWTResult = NULL;
	DBDataPanel2D * pTempDataA_LL = NULL, * pTempDataH_LH = NULL, * pTempDataV_HL = NULL, * pTempDataD_HH = NULL;
	DBDataPanel2D * pTempDataA_LL2 = NULL, * pTempDataH_LH2 = NULL, * pTempDataV_HL2 = NULL, * pTempDataD_HH2 = NULL;
	DBDataPanel2D * pTempDataExt = NULL, * pTempDataA_H = NULL, * pTempDataV_D = NULL;
	DBDataPanel2D * pTempDataA_H2 = NULL, * pTempDataV_D2 = NULL;

	if (!(pWTResult = (WTCOEFSet*)calloc(1, sizeof(WTCOEFSet))))
		exit(1);

	/* ����nExtType��ԭʼ���ݽ������� */
	pTempDataExt = WExtend2D(pSrcData, nExtType, pWaveBase->nFilterLen-1, pWaveBase->nFilterLen-1);

	/* �з�������ͨ�˲� �в��� */
	pTempDataA_H = CONV2D(pTempDataExt, pWaveBase->LO_D, pWaveBase->nFilterLen, DIR_ROW, CONVT_FULL);
	pTempDataA_H2 = DYADDOWN(pTempDataA_H, DYAD_EVEN, DIR_COL);
	DDP_FREE(pTempDataA_H);

	/* �з�������ͨ/��ͨ�˲����в������õ���Ƶ������ˮƽ���� */
	pTempDataA_LL = CONV2D(pTempDataA_H2, pWaveBase->LO_D, pWaveBase->nFilterLen, DIR_COL, CONVT_FULL);
	pTempDataA_LL2 = DYADDOWN(pTempDataA_LL, DYAD_EVEN, DIR_ROW);
	DDP_FREE(pTempDataA_LL);

	pTempDataH_LH = CONV2D(pTempDataA_H2, pWaveBase->HI_D, pWaveBase->nFilterLen, DIR_COL, CONVT_FULL);
	pTempDataH_LH2 = DYADDOWN(pTempDataH_LH, DYAD_EVEN, DIR_ROW);
	DDP_FREE(pTempDataH_LH);

	/* �з�������ͨ�˲� �в��� */
	pTempDataV_D = CONV2D(pTempDataExt, pWaveBase->HI_D, pWaveBase->nFilterLen, DIR_ROW, CONVT_FULL);
	pTempDataV_D2 = DYADDOWN(pTempDataV_D, DYAD_EVEN, DIR_COL);
	DDP_FREE(pTempDataV_D);

	/* �з�������ͨ/��ͨ�˲����в������õ���ֱ�����ͶԽǷ��� */
	pTempDataV_HL = CONV2D(pTempDataV_D2, pWaveBase->LO_D, pWaveBase->nFilterLen, DIR_COL, CONVT_FULL);
	pTempDataV_HL2 = DYADDOWN(pTempDataV_HL, DYAD_EVEN, DIR_ROW);
	DDP_FREE(pTempDataV_HL);

	pTempDataD_HH = CONV2D(pTempDataV_D2, pWaveBase->HI_D, pWaveBase->nFilterLen, DIR_COL, CONVT_FULL);
	pTempDataD_HH2 = DYADDOWN(pTempDataD_HH, DYAD_EVEN, DIR_ROW);
	DDP_FREE(pTempDataD_HH);

	pWTResult->A_LL = pTempDataA_LL2;
	pWTResult->H_LH = pTempDataH_LH2;
	pWTResult->V_HL = pTempDataV_HL2;
	pWTResult->D_HH = pTempDataD_HH2;

	DDP_FREE(pTempDataExt);	DDP_FREE(pTempDataA_H2);	DDP_FREE(pTempDataV_D2);
	return pWTResult;
}


WTInfo * waveDec2Int(IntDataPanel2D * pSrcData, int nWTLevel, int nWaveType, int nExtType)
{
	int i, j;
	DBDataPanel2D * pTempSrcData = NULL;
	WTInfo * pWTResult = NULL;

	if (!pSrcData)
		exit(1);

	if (!(pTempSrcData = (DBDataPanel2D *)calloc(1, sizeof(DBDataPanel2D))))
		exit(1);

	pTempSrcData->m_nSizeRow = pSrcData->m_nSizeRow;
	pTempSrcData->m_nSizeCol = pSrcData->m_nSizeCol;
	pTempSrcData->m_pData2D = (double *) calloc(pTempSrcData->m_nSizeRow*pTempSrcData->m_nSizeCol, sizeof(double));
	if (!pTempSrcData->m_pData2D) {
		DDP_FREE(pTempSrcData);
		exit(1);
	}

	for (i = 0; i < pTempSrcData->m_nSizeRow; i++)
		for (j = 0; j < pTempSrcData->m_nSizeCol; j++)
			DATA2D(pTempSrcData->m_pData2D, i, j, pTempSrcData->m_nSizeCol) = (double)DATA2D(pSrcData->m_pData2D, i, j, pSrcData->m_nSizeCol);

	pWTResult = waveDec2(pTempSrcData, nWTLevel, nWaveType, nExtType);

	DDP_FREE(pTempSrcData);
	return pWTResult;
}
