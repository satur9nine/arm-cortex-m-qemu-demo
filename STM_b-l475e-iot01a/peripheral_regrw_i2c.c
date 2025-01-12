#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"

//
// STM HAL drivers appear to be intended for controllers (master) rather than peripherals (slave)
// This files introduces functions and callbacks that it make possible for an STM microcontroller
// to operate as a peripheral, see HAL_I2C_Slave_ByteProtocol_Poller below.
//


/* Below ST driver functions were private (static) but must be modified to be public */

HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status,
                                                    uint32_t Timeout, uint32_t Tickstart);
HAL_StatusTypeDef I2C_WaitOnRXNEFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout,
                                                        uint32_t Tickstart);
HAL_StatusTypeDef I2C_WaitOnTXISFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout,
                                                        uint32_t Tickstart);
HAL_StatusTypeDef I2C_WaitOnSTOPFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout,
                                                        uint32_t Tickstart);
HAL_StatusTypeDef I2C_IsErrorOccurred(I2C_HandleTypeDef *hi2c, uint32_t Timeout,
                                             uint32_t Tickstart);
void I2C_Flush_TXDR(I2C_HandleTypeDef *hi2c);

__weak void Error_Handler(void)
{
  while (1);
}

/* Callback functions must be implemented elsewhere */

__weak uint8_t HAL_I2C_RegGetByte_Callback(I2C_HandleTypeDef *hi2c, uint8_t RegAddr)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2c);
  UNUSED(RegAddr);

  /* Shouldn't be used in practice */
  return 0x77;
}

__weak void HAL_I2C_RegSendByte_Callback(I2C_HandleTypeDef *hi2c, uint8_t RegAddr, uint8_t RegValue)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(hi2c);
  UNUSED(RegAddr);
  UNUSED(RegValue);
}

/*
 * Special function that waits until the i2c module indicates a read occurred or address match was
 * received.
 */
static HAL_StatusTypeDef I2C_WaitOnReadOrAddrUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Timeout,
                                                        uint32_t Tickstart, uint32_t *Result)
{
  int no_read = 1;
  int no_addr = 1;

  /* Enable Address Acknowledge */
  hi2c->Instance->CR2 &= ~I2C_CR2_NACK;

  do
  {
    /* Check if an error is detected */
    if (I2C_IsErrorOccurred(hi2c, Timeout, Tickstart) != HAL_OK)
    {
      return HAL_ERROR;
    }

    /* Check if a STOPF is detected */
    if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_STOPF) == SET)
    {
      /* Check if an RXNE is pending */
      /* Store Last receive data if any */
      if ((__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_RXNE) == SET) && (hi2c->XferSize > 0U))
      {
        /* Inform caller a read has occurred */
        Result[0] |= I2C_FLAG_RXNE;
        /* Return HAL_OK */
        /* The Reading of data from RXDR will be done in caller function */
        return HAL_OK;
      }
      else
      {
        if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_AF) == SET)
        {
          __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
          hi2c->ErrorCode = HAL_I2C_ERROR_AF;
        }
        else
        {
          hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
        }

        /* Clear STOP Flag */
        __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_STOPF);

        /* Clear Configuration Register 2 */
        I2C_RESET_CR2(hi2c);

        hi2c->State = HAL_I2C_STATE_READY;
        hi2c->Mode = HAL_I2C_MODE_NONE;

        /* Process Unlocked */
        __HAL_UNLOCK(hi2c);

        return HAL_ERROR;
      }
    }

    /* Check for the Timeout */
    if (((HAL_GetTick() - Tickstart) > Timeout) || (Timeout == 0U))
    {
      hi2c->ErrorCode |= HAL_I2C_ERROR_TIMEOUT;
      hi2c->State = HAL_I2C_STATE_READY;

      /* Process Unlocked */
      __HAL_UNLOCK(hi2c);

      return HAL_ERROR;
    }

    /* Check for read and addr */
    no_read = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_RXNE) == RESET;
    no_addr = __HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_ADDR) == RESET;
  } while (no_read && no_addr);

  if (!no_read) {
    /* Inform caller a read has occurred */
    Result[0] |= I2C_FLAG_RXNE;
  }

  if (!no_addr) {
    /* Inform caller an address command has occurred */
    Result[0] |= I2C_FLAG_ADDR;
  }

  return HAL_OK;
}

