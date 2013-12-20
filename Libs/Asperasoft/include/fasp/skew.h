#ifndef AS_SKEW_H
#define AS_SKEW_H

/* Order an array of doubles using bubble sort */
void order(double *unord_arr, double *ord_arr, int no_elems);

/* wrapper function */
void remove_skew(pp *pp_info, pp *pp_noskew, int cur_pp, int obs_len, int algorithm);

/* Robust linear regression (RLF) algorithm to remove clock skew */
void remove_skew_RLF(pp *pp_info, pp *pp_noskew, int cur_pp, int obs_len);

/* RLF algorithm combined with de-noising */
void remove_skew_RLF_denoi(pp *pp_info, pp *pp_noskew, int cur_pp, int obs_len);

/* Convex Hull algorithm to remove clock skew */
void remove_skew_ConvHull(pp *pp_info, pp *pp_noskew, int cur_pp, int obs_len);

#endif
