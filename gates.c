#include "gates.h"

#include <stdio.h>
#include <assert.h>

#define SZ 64

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    uint64_t mask = (uint64_t)1 << i;

    mask &= nr;

    res = mask ? 1 : 0;
    
    return res;
}


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    uint64_t mask = (uint64_t)1 << i;
    res = nr ^ mask;
    
    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;

    uint64_t mask = (uint64_t)1 << i;

    res = nr | mask;

    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    uint64_t mask = (uint64_t)1 << i;
    mask = ~mask;

    res = nr & mask;
    
    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    uint8_t part = nand_gate(a, b);
    res = nand_gate(part,  part);

    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    res = nand_gate(a, a);

    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    uint8_t first = nand_gate(a, a);
    uint8_t second = nand_gate(b, b);

    res = nand_gate(first, second);

    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    uint8_t nandab = nand_gate(a, b);
    uint8_t first = nand_gate(nandab, a);
    uint8_t second = nand_gate(nandab, b);

    res = nand_gate(first, second);

    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1;

    uint8_t xorab = xor_gate(a, b);
    uint8_t andab = and_gate(a, b);

    uint8_t sum = xor_gate(xorab, c);
    uint8_t part = and_gate(xorab, c);
    uint8_t carry = or_gate(andab, part);
    
    res = (carry << 1) | (sum);
    //printf("%u %u %u %u\n", res, a, b, c);
    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = 0;

    uint8_t i, carry = 0;

    for(i = 0; i < SZ; i++){
        uint8_t a_bit = get_bit(a, i);
        uint8_t b_bit = get_bit(b, i);
        uint8_t adder_res = full_adder(a_bit, b_bit, carry);
        
        carry = get_bit((uint64_t)adder_res, 1);
        uint8_t sum_bit = get_bit((uint64_t)adder_res, 0);
       
        if( sum_bit )
            res = activate_bit(res, i);
    }
    //Daca iesim cu carry 1 din suma pe 64 de biti e oveflow...si trebuie
    //pus 0 desi UINT64_MAX+UINT64_MAX nu dau 0, dar ma rog...
    if(carry == 1)
        return 0;
    
    return res;
}
