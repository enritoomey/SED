/* Include files */

#include <stddef.h>
#include "blas.h"
#include "modelo_sfun.h"
#include "c1_modelo.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "modelo_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[25] = { "w1", "w2", "w3", "w4", "W",
  "m", "n", "N", "Hm", "facet", "i", "j", "aux", "facet_aux", "k", "l", "aux2",
  "Hmax_aux", "M", "sol", "nargin", "nargout", "H", "Hmax", "Hwheel" };

/* Function Declarations */
static void initialize_c1_modelo(SFc1_modeloInstanceStruct *chartInstance);
static void initialize_params_c1_modelo(SFc1_modeloInstanceStruct *chartInstance);
static void enable_c1_modelo(SFc1_modeloInstanceStruct *chartInstance);
static void disable_c1_modelo(SFc1_modeloInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_modelo(SFc1_modeloInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_modelo(SFc1_modeloInstanceStruct
  *chartInstance);
static void set_sim_state_c1_modelo(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_st);
static void finalize_c1_modelo(SFc1_modeloInstanceStruct *chartInstance);
static void sf_c1_modelo(SFc1_modeloInstanceStruct *chartInstance);
static void c1_chartstep_c1_modelo(SFc1_modeloInstanceStruct *chartInstance);
static void initSimStructsc1_modelo(SFc1_modeloInstanceStruct *chartInstance);
static void registerMessagesc1_modelo(SFc1_modeloInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static void c1_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance, const
  mxArray *c1_Hwheel, const char_T *c1_identifier, real_T c1_y[4]);
static void c1_b_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[4]);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_c_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_d_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3]);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[4], int32_T c1_inData_sizes[2]);
static void c1_e_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y_data[4],
  int32_T c1_y_sizes[2]);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[4],
  int32_T c1_outData_sizes[2]);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_f_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[9]);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[4], int32_T c1_inData_sizes[1]);
static void c1_g_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y_data[4],
  int32_T c1_y_sizes[1]);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[4],
  int32_T c1_outData_sizes[1]);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_h_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[4]);
static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_i_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[16]);
static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_j_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[48]);
static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_k_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[96]);
static void c1_b_info_helper(c1_ResolvedFunctionInfo c1_info[96]);
static void c1_cross(SFc1_modeloInstanceStruct *chartInstance, real_T c1_a[3],
                     real_T c1_b[3], real_T c1_c[3]);
static real_T c1_dot(SFc1_modeloInstanceStruct *chartInstance, real_T c1_a[3],
                     real_T c1_b[3]);
static void c1_eml_scalar_eg(SFc1_modeloInstanceStruct *chartInstance);
static real_T c1_abs(SFc1_modeloInstanceStruct *chartInstance, real_T c1_x);
static real_T c1_b_dot(SFc1_modeloInstanceStruct *chartInstance, real_T c1_a[3],
  real_T c1_b[3]);
static void c1_b_eml_scalar_eg(SFc1_modeloInstanceStruct *chartInstance);
static void c1_eml_li_find(SFc1_modeloInstanceStruct *chartInstance, boolean_T
  c1_x[4], int32_T c1_y_data[4], int32_T c1_y_sizes[2]);
static void c1_b_eml_li_find(SFc1_modeloInstanceStruct *chartInstance, boolean_T
  c1_x_data[4], int32_T c1_x_sizes[2], int32_T c1_y_data[4], int32_T c1_y_sizes
  [2]);
static void c1_c_eml_scalar_eg(SFc1_modeloInstanceStruct *chartInstance);
static void c1_d_eml_scalar_eg(SFc1_modeloInstanceStruct *chartInstance);
static void c1_eml_xgemm(SFc1_modeloInstanceStruct *chartInstance, int32_T c1_k,
  real_T c1_A_data[12], int32_T c1_A_sizes[2], real_T c1_B_data[4], int32_T
  c1_B_sizes[1], int32_T c1_ldb, real_T c1_C[3], real_T c1_b_C[3]);
static void c1_mldivide(SFc1_modeloInstanceStruct *chartInstance, real_T c1_A[9],
  real_T c1_B[3], real_T c1_Y[3]);
static void c1_eml_warning(SFc1_modeloInstanceStruct *chartInstance);
static const mxArray *c1_l_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_k_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_l_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_modelo, const char_T *c1_identifier);
static uint8_T c1_m_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_eml_xgemm(SFc1_modeloInstanceStruct *chartInstance, int32_T
  c1_k, real_T c1_A_data[12], int32_T c1_A_sizes[2], real_T c1_B_data[4],
  int32_T c1_B_sizes[1], int32_T c1_ldb, real_T c1_C[3]);
