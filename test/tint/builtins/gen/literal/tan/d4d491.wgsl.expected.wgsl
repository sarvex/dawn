enable f16;

fn tan_d4d491() {
  var res : f16 = tan(f16());
}

@vertex
fn vertex_main() -> @builtin(position) vec4<f32> {
  tan_d4d491();
  return vec4<f32>();
}

@fragment
fn fragment_main() {
  tan_d4d491();
}

@compute @workgroup_size(1)
fn compute_main() {
  tan_d4d491();
}