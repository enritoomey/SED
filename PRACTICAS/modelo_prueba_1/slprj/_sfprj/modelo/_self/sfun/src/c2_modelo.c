/* Include files */

#include <stddef.h>
#include "blas.h"
#include "modelo_sfun.h"
#include "c2_modelo.h"
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
static const char * c2_debug_family_names[26] = { "w1", "w2", "w3", "w4", "W",
  "m", "n", "N", "facet", "i", "j", "facet_aux", "k", "l", "aux", "V", "D",
  "aux2", "aux_3", "HI", "HII", "H0", "nargin", "nargout", "H", "Hwheel" };

/* Function Declarations */
static void initialize_c2_modelo(SFc2_modeloInstanceStruct *chartInstance);
static void initialize_params_c2_modelo(SFc2_modeloInstanceStruct *chartInstance);
static void enable_c2_modelo(SFc2_modeloInstanceStruct *chartInstance);
static void disable_c2_modelo(SFc2_modeloInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_modelo(SFc2_modeloInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_modelo(SFc2_modeloInstanceStruct
  *chartInstance);
static void set_sim_state_c2_modelo(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_modelo(SFc2_modeloInstanceStruct *chartInstance);
static void sf_c2_modelo(SFc2_modeloInstanceStruct *chartInstance);
static void c2_chartstep_c2_modelo(SFc2_modeloInstanceStruct *chartInstance);
static void initSimStructsc2_modelo(SFc2_modeloInstanceStruct *chartInstance);
static void registerMessagesc2_modelo(SFc2_modeloInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance, const
  mxArray *c2_Hwheel, const char_T *c2_identifier, real_T c2_y[4]);
static void c2_b_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_c_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, real_T
  c2_inData_data[4], int32_T c2_inData_sizes[2]);
static void c2_d_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y_data[4],
  int32_T c2_y_sizes[2]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, real_T c2_outData_data[4],
  int32_T c2_outData_sizes[2]);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, real_T
  c2_inData_data[4], int32_T c2_inData_sizes[1]);
static void c2_e_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y_data[4],
  int32_T c2_y_sizes[1]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, real_T c2_outData_data[4],
  int32_T c2_outData_sizes[1]);
static void c2_f_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[3]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_g_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4]);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_h_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[48]);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[80]);
static void c2_b_info_helper(c2_ResolvedFunctionInfo c2_info[80]);
static void c2_cross(SFc2_modeloInstanceStruct *chartInstance, real_T c2_a[3],
                     real_T c2_b[3], real_T c2_c[3]);
static real_T c2_dot(SFc2_modeloInstanceStruct *chartInstance, real_T c2_a[3],
                     real_T c2_b[3]);
static void c2_eml_scalar_eg(SFc2_modeloInstanceStruct *chartInstance);
static void c2_eml_li_find(SFc2_modeloInstanceStruct *chartInstance, boolean_T
  c2_x[4], int32_T c2_y_data[4], int32_T c2_y_sizes[2]);
static void c2_b_eml_li_find(SFc2_modeloInstanceStruct *chartInstance, boolean_T
  c2_x_data[4], int32_T c2_x_sizes[2], int32_T c2_y_data[4], int32_T c2_y_sizes
  [2]);
static real_T c2_b_dot(SFc2_modeloInstanceStruct *chartInstance, real_T c2_a[3],
  real_T c2_b[3]);
static void c2_b_eml_scalar_eg(SFc2_modeloInstanceStruct *chartInstance);
static real_T c2_c_dot(SFc2_modeloInstanceStruct *chartInstance, real_T c2_a[3],
  real_T c2_b[3]);
static void c2_c_eml_scalar_eg(SFc2_modeloInstanceStruct *chartInstance);
static void c2_d_eml_scalar_eg(SFc2_modeloInstanceStruct *chartInstance);
static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_i_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_j_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_modelo, const char_T *c2_identifier);
static uint8_T c2_k_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_modeloInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_modelo(SFc2_modeloInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_modelo = 0U;
}

static void initialize_params_c2_modelo(SFc2_modeloInstanceStruct *chartInstance)
{
}