static void init_dsm_address_info(SFc1_modeloInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_modelo(SFc1_modeloInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_modelo = 0U;
}

static void initialize_params_c1_modelo(SFc1_modeloInstanceStruct *chartInstance)
{
}

static void enable_c1_modelo(SFc1_modeloInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_modelo(SFc1_modeloInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_modelo(SFc1_modeloInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_modelo(SFc1_modeloInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  int32_T c1_i0;
  real_T c1_u[4];
  const mxArray *c1_b_y = NULL;
  uint8_T c1_hoistedGlobal;
  uint8_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T (*c1_Hwheel)[4];
  c1_Hwheel = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(2), FALSE);
  for (c1_i0 = 0; c1_i0 < 4; c1_i0++) {
    c1_u[c1_i0] = (*c1_Hwheel)[c1_i0];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_hoistedGlobal = chartInstance->c1_is_active_c1_modelo;
  c1_b_u = c1_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_modelo(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv0[4];
  int32_T c1_i1;
  real_T (*c1_Hwheel)[4];
  c1_Hwheel = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
                      "Hwheel", c1_dv0);
  for (c1_i1 = 0; c1_i1 < 4; c1_i1++) {
    (*c1_Hwheel)[c1_i1] = c1_dv0[c1_i1];
  }

  chartInstance->c1_is_active_c1_modelo = c1_l_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 1)), "is_active_c1_modelo");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_modelo(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_modelo(SFc1_modeloInstanceStruct *chartInstance)
{
}

static void sf_c1_modelo(SFc1_modeloInstanceStruct *chartInstance)
{
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  real_T (*c1_Hmax)[4];
  real_T (*c1_Hwheel)[4];
  real_T (*c1_H)[3];
  c1_Hmax = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
  c1_Hwheel = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_H = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i2 = 0; c1_i2 < 3; c1_i2++) {
    _SFD_DATA_RANGE_CHECK((*c1_H)[c1_i2], 0U);
  }

  for (c1_i3 = 0; c1_i3 < 4; c1_i3++) {
    _SFD_DATA_RANGE_CHECK((*c1_Hwheel)[c1_i3], 1U);
  }

  for (c1_i4 = 0; c1_i4 < 4; c1_i4++) {
    _SFD_DATA_RANGE_CHECK((*c1_Hmax)[c1_i4], 2U);
  }

  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_modelo(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_modeloMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_modelo(SFc1_modeloInstanceStruct *chartInstance)
{
  int32_T c1_i5;
  real_T c1_H[3];
  int32_T c1_i6;
  real_T c1_Hmax[4];
  uint32_T c1_debug_family_var_map[25];
  real_T c1_w1[3];
  real_T c1_w2[3];
  real_T c1_w3[3];
  real_T c1_w4[3];
  real_T c1_W[12];
  real_T c1_m;
  real_T c1_n;
  real_T c1_N[48];
  real_T c1_Hm[16];
  real_T c1_facet;
  real_T c1_i;
  real_T c1_j;
  real_T c1_aux[4];
  real_T c1_facet_aux;
  real_T c1_k;
  real_T c1_l;
  int32_T c1_aux2_sizes;
  real_T c1_aux2_data[4];
  int32_T c1_Hmax_aux_sizes;
  real_T c1_Hmax_aux_data[4];
  real_T c1_M[9];
  real_T c1_sol[3];
  int32_T c1_aux_sizes[2];
  real_T c1_aux_data[4];
  real_T c1_b_aux[3];
  real_T c1_nargin = 2.0;
  real_T c1_nargout = 1.0;
  real_T c1_Hwheel[4];
  int32_T c1_i7;
  int32_T c1_i8;
  static real_T c1_dv1[3] = { -0.57735026918962584, -0.57735026918962584,
    0.57735026918962584 };

  int32_T c1_i9;
  static real_T c1_dv2[3] = { -0.57735026918962584, 0.57735026918962584,
    0.57735026918962584 };

  int32_T c1_i10;
  static real_T c1_dv3[3] = { -0.57735026918962584, 0.57735026918962584,
    -0.57735026918962584 };

  int32_T c1_i11;
  static real_T c1_dv4[12] = { -0.57735026918962584, -0.57735026918962584,
    -0.57735026918962584, -0.57735026918962584, -0.57735026918962584,
    0.57735026918962584, -0.57735026918962584, 0.57735026918962584,
    0.57735026918962584, -0.57735026918962584, 0.57735026918962584,
    -0.57735026918962584 };

  int32_T c1_i12;
  int32_T c1_i13;
  int32_T c1_b_i;
  int32_T c1_b_j;
  int32_T c1_c_i;
  int32_T c1_i14;
  real_T c1_b_W[3];
  int32_T c1_c_j;
  int32_T c1_i15;
  real_T c1_c_W[3];
  real_T c1_dv5[3];
  int32_T c1_i16;
  int32_T c1_d_j;
  int32_T c1_d_i;
  int32_T c1_i17;
  int32_T c1_b_m;
  real_T c1_a;
  int32_T c1_c_m;
  int32_T c1_i18;
  real_T c1_d_W[3];
  int32_T c1_i19;
  real_T c1_c_aux[3];
  real_T c1_b;
  real_T c1_y;
  real_T c1_b_N[3];
  int32_T c1_i20;
  real_T c1_b_H[3];
  real_T c1_A;
  real_T c1_B;
  real_T c1_x;
  real_T c1_b_y;
  real_T c1_b_x;
  real_T c1_c_y;
  int32_T c1_i21;
  int32_T c1_i22;
  boolean_T c1_d_aux[4];
  int32_T c1_tmp_sizes[2];
  int32_T c1_tmp_data[4];
  int32_T c1_e_aux;
  int32_T c1_f_aux;
  int32_T c1_loop_ub;
  int32_T c1_i23;
  int32_T c1_b_aux_sizes[2];
  int32_T c1_g_aux;
  int32_T c1_h_aux;
  int32_T c1_b_loop_ub;
  int32_T c1_i24;
  boolean_T c1_b_aux_data[4];
  int32_T c1_i_aux;
  int32_T c1_j_aux[1];
  int32_T c1_k_aux;
  int32_T c1_c_aux_sizes[2];
  int32_T c1_c_loop_ub;
  int32_T c1_i25;
  real_T c1_c_aux_data[4];
  int32_T c1_d_loop_ub;
  int32_T c1_i26;
  int32_T c1_x_sizes[2];
  int32_T c1_c_x;
  int32_T c1_d_x;
  int32_T c1_e_loop_ub;
  int32_T c1_i27;
  real_T c1_x_data[4];
  real_T c1_b_n;
  int32_T c1_f_loop_ub;
  int32_T c1_i28;
  int32_T c1_e_x;
  int32_T c1_f_x;
  int32_T c1_g_loop_ub;
  int32_T c1_i29;
  real_T c1_d0;
  int32_T c1_i30;
  int32_T c1_e_i;
  int32_T c1_l_aux[1];
  int32_T c1_m_aux;
  int32_T c1_i31;
  real_T c1_b_a[3];
  real_T c1_b_b[3];
  real_T c1_c;
  int32_T c1_ix;
  int32_T c1_iy;
  int32_T c1_b_k;
  int32_T c1_c_a;
  int32_T c1_d_a;
  real_T c1_g_x;
  real_T c1_h_x;
  int32_T c1_d_aux_sizes[2];
  int32_T c1_h_loop_ub;
  int32_T c1_i32;
  int32_T c1_d_aux_data[4];
  int32_T c1_b_sizes;
  int32_T c1_i_loop_ub;
  int32_T c1_i33;
  real_T c1_b_data[4];
  int32_T c1_j_loop_ub;
  int32_T c1_i34;
  int32_T c1_n_aux[1];
  int32_T c1_a_sizes[2];
  int32_T c1_k_loop_ub;
  int32_T c1_i35;
  int32_T c1_i36;
  real_T c1_a_data[12];
  int32_T c1_l_loop_ub;
  int32_T c1_i37;
  boolean_T c1_innerDimOk;
  int32_T c1_i38;
  static char_T c1_cv0[45] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'm', 't', 'i', 'm', 'e', 's', '_', 'n', 'o', 'D', 'y',
    'n', 'a', 'm', 'i', 'c', 'S', 'c', 'a', 'l', 'a', 'r', 'E', 'x', 'p', 'a',
    'n', 's', 'i', 'o', 'n' };

  char_T c1_u[45];
  const mxArray *c1_d_y = NULL;
  int32_T c1_i39;
  static char_T c1_cv1[21] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T', 'L',
    'A', 'B', ':', 'i', 'n', 'n', 'e', 'r', 'd', 'i', 'm' };

  char_T c1_b_u[21];
  const mxArray *c1_e_y = NULL;
  int32_T c1_i40;
  int32_T c1_m_loop_ub;
  int32_T c1_i41;
  int32_T c1_c_k;
  int32_T c1_i42;
  int32_T c1_b_a_sizes[2];
  int32_T c1_e_a;
  int32_T c1_f_a;
  int32_T c1_n_loop_ub;
  int32_T c1_i43;
  real_T c1_b_a_data[12];
  int32_T c1_b_b_sizes;
  int32_T c1_o_loop_ub;
  int32_T c1_i44;
  real_T c1_b_b_data[4];
  int32_T c1_d_k;
  int32_T c1_b_l;
  int32_T c1_i45;
  int32_T c1_i46;
  int32_T c1_i47;
  int32_T c1_i48;
  real_T c1_b_M[9];
  int32_T c1_i49;
  real_T c1_c_H[3];
  real_T c1_dv6[3];
  int32_T c1_i50;
  int32_T c1_i51;
  int32_T c1_i_x;
  int32_T c1_j_x;
  int32_T c1_p_loop_ub;
  int32_T c1_i52;
  real_T c1_d1;
  int32_T c1_i53;
  int32_T c1_f_i;
  real_T c1_g_a;
  real_T c1_c_b;
  real_T c1_f_y;
  int32_T c1_i54;
  real_T (*c1_b_Hwheel)[4];
  real_T (*c1_b_Hmax)[4];
  real_T (*c1_d_H)[3];
  boolean_T guard1 = FALSE;
  c1_b_Hmax = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
  c1_b_Hwheel = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c1_d_H = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i5 = 0; c1_i5 < 3; c1_i5++) {
    c1_H[c1_i5] = (*c1_d_H)[c1_i5];
  }

  for (c1_i6 = 0; c1_i6 < 4; c1_i6++) {
    c1_Hmax[c1_i6] = (*c1_b_Hmax)[c1_i6];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 25U, 27U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_w1, 0U, c1_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_w2, 1U, c1_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_w3, 2U, c1_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_w4, 3U, c1_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_W, 4U, c1_j_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_m, 5U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_n, 6U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_N, 7U, c1_i_sf_marshallOut,
    c1_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Hm, 8U, c1_h_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_facet, 9U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_i, 10U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_j, 11U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_aux, MAX_uint32_T, c1_g_sf_marshallOut,
    c1_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_facet_aux, 13U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_k, 14U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_l, 15U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c1_aux2_data, (const int32_T *)
    &c1_aux2_sizes, NULL, 0, 16, (void *)c1_f_sf_marshallOut, (void *)
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c1_Hmax_aux_data, (const int32_T *)
    &c1_Hmax_aux_sizes, NULL, 0, 17, (void *)c1_f_sf_marshallOut, (void *)
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_M, 18U, c1_e_sf_marshallOut,
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_sol, 19U, c1_b_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c1_aux_data, (const int32_T *)
    &c1_aux_sizes, NULL, 0, -1, (void *)c1_d_sf_marshallOut, (void *)
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_b_aux, MAX_uint32_T,
    c1_b_sf_marshallOut, c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 20U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 21U, c1_c_sf_marshallOut,
    c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_H, 22U, c1_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_Hmax, 23U, c1_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_Hwheel, 24U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
  for (c1_i7 = 0; c1_i7 < 3; c1_i7++) {
    c1_w1[c1_i7] = -0.57735026918962584;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 5);
  for (c1_i8 = 0; c1_i8 < 3; c1_i8++) {
    c1_w2[c1_i8] = c1_dv1[c1_i8];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
  for (c1_i9 = 0; c1_i9 < 3; c1_i9++) {
    c1_w3[c1_i9] = c1_dv2[c1_i9];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
  for (c1_i10 = 0; c1_i10 < 3; c1_i10++) {
    c1_w4[c1_i10] = c1_dv3[c1_i10];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 8);
  for (c1_i11 = 0; c1_i11 < 12; c1_i11++) {
    c1_W[c1_i11] = c1_dv4[c1_i11];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
  c1_m = 3.0;
  c1_n = 4.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 11);
  for (c1_i12 = 0; c1_i12 < 48; c1_i12++) {
    c1_N[c1_i12] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 12);
  for (c1_i13 = 0; c1_i13 < 16; c1_i13++) {
    c1_Hm[c1_i13] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 13);
  c1_facet = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 14);
  c1_i = 1.0;
  c1_b_i = 0;
  while (c1_b_i < 4) {
    c1_i = 1.0 + (real_T)c1_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 15);
    c1_j = 1.0;
    c1_b_j = 0;
    while (c1_b_j < 4) {
      c1_j = 1.0 + (real_T)c1_b_j;
      CV_EML_FOR(0, 1, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 16);
      c1_c_i = (int32_T)c1_i - 1;
      for (c1_i14 = 0; c1_i14 < 3; c1_i14++) {
        c1_b_W[c1_i14] = c1_W[c1_i14 + 3 * c1_c_i];
      }

      c1_c_j = (int32_T)c1_j - 1;
      for (c1_i15 = 0; c1_i15 < 3; c1_i15++) {
        c1_c_W[c1_i15] = c1_W[c1_i15 + 3 * c1_c_j];
      }

      c1_cross(chartInstance, c1_b_W, c1_c_W, c1_dv5);
      for (c1_i16 = 0; c1_i16 < 3; c1_i16++) {
        c1_b_aux[c1_i16] = c1_dv5[c1_i16];
      }

      _SFD_SYMBOL_SWITCH(12U, 21U);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 17);
      c1_d_j = (int32_T)c1_j - 1;
      c1_d_i = (int32_T)c1_i - 1;
      for (c1_i17 = 0; c1_i17 < 3; c1_i17++) {
        c1_N[(c1_d_i + (c1_d_j << 2)) + (c1_i17 << 4)] = c1_b_aux[c1_i17];
      }

      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 18);
      c1_m = 1.0;
      c1_b_m = 0;
      while (c1_b_m < 4) {
        c1_m = 1.0 + (real_T)c1_b_m;
        CV_EML_FOR(0, 1, 2, 1);
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 19);
        c1_a = c1_Hmax[(int32_T)c1_m - 1];
        c1_c_m = (int32_T)c1_m - 1;
        for (c1_i18 = 0; c1_i18 < 3; c1_i18++) {
          c1_d_W[c1_i18] = c1_W[c1_i18 + 3 * c1_c_m];
        }

        for (c1_i19 = 0; c1_i19 < 3; c1_i19++) {
          c1_c_aux[c1_i19] = c1_b_aux[c1_i19];
        }

        c1_b = c1_abs(chartInstance, c1_dot(chartInstance, c1_d_W, c1_c_aux));
        c1_y = c1_a * c1_b;
        c1_Hm[((int32_T)c1_i + (((int32_T)c1_j - 1) << 2)) - 1] += c1_y;
        c1_b_m++;
        _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
      }

      CV_EML_FOR(0, 1, 2, 0);
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 21);
      if (CV_EML_IF(0, 1, 0, c1_i != c1_j)) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 22);
        c1_b_N[0] = c1_N[((int32_T)c1_i + (((int32_T)c1_j - 1) << 2)) - 1];
        c1_b_N[1] = c1_N[((int32_T)c1_i + (((int32_T)c1_j - 1) << 2)) + 15];
        c1_b_N[2] = c1_N[((int32_T)c1_i + (((int32_T)c1_j - 1) << 2)) + 31];
        for (c1_i20 = 0; c1_i20 < 3; c1_i20++) {
          c1_b_H[c1_i20] = c1_H[c1_i20];
        }

        c1_A = c1_b_dot(chartInstance, c1_b_N, c1_b_H);
        c1_B = c1_Hm[((int32_T)c1_i + (((int32_T)c1_j - 1) << 2)) - 1];
        c1_x = c1_A;
        c1_b_y = c1_B;
        c1_b_x = c1_x;
        c1_c_y = c1_b_y;
        c1_facet_aux = c1_b_x / c1_c_y;
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 23);
        if (CV_EML_IF(0, 1, 1, c1_facet_aux <= c1_facet)) {
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
          c1_facet = c1_facet_aux;
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 25);
          c1_k = c1_i;
          _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 26);
          c1_l = c1_j;
        }
      }

      c1_b_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 1, 0);
    c1_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 33);
  for (c1_i21 = 0; c1_i21 < 4; c1_i21++) {
    c1_aux[c1_i21] = 1.0 + (real_T)c1_i21;
  }

  _SFD_SYMBOL_SWITCH(12U, 12U);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 33);
  for (c1_i22 = 0; c1_i22 < 4; c1_i22++) {
    c1_d_aux[c1_i22] = (c1_aux[c1_i22] != c1_k);
  }

  c1_eml_li_find(chartInstance, c1_d_aux, c1_tmp_data, c1_tmp_sizes);
  c1_aux_sizes[0] = 1;
  c1_aux_sizes[1] = c1_tmp_sizes[1];
  c1_e_aux = c1_aux_sizes[0];
  c1_f_aux = c1_aux_sizes[1];
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i23 = 0; c1_i23 <= c1_loop_ub; c1_i23++) {
    c1_aux_data[c1_i23] = c1_aux[c1_tmp_data[c1_i23] - 1];
  }

  _SFD_SYMBOL_SWITCH(12U, 20U);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 33);
  c1_b_aux_sizes[0] = 1;
  c1_b_aux_sizes[1] = c1_aux_sizes[1];
  c1_g_aux = c1_b_aux_sizes[0];
  c1_h_aux = c1_b_aux_sizes[1];
  c1_b_loop_ub = c1_aux_sizes[0] * c1_aux_sizes[1] - 1;
  for (c1_i24 = 0; c1_i24 <= c1_b_loop_ub; c1_i24++) {
    c1_b_aux_data[c1_i24] = (c1_aux_data[c1_i24] != c1_l);
  }

  c1_b_eml_li_find(chartInstance, c1_b_aux_data, c1_b_aux_sizes, c1_tmp_data,
                   c1_tmp_sizes);
  c1_i_aux = c1_aux_sizes[1];
  c1_j_aux[0] = c1_i_aux;
  c1_k_aux = c1_aux_sizes[1];
  c1_c_aux_sizes[0] = 1;
  c1_c_aux_sizes[1] = c1_tmp_sizes[1];
  c1_c_loop_ub = c1_tmp_sizes[1] - 1;
  for (c1_i25 = 0; c1_i25 <= c1_c_loop_ub; c1_i25++) {
    c1_c_aux_data[c1_c_aux_sizes[0] * c1_i25] =
      c1_aux_data[_SFD_EML_ARRAY_BOUNDS_CHECK("aux", c1_tmp_data[c1_tmp_sizes[0]
      * c1_i25], 1, c1_k_aux, 1, 0) - 1];
  }

  c1_aux_sizes[0] = 1;
  c1_aux_sizes[1] = c1_c_aux_sizes[1];
  c1_d_loop_ub = c1_c_aux_sizes[1] - 1;
  for (c1_i26 = 0; c1_i26 <= c1_d_loop_ub; c1_i26++) {
    c1_aux_data[c1_aux_sizes[0] * c1_i26] = c1_c_aux_data[c1_c_aux_sizes[0] *
      c1_i26];
  }

  _SFD_SYMBOL_SWITCH(12U, 20U);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 34);
  c1_x_sizes[0] = 1;
  c1_x_sizes[1] = c1_aux_sizes[1];
  c1_c_x = c1_x_sizes[0];
  c1_d_x = c1_x_sizes[1];
  c1_e_loop_ub = c1_aux_sizes[0] * c1_aux_sizes[1] - 1;
  for (c1_i27 = 0; c1_i27 <= c1_e_loop_ub; c1_i27++) {
    c1_x_data[c1_i27] = c1_aux_data[c1_i27];
  }

  c1_b_n = (real_T)c1_x_sizes[1];
  c1_aux2_sizes = (int32_T)c1_b_n;
  c1_f_loop_ub = (int32_T)c1_b_n - 1;
  for (c1_i28 = 0; c1_i28 <= c1_f_loop_ub; c1_i28++) {
    c1_aux2_data[c1_i28] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 35);
  c1_x_sizes[0] = 1;
  c1_x_sizes[1] = c1_aux_sizes[1];
  c1_e_x = c1_x_sizes[0];
  c1_f_x = c1_x_sizes[1];
  c1_g_loop_ub = c1_aux_sizes[0] * c1_aux_sizes[1] - 1;
  for (c1_i29 = 0; c1_i29 <= c1_g_loop_ub; c1_i29++) {
    c1_x_data[c1_i29] = c1_aux_data[c1_i29];
  }

  c1_d0 = (real_T)c1_x_sizes[1];
  c1_i30 = (int32_T)c1_d0 - 1;
  c1_i = 1.0;
  c1_e_i = 0;
  while (c1_e_i <= c1_i30) {
    c1_i = 1.0 + (real_T)c1_e_i;
    CV_EML_FOR(0, 1, 3, 1);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 36);
    c1_l_aux[0] = c1_aux_sizes[1];
    c1_m_aux = (int32_T)c1_aux_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK
      ("aux", (int32_T)c1_i, 1, c1_aux_sizes[1], 1, 0) - 1] - 1;
    for (c1_i31 = 0; c1_i31 < 3; c1_i31++) {
      c1_b_a[c1_i31] = c1_W[c1_i31 + 3 * c1_m_aux];
    }

    c1_b_b[0] = c1_N[((int32_T)c1_k + (((int32_T)c1_l - 1) << 2)) - 1];
    c1_b_b[1] = c1_N[((int32_T)c1_k + (((int32_T)c1_l - 1) << 2)) + 15];
    c1_b_b[2] = c1_N[((int32_T)c1_k + (((int32_T)c1_l - 1) << 2)) + 31];
    c1_c_eml_scalar_eg(chartInstance);
    c1_c_eml_scalar_eg(chartInstance);
    c1_c = 0.0;
    c1_ix = 1;
    c1_iy = 1;
    for (c1_b_k = 1; c1_b_k < 4; c1_b_k++) {
      c1_c += c1_b_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_ix, 1, 3, 1, 0) - 1] *
        c1_b_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_iy, 1, 3, 1, 0) - 1];
      c1_c_a = c1_ix + 1;
      c1_ix = c1_c_a;
      c1_d_a = c1_iy + 1;
      c1_iy = c1_d_a;
    }

    c1_g_x = c1_c;
    c1_h_x = c1_g_x;
    c1_h_x = muDoubleScalarSign(c1_h_x);
    c1_aux2_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("aux2", (int32_T)
      c1_i, 1, c1_aux2_sizes, 1, 0) - 1] = c1_h_x;
    c1_e_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 3, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 38);
  c1_d_aux_sizes[0] = 1;
  c1_d_aux_sizes[1] = c1_aux_sizes[1];
  c1_h_loop_ub = c1_aux_sizes[1] - 1;
  for (c1_i32 = 0; c1_i32 <= c1_h_loop_ub; c1_i32++) {
    c1_d_aux_data[c1_d_aux_sizes[0] * c1_i32] = (int32_T)
      c1_aux_data[c1_aux_sizes[0] * c1_i32];
  }

  c1_b_sizes = c1_d_aux_sizes[1];
  c1_i_loop_ub = c1_d_aux_sizes[1] - 1;
  for (c1_i33 = 0; c1_i33 <= c1_i_loop_ub; c1_i33++) {
    c1_b_data[c1_i33] = c1_Hmax[(int32_T)c1_aux_data[c1_i33] - 1];
  }

  _SFD_SIZE_EQ_CHECK_1D(c1_aux2_sizes, c1_b_sizes);
  c1_Hmax_aux_sizes = c1_aux2_sizes;
  c1_j_loop_ub = c1_aux2_sizes - 1;
  for (c1_i34 = 0; c1_i34 <= c1_j_loop_ub; c1_i34++) {
    c1_Hmax_aux_data[c1_i34] = c1_aux2_data[c1_i34] * c1_b_data[c1_i34];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 41);
  c1_n_aux[0] = c1_aux_sizes[1];
  c1_a_sizes[0] = 3;
  c1_a_sizes[1] = c1_n_aux[0];
  c1_k_loop_ub = c1_n_aux[0] - 1;
  for (c1_i35 = 0; c1_i35 <= c1_k_loop_ub; c1_i35++) {
    for (c1_i36 = 0; c1_i36 < 3; c1_i36++) {
      c1_a_data[c1_i36 + c1_a_sizes[0] * c1_i35] = c1_W[c1_i36 + 3 * ((int32_T)
        c1_aux_data[c1_i35] - 1)];
    }
  }

  c1_b_sizes = c1_Hmax_aux_sizes;
  c1_l_loop_ub = c1_Hmax_aux_sizes - 1;
  for (c1_i37 = 0; c1_i37 <= c1_l_loop_ub; c1_i37++) {
    c1_b_data[c1_i37] = c1_Hmax_aux_data[c1_i37];
  }

  c1_innerDimOk = ((real_T)c1_a_sizes[1] == (real_T)c1_b_sizes);
  if (!c1_innerDimOk) {
    if (c1_b_sizes == 1) {
      for (c1_i38 = 0; c1_i38 < 45; c1_i38++) {
        c1_u[c1_i38] = c1_cv0[c1_i38];
      }

      c1_d_y = NULL;
      sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 45),
                    FALSE);
      sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
        14, c1_d_y));
    } else {
      for (c1_i39 = 0; c1_i39 < 21; c1_i39++) {
        c1_b_u[c1_i39] = c1_cv1[c1_i39];
      }

      c1_e_y = NULL;
      sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_b_u, 10, 0U, 1U, 0U, 2, 1, 21),
                    FALSE);
      sf_mex_call_debug("error", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
        14, c1_e_y));
    }
  }

  guard1 = FALSE;
  if ((real_T)c1_a_sizes[1] == 1.0) {
    guard1 = TRUE;
  } else if ((real_T)c1_b_sizes == 1.0) {
    guard1 = TRUE;
  } else {
    c1_c_k = (int32_T)(real_T)c1_a_sizes[1];
    c1_d_eml_scalar_eg(chartInstance);
    c1_d_eml_scalar_eg(chartInstance);
    for (c1_i42 = 0; c1_i42 < 3; c1_i42++) {
      c1_b_a[c1_i42] = 0.0;
    }

    c1_b_a_sizes[0] = 3;
    c1_b_a_sizes[1] = c1_a_sizes[1];
    c1_e_a = c1_b_a_sizes[0];
    c1_f_a = c1_b_a_sizes[1];
    c1_n_loop_ub = c1_a_sizes[0] * c1_a_sizes[1] - 1;
    for (c1_i43 = 0; c1_i43 <= c1_n_loop_ub; c1_i43++) {
      c1_b_a_data[c1_i43] = c1_a_data[c1_i43];
    }

    c1_b_b_sizes = c1_b_sizes;
    c1_o_loop_ub = c1_b_sizes - 1;
    for (c1_i44 = 0; c1_i44 <= c1_o_loop_ub; c1_i44++) {
      c1_b_b_data[c1_i44] = c1_b_data[c1_i44];
    }

    c1_b_eml_xgemm(chartInstance, c1_c_k, c1_b_a_data, c1_b_a_sizes, c1_b_b_data,
                   *(int32_T (*)[1])&c1_b_b_sizes, c1_c_k, c1_b_a);
  }

  if (guard1 == TRUE) {
    for (c1_i40 = 0; c1_i40 < 3; c1_i40++) {
      c1_b_a[c1_i40] = 0.0;
      c1_m_loop_ub = c1_a_sizes[1] - 1;
      for (c1_i41 = 0; c1_i41 <= c1_m_loop_ub; c1_i41++) {
        c1_b_a[c1_i40] += c1_a_data[c1_i40 + c1_a_sizes[0] * c1_i41] *
          c1_b_data[c1_i41];
      }
    }
  }

  c1_d_k = (int32_T)c1_k - 1;
  c1_b_l = (int32_T)c1_l - 1;
  for (c1_i45 = 0; c1_i45 < 3; c1_i45++) {
    c1_M[c1_i45] = c1_W[c1_i45 + 3 * c1_d_k];
  }

  for (c1_i46 = 0; c1_i46 < 3; c1_i46++) {
    c1_M[3 + c1_i46] = c1_W[c1_i46 + 3 * c1_b_l];
  }

  for (c1_i47 = 0; c1_i47 < 3; c1_i47++) {
    c1_M[c1_i47 + 6] = c1_b_a[c1_i47];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 42);
  for (c1_i48 = 0; c1_i48 < 9; c1_i48++) {
    c1_b_M[c1_i48] = c1_M[c1_i48];
  }

  for (c1_i49 = 0; c1_i49 < 3; c1_i49++) {
    c1_c_H[c1_i49] = c1_H[c1_i49];
  }

  c1_mldivide(chartInstance, c1_b_M, c1_c_H, c1_dv6);
  for (c1_i50 = 0; c1_i50 < 3; c1_i50++) {
    c1_sol[c1_i50] = c1_dv6[c1_i50];
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 45);
  for (c1_i51 = 0; c1_i51 < 4; c1_i51++) {
    c1_Hwheel[c1_i51] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 46);
  c1_Hwheel[(int32_T)c1_k - 1] = c1_sol[0];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 47);
  c1_Hwheel[(int32_T)c1_l - 1] = c1_sol[1];
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 48);
  c1_x_sizes[0] = 1;
  c1_x_sizes[1] = c1_aux_sizes[1];
  c1_i_x = c1_x_sizes[0];
  c1_j_x = c1_x_sizes[1];
  c1_p_loop_ub = c1_aux_sizes[0] * c1_aux_sizes[1] - 1;
  for (c1_i52 = 0; c1_i52 <= c1_p_loop_ub; c1_i52++) {
    c1_x_data[c1_i52] = c1_aux_data[c1_i52];
  }

  c1_d1 = (real_T)c1_x_sizes[1];
  c1_i53 = (int32_T)c1_d1 - 1;
  c1_i = 1.0;
  c1_f_i = 0;
  while (c1_f_i <= c1_i53) {
    c1_i = 1.0 + (real_T)c1_f_i;
    CV_EML_FOR(0, 1, 4, 1);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 49);
    c1_g_a = c1_sol[2];
    c1_c_b = c1_Hmax_aux_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
      "Hmax_aux", (int32_T)c1_i, 1, c1_Hmax_aux_sizes, 1, 0) - 1];
    c1_f_y = c1_g_a * c1_c_b;
    c1_Hwheel[(int32_T)c1_aux_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK(
      "aux", (int32_T)c1_i, 1, c1_aux_sizes[1], 1, 0) - 1] - 1] = c1_f_y;
    c1_f_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 4, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -49);
  _SFD_SYMBOL_SCOPE_POP();
  for (c1_i54 = 0; c1_i54 < 4; c1_i54++) {
    (*c1_b_Hwheel)[c1_i54] = c1_Hwheel[c1_i54];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_modelo(SFc1_modeloInstanceStruct *chartInstance)
{
}

static void registerMessagesc1_modelo(SFc1_modeloInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i55;
  real_T c1_b_inData[4];
  int32_T c1_i56;
  real_T c1_u[4];
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i55 = 0; c1_i55 < 4; c1_i55++) {
    c1_b_inData[c1_i55] = (*(real_T (*)[4])c1_inData)[c1_i55];
  }

  for (c1_i56 = 0; c1_i56 < 4; c1_i56++) {
    c1_u[c1_i56] = c1_b_inData[c1_i56];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance, const
  mxArray *c1_Hwheel, const char_T *c1_identifier, real_T c1_y[4])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Hwheel), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_Hwheel);
}

