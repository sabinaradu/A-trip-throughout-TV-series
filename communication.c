#include "communication.h"
#include "util_comm.h"

#include <stdio.h>

#define ENC 'A'+1
#define DEC 'A'-1
#define HALF_BYTE 4

/* Task 1 - The Beginning */

void send_byte_message(void)
{
    send_squanch('R'-ENC);
    send_squanch('I'-ENC);
    send_squanch('C'-ENC);
    send_squanch('K'-ENC);
    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */
}


void recv_byte_message(void)
{
    char c;
    int i;
    for(i = 0; i < 5; i++){
        c = recv_squanch();
        fprintf(stdout, "%c", c+DEC);
    }
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */
}


void comm_byte(void)
{
    int i;
    for(i = 0; i < 10; i++){
        char c = recv_squanch();
        send_squanch(c);
        send_squanch(c);
    }
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */
}


/* Task 2 - Waiting for the Message */

void send_message(void)
{
    char message[] = "HELLOTHERE";
    int len = 10, i;

    send_squanch(len<<2);
    for(i = 0; i < len; i++){
        send_squanch(message[i]-ENC);
    }

    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */
}


void recv_message(void)
{
    uint8_t len, i;
    len = recv_squanch();
    len = len << 2;
    len = len >> 4;
    fprintf(stdout, "%u", len);
    for(i = 0; i < len; i++){
        char c = recv_squanch();
        fprintf(stdout, "%c", c+DEC);
    }
    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */
}


void comm_message(void)
{
    uint8_t len, i;
    len = recv_squanch();
    len = len << 2;
    len = len >> 4;

    char message[len];    
    
    for(i = 0; i < len; i++){
        message[i] = recv_squanch()+DEC;
    }

    if( message[len-1] == 'P' ){
        char send[] = "PICKLERICK";
        uint8_t send_len = 10;

        send_squanch(send_len<<2);

        for(i = 0; i < send_len; i++){
            send_squanch(send[i]-ENC);
        }
        
    }
    else{
        char send[] = "VINDICATORS";
        uint8_t send_len = 11;

        send_squanch(send_len<<2);

        for(i = 0; i < send_len; i++){
            send_squanch(send[i]-ENC);
        }
    }
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */
}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    uint8_t mask, new_char = 0;
    uint8_t i;

    for(i = 0; i < HALF_BYTE; i++){
        uint8_t temp = 0;

        mask = 1 << i;
        temp |= (mask & c1) >> i;
        
        temp <<= 1;
        temp |= (mask & c2) >> i;
        
        new_char |= temp << (i*2);
    }

    send_squanch(new_char);

    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */
}


uint8_t decode_squanch2(uint8_t c)
{
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = 0;

    uint8_t mask = 1, i;
    for(i = 0; i < HALF_BYTE; i++, mask <<= 2){
        uint8_t temp = 0;

        temp |= (mask & c);
        
        res |= temp >> i; 
    }

    mask = 1 << 1;
    for(i = 0; i < HALF_BYTE; i++, mask <<= 2){
        uint8_t temp = 0;
        
        temp |= (mask & c);
        
        res |= temp << (HALF_BYTE - (i + 1)); 
    }


    /* TODO */

    return res;
}
