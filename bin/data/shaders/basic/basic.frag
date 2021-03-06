#version 150

uniform sampler2DRect tex0;
uniform float hue;
uniform float brightness;
uniform float contrast;
uniform float saturation;

in vec2 texCoordVarying;
out vec4 outputColor;

//https://gist.github.com/jashmenn/5328940
vec3 ContrastSaturationBrightness(vec3 color, float brt, float sat, float con) {
    // Increase or decrease theese values to adjust r, g and b color channels seperately
    const float AvgLumR = 1.0;
    const float AvgLumG = 1.0;
    const float AvgLumB = 1.0;
    
    const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);
    
    vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);
    vec3 brtColor = color * brt;
    vec3 intensity = vec3(dot(brtColor, LumCoeff));
    vec3 satColor = mix(intensity, brtColor, sat);
    vec3 conColor = mix(AvgLumin, satColor, con);
    return conColor;
}

void main() {

    vec4 color = texture(tex0, texCoordVarying);
    vec3 col = ContrastSaturationBrightness(color.rgb, brightness, saturation, contrast);
    
    outputColor = vec4(col, color.a);
}