static void c1_b_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[4])
{
  real_T c1_dv7[4];
  int32_T c1_i57;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv7, 1, 0, 0U, 1, 0U, 1, 4);
  for (c1_i57 = 0; c1_i57 < 4; c1_i57++) {
    c1_y[c1_i57] = c1_dv7[c1_i57];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_Hwheel;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[4];
  int32_T c1_i58;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_Hwheel = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Hwheel), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_Hwheel);
  for (c1_i58 = 0; c1_i58 < 4; c1_i58++) {
    (*(real_T (*)[4])c1_outData)[c1_i58] = c1_y[c1_i58];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i59;
  real_T c1_b_inData[3];
  int32_T c1_i60;
  real_T c1_u[3];
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i59 = 0; c1_i59 < 3; c1_i59++) {
    c1_b_inData[c1_i59] = (*(real_T (*)[3])c1_inData)[c1_i59];
  }

  for (c1_i60 = 0; c1_i60 < 3; c1_i60++) {
    c1_u[c1_i60] = c1_b_inData[c1_i60];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_c_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d2;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d2, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d2;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nargout;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_nargout = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nargout), &c1_thisId);
  sf_mex_destroy(&c1_nargout);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static void c1_d_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[3])
{
  real_T c1_dv8[3];
  int32_T c1_i61;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv8, 1, 0, 0U, 1, 0U, 1, 3);
  for (c1_i61 = 0; c1_i61 < 3; c1_i61++) {
    c1_y[c1_i61] = c1_dv8[c1_i61];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_aux;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[3];
  int32_T c1_i62;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_aux = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_aux), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_aux);
  for (c1_i62 = 0; c1_i62 < 3; c1_i62++) {
    (*(real_T (*)[3])c1_outData)[c1_i62] = c1_y[c1_i62];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[4], int32_T c1_inData_sizes[2])
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_b_inData_sizes[2];
  int32_T c1_loop_ub;
  int32_T c1_i63;
  real_T c1_b_inData_data[4];
  int32_T c1_u_sizes[2];
  int32_T c1_b_loop_ub;
  int32_T c1_i64;
  real_T c1_u_data[4];
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_b_inData_sizes[0] = 1;
  c1_b_inData_sizes[1] = c1_inData_sizes[1];
  c1_loop_ub = c1_inData_sizes[1] - 1;
  for (c1_i63 = 0; c1_i63 <= c1_loop_ub; c1_i63++) {
    c1_b_inData_data[c1_b_inData_sizes[0] * c1_i63] =
      c1_inData_data[c1_inData_sizes[0] * c1_i63];
  }

  c1_u_sizes[0] = 1;
  c1_u_sizes[1] = c1_b_inData_sizes[1];
  c1_b_loop_ub = c1_b_inData_sizes[1] - 1;
  for (c1_i64 = 0; c1_i64 <= c1_b_loop_ub; c1_i64++) {
    c1_u_data[c1_u_sizes[0] * c1_i64] = c1_b_inData_data[c1_b_inData_sizes[0] *
      c1_i64];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u_data, 0, 0U, 1U, 0U, 2,
    c1_u_sizes[0], c1_u_sizes[1]), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_e_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y_data[4],
  int32_T c1_y_sizes[2])
{
  int32_T c1_i65;
  uint32_T c1_uv0[2];
  int32_T c1_i66;
  static boolean_T c1_bv0[2] = { FALSE, TRUE };

  boolean_T c1_bv1[2];
  int32_T c1_tmp_sizes[2];
  real_T c1_tmp_data[4];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i67;
  for (c1_i65 = 0; c1_i65 < 2; c1_i65++) {
    c1_uv0[c1_i65] = 1U + 3U * (uint32_T)c1_i65;
  }

  for (c1_i66 = 0; c1_i66 < 2; c1_i66++) {
    c1_bv1[c1_i66] = c1_bv0[c1_i66];
  }

  sf_mex_import_vs(c1_parentId, sf_mex_dup(c1_u), c1_tmp_data, 1, 0, 0U, 1, 0U,
                   2, c1_bv1, c1_uv0, c1_tmp_sizes);
  c1_y_sizes[0] = 1;
  c1_y_sizes[1] = c1_tmp_sizes[1];
  c1_y = c1_y_sizes[0];
  c1_b_y = c1_y_sizes[1];
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i67 = 0; c1_i67 <= c1_loop_ub; c1_i67++) {
    c1_y_data[c1_i67] = c1_tmp_data[c1_i67];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[4],
  int32_T c1_outData_sizes[2])
{
  const mxArray *c1_aux;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y_sizes[2];
  real_T c1_y_data[4];
  int32_T c1_loop_ub;
  int32_T c1_i68;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_aux = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_aux), &c1_thisId, c1_y_data,
                        c1_y_sizes);
  sf_mex_destroy(&c1_aux);
  c1_outData_sizes[0] = 1;
  c1_outData_sizes[1] = c1_y_sizes[1];
  c1_loop_ub = c1_y_sizes[1] - 1;
  for (c1_i68 = 0; c1_i68 <= c1_loop_ub; c1_i68++) {
    c1_outData_data[c1_outData_sizes[0] * c1_i68] = c1_y_data[c1_y_sizes[0] *
      c1_i68];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i69;
  int32_T c1_i70;
  int32_T c1_i71;
  real_T c1_b_inData[9];
  int32_T c1_i72;
  int32_T c1_i73;
  int32_T c1_i74;
  real_T c1_u[9];
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i69 = 0;
  for (c1_i70 = 0; c1_i70 < 3; c1_i70++) {
    for (c1_i71 = 0; c1_i71 < 3; c1_i71++) {
      c1_b_inData[c1_i71 + c1_i69] = (*(real_T (*)[9])c1_inData)[c1_i71 + c1_i69];
    }

    c1_i69 += 3;
  }

  c1_i72 = 0;
  for (c1_i73 = 0; c1_i73 < 3; c1_i73++) {
    for (c1_i74 = 0; c1_i74 < 3; c1_i74++) {
      c1_u[c1_i74 + c1_i72] = c1_b_inData[c1_i74 + c1_i72];
    }

    c1_i72 += 3;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_f_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[9])
{
  real_T c1_dv9[9];
  int32_T c1_i75;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv9, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c1_i75 = 0; c1_i75 < 9; c1_i75++) {
    c1_y[c1_i75] = c1_dv9[c1_i75];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_M;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[9];
  int32_T c1_i76;
  int32_T c1_i77;
  int32_T c1_i78;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_M = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_M), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_M);
  c1_i76 = 0;
  for (c1_i77 = 0; c1_i77 < 3; c1_i77++) {
    for (c1_i78 = 0; c1_i78 < 3; c1_i78++) {
      (*(real_T (*)[9])c1_outData)[c1_i78 + c1_i76] = c1_y[c1_i78 + c1_i76];
    }

    c1_i76 += 3;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[4], int32_T c1_inData_sizes[1])
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_b_inData_sizes;
  int32_T c1_loop_ub;
  int32_T c1_i79;
  real_T c1_b_inData_data[4];
  int32_T c1_u_sizes;
  int32_T c1_b_loop_ub;
  int32_T c1_i80;
  real_T c1_u_data[4];
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_b_inData_sizes = c1_inData_sizes[0];
  c1_loop_ub = c1_inData_sizes[0] - 1;
  for (c1_i79 = 0; c1_i79 <= c1_loop_ub; c1_i79++) {
    c1_b_inData_data[c1_i79] = c1_inData_data[c1_i79];
  }

  c1_u_sizes = c1_b_inData_sizes;
  c1_b_loop_ub = c1_b_inData_sizes - 1;
  for (c1_i80 = 0; c1_i80 <= c1_b_loop_ub; c1_i80++) {
    c1_u_data[c1_i80] = c1_b_inData_data[c1_i80];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u_data, 0, 0U, 1U, 0U, 1,
    c1_u_sizes), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_g_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y_data[4],
  int32_T c1_y_sizes[1])
{
  static uint32_T c1_uv1[1] = { 4U };

  uint32_T c1_uv2[1];
  static boolean_T c1_bv2[1] = { TRUE };

  boolean_T c1_bv3[1];
  int32_T c1_tmp_sizes;
  real_T c1_tmp_data[4];
  int32_T c1_loop_ub;
  int32_T c1_i81;
  c1_uv2[0] = c1_uv1[0];
  c1_bv3[0] = c1_bv2[0];
  sf_mex_import_vs(c1_parentId, sf_mex_dup(c1_u), c1_tmp_data, 1, 0, 0U, 1, 0U,
                   1, c1_bv3, c1_uv2, &c1_tmp_sizes);
  c1_y_sizes[0] = c1_tmp_sizes;
  c1_loop_ub = c1_tmp_sizes - 1;
  for (c1_i81 = 0; c1_i81 <= c1_loop_ub; c1_i81++) {
    c1_y_data[c1_i81] = c1_tmp_data[c1_i81];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[4],
  int32_T c1_outData_sizes[1])
{
  const mxArray *c1_Hmax_aux;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y_sizes;
  real_T c1_y_data[4];
  int32_T c1_loop_ub;
  int32_T c1_i82;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_Hmax_aux = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Hmax_aux), &c1_thisId,
                        c1_y_data, *(int32_T (*)[1])&c1_y_sizes);
  sf_mex_destroy(&c1_Hmax_aux);
  c1_outData_sizes[0] = c1_y_sizes;
  c1_loop_ub = c1_y_sizes - 1;
  for (c1_i82 = 0; c1_i82 <= c1_loop_ub; c1_i82++) {
    c1_outData_data[c1_i82] = c1_y_data[c1_i82];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i83;
  real_T c1_b_inData[4];
  int32_T c1_i84;
  real_T c1_u[4];
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i83 = 0; c1_i83 < 4; c1_i83++) {
    c1_b_inData[c1_i83] = (*(real_T (*)[4])c1_inData)[c1_i83];
  }

  for (c1_i84 = 0; c1_i84 < 4; c1_i84++) {
    c1_u[c1_i84] = c1_b_inData[c1_i84];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 4), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_h_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[4])
{
  real_T c1_dv10[4];
  int32_T c1_i85;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv10, 1, 0, 0U, 1, 0U, 2, 1, 4);
  for (c1_i85 = 0; c1_i85 < 4; c1_i85++) {
    c1_y[c1_i85] = c1_dv10[c1_i85];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_aux;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[4];
  int32_T c1_i86;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_aux = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_aux), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_aux);
  for (c1_i86 = 0; c1_i86 < 4; c1_i86++) {
    (*(real_T (*)[4])c1_outData)[c1_i86] = c1_y[c1_i86];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i87;
  int32_T c1_i88;
  int32_T c1_i89;
  real_T c1_b_inData[16];
  int32_T c1_i90;
  int32_T c1_i91;
  int32_T c1_i92;
  real_T c1_u[16];
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i87 = 0;
  for (c1_i88 = 0; c1_i88 < 4; c1_i88++) {
    for (c1_i89 = 0; c1_i89 < 4; c1_i89++) {
      c1_b_inData[c1_i89 + c1_i87] = (*(real_T (*)[16])c1_inData)[c1_i89 +
        c1_i87];
    }

    c1_i87 += 4;
  }

  c1_i90 = 0;
  for (c1_i91 = 0; c1_i91 < 4; c1_i91++) {
    for (c1_i92 = 0; c1_i92 < 4; c1_i92++) {
      c1_u[c1_i92 + c1_i90] = c1_b_inData[c1_i92 + c1_i90];
    }

    c1_i90 += 4;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 4, 4), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_i_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[16])
{
  real_T c1_dv11[16];
  int32_T c1_i93;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv11, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c1_i93 = 0; c1_i93 < 16; c1_i93++) {
    c1_y[c1_i93] = c1_dv11[c1_i93];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_Hm;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[16];
  int32_T c1_i94;
  int32_T c1_i95;
  int32_T c1_i96;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_Hm = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_Hm), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_Hm);
  c1_i94 = 0;
  for (c1_i95 = 0; c1_i95 < 4; c1_i95++) {
    for (c1_i96 = 0; c1_i96 < 4; c1_i96++) {
      (*(real_T (*)[16])c1_outData)[c1_i96 + c1_i94] = c1_y[c1_i96 + c1_i94];
    }

    c1_i94 += 4;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i97;
  int32_T c1_i98;
  int32_T c1_i99;
  int32_T c1_i100;
  int32_T c1_i101;
  real_T c1_b_inData[48];
  int32_T c1_i102;
  int32_T c1_i103;
  int32_T c1_i104;
  int32_T c1_i105;
  int32_T c1_i106;
  real_T c1_u[48];
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i97 = 0;
  for (c1_i98 = 0; c1_i98 < 3; c1_i98++) {
    c1_i99 = 0;
    for (c1_i100 = 0; c1_i100 < 4; c1_i100++) {
      for (c1_i101 = 0; c1_i101 < 4; c1_i101++) {
        c1_b_inData[(c1_i101 + c1_i99) + c1_i97] = (*(real_T (*)[48])c1_inData)
          [(c1_i101 + c1_i99) + c1_i97];
      }

      c1_i99 += 4;
    }

    c1_i97 += 16;
  }

  c1_i102 = 0;
  for (c1_i103 = 0; c1_i103 < 3; c1_i103++) {
    c1_i104 = 0;
    for (c1_i105 = 0; c1_i105 < 4; c1_i105++) {
      for (c1_i106 = 0; c1_i106 < 4; c1_i106++) {
        c1_u[(c1_i106 + c1_i104) + c1_i102] = c1_b_inData[(c1_i106 + c1_i104) +
          c1_i102];
      }

      c1_i104 += 4;
    }

    c1_i102 += 16;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 3, 4, 4, 3),
                FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_j_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[48])
{
  real_T c1_dv12[48];
  int32_T c1_i107;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv12, 1, 0, 0U, 1, 0U, 3, 4, 4,
                3);
  for (c1_i107 = 0; c1_i107 < 48; c1_i107++) {
    c1_y[c1_i107] = c1_dv12[c1_i107];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_N;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[48];
  int32_T c1_i108;
  int32_T c1_i109;
  int32_T c1_i110;
  int32_T c1_i111;
  int32_T c1_i112;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_N = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_N), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_N);
  c1_i108 = 0;
  for (c1_i109 = 0; c1_i109 < 3; c1_i109++) {
    c1_i110 = 0;
    for (c1_i111 = 0; c1_i111 < 4; c1_i111++) {
      for (c1_i112 = 0; c1_i112 < 4; c1_i112++) {
        (*(real_T (*)[48])c1_outData)[(c1_i112 + c1_i110) + c1_i108] = c1_y
          [(c1_i112 + c1_i110) + c1_i108];
      }

      c1_i110 += 4;
    }

    c1_i108 += 16;
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i113;
  int32_T c1_i114;
  int32_T c1_i115;
  real_T c1_b_inData[12];
  int32_T c1_i116;
  int32_T c1_i117;
  int32_T c1_i118;
  real_T c1_u[12];
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_i113 = 0;
  for (c1_i114 = 0; c1_i114 < 4; c1_i114++) {
    for (c1_i115 = 0; c1_i115 < 3; c1_i115++) {
      c1_b_inData[c1_i115 + c1_i113] = (*(real_T (*)[12])c1_inData)[c1_i115 +
        c1_i113];
    }

    c1_i113 += 3;
  }

  c1_i116 = 0;
  for (c1_i117 = 0; c1_i117 < 4; c1_i117++) {
    for (c1_i118 = 0; c1_i118 < 3; c1_i118++) {
      c1_u[c1_i118 + c1_i116] = c1_b_inData[c1_i118 + c1_i116];
    }

    c1_i116 += 3;
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 3, 4), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_k_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i119;
  real_T c1_b_inData[3];
  int32_T c1_i120;
  real_T c1_u[3];
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i119 = 0; c1_i119 < 3; c1_i119++) {
    c1_b_inData[c1_i119] = (*(real_T (*)[3])c1_inData)[c1_i119];
  }

  for (c1_i120 = 0; c1_i120 < 3; c1_i120++) {
    c1_u[c1_i120] = c1_b_inData[c1_i120];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

const mxArray *sf_c1_modelo_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo;
  c1_ResolvedFunctionInfo c1_info[96];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i121;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  c1_b_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 96), FALSE);
  for (c1_i121 = 0; c1_i121 < 96; c1_i121++) {
    c1_r0 = &c1_info[c1_i121];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context", "nameCaptureInfo",
                    c1_i121);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name", "nameCaptureInfo", c1_i121);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c1_i121);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved", "nameCaptureInfo",
                    c1_i121);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c1_i121);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c1_i121);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c1_i121);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c1_i121);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[96])
{
  c1_info[0].context = "";
  c1_info[0].name = "sqrt";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[0].fileTimeLo = 1343848386U;
  c1_info[0].fileTimeHi = 0U;
  c1_info[0].mFileTimeLo = 0U;
  c1_info[0].mFileTimeHi = 0U;
  c1_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[1].name = "eml_error";
  c1_info[1].dominantType = "char";
  c1_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c1_info[1].fileTimeLo = 1343848358U;
  c1_info[1].fileTimeHi = 0U;
  c1_info[1].mFileTimeLo = 0U;
  c1_info[1].mFileTimeHi = 0U;
  c1_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c1_info[2].name = "eml_scalar_sqrt";
  c1_info[2].dominantType = "double";
  c1_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c1_info[2].fileTimeLo = 1286836738U;
  c1_info[2].fileTimeHi = 0U;
  c1_info[2].mFileTimeLo = 0U;
  c1_info[2].mFileTimeHi = 0U;
  c1_info[3].context = "";
  c1_info[3].name = "mrdivide";
  c1_info[3].dominantType = "double";
  c1_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[3].fileTimeLo = 1357962348U;
  c1_info[3].fileTimeHi = 0U;
  c1_info[3].mFileTimeLo = 1319744366U;
  c1_info[3].mFileTimeHi = 0U;
  c1_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[4].name = "rdivide";
  c1_info[4].dominantType = "double";
  c1_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[4].fileTimeLo = 1346528388U;
  c1_info[4].fileTimeHi = 0U;
  c1_info[4].mFileTimeLo = 0U;
  c1_info[4].mFileTimeHi = 0U;
  c1_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[5].name = "eml_scalexp_compatible";
  c1_info[5].dominantType = "double";
  c1_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c1_info[5].fileTimeLo = 1286836796U;
  c1_info[5].fileTimeHi = 0U;
  c1_info[5].mFileTimeLo = 0U;
  c1_info[5].mFileTimeHi = 0U;
  c1_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c1_info[6].name = "eml_div";
  c1_info[6].dominantType = "double";
  c1_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[6].fileTimeLo = 1313365810U;
  c1_info[6].fileTimeHi = 0U;
  c1_info[6].mFileTimeLo = 0U;
  c1_info[6].mFileTimeHi = 0U;
  c1_info[7].context = "";
  c1_info[7].name = "cross";
  c1_info[7].dominantType = "double";
  c1_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c1_info[7].fileTimeLo = 1286836842U;
  c1_info[7].fileTimeHi = 0U;
  c1_info[7].mFileTimeLo = 0U;
  c1_info[7].mFileTimeHi = 0U;
  c1_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c1_info[8].name = "mtimes";
  c1_info[8].dominantType = "double";
  c1_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[8].fileTimeLo = 1289530492U;
  c1_info[8].fileTimeHi = 0U;
  c1_info[8].mFileTimeLo = 0U;
  c1_info[8].mFileTimeHi = 0U;
  c1_info[9].context = "";
  c1_info[9].name = "dot";
  c1_info[9].dominantType = "double";
  c1_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c1_info[9].fileTimeLo = 1313365816U;
  c1_info[9].fileTimeHi = 0U;
  c1_info[9].mFileTimeLo = 0U;
  c1_info[9].mFileTimeHi = 0U;
  c1_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c1_info[10].name = "isequal";
  c1_info[10].dominantType = "double";
  c1_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c1_info[10].fileTimeLo = 1286836758U;
  c1_info[10].fileTimeHi = 0U;
  c1_info[10].mFileTimeLo = 0U;
  c1_info[10].mFileTimeHi = 0U;
  c1_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c1_info[11].name = "eml_isequal_core";
  c1_info[11].dominantType = "double";
  c1_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c1_info[11].fileTimeLo = 1286836786U;
  c1_info[11].fileTimeHi = 0U;
  c1_info[11].mFileTimeLo = 0U;
  c1_info[11].mFileTimeHi = 0U;
  c1_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c1_info[12].name = "isnan";
  c1_info[12].dominantType = "double";
  c1_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c1_info[12].fileTimeLo = 1286836760U;
  c1_info[12].fileTimeHi = 0U;
  c1_info[12].mFileTimeLo = 0U;
  c1_info[12].mFileTimeHi = 0U;
  c1_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c1_info[13].name = "eml_index_class";
  c1_info[13].dominantType = "";
  c1_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[13].fileTimeLo = 1323181378U;
  c1_info[13].fileTimeHi = 0U;
  c1_info[13].mFileTimeLo = 0U;
  c1_info[13].mFileTimeHi = 0U;
  c1_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c1_info[14].name = "eml_scalar_eg";
  c1_info[14].dominantType = "double";
  c1_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[14].fileTimeLo = 1286836796U;
  c1_info[14].fileTimeHi = 0U;
  c1_info[14].mFileTimeLo = 0U;
  c1_info[14].mFileTimeHi = 0U;
  c1_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m!vdot";
  c1_info[15].name = "eml_xdotc";
  c1_info[15].dominantType = "double";
  c1_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c1_info[15].fileTimeLo = 1299087572U;
  c1_info[15].fileTimeHi = 0U;
  c1_info[15].mFileTimeLo = 0U;
  c1_info[15].mFileTimeHi = 0U;
  c1_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c1_info[16].name = "eml_blas_inline";
  c1_info[16].dominantType = "";
  c1_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c1_info[16].fileTimeLo = 1299087568U;
  c1_info[16].fileTimeHi = 0U;
  c1_info[16].mFileTimeLo = 0U;
  c1_info[16].mFileTimeHi = 0U;
  c1_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c1_info[17].name = "eml_xdot";
  c1_info[17].dominantType = "double";
  c1_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c1_info[17].fileTimeLo = 1299087572U;
  c1_info[17].fileTimeHi = 0U;
  c1_info[17].mFileTimeLo = 0U;
  c1_info[17].mFileTimeHi = 0U;
  c1_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c1_info[18].name = "eml_blas_inline";
  c1_info[18].dominantType = "";
  c1_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c1_info[18].fileTimeLo = 1299087568U;
  c1_info[18].fileTimeHi = 0U;
  c1_info[18].mFileTimeLo = 0U;
  c1_info[18].mFileTimeHi = 0U;
  c1_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m!below_threshold";
  c1_info[19].name = "length";
  c1_info[19].dominantType = "double";
  c1_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c1_info[19].fileTimeLo = 1303164206U;
  c1_info[19].fileTimeHi = 0U;
  c1_info[19].mFileTimeLo = 0U;
  c1_info[19].mFileTimeHi = 0U;
  c1_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c1_info[20].name = "eml_index_class";
  c1_info[20].dominantType = "";
  c1_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[20].fileTimeLo = 1323181378U;
  c1_info[20].fileTimeHi = 0U;
  c1_info[20].mFileTimeLo = 0U;
  c1_info[20].mFileTimeHi = 0U;
  c1_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c1_info[21].name = "eml_refblas_xdot";
  c1_info[21].dominantType = "double";
  c1_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c1_info[21].fileTimeLo = 1299087572U;
  c1_info[21].fileTimeHi = 0U;
  c1_info[21].mFileTimeLo = 0U;
  c1_info[21].mFileTimeHi = 0U;
  c1_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c1_info[22].name = "eml_refblas_xdotx";
  c1_info[22].dominantType = "char";
  c1_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[22].fileTimeLo = 1299087574U;
  c1_info[22].fileTimeHi = 0U;
  c1_info[22].mFileTimeLo = 0U;
  c1_info[22].mFileTimeHi = 0U;
  c1_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[23].name = "eml_scalar_eg";
  c1_info[23].dominantType = "double";
  c1_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[23].fileTimeLo = 1286836796U;
  c1_info[23].fileTimeHi = 0U;
  c1_info[23].mFileTimeLo = 0U;
  c1_info[23].mFileTimeHi = 0U;
  c1_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[24].name = "eml_index_class";
  c1_info[24].dominantType = "";
  c1_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[24].fileTimeLo = 1323181378U;
  c1_info[24].fileTimeHi = 0U;
  c1_info[24].mFileTimeLo = 0U;
  c1_info[24].mFileTimeHi = 0U;
  c1_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[25].name = "eml_int_forloop_overflow_check";
  c1_info[25].dominantType = "";
  c1_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[25].fileTimeLo = 1346528340U;
  c1_info[25].fileTimeHi = 0U;
  c1_info[25].mFileTimeLo = 0U;
  c1_info[25].mFileTimeHi = 0U;
  c1_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c1_info[26].name = "intmax";
  c1_info[26].dominantType = "char";
  c1_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[26].fileTimeLo = 1311273316U;
  c1_info[26].fileTimeHi = 0U;
  c1_info[26].mFileTimeLo = 0U;
  c1_info[26].mFileTimeHi = 0U;
  c1_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[27].name = "eml_index_minus";
  c1_info[27].dominantType = "double";
  c1_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[27].fileTimeLo = 1286836778U;
  c1_info[27].fileTimeHi = 0U;
  c1_info[27].mFileTimeLo = 0U;
  c1_info[27].mFileTimeHi = 0U;
  c1_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[28].name = "eml_index_class";
  c1_info[28].dominantType = "";
  c1_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[28].fileTimeLo = 1323181378U;
  c1_info[28].fileTimeHi = 0U;
  c1_info[28].mFileTimeLo = 0U;
  c1_info[28].mFileTimeHi = 0U;
  c1_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[29].name = "eml_index_times";
  c1_info[29].dominantType = "coder.internal.indexInt";
  c1_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[29].fileTimeLo = 1286836780U;
  c1_info[29].fileTimeHi = 0U;
  c1_info[29].mFileTimeLo = 0U;
  c1_info[29].mFileTimeHi = 0U;
  c1_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[30].name = "eml_index_class";
  c1_info[30].dominantType = "";
  c1_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[30].fileTimeLo = 1323181378U;
  c1_info[30].fileTimeHi = 0U;
  c1_info[30].mFileTimeLo = 0U;
  c1_info[30].mFileTimeHi = 0U;
  c1_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[31].name = "eml_index_plus";
  c1_info[31].dominantType = "coder.internal.indexInt";
  c1_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[31].fileTimeLo = 1286836778U;
  c1_info[31].fileTimeHi = 0U;
  c1_info[31].mFileTimeLo = 0U;
  c1_info[31].mFileTimeHi = 0U;
  c1_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[32].name = "eml_index_class";
  c1_info[32].dominantType = "";
  c1_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[32].fileTimeLo = 1323181378U;
  c1_info[32].fileTimeHi = 0U;
  c1_info[32].mFileTimeLo = 0U;
  c1_info[32].mFileTimeHi = 0U;
  c1_info[33].context = "";
  c1_info[33].name = "abs";
  c1_info[33].dominantType = "double";
  c1_info[33].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[33].fileTimeLo = 1343848366U;
  c1_info[33].fileTimeHi = 0U;
  c1_info[33].mFileTimeLo = 0U;
  c1_info[33].mFileTimeHi = 0U;
  c1_info[34].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[34].name = "eml_scalar_abs";
  c1_info[34].dominantType = "double";
  c1_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c1_info[34].fileTimeLo = 1286836712U;
  c1_info[34].fileTimeHi = 0U;
  c1_info[34].mFileTimeLo = 0U;
  c1_info[34].mFileTimeHi = 0U;
  c1_info[35].context = "";
  c1_info[35].name = "mtimes";
  c1_info[35].dominantType = "double";
  c1_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[35].fileTimeLo = 1289530492U;
  c1_info[35].fileTimeHi = 0U;
  c1_info[35].mFileTimeLo = 0U;
  c1_info[35].mFileTimeHi = 0U;
  c1_info[36].context = "";
  c1_info[36].name = "colon";
  c1_info[36].dominantType = "double";
  c1_info[36].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c1_info[36].fileTimeLo = 1348209928U;
  c1_info[36].fileTimeHi = 0U;
  c1_info[36].mFileTimeLo = 0U;
  c1_info[36].mFileTimeHi = 0U;
  c1_info[37].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c1_info[37].name = "colon";
  c1_info[37].dominantType = "double";
  c1_info[37].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c1_info[37].fileTimeLo = 1348209928U;
  c1_info[37].fileTimeHi = 0U;
  c1_info[37].mFileTimeLo = 0U;
  c1_info[37].mFileTimeHi = 0U;
  c1_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon";
  c1_info[38].name = "isfinite";
  c1_info[38].dominantType = "double";
  c1_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c1_info[38].fileTimeLo = 1286836758U;
  c1_info[38].fileTimeHi = 0U;
  c1_info[38].mFileTimeLo = 0U;
  c1_info[38].mFileTimeHi = 0U;
  c1_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c1_info[39].name = "isinf";
  c1_info[39].dominantType = "double";
  c1_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c1_info[39].fileTimeLo = 1286836760U;
  c1_info[39].fileTimeHi = 0U;
  c1_info[39].mFileTimeLo = 0U;
  c1_info[39].mFileTimeHi = 0U;
  c1_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c1_info[40].name = "isnan";
  c1_info[40].dominantType = "double";
  c1_info[40].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c1_info[40].fileTimeLo = 1286836760U;
  c1_info[40].fileTimeHi = 0U;
  c1_info[40].mFileTimeLo = 0U;
  c1_info[40].mFileTimeHi = 0U;
  c1_info[41].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon";
  c1_info[41].name = "floor";
  c1_info[41].dominantType = "double";
  c1_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[41].fileTimeLo = 1343848380U;
  c1_info[41].fileTimeHi = 0U;
  c1_info[41].mFileTimeLo = 0U;
  c1_info[41].mFileTimeHi = 0U;
  c1_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[42].name = "eml_scalar_floor";
  c1_info[42].dominantType = "double";
  c1_info[42].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c1_info[42].fileTimeLo = 1286836726U;
  c1_info[42].fileTimeHi = 0U;
  c1_info[42].mFileTimeLo = 0U;
  c1_info[42].mFileTimeHi = 0U;
  c1_info[43].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!maxabs";
  c1_info[43].name = "abs";
  c1_info[43].dominantType = "double";
  c1_info[43].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[43].fileTimeLo = 1343848366U;
  c1_info[43].fileTimeHi = 0U;
  c1_info[43].mFileTimeLo = 0U;
  c1_info[43].mFileTimeHi = 0U;
  c1_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon";
  c1_info[44].name = "eps";
  c1_info[44].dominantType = "double";
  c1_info[44].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[44].fileTimeLo = 1326738796U;
  c1_info[44].fileTimeHi = 0U;
  c1_info[44].mFileTimeLo = 0U;
  c1_info[44].mFileTimeHi = 0U;
  c1_info[45].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[45].name = "eml_mantissa_nbits";
  c1_info[45].dominantType = "char";
  c1_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_mantissa_nbits.m";
  c1_info[45].fileTimeLo = 1307669242U;
  c1_info[45].fileTimeHi = 0U;
  c1_info[45].mFileTimeLo = 0U;
  c1_info[45].mFileTimeHi = 0U;
  c1_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_mantissa_nbits.m";
  c1_info[46].name = "eml_float_model";
  c1_info[46].dominantType = "char";
  c1_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c1_info[46].fileTimeLo = 1326738796U;
  c1_info[46].fileTimeHi = 0U;
  c1_info[46].mFileTimeLo = 0U;
  c1_info[46].mFileTimeHi = 0U;
  c1_info[47].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[47].name = "eml_realmin";
  c1_info[47].dominantType = "char";
  c1_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c1_info[47].fileTimeLo = 1307669244U;
  c1_info[47].fileTimeHi = 0U;
  c1_info[47].mFileTimeLo = 0U;
  c1_info[47].mFileTimeHi = 0U;
  c1_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c1_info[48].name = "eml_float_model";
  c1_info[48].dominantType = "char";
  c1_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c1_info[48].fileTimeLo = 1326738796U;
  c1_info[48].fileTimeHi = 0U;
  c1_info[48].mFileTimeLo = 0U;
  c1_info[48].mFileTimeHi = 0U;
  c1_info[49].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[49].name = "eml_realmin_denormal";
  c1_info[49].dominantType = "char";
  c1_info[49].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin_denormal.m";
  c1_info[49].fileTimeLo = 1326738798U;
  c1_info[49].fileTimeHi = 0U;
  c1_info[49].mFileTimeLo = 0U;
  c1_info[49].mFileTimeHi = 0U;
  c1_info[50].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin_denormal.m";
  c1_info[50].name = "eml_float_model";
  c1_info[50].dominantType = "char";
  c1_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c1_info[50].fileTimeLo = 1326738796U;
  c1_info[50].fileTimeHi = 0U;
  c1_info[50].mFileTimeLo = 0U;
  c1_info[50].mFileTimeHi = 0U;
  c1_info[51].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[51].name = "abs";
  c1_info[51].dominantType = "double";
  c1_info[51].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[51].fileTimeLo = 1343848366U;
  c1_info[51].fileTimeHi = 0U;
  c1_info[51].mFileTimeLo = 0U;
  c1_info[51].mFileTimeHi = 0U;
  c1_info[52].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c1_info[52].name = "isfinite";
  c1_info[52].dominantType = "double";
  c1_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c1_info[52].fileTimeLo = 1286836758U;
  c1_info[52].fileTimeHi = 0U;
  c1_info[52].mFileTimeLo = 0U;
  c1_info[52].mFileTimeHi = 0U;
  c1_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c1_info[53].name = "realmax";
  c1_info[53].dominantType = "char";
  c1_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m";
  c1_info[53].fileTimeLo = 1307669242U;
  c1_info[53].fileTimeHi = 0U;
  c1_info[53].mFileTimeLo = 0U;
  c1_info[53].mFileTimeHi = 0U;
  c1_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m";
  c1_info[54].name = "eml_realmax";
  c1_info[54].dominantType = "char";
  c1_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m";
  c1_info[54].fileTimeLo = 1326738796U;
  c1_info[54].fileTimeHi = 0U;
  c1_info[54].mFileTimeLo = 0U;
  c1_info[54].mFileTimeHi = 0U;
  c1_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m";
  c1_info[55].name = "eml_float_model";
  c1_info[55].dominantType = "char";
  c1_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c1_info[55].fileTimeLo = 1326738796U;
  c1_info[55].fileTimeHi = 0U;
  c1_info[55].mFileTimeLo = 0U;
  c1_info[55].mFileTimeHi = 0U;
  c1_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m";
  c1_info[56].name = "mtimes";
  c1_info[56].dominantType = "double";
  c1_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[56].fileTimeLo = 1289530492U;
  c1_info[56].fileTimeHi = 0U;
  c1_info[56].mFileTimeLo = 0U;
  c1_info[56].mFileTimeHi = 0U;
  c1_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c1_info[57].name = "mrdivide";
  c1_info[57].dominantType = "double";
  c1_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c1_info[57].fileTimeLo = 1357962348U;
  c1_info[57].fileTimeHi = 0U;
  c1_info[57].mFileTimeLo = 1319744366U;
  c1_info[57].mFileTimeHi = 0U;
  c1_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c1_info[58].name = "floor";
  c1_info[58].dominantType = "double";
  c1_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c1_info[58].fileTimeLo = 1343848380U;
  c1_info[58].fileTimeHi = 0U;
  c1_info[58].mFileTimeLo = 0U;
  c1_info[58].mFileTimeHi = 0U;
  c1_info[59].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c1_info[59].name = "eml_index_class";
  c1_info[59].dominantType = "";
  c1_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[59].fileTimeLo = 1323181378U;
  c1_info[59].fileTimeHi = 0U;
  c1_info[59].mFileTimeLo = 0U;
  c1_info[59].mFileTimeHi = 0U;
  c1_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c1_info[60].name = "intmax";
  c1_info[60].dominantType = "char";
  c1_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c1_info[60].fileTimeLo = 1311273316U;
  c1_info[60].fileTimeHi = 0U;
  c1_info[60].mFileTimeLo = 0U;
  c1_info[60].mFileTimeHi = 0U;
  c1_info[61].context = "";
  c1_info[61].name = "eml_li_find";
  c1_info[61].dominantType = "";
  c1_info[61].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m";
  c1_info[61].fileTimeLo = 1286836786U;
  c1_info[61].fileTimeHi = 0U;
  c1_info[61].mFileTimeLo = 0U;
  c1_info[61].mFileTimeHi = 0U;
  c1_info[62].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m";
  c1_info[62].name = "eml_index_class";
  c1_info[62].dominantType = "";
  c1_info[62].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[62].fileTimeLo = 1323181378U;
  c1_info[62].fileTimeHi = 0U;
  c1_info[62].mFileTimeLo = 0U;
  c1_info[62].mFileTimeHi = 0U;
  c1_info[63].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m!compute_nones";
  c1_info[63].name = "eml_index_class";
  c1_info[63].dominantType = "";
  c1_info[63].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[63].fileTimeLo = 1323181378U;
  c1_info[63].fileTimeHi = 0U;
  c1_info[63].mFileTimeLo = 0U;
  c1_info[63].mFileTimeHi = 0U;
}

