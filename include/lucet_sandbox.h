#ifndef LUCET_SANDBOX_H
#define LUCET_SANDBOX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

struct LucetSandboxInstance;
typedef struct LucetSandboxInstance LucetSandboxInstance;

enum LucetValueType {
  LucetValueType_I32,
  LucetValueType_I64,
  LucetValueType_F32,
  LucetValueType_F64,
  LucetValueType_Void
};

typedef struct {
  enum LucetValueType val_type;
  union {
    uint32_t u32;
    uint64_t u64;
    float f32;
    double f64;
  };
} LucetValue;

typedef struct {
  enum LucetValueType ret;
  uint32_t parameter_cnt;
  LucetValueType *parameters;
} LucetFunctionSignature;

typedef struct {
  uint64_t ty;
  uint64_t rf;
} LucetFunctionTableElement;

typedef struct {
  LucetFunctionTableElement *data;
  size_t length;
} LucetFunctionTable;

void lucet_ensure_linked();
LucetSandboxInstance *lucet_load_module(const char *lucet_module_path);
void lucet_drop_module(LucetSandboxInstance *inst);

uint32_t lucet_lookup_function(LucetSandboxInstance *inst,
                                const char *fn_name);
void lucet_run_function_return_void(LucetSandboxInstance *inst,
                                    const char *fn_name, int argc,
                                    LucetValue *argv);
uint32_t lucet_run_function_return_u32(LucetSandboxInstance *inst,
                                       const char *fn_name, int argc,
                                       LucetValue *argv);
uint64_t lucet_run_function_return_u64(LucetSandboxInstance *inst,
                                       const char *fn_name, int argc,
                                       LucetValue *argv);
float lucet_run_function_return_f32(LucetSandboxInstance *inst,
                                    const char *fn_name, int argc,
                                    LucetValue *argv);
double lucet_run_function_return_f64(LucetSandboxInstance *inst,
                                     const char *fn_name, int argc,
                                     LucetValue *argv);

uintptr_t lucet_get_reserved_callback_slot_val(void *inst,
                                               uint32_t slot_number);
LucetFunctionTable lucet_get_function_pointer_table(void *inst);
int32_t lucet_get_function_type_index(void *inst, LucetFunctionSignature csig);

void *lucet_get_heap_base(LucetSandboxInstance *inst);
size_t lucet_get_heap_size(LucetSandboxInstance *inst);
void *lucet_get_unsandboxed_ptr(void *inst, uintptr_t sandboxed_ptr);
uintptr_t lucet_get_sandboxed_ptr(void *inst, void *unsandboxed_ptr);

#ifdef __cplusplus
}
#endif

#endif