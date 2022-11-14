#include"server.h"
#include"app.h"
#include<stdio.h>



uint8_t appStart(void)
{
	ST_cardData_t user1;
	ST_terminalData_t user2;
	ST_transaction_t user3;
	
	static uint8_t test_cases = 0;

	printf("Test Case: %d\n", test_cases);

	if (getCardHolderName(&user1) == WRONG_NAME)
	{
		printf("WRONG_NAME\n");
		test_cases++;
		return EXIST;
	}
	

	if (getCardExpiryDate(&user1) == WRONG_EXP_DATE)
	{
		printf("WRONG_EXP_DATE\n");
		test_cases++;
		return EXIST;
	}
	
	

	if (getCardPAN(&user1) == WRONG_PAN)
	{
		printf(" WRONG_PAN\n");
		test_cases++;
		return EXIST;
	}
	

	if (getTransactionDate(&user2) == WRONG_DATE)
	{
		printf(" WRONG_DATE\n");
		test_cases++;
		return EXIST;
	}
	

	if (isCardExpired(user1, user2) == EXPIRED_CARD)
	{
		printf(" EXPIRED_CARD\n");
		test_cases++;
		return EXIST;
	}
	

	if (getTransactionAmount(&user2) == INVALID_AMOUNT)
	{
		printf(" INVALID_AMOUNT\n");
		test_cases++;
		return EXIST;
	}
	
	
	if (setMaxAmount(&user2) == INVALID_MAX_AMOUNT)
	{
		printf(" INVALID_MAX_AMOUNT\n");
		test_cases++;
		return EXIST;
	}
	
	
	
	if (isBelowMaxAmount(&user2) == EXCEED_MAX_AMOUNT)
	{
		printf(" EXCEED_MAX_AMOUNT\n");
		test_cases++;
		return EXIST;
	}
	

	user3.cardHolderData = user1;
	user3.terminalData = user2;

	

	 if(recieveTransactionData(&user3) == INTERNAL_SERVER_ERROR)
		 return SERVER_ERROR;

	test_cases++;

	return EXIST;

	



	


}