static void c1_b_info_helper(c1_ResolvedFunctionInfo c1_info[96])
{
  c1_info[64].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m!compute_nones";
  c1_info[64].name = "eml_int_forloop_overflow_check";
  c1_info[64].dominantType = "";
  c1_info[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[64].fileTimeLo = 1346528340U;
  c1_info[64].fileTimeHi = 0U;
  c1_info[64].mFileTimeLo = 0U;
  c1_info[64].mFileTimeHi = 0U;
  c1_info[65].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m!compute_nones";
  c1_info[65].name = "eml_index_plus";
  c1_info[65].dominantType = "double";
  c1_info[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[65].fileTimeLo = 1286836778U;
  c1_info[65].fileTimeHi = 0U;
  c1_info[65].mFileTimeLo = 0U;
  c1_info[65].mFileTimeHi = 0U;
  c1_info[66].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m";
  c1_info[66].name = "eml_int_forloop_overflow_check";
  c1_info[66].dominantType = "";
  c1_info[66].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[66].fileTimeLo = 1346528340U;
  c1_info[66].fileTimeHi = 0U;
  c1_info[66].mFileTimeLo = 0U;
  c1_info[66].mFileTimeHi = 0U;
  c1_info[67].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m";
  c1_info[67].name = "eml_index_plus";
  c1_info[67].dominantType = "double";
  c1_info[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[67].fileTimeLo = 1286836778U;
  c1_info[67].fileTimeHi = 0U;
  c1_info[67].mFileTimeLo = 0U;
  c1_info[67].mFileTimeHi = 0U;
  c1_info[68].context = "";
  c1_info[68].name = "length";
  c1_info[68].dominantType = "double";
  c1_info[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c1_info[68].fileTimeLo = 1303164206U;
  c1_info[68].fileTimeHi = 0U;
  c1_info[68].mFileTimeLo = 0U;
  c1_info[68].mFileTimeHi = 0U;
  c1_info[69].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[69].name = "eml_index_minus";
  c1_info[69].dominantType = "coder.internal.indexInt";
  c1_info[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[69].fileTimeLo = 1286836778U;
  c1_info[69].fileTimeHi = 0U;
  c1_info[69].mFileTimeLo = 0U;
  c1_info[69].mFileTimeHi = 0U;
  c1_info[70].context = "";
  c1_info[70].name = "sign";
  c1_info[70].dominantType = "double";
  c1_info[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c1_info[70].fileTimeLo = 1354378864U;
  c1_info[70].fileTimeHi = 0U;
  c1_info[70].mFileTimeLo = 0U;
  c1_info[70].mFileTimeHi = 0U;
  c1_info[71].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c1_info[71].name = "eml_scalar_sign";
  c1_info[71].dominantType = "double";
  c1_info[71].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sign.m";
  c1_info[71].fileTimeLo = 1354378864U;
  c1_info[71].fileTimeHi = 0U;
  c1_info[71].mFileTimeLo = 0U;
  c1_info[71].mFileTimeHi = 0U;
  c1_info[72].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[72].name = "eml_index_class";
  c1_info[72].dominantType = "";
  c1_info[72].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[72].fileTimeLo = 1323181378U;
  c1_info[72].fileTimeHi = 0U;
  c1_info[72].mFileTimeLo = 0U;
  c1_info[72].mFileTimeHi = 0U;
  c1_info[73].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[73].name = "eml_scalar_eg";
  c1_info[73].dominantType = "double";
  c1_info[73].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[73].fileTimeLo = 1286836796U;
  c1_info[73].fileTimeHi = 0U;
  c1_info[73].mFileTimeLo = 0U;
  c1_info[73].mFileTimeHi = 0U;
  c1_info[74].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[74].name = "eml_xgemm";
  c1_info[74].dominantType = "char";
  c1_info[74].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c1_info[74].fileTimeLo = 1299087572U;
  c1_info[74].fileTimeHi = 0U;
  c1_info[74].mFileTimeLo = 0U;
  c1_info[74].mFileTimeHi = 0U;
  c1_info[75].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c1_info[75].name = "eml_blas_inline";
  c1_info[75].dominantType = "";
  c1_info[75].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c1_info[75].fileTimeLo = 1299087568U;
  c1_info[75].fileTimeHi = 0U;
  c1_info[75].mFileTimeLo = 0U;
  c1_info[75].mFileTimeHi = 0U;
  c1_info[76].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[76].name = "eml_index_class";
  c1_info[76].dominantType = "";
  c1_info[76].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[76].fileTimeLo = 1323181378U;
  c1_info[76].fileTimeHi = 0U;
  c1_info[76].mFileTimeLo = 0U;
  c1_info[76].mFileTimeHi = 0U;
  c1_info[77].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[77].name = "eml_scalar_eg";
  c1_info[77].dominantType = "double";
  c1_info[77].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[77].fileTimeLo = 1286836796U;
  c1_info[77].fileTimeHi = 0U;
  c1_info[77].mFileTimeLo = 0U;
  c1_info[77].mFileTimeHi = 0U;
  c1_info[78].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c1_info[78].name = "eml_refblas_xgemm";
  c1_info[78].dominantType = "char";
  c1_info[78].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c1_info[78].fileTimeLo = 1299087574U;
  c1_info[78].fileTimeHi = 0U;
  c1_info[78].mFileTimeLo = 0U;
  c1_info[78].mFileTimeHi = 0U;
  c1_info[79].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c1_info[79].name = "eml_index_minus";
  c1_info[79].dominantType = "double";
  c1_info[79].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[79].fileTimeLo = 1286836778U;
  c1_info[79].fileTimeHi = 0U;
  c1_info[79].mFileTimeLo = 0U;
  c1_info[79].mFileTimeHi = 0U;
  c1_info[80].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c1_info[80].name = "eml_index_class";
  c1_info[80].dominantType = "";
  c1_info[80].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[80].fileTimeLo = 1323181378U;
  c1_info[80].fileTimeHi = 0U;
  c1_info[80].mFileTimeLo = 0U;
  c1_info[80].mFileTimeHi = 0U;
  c1_info[81].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c1_info[81].name = "eml_scalar_eg";
  c1_info[81].dominantType = "double";
  c1_info[81].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[81].fileTimeLo = 1286836796U;
  c1_info[81].fileTimeHi = 0U;
  c1_info[81].mFileTimeLo = 0U;
  c1_info[81].mFileTimeHi = 0U;
  c1_info[82].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c1_info[82].name = "eml_index_times";
  c1_info[82].dominantType = "coder.internal.indexInt";
  c1_info[82].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c1_info[82].fileTimeLo = 1286836780U;
  c1_info[82].fileTimeHi = 0U;
  c1_info[82].mFileTimeLo = 0U;
  c1_info[82].mFileTimeHi = 0U;
  c1_info[83].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c1_info[83].name = "eml_index_plus";
  c1_info[83].dominantType = "coder.internal.indexInt";
  c1_info[83].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[83].fileTimeLo = 1286836778U;
  c1_info[83].fileTimeHi = 0U;
  c1_info[83].mFileTimeLo = 0U;
  c1_info[83].mFileTimeHi = 0U;
  c1_info[84].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c1_info[84].name = "eml_index_plus";
  c1_info[84].dominantType = "double";
  c1_info[84].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[84].fileTimeLo = 1286836778U;
  c1_info[84].fileTimeHi = 0U;
  c1_info[84].mFileTimeLo = 0U;
  c1_info[84].mFileTimeHi = 0U;
  c1_info[85].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c1_info[85].name = "eml_int_forloop_overflow_check";
  c1_info[85].dominantType = "";
  c1_info[85].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c1_info[85].fileTimeLo = 1346528340U;
  c1_info[85].fileTimeHi = 0U;
  c1_info[85].mFileTimeLo = 0U;
  c1_info[85].mFileTimeHi = 0U;
  c1_info[86].context = "";
  c1_info[86].name = "mldivide";
  c1_info[86].dominantType = "double";
  c1_info[86].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p";
  c1_info[86].fileTimeLo = 1357962348U;
  c1_info[86].fileTimeHi = 0U;
  c1_info[86].mFileTimeLo = 1319744366U;
  c1_info[86].mFileTimeHi = 0U;
  c1_info[87].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mldivide.p";
  c1_info[87].name = "eml_lusolve";
  c1_info[87].dominantType = "double";
  c1_info[87].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m";
  c1_info[87].fileTimeLo = 1309469196U;
  c1_info[87].fileTimeHi = 0U;
  c1_info[87].mFileTimeLo = 0U;
  c1_info[87].mFileTimeHi = 0U;
  c1_info[88].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m";
  c1_info[88].name = "eml_index_class";
  c1_info[88].dominantType = "";
  c1_info[88].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[88].fileTimeLo = 1323181378U;
  c1_info[88].fileTimeHi = 0U;
  c1_info[88].mFileTimeLo = 0U;
  c1_info[88].mFileTimeHi = 0U;
  c1_info[89].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolve3x3";
  c1_info[89].name = "eml_index_class";
  c1_info[89].dominantType = "";
  c1_info[89].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[89].fileTimeLo = 1323181378U;
  c1_info[89].fileTimeHi = 0U;
  c1_info[89].mFileTimeLo = 0U;
  c1_info[89].mFileTimeHi = 0U;
  c1_info[90].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolve3x3";
  c1_info[90].name = "eml_xcabs1";
  c1_info[90].dominantType = "double";
  c1_info[90].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c1_info[90].fileTimeLo = 1286836706U;
  c1_info[90].fileTimeHi = 0U;
  c1_info[90].mFileTimeLo = 0U;
  c1_info[90].mFileTimeHi = 0U;
  c1_info[91].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xcabs1.m";
  c1_info[91].name = "abs";
  c1_info[91].dominantType = "double";
  c1_info[91].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c1_info[91].fileTimeLo = 1343848366U;
  c1_info[91].fileTimeHi = 0U;
  c1_info[91].mFileTimeLo = 0U;
  c1_info[91].mFileTimeHi = 0U;
  c1_info[92].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolve3x3";
  c1_info[92].name = "eml_div";
  c1_info[92].dominantType = "double";
  c1_info[92].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c1_info[92].fileTimeLo = 1313365810U;
  c1_info[92].fileTimeHi = 0U;
  c1_info[92].mFileTimeLo = 0U;
  c1_info[92].mFileTimeHi = 0U;
  c1_info[93].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolve3x3";
  c1_info[93].name = "mtimes";
  c1_info[93].dominantType = "double";
  c1_info[93].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[93].fileTimeLo = 1289530492U;
  c1_info[93].fileTimeHi = 0U;
  c1_info[93].mFileTimeLo = 0U;
  c1_info[93].mFileTimeHi = 0U;
  c1_info[94].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!warn_singular";
  c1_info[94].name = "eml_warning";
  c1_info[94].dominantType = "char";
  c1_info[94].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_warning.m";
  c1_info[94].fileTimeLo = 1286836802U;
  c1_info[94].fileTimeHi = 0U;
  c1_info[94].mFileTimeLo = 0U;
  c1_info[94].mFileTimeHi = 0U;
  c1_info[95].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_lusolve.m!lusolve3x3";
  c1_info[95].name = "eml_scalar_eg";
  c1_info[95].dominantType = "double";
  c1_info[95].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[95].fileTimeLo = 1286836796U;
  c1_info[95].fileTimeHi = 0U;
  c1_info[95].mFileTimeLo = 0U;
  c1_info[95].mFileTimeHi = 0U;
}

static void c1_cross(SFc1_modeloInstanceStruct *chartInstance, real_T c1_a[3],
                     real_T c1_b[3], real_T c1_c[3])
{
  real_T c1_b_a;
  real_T c1_b_b;
  real_T c1_y;
  real_T c1_c_a;
  real_T c1_c_b;
  real_T c1_b_y;
  real_T c1_c1;
  real_T c1_d_a;
  real_T c1_d_b;
  real_T c1_c_y;
  real_T c1_e_a;
  real_T c1_e_b;
  real_T c1_d_y;
  real_T c1_c2;
  real_T c1_f_a;
  real_T c1_f_b;
  real_T c1_e_y;
  real_T c1_g_a;
  real_T c1_g_b;
  real_T c1_f_y;
  real_T c1_c3;
  c1_b_a = c1_a[1];
  c1_b_b = c1_b[2];
  c1_y = c1_b_a * c1_b_b;
  c1_c_a = c1_a[2];
  c1_c_b = c1_b[1];
  c1_b_y = c1_c_a * c1_c_b;
  c1_c1 = c1_y - c1_b_y;
  c1_d_a = c1_a[2];
  c1_d_b = c1_b[0];
  c1_c_y = c1_d_a * c1_d_b;
  c1_e_a = c1_a[0];
  c1_e_b = c1_b[2];
  c1_d_y = c1_e_a * c1_e_b;
  c1_c2 = c1_c_y - c1_d_y;
  c1_f_a = c1_a[0];
  c1_f_b = c1_b[1];
  c1_e_y = c1_f_a * c1_f_b;
  c1_g_a = c1_a[1];
  c1_g_b = c1_b[0];
  c1_f_y = c1_g_a * c1_g_b;
  c1_c3 = c1_e_y - c1_f_y;
  c1_c[0] = c1_c1;
  c1_c[1] = c1_c2;
  c1_c[2] = c1_c3;
}

static real_T c1_dot(SFc1_modeloInstanceStruct *chartInstance, real_T c1_a[3],
                     real_T c1_b[3])
{
  real_T c1_c;
  int32_T c1_k;
  int32_T c1_b_k;
  c1_eml_scalar_eg(chartInstance);
  c1_eml_scalar_eg(chartInstance);
  c1_c = 0.0;
  for (c1_k = 1; c1_k < 4; c1_k++) {
    c1_b_k = c1_k - 1;
    c1_c += c1_a[c1_b_k] * c1_b[c1_b_k];
  }

  return c1_c;
}

static void c1_eml_scalar_eg(SFc1_modeloInstanceStruct *chartInstance)
{
}

static real_T c1_abs(SFc1_modeloInstanceStruct *chartInstance, real_T c1_x)
{
  real_T c1_b_x;
  c1_b_x = c1_x;
  return muDoubleScalarAbs(c1_b_x);
}

static real_T c1_b_dot(SFc1_modeloInstanceStruct *chartInstance, real_T c1_a[3],
  real_T c1_b[3])
{
  real_T c1_c;
  int32_T c1_k;
  int32_T c1_b_k;
  c1_b_eml_scalar_eg(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  c1_c = 0.0;
  for (c1_k = 1; c1_k < 4; c1_k++) {
    c1_b_k = c1_k - 1;
    c1_c += c1_a[c1_b_k] * c1_b[c1_b_k];
  }

  return c1_c;
}

static void c1_b_eml_scalar_eg(SFc1_modeloInstanceStruct *chartInstance)
{
}

static void c1_eml_li_find(SFc1_modeloInstanceStruct *chartInstance, boolean_T
  c1_x[4], int32_T c1_y_data[4], int32_T c1_y_sizes[2])
{
  int32_T c1_k;
  int32_T c1_i;
  int32_T c1_b_i;
  int32_T c1_a;
  const mxArray *c1_y = NULL;
  int32_T c1_tmp_sizes[2];
  int32_T c1_iv0[2];
  int32_T c1_i122;
  int32_T c1_i123;
  int32_T c1_loop_ub;
  int32_T c1_i124;
  int32_T c1_tmp_data[4];
  int32_T c1_i125;
  int32_T c1_j;
  int32_T c1_c_i;
  int32_T c1_d_i;
  int32_T c1_b_a;
  c1_k = 0;
  for (c1_i = 1; c1_i < 5; c1_i++) {
    c1_b_i = c1_i - 1;
    if (c1_x[c1_b_i]) {
      c1_a = c1_k + 1;
      c1_k = c1_a;
    }
  }

  if (c1_k <= 4) {
  } else {
    c1_y = NULL;
    sf_mex_assign(&c1_y, sf_mex_create("y", "Assertion failed.", 15, 0U, 0U, 0U,
      2, 1, strlen("Assertion failed.")), FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, c1_y);
  }

  c1_tmp_sizes[0] = 1;
  c1_iv0[0] = 1;
  c1_iv0[1] = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c1_k);
  c1_tmp_sizes[1] = c1_iv0[1];
  c1_i122 = c1_tmp_sizes[0];
  c1_i123 = c1_tmp_sizes[1];
  c1_loop_ub = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c1_k) - 1;
  for (c1_i124 = 0; c1_i124 <= c1_loop_ub; c1_i124++) {
    c1_tmp_data[c1_i124] = 0;
  }

  for (c1_i125 = 0; c1_i125 < 2; c1_i125++) {
    c1_y_sizes[c1_i125] = c1_tmp_sizes[c1_i125];
  }

  c1_j = 1;
  for (c1_c_i = 1; c1_c_i < 5; c1_c_i++) {
    c1_d_i = c1_c_i;
    if (c1_x[c1_d_i - 1]) {
      c1_y_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_j, 1, c1_y_sizes[1], 1, 0) -
        1] = c1_d_i;
      c1_b_a = c1_j + 1;
      c1_j = c1_b_a;
    }
  }
}

static void c1_b_eml_li_find(SFc1_modeloInstanceStruct *chartInstance, boolean_T
  c1_x_data[4], int32_T c1_x_sizes[2], int32_T c1_y_data[4], int32_T c1_y_sizes
  [2])
{
  int32_T c1_n;
  int32_T c1_b_n;
  int32_T c1_k;
  int32_T c1_c_n;
  int32_T c1_i;
  int32_T c1_b_i;
  int32_T c1_a;
  const mxArray *c1_y = NULL;
  int32_T c1_tmp_sizes[2];
  int32_T c1_iv1[2];
  int32_T c1_i126;
  int32_T c1_i127;
  int32_T c1_loop_ub;
  int32_T c1_i128;
  int32_T c1_tmp_data[4];
  int32_T c1_i129;
  int32_T c1_j;
  int32_T c1_d_n;
  int32_T c1_c_i;
  int32_T c1_d_i;
  int32_T c1_b_a;
  c1_n = (int32_T)(real_T)c1_x_sizes[1];
  c1_b_n = c1_n;
  c1_k = 0;
  c1_c_n = c1_b_n;
  for (c1_i = 1; c1_i <= c1_c_n; c1_i++) {
    c1_b_i = c1_i;
    if (c1_x_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_b_i, 1, c1_x_sizes[1], 1, 0)
        - 1]) {
      c1_a = c1_k + 1;
      c1_k = c1_a;
    }
  }

  if (c1_k <= c1_n) {
  } else {
    c1_y = NULL;
    sf_mex_assign(&c1_y, sf_mex_create("y", "Assertion failed.", 15, 0U, 0U, 0U,
      2, 1, strlen("Assertion failed.")), FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, c1_y);
  }

  c1_tmp_sizes[0] = 1;
  c1_iv1[0] = 1;
  c1_iv1[1] = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c1_k);
  c1_tmp_sizes[1] = c1_iv1[1];
  c1_i126 = c1_tmp_sizes[0];
  c1_i127 = c1_tmp_sizes[1];
  c1_loop_ub = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c1_k) - 1;
  for (c1_i128 = 0; c1_i128 <= c1_loop_ub; c1_i128++) {
    c1_tmp_data[c1_i128] = 0;
  }

  for (c1_i129 = 0; c1_i129 < 2; c1_i129++) {
    c1_y_sizes[c1_i129] = c1_tmp_sizes[c1_i129];
  }

  c1_j = 1;
  c1_d_n = c1_n;
  for (c1_c_i = 1; c1_c_i <= c1_d_n; c1_c_i++) {
    c1_d_i = c1_c_i;
    if (c1_x_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_d_i, 1, c1_x_sizes[1], 1, 0)
        - 1]) {
      c1_y_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_j, 1, c1_y_sizes[1], 1, 0) -
        1] = c1_d_i;
      c1_b_a = c1_j + 1;
      c1_j = c1_b_a;
    }
  }
}

