#ifdef GL_ES
precision mediump float;
#endif
uniform float Hue; //色相
uniform float Sat; //饱和度
uniform float Lig; //明度
uniform float Bri; //亮度
uniform float mode;
uniform vec2 TextureSize;
uniform vec2 resolution;
uniform vec3 GlowColor;//发光色
uniform float GlowRange;//发光范围
uniform float GlowExpand; //发光强度
uniform vec3  OutlineColor;//描边颜色
uniform float OutlineRange;//描边范围
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
void main(){
    float radius=0.005;
    vec4 normal = texture2D(jjxx, vec2(jjv_texCoord.x, jjv_texCoord.y));
    vec4 accum;
   accum += texture2D(jjxx, vec2(jjv_texCoord.x - radius, jjv_texCoord.y - radius));
    accum += texture2D(jjxx, vec2(jjv_texCoord.x + radius, jjv_texCoord.y - radius));
    accum += texture2D(jjxx, vec2(jjv_texCoord.x + radius, jjv_texCoord.y + radius));
    accum += texture2D(jjxx, vec2(jjv_texCoord.x - radius, jjv_texCoord.y + radius));
    
    accum *=1.0;
    accum.rgb =  vec3(1,1,0) * accum.a;
    //accum.a = 1;
    normal = ( accum * (1.0 - normal.a)) + (normal * normal.a);
    gl_FragColor =normal;
    
}