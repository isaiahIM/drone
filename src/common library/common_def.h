#ifndef COMMON_DEF__H
#define COMMON_DEF__H


#ifdef USE_ARM_DSP
#include "arm_math.h"
#include "math_helper.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum date
{
    SUN=0,///< Sunday
    MON,///< Monday
    TUE,///< Tuesday
    WED,///< Wednesday
    THU,///< Thursday
    FRI,///< Friday
    SAT///< Saturday
};

enum month
{
    JAN=1,///< January
    FEB=2,///< February
    MAR,///< March
    APR,///< April
    MAY,///< May
    JUN,///< June
    JLY,///< July
    AUG,///< August
    SEP,///< September
    OCT,///< October
    NOV,///< November
    DEC///< December
};

#endif