static void enable_c2_modelo(SFc2_modeloInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_modelo(SFc2_modeloInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_modelo(SFc2_modeloInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_modelo(SFc2_modeloInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  real_T c2_u[4];
  const mxArray *c2_b_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real_T (*c2_Hwheel)[4];
  c2_Hwheel = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(2), FALSE);
  for (c2_i0 = 0; c2_i0 < 4; c2_i0++) {
    c2_u[c2_i0] = (*c2_Hwheel)[c2_i0];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_modelo;
  c2_b_u = c2_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_modelo(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[4];
  int32_T c2_i1;
  real_T (*c2_Hwheel)[4];
  c2_Hwheel = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                      "Hwheel", c2_dv0);
  for (c2_i1 = 0; c2_i1 < 4; c2_i1++) {
    (*c2_Hwheel)[c2_i1] = c2_dv0[c2_i1];
  }

  chartInstance->c2_is_active_c2_modelo = c2_j_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 1)), "is_active_c2_modelo");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_modelo(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_modelo(SFc2_modeloInstanceStruct *chartInstance)
{
}

static void sf_c2_modelo(SFc2_modeloInstanceStruct *chartInstance)
{
  int32_T c2_i2;
  int32_T c2_i3;
  real_T (*c2_Hwheel)[4];
  real_T (*c2_H)[3];
  c2_Hwheel = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_H = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i2 = 0; c2_i2 < 3; c2_i2++) {
    _SFD_DATA_RANGE_CHECK((*c2_H)[c2_i2], 0U);
  }

  for (c2_i3 = 0; c2_i3 < 4; c2_i3++) {
    _SFD_DATA_RANGE_CHECK((*c2_Hwheel)[c2_i3], 1U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_modelo(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_modeloMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_modelo(SFc2_modeloInstanceStruct *chartInstance)
{
  int32_T c2_i4;
  real_T c2_H[3];
  uint32_T c2_debug_family_var_map[26];
  real_T c2_w1[3];
  real_T c2_w2[3];
  real_T c2_w3[3];
  real_T c2_w4[3];
  real_T c2_W[12];
  real_T c2_m;
  real_T c2_n;
  real_T c2_N[48];
  real_T c2_facet;
  real_T c2_i;
  real_T c2_j;
  real_T c2_facet_aux;
  real_T c2_k;
  real_T c2_l;
  real_T c2_aux[4];
  real_T c2_V[3];
  real_T c2_D;
  int32_T c2_aux2_sizes;
  real_T c2_aux2_data[4];
  real_T c2_aux_3;
  real_T c2_HI;
  real_T c2_HII;
  real_T c2_H0;
  int32_T c2_aux_sizes[2];
  real_T c2_aux_data[4];
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  real_T c2_Hwheel[4];
  int32_T c2_i5;
  int32_T c2_i6;
  static real_T c2_dv1[3] = { -0.57735026918962584, -0.57735026918962584,
    0.57735026918962584 };

  int32_T c2_i7;
  static real_T c2_dv2[3] = { -0.57735026918962584, 0.57735026918962584,
    0.57735026918962584 };

  int32_T c2_i8;
  static real_T c2_dv3[3] = { -0.57735026918962584, 0.57735026918962584,
    -0.57735026918962584 };

  int32_T c2_i9;
  static real_T c2_dv4[12] = { -0.57735026918962584, -0.57735026918962584,
    -0.57735026918962584, -0.57735026918962584, -0.57735026918962584,
    0.57735026918962584, -0.57735026918962584, 0.57735026918962584,
    0.57735026918962584, -0.57735026918962584, 0.57735026918962584,
    -0.57735026918962584 };

  int32_T c2_i10;
  int32_T c2_b_i;
  int32_T c2_b_j;
  int32_T c2_c_i;
  int32_T c2_i11;
  real_T c2_b_W[3];
  int32_T c2_c_j;
  int32_T c2_i12;
  real_T c2_c_W[3];
  real_T c2_a[3];
  int32_T c2_d_j;
  int32_T c2_d_i;
  int32_T c2_i13;
  real_T c2_b_N[3];
  int32_T c2_i14;
  real_T c2_b_H[3];
  int32_T c2_i15;
  int32_T c2_i16;
  boolean_T c2_b_aux[4];
  int32_T c2_tmp_sizes[2];
  int32_T c2_tmp_data[4];
  int32_T c2_c_aux;
  int32_T c2_d_aux;
  int32_T c2_loop_ub;
  int32_T c2_i17;
  int32_T c2_b_aux_sizes[2];
  int32_T c2_e_aux;
  int32_T c2_f_aux;
  int32_T c2_b_loop_ub;
  int32_T c2_i18;
  boolean_T c2_b_aux_data[4];
  int32_T c2_g_aux;
  int32_T c2_h_aux[1];
  int32_T c2_i_aux;
  int32_T c2_c_aux_sizes[2];
  int32_T c2_c_loop_ub;
  int32_T c2_i19;
  real_T c2_c_aux_data[4];
  int32_T c2_d_loop_ub;
  int32_T c2_i20;
  int32_T c2_i21;
  int32_T c2_x_sizes[2];
  int32_T c2_x;
  int32_T c2_b_x;
  int32_T c2_e_loop_ub;
  int32_T c2_i22;
  real_T c2_x_data[4];
  real_T c2_b_n;
  int32_T c2_f_loop_ub;
  int32_T c2_i23;
  int32_T c2_c_x;
  int32_T c2_d_x;
  int32_T c2_g_loop_ub;
  int32_T c2_i24;
  real_T c2_d0;
  int32_T c2_i25;
  int32_T c2_e_i;
  int32_T c2_j_aux[1];
  int32_T c2_k_aux;
  int32_T c2_i26;
  real_T c2_d_W[3];
  real_T c2_c_N[3];
  real_T c2_e_x;
  real_T c2_f_x;
  int32_T c2_l_aux[1];
  int32_T c2_m_aux;
  int32_T c2_i27;
  real_T c2_b;
  int32_T c2_i28;
  int32_T c2_i29;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_y;
  int32_T c2_b_k;
  int32_T c2_i30;
  real_T c2_e_W[3];
  int32_T c2_b_l;
  int32_T c2_i31;
  real_T c2_f_W[3];
  int32_T c2_i32;
  real_T c2_b_V[3];
  int32_T c2_i33;
  real_T c2_b_a[3];
  real_T c2_c_a;
  real_T c2_d_a;
  real_T c2_e_a;
  real_T c2_ak;
  real_T c2_f_a;
  real_T c2_B;
  real_T c2_b_y;
  real_T c2_c_y;
  real_T c2_g_a;
  int32_T c2_c_l;
  int32_T c2_i34;
  real_T c2_g_W[3];
  int32_T c2_i35;
  real_T c2_c_V[3];
  int32_T c2_i36;
  real_T c2_h_a[3];
  int32_T c2_i37;
  real_T c2_c_H[3];
  real_T c2_b_b;
  real_T c2_i_a;
  int32_T c2_i38;
  real_T c2_d_V[3];
  int32_T c2_c_k;
  int32_T c2_i39;
  real_T c2_h_W[3];
  int32_T c2_i40;
  real_T c2_j_a[3];
  int32_T c2_i41;
  real_T c2_d_H[3];
  real_T c2_c_b;
  real_T c2_d_N[3];
  int32_T c2_i42;
  real_T c2_e_H[3];
  real_T c2_A;
  real_T c2_b_B;
  real_T c2_j_x;
  real_T c2_d_y;
  real_T c2_k_x;
  real_T c2_e_y;
  int32_T c2_i43;
  int32_T c2_i44;
  int32_T c2_i45;
  int32_T c2_h_loop_ub;
  int32_T c2_i46;
  int32_T c2_b_x_sizes;
  int32_T c2_i_loop_ub;
  int32_T c2_i47;
  real_T c2_b_x_data[4];
  real_T c2_d1;
  int32_T c2_i48;
  int32_T c2_d_k;
  real_T c2_e_k;
  real_T c2_l_x;
  real_T c2_m_x;
  real_T c2_k_a;
  int32_T c2_j_loop_ub;
  int32_T c2_i49;
  int32_T c2_k_loop_ub;
  int32_T c2_i50;
  int32_T c2_i51;
  real_T (*c2_b_Hwheel)[4];
  real_T (*c2_f_H)[3];
  c2_b_Hwheel = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
  c2_f_H = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i4 = 0; c2_i4 < 3; c2_i4++) {
    c2_H[c2_i4] = (*c2_f_H)[c2_i4];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 26U, 27U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_w1, 0U, c2_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_w2, 1U, c2_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_w3, 2U, c2_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_w4, 3U, c2_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_W, 4U, c2_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_m, 5U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_n, 6U, c2_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_N, 7U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_facet, 8U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_i, 9U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_j, 10U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_facet_aux, 11U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_k, 12U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_l, 13U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_aux, MAX_uint32_T, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_V, 15U, c2_b_sf_marshallOut,
    c2_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_D, 16U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c2_aux2_data, (const int32_T *)
    &c2_aux2_sizes, NULL, 0, 17, (void *)c2_e_sf_marshallOut, (void *)
    c2_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_aux_3, 18U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_HI, 19U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_HII, 20U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_H0, 21U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c2_aux_data, (const int32_T *)
    &c2_aux_sizes, NULL, 0, -1, (void *)c2_d_sf_marshallOut, (void *)
    c2_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 22U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 23U, c2_c_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c2_H, 24U, c2_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_Hwheel, 25U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  for (c2_i5 = 0; c2_i5 < 3; c2_i5++) {
    c2_w1[c2_i5] = -0.57735026918962584;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  for (c2_i6 = 0; c2_i6 < 3; c2_i6++) {
    c2_w2[c2_i6] = c2_dv1[c2_i6];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
  for (c2_i7 = 0; c2_i7 < 3; c2_i7++) {
    c2_w3[c2_i7] = c2_dv2[c2_i7];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  for (c2_i8 = 0; c2_i8 < 3; c2_i8++) {
    c2_w4[c2_i8] = c2_dv3[c2_i8];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 9);
  for (c2_i9 = 0; c2_i9 < 12; c2_i9++) {
    c2_W[c2_i9] = c2_dv4[c2_i9];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
  c2_m = 3.0;
  c2_n = 4.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
  for (c2_i10 = 0; c2_i10 < 48; c2_i10++) {
    c2_N[c2_i10] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  c2_facet = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
  c2_i = 1.0;
  c2_b_i = 0;
  while (c2_b_i < 4) {
    c2_i = 1.0 + (real_T)c2_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
    c2_j = 1.0;
    c2_b_j = 0;
    while (c2_b_j < 4) {
      c2_j = 1.0 + (real_T)c2_b_j;
      CV_EML_FOR(0, 1, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
      c2_c_i = (int32_T)c2_i - 1;
      for (c2_i11 = 0; c2_i11 < 3; c2_i11++) {
        c2_b_W[c2_i11] = c2_W[c2_i11 + 3 * c2_c_i];
      }

      c2_c_j = (int32_T)c2_j - 1;
      for (c2_i12 = 0; c2_i12 < 3; c2_i12++) {
        c2_c_W[c2_i12] = c2_W[c2_i12 + 3 * c2_c_j];
      }

      c2_cross(chartInstance, c2_b_W, c2_c_W, c2_a);
      c2_d_j = (int32_T)c2_j - 1;
      c2_d_i = (int32_T)c2_i - 1;
      for (c2_i13 = 0; c2_i13 < 3; c2_i13++) {
        c2_N[(c2_d_i + (c2_d_j << 2)) + (c2_i13 << 4)] = c2_a[c2_i13];
      }

      _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 16);
      if (CV_EML_IF(0, 1, 0, c2_i != c2_j)) {
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 17);
        c2_b_N[0] = c2_N[((int32_T)c2_i + (((int32_T)c2_j - 1) << 2)) - 1];
        c2_b_N[1] = c2_N[((int32_T)c2_i + (((int32_T)c2_j - 1) << 2)) + 15];
        c2_b_N[2] = c2_N[((int32_T)c2_i + (((int32_T)c2_j - 1) << 2)) + 31];
        for (c2_i14 = 0; c2_i14 < 3; c2_i14++) {
          c2_b_H[c2_i14] = c2_H[c2_i14];
        }

        c2_facet_aux = c2_dot(chartInstance, c2_b_N, c2_b_H);
        _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 18);
        if (CV_EML_IF(0, 1, 1, c2_facet_aux <= c2_facet)) {
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 19);
          c2_facet = c2_facet_aux;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
          c2_k = c2_i;
          _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 21);
          c2_l = c2_j;
        }
      }

      c2_b_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 1, 0);
    c2_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  for (c2_i15 = 0; c2_i15 < 4; c2_i15++) {
    c2_aux[c2_i15] = 1.0 + (real_T)c2_i15;
  }

  _SFD_SYMBOL_SWITCH(14U, 14U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  for (c2_i16 = 0; c2_i16 < 4; c2_i16++) {
    c2_b_aux[c2_i16] = (c2_aux[c2_i16] != c2_k);
  }

  c2_eml_li_find(chartInstance, c2_b_aux, c2_tmp_data, c2_tmp_sizes);
  c2_aux_sizes[0] = 1;
  c2_aux_sizes[1] = c2_tmp_sizes[1];
  c2_c_aux = c2_aux_sizes[0];
  c2_d_aux = c2_aux_sizes[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i17 = 0; c2_i17 <= c2_loop_ub; c2_i17++) {
    c2_aux_data[c2_i17] = c2_aux[c2_tmp_data[c2_i17] - 1];
  }

  _SFD_SYMBOL_SWITCH(14U, 22U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_b_aux_sizes[0] = 1;
  c2_b_aux_sizes[1] = c2_aux_sizes[1];
  c2_e_aux = c2_b_aux_sizes[0];
  c2_f_aux = c2_b_aux_sizes[1];
  c2_b_loop_ub = c2_aux_sizes[0] * c2_aux_sizes[1] - 1;
  for (c2_i18 = 0; c2_i18 <= c2_b_loop_ub; c2_i18++) {
    c2_b_aux_data[c2_i18] = (c2_aux_data[c2_i18] != c2_l);
  }

  c2_b_eml_li_find(chartInstance, c2_b_aux_data, c2_b_aux_sizes, c2_tmp_data,
                   c2_tmp_sizes);
  c2_g_aux = c2_aux_sizes[1];
  c2_h_aux[0] = c2_g_aux;
  c2_i_aux = c2_aux_sizes[1];
  c2_c_aux_sizes[0] = 1;
  c2_c_aux_sizes[1] = c2_tmp_sizes[1];
  c2_c_loop_ub = c2_tmp_sizes[1] - 1;
  for (c2_i19 = 0; c2_i19 <= c2_c_loop_ub; c2_i19++) {
    c2_c_aux_data[c2_c_aux_sizes[0] * c2_i19] =
      c2_aux_data[_SFD_EML_ARRAY_BOUNDS_CHECK("aux", c2_tmp_data[c2_tmp_sizes[0]
      * c2_i19], 1, c2_i_aux, 1, 0) - 1];
  }

  c2_aux_sizes[0] = 1;
  c2_aux_sizes[1] = c2_c_aux_sizes[1];
  c2_d_loop_ub = c2_c_aux_sizes[1] - 1;
  for (c2_i20 = 0; c2_i20 <= c2_d_loop_ub; c2_i20++) {
    c2_aux_data[c2_aux_sizes[0] * c2_i20] = c2_c_aux_data[c2_c_aux_sizes[0] *
      c2_i20];
  }

  _SFD_SYMBOL_SWITCH(14U, 22U);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 30);
  for (c2_i21 = 0; c2_i21 < 3; c2_i21++) {
    c2_V[c2_i21] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 31);
  c2_D = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 32);
  c2_x_sizes[0] = 1;
  c2_x_sizes[1] = c2_aux_sizes[1];
  c2_x = c2_x_sizes[0];
  c2_b_x = c2_x_sizes[1];
  c2_e_loop_ub = c2_aux_sizes[0] * c2_aux_sizes[1] - 1;
  for (c2_i22 = 0; c2_i22 <= c2_e_loop_ub; c2_i22++) {
    c2_x_data[c2_i22] = c2_aux_data[c2_i22];
  }

  c2_b_n = (real_T)c2_x_sizes[1];
  c2_aux2_sizes = (int32_T)c2_b_n;
  c2_f_loop_ub = (int32_T)c2_b_n - 1;
  for (c2_i23 = 0; c2_i23 <= c2_f_loop_ub; c2_i23++) {
    c2_aux2_data[c2_i23] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 33);
  c2_x_sizes[0] = 1;
  c2_x_sizes[1] = c2_aux_sizes[1];
  c2_c_x = c2_x_sizes[0];
  c2_d_x = c2_x_sizes[1];
  c2_g_loop_ub = c2_aux_sizes[0] * c2_aux_sizes[1] - 1;
  for (c2_i24 = 0; c2_i24 <= c2_g_loop_ub; c2_i24++) {
    c2_x_data[c2_i24] = c2_aux_data[c2_i24];
  }

  c2_d0 = (real_T)c2_x_sizes[1];
  c2_i25 = (int32_T)c2_d0 - 1;
  c2_i = 1.0;
  c2_e_i = 0;
  while (c2_e_i <= c2_i25) {
    c2_i = 1.0 + (real_T)c2_e_i;
    CV_EML_FOR(0, 1, 2, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 34);
    c2_j_aux[0] = c2_aux_sizes[1];
    c2_k_aux = (int32_T)c2_aux_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK
      ("aux", (int32_T)c2_i, 1, c2_aux_sizes[1], 1, 0) - 1] - 1;
    for (c2_i26 = 0; c2_i26 < 3; c2_i26++) {
      c2_d_W[c2_i26] = c2_W[c2_i26 + 3 * c2_k_aux];
    }

    c2_c_N[0] = c2_N[((int32_T)c2_k + (((int32_T)c2_l - 1) << 2)) - 1];
    c2_c_N[1] = c2_N[((int32_T)c2_k + (((int32_T)c2_l - 1) << 2)) + 15];
    c2_c_N[2] = c2_N[((int32_T)c2_k + (((int32_T)c2_l - 1) << 2)) + 31];
    c2_aux2_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("aux2", (int32_T)
      c2_i, 1, c2_aux2_sizes, 1, 0) - 1] = c2_b_dot(chartInstance, c2_d_W,
      c2_c_N);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 35);
    c2_e_x = c2_aux2_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("aux2",
      (int32_T)c2_i, 1, c2_aux2_sizes, 1, 0) - 1];
    c2_f_x = c2_e_x;
    c2_f_x = muDoubleScalarSign(c2_f_x);
    c2_l_aux[0] = c2_aux_sizes[1];
    c2_m_aux = (int32_T)c2_aux_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK
      ("aux", (int32_T)c2_i, 1, c2_aux_sizes[1], 1, 0) - 1] - 1;
    for (c2_i27 = 0; c2_i27 < 3; c2_i27++) {
      c2_a[c2_i27] = c2_W[c2_i27 + 3 * c2_m_aux];
    }

    c2_b = c2_f_x;
    for (c2_i28 = 0; c2_i28 < 3; c2_i28++) {
      c2_a[c2_i28] *= c2_b;
    }

    for (c2_i29 = 0; c2_i29 < 3; c2_i29++) {
      c2_V[c2_i29] += c2_a[c2_i29];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 36);
    c2_g_x = c2_aux2_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("aux2",
      (int32_T)c2_i, 1, c2_aux2_sizes, 1, 0) - 1];
    c2_h_x = c2_g_x;
    c2_i_x = c2_h_x;
    c2_y = muDoubleScalarAbs(c2_i_x);
    c2_D += c2_y;
    c2_e_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 2, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 47);
  c2_b_k = (int32_T)c2_k - 1;
  for (c2_i30 = 0; c2_i30 < 3; c2_i30++) {
    c2_e_W[c2_i30] = c2_W[c2_i30 + 3 * c2_b_k];
  }

  c2_b_l = (int32_T)c2_l - 1;
  for (c2_i31 = 0; c2_i31 < 3; c2_i31++) {
    c2_f_W[c2_i31] = c2_W[c2_i31 + 3 * c2_b_l];
  }

  c2_cross(chartInstance, c2_e_W, c2_f_W, c2_a);
  for (c2_i32 = 0; c2_i32 < 3; c2_i32++) {
    c2_b_V[c2_i32] = c2_V[c2_i32];
  }

  for (c2_i33 = 0; c2_i33 < 3; c2_i33++) {
    c2_b_a[c2_i33] = c2_a[c2_i33];
  }

  c2_c_a = c2_c_dot(chartInstance, c2_b_V, c2_b_a);
  c2_d_a = c2_c_a;
  c2_e_a = c2_d_a;
  c2_d_eml_scalar_eg(chartInstance);
  c2_ak = c2_e_a;
  c2_f_a = c2_ak;
  c2_d_eml_scalar_eg(chartInstance);
  c2_B = c2_f_a;
  c2_b_y = c2_B;
  c2_c_y = c2_b_y;
  c2_aux_3 = 1.0 / c2_c_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 48);
  c2_g_a = c2_aux_3;
  c2_c_l = (int32_T)c2_l - 1;
  for (c2_i34 = 0; c2_i34 < 3; c2_i34++) {
    c2_g_W[c2_i34] = c2_W[c2_i34 + 3 * c2_c_l];
  }

  for (c2_i35 = 0; c2_i35 < 3; c2_i35++) {
    c2_c_V[c2_i35] = c2_V[c2_i35];
  }

  c2_cross(chartInstance, c2_g_W, c2_c_V, c2_a);
  for (c2_i36 = 0; c2_i36 < 3; c2_i36++) {
    c2_h_a[c2_i36] = c2_a[c2_i36];
  }

  for (c2_i37 = 0; c2_i37 < 3; c2_i37++) {
    c2_c_H[c2_i37] = c2_H[c2_i37];
  }

  c2_b_b = c2_c_dot(chartInstance, c2_h_a, c2_c_H);
  c2_HI = c2_g_a * c2_b_b;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 49);
  c2_i_a = c2_aux_3;
  for (c2_i38 = 0; c2_i38 < 3; c2_i38++) {
    c2_d_V[c2_i38] = c2_V[c2_i38];
  }

  c2_c_k = (int32_T)c2_k - 1;
  for (c2_i39 = 0; c2_i39 < 3; c2_i39++) {
    c2_h_W[c2_i39] = c2_W[c2_i39 + 3 * c2_c_k];
  }

  c2_cross(chartInstance, c2_d_V, c2_h_W, c2_a);
  for (c2_i40 = 0; c2_i40 < 3; c2_i40++) {
    c2_j_a[c2_i40] = c2_a[c2_i40];
  }

  for (c2_i41 = 0; c2_i41 < 3; c2_i41++) {
    c2_d_H[c2_i41] = c2_H[c2_i41];
  }

  c2_c_b = c2_c_dot(chartInstance, c2_j_a, c2_d_H);
  c2_HII = c2_i_a * c2_c_b;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 50);
  c2_d_N[0] = c2_N[((int32_T)c2_k + (((int32_T)c2_l - 1) << 2)) - 1];
  c2_d_N[1] = c2_N[((int32_T)c2_k + (((int32_T)c2_l - 1) << 2)) + 15];
  c2_d_N[2] = c2_N[((int32_T)c2_k + (((int32_T)c2_l - 1) << 2)) + 31];
  for (c2_i42 = 0; c2_i42 < 3; c2_i42++) {
    c2_e_H[c2_i42] = c2_H[c2_i42];
  }

  c2_A = c2_dot(chartInstance, c2_d_N, c2_e_H);
  c2_b_B = c2_D;
  c2_j_x = c2_A;
  c2_d_y = c2_b_B;
  c2_k_x = c2_j_x;
  c2_e_y = c2_d_y;
  c2_H0 = c2_k_x / c2_e_y;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 53);
  for (c2_i43 = 0; c2_i43 < 4; c2_i43++) {
    c2_Hwheel[c2_i43] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 54);
  c2_tmp_sizes[0] = 1;
  c2_tmp_sizes[1] = c2_aux_sizes[1];
  c2_i44 = c2_tmp_sizes[0];
  c2_i45 = c2_tmp_sizes[1];
  c2_h_loop_ub = c2_aux_sizes[0] * c2_aux_sizes[1] - 1;
  for (c2_i46 = 0; c2_i46 <= c2_h_loop_ub; c2_i46++) {
    c2_tmp_data[c2_i46] = (int32_T)c2_aux_data[c2_i46];
  }

  c2_b_x_sizes = c2_aux2_sizes;
  c2_i_loop_ub = c2_aux2_sizes - 1;
  for (c2_i47 = 0; c2_i47 <= c2_i_loop_ub; c2_i47++) {
    c2_b_x_data[c2_i47] = c2_aux2_data[c2_i47];
  }

  c2_d1 = (real_T)c2_b_x_sizes;
  c2_i48 = (int32_T)c2_d1 - 1;
  for (c2_d_k = 0; c2_d_k <= c2_i48; c2_d_k++) {
    c2_e_k = 1.0 + (real_T)c2_d_k;
    c2_l_x = c2_b_x_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("",
      (int32_T)c2_e_k, 1, c2_b_x_sizes, 1, 0) - 1];
    c2_m_x = c2_l_x;
    c2_m_x = muDoubleScalarSign(c2_m_x);
    c2_b_x_data[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)c2_e_k,
      1, c2_b_x_sizes, 1, 0) - 1] = c2_m_x;
  }

  c2_k_a = c2_H0;
  c2_b_x_sizes;
  c2_j_loop_ub = c2_b_x_sizes - 1;
  for (c2_i49 = 0; c2_i49 <= c2_j_loop_ub; c2_i49++) {
    c2_b_x_data[c2_i49] *= c2_k_a;
  }

  _SFD_SIZE_EQ_CHECK_1D(c2_tmp_sizes[1], c2_b_x_sizes);
  c2_k_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i50 = 0; c2_i50 <= c2_k_loop_ub; c2_i50++) {
    c2_Hwheel[c2_tmp_data[c2_i50] - 1] = c2_b_x_data[c2_i50];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 55);
  c2_Hwheel[(int32_T)c2_k - 1] = c2_HI;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 56);
  c2_Hwheel[(int32_T)c2_l - 1] = c2_HII;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -56);
  _SFD_SYMBOL_SCOPE_POP();
  for (c2_i51 = 0; c2_i51 < 4; c2_i51++) {
    (*c2_b_Hwheel)[c2_i51] = c2_Hwheel[c2_i51];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_modelo(SFc2_modeloInstanceStruct *chartInstance)
{
}

static void registerMessagesc2_modelo(SFc2_modeloInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i52;
  real_T c2_b_inData[4];
  int32_T c2_i53;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i52 = 0; c2_i52 < 4; c2_i52++) {
    c2_b_inData[c2_i52] = (*(real_T (*)[4])c2_inData)[c2_i52];
  }

  for (c2_i53 = 0; c2_i53 < 4; c2_i53++) {
    c2_u[c2_i53] = c2_b_inData[c2_i53];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance, const
  mxArray *c2_Hwheel, const char_T *c2_identifier, real_T c2_y[4])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Hwheel), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_Hwheel);
}