static void c1_c_eml_scalar_eg(SFc1_modeloInstanceStruct *chartInstance)
{
}

static void c1_d_eml_scalar_eg(SFc1_modeloInstanceStruct *chartInstance)
{
}

static void c1_eml_xgemm(SFc1_modeloInstanceStruct *chartInstance, int32_T c1_k,
  real_T c1_A_data[12], int32_T c1_A_sizes[2], real_T c1_B_data[4], int32_T
  c1_B_sizes[1], int32_T c1_ldb, real_T c1_C[3], real_T c1_b_C[3])
{
  int32_T c1_i130;
  int32_T c1_b_A_sizes[2];
  int32_T c1_A;
  int32_T c1_b_A;
  int32_T c1_loop_ub;
  int32_T c1_i131;
  real_T c1_b_A_data[12];
  int32_T c1_b_B_sizes;
  int32_T c1_b_loop_ub;
  int32_T c1_i132;
  real_T c1_b_B_data[4];
  for (c1_i130 = 0; c1_i130 < 3; c1_i130++) {
    c1_b_C[c1_i130] = c1_C[c1_i130];
  }

  c1_b_A_sizes[0] = 3;
  c1_b_A_sizes[1] = c1_A_sizes[1];
  c1_A = c1_b_A_sizes[0];
  c1_b_A = c1_b_A_sizes[1];
  c1_loop_ub = c1_A_sizes[0] * c1_A_sizes[1] - 1;
  for (c1_i131 = 0; c1_i131 <= c1_loop_ub; c1_i131++) {
    c1_b_A_data[c1_i131] = c1_A_data[c1_i131];
  }

  c1_b_B_sizes = c1_B_sizes[0];
  c1_b_loop_ub = c1_B_sizes[0] - 1;
  for (c1_i132 = 0; c1_i132 <= c1_b_loop_ub; c1_i132++) {
    c1_b_B_data[c1_i132] = c1_B_data[c1_i132];
  }

  c1_b_eml_xgemm(chartInstance, c1_k, c1_b_A_data, c1_b_A_sizes, c1_b_B_data,
                 *(int32_T (*)[1])&c1_b_B_sizes, c1_ldb, c1_b_C);
}

