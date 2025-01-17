#version 310 es

struct atomic_compare_exchange_resulti32 {
  int old_value;
  bool exchanged;
};


struct x__atomic_compare_exchange_resulti32 {
  int old_value;
  bool exchanged;
};

uint local_invocation_index_1 = 0u;
shared int arg_0;
void atomicCompareExchangeWeak_e88938() {
  int arg_1 = 0;
  int arg_2 = 0;
  x__atomic_compare_exchange_resulti32 res = x__atomic_compare_exchange_resulti32(0, false);
  arg_1 = 1;
  arg_2 = 1;
  int x_22 = arg_2;
  int x_23 = arg_1;
  atomic_compare_exchange_resulti32 atomic_compare_result;
  atomic_compare_result.old_value = atomicCompSwap(arg_0, x_23, x_22);
  atomic_compare_result.exchanged = atomic_compare_result.old_value == x_23;
  atomic_compare_exchange_resulti32 tint_symbol = atomic_compare_result;
  int old_value_1 = tint_symbol.old_value;
  int x_24 = old_value_1;
  x__atomic_compare_exchange_resulti32 tint_symbol_1 = x__atomic_compare_exchange_resulti32(x_24, (x_24 == x_22));
  res = tint_symbol_1;
  return;
}

void compute_main_inner(uint local_invocation_index_2) {
  atomicExchange(arg_0, 0);
  barrier();
  atomicCompareExchangeWeak_e88938();
  return;
}

void compute_main_1() {
  uint x_41 = local_invocation_index_1;
  compute_main_inner(x_41);
  return;
}

void compute_main(uint local_invocation_index_1_param) {
  {
    atomicExchange(arg_0, 0);
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
