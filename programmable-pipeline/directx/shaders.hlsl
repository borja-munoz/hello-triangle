/* vertex attributes (input to the vertex shader) */
struct vs_in {
    float3 position_local : POS;
    float3 color : COL;
};

/* outputs from vertex shader */
struct vs_out {
    float4 position_clip : SV_POSITION; // required output of VS
    float3 color : COL;
};

vs_out vs_main(vs_in input) {
  vs_out output = (vs_out)0; 
  output.position_clip = float4(input.position_local, 1.0);
  output.color = input.color;
  return output;
}

float4 ps_main(vs_out input) : SV_TARGET {
  return float4(input.color, 1.0); // RGBA colour
}