static void c1_mldivide(SFc1_modeloInstanceStruct *chartInstance, real_T c1_A[9],
  real_T c1_B[3], real_T c1_Y[3])
{
  int32_T c1_i133;
  real_T c1_b_A[9];
  int32_T c1_r1;
  int32_T c1_r2;
  int32_T c1_r3;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_c_x;
  real_T c1_y;
  real_T c1_d_x;
  real_T c1_e_x;
  real_T c1_b_y;
  real_T c1_maxval;
  real_T c1_f_x;
  real_T c1_g_x;
  real_T c1_h_x;
  real_T c1_c_y;
  real_T c1_i_x;
  real_T c1_j_x;
  real_T c1_d_y;
  real_T c1_a21;
  real_T c1_k_x;
  real_T c1_l_x;
  real_T c1_m_x;
  real_T c1_e_y;
  real_T c1_n_x;
  real_T c1_o_x;
  real_T c1_f_y;
  real_T c1_d;
  real_T c1_p_x;
  real_T c1_g_y;
  real_T c1_z;
  real_T c1_q_x;
  real_T c1_h_y;
  real_T c1_b_z;
  real_T c1_a;
  real_T c1_b;
  real_T c1_i_y;
  real_T c1_b_a;
  real_T c1_b_b;
  real_T c1_j_y;
  real_T c1_c_a;
  real_T c1_c_b;
  real_T c1_k_y;
  real_T c1_d_a;
  real_T c1_d_b;
  real_T c1_l_y;
  real_T c1_r_x;
  real_T c1_s_x;
  real_T c1_t_x;
  real_T c1_m_y;
  real_T c1_u_x;
  real_T c1_v_x;
  real_T c1_n_y;
  real_T c1_b_d;
  real_T c1_w_x;
  real_T c1_x_x;
  real_T c1_y_x;
  real_T c1_o_y;
  real_T c1_ab_x;
  real_T c1_bb_x;
  real_T c1_p_y;
  real_T c1_c_d;
  int32_T c1_rtemp;
  real_T c1_cb_x;
  real_T c1_q_y;
  real_T c1_c_z;
  real_T c1_e_a;
  real_T c1_e_b;
  real_T c1_r_y;
  real_T c1_f_a;
  real_T c1_f_b;
  real_T c1_s_y;
  real_T c1_g_a;
  real_T c1_g_b;
  real_T c1_t_y;
  real_T c1_h_a;
  real_T c1_h_b;
  real_T c1_u_y;
  real_T c1_db_x;
  real_T c1_v_y;
  real_T c1_d_z;
  real_T c1_i_a;
  real_T c1_i_b;
  real_T c1_w_y;
  real_T c1_j_a;
  real_T c1_j_b;
  real_T c1_x_y;
  real_T c1_eb_x;
  real_T c1_y_y;
  real_T c1_e_z;
  real_T c1_k_a;
  real_T c1_k_b;
  real_T c1_ab_y;
  real_T c1_fb_x;
  real_T c1_bb_y;
  real_T c1_f_z;
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  for (c1_i133 = 0; c1_i133 < 9; c1_i133++) {
    c1_b_A[c1_i133] = c1_A[c1_i133];
  }

  c1_r1 = 0;
  c1_r2 = 1;
  c1_r3 = 2;
  c1_x = c1_b_A[0];
  c1_b_x = c1_x;
  c1_c_x = c1_b_x;
  c1_y = muDoubleScalarAbs(c1_c_x);
  c1_d_x = 0.0;
  c1_e_x = c1_d_x;
  c1_b_y = muDoubleScalarAbs(c1_e_x);
  c1_maxval = c1_y + c1_b_y;
  c1_f_x = c1_b_A[1];
  c1_g_x = c1_f_x;
  c1_h_x = c1_g_x;
  c1_c_y = muDoubleScalarAbs(c1_h_x);
  c1_i_x = 0.0;
  c1_j_x = c1_i_x;
  c1_d_y = muDoubleScalarAbs(c1_j_x);
  c1_a21 = c1_c_y + c1_d_y;
  if (c1_a21 > c1_maxval) {
    c1_maxval = c1_a21;
    c1_r1 = 1;
    c1_r2 = 0;
  }

  c1_k_x = c1_b_A[2];
  c1_l_x = c1_k_x;
  c1_m_x = c1_l_x;
  c1_e_y = muDoubleScalarAbs(c1_m_x);
  c1_n_x = 0.0;
  c1_o_x = c1_n_x;
  c1_f_y = muDoubleScalarAbs(c1_o_x);
  c1_d = c1_e_y + c1_f_y;
  if (c1_d > c1_maxval) {
    c1_r1 = 2;
    c1_r2 = 1;
    c1_r3 = 0;
  }

  c1_p_x = c1_b_A[c1_r2];
  c1_g_y = c1_b_A[c1_r1];
  c1_z = c1_p_x / c1_g_y;
  c1_b_A[c1_r2] = c1_z;
  c1_q_x = c1_b_A[c1_r3];
  c1_h_y = c1_b_A[c1_r1];
  c1_b_z = c1_q_x / c1_h_y;
  c1_b_A[c1_r3] = c1_b_z;
  c1_a = c1_b_A[c1_r2];
  c1_b = c1_b_A[3 + c1_r1];
  c1_i_y = c1_a * c1_b;
  c1_b_A[3 + c1_r2] -= c1_i_y;
  c1_b_a = c1_b_A[c1_r3];
  c1_b_b = c1_b_A[3 + c1_r1];
  c1_j_y = c1_b_a * c1_b_b;
  c1_b_A[3 + c1_r3] -= c1_j_y;
  c1_c_a = c1_b_A[c1_r2];
  c1_c_b = c1_b_A[6 + c1_r1];
  c1_k_y = c1_c_a * c1_c_b;
  c1_b_A[6 + c1_r2] -= c1_k_y;
  c1_d_a = c1_b_A[c1_r3];
  c1_d_b = c1_b_A[6 + c1_r1];
  c1_l_y = c1_d_a * c1_d_b;
  c1_b_A[6 + c1_r3] -= c1_l_y;
  c1_r_x = c1_b_A[3 + c1_r3];
  c1_s_x = c1_r_x;
  c1_t_x = c1_s_x;
  c1_m_y = muDoubleScalarAbs(c1_t_x);
  c1_u_x = 0.0;
  c1_v_x = c1_u_x;
  c1_n_y = muDoubleScalarAbs(c1_v_x);
  c1_b_d = c1_m_y + c1_n_y;
  c1_w_x = c1_b_A[3 + c1_r2];
  c1_x_x = c1_w_x;
  c1_y_x = c1_x_x;
  c1_o_y = muDoubleScalarAbs(c1_y_x);
  c1_ab_x = 0.0;
  c1_bb_x = c1_ab_x;
  c1_p_y = muDoubleScalarAbs(c1_bb_x);
  c1_c_d = c1_o_y + c1_p_y;
  if (c1_b_d > c1_c_d) {
    c1_rtemp = c1_r2 + 1;
    c1_r2 = c1_r3;
    c1_r3 = c1_rtemp - 1;
  }

  c1_cb_x = c1_b_A[3 + c1_r3];
  c1_q_y = c1_b_A[3 + c1_r2];
  c1_c_z = c1_cb_x / c1_q_y;
  c1_b_A[3 + c1_r3] = c1_c_z;
  c1_e_a = c1_b_A[3 + c1_r3];
  c1_e_b = c1_b_A[6 + c1_r2];
  c1_r_y = c1_e_a * c1_e_b;
  c1_b_A[6 + c1_r3] -= c1_r_y;
  guard1 = FALSE;
  guard2 = FALSE;
  if (c1_b_A[c1_r1] == 0.0) {
    guard2 = TRUE;
  } else if (c1_b_A[3 + c1_r2] == 0.0) {
    guard2 = TRUE;
  } else {
    if (c1_b_A[6 + c1_r3] == 0.0) {
      guard1 = TRUE;
    }
  }

  if (guard2 == TRUE) {
    guard1 = TRUE;
  }

  if (guard1 == TRUE) {
    c1_eml_warning(chartInstance);
  }

  c1_Y[0] = c1_B[c1_r1];
  c1_f_a = c1_Y[0];
  c1_f_b = c1_b_A[c1_r2];
  c1_s_y = c1_f_a * c1_f_b;
  c1_Y[1] = c1_B[c1_r2] - c1_s_y;
  c1_g_a = c1_Y[0];
  c1_g_b = c1_b_A[c1_r3];
  c1_t_y = c1_g_a * c1_g_b;
  c1_h_a = c1_Y[1];
  c1_h_b = c1_b_A[3 + c1_r3];
  c1_u_y = c1_h_a * c1_h_b;
  c1_Y[2] = (c1_B[c1_r3] - c1_t_y) - c1_u_y;
  c1_db_x = c1_Y[2];
  c1_v_y = c1_b_A[6 + c1_r3];
  c1_d_z = c1_db_x / c1_v_y;
  c1_Y[2] = c1_d_z;
  c1_i_a = c1_Y[2];
  c1_i_b = c1_b_A[6 + c1_r1];
  c1_w_y = c1_i_a * c1_i_b;
  c1_Y[0] -= c1_w_y;
  c1_j_a = c1_Y[2];
  c1_j_b = c1_b_A[6 + c1_r2];
  c1_x_y = c1_j_a * c1_j_b;
  c1_Y[1] -= c1_x_y;
  c1_eb_x = c1_Y[1];
  c1_y_y = c1_b_A[3 + c1_r2];
  c1_e_z = c1_eb_x / c1_y_y;
  c1_Y[1] = c1_e_z;
  c1_k_a = c1_Y[1];
  c1_k_b = c1_b_A[3 + c1_r1];
  c1_ab_y = c1_k_a * c1_k_b;
  c1_Y[0] -= c1_ab_y;
  c1_fb_x = c1_Y[0];
  c1_bb_y = c1_b_A[c1_r1];
  c1_f_z = c1_fb_x / c1_bb_y;
  c1_Y[0] = c1_f_z;
}