/*
 * Reads a single byte in slave mode.
 */
static HAL_StatusTypeDef I2C_Slave_Raw_Read_Byte(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Timeout, uint32_t Tickstart)
{
  hi2c->State     = HAL_I2C_STATE_BUSY_RX;
  hi2c->Mode      = HAL_I2C_MODE_SLAVE;
  hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

  /* Prepare transfer parameters */
  hi2c->pBuffPtr  = pData;
  hi2c->XferCount = 1;
  hi2c->XferSize = hi2c->XferCount;
  hi2c->XferISR   = NULL;

  while (hi2c->XferCount > 0U)
  {
    /* Wait until RXNE flag is set */
    if (I2C_WaitOnRXNEFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
    {
      /* Disable Address Acknowledge */
      hi2c->Instance->CR2 |= I2C_CR2_NACK;

      /* Store Last receive data if any */
      if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_RXNE) == SET)
      {
        /* Read data from RXDR */
        *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->RXDR;

        /* Increment Buffer pointer */
        hi2c->pBuffPtr++;

        hi2c->XferCount--;
        hi2c->XferSize--;
      }

      return HAL_ERROR;
    }

    /* Read data from RXDR */
    *hi2c->pBuffPtr = (uint8_t)hi2c->Instance->RXDR;

    /* Increment Buffer pointer */
    hi2c->pBuffPtr++;

    hi2c->XferCount--;
    hi2c->XferSize--;
  }

  return HAL_OK;
}

/*
 * Performs a single byte write in slave mode.
 */
static HAL_StatusTypeDef I2C_Slave_Raw_Write_Byte(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint32_t Timeout, uint32_t Tickstart)
{

  hi2c->State     = HAL_I2C_STATE_BUSY_TX;
  hi2c->Mode      = HAL_I2C_MODE_SLAVE;
  hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

  /* Prepare transfer parameters */
  hi2c->pBuffPtr  = pData;
  hi2c->XferCount = 1;
  hi2c->XferISR   = NULL;

  /* Wait until DIR flag is set Transmitter mode */
  if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_DIR, RESET, Timeout, Tickstart) != HAL_OK)
  {
    /* Disable Address Acknowledge */
    hi2c->Instance->CR2 |= I2C_CR2_NACK;
    return HAL_ERROR;
  }

  while (hi2c->XferCount > 0U)
  {
    /* Wait until TXIS flag is set */
    if (I2C_WaitOnTXISFlagUntilTimeout(hi2c, Timeout, Tickstart) != HAL_OK)
    {
      /* Disable Address Acknowledge */
      hi2c->Instance->CR2 |= I2C_CR2_NACK;
      return HAL_ERROR;
    }

    /* Write data to TXDR */
    hi2c->Instance->TXDR = *hi2c->pBuffPtr;

    /* Increment Buffer pointer */
    hi2c->pBuffPtr++;

    hi2c->XferCount--;
  }

  /* Wait until AF flag is set */
  if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_AF, RESET, Timeout, Tickstart) != HAL_OK)
  {
    /* Disable Address Acknowledge */
    hi2c->Instance->CR2 |= I2C_CR2_NACK;
    return HAL_ERROR;
  }

  /* Flush TX register */
  I2C_Flush_TXDR(hi2c);

  /* Clear AF flag */
  __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);

  return HAL_OK;
}

#define DEFAULT_I2C_TIMEOUT (100U)

/**
 * Perform a single byte slave read or write at a particular address via I2C.
 *
 * A good overview of these fairly standard read and write operations can be found in the TI
 * document SLVA704 "Understanding the I2C Bus", specifically section 3.1 and 3.2. Also see
 * NXP document UM10204 which describes the protocol to read memory from a slave address in a
 * operation as the "combined format".
 *
 * Oddly ST drivers don't offer a function that implements this particular address-based byte
 * I2C protocol, probably because they are assuming the STM MCU is always the master.
 *
 * This function is intended to be the only I2C function invoked by the main program and called
 * in a loop.
 */
