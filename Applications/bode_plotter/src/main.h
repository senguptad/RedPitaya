/**
 * $Id: main.h 881 2013-12-16 05:37:34Z rp_jmenart $
 *
 * @brief Red Pitaya Oscilloscope main module.
 *
 * @Author Jure Menart <juremenart@gmail.com>
 *         
 * (c) Red Pitaya  http://www.redpitaya.com
 *
 * This part of code is written in C programming language.
 * Please visit http://en.wikipedia.org/wiki/C_(programming_language)
 * for more details on the language used herein.
 */

#ifndef __MAIN_H
#define __MAIN_H

#ifdef DEBUG
#  define TRACE(args...) fprintf(stderr, args)
#else
#  define TRACE(args...) {}
#endif

/* Parameters description structure - must be the same for all RP controllers */
typedef struct rp_app_params_s {
    char  *name;
    float  value;
    int    fpga_update;
    int    read_only;
    float  min_val;
    float  max_val;
} rp_app_params_t;

/* Signal measurement results structure - filled in worker and updated when
 * also measurement signal is stored from worker 
 */
typedef struct rp_osc_meas_res_s {
    float min;
    float max;
    float amp;
    float avg;
    float freq;
    float period;
} rp_osc_meas_res_t;

/* Parameters indexes - these defines should be in the same order as 
 * rp_app_params_t structure defined in main.c */
#define PARAMS_NUM        89
#define MIN_GUI_PARAM     0
#define MAX_GUI_PARAM     1
#define TRIG_MODE_PARAM   2
#define TRIG_SRC_PARAM    3
#define TRIG_EDGE_PARAM   4
#define TRIG_DLY_PARAM    5
#define TRIG_LEVEL_PARAM  6
#define SINGLE_BUT_PARAM  7
#define TIME_RANGE_PARAM  8
#define TIME_UNIT_PARAM   9
#define EN_AVG_AT_DEC     10
#define AUTO_FLAG_PARAM   11
#define MIN_Y_PARAM       12
#define MAX_Y_PARAM       13
#define FORCEX_FLAG_PARAM 14
#define MEAS_MIN_CH1      15
#define MEAS_MAX_CH1      16
#define MEAS_AMP_CH1      17
#define MEAS_AVG_CH1      18
#define MEAS_FREQ_CH1     19
#define MEAS_PER_CH1      20
#define MEAS_MIN_CH2      21
#define MEAS_MAX_CH2      22
#define MEAS_AMP_CH2      23
#define MEAS_AVG_CH2      24
#define MEAS_FREQ_CH2     25
#define MEAS_PER_CH2      26
#define PRB_ATT_CH1       27
#define GAIN_CH1          28
#define PRB_ATT_CH2       29
#define GAIN_CH2          30
#define GUI_RST_Y_RANGE   31
#define GEN_DC_OFFS_1     32
#define GEN_DC_OFFS_2     33
#define GUI_XMIN          34
#define GUI_XMAX          35
#define MIN_Y_NORM        36
#define MAX_Y_NORM        37
#define GEN_DC_NORM_1     38
#define GEN_DC_NORM_2     39
#define SCALE_CH1         40
#define SCALE_CH2         41
/* BODE parameters */
#define BODE_S_MEASURE    42
#define BODE_GEN_AMP      43
#define BODE_GEN_AVG      44
#define BODE_GEN_DC_BIAS  45
#define BODE_STAR_FREQ    46
#define BODE_END_FREQ     47
#define DATA_PLOT         48
#define BODE_SCALE_TYPE   49
/* AWG parameters */
#define GEN_TRIG_MODE_CH1 50
#define GEN_SIG_TYPE_CH1  51
#define GEN_ENABLE_CH1    52
#define GEN_SINGLE_CH1    53
#define GEN_SIG_AMP_CH1   54
#define GEN_SIG_FREQ_CH1  55
#define GEN_SIG_DCOFF_CH1 56
#define GEN_TRIG_MODE_CH2 57
#define GEN_SIG_TYPE_CH2  58
#define GEN_ENABLE_CH2    59
#define GEN_SINGLE_CH2    60
#define GEN_SIG_AMP_CH2   61
#define GEN_SIG_FREQ_CH2  62
#define GEN_SIG_DCOFF_CH2 63
#define GEN_AWG_REFRESH   64
/* PID parameters */
#define PID_11_ENABLE     65
#define PID_11_RESET      66
#define PID_11_SP         67
#define PID_11_KP         68
#define PID_11_KI         69
#define PID_11_KD         70
#define PID_12_ENABLE     71
#define PID_12_RESET      72
#define PID_12_SP         73
#define PID_12_KP         74
#define PID_12_KI         75
#define PID_12_KD         76
#define PID_21_ENABLE     77
#define PID_21_RESET      78
#define PID_21_SP         79
#define PID_21_KP         80
#define PID_21_KI         81
#define PID_21_KD         82
#define PID_22_ENABLE     83
#define PID_22_RESET      84
#define PID_22_SP         85
#define PID_22_KP         86
#define PID_22_KI         87
#define PID_22_KD         88

/* Defines from which parameters on are AWG parameters (used in set_param() to
 * trigger update only on needed part - either Oscilloscope, AWG or PID */
#define PARAMS_AWG_PARAMS 50

/* Defines from which parameters on are PID parameters (used in set_param() to
 * trigger update only on needed part - either Oscilloscope, AWG or PID */
#define PARAMS_PID_PARAMS 65
#define PARAMS_PER_PID     6

/* Output signals */
#define SIGNAL_LENGTH (101) /* Must be 2^n! */
#define SIGNALS_NUM   3


/* module entry points */
int rp_app_init(void);
int rp_app_exit(void);
int rp_set_params(rp_app_params_t *p, int len);
int rp_get_params(rp_app_params_t **p);
int rp_get_signals(float ***s, int *sig_num, int *sig_len);

/* Internal helper functions */
int  rp_create_signals(float ***a_signals);
void rp_cleanup_signals(float ***a_signals);

/* copies parameters from src to dst - if dst does not exists, it creates it */
int rp_copy_params(rp_app_params_t *src, rp_app_params_t **dst);

/* cleans up memory of parameters structure */
int rp_clean_params(rp_app_params_t *params);

/* Updates all parameters (structure must be aligned with main parameter
 * structure - this includes also ready-only parameters. After the 
* parameters are updated it also changed the worker state machine.
 */
int rp_update_main_params(rp_app_params_t *params);
void get_scales(rp_app_params_t *p, float *scale1, float *scale2, float *maxv);
void transform_to_iface_units(rp_app_params_t *p);
void transform_from_iface_units(rp_app_params_t *p);

/* sets the measurement data to output parameters structure - these parameters
 * are read-only for the client and there is no need to update them internally
 * in the application 
 */
int rp_update_meas_data(rp_osc_meas_res_t ch1_meas, rp_osc_meas_res_t ch2_meas);

/* Waveform generator frequency limiter. */
float rp_gen_limit_freq(float freq, float gen_type);

/* Bode param return */
float rp_get_params_bode(int pos);

/* Bode set params */
void rp_set_params_bode(int pos, int val);

#endif /*  __MAIN_H */
