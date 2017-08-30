#ifdef GL_ES
precision mediump float;
#endif
uniform float Hue; //ɫ��
uniform float Sat; //���Ͷ�
uniform float Lig; //����
uniform float Bri; //����
uniform float mode;
uniform vec2 TextureSize;
uniform vec2 resolution;
uniform vec3 GlowColor;//����ɫ
uniform float GlowRange;//���ⷶΧ
uniform float GlowExpand; //����ǿ��
uniform vec3  OutlineColor;//�����ɫ
uniform float OutlineRange;//��߷�Χ
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