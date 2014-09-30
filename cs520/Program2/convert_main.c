#include "convert.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv){
/////////////////////////////////////////////////////// 
///////////////////////////////////////////////////////
// Test Cases for double to long
// un-comment and use one at a time.
/////////////////////////////////////////////////////// 


    //for(double d = -3.0e-200; d < 0xffffffffffffffff; d*= 2){ 
    //    long l1 = double_to_long(d);
    //    long l2 = (long) d;
    //    if(l1 != l2){
    //        fprintf(stderr, "Input: %e, Should be %ld, got %ld\n", d, l2, l1);
    //        return 1;
    //    }   
    //}

    //for(double d = 0xffffffffffffffff; d > -3.0e-324; d/= 2){ 
    //    long l1 = double_to_long(d);
    //    long l2 = (long) d;
    //    if(l1 != l2){
    //        fprintf(stderr, "Input: %e, Should be %ld, got %ld\n", d, l2, l1);
    //        return 1;
    //    }   
    //}
    
    //for(double d = 1000000000; d > -1000000000; d--){ 
    //    long l1 = double_to_long(d);
    //    long l2 = (long) d;
    //    if(l1 != l2){
    //        fprintf(stderr, "Input: %e, Should be %ld, got %ld\n", d, l2, l1);
    //        return 1;
    //    }   
    //}
    
    //long not_a_number = double_to_long(NAN);
    //long l2 = (long) NAN;
    //if(not_a_number != l2){
    //    fprintf(stderr, "Input: %e, Should be %ld, got %ld\n", NAN, l2, not_a_number);
    //    //return 1;
    //}

    long negativeInfinity = double_to_long(-INFINITY);
    long l2 = (long) -INFINITY;
    if(negativeInfinity != l2){
        fprintf(stderr, "Input: %e, Should be %ld, got %ld\n", -INFINITY, l2, negativeInfinity);
        //return 1;
    }



/////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////// 
// test cases for double to long
// these can be run all at once    
///////////////////////////////////////////////////////     

    /*for( long l = 3; l < 0x8000000000000005l && l != 0 ; l *= 2 ){
        double d1 = long_to_double(l);
        double d2 = (double) l;
        if( d1 != d2 ){
            fprintf( stderr, "Input: %ld, Should be %lf, got %lf\n\n\n\n", l, d2, d1 );
            return 1;
        }
    }

    for( long l = -3; l > ~0x8000000000000005l + 1 && l != 0 ; l *= 2 ){
        double d1 = long_to_double(l);
        double d2 = (double) l;
        if( d1 != d2 ){
            fprintf( stderr, "Input: %ld, Should be %lf, got %lf\n\n\n\n", l, d2, d1 );
            return 1;
        }
    }

    for( long l = 0; l < 16; l ++ ){
        double d1 = long_to_double(l);
        double d2 = (double) l;
        if( d1 != d2 ){
            fprintf( stderr, "Input: %ld, Should be %lf, got %lf\n\n\n\n", l, d2, d1 );
            return 1;
        }
    }
    
    for( long l = 0; l > -16; l -- ){
        double d1 = long_to_double(l);
        double d2 = (double) l;
        if( d1 != d2 ){
            fprintf( stderr, "Input: %ld, Should be %lf, got %lf\n\n\n\n", l, d2, d1 );
            return 1;
        }
    }


    for( long l = 0x3000000000000000; l < 0x3000000000000010; l ++ ){
        
        double d1 = long_to_double(l);
        double d2 = (double)l;
        if( d1 != d2 ){
            fprintf( stderr, "Input: %ld, Should be %lf, got %lf\n\n\n\n", l, d2, d1 );
            return 1;
        }
    }
    
    
    for( long l = ~0x3000000000000000; l > ~0x3000000000000010; l -- ){
        
        double d1 = long_to_double(l);
        double d2 = (double)l;
        if( d1 != d2 ){
            fprintf( stderr, "Input: %#lx, Should be %lf, got %lf\n\n\n\n", l, d2, d1 );
            return 1;
        }
    }

    
    for( long l = 18014398609481983; l > 18014398409481983 && l != 0 ; l -- ){
        
        double d1 = long_to_double(l);
        double d2 = (double)l;
        if( d1 != d2 ){
            fprintf( stderr, "Input: %#lx, Should be %lf, got %lf\n\n\n\n", l, d2, d1 );
            return 1;
        }
    }

    double d1 = long_to_double(0xFFFFFFFFFFFFFFFF);
    double d2 = (double)d1;
    if( d1 != d2 ){
        fprintf( stderr, "Input: %#lx, Should be %lf, got %lf\n\n\n\n", 0xFFFFFFFFFFFFFFFF, d2, d1 );
        return 1;
    }*/

    return 0;
}

