#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include"server.h"
#include<string.h>

ST_accountsDB_t arr1[255]={3000.0,RUNNING,"22334455667788992",5000.0,BLOCKED,"22334455661188992",4000.0,RUNNING,"22334455660088992"\
,50000.0,BLOCKED,"20334455661188992",8000.0,RUNNING,"22334455660089992" };
ST_transaction_t arr2[255] = { 0 };

uint8_t g_accountIndex = -1;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_transState_t state = APPROVED;
	EN_transState_t state2;
	
	
	if (isValidAccount(&(transData->cardHolderData)) == ACCOUNT_NOT_FOUND)
	{
		state = FRAUD_CARD;
	}

	else if (isBlockedAccount() == BLOCKED_ACCOUNT)
	{
		state = DECLINED_STOLEN_CARD;
	}

	
	else if (isAmountAvailable(&(transData->terminalData)) == LOW_BALANCE)
	{
		state = DECLINED_INSUFFECIENT_FUND;
	}
	
	
	if (state == APPROVED)
		arr1[g_accountIndex].balance -= transData->terminalData.transAmount;

	
	state2 = saveTransaction(transData, state);
	
	
	if (state2 == INTERNAL_SERVER_ERROR)
	{
		printf("\nINTERNAL SERVER ERROR\n");
		return INTERNAL_SERVER_ERROR;

	}
	
	return APPROVED;
	

	
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	uint8_t counter = 0;
	

	for (counter = 0; counter < 255; counter++)
	{
		if (!(strcmp(cardData->primaryAccountNumber ,arr1[counter].primaryAccountNumber)))
		{
			g_accountIndex = counter;
			return SERVER_OK;
		}
	}
	
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(void)
{
	if (arr1[g_accountIndex].state == RUNNING)
	{
		return SERVER_OK;
	}
	else if (arr1[g_accountIndex].state == BLOCKED)
	{
		return BLOCKED_ACCOUNT;
	}

}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	    if (termData->transAmount <= arr1[g_accountIndex].balance)
		{
			
			return SERVER_OK;
		}
		
		else
		{
			
			return LOW_BALANCE;
		}
	
}

EN_serverError_t saveTransaction(ST_transaction_t* transData, EN_transState_t state)
{
	static transSequanceNumber = 252;

	if (transSequanceNumber > 255)
	{
		state = INTERNAL_SERVER_ERROR;
		
	}
	else
	{
		arr2[transSequanceNumber].cardHolderData = transData->cardHolderData;
		arr2[transSequanceNumber].terminalData = transData->terminalData;
		arr2[transSequanceNumber].transState = transData->transState;
		arr2[transSequanceNumber].transactionSequenceNumber = transSequanceNumber;
		

		getTransaction(transSequanceNumber, state);
		transSequanceNumber++;
		
	}
	return state;

}
void getTransaction(uint32_t transactionSequenceNumber, EN_transState_t state)
{
	if (transactionSequenceNumber > 255)
	{
		return TRANSACTION_NOT_FOUND;
	}
	else
	{
		printf("\n#########################\n");
		printf("Transaction Sequence Number:%d\n", transactionSequenceNumber);
		printf("Trnsaction date:            %s\n", arr2[transactionSequenceNumber].terminalData.transactionDate);
		printf("Trnsaction amount:          %f\n", arr2[transactionSequenceNumber].terminalData.transAmount);
		
		if (state == FRAUD_CARD)
			printf("Transaction state :         FRAUD_CARD\n");
		else if (state == DECLINED_STOLEN_CARD)
			printf("Transaction state :         BLOCKED\n");
		else if (state == DECLINED_INSUFFECIENT_FUND)
			printf("Transaction state :         DECLINED_INSUFFECIENT_FUND\n");
		else if (state == INTERNAL_SERVER_ERROR)
			printf("Transaction state :         INTERNAL_SERVER_ERRO\nR");
		else
			printf("Transaction state :         APPROVED\n");

		printf("Terminal mAx amount:        %f\n", arr2[transactionSequenceNumber].terminalData.maxTransAmount);
		printf("Card holder name:           %s\n", arr2[transactionSequenceNumber].cardHolderData.cardHolderName);
		printf("Card primary Account Number:%s\n", arr2[transactionSequenceNumber].cardHolderData.primaryAccountNumber);
		printf("Card current balance:       %f\n", arr1[g_accountIndex].balance);
		printf("Card expiration date:       %s\n", arr2[transactionSequenceNumber].cardHolderData.cardExpirationDate);
		printf("#########################\n");
		
		return SERVER_OK;
	}
}

