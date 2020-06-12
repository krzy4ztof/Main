#version 430 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

void main(){

    // Output color = color of the texture at the specified UV
    color = texture( myTextureSampler, UV );

}


/*

#version 430 core                                                              
                                                                               
uniform sampler2D s;                                                           
                                                                               
out vec4 color;                                                                
                                                                               
void main(void)                                                                
{                                                                              
    color = texture(s, gl_FragCoord.xy / textureSize(s, 0));
    //color = vec4(0,0,1,1); //blue                   
} 
*/      
                                                                       