static void c2_b_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4])
{
  real_T c2_dv5[4];
  int32_T c2_i54;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv5, 1, 0, 0U, 1, 0U, 1, 4);
  for (c2_i54 = 0; c2_i54 < 4; c2_i54++) {
    c2_y[c2_i54] = c2_dv5[c2_i54];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Hwheel;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i55;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_Hwheel = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Hwheel), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_Hwheel);
  for (c2_i55 = 0; c2_i55 < 4; c2_i55++) {
    (*(real_T (*)[4])c2_outData)[c2_i55] = c2_y[c2_i55];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i56;
  real_T c2_b_inData[3];
  int32_T c2_i57;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i56 = 0; c2_i56 < 3; c2_i56++) {
    c2_b_inData[c2_i56] = (*(real_T (*)[3])c2_inData)[c2_i56];
  }

  for (c2_i57 = 0; c2_i57 < 3; c2_i57++) {
    c2_u[c2_i57] = c2_b_inData[c2_i57];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_c_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d2;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d2, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d2;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, real_T
  c2_inData_data[4], int32_T c2_inData_sizes[2])
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_b_inData_sizes[2];
  int32_T c2_loop_ub;
  int32_T c2_i58;
  real_T c2_b_inData_data[4];
  int32_T c2_u_sizes[2];
  int32_T c2_b_loop_ub;
  int32_T c2_i59;
  real_T c2_u_data[4];
  const mxArray *c2_y = NULL;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_inData_sizes[0] = 1;
  c2_b_inData_sizes[1] = c2_inData_sizes[1];
  c2_loop_ub = c2_inData_sizes[1] - 1;
  for (c2_i58 = 0; c2_i58 <= c2_loop_ub; c2_i58++) {
    c2_b_inData_data[c2_b_inData_sizes[0] * c2_i58] =
      c2_inData_data[c2_inData_sizes[0] * c2_i58];
  }

  c2_u_sizes[0] = 1;
  c2_u_sizes[1] = c2_b_inData_sizes[1];
  c2_b_loop_ub = c2_b_inData_sizes[1] - 1;
  for (c2_i59 = 0; c2_i59 <= c2_b_loop_ub; c2_i59++) {
    c2_u_data[c2_u_sizes[0] * c2_i59] = c2_b_inData_data[c2_b_inData_sizes[0] *
      c2_i59];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u_data, 0, 0U, 1U, 0U, 2,
    c2_u_sizes[0], c2_u_sizes[1]), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_d_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y_data[4],
  int32_T c2_y_sizes[2])
{
  int32_T c2_i60;
  uint32_T c2_uv0[2];
  int32_T c2_i61;
  static boolean_T c2_bv0[2] = { FALSE, TRUE };

  boolean_T c2_bv1[2];
  int32_T c2_tmp_sizes[2];
  real_T c2_tmp_data[4];
  int32_T c2_y;
  int32_T c2_b_y;
  int32_T c2_loop_ub;
  int32_T c2_i62;
  for (c2_i60 = 0; c2_i60 < 2; c2_i60++) {
    c2_uv0[c2_i60] = 1U + 3U * (uint32_T)c2_i60;
  }

  for (c2_i61 = 0; c2_i61 < 2; c2_i61++) {
    c2_bv1[c2_i61] = c2_bv0[c2_i61];
  }

  sf_mex_import_vs(c2_parentId, sf_mex_dup(c2_u), c2_tmp_data, 1, 0, 0U, 1, 0U,
                   2, c2_bv1, c2_uv0, c2_tmp_sizes);
  c2_y_sizes[0] = 1;
  c2_y_sizes[1] = c2_tmp_sizes[1];
  c2_y = c2_y_sizes[0];
  c2_b_y = c2_y_sizes[1];
  c2_loop_ub = c2_tmp_sizes[0] * c2_tmp_sizes[1] - 1;
  for (c2_i62 = 0; c2_i62 <= c2_loop_ub; c2_i62++) {
    c2_y_data[c2_i62] = c2_tmp_data[c2_i62];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, real_T c2_outData_data[4],
  int32_T c2_outData_sizes[2])
{
  const mxArray *c2_aux;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y_sizes[2];
  real_T c2_y_data[4];
  int32_T c2_loop_ub;
  int32_T c2_i63;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_aux = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_aux), &c2_thisId, c2_y_data,
                        c2_y_sizes);
  sf_mex_destroy(&c2_aux);
  c2_outData_sizes[0] = 1;
  c2_outData_sizes[1] = c2_y_sizes[1];
  c2_loop_ub = c2_y_sizes[1] - 1;
  for (c2_i63 = 0; c2_i63 <= c2_loop_ub; c2_i63++) {
    c2_outData_data[c2_outData_sizes[0] * c2_i63] = c2_y_data[c2_y_sizes[0] *
      c2_i63];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, real_T
  c2_inData_data[4], int32_T c2_inData_sizes[1])
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_b_inData_sizes;
  int32_T c2_loop_ub;
  int32_T c2_i64;
  real_T c2_b_inData_data[4];
  int32_T c2_u_sizes;
  int32_T c2_b_loop_ub;
  int32_T c2_i65;
  real_T c2_u_data[4];
  const mxArray *c2_y = NULL;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_b_inData_sizes = c2_inData_sizes[0];
  c2_loop_ub = c2_inData_sizes[0] - 1;
  for (c2_i64 = 0; c2_i64 <= c2_loop_ub; c2_i64++) {
    c2_b_inData_data[c2_i64] = c2_inData_data[c2_i64];
  }

  c2_u_sizes = c2_b_inData_sizes;
  c2_b_loop_ub = c2_b_inData_sizes - 1;
  for (c2_i65 = 0; c2_i65 <= c2_b_loop_ub; c2_i65++) {
    c2_u_data[c2_i65] = c2_b_inData_data[c2_i65];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u_data, 0, 0U, 1U, 0U, 1,
    c2_u_sizes), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_e_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y_data[4],
  int32_T c2_y_sizes[1])
{
  static uint32_T c2_uv1[1] = { 4U };

  uint32_T c2_uv2[1];
  static boolean_T c2_bv2[1] = { TRUE };

  boolean_T c2_bv3[1];
  int32_T c2_tmp_sizes;
  real_T c2_tmp_data[4];
  int32_T c2_loop_ub;
  int32_T c2_i66;
  c2_uv2[0] = c2_uv1[0];
  c2_bv3[0] = c2_bv2[0];
  sf_mex_import_vs(c2_parentId, sf_mex_dup(c2_u), c2_tmp_data, 1, 0, 0U, 1, 0U,
                   1, c2_bv3, c2_uv2, &c2_tmp_sizes);
  c2_y_sizes[0] = c2_tmp_sizes;
  c2_loop_ub = c2_tmp_sizes - 1;
  for (c2_i66 = 0; c2_i66 <= c2_loop_ub; c2_i66++) {
    c2_y_data[c2_i66] = c2_tmp_data[c2_i66];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, real_T c2_outData_data[4],
  int32_T c2_outData_sizes[1])
{
  const mxArray *c2_aux2;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y_sizes;
  real_T c2_y_data[4];
  int32_T c2_loop_ub;
  int32_T c2_i67;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_aux2 = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_aux2), &c2_thisId,
                        c2_y_data, *(int32_T (*)[1])&c2_y_sizes);
  sf_mex_destroy(&c2_aux2);
  c2_outData_sizes[0] = c2_y_sizes;
  c2_loop_ub = c2_y_sizes - 1;
  for (c2_i67 = 0; c2_i67 <= c2_loop_ub; c2_i67++) {
    c2_outData_data[c2_i67] = c2_y_data[c2_i67];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_f_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[3])
{
  real_T c2_dv6[3];
  int32_T c2_i68;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv6, 1, 0, 0U, 1, 0U, 1, 3);
  for (c2_i68 = 0; c2_i68 < 3; c2_i68++) {
    c2_y[c2_i68] = c2_dv6[c2_i68];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_V;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i69;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_V = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_V), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_V);
  for (c2_i69 = 0; c2_i69 < 3; c2_i69++) {
    (*(real_T (*)[3])c2_outData)[c2_i69] = c2_y[c2_i69];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i70;
  real_T c2_b_inData[4];
  int32_T c2_i71;
  real_T c2_u[4];
  const mxArray *c2_y = NULL;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i70 = 0; c2_i70 < 4; c2_i70++) {
    c2_b_inData[c2_i70] = (*(real_T (*)[4])c2_inData)[c2_i70];
  }

  for (c2_i71 = 0; c2_i71 < 4; c2_i71++) {
    c2_u[c2_i71] = c2_b_inData[c2_i71];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_g_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[4])
{
  real_T c2_dv7[4];
  int32_T c2_i72;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv7, 1, 0, 0U, 1, 0U, 2, 1, 4);
  for (c2_i72 = 0; c2_i72 < 4; c2_i72++) {
    c2_y[c2_i72] = c2_dv7[c2_i72];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_aux;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[4];
  int32_T c2_i73;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_aux = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_aux), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_aux);
  for (c2_i73 = 0; c2_i73 < 4; c2_i73++) {
    (*(real_T (*)[4])c2_outData)[c2_i73] = c2_y[c2_i73];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i74;
  int32_T c2_i75;
  int32_T c2_i76;
  int32_T c2_i77;
  int32_T c2_i78;
  real_T c2_b_inData[48];
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  int32_T c2_i82;
  int32_T c2_i83;
  real_T c2_u[48];
  const mxArray *c2_y = NULL;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i74 = 0;
  for (c2_i75 = 0; c2_i75 < 3; c2_i75++) {
    c2_i76 = 0;
    for (c2_i77 = 0; c2_i77 < 4; c2_i77++) {
      for (c2_i78 = 0; c2_i78 < 4; c2_i78++) {
        c2_b_inData[(c2_i78 + c2_i76) + c2_i74] = (*(real_T (*)[48])c2_inData)
          [(c2_i78 + c2_i76) + c2_i74];
      }

      c2_i76 += 4;
    }

    c2_i74 += 16;
  }

  c2_i79 = 0;
  for (c2_i80 = 0; c2_i80 < 3; c2_i80++) {
    c2_i81 = 0;
    for (c2_i82 = 0; c2_i82 < 4; c2_i82++) {
      for (c2_i83 = 0; c2_i83 < 4; c2_i83++) {
        c2_u[(c2_i83 + c2_i81) + c2_i79] = c2_b_inData[(c2_i83 + c2_i81) +
          c2_i79];
      }

      c2_i81 += 4;
    }

    c2_i79 += 16;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 3, 4, 4, 3),
                FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_h_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[48])
{
  real_T c2_dv8[48];
  int32_T c2_i84;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv8, 1, 0, 0U, 1, 0U, 3, 4, 4,
                3);
  for (c2_i84 = 0; c2_i84 < 48; c2_i84++) {
    c2_y[c2_i84] = c2_dv8[c2_i84];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_N;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[48];
  int32_T c2_i85;
  int32_T c2_i86;
  int32_T c2_i87;
  int32_T c2_i88;
  int32_T c2_i89;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_N = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_N), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_N);
  c2_i85 = 0;
  for (c2_i86 = 0; c2_i86 < 3; c2_i86++) {
    c2_i87 = 0;
    for (c2_i88 = 0; c2_i88 < 4; c2_i88++) {
      for (c2_i89 = 0; c2_i89 < 4; c2_i89++) {
        (*(real_T (*)[48])c2_outData)[(c2_i89 + c2_i87) + c2_i85] = c2_y[(c2_i89
          + c2_i87) + c2_i85];
      }

      c2_i87 += 4;
    }

    c2_i85 += 16;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i90;
  int32_T c2_i91;
  int32_T c2_i92;
  real_T c2_b_inData[12];
  int32_T c2_i93;
  int32_T c2_i94;
  int32_T c2_i95;
  real_T c2_u[12];
  const mxArray *c2_y = NULL;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i90 = 0;
  for (c2_i91 = 0; c2_i91 < 4; c2_i91++) {
    for (c2_i92 = 0; c2_i92 < 3; c2_i92++) {
      c2_b_inData[c2_i92 + c2_i90] = (*(real_T (*)[12])c2_inData)[c2_i92 +
        c2_i90];
    }

    c2_i90 += 3;
  }

  c2_i93 = 0;
  for (c2_i94 = 0; c2_i94 < 4; c2_i94++) {
    for (c2_i95 = 0; c2_i95 < 3; c2_i95++) {
      c2_u[c2_i95 + c2_i93] = c2_b_inData[c2_i95 + c2_i93];
    }

    c2_i93 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i96;
  real_T c2_b_inData[3];
  int32_T c2_i97;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i96 = 0; c2_i96 < 3; c2_i96++) {
    c2_b_inData[c2_i96] = (*(real_T (*)[3])c2_inData)[c2_i96];
  }

  for (c2_i97 = 0; c2_i97 < 3; c2_i97++) {
    c2_u[c2_i97] = c2_b_inData[c2_i97];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

const mxArray *sf_c2_modelo_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[80];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i98;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  c2_b_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 80), FALSE);
  for (c2_i98 = 0; c2_i98 < 80; c2_i98++) {
    c2_r0 = &c2_info[c2_i98];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context", "nameCaptureInfo",
                    c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name", "nameCaptureInfo", c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved", "nameCaptureInfo",
                    c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i98);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i98);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[80])
{
  c2_info[0].context = "";
  c2_info[0].name = "sqrt";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c2_info[0].fileTimeLo = 1343848386U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 0U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c2_info[1].name = "eml_error";
  c2_info[1].dominantType = "char";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c2_info[1].fileTimeLo = 1343848358U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 0U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c2_info[2].name = "eml_scalar_sqrt";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c2_info[2].fileTimeLo = 1286836738U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context = "";
  c2_info[3].name = "mrdivide";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[3].fileTimeLo = 1357962348U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 1319744366U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[4].name = "rdivide";
  c2_info[4].dominantType = "double";
  c2_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[4].fileTimeLo = 1346528388U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[5].name = "eml_scalexp_compatible";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c2_info[5].fileTimeLo = 1286836796U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[6].name = "eml_div";
  c2_info[6].dominantType = "double";
  c2_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[6].fileTimeLo = 1313365810U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 0U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context = "";
  c2_info[7].name = "cross";
  c2_info[7].dominantType = "double";
  c2_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c2_info[7].fileTimeLo = 1286836842U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c2_info[8].name = "mtimes";
  c2_info[8].dominantType = "double";
  c2_info[8].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[8].fileTimeLo = 1289530492U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context = "";
  c2_info[9].name = "dot";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c2_info[9].fileTimeLo = 1313365816U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c2_info[10].name = "isequal";
  c2_info[10].dominantType = "double";
  c2_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[10].fileTimeLo = 1286836758U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c2_info[11].name = "eml_isequal_core";
  c2_info[11].dominantType = "double";
  c2_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c2_info[11].fileTimeLo = 1286836786U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m!isequal_scalar";
  c2_info[12].name = "isnan";
  c2_info[12].dominantType = "double";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[12].fileTimeLo = 1286836760U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c2_info[13].name = "eml_index_class";
  c2_info[13].dominantType = "";
  c2_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[13].fileTimeLo = 1323181378U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m";
  c2_info[14].name = "eml_scalar_eg";
  c2_info[14].dominantType = "double";
  c2_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[14].fileTimeLo = 1286836796U;
  c2_info[14].fileTimeHi = 0U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/dot.m!vdot";
  c2_info[15].name = "eml_xdotc";
  c2_info[15].dominantType = "double";
  c2_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c2_info[15].fileTimeLo = 1299087572U;
  c2_info[15].fileTimeHi = 0U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
  c2_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c2_info[16].name = "eml_blas_inline";
  c2_info[16].dominantType = "";
  c2_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[16].fileTimeLo = 1299087568U;
  c2_info[16].fileTimeHi = 0U;
  c2_info[16].mFileTimeLo = 0U;
  c2_info[16].mFileTimeHi = 0U;
  c2_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotc.m";
  c2_info[17].name = "eml_xdot";
  c2_info[17].dominantType = "double";
  c2_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c2_info[17].fileTimeLo = 1299087572U;
  c2_info[17].fileTimeHi = 0U;
  c2_info[17].mFileTimeLo = 0U;
  c2_info[17].mFileTimeHi = 0U;
  c2_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c2_info[18].name = "eml_blas_inline";
  c2_info[18].dominantType = "";
  c2_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[18].fileTimeLo = 1299087568U;
  c2_info[18].fileTimeHi = 0U;
  c2_info[18].mFileTimeLo = 0U;
  c2_info[18].mFileTimeHi = 0U;
  c2_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m!below_threshold";
  c2_info[19].name = "length";
  c2_info[19].dominantType = "double";
  c2_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[19].fileTimeLo = 1303164206U;
  c2_info[19].fileTimeHi = 0U;
  c2_info[19].mFileTimeLo = 0U;
  c2_info[19].mFileTimeHi = 0U;
  c2_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c2_info[20].name = "eml_index_class";
  c2_info[20].dominantType = "";
  c2_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[20].fileTimeLo = 1323181378U;
  c2_info[20].fileTimeHi = 0U;
  c2_info[20].mFileTimeLo = 0U;
  c2_info[20].mFileTimeHi = 0U;
  c2_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c2_info[21].name = "eml_refblas_xdot";
  c2_info[21].dominantType = "double";
  c2_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c2_info[21].fileTimeLo = 1299087572U;
  c2_info[21].fileTimeHi = 0U;
  c2_info[21].mFileTimeLo = 0U;
  c2_info[21].mFileTimeHi = 0U;
  c2_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c2_info[22].name = "eml_refblas_xdotx";
  c2_info[22].dominantType = "char";
  c2_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[22].fileTimeLo = 1299087574U;
  c2_info[22].fileTimeHi = 0U;
  c2_info[22].mFileTimeLo = 0U;
  c2_info[22].mFileTimeHi = 0U;
  c2_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[23].name = "eml_scalar_eg";
  c2_info[23].dominantType = "double";
  c2_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[23].fileTimeLo = 1286836796U;
  c2_info[23].fileTimeHi = 0U;
  c2_info[23].mFileTimeLo = 0U;
  c2_info[23].mFileTimeHi = 0U;
  c2_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[24].name = "eml_index_class";
  c2_info[24].dominantType = "";
  c2_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[24].fileTimeLo = 1323181378U;
  c2_info[24].fileTimeHi = 0U;
  c2_info[24].mFileTimeLo = 0U;
  c2_info[24].mFileTimeHi = 0U;
  c2_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[25].name = "eml_int_forloop_overflow_check";
  c2_info[25].dominantType = "";
  c2_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[25].fileTimeLo = 1346528340U;
  c2_info[25].fileTimeHi = 0U;
  c2_info[25].mFileTimeLo = 0U;
  c2_info[25].mFileTimeHi = 0U;
  c2_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c2_info[26].name = "intmax";
  c2_info[26].dominantType = "char";
  c2_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[26].fileTimeLo = 1311273316U;
  c2_info[26].fileTimeHi = 0U;
  c2_info[26].mFileTimeLo = 0U;
  c2_info[26].mFileTimeHi = 0U;
  c2_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[27].name = "eml_index_minus";
  c2_info[27].dominantType = "double";
  c2_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[27].fileTimeLo = 1286836778U;
  c2_info[27].fileTimeHi = 0U;
  c2_info[27].mFileTimeLo = 0U;
  c2_info[27].mFileTimeHi = 0U;
  c2_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[28].name = "eml_index_class";
  c2_info[28].dominantType = "";
  c2_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[28].fileTimeLo = 1323181378U;
  c2_info[28].fileTimeHi = 0U;
  c2_info[28].mFileTimeLo = 0U;
  c2_info[28].mFileTimeHi = 0U;
  c2_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[29].name = "eml_index_times";
  c2_info[29].dominantType = "coder.internal.indexInt";
  c2_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[29].fileTimeLo = 1286836780U;
  c2_info[29].fileTimeHi = 0U;
  c2_info[29].mFileTimeLo = 0U;
  c2_info[29].mFileTimeHi = 0U;
  c2_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c2_info[30].name = "eml_index_class";
  c2_info[30].dominantType = "";
  c2_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[30].fileTimeLo = 1323181378U;
  c2_info[30].fileTimeHi = 0U;
  c2_info[30].mFileTimeLo = 0U;
  c2_info[30].mFileTimeHi = 0U;
  c2_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[31].name = "eml_index_plus";
  c2_info[31].dominantType = "coder.internal.indexInt";
  c2_info[31].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[31].fileTimeLo = 1286836778U;
  c2_info[31].fileTimeHi = 0U;
  c2_info[31].mFileTimeLo = 0U;
  c2_info[31].mFileTimeHi = 0U;
  c2_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[32].name = "eml_index_class";
  c2_info[32].dominantType = "";
  c2_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[32].fileTimeLo = 1323181378U;
  c2_info[32].fileTimeHi = 0U;
  c2_info[32].mFileTimeLo = 0U;
  c2_info[32].mFileTimeHi = 0U;
  c2_info[33].context = "";
  c2_info[33].name = "colon";
  c2_info[33].dominantType = "double";
  c2_info[33].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c2_info[33].fileTimeLo = 1348209928U;
  c2_info[33].fileTimeHi = 0U;
  c2_info[33].mFileTimeLo = 0U;
  c2_info[33].mFileTimeHi = 0U;
  c2_info[34].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c2_info[34].name = "colon";
  c2_info[34].dominantType = "double";
  c2_info[34].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m";
  c2_info[34].fileTimeLo = 1348209928U;
  c2_info[34].fileTimeHi = 0U;
  c2_info[34].mFileTimeLo = 0U;
  c2_info[34].mFileTimeHi = 0U;
  c2_info[35].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon";
  c2_info[35].name = "isfinite";
  c2_info[35].dominantType = "double";
  c2_info[35].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c2_info[35].fileTimeLo = 1286836758U;
  c2_info[35].fileTimeHi = 0U;
  c2_info[35].mFileTimeLo = 0U;
  c2_info[35].mFileTimeHi = 0U;
  c2_info[36].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c2_info[36].name = "isinf";
  c2_info[36].dominantType = "double";
  c2_info[36].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m";
  c2_info[36].fileTimeLo = 1286836760U;
  c2_info[36].fileTimeHi = 0U;
  c2_info[36].mFileTimeLo = 0U;
  c2_info[36].mFileTimeHi = 0U;
  c2_info[37].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c2_info[37].name = "isnan";
  c2_info[37].dominantType = "double";
  c2_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m";
  c2_info[37].fileTimeLo = 1286836760U;
  c2_info[37].fileTimeHi = 0U;
  c2_info[37].mFileTimeLo = 0U;
  c2_info[37].mFileTimeHi = 0U;
  c2_info[38].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon";
  c2_info[38].name = "floor";
  c2_info[38].dominantType = "double";
  c2_info[38].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[38].fileTimeLo = 1343848380U;
  c2_info[38].fileTimeHi = 0U;
  c2_info[38].mFileTimeLo = 0U;
  c2_info[38].mFileTimeHi = 0U;
  c2_info[39].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[39].name = "eml_scalar_floor";
  c2_info[39].dominantType = "double";
  c2_info[39].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c2_info[39].fileTimeLo = 1286836726U;
  c2_info[39].fileTimeHi = 0U;
  c2_info[39].mFileTimeLo = 0U;
  c2_info[39].mFileTimeHi = 0U;
  c2_info[40].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!maxabs";
  c2_info[40].name = "abs";
  c2_info[40].dominantType = "double";
  c2_info[40].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[40].fileTimeLo = 1343848366U;
  c2_info[40].fileTimeHi = 0U;
  c2_info[40].mFileTimeLo = 0U;
  c2_info[40].mFileTimeHi = 0U;
  c2_info[41].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[41].name = "eml_scalar_abs";
  c2_info[41].dominantType = "double";
  c2_info[41].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m";
  c2_info[41].fileTimeLo = 1286836712U;
  c2_info[41].fileTimeHi = 0U;
  c2_info[41].mFileTimeLo = 0U;
  c2_info[41].mFileTimeHi = 0U;
  c2_info[42].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon";
  c2_info[42].name = "eps";
  c2_info[42].dominantType = "double";
  c2_info[42].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[42].fileTimeLo = 1326738796U;
  c2_info[42].fileTimeHi = 0U;
  c2_info[42].mFileTimeLo = 0U;
  c2_info[42].mFileTimeHi = 0U;
  c2_info[43].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[43].name = "eml_mantissa_nbits";
  c2_info[43].dominantType = "char";
  c2_info[43].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_mantissa_nbits.m";
  c2_info[43].fileTimeLo = 1307669242U;
  c2_info[43].fileTimeHi = 0U;
  c2_info[43].mFileTimeLo = 0U;
  c2_info[43].mFileTimeHi = 0U;
  c2_info[44].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_mantissa_nbits.m";
  c2_info[44].name = "eml_float_model";
  c2_info[44].dominantType = "char";
  c2_info[44].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c2_info[44].fileTimeLo = 1326738796U;
  c2_info[44].fileTimeHi = 0U;
  c2_info[44].mFileTimeLo = 0U;
  c2_info[44].mFileTimeHi = 0U;
  c2_info[45].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[45].name = "eml_realmin";
  c2_info[45].dominantType = "char";
  c2_info[45].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c2_info[45].fileTimeLo = 1307669244U;
  c2_info[45].fileTimeHi = 0U;
  c2_info[45].mFileTimeLo = 0U;
  c2_info[45].mFileTimeHi = 0U;
  c2_info[46].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m";
  c2_info[46].name = "eml_float_model";
  c2_info[46].dominantType = "char";
  c2_info[46].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c2_info[46].fileTimeLo = 1326738796U;
  c2_info[46].fileTimeHi = 0U;
  c2_info[46].mFileTimeLo = 0U;
  c2_info[46].mFileTimeHi = 0U;
  c2_info[47].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[47].name = "eml_realmin_denormal";
  c2_info[47].dominantType = "char";
  c2_info[47].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin_denormal.m";
  c2_info[47].fileTimeLo = 1326738798U;
  c2_info[47].fileTimeHi = 0U;
  c2_info[47].mFileTimeLo = 0U;
  c2_info[47].mFileTimeHi = 0U;
  c2_info[48].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin_denormal.m";
  c2_info[48].name = "eml_float_model";
  c2_info[48].dominantType = "char";
  c2_info[48].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c2_info[48].fileTimeLo = 1326738796U;
  c2_info[48].fileTimeHi = 0U;
  c2_info[48].mFileTimeLo = 0U;
  c2_info[48].mFileTimeHi = 0U;
  c2_info[49].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[49].name = "abs";
  c2_info[49].dominantType = "double";
  c2_info[49].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[49].fileTimeLo = 1343848366U;
  c2_info[49].fileTimeHi = 0U;
  c2_info[49].mFileTimeLo = 0U;
  c2_info[49].mFileTimeHi = 0U;
  c2_info[50].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m";
  c2_info[50].name = "isfinite";
  c2_info[50].dominantType = "double";
  c2_info[50].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m";
  c2_info[50].fileTimeLo = 1286836758U;
  c2_info[50].fileTimeHi = 0U;
  c2_info[50].mFileTimeLo = 0U;
  c2_info[50].mFileTimeHi = 0U;
  c2_info[51].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange";
  c2_info[51].name = "realmax";
  c2_info[51].dominantType = "char";
  c2_info[51].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m";
  c2_info[51].fileTimeLo = 1307669242U;
  c2_info[51].fileTimeHi = 0U;
  c2_info[51].mFileTimeLo = 0U;
  c2_info[51].mFileTimeHi = 0U;
  c2_info[52].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m";
  c2_info[52].name = "eml_realmax";
  c2_info[52].dominantType = "char";
  c2_info[52].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m";
  c2_info[52].fileTimeLo = 1326738796U;
  c2_info[52].fileTimeHi = 0U;
  c2_info[52].mFileTimeLo = 0U;
  c2_info[52].mFileTimeHi = 0U;
  c2_info[53].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m";
  c2_info[53].name = "eml_float_model";
  c2_info[53].dominantType = "char";
  c2_info[53].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m";
  c2_info[53].fileTimeLo = 1326738796U;
  c2_info[53].fileTimeHi = 0U;
  c2_info[53].mFileTimeLo = 0U;
  c2_info[53].mFileTimeHi = 0U;
  c2_info[54].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m";
  c2_info[54].name = "mtimes";
  c2_info[54].dominantType = "double";
  c2_info[54].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[54].fileTimeLo = 1289530492U;
  c2_info[54].fileTimeHi = 0U;
  c2_info[54].mFileTimeLo = 0U;
  c2_info[54].mFileTimeHi = 0U;
  c2_info[55].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c2_info[55].name = "mrdivide";
  c2_info[55].dominantType = "double";
  c2_info[55].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[55].fileTimeLo = 1357962348U;
  c2_info[55].fileTimeHi = 0U;
  c2_info[55].mFileTimeLo = 1319744366U;
  c2_info[55].mFileTimeHi = 0U;
  c2_info[56].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c2_info[56].name = "floor";
  c2_info[56].dominantType = "double";
  c2_info[56].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[56].fileTimeLo = 1343848380U;
  c2_info[56].fileTimeHi = 0U;
  c2_info[56].mFileTimeLo = 0U;
  c2_info[56].mFileTimeHi = 0U;
  c2_info[57].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c2_info[57].name = "eml_index_class";
  c2_info[57].dominantType = "";
  c2_info[57].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[57].fileTimeLo = 1323181378U;
  c2_info[57].fileTimeHi = 0U;
  c2_info[57].mFileTimeLo = 0U;
  c2_info[57].mFileTimeHi = 0U;
  c2_info[58].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon";
  c2_info[58].name = "intmax";
  c2_info[58].dominantType = "char";
  c2_info[58].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[58].fileTimeLo = 1311273316U;
  c2_info[58].fileTimeHi = 0U;
  c2_info[58].mFileTimeLo = 0U;
  c2_info[58].mFileTimeHi = 0U;
  c2_info[59].context = "";
  c2_info[59].name = "eml_li_find";
  c2_info[59].dominantType = "";
  c2_info[59].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m";
  c2_info[59].fileTimeLo = 1286836786U;
  c2_info[59].fileTimeHi = 0U;
  c2_info[59].mFileTimeLo = 0U;
  c2_info[59].mFileTimeHi = 0U;
  c2_info[60].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m";
  c2_info[60].name = "eml_index_class";
  c2_info[60].dominantType = "";
  c2_info[60].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[60].fileTimeLo = 1323181378U;
  c2_info[60].fileTimeHi = 0U;
  c2_info[60].mFileTimeLo = 0U;
  c2_info[60].mFileTimeHi = 0U;
  c2_info[61].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m!compute_nones";
  c2_info[61].name = "eml_index_class";
  c2_info[61].dominantType = "";
  c2_info[61].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[61].fileTimeLo = 1323181378U;
  c2_info[61].fileTimeHi = 0U;
  c2_info[61].mFileTimeLo = 0U;
  c2_info[61].mFileTimeHi = 0U;
  c2_info[62].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m!compute_nones";
  c2_info[62].name = "eml_int_forloop_overflow_check";
  c2_info[62].dominantType = "";
  c2_info[62].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[62].fileTimeLo = 1346528340U;
  c2_info[62].fileTimeHi = 0U;
  c2_info[62].mFileTimeLo = 0U;
  c2_info[62].mFileTimeHi = 0U;
  c2_info[63].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m!compute_nones";
  c2_info[63].name = "eml_index_plus";
  c2_info[63].dominantType = "double";
  c2_info[63].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[63].fileTimeLo = 1286836778U;
  c2_info[63].fileTimeHi = 0U;
  c2_info[63].mFileTimeLo = 0U;
  c2_info[63].mFileTimeHi = 0U;
}

static void c2_b_info_helper(c2_ResolvedFunctionInfo c2_info[80])
{
  c2_info[64].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m";
  c2_info[64].name = "eml_int_forloop_overflow_check";
  c2_info[64].dominantType = "";
  c2_info[64].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[64].fileTimeLo = 1346528340U;
  c2_info[64].fileTimeHi = 0U;
  c2_info[64].mFileTimeLo = 0U;
  c2_info[64].mFileTimeHi = 0U;
  c2_info[65].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_li_find.m";
  c2_info[65].name = "eml_index_plus";
  c2_info[65].dominantType = "double";
  c2_info[65].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c2_info[65].fileTimeLo = 1286836778U;
  c2_info[65].fileTimeHi = 0U;
  c2_info[65].mFileTimeLo = 0U;
  c2_info[65].mFileTimeHi = 0U;
  c2_info[66].context = "";
  c2_info[66].name = "length";
  c2_info[66].dominantType = "double";
  c2_info[66].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m";
  c2_info[66].fileTimeLo = 1303164206U;
  c2_info[66].fileTimeHi = 0U;
  c2_info[66].mFileTimeLo = 0U;
  c2_info[66].mFileTimeHi = 0U;
  c2_info[67].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c2_info[67].name = "eml_index_minus";
  c2_info[67].dominantType = "coder.internal.indexInt";
  c2_info[67].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c2_info[67].fileTimeLo = 1286836778U;
  c2_info[67].fileTimeHi = 0U;
  c2_info[67].mFileTimeLo = 0U;
  c2_info[67].mFileTimeHi = 0U;
  c2_info[68].context = "";
  c2_info[68].name = "sign";
  c2_info[68].dominantType = "double";
  c2_info[68].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c2_info[68].fileTimeLo = 1354378864U;
  c2_info[68].fileTimeHi = 0U;
  c2_info[68].mFileTimeLo = 0U;
  c2_info[68].mFileTimeHi = 0U;
  c2_info[69].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sign.m";
  c2_info[69].name = "eml_scalar_sign";
  c2_info[69].dominantType = "double";
  c2_info[69].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sign.m";
  c2_info[69].fileTimeLo = 1354378864U;
  c2_info[69].fileTimeHi = 0U;
  c2_info[69].mFileTimeLo = 0U;
  c2_info[69].mFileTimeHi = 0U;
  c2_info[70].context = "";
  c2_info[70].name = "mtimes";
  c2_info[70].dominantType = "double";
  c2_info[70].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[70].fileTimeLo = 1289530492U;
  c2_info[70].fileTimeHi = 0U;
  c2_info[70].mFileTimeLo = 0U;
  c2_info[70].mFileTimeHi = 0U;
  c2_info[71].context = "";
  c2_info[71].name = "norm";
  c2_info[71].dominantType = "double";
  c2_info[71].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c2_info[71].fileTimeLo = 1336540094U;
  c2_info[71].fileTimeHi = 0U;
  c2_info[71].mFileTimeLo = 0U;
  c2_info[71].mFileTimeHi = 0U;
  c2_info[72].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/matfun/norm.m";
  c2_info[72].name = "abs";
  c2_info[72].dominantType = "double";
  c2_info[72].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m";
  c2_info[72].fileTimeLo = 1343848366U;
  c2_info[72].fileTimeHi = 0U;
  c2_info[72].mFileTimeLo = 0U;
  c2_info[72].mFileTimeHi = 0U;
  c2_info[73].context = "";
  c2_info[73].name = "mpower";
  c2_info[73].dominantType = "double";
  c2_info[73].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[73].fileTimeLo = 1286836842U;
  c2_info[73].fileTimeHi = 0U;
  c2_info[73].mFileTimeLo = 0U;
  c2_info[73].mFileTimeHi = 0U;
  c2_info[74].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c2_info[74].name = "power";
  c2_info[74].dominantType = "double";
  c2_info[74].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c2_info[74].fileTimeLo = 1348209930U;
  c2_info[74].fileTimeHi = 0U;
  c2_info[74].mFileTimeLo = 0U;
  c2_info[74].mFileTimeHi = 0U;
  c2_info[75].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c2_info[75].name = "eml_scalar_eg";
  c2_info[75].dominantType = "double";
  c2_info[75].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[75].fileTimeLo = 1286836796U;
  c2_info[75].fileTimeHi = 0U;
  c2_info[75].mFileTimeLo = 0U;
  c2_info[75].mFileTimeHi = 0U;
  c2_info[76].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c2_info[76].name = "eml_scalexp_alloc";
  c2_info[76].dominantType = "double";
  c2_info[76].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c2_info[76].fileTimeLo = 1352435660U;
  c2_info[76].fileTimeHi = 0U;
  c2_info[76].mFileTimeLo = 0U;
  c2_info[76].mFileTimeHi = 0U;
  c2_info[77].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower";
  c2_info[77].name = "floor";
  c2_info[77].dominantType = "double";
  c2_info[77].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m";
  c2_info[77].fileTimeLo = 1343848380U;
  c2_info[77].fileTimeHi = 0U;
  c2_info[77].mFileTimeLo = 0U;
  c2_info[77].mFileTimeHi = 0U;
  c2_info[78].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c2_info[78].name = "eml_scalar_eg";
  c2_info[78].dominantType = "double";
  c2_info[78].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[78].fileTimeLo = 1286836796U;
  c2_info[78].fileTimeHi = 0U;
  c2_info[78].mFileTimeLo = 0U;
  c2_info[78].mFileTimeHi = 0U;
  c2_info[79].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power";
  c2_info[79].name = "mrdivide";
  c2_info[79].dominantType = "double";
  c2_info[79].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[79].fileTimeLo = 1357962348U;
  c2_info[79].fileTimeHi = 0U;
  c2_info[79].mFileTimeLo = 1319744366U;
  c2_info[79].mFileTimeHi = 0U;
}

static void c2_cross(SFc2_modeloInstanceStruct *chartInstance, real_T c2_a[3],
                     real_T c2_b[3], real_T c2_c[3])
{
  real_T c2_b_a;
  real_T c2_b_b;
  real_T c2_y;
  real_T c2_c_a;
  real_T c2_c_b;
  real_T c2_b_y;
  real_T c2_c1;
  real_T c2_d_a;
  real_T c2_d_b;
  real_T c2_c_y;
  real_T c2_e_a;
  real_T c2_e_b;
  real_T c2_d_y;
  real_T c2_c2;
  real_T c2_f_a;
  real_T c2_f_b;
  real_T c2_e_y;
  real_T c2_g_a;
  real_T c2_g_b;
  real_T c2_f_y;
  real_T c2_c3;
  c2_b_a = c2_a[1];
  c2_b_b = c2_b[2];
  c2_y = c2_b_a * c2_b_b;
  c2_c_a = c2_a[2];
  c2_c_b = c2_b[1];
  c2_b_y = c2_c_a * c2_c_b;
  c2_c1 = c2_y - c2_b_y;
  c2_d_a = c2_a[2];
  c2_d_b = c2_b[0];
  c2_c_y = c2_d_a * c2_d_b;
  c2_e_a = c2_a[0];
  c2_e_b = c2_b[2];
  c2_d_y = c2_e_a * c2_e_b;
  c2_c2 = c2_c_y - c2_d_y;
  c2_f_a = c2_a[0];
  c2_f_b = c2_b[1];
  c2_e_y = c2_f_a * c2_f_b;
  c2_g_a = c2_a[1];
  c2_g_b = c2_b[0];
  c2_f_y = c2_g_a * c2_g_b;
  c2_c3 = c2_e_y - c2_f_y;
  c2_c[0] = c2_c1;
  c2_c[1] = c2_c2;
  c2_c[2] = c2_c3;
}

