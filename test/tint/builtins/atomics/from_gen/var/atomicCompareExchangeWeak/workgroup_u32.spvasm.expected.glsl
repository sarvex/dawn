#version 310 es

struct atomic_compare_exchange_resultu32 {
  uint old_value;
  bool exchanged;
};


struct x__atomic_compare_exchange_resultu32 {
  uint old_value;
  bool exchanged;
};

uint local_invocation_index_1 = 0u;
shared uint arg_0;
void atomicCompareExchangeWeak_83580d() {
  uint arg_1 = 0u;
  uint arg_2 = 0u;
  x__atomic_compare_exchange_resultu32 res = x__atomic_compare_exchange_resultu32(0u, false);
  arg_1 = 1u;
  arg_2 = 1u;
  uint x_21 = arg_2;
  uint x_22 = arg_1;
  atomic_compare_exchange_resultu32 atomic_compare_result;
  atomic_compare_result.old_value = atomicCompSwap(arg_0, x_22, x_21);
  atomic_compare_result.exchanged = atomic_compare_result.old_value == x_22;
  atomic_compare_exchange_resultu32 tint_symbol = atomic_compare_result;
  uint old_value_1 = tint_symbol.old_value;
  uint x_23 = old_value_1;
  x__atomic_compare_exchange_resultu32 tint_symbol_1 = x__atomic_compare_exchange_resultu32(x_23, (x_23 == x_21));
  res = tint_symbol_1;
  return;
}

void compute_main_inner(uint local_invocation_index_2) {
  atomicExchange(arg_0, 0u);
  barrier();
  atomicCompareExchangeWeak_83580d();
  return;
}

void compute_main_1() {
  uint x_40 = local_invocation_index_1;
  compute_main_inner(x_40);
  return;
}

void compute_main(uint local_invocation_index_1_param) {
  {
    atomicExchange(arg_0, 0u);
  }
  barrier();
  local_invocation_index_1 = local_invocation_index_1_param;
  compute_main_1();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main(gl_LocalInvocationIndex);
  return;
}
