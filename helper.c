/**
 * @file    helper.c
 * @author  F Lundevall
 * @author  Axel Isaksson
 * @author  Joel Wachsler (wachsler@kth.se)
 * @author  Marcus Werlinder (werli@kth.se)
 * @date    2015-2016
 * @copyright For copyright and licensing, see file COPYING
 *
 * This file was written 2016 by Joel wachsler and Marcus Werlinder
 * Content of this file is based on the file "mipslabwork.c" 2015 by F Lundevall
 * Some parts are original code written by Axel Isaksson
 */

#include "declaration.h"

/**
 * Pow doesn't exist so let's create one!
 *
 * @param [in] base The base of the number.
 * @param [in] exponent The exponent.
 */
unsigned int pow(unsigned const char base, unsigned char exponent) {
    unsigned int result = 1;
    for(;exponent > 0; exponent--)
        result *= base;
    return result;
}

/**
 * A simple function to create a small delay.
 * Very inefficient use of computing resources,
 * but very handy in some special cases.
 *
 * @param [in] cyc how long should the sleep be
 */
void quicksleep(int cyc) {
    int i;
    for(i = cyc; i > 0; i--);
}

/**
 * @brief Simple conversion routine
 * Converts binary to decimal numbers
 * Returns pointer to (static) char array
 *
 * The integer argument is converted to a string
 * of digits representing the integer in decimal format.
 * The integer is considered signed, and a minus-sign
 * precedes the string of digits if the number is
 * negative.
 *
 * This routine will return a varying number of digits, from
 * one digit (for integers in the range 0 through 9) and up to
 * 10 digits and a leading minus-sign (for the largest negative
 * 32-bit integers).
 *
 * If the integer has the special value
 * 100000...0 (that's 31 zeros), the number cannot be
 * negated. We check for this, and treat this as a special case.
 * If the integer has any other value, the sign is saved separately.
 *
 * If the integer is negative, it is then converted to
 * its positive counterpart. We then use the positive
 * absolute value for conversion.
 *
 * Conversion produces the least-significant digits first,
 * which is the reverse of the order in which we wish to
 * print the digits. We therefore store all digits in a buffer,
 * in ASCII form.
 *
 * To avoid a separate step for reversing the contents of the buffer,
 * the buffer is initialized with an end-of-string marker at the
 * very end of the buffer. The digits produced by conversion are then
 * stored right-to-left in the buffer: starting with the position
 * immediately before the end-of-string marker and proceeding towards
 * the beginning of the buffer.
 *
 * For this to work, the buffer size must of course be big enough
 * to hold the decimal representation of the largest possible integer,
 * and the minus sign, and the trailing end-of-string marker.
 * The value 24 for ITOA_BUFSIZ was selected to allow conversion of
 * 64-bit quantities; however, the size of an int on your current compiler
 * may not allow this straight away.
 *
 * @param [in] num interger to convert
 * @return A pointer to the char representation of the interger
 */
#define ITOA_BUFSIZ (24)
char *itoaconv(int num) {
    register int i, sign;
    static char itoa_buffer[ ITOA_BUFSIZ ];
    static const char maxneg[] = "-2147483648";

    itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
    sign = num;                           /* Save sign. */
    if( num < 0 && num - 1 > 0 ) {        /* Check for most negative integer */
        for( i = 0; i < sizeof( maxneg ); i += 1 )
            itoa_buffer[ i + 1 ] = maxneg[ i ];
        i = 0;
    } else {
        if( num < 0 ) num = -num;           /* Make number positive. */
        i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
        do {
            itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
            num = num / 10;                   /* Remove digit from number. */
            i -= 1;                           /* Move index to next empty position. */
        } while( num > 0 );
        if( sign < 0 ) {
            itoa_buffer[ i ] = '-';
            i -= 1;
        }
    }
    /* Since the loop always sets the index i to the next empty position,
     * we must add 1 in order to return a pointer to the first occupied position. */
    return( &itoa_buffer[ i + 1 ] );
}
