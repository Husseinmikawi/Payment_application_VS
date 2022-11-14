#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include"terminal.h"
#include<stdio.h>

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint8_t Counter = 0;

	printf("PLease enter your card transction date: ");
	scanf("%s", &(termData->transactionDate));

	while ((termData->transactionDate[Counter]) != '\0')
	{
		Counter++;
	}
	
	if (Counter != 10)
	{
		return WRONG_DATE;
	}

	if ((termData->transactionDate[0] > '3') || (termData->transactionDate[0] < '0'))
	{
		return WRONG_DATE;
	}
	else if (termData->transactionDate[0] == '3')
	{
		if (termData->transactionDate[1] > '1')
			return WRONG_DATE;
	}

	if((termData->transactionDate[1] > '9') || (termData->transactionDate[1] < '0'))
	{
		return WRONG_DATE;
	}

	if(termData->transactionDate[2] != '/')
	{
		return WRONG_DATE;
	}

	if ((termData->transactionDate[3] > '1') || (termData->transactionDate[3] < '0'))
	{
		return WRONG_DATE;
	}
	else if((termData->transactionDate[3] == '1') && (termData->transactionDate[4] > '2'))
	{
		return WRONG_DATE;
	}

	if ((termData->transactionDate[4] > '9') || (termData->transactionDate[4] < '0'))
	{
		return WRONG_DATE;
	}

	if (termData->transactionDate[5] != '/')
	{
		return WRONG_DATE;
	}

	if (termData->transactionDate[6] != '2')
	{
		return WRONG_DATE;
	}

	if ((termData->transactionDate[7] > '9') || (termData->transactionDate[7] < '0'))
	{
		return WRONG_DATE;
	}

	if ((termData->transactionDate[8] > '9') || (termData->transactionDate[8] < '0'))
	{
		return WRONG_DATE;
	}

	if ((termData->transactionDate[9] > '9') || (termData->transactionDate[9] < '0'))
	{
		return WRONG_DATE;
	}


	return TERMINAL_OK;
}                     

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	// check tens of years
	if (cardData.cardExpirationDate[3] > termData.transactionDate[8])
		return TERMINAL_OK;
	else if (cardData.cardExpirationDate[3] == termData.transactionDate[8])
	{		//check units of years
		if (cardData.cardExpirationDate[4] > termData.transactionDate[9])
			return TERMINAL_OK;
		else if (cardData.cardExpirationDate[4] == termData.transactionDate[9])
		{		//check tens of months
			if (cardData.cardExpirationDate[0] > termData.transactionDate[3])
				return TERMINAL_OK;
			else if (cardData.cardExpirationDate[0] == termData.transactionDate[3])
			{		//check uints of months
				if (cardData.cardExpirationDate[1] > termData.transactionDate[4])
					return TERMINAL_OK;
				else
					return EXPIRED_CARD;
			}
			else
				return EXPIRED_CARD;
		}
		else
			return EXPIRED_CARD;
	}
	else
		return EXPIRED_CARD;
	
	
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	printf("PLease enter your transaction amount: ");
	scanf("%f", &(termData->transAmount));
	if ((termData->transAmount) <= 0)
		return INVALID_AMOUNT;
	else
		return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if ((termData->transAmount) > (termData->maxTransAmount))
		return EXCEED_MAX_AMOUNT;
	else
		return TERMINAL_OK;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	printf("set the maximum allowed amount: ");
	scanf("%f", &(termData->maxTransAmount));
	if ((termData->maxTransAmount) <= 0)
		return INVALID_MAX_AMOUNT;
	else
		return TERMINAL_OK;
}

