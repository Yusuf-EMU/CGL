#version 440 core

layout(location = 0) in vec4 position;

out vec2 tex_coords;

uniform vec3 rotation;
uniform vec3 translation;
uniform vec3 scale;

uniform mat4 projection;

mat4 rotate_mat(float angle,vec3 vec,mat4 mat) {
    float s = sin(angle);
    float c = cos(angle);
    float C = 1.0 - c;

    float xx = vec.x * vec.x;
    float xy = vec.x * vec.y;
    float xz = vec.x * vec.z;
    float yy = vec.y * vec.y, yz = vec.y * vec.z;
    float zz = vec.z * vec.z;
    float rm00 = xx * C + c;
    float rm01 = xy * C + vec.z * s;
    float rm02 = xz * C - vec.y * s;
    float rm10 = xy * C - vec.z * s;
    float rm11 = yy * C + c;
    float rm12 = yz * C + vec.x * s;
    float rm20 = xz * C + vec.y * s;
    float rm21 = yz * C - vec.x * s;
    float rm22 = zz * C + c;

    float nm00 = mat[0][0] * rm00 + mat[1][0] * rm01 + mat[2][0] * rm02;
    float nm01 = mat[0][1] * rm00 + mat[1][1] * rm01 + mat[2][1] * rm02;
    float nm02 = mat[0][2] * rm00 + mat[1][2] * rm01 + mat[2][2] * rm02;
    float nm03 = mat[0][3] * rm00 + mat[1][3] * rm01 + mat[2][3] * rm02;
    float nm10 = mat[0][0] * rm10 + mat[1][0] * rm11 + mat[2][0] * rm12;
    float nm11 = mat[0][1] * rm10 + mat[1][1] * rm11 + mat[2][1] * rm12;
    float nm12 = mat[0][2] * rm10 + mat[1][2] * rm11 + mat[2][2] * rm12;
    float nm13 = mat[0][3] * rm10 + mat[1][3] * rm11 + mat[2][3] * rm12;
 
    mat[0][0] = nm00;
    mat[0][1] = nm01;
    mat[0][2] = nm02;
    mat[0][3] = nm03;
    mat[1][0] = nm10;
    mat[1][1] = nm11;
    mat[1][2] = nm12;
    mat[1][3] = nm13;
    mat[2][0] = mat[0][0] * rm20 + mat[1][0] * rm21 + mat[2][0] * rm22;
    mat[2][1] = mat[0][1] * rm20 + mat[1][1] * rm21 + mat[2][1] * rm22;
    mat[2][2] = mat[0][2] * rm20 + mat[1][2] * rm21 + mat[2][2] * rm22;
    mat[2][3] = mat[0][3] * rm20 + mat[1][3] * rm21 + mat[2][3] * rm22;
    mat[3][0] = mat[3][0];
    mat[3][1] = mat[3][1];
    mat[3][2] = mat[3][2];
    mat[3][3] = mat[3][3];
    return mat;
}

mat4 scale_mat(vec3 vec, mat4 mat) {
    mat[0][0] = mat[0][0] * vec.x;
    mat[0][1] = mat[0][1] * vec.x;
    mat[0][2] = mat[0][2] * vec.x;
    mat[0][3] = mat[0][3] * vec.x;
    mat[1][0] = mat[1][0] * vec.y;
    mat[1][1] = mat[1][1] * vec.y;
    mat[1][2] = mat[1][2] * vec.y;
    mat[1][3] = mat[1][3] * vec.y;
    mat[2][0] = mat[2][0] * vec.z;
    mat[2][1] = mat[2][1] * vec.z;
    mat[2][2] = mat[2][2] * vec.z;
    mat[2][3] = mat[2][3] * vec.z;
    mat[3][0] = mat[3][0];
    mat[3][1] = mat[3][1];
    mat[3][2] = mat[3][2];
    mat[3][3] = mat[3][3];
    return mat;
}

mat4 translate_mat(vec3 vec, mat4 mat) {
    mat[3][0] = mat[0][0] * vec.x + mat[1][0] * vec.y + mat[2][0] * vec.z + mat[3][0];
    mat[3][1] = mat[0][1] * vec.x + mat[1][1] * vec.y + mat[2][1] * vec.z + mat[3][1];
    mat[3][2] = mat[0][2] * vec.x + mat[1][2] * vec.y + mat[2][2] * vec.z + mat[3][2];
    mat[3][3] = mat[0][3] * vec.x + mat[1][3] * vec.y + mat[2][3] * vec.z + mat[3][3];
    return mat;
}

void main() {
    mat4 transform = mat4(1.0f);
    
    transform = rotate_mat(rotation.x, vec3(1.0f, 0.0f, 0.0f), transform);
    transform = rotate_mat(rotation.y, vec3(0.0f, 1.0f, 0.0f), transform);
    transform = rotate_mat(rotation.z, vec3(0.0f, 0.0f, 1.0f), transform);

    transform = scale_mat(scale, transform);

    transform = translate_mat(translation, transform);

    gl_Position = 
        //projection * 
        transform * 
        position;
        
    tex_coords = position.xy;
}