static real_T c2_dot(SFc2_modeloInstanceStruct *chartInstance, real_T c2_a[3],
                     real_T c2_b[3])
{
  real_T c2_c;
  int32_T c2_k;
  int32_T c2_b_k;
  c2_eml_scalar_eg(chartInstance);
  c2_eml_scalar_eg(chartInstance);
  c2_c = 0.0;
  for (c2_k = 1; c2_k < 4; c2_k++) {
    c2_b_k = c2_k - 1;
    c2_c += c2_a[c2_b_k] * c2_b[c2_b_k];
  }

  return c2_c;
}

static void c2_eml_scalar_eg(SFc2_modeloInstanceStruct *chartInstance)
{
}

static void c2_eml_li_find(SFc2_modeloInstanceStruct *chartInstance, boolean_T
  c2_x[4], int32_T c2_y_data[4], int32_T c2_y_sizes[2])
{
  int32_T c2_k;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_a;
  const mxArray *c2_y = NULL;
  int32_T c2_tmp_sizes[2];
  int32_T c2_iv0[2];
  int32_T c2_i99;
  int32_T c2_i100;
  int32_T c2_loop_ub;
  int32_T c2_i101;
  int32_T c2_tmp_data[4];
  int32_T c2_i102;
  int32_T c2_j;
  int32_T c2_c_i;
  int32_T c2_d_i;
  int32_T c2_b_a;
  c2_k = 0;
  for (c2_i = 1; c2_i < 5; c2_i++) {
    c2_b_i = c2_i - 1;
    if (c2_x[c2_b_i]) {
      c2_a = c2_k + 1;
      c2_k = c2_a;
    }
  }

  if (c2_k <= 4) {
  } else {
    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", "Assertion failed.", 15, 0U, 0U, 0U,
      2, 1, strlen("Assertion failed.")), FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, c2_y);
  }

  c2_tmp_sizes[0] = 1;
  c2_iv0[0] = 1;
  c2_iv0[1] = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c2_k);
  c2_tmp_sizes[1] = c2_iv0[1];
  c2_i99 = c2_tmp_sizes[0];
  c2_i100 = c2_tmp_sizes[1];
  c2_loop_ub = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c2_k) - 1;
  for (c2_i101 = 0; c2_i101 <= c2_loop_ub; c2_i101++) {
    c2_tmp_data[c2_i101] = 0;
  }

  for (c2_i102 = 0; c2_i102 < 2; c2_i102++) {
    c2_y_sizes[c2_i102] = c2_tmp_sizes[c2_i102];
  }

  c2_j = 1;
  for (c2_c_i = 1; c2_c_i < 5; c2_c_i++) {
    c2_d_i = c2_c_i;
    if (c2_x[c2_d_i - 1]) {
      c2_y_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c2_j, 1, c2_y_sizes[1], 1, 0) -
        1] = c2_d_i;
      c2_b_a = c2_j + 1;
      c2_j = c2_b_a;
    }
  }
}

static void c2_b_eml_li_find(SFc2_modeloInstanceStruct *chartInstance, boolean_T
  c2_x_data[4], int32_T c2_x_sizes[2], int32_T c2_y_data[4], int32_T c2_y_sizes
  [2])
{
  int32_T c2_n;
  int32_T c2_b_n;
  int32_T c2_k;
  int32_T c2_c_n;
  int32_T c2_i;
  int32_T c2_b_i;
  int32_T c2_a;
  const mxArray *c2_y = NULL;
  int32_T c2_tmp_sizes[2];
  int32_T c2_iv1[2];
  int32_T c2_i103;
  int32_T c2_i104;
  int32_T c2_loop_ub;
  int32_T c2_i105;
  int32_T c2_tmp_data[4];
  int32_T c2_i106;
  int32_T c2_j;
  int32_T c2_d_n;
  int32_T c2_c_i;
  int32_T c2_d_i;
  int32_T c2_b_a;
  c2_n = (int32_T)(real_T)c2_x_sizes[1];
  c2_b_n = c2_n;
  c2_k = 0;
  c2_c_n = c2_b_n;
  for (c2_i = 1; c2_i <= c2_c_n; c2_i++) {
    c2_b_i = c2_i;
    if (c2_x_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c2_b_i, 1, c2_x_sizes[1], 1, 0)
        - 1]) {
      c2_a = c2_k + 1;
      c2_k = c2_a;
    }
  }

  if (c2_k <= c2_n) {
  } else {
    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", "Assertion failed.", 15, 0U, 0U, 0U,
      2, 1, strlen("Assertion failed.")), FALSE);
    sf_mex_call_debug("error", 0U, 1U, 14, c2_y);
  }

  c2_tmp_sizes[0] = 1;
  c2_iv1[0] = 1;
  c2_iv1[1] = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c2_k);
  c2_tmp_sizes[1] = c2_iv1[1];
  c2_i103 = c2_tmp_sizes[0];
  c2_i104 = c2_tmp_sizes[1];
  c2_loop_ub = (int32_T)_SFD_NON_NEGATIVE_CHECK("", (real_T)c2_k) - 1;
  for (c2_i105 = 0; c2_i105 <= c2_loop_ub; c2_i105++) {
    c2_tmp_data[c2_i105] = 0;
  }

  for (c2_i106 = 0; c2_i106 < 2; c2_i106++) {
    c2_y_sizes[c2_i106] = c2_tmp_sizes[c2_i106];
  }

  c2_j = 1;
  c2_d_n = c2_n;
  for (c2_c_i = 1; c2_c_i <= c2_d_n; c2_c_i++) {
    c2_d_i = c2_c_i;
    if (c2_x_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c2_d_i, 1, c2_x_sizes[1], 1, 0)
        - 1]) {
      c2_y_data[_SFD_EML_ARRAY_BOUNDS_CHECK("", c2_j, 1, c2_y_sizes[1], 1, 0) -
        1] = c2_d_i;
      c2_b_a = c2_j + 1;
      c2_j = c2_b_a;
    }
  }
}

