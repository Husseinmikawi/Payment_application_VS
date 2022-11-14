#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include"card.h"
#include<stdio.h>

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t charCounter=0;

	printf("PLease enter your name: ");
	scanf("%s", &(cardData->cardHolderName));

	while ((cardData->cardHolderName[charCounter]) != '\0')
	{
		charCounter++;
	 }
	
	if (charCounter < 20)
	{
		return WRONG_NAME;
	}
	else if (charCounter > 24)
	{
		return WRONG_NAME;
	}
	else
	{
		return CARD_OK;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t Counter = 0;
	
	printf("PLease enter your card expiry date: ");
	scanf("%s", &(cardData->cardExpirationDate));
	
	while ((cardData->cardExpirationDate[Counter]) != '\0')
	{
		Counter++;
	}

	if (Counter != 5)
	{
		return WRONG_EXP_DATE;
	}
	// check tens of months not equal one or zero
	else if ((cardData->cardExpirationDate[0] > '1') ||( cardData->cardExpirationDate[0] < '0'))
	{
		return WRONG_EXP_DATE;
	}
	//if tens of months equals one unitsof months must not exceed two
	else if ((cardData->cardExpirationDate[0] == '1') && (cardData->cardExpirationDate[1] > '2'))
	{
		return WRONG_EXP_DATE;
	}
	// check that units of months between 0 and 9 
	else if ((cardData->cardExpirationDate[1] > '9') || (cardData->cardExpirationDate[1] < '0'))
	{
		return WRONG_EXP_DATE;
	}
	
	else if (cardData->cardExpirationDate[2] != '/')
	{
		return WRONG_EXP_DATE;
	}
	else if ((cardData->cardExpirationDate[3] > '9') || (cardData->cardExpirationDate[1] < '0'))
	{
		return WRONG_EXP_DATE;
	}
	else if ((cardData->cardExpirationDate[4] > '9') || (cardData->cardExpirationDate[1] < '0'))
	{
		return WRONG_EXP_DATE;
	}

	return CARD_OK;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t charCounter = 0;
	
	printf("PLease enter your card's Primary Account Number: ");
	scanf("%s", &(cardData->primaryAccountNumber));
	
	while ((cardData->primaryAccountNumber[charCounter]) != '\0')
	{
		charCounter++;
	}
	
	if (charCounter < 16)
	{
		return WRONG_PAN;
	}
	else if (charCounter > 19)
	{
		return WRONG_PAN;
	}
	else
	{
		return CARD_OK;
	}
}