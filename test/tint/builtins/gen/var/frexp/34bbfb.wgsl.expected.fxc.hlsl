struct frexp_result_vec4 {
  float4 fract;
  int4 exp;
};
void frexp_34bbfb() {
  frexp_result_vec4 res = {(0.5f).xxxx, (1).xxxx};
}

struct tint_symbol {
  float4 value : SV_Position;
};

float4 vertex_main_inner() {
  frexp_34bbfb();
  return (0.0f).xxxx;
}

tint_symbol vertex_main() {
  const float4 inner_result = vertex_main_inner();
  tint_symbol wrapper_result = (tint_symbol)0;
  wrapper_result.value = inner_result;
  return wrapper_result;
}

void fragment_main() {
  frexp_34bbfb();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  frexp_34bbfb();
  return;
}