static void c1_eml_warning(SFc1_modeloInstanceStruct *chartInstance)
{
  int32_T c1_i134;
  static char_T c1_varargin_1[27] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'i', 'n', 'g', 'u', 'l', 'a', 'r', 'M', 'a',
    't', 'r', 'i', 'x' };

  char_T c1_u[27];
  const mxArray *c1_y = NULL;
  for (c1_i134 = 0; c1_i134 < 27; c1_i134++) {
    c1_u[c1_i134] = c1_varargin_1[c1_i134];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 27), FALSE);
  sf_mex_call_debug("warning", 0U, 1U, 14, sf_mex_call_debug("message", 1U, 1U,
    14, c1_y));
}

static const mxArray *c1_l_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_k_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i135;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i135, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i135;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_l_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_modelo, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_is_active_c1_modelo), &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_modelo);
  return c1_y;
}

static uint8_T c1_m_emlrt_marshallIn(SFc1_modeloInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_eml_xgemm(SFc1_modeloInstanceStruct *chartInstance, int32_T
  c1_k, real_T c1_A_data[12], int32_T c1_A_sizes[2], real_T c1_B_data[4],
  int32_T c1_B_sizes[1], int32_T c1_ldb, real_T c1_C[3])
{
  int32_T c1_b_k;
  int32_T c1_b_ldb;
  int32_T c1_c_k;
  real_T c1_alpha1;
  int32_T c1_c_ldb;
  real_T c1_beta1;
  char_T c1_TRANSB;
  char_T c1_TRANSA;
  ptrdiff_t c1_m_t;
  ptrdiff_t c1_n_t;
  int32_T c1_var;
  ptrdiff_t c1_k_t;
  ptrdiff_t c1_lda_t;
  int32_T c1_b_var;
  ptrdiff_t c1_ldb_t;
  ptrdiff_t c1_ldc_t;
  double * c1_alpha1_t;
  double * c1_Aia0_t;
  double * c1_Bib0_t;
  double * c1_beta1_t;
  double * c1_Cic0_t;
  c1_b_k = c1_k;
  c1_b_ldb = c1_ldb;
  if (c1_b_k < 1) {
  } else {
    c1_c_k = c1_b_k;
    c1_alpha1 = 1.0;
    c1_c_ldb = c1_b_ldb;
    c1_beta1 = 0.0;
    c1_TRANSB = 'N';
    c1_TRANSA = 'N';
    c1_m_t = (ptrdiff_t)(3);
    c1_n_t = (ptrdiff_t)(1);
    c1_var = c1_c_k;
    c1_k_t = (ptrdiff_t)(c1_var);
    c1_lda_t = (ptrdiff_t)(3);
    c1_b_var = c1_c_ldb;
    c1_ldb_t = (ptrdiff_t)(c1_b_var);
    c1_ldc_t = (ptrdiff_t)(3);
    c1_alpha1_t = (double *)(&c1_alpha1);
    _SFD_EML_ARRAY_BOUNDS_CHECK("", 1, 1, 3 * c1_A_sizes[1], 1, 0);
    c1_Aia0_t = (double *)(&c1_A_data[0]);
    _SFD_EML_ARRAY_BOUNDS_CHECK("", 1, 1, c1_B_sizes[0], 1, 0);
    c1_Bib0_t = (double *)(&c1_B_data[0]);
    c1_beta1_t = (double *)(&c1_beta1);
    c1_Cic0_t = (double *)(&c1_C[0]);
    dgemm(&c1_TRANSA, &c1_TRANSB, &c1_m_t, &c1_n_t, &c1_k_t, c1_alpha1_t,
          c1_Aia0_t, &c1_lda_t, c1_Bib0_t, &c1_ldb_t, c1_beta1_t, c1_Cic0_t,
          &c1_ldc_t);
  }
}

static void init_dsm_address_info(SFc1_modeloInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c1_modelo_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3500139483U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4139191679U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1642464292U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3941080477U);
}