HAL_StatusTypeDef HAL_I2C_Slave_ByteProtocol_Poller(I2C_HandleTypeDef *hi2c)
{
  uint32_t Timeout = DEFAULT_I2C_TIMEOUT;
  uint32_t tickstart;
  uint8_t RegAddr = 0;
  uint8_t RegValue = 0;

  if (hi2c->State != HAL_I2C_STATE_READY)
  {
    return HAL_ERROR;
  }

  hi2c->Mode = HAL_I2C_MODE_SLAVE;

  /* Enable Address Acknowledge if not already enabled */
  hi2c->Instance->CR2 &= ~I2C_CR2_NACK;

  /* Check if ADDR flag is set */
  if (__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_ADDR) == RESET) {
    /* Return timeout here when there is nothing to do, thats normal */
    return HAL_TIMEOUT;
  }

  /* I2C communication sequence started, setup timeout */
  tickstart = HAL_GetTick();

  /* Clear ADDR flag */
  __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ADDR);

  /* Wait until DIR flag is reset Receiver mode */
  if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_DIR, SET, Timeout, tickstart) != HAL_OK)
  {
    /* Disable Address Acknowledge */
    hi2c->Instance->CR2 |= I2C_CR2_NACK;
    return HAL_ERROR;
  }

  /* Read a register address as a single byte  */
  if (I2C_Slave_Raw_Read_Byte(hi2c, &RegAddr, Timeout, tickstart) != HAL_OK) {
    return HAL_ERROR;
  }

  /* Wait on both RXNE and ADDR!! */
  uint32_t ReadAddrResult = 0;

  if (I2C_WaitOnReadOrAddrUntilTimeout(hi2c, Timeout, tickstart, &ReadAddrResult) != HAL_OK) {
    return HAL_ERROR;
  }

  /* Another read detected, perform a single byte read from specified register */
  if ((ReadAddrResult & I2C_FLAG_RXNE) == I2C_FLAG_RXNE) {
    if (I2C_Slave_Raw_Read_Byte(hi2c, &RegValue, Timeout, tickstart) != HAL_OK) {
      return HAL_ERROR;
    }

    /* Process the data byte for the address given */
    HAL_I2C_RegSendByte_Callback(hi2c, RegAddr, RegValue);

    /* Processed, clear previous result */
    ReadAddrResult = 0;
  }

  /* Address detected, expecting a direction change for a single byte write */
  if ((ReadAddrResult & I2C_FLAG_ADDR) == I2C_FLAG_ADDR) {
    /* Clear ADDR flag */
    __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ADDR);

    /* Get the data byte for the address given */
    RegValue = HAL_I2C_RegGetByte_Callback(hi2c, RegAddr);

    /* Perform single byte write from specified register */
    if (I2C_Slave_Raw_Write_Byte(hi2c, &RegValue, Timeout, tickstart) != HAL_OK) {
      /* Disable Address Acknowledge */
      hi2c->Instance->CR2 |= I2C_CR2_NACK;
      return HAL_ERROR;
    }

    /* Processed, clear previous result */
    ReadAddrResult = 0;
  }

  /* CONTINUE typical STM implementation */

  /* Wait until STOP flag is set */
  if (I2C_WaitOnSTOPFlagUntilTimeout(hi2c, Timeout, tickstart) != HAL_OK)
  {
    /* Disable Address Acknowledge */
    hi2c->Instance->CR2 |= I2C_CR2_NACK;
    return HAL_ERROR;
  }

  /* Clear STOP flag */
  __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_STOPF);

  /* Leave Address Acknowledge enabled, immediately ready for another message */

  hi2c->State = HAL_I2C_STATE_READY;

  return HAL_OK;
}


static HAL_StatusTypeDef I2C_Wakeup_ISR_IT(struct __I2C_HandleTypeDef *hi2c, uint32_t ITFlags,
                                           uint32_t ITSources)
{
  __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_ADDRI);
  return HAL_OK;
}

void HAL_I2C_StopMode_Setup(struct __I2C_HandleTypeDef *hi2c)
{
  if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_BUSY, SET, 1000U, HAL_GetTick()) != HAL_OK)
  {
    Error_Handler();
  }

  __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ADDR);

  if (I2C_WaitOnFlagUntilTimeout(hi2c, I2C_FLAG_ADDR, SET, 1000U, HAL_GetTick()) != HAL_OK)
  {
    Error_Handler();
  }

  hi2c->XferISR = I2C_Wakeup_ISR_IT;

  __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_ADDRI);
}