static real_T c2_b_dot(SFc2_modeloInstanceStruct *chartInstance, real_T c2_a[3],
  real_T c2_b[3])
{
  real_T c2_c;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_k;
  int32_T c2_b_a;
  int32_T c2_c_a;
  c2_b_eml_scalar_eg(chartInstance);
  c2_b_eml_scalar_eg(chartInstance);
  c2_c = 0.0;
  c2_ix = 1;
  c2_iy = 1;
  for (c2_k = 1; c2_k < 4; c2_k++) {
    c2_c += c2_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", c2_ix, 1, 3, 1, 0) - 1] *
      c2_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", c2_iy, 1, 3, 1, 0) - 1];
    c2_b_a = c2_ix + 1;
    c2_ix = c2_b_a;
    c2_c_a = c2_iy + 1;
    c2_iy = c2_c_a;
  }

  return c2_c;
}

static void c2_b_eml_scalar_eg(SFc2_modeloInstanceStruct *chartInstance)
{
}

static real_T c2_c_dot(SFc2_modeloInstanceStruct *chartInstance, real_T c2_a[3],
  real_T c2_b[3])
{
  real_T c2_c;
  int32_T c2_ix;
  int32_T c2_iy;
  int32_T c2_k;
  int32_T c2_b_a;
  int32_T c2_c_a;
  c2_c_eml_scalar_eg(chartInstance);
  c2_c_eml_scalar_eg(chartInstance);
  c2_c = 0.0;
  c2_ix = 1;
  c2_iy = 1;
  for (c2_k = 1; c2_k < 4; c2_k++) {
    c2_c += c2_a[_SFD_EML_ARRAY_BOUNDS_CHECK("", c2_ix, 1, 3, 1, 0) - 1] *
      c2_b[_SFD_EML_ARRAY_BOUNDS_CHECK("", c2_iy, 1, 3, 1, 0) - 1];
    c2_b_a = c2_ix + 1;
    c2_ix = c2_b_a;
    c2_c_a = c2_iy + 1;
    c2_iy = c2_c_a;
  }

  return c2_c;
}

static void c2_c_eml_scalar_eg(SFc2_modeloInstanceStruct *chartInstance)
{
}

static void c2_d_eml_scalar_eg(SFc2_modeloInstanceStruct *chartInstance)
{
}

static const mxArray *c2_j_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_i_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i107;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i107, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i107;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_j_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_modelo, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_modelo), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_modelo);
  return c2_y;
}

static uint8_T c2_k_emlrt_marshallIn(SFc2_modeloInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_modeloInstanceStruct *chartInstance)
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

void sf_c2_modelo_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4110388567U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2996390007U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(783965487U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(739347971U);
}

mxArray *sf_c2_modelo_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("ehqW1MMdWbO3nQntxFGxbD");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

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

mxArray *sf_c2_modelo_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c2_modelo(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"Hwheel\",},{M[8],M[0],T\"is_active_c2_modelo\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_modelo_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_modeloInstanceStruct *chartInstance;
    chartInstance = (SFc2_modeloInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _modeloMachineNumber_,
           2,
           1,
           1,
           2,
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
        _SFD_CV_INIT_EML(0,1,1,2,0,0,0,3,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2053);
        _SFD_CV_INIT_EML_IF(0,1,0,532,539,-1,744);
        _SFD_CV_INIT_EML_IF(0,1,1,613,634,-1,731);
        _SFD_CV_INIT_EML_FOR(0,1,0,457,467,756);
        _SFD_CV_INIT_EML_FOR(0,1,1,471,481,752);
        _SFD_CV_INIT_EML_FOR(0,1,2,988,1010,1146);
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
            1.0,0,0,(MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)
            c2_sf_marshallIn);
        }

        {
          real_T (*c2_H)[3];
          real_T (*c2_Hwheel)[4];
          c2_Hwheel = (real_T (*)[4])ssGetOutputPortSignal(chartInstance->S, 1);
          c2_H = (real_T (*)[3])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_H);
          _SFD_SET_DATA_VALUE_PTR(1U, *c2_Hwheel);
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
  return "qJrtglvNcihQYw6blvXgnB";
}

static void sf_opaque_initialize_c2_modelo(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_modeloInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c2_modelo((SFc2_modeloInstanceStruct*) chartInstanceVar);
  initialize_c2_modelo((SFc2_modeloInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_modelo(void *chartInstanceVar)
{
  enable_c2_modelo((SFc2_modeloInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_modelo(void *chartInstanceVar)
{
  disable_c2_modelo((SFc2_modeloInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_modelo(void *chartInstanceVar)
{
  sf_c2_modelo((SFc2_modeloInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_modelo(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_modelo((SFc2_modeloInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_modelo();/* state var info */
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

extern void sf_internal_set_sim_state_c2_modelo(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_modelo();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_modelo((SFc2_modeloInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_modelo(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_modelo(S);
}

static void sf_opaque_set_sim_state_c2_modelo(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c2_modelo(S, st);
}

static void sf_opaque_terminate_c2_modelo(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_modeloInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_modelo_optimization_info();
    }

    finalize_c2_modelo((SFc2_modeloInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_modelo((SFc2_modeloInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_modelo(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_modelo((SFc2_modeloInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_modelo(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_modelo_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2681599529U));
  ssSetChecksum1(S,(861251459U));
  ssSetChecksum2(S,(2039859942U));
  ssSetChecksum3(S,(1220141354U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_modelo(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_modelo(SimStruct *S)
{
  SFc2_modeloInstanceStruct *chartInstance;
  chartInstance = (SFc2_modeloInstanceStruct *)utMalloc(sizeof
    (SFc2_modeloInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_modeloInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_modelo;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_modelo;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_modelo;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_modelo;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_modelo;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_modelo;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_modelo;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_modelo;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_modelo;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_modelo;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_modelo;
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

void c2_modelo_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_modelo(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_modelo(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_modelo(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_modelo_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
