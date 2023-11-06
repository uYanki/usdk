#if defined(__CC_ARM) || defined(__ICCARM__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))

/*!
 * @brief  Redirect C Library function printf to serial port.
 * @param  ch:  The characters that need to be send.
 * @param  *f:  pointer to a FILE that can recording all information needed to control a stream
 * @retval The characters that need to be send.
 * @note
 */
int fputc(int ch, FILE* f)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, (uint8_t)ch);

    /* wait for the data to be send */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET)
        ;

    return (ch);
}

#elif defined(__GNUC__)

int __io_putchar(int ch)
{
    /* send a byte of data to the serial port */
    USART_TxData(DEBUG_USART, ch);

    /* wait for the data to be send */
    while (USART_ReadStatusFlag(DEBUG_USART, USART_FLAG_TXBE) == RESET)
        ;

    return ch;
}

/*!
 * @brief  Redirect C Library function printf to serial port.
 * @param  file:  Meaningless in this function.
 * @param  *ptr:  Buffer pointer for data to be sent.
 * @param  len:  Length of data to be sent.
 * @retval The characters that need to be send.
 * @note
 */
int _write(int file, char* ptr, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        __io_putchar(*ptr++);
    }

    return len;
}

#else
#warning Not supported compiler type
#endif