mxArray *sf_c1_modelo_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("ESDwaCiEK9athEHcg962I");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_modelo_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c1_modelo(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"Hwheel\",},{M[8],M[0],T\"is_active_c1_modelo\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_modelo_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_modeloInstanceStruct *chartInstance;
    chartInstance = (SFc1_modeloInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _modeloMachineNumber_,
           1,
           1,
           1,
           3,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_modeloMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_modeloMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _modeloMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"H");
          _SFD_SET_DATA_PROPS(1,2,0,1,"Hwheel");
          _SFD_SET_DATA_PROPS(2,1,1,0,"Hmax");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,2,0,0,0,5,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1694);
        _SFD_CV_INIT_EML_IF(0,1,0,636,643,-1,855);
        _SFD_CV_INIT_EML_IF(0,1,1,725,746,-1,843);
        _SFD_CV_INIT_EML_FOR(0,1,0,452,462,867);
        _SFD_CV_INIT_EML_FOR(0,1,1,466,476,863);
        _SFD_CV_INIT_EML_FOR(0,1,2,544,556,627);
        _SFD_CV_INIT_EML_FOR(0,1,3,1001,1024,1094);
        _SFD_CV_INIT_EML_FOR(0,1,4,1314,1334,1376);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)
            c1_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T (*c1_H)[3];
          real_T (*c1_Hwheel)[4];
          real_T (*c1_Hmax)[4];
          c1_Hmax = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 1);
          c1_Hwheel = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
          c1_H = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_H);
          _SFD_SET_DATA_VALUE_PTR(1U, *c1_Hwheel);
          _SFD_SET_DATA_VALUE_PTR(2U, *c1_Hmax);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _modeloMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "rEMbc3dtIVEAQF7PqJ1o7G";
}

static void sf_opaque_initialize_c1_modelo(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_modeloInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c1_modelo((SFc1_modeloInstanceStruct*) chartInstanceVar);
  initialize_c1_modelo((SFc1_modeloInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_modelo(void *chartInstanceVar)
{
  enable_c1_modelo((SFc1_modeloInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_modelo(void *chartInstanceVar)
{
  disable_c1_modelo((SFc1_modeloInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_modelo(void *chartInstanceVar)
{
  sf_c1_modelo((SFc1_modeloInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_modelo(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_modelo((SFc1_modeloInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_modelo();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_modelo(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_modelo();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_modelo((SFc1_modeloInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_modelo(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_modelo(S);
}

static void sf_opaque_set_sim_state_c1_modelo(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_modelo(S, st);
}

static void sf_opaque_terminate_c1_modelo(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_modeloInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_modelo_optimization_info();
    }

    finalize_c1_modelo((SFc1_modeloInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_modelo((SFc1_modeloInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_modelo(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_modelo((SFc1_modeloInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_modelo(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_modelo_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(561865782U));
  ssSetChecksum1(S,(3612013647U));
  ssSetChecksum2(S,(3238256099U));
  ssSetChecksum3(S,(2884352675U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_modelo(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_modelo(SimStruct *S)
{
  SFc1_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc1_modeloInstanceStruct *)utMalloc(sizeof
    (SFc1_modeloInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_modeloInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_modelo;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_modelo;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_modelo;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_modelo;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_modelo;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_modelo;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_modelo;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_modelo;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_modelo;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_modelo;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_modelo;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_modelo_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_modelo(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_modelo(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_modelo(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_